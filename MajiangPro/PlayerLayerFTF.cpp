//
//  PlayerLayerFTF.cpp
//  MaJiong
//
//  Created by HalloWorld on 13-3-4.
//
//

#include "PlayerLayerFTF.h"

PlayerLayer * PlayerLayerFTF::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
    PlayerLayerFTF *player = new PlayerLayerFTF;
    if (player != NULL && player->initWithColor(color, width, height)) {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}
bool PlayerLayerFTF::initWithColor(const ccColor4B& color, GLfloat width, GLfloat height)
{
    if (!PlayerLayer::initWithColor(color, width, height)) {
        return false;
    }
    categary = PlayerCategaryPerson;
    return true;
}

void PlayerLayerFTF::initLayout()
{
    if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetIpad) {
        //ipad 分数
        ScoreLabel = CCLabelBMFont::create("", "Fonts/bitmapFontTest4.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentLeft);
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

void PlayerLayerFTF::setScore(const char *score)
{
    std::string str = ":";
    str = str + score;
    ScoreLabel->setString(str.c_str());
}
