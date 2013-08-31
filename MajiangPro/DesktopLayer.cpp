//
//  DesktopLayer.cpp
//  MaJiong
//
//  Created by HalloWorld on 13-1-29.
//
//

#include "DesktopLayer.h"

using namespace std;

DesktopLayer::DesktopLayer()
{
    tempDrawList = NULL;
}

DesktopLayer::~DesktopLayer()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kStringPlayerStopNotiName);
    MajiongsArray->release();
    if (tempDrawList) {
        CC_SAFE_DELETE(tempDrawList);
    }
}

bool DesktopLayer::init()
{
    if (CCLayerColor::init()) {
        this->setColor(ccc3(100, 100, 100));
        tempSelectMajiong = NULL;
        MJHeight = 0.f;
        MJWidth = 0.f;
        
        //add 双人单击对战button
        CCLabelBMFont *label = CCLabelBMFont::create("", "Fonts/bitmapFontTest4.fnt");
        label->setAlignment(kCCTextAlignmentCenter);
        CCScale9Sprite *bg = CCScale9Sprite::create("back.png");
        CCControlButton *btn = CCControlButton::create(label, bg);
        btn->setAdjustBackgroundImage(false);
        btn->addTargetWithActionForControlEvents(this, cccontrol_selector(DesktopLayer::menuBackCallback), CCControlEventTouchDown);
        CCSize s = btn->getContentSize();
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        btn->setPosition(s.width/2+20, winSize.height - s.height/2 - 20);
        addChild(btn);
        
        MajiongsArray = CCArray::createWithCapacity(72);
        MajiongsArray->retain();
        this->initializeMajiong();
        this->initializePlayer();
        
        return true;
    } else return false;
}

void DesktopLayer::menuBackCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->popScene();
}

bool DesktopLayer::canLinkOnLineOnX(const CCPoint &pf, const CCPoint &pt)
{
    if (pf.equals(pt)) {
        return false;
    }
    
    if (fabsf(pf.y - pt.y) < 0.0001) {
        //两点在同一X轴上
        CCPoint pLow = (pf.x > pt.x) ? pt : pf;
        int xx = (int)fabsf(pf.x - pt.x);
        bool icanConnect = true;
        for (int i = 1; i < xx; i ++) {
            CCPoint np = ccp(pLow.x+i, pLow.y);
            DesktopState status = DesktopMapState(np);
            if (status != DesktopStateNone) {
                icanConnect = false;
            }
        }
        return icanConnect;
    }
    return false;
}

bool DesktopLayer::canLinkOnLineOnY(const CCPoint &pf, const CCPoint &pt)
{
    if (pf.equals(pt)) {
        return false;
    }
    
    if (fabsf(pf.x - pt.x) < 0.0001) {
        //两点在同一Y轴上
        CCPoint pLow = (pf.y > pt.y) ? pt : pf;
        int yy = (int)fabsf(pf.y - pt.y);
        bool icanConnect = true;
        for (int i = 1; i < yy; i ++) {
            CCPoint np = ccp(pLow.x, pLow.y+i);
            DesktopState status = DesktopMapState(np);
            if (status != DesktopStateNone) {
                icanConnect = false;
                break;
            }
        }
        return icanConnect;
    }
    return false;
}


bool DesktopLayer::canLinkOnLine(const CCPoint &pf, const CCPoint &pt)
{
    bool bx = canLinkOnLineOnX(pf, pt);
    bool by = canLinkOnLineOnY(pf, pt);
    return bx || by;
}

