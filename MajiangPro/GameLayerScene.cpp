//
//  GameLayerScene.cpp
//  MaJiong
//
//  Created by HalloWorld on 13-3-21.
//
//

#include "CCControlButton.h"
#include "DesktopScene.h"
#include "GameLayerScene.h"

GameLayerScene::GameLayerScene()
{}
GameLayerScene::~GameLayerScene()
{}

GameLayerScene *GameLayerScene::createWithScore(int score1, int score2)
{
    GameLayerScene *go = new GameLayerScene;
    if (go && go->initWithScore(score1, score2)) {
        go->autorelease();
        return go;
    }
    CC_SAFE_DELETE(go);
    return NULL;
}

bool GameLayerScene::initWithScore(int scoreSG)
{
    if (CCScene::init()) {
        
        CCSprite *back = CCSprite::create("background2.png");
        back->setAnchorPoint(ccp(0,0));
        back->setPosition(ccp(0, 0));
        addChild(back);
        
        PlayAgainCategary = DesktopLayerNone;
        scorePlayer1 = scoreSG;
        //init code  gameoverscene
        CCLabelBMFont *label = CCLabelBMFont::create("Replay", "Fonts/bitmapFontTest4.fnt");
        label->setAlignment(kCCTextAlignmentCenter);
        CCScale9Sprite *bg = CCScale9Sprite::create("btnBack1.png");
        CCControlButton *btn = CCControlButton::create(label, bg);
        btn->setAdjustBackgroundImage(false);
        btn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayerScene::btnPlayAgainCallback), CCControlEventTouchDown);
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        btn->setPosition(s.width/2, s.height/ 8 * 5);
        addChild(btn);
        
        //init code  gameoverscene
        CCLabelBMFont *labelMenu = CCLabelBMFont::create("Menu", "Fonts/bitmapFontTest4.fnt");
        labelMenu->setAlignment(kCCTextAlignmentCenter);
        CCScale9Sprite *bgMenu = CCScale9Sprite::create("btnBack1.png");
        CCControlButton *btnMenu = CCControlButton::create(labelMenu, bgMenu);
        btnMenu->setAdjustBackgroundImage(false);
        btnMenu->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayerScene::btnMenuCallback), CCControlEventTouchDown);
        btnMenu->setPosition(s.width/2, s.height/ 8 * 4);
        addChild(btnMenu);
        
        return true;
    }
    return false;
}

bool GameLayerScene::initWithScore(int score1, int score2)
{
    if (CCScene::init()) {
        
        CCSprite *back = CCSprite::create("background1.png");
        back->setAnchorPoint(ccp(0,0));
        back->setPosition(ccp(0, 0));
        addChild(back);
        
        PlayAgainCategary = DesktopLayerNone;
        scorePlayer1 = score1;
        scorePlayer2 = score2;
        //init code  gameoverscene
        CCLabelBMFont *label = CCLabelBMFont::create("Replay", "Fonts/bitmapFontTest4.fnt");
        label->setAlignment(kCCTextAlignmentCenter);
        CCScale9Sprite *bg = CCScale9Sprite::create("btnBack1.png");
        CCControlButton *btn = CCControlButton::create(label, bg);
        btn->setAdjustBackgroundImage(false);
        btn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayerScene::btnPlayAgainCallback), CCControlEventTouchDown);
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        btn->setPosition(s.width/2, s.height/ 8 * 5);
        addChild(btn);
        
        //init code  gameoverscene
        CCLabelBMFont *labelMenu = CCLabelBMFont::create("Menu", "Fonts/bitmapFontTest4.fnt");
        labelMenu->setAlignment(kCCTextAlignmentCenter);
        CCScale9Sprite *bgMenu = CCScale9Sprite::create("btnBack1.png");
        CCControlButton *btnMenu = CCControlButton::create(labelMenu, bgMenu);
        btnMenu->setAdjustBackgroundImage(false);
        btnMenu->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayerScene::btnMenuCallback), CCControlEventTouchDown);
        btnMenu->setPosition(s.width/2, s.height/ 8 * 4);
        addChild(btnMenu);
        
        return true;
    }
    return false;
}

void GameLayerScene::onEnterTransitionDidFinish()
{
    CCScene::onEnterTransitionDidFinish();
    drawWin();
}

void GameLayerScene::drawWin()
{}

void GameLayerScene::btnPlayAgainCallback(CCObject* pSender, CCControlEvent event)
{
    CCScene *desktop = DesktopScene::createWithCategary(PlayAgainCategary);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(1, desktop));
}

void GameLayerScene::btnMenuCallback(CCObject* pSender, CCControlEvent event)
{
    CCDirector::sharedDirector()->popScene();
}