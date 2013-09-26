//
//  MaJiongSprite.cpp
//  MaJiong
//
//  Created by HalloWorld on 13-1-4.
//
//

#include "MaJiongSprite.h"
#include "DesktopLayer.h"

#define kTagRotate 101

MaJiongSprite* MaJiongSprite::MaJiongWithFile(const char *pszFilename)
{
    MaJiongSprite* pMaJiong = new MaJiongSprite();
    pMaJiong->initWithFile(pszFilename);
    pMaJiong->autorelease();
    return pMaJiong;
}

bool MaJiongSprite::initWithFile(const char *pszFilename)
{
    if( CCSprite::initWithFile(pszFilename) )
    {//init code
        isSelected = false;
        OringCoord = ccp(0, 0);
        char color = pszFilename[0];
        switch (color) {
            case '1':
                MJColor = MaJiongColorTiao;
                break;
            case '2':
                MJColor = MaJiongColorWan;
                break;
            case '3':
                MJColor = MaJiongColorTong;
                break;
            default:
                break;
        }
        MJScore = pszFilename[1] - 48;
    }
    return true;
}


void MaJiongSprite::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}

void MaJiongSprite::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

#pragma mark - TouchDispatcher

CCRect MaJiongSprite::rect()
{
    /*
    CCSize s = getTexture()->getContentSize();
    CCRect rect = CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
     */
    CCRect rect = this->boundingBox();
    return rect;
}

bool MaJiongSprite::containsTouchLocation(CCTouch* touch)
{
//    CCPoint p = convertTouchToNodeSpaceAR(touch);
    CCPoint p = touch->getLocation();
    return rect().containsPoint(p);
}

bool MaJiongSprite::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (!isVisible()) {
        return false;
    }
    
    PlayerLayer *py = SelectedObserver->getCurrentPlayer();
    if (py != NULL && py->getCategary() == PlayerCategaryBot) {
        return false;
    }
    bool ifContain = containsTouchLocation(touch);
    return ifContain;
}

void MaJiongSprite::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    // If it weren't for the TouchDispatcher, you would need to keep a reference
    // to the touch from touchBegan and check that the current touch is the same
    // as that one.
    // Actually, it would be even more complicated since in the Cocos dispatcher
    // you get CCSets instead of 1 UITouch, so you'd need to loop through the set
    // in each touchXXX method.
}

void MaJiongSprite::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    if (containsTouchLocation(touch)) {
        if (isSelected == false) {
            Select();
            SelectedObserver->SelectMajiong(this);
        } else {
            Diselect();
            SelectedObserver->SelectMajiong(NULL);
        }
    }
}

#pragma mark - Getter & setter

MaJiongColorEnum MaJiongSprite::getMJColor()
{
    return MJColor;
}
uint16_t MaJiongSprite::getMJScore()
{
    return MJScore;
}

bool MaJiongSprite::getSelected()
{
    return isSelected;
}

void MaJiongSprite::setOriginCoord(int x, int y)
{
    OringCoord = ccp(x, y);
}
void MaJiongSprite::setOriginCoord(CCPoint p)
{
    OringCoord = p;
}
CCPoint MaJiongSprite::getOriginCoord()
{
    return OringCoord;
}
#pragma mark - Actions

//Actions
void MaJiongSprite::Select()
{
    isSelected = true;
    
    CCRotateTo *r1 = CCRotateTo::create(0.2, 15);
    CCRotateTo *r2 = CCRotateTo::create(0.2, - 15);
    CCFiniteTimeAction *seq = CCSequence::create(r1,r2,NULL);
    CCRepeatForever *rep = CCRepeatForever::create((CCActionInterval *)seq);
    rep->setTag(kTagRotate);
    this->runAction(rep);
}

void MaJiongSprite::Diselect()
{
    isSelected = false;
    
    this->stopActionByTag(kTagRotate);
    this->setRotation(0);
}

void MaJiongSprite::Disappear()
{
    this->setVisible(false);
}

void MaJiongSprite::AddSelectedObserver(DesktopLayer *desktop)
{
    SelectedObserver = desktop;
}

bool MaJiongSprite::operator==(MaJiongSprite *mj)
{
    if (MJColor == mj->getMJColor() && MJScore == mj->getMJScore()) {//
        return true;
    }
    else return false;
}

bool MaJiongSprite::isEqualTo(MaJiongSprite *mj)
{
    if (MJColor == mj->getMJColor() && MJScore == mj->getMJScore()) { //
        return true;
    }
    else return false;
}