//连连看消去算法
std::vector<CCPoint> *DesktopLayer::link(cocos2d::CCPoint pFrom, cocos2d::CCPoint pTo)
{
    if (pFrom.equals(pTo)) {
        return NULL;
    }
    
    if (canLinkOnLine(pFrom, pTo)) {
        /*
        CCArray *arr = CCArray::create((CCPoint *)&pFrom, (CCPoint *)&pTo, NULL);
        arr->retain();
        return arr;
         */
        vector<CCPoint> *arr = new vector<CCPoint>;
        arr->push_back(pFrom);
        arr->push_back(pTo);
        return arr;
    }
    
    //判断一拐点相连
    CCPoint g1 = ccp(pFrom.x, pTo.y);
    if (DesktopMapState(g1) ==DesktopStateNone && canLinkOnLine(g1, pFrom) && canLinkOnLine(g1, pTo)) {
        /*
        CCArray *arr = CCArray::create((CCPoint *)&pFrom, (CCPoint *)&g1, (CCPoint *)&pTo, NULL);
        arr->retain();
        return arr;
         */
        vector<CCPoint> *arr = new vector<CCPoint>;
        arr->push_back(pFrom);
        arr->push_back(g1);
        arr->push_back(pTo);
        return arr;
    }
    
    CCPoint g2 = ccp(pTo.x, pFrom.y);
    if (DesktopMapState(g2) ==DesktopStateNone && canLinkOnLine(g2, pFrom) && canLinkOnLine(g2, pTo)) {
        /*
        CCArray *arr = CCArray::create((CCPoint *)&pFrom, (CCPoint *)&g2, (CCPoint *)&pTo, NULL);
        arr->retain();
        return arr;
         */
        vector<CCPoint> *arr = new vector<CCPoint>;
        arr->push_back(pFrom);
        arr->push_back(g2);
        arr->push_back(pTo);
        return arr;
    }
    
    //判断两个拐点相连
    //DesktopMap[10][11]
    //先纵向
    for (int x = 0; x < kMatrixMaxX; x ++) {
        CCPoint pf = ccp(x, pFrom.y);
        CCPoint pt = ccp(x, pTo.y);
        if (DesktopMapState(pf) == DesktopStateNone && DesktopMapState(pt) == DesktopStateNone) {
            if (canLinkOnLine(pFrom, pf) && canLinkOnLine(pf, pt) && canLinkOnLine(pt, pTo)) {
                /*
                CCArray *arr = CCArray::create((CCPoint *)&pFrom, (CCPoint *)&pf, (CCPoint *)&pt,(CCPoint *)&pTo, NULL);
                arr->retain();
                return arr;
                 */
                vector<CCPoint> *arr = new vector<CCPoint>;
                arr->push_back(pFrom);
                arr->push_back(pf);
                arr->push_back(pt);
                arr->push_back(pTo);
                return arr;
            }
        }
    }
    //再横向
    for (int y = 0; y < kMatrixMaxY; y ++) {
        CCPoint pf = ccp(pFrom.x, y);
        CCPoint pt = ccp(pTo.x, y);
        if (DesktopMapState(pf) == DesktopStateNone && DesktopMapState(pt) == DesktopStateNone) {
            if (canLinkOnLine(pFrom, pf) && canLinkOnLine(pf, pt) && canLinkOnLine(pt, pTo)) {
                /*
                CCArray *arr = CCArray::create((CCPoint *)&pFrom, (CCPoint *)&pf, (CCPoint *)&pt,(CCPoint *)&pTo, NULL);
                arr->retain();
                return arr;
                 */
                vector<CCPoint> *arr = new vector<CCPoint>;
                arr->push_back(pFrom);
                arr->push_back(pf);
                arr->push_back(pt);
                arr->push_back(pTo);
                return arr;
            }
        }
    }
    
    return NULL;
}

CCPoint DesktopLayer::PositionOfCoord(CCPoint p)
{
    return ccp(0, 0);
}

void DesktopLayer::draw()
{
    CCLayerColor::draw();
//    glEnable(GL_LINE_SMOOTH);
    glLineWidth(8);
    ccDrawColor4B(255,0,0,255);

    if (tempDrawList) {
        //draw
        int count = tempDrawList->size();
        CCPoint *path = new CCPoint[count];
        for (int i = 0; i < count; i ++) {
            path[i] = PositionOfCoord((*tempDrawList)[i]);
        }
        ccDrawPoly(path, count, false);
        CC_SAFE_DELETE_ARRAY(path);
        CC_SAFE_DELETE(tempDrawList);
    }
}

