//
//  PlayerLayerBot.cpp
//  MaJiong
//
//  Created by HalloWorld on 13-4-22.
//
//

#include "PlayerLayerBot.h"
#include "DesktopLayer.h"

PlayerLayerBot::~PlayerLayerBot()
{
    mj1 = NULL;
    mj2 = NULL;
    AutoSelectDelegate = NULL;
}

void PlayerLayerBot::setAutoSelectDelegate(DesktopLayer *del)
{
    AutoSelectDelegate = del;
}

PlayerLayer * PlayerLayerBot::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
    PlayerLayerBot *player = new PlayerLayerBot;
    if (player != NULL && player->initWithColor(color, width, height)) {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}

bool PlayerLayerBot::initWithColor(const ccColor4B& color, GLfloat width, GLfloat height)
{
    if (!PlayerLayer::initWithColor(color, width, height)) {
        return false;
    }
    categary = PlayerCategaryBot;
    return true;
}

void PlayerLayerBot::initLayout()
{
    if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetIpad) {
        //ipad 分数
        ScoreLabel = CCLabelBMFont::create("", "Fonts/bitmapFontTest4.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentCenter);
        addChild(ScoreLabel);
        CCSize s = getContentSize();
        ScoreLabel->setWidth(s.width/2);
        ScoreLabel->setPosition( ccp(s.width*3/4+5, s.height/2) );
        ScoreLabel->setAnchorPoint( ccp(0.5f, 0.5f) );
        //姓名
        UserInfoLabel = CCLabelBMFont::create("", "Fonts/bitmapFontTest4.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentRight);
        addChild(UserInfoLabel);
        UserInfoLabel->setWidth(s.width/2);
        UserInfoLabel->setPosition( ccp(s.width/4+15, s.height/2) );
        UserInfoLabel->setAnchorPoint( ccp(0.5f, 0.5f) );
        UserInfoLabel->setColor(ccORANGE);
        //init 倒计时
        progressTimer = ProgressLayer::create();
        CCSize ps = progressTimer->getContentSize();
        progressTimer->setPosition(ccp(s.width+5, 0));
        progressTimer->setAnchorPoint(ccp(0.5, 0.5));
        progressTimer->setVisible(false);
        addChild(progressTimer);
        progressTimer->addTargetAndSelector(this, callfuncO_selector(PlayerLayer::handdleProgressStoped), callfuncO_selector(PlayerLayer::handdleProgressSecond));
    }else {
        //iphone
    }
}

void PlayerLayerBot::setScore(const char *score)
{
    std::string str = ":";
    str = str + score;
    ScoreLabel->setString(str.c_str());
}

void PlayerLayerBot::currentSwitch()
{
    iscurrent = !iscurrent;
    if (iscurrent) {
        startProgress(10);
    } else {
        stopProgressTimer();
    }
}


void PlayerLayerBot::optimalMJs(MaJiongSprite *m1,MaJiongSprite *m2)
{//最优选择麻将路径
    mj1 = m1;
    mj2 = m2;
}

void PlayerLayerBot::handdleProgressSecond(CCObject *obj)
{
    ProgressLayer *prog = (ProgressLayer *)obj;
    uint8_t sec = prog->getCurrentProgressSecond();
    if (10 - sec == 1) {
        //first select
        mj1->Select();
        AutoSelectDelegate->SelectMajiong(mj1);
    } else if (10 - sec == 2) {
        //second select
        mj2->Select();
        AutoSelectDelegate->SelectMajiong(mj2);
    }
}