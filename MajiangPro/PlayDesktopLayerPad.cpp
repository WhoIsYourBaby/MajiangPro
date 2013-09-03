
#include "PlayDesktopLayerPad.h"
#include "MaJiongSprite.h"
#include "Definition.h"
#include "PlayerLayerFTF.h"
#include <dispatch/dispatch.h>
#include "GameOverScenePVP.h"


using namespace cocos2d;

PlayDesktopLayerPad::PlayDesktopLayerPad()
{
}
PlayDesktopLayerPad::~PlayDesktopLayerPad()
{
}

bool PlayDesktopLayerPad::init()
{
    if (!DesktopLayer::init()) {
        return false;
    }
    
    CCLabelBMFont *label = CCLabelBMFont::create("VS", "Fonts/bitmapFontTest4.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentCenter);
    addChild(label, -1);
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    label->setPosition( ccp(s.width/2, s.height/2) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );
    label->setScale(2.0);
    
    return true;
}

void PlayDesktopLayerPad::initializePlayer()
{
    //两人同玩一pad对战
    Player1 = PlayerLayerFTF::create(ccc4(200, 200, 200, 100), 150, 60);
    Player1->setPosition(ccp(500,20));
    this->addChild(Player1);
    Player1->setScore((uint16_t)0);
    Player1->setCurrent(false);
    Player1->setUserName("Player1");
    Player1->addTargetAndSelector(this, callfuncO_selector(PlayDesktopLayerPad::handdleTurnPlayer));
    
    Player2 = PlayerLayerFTF::create(ccc4(200, 200, 200, 100), 150, 60);
    Player2->setPosition(ccp(115,944));
    this->addChild(Player2);
    Player2->setScore((uint16_t)0);
    Player2->setCurrent(false);
    Player2->setRotation(180);
    Player2->setUserName("Player2");
    Player2->addTargetAndSelector(this, callfuncO_selector(PlayDesktopLayerPad::handdleTurnPlayer));
    
    Player1->setCurrent(true);
    Player1->startProgress(10);
}

void PlayDesktopLayerPad::initializeMajiong()
{
    for (int i = 9; i > 0; i --) {
        for (int j = 0; j < 4; j ++) {
            char name[111];
            sprintf(name, "1%d.png", i);
            MaJiongSprite *mj = MaJiongSprite::MaJiongWithFile(name);
            mj->AddSelectedObserver(this);
            MajiongsArray->addObject(mj);
            
            sprintf(name, "3%d.png", i);
            MaJiongSprite *mj1 = MaJiongSprite::MaJiongWithFile(name);
            mj1->AddSelectedObserver(this);
            MajiongsArray->addObject(mj1);
            
//            mj->setVisible(false);
//            mj1->setVisible(false);
        }
    }
    randMaJiang();
}

void PlayDesktopLayerPad::randMaJiang()
{
    srand(time(NULL));
    int count = MajiongsArray->count();
    //产生一个0~72的随机序列数组
    int randIndex[72] = {0};
    int temp[72] = {0};
    for (int i = 0; i < 72; i++) {
        temp[i] = i;
    }
    
    int l = 71;
    for (int i = 0; i < 72; i ++) {
        int t = rand() % (72 - i);
        randIndex[i] = temp[t];
        temp[t] = temp[l];
        l --;
    }
    
    /*/输出
    printf("\n{");
    for (int i = 0; i < 72; i ++) {
    printf("%d, ", randIndex[i]);
    }
    printf("}\n");
    //*/
    
    //打乱所有麻将位置
    for (int i = 0; i < kMaxX; i ++) {
        for (int j = 0; j < kMaxY; j ++) {
            MaJiongSprite *majiong = (MaJiongSprite *)MajiongsArray->objectAtIndex(randIndex[i * kMaxY + j]);
            int x = i+1;
            int y = j+1;
            majiong->setOriginCoord(x, y);
            if (majiong->isVisible()) {
                DesktopMap[x][y] = DesktopStateMaJiong;
            } else {
                DesktopMap[x][y] = DesktopStateNone;
            }
            MJWidth = majiong->boundingBox().size.width;
            MJHeight = majiong->boundingBox().size.height;
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            if (fabs(winSize.width - 768) < 0.01) {
                //ipad
                majiong->setPosition(ccp(OriginRootPad.x + MJWidth * x, OriginRootPad.y + MJHeight * y));
            } else {
                majiong->setPosition(ccp(OriginRoot.x + MJWidth * x, OriginRoot.y + MJHeight * y));
            }
            if (getChildByTag(i * kMaxY + j) == NULL) {
                this->addChild(majiong, 0, i * kMaxY + j);
            }
            count --;
        }
    }
}

void PlayDesktopLayerPad::SelectMajiong(MaJiongSprite *mj)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("select.mp3");
    if (tempSelectMajiong && mj) {
        if (tempSelectMajiong->isEqualTo(mj) && tempSelectMajiong != mj) {//1 在这个条件里面判断两麻将是否能联通
            //前后选择的两个麻将花色与大小相同
            vector<CCPoint> *linkPath = link(tempSelectMajiong->OringCoord, mj->OringCoord);
            if (linkPath != NULL) {//如果有路径可以连通
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("disappear.mp3");
                //1绘制路径
                MaJiongDrawLinkPath(linkPath);
                //2消去两麻将
                SetDesktopState(tempSelectMajiong->OringCoord, DesktopStateNone);
                tempSelectMajiong->Disappear();
                SetDesktopState(mj->OringCoord, DesktopStateNone);
                mj->Disappear();
                //3当前玩家加分
                PlayerLayer *pl = getCurrentPlayer();
                pl->addScore(tempSelectMajiong->getMJScore());
                handdleTurnPlayer(pl);
                //4释放数组
                tempSelectMajiong = NULL;
                delete linkPath;
                linkPath = NULL;
            } else {
                tempSelectMajiong->Diselect();
                tempSelectMajiong = mj;
            }
        } else {
            tempSelectMajiong->Diselect();
            tempSelectMajiong = mj;
        }
    } else tempSelectMajiong = mj;
}

CCPoint PlayDesktopLayerPad::PositionOfCoord(CCPoint p)
{
    CCPoint pr = ccp(OriginRootPad.x + MJWidth * p.x, OriginRootPad.y + MJHeight * p.y);
    return pr;
}

void PlayDesktopLayerPad::handdleTurnPlayer(PlayerLayer *player)
{
    if (tempSelectMajiong) {
        tempSelectMajiong->Diselect();
        tempSelectMajiong = NULL;
    }
    
    Player1->currentSwitch();
    Player2->currentSwitch();
    
    bool hasVisible = false;
    CCObject *obj = NULL;
    CCARRAY_FOREACH(MajiongsArray, obj){
        MaJiongSprite *mj = (MaJiongSprite *)obj;
        if (mj->isVisible()) {
            hasVisible = true;
        }
    }
    if (!hasVisible) {   //还有显示的麻将直接返回,不执行后面的
        //游戏正常结束逻辑
        GameOver();
        return ;
    }
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        std::vector<CCPoint> *path = thereIsLink();
        if (path == NULL) {
            //调整麻将位置
            printf("\nNeed to random MJ Position!");
            dispatch_async(dispatch_get_main_queue(), ^{
                randMaJiang();
                getCurrentPlayer()->startProgress(10);
            });
        } else {
            std::vector<CCPoint>::iterator it = path->begin();
            printf("\n(%f, %f)", (*it).x, (*it).y);
        }
    });
}

void PlayDesktopLayerPad::GameOver()
{
    GameLayerScene *gameover = GameOverScenePVP::createWithScore(Player1->getScore(), Player2->getScore());
//    GameLayerScene *gameover = GameOverScenePVP::createWithScore(2,2);
    gameover->setPlayAgainCategary(DesktopLayerPVP);
    CCDirector::sharedDirector()->replaceScene(gameover);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("gameover.mp3");
}