void DesktopLayer::MaJiongDrawLinkPath(vector<CCPoint> *arr)
{
    tempDrawList = new vector<CCPoint>(*arr);
    /*/
    CCParticleSystemQuad *par = CCParticleSystemQuad::create("path.plist");
    vector<CCPoint>::iterator it = arr->begin();
    CCPoint p1 = *it;
    par->setPosition(PositionOfCoord(p1));
    this->addChild(par, 100);
    it++;
    CCPoint p2 = *it;
    CCActionInterval *mov1 = CCMoveTo::create(0.5, PositionOfCoord(p2));
    CCArray *seqArr = CCArray::createWithObject(mov1);
    
    if (arr->size() > 2) {
        it ++;
        CCPoint p3 = *it;
        CCActionInterval *mov2 = (CCActionInterval *)CCMoveTo::create(0.5, PositionOfCoord(p3));
        seqArr->addObject(mov2);
    }
    if (arr->size() > 3) {
        it ++;
        CCPoint p4 = *it;
        CCActionInterval *mov3 = (CCActionInterval *)CCMoveTo::create(0.5, PositionOfCoord(p4));
        seqArr->addObject(mov3);
    }
    CCActionInterval *call = (CCActionInterval *)CCCallFuncND::create(this, callfuncND_selector(DesktopLayer::particleDispear), (void *)par);
    seqArr->addObject(call);
    CCActionInterval *seq = (CCActionInterval *)CCSequence::create(seqArr);
    par->runAction(seq);
    //*/
}

void DesktopLayer::particleDispear(void *par)
{
    CCParticleSystemQuad *p = (CCParticleSystemQuad *)par;
    p->removeFromParentAndCleanup(true);
}

void DesktopLayer::SetDesktopState(CCPoint p, DesktopState state)
{
    DesktopMap[(int)p.x][(int)p.y] = state;
}

DesktopState DesktopLayer::DesktopMapState(CCPoint p)
{
    return DesktopMap[(int)p.x][(int)p.y];
}

MaJiongSprite *DesktopLayer::MaJiongOfOrigin(int x, int y)
{
    int i = x -1;
    int j = y -1;
    MaJiongSprite *mj = (MaJiongSprite *)this->getChildByTag(i * kMaxY + j);
    return mj;
}

MaJiongSprite *DesktopLayer::MaJiongOfOrigin(cocos2d::CCPoint origin)
{
    return MaJiongOfOrigin(origin.x, origin.y);
}

void DesktopLayer::initializeMajiong()
{}

void DesktopLayer::initializePlayer()
{}

void DesktopLayer::SelectMajiong(MaJiongSprite *mj)
{}

void DesktopLayer::randMaJiang()
{}
void DesktopLayer::handdleTurnPlayer(PlayerLayer *player)
{}

PlayerLayer *DesktopLayer::getCurrentPlayer()
{
    if (Player1 == NULL && Player2 == NULL) {
        return NULL;
    }
    
    if (Player2 == NULL && Player1 != NULL) {
        return Player1;
    }
    
    if (Player2 != NULL && Player1 == NULL) {
        return Player2;
    }
    
    if (Player2 != NULL && Player1 != NULL) {
        if (Player1->isCurrent() && !Player2->isCurrent()) {
            return Player1;
        }
        else if (Player2->isCurrent() && !Player1->isCurrent()) {
            return Player2;
        } else return NULL;
    }
    return NULL;
}

std::vector<CCPoint> *DesktopLayer::thereIsLink()
{
    CCObject *obj = NULL;
    CCARRAY_FOREACH(MajiongsArray, obj) {
        MaJiongSprite *mj = (MaJiongSprite *)obj;
        if (mj->isVisible()) {
            std::vector<CCPoint> *path = thereIsLinkOfMJ(mj);
            if (path) return path;  //path存的路径是反的,读取的时候注意
        }
    }
    return NULL;
}

std::vector<CCPoint> *DesktopLayer::thereIsLinkOfMJ(MaJiongSprite *mj)
{
    CCPoint origin = mj->OringCoord;
    MyTreeNode *rootNode = new MyTreeNode(mj->OringCoord);
    MyTree *tree = new MyTree(rootNode);
    MyTreeNode *targetNode = addChildrenLine(rootNode, 0);
    std::vector<CCPoint> *path = NULL;
    if (targetNode) {
        printf("\ntarget(%f, %f)", targetNode->Position.x, targetNode->Position.y);
        path = new std::vector<CCPoint>;
        while (targetNode) {
            path->push_back(targetNode->Position);
            targetNode = targetNode->ParentNode();
        }
    }
    delete tree;
    return path;    //返回该返回的值
}

