//
//  MenuScenePad.cpp
//  MaJiong
//
//  Created by HalloWorld on 13-1-29.
//
//

#include "MenuScenePad.h"
#include "SimpleAudioEngine.h"
#import "IOSHelper.h"
#import "WeiboShareManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

CCScene* MenuScenePad::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MenuScenePad *layer = MenuScenePad::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScenePad::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    // add "MenuScene" splash screen"
    CCSprite* pSprite = CCSprite::create("background3.png");
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    //add 双人单击对战button
    CCLabelBMFont *label = CCLabelBMFont::create("VS Friend", "Fonts/bitmapFontTest4.fnt");
    label->setAlignment(kCCTextAlignmentCenter);
    CCScale9Sprite *bg = CCScale9Sprite::create("btnBack1.png");
    CCControlButton *btn = CCControlButton::create(label, bg);
    btn->setAdjustBackgroundImage(false);
    btn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScenePad::menuPVPCallback), CCControlEventTouchDown);
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    btn->setPosition(s.width/2, s.height/ 4 * 3);
    addChild(btn);
    
    CCLabelBMFont *label1 = CCLabelBMFont::create("VS Bot", "Fonts/bitmapFontTest4.fnt");
    label->setAlignment(kCCTextAlignmentCenter);
    CCScale9Sprite *bg1 = CCScale9Sprite::create("btnBack1.png");
    CCControlButton *btn1 = CCControlButton::create(label1, bg1);
    btn1->setAdjustBackgroundImage(false);
    btn1->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScenePad::menuPVECallback), CCControlEventTouchDown);
    btn1->setPosition(s.width/2, s.height/ 4 * 2.4);
    addChild(btn1);
    
    CCLabelBMFont *labelSp = CCLabelBMFont::create("Single Player", "Fonts/bitmapFontTest4.fnt");
    labelSp->setAlignment(kCCTextAlignmentCenter);
    CCScale9Sprite *bgSp = CCScale9Sprite::create("btnBack1.png");
    CCControlButton *btnSp = CCControlButton::create(labelSp, bgSp);
    btnSp->setAdjustBackgroundImage(false);
    btnSp->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScenePad::menuSingleCallback), CCControlEventTouchDown);
    btnSp->setPosition(s.width/2, s.height/ 4 * 1.8);
    addChild(btnSp);
    
    
    CCLabelBMFont *label2 = CCLabelBMFont::create(" ", "Fonts/bitmapFontTest4.fnt");
    label->setAlignment(kCCTextAlignmentCenter);
    CCScale9Sprite *bg2 = CCScale9Sprite::create("logo.png");
    CCControlButton *sinaBtn = CCControlButton::create(label2, bg2);
    sinaBtn->setAdjustBackgroundImage(false);
    sinaBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScenePad::menuSinaShareCallback), CCControlEventTouchDown);
    sinaBtn->setPosition(s.width/2 - 80, s.height/ 4 * 1.4);
    addChild(sinaBtn);
    
    
    CCLabelBMFont *label3 = CCLabelBMFont::create(" ", "Fonts/bitmapFontTest4.fnt");
    label->setAlignment(kCCTextAlignmentCenter);
    CCScale9Sprite *bg3 = CCScale9Sprite::create("twitter.png");
    CCControlButton *twitterBtn = CCControlButton::create(label3, bg3);
    twitterBtn->setAdjustBackgroundImage(false);
    twitterBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScenePad::menuTwitterShareCallback), CCControlEventTouchDown);
    twitterBtn->setPosition(s.width/2 + 80, s.height/ 4 * 1.4);
    addChild(twitterBtn);
    
    
    //add 双人单击对战button
    if (![[NSUserDefaults standardUserDefaults] boolForKey:@"noiad"]) {
        CCLabelBMFont *label5 = CCLabelBMFont::create(" ", "Fonts/bitmapFontTest4.fnt");
        label5->setAlignment(kCCTextAlignmentCenter);
        CCScale9Sprite *bg5 = CCScale9Sprite::create("noiad.png");
        CCControlButton *btniad = CCControlButton::create(label5, bg5);
        btniad->setAdjustBackgroundImage(false);
        btniad->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScenePad::menuNoiadCallback), CCControlEventTouchDown);
        btniad->setPosition(s.width/2, s.height/ 4 * 1.1);
        addChild(btniad);
    }
    
    return true;
}

#pragma mark - Menu CallBack

void MenuScenePad::menuSinaShareCallback(CCObject *pSender)
{
    [WeiboShareManager LoginAndShareSina];
}

void MenuScenePad::menuTwitterShareCallback(CCObject *pSender)
{
    [WeiboShareManager LoginAndShareTwitter];
}


void MenuScenePad::menuPVPCallback(CCObject* pSender)
{
    CCScene *desktop = DesktopScene::createWithCategary(DesktopLayerPVP);
    CCDirector::sharedDirector()->pushScene(CCTransitionFlipAngular::create(1, desktop));
    SimpleAudioEngine::sharedEngine()->playEffect("select.mp3");
}

void MenuScenePad::menuPVECallback(CCObject* pSender)
{//"vs bot" select
    CCScene *desktop = DesktopScene::createWithCategary(DesktopLayerPVE);
    CCDirector::sharedDirector()->pushScene(CCTransitionFlipAngular::create(1, desktop));
    SimpleAudioEngine::sharedEngine()->playEffect("select.mp3");
}

void MenuScenePad::menuSingleCallback(CCObject* pSender)
{
    CCScene *desktop = DesktopScene::createWithCategary(DesktopLayerSG);
    CCDirector::sharedDirector()->pushScene(CCTransitionFlipAngular::create(1, desktop));
    SimpleAudioEngine::sharedEngine()->playEffect("select.mp3");
}

void MenuScenePad::menuNoiadCallback(CCObject* pSender)
{
    [IOSHelper buyNoIad];
}