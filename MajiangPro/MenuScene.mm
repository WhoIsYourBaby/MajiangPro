//
//  MenuScene.cpp
//  MaJiong
//
//  Created by HalloWorld on 12-12-28.
//
//

#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#import "IOSHelper.h"
#import "WeiboShareManager.h"
#import "GCHelper.h"
#import "AppController.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MenuScene *layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    // add "MenuScene" splash screen"
    CCSprite* pSprite = CCSprite::create("background3.png");
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    //联机对战
    CCLabelBMFont *label1 = CCLabelBMFont::create("VS Game Center", "Fonts/bitmapFontTest4.fnt");
    label1->setAlignment(kCCTextAlignmentCenter);
    CCScale9Sprite *bg1 = CCScale9Sprite::create("btnBack1.png");
    CCControlButton *btn1 = CCControlButton::create(label1, bg1);
    btn1->setAdjustBackgroundImage(false);
    btn1->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuPVPCallback), CCControlEventTouchDown);
    btn1->setPosition(s.width/2, s.height/ 4 * 2.8);
    addChild(btn1);
    
    CCLabelBMFont *labelSp = CCLabelBMFont::create("Single Player", "Fonts/bitmapFontTest4.fnt");
    labelSp->setAlignment(kCCTextAlignmentCenter);
    CCScale9Sprite *bgSp = CCScale9Sprite::create("btnBack1.png");
    CCControlButton *btnSp = CCControlButton::create(labelSp, bgSp);
    btnSp->setAdjustBackgroundImage(false);
    btnSp->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuSingleCallback), CCControlEventTouchDown);
    btnSp->setPosition(s.width/2, s.height/ 4 * 2.15);
    addChild(btnSp);
    
    
    CCLabelBMFont *label2 = CCLabelBMFont::create(" ", "Fonts/bitmapFontTest4.fnt");
    label2->setAlignment(kCCTextAlignmentCenter);
    CCScale9Sprite *bg2 = CCScale9Sprite::create("logo.png");
    CCControlButton *sinaBtn = CCControlButton::create(label2, bg2);
    sinaBtn->setAdjustBackgroundImage(false);
    sinaBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuSinaShareCallback), CCControlEventTouchDown);
    sinaBtn->setPosition(s.width/2 - 80, s.height/ 4 * 1.4);
    addChild(sinaBtn);
    
    
    CCLabelBMFont *label3 = CCLabelBMFont::create(" ", "Fonts/bitmapFontTest4.fnt");
    label3->setAlignment(kCCTextAlignmentCenter);
    CCScale9Sprite *bg3 = CCScale9Sprite::create("twitter.png");
    CCControlButton *twitterBtn = CCControlButton::create(label3, bg3);
    twitterBtn->setAdjustBackgroundImage(false);
    twitterBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTwitterShareCallback), CCControlEventTouchDown);
    twitterBtn->setPosition(s.width/2 + 80, s.height/ 4 * 1.4);
    addChild(twitterBtn);
    
    if (![[NSUserDefaults standardUserDefaults] boolForKey:@"noiad"]) {
        CCLabelBMFont *label5 = CCLabelBMFont::create(" ", "Fonts/bitmapFontTest4.fnt");
        label5->setAlignment(kCCTextAlignmentCenter);
        CCScale9Sprite *bg5 = CCScale9Sprite::create("noiad.png");
        CCControlButton *btniad = CCControlButton::create(label5, bg5);
        btniad->setAdjustBackgroundImage(false);
        btniad->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuNoiadCallback), CCControlEventTouchDown);
        btniad->setPosition(s.width/2, s.height/ 4 * 1.4);
        addChild(btniad);
    }
    
    return true;
}

#pragma mark - Menu CallBack

void MenuScene::menuSingleCallback(CCObject* pSender)
{
    CCScene *desktop = DesktopScene::createWithCategary(DesktopLayerSG);
    CCDirector::sharedDirector()->pushScene(CCTransitionFlipAngular::create(1, desktop));
    SimpleAudioEngine::sharedEngine()->playEffect("select.mp3");
}

void MenuScene::menuPVPCallback(CCObject* pSender)
{
    [[AppController shareInterface] findPlayer];
}

void MenuScene::menuPVECallback(CCObject* pSender)
{
    printf("%s", __FUNCTION__);
}

void MenuScene::menuSinaShareCallback(CCObject *psender)
{
    [WeiboShareManager LoginAndShareSina];
}


void MenuScene::menuTwitterShareCallback(CCObject *psender)
{
    [WeiboShareManager LoginAndShareTwitter];
}

void MenuScene::menuNoiadCallback(CCObject* pSender)
{
    [IOSHelper buyNoIad];
}