MyTreeNode *DesktopLayer::addChildrenLine(MyTreeNode *pNode, int turnTime)
{
    CCPoint pRoot = pNode->Position;
    //检查坐标有未越界
    assert((int)(pRoot.x) <= kMatrixMaxX && (int)(pRoot.y) <= kMatrixMaxY);
    if (turnTime > 2) {
        return NULL;
    } else {
        if (pNode->searchDirection == SearchDirectionO) {
            //1,搜索pNode直线上的可连接点, 并对每个节点都addChildrenLine(subnode, 1+turnTime)
            for (int i = 0; i < kMatrixMaxX; i ++) {
                CCPoint tempP = ccp(i, pRoot.y);
                if (canLinkOnLine(tempP, pRoot)) {
                    MyTreeNode *child = new MyTreeNode(tempP, SearchDirectionX);
                    pNode->addChildNode(child);
                    if (DesktopMapState(tempP) == DesktopStateNone) {
                        //此点没有麻将拦路,转弯继续搜索
                        MyTreeNode *rNode = addChildrenLine(child, turnTime + 1);
                        if (rNode) return rNode;
                    } else {
                        //此点有麻将,判断是否是最终解,并不继续加拐搜索
                        MaJiongSprite *mjRoot = MaJiongOfOrigin(pNode->SuperParent()->Position);
                        MaJiongSprite *mjTar = MaJiongOfOrigin(child->Position);
                        if (mjRoot->isEqualTo(mjTar)) {
                            return child;
                        }
                    }
                }
            }
            
            for (int i = 0; i < kMatrixMaxY; i ++) {
                CCPoint tempP = ccp(pRoot.x, i);
                if (canLinkOnLine(tempP, pRoot)) {
                    MyTreeNode *child = new MyTreeNode(tempP, SearchDirectionY);
                    pNode->addChildNode(child);
                    if (DesktopMapState(tempP) == DesktopStateNone) {
                        MyTreeNode *rNode = addChildrenLine(child, turnTime + 1);
                        if (rNode) return rNode;
                    } else {
                        MaJiongSprite *mjRoot = MaJiongOfOrigin(pNode->SuperParent()->Position);
                        MaJiongSprite *mjTar = MaJiongOfOrigin(child->Position);
                        if (mjRoot->isEqualTo(mjTar)) {
                            return child;
                        }
                    }
                }
            }
        }
        if (pNode->searchDirection == SearchDirectionX) {
            //
            for (int i = 0; i < kMatrixMaxY; i ++) {
                CCPoint tempP = ccp(pRoot.x, i);
                if (canLinkOnLine(tempP, pRoot)) {
                    MyTreeNode *child = new MyTreeNode(tempP, SearchDirectionY);
                    pNode->addChildNode(child);
                    if (DesktopMapState(tempP) == DesktopStateNone) {
                        MyTreeNode *rNode = addChildrenLine(child, turnTime + 1);
                        if (rNode) return rNode;
                    } else {
                        MaJiongSprite *mjRoot = MaJiongOfOrigin(pNode->SuperParent()->Position);
                        MaJiongSprite *mjTar = MaJiongOfOrigin(child->Position);
                        if (mjRoot->isEqualTo(mjTar)) {
                            return child;
                        }
                    }
                }
            }
        }
        if (pNode->searchDirection == SearchDirectionY) {
            //
            for (int i = 0; i < kMatrixMaxX; i ++) {
                CCPoint tempP = ccp(i, pRoot.y);
                if (canLinkOnLine(tempP, pRoot)) {
                    MyTreeNode *child = new MyTreeNode(tempP, SearchDirectionX);
                    pNode->addChildNode(child);
                    if (DesktopMapState(tempP) == DesktopStateNone) {
                        //此点没有麻将拦路,转弯继续搜索
                        MyTreeNode *rNode = addChildrenLine(child, turnTime + 1);
                        if (rNode) return rNode;
                    } else {
                        //此点有麻将,判断是否是最终解,并不继续加拐搜索
                        MaJiongSprite *mjRoot = MaJiongOfOrigin(pNode->SuperParent()->Position);
                        MaJiongSprite *mjTar = MaJiongOfOrigin(child->Position);
                        if (mjRoot->isEqualTo(mjTar)) {
                            return child;
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

void DesktopLayer::onEnter()
{
    CCLayerColor::onEnter();
}

void DesktopLayer::onEnterTransitionDidFinish()
{
    CCLayerColor::onEnterTransitionDidFinish();
}

void DesktopLayer::GameOver()
{
}