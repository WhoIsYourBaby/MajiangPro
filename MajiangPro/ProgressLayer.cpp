//
//  ProgressLayer.cpp
//  MaJiong
//
//  Created by HalloWorld on 13-3-5.
//
//

#include "ProgressLayer.h"

ProgressLayer::~ProgressLayer()
{
    target = NULL;
    stopCall = NULL;
    secondCall = NULL;
}

bool ProgressLayer::init()
{
    float w = 0.0;
    float h = 0.0;
    if (kTargetIpad == CCApplication::sharedApplication()->getTargetPlatform()) {
        w = 60.0;
        h = 60.0;
    } else {
        w = 30.0;
        h = 30.0;
    }
    if (CCLayerColor::initWithColor(ccc4(200, 200, 200, 0), w, h)) {
        //init code
        progress = CCProgressTimer::create(CCSprite::create("progress.png"));
        progress->setType( kCCProgressTimerTypeRadial );
        addChild(progress);
        progress->setReverseProgress(true);
        CCSize s = getContentSize();
        progress->setPosition(CCPointMake(s.width/2, s.height/2));
        
        //init 倒计时文字
        labelSeconds = CCLabelBMFont::create("", "Fonts/bitmapFontTest4.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentCenter);
        addChild(labelSeconds);
        labelSeconds->setWidth(s.width);
        labelSeconds->setPosition( ccp(s.width/2, s.height/2) );
        labelSeconds->setAnchorPoint( ccp(0.5f, 0.5f) );
        
        return true;
    }
    return false;
}

void ProgressLayer::startProgress(uint8_t s)
{
    setVisible(true);
    ProgressSeconds = s;
    updateLabel();
    
    CCProgressTo *pt = CCProgressTo::create(1, 100);
    CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(ProgressLayer::callFunProgress));
    CCFiniteTimeAction *seq = CCSequence::create(pt,func,NULL);
    progress->setPercentage(0); //从头开始转,否则会出现从半圆开始转圈
    progress->runAction(CCRepeatForever::create((CCActionInterval *)seq));
}

void ProgressLayer::startProgressAdd(uint8_t s)
{
    uint8_t totalSec = ProgressSeconds + s;
    startProgress(totalSec);
}

void ProgressLayer::stopProgress()
{
    progress->stopAllActions();
    setVisible(false);
    if (target)
    {
		(target->*stopCall)(this);
    }
}

void ProgressLayer::callFunProgress()
{
    if (ProgressSeconds == 0) {
        stopProgress();
    } else {
        ProgressSeconds --;
        updateLabel();
        if (target) {
            (target->*secondCall)(this);
        }
    }
}

void ProgressLayer::updateLabel()
{
    char str[10];
    sprintf(str, "%d",ProgressSeconds);
    labelSeconds->setString(str);
}

void ProgressLayer::stopProgressByPlayer()
{
    progress->stopAllActions();
    setVisible(false);
}

void ProgressLayer::addTargetAndSelector(cocos2d::CCObject *tar, SEL_CallFuncO sel, SEL_CallFuncO secSel)
{
    target = tar;
    stopCall = sel;
    secondCall = secSel;
}

uint8_t ProgressLayer::getCurrentProgressSecond()
{
    return ProgressSeconds;
}