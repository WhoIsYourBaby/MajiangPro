//
//  PlayerLayer.cpp
//  MaJiong
//
//  Created by HalloWorld on 13-2-26.
//
//

#include "PlayerLayer.h"

PlayerLayer::PlayerLayer()
{}
PlayerLayer::~PlayerLayer()
{
    stopTarget = NULL;
    handdleStopCall = NULL;
}
bool PlayerLayer::init()
{
    if (!CCLayerColor::init()) {
        return false;
    }
    //code
    return true;
}

PlayerLayer * PlayerLayer::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
    PlayerLayer *player = new PlayerLayer();
    if (player && player->initWithColor(color, width, height)) {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}

bool PlayerLayer::initWithColor(const ccColor4B& color, GLfloat width, GLfloat height)
{
    if (!CCLayerColor::initWithColor(color, width, height)) {
        return false;
    }
    iscurrent = false;
    myScore = 0;
    initLayout();
    return true;
}

void PlayerLayer::handdleProgressStoped(CCObject *obj)
{
    if (stopTarget) {
        (stopTarget->*handdleStopCall)(this);
    }
    //DesktopLayer接收此消息,其子类重写实现各种不同的功能
}

void PlayerLayer::addTargetAndSelector(CCObject *tar, SEL_CallFuncO stopSel)
{
    stopTarget = tar;
    handdleStopCall = stopSel;
}

void PlayerLayer::handdleProgressSecond(CCObject *obj)
{
}
void PlayerLayer::initLayout()
{//子类必须重写用以规划布局
}

uint16_t PlayerLayer::getScore()
{
    return myScore;
}

void PlayerLayer::setScore(const char *score)
{
}

void PlayerLayer::setUserName(const char *name)
{
    UserInfoLabel->setString(name);
}

void PlayerLayer::setScore(uint16_t sc)
{
    char score[10];
    sprintf(score, "%d", sc);
    setScore(score);
}

void PlayerLayer::addScore(uint16_t sc)
{
    myScore += sc;
    setScore(myScore);
    animateScore(sc);
}

void PlayerLayer::startProgressAdded(uint8_t added)
{
    progressTimer->startProgressAdd(added);
}

void PlayerLayer::startProgress(uint8_t s)
{
    progressTimer->startProgress(s);
}

void PlayerLayer::stopProgressTimer()
{
    progressTimer->stopProgressByPlayer();
}

bool PlayerLayer::isCurrent()
{
    return iscurrent;
}

void PlayerLayer::setCurrent(bool cur)
{
    iscurrent = cur;
}

void PlayerLayer::currentSwitch()
{
    iscurrent = !iscurrent;
    if (iscurrent) {
        startProgress(10);
    } else {
        stopProgressTimer();
    }
}

void PlayerLayer::animateScore(uint16_t sc)
{
    char str[10] = {0};
    sprintf(str, "+%d", sc);
    CCLabelBMFont *label = CCLabelBMFont::create(str, "Fonts/bitmapFontTest4.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentCenter);
    addChild(label);
    CCSize s = getContentSize();
    label->setWidth(s.width);
    label->setPosition( ccp(s.width/2 + 60, s.height/2) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );
    label->setColor(ccRED);
    
    CCArray *actions = CCArray::createWithCapacity(5);
    CCActionInterval *scale1 = CCScaleTo::create(0.25, 3.5);
    CCActionInterval *delay = CCDelayTime::create(0.5);
    CCActionInterval *scale2 = CCScaleTo::create(0.15, 1.5);
    CCActionInterval *func = (CCActionInterval *)CCCallFuncN::create(this, callfuncN_selector(PlayerLayer::animateScoreEnd));
    actions->addObject(scale1);
    actions->addObject(delay);
    actions->addObject(scale2);
    actions->addObject(func);
    CCSequence *seq = (CCSequence *)CCSequence::create(actions);
    label->runAction(seq);
}

void PlayerLayer::animateScoreEnd(CCNode *scLabel)
{
    scLabel->removeFromParentAndCleanup(true);
}

PlayerCategary PlayerLayer::getCategary()
{
    return categary;
}

uint8_t PlayerLayer::getCurrentProgressSecond()
{
    return progressTimer->getCurrentProgressSecond();
}