//
//  MenuScene.cpp
//  MaJiong
//
//  Created by HalloWorld on 12-12-28.
//
//

#include "MenuScene.h"
#include "SimpleAudioEngine.h"

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
    CCMenuItemImage *pPVPItem = CCMenuItemImage::create("btn.png", "btn.png", this, menu_selector(MenuScene::menuPVPCallback));
    pPVPItem->setAnchorPoint(ccp(0,0));
    pPVPItem->setPosition(140, 200);
    
    CCMenuItemImage *pPVEItem = CCMenuItemImage::create("btn.png", "btn.png", this, menu_selector(MenuScene::menuPVECallback));
    pPVEItem->setAnchorPoint(ccp(0,0));
    pPVEItem->setPosition(150, 150);
    
    CCMenuItemImage *pHelpItem = CCMenuItemImage::create("btn.png", "btn.png", this, menu_selector(MenuScene::menuHelpCallback));
    pHelpItem->setAnchorPoint(ccp(0,0));
    pHelpItem->setPosition(140, 100);
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pPVPItem, pPVEItem, pHelpItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    // add "MenuScene" splash screen"
    CCSprite* pSprite = CCSprite::create("background2.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}

void MenuScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

#pragma mark - Menu CallBack
void MenuScene::menuPVPCallback(CCObject* pSender)
{
    CCScene *desktop = CCScene::create();
    CCDirector::sharedDirector()->pushScene(CCTransitionFlipAngular::create(1, desktop));
}

void MenuScene::menuPVECallback(CCObject* pSender)
{
    printf("%s", __FUNCTION__);
}

void MenuScene::menuHelpCallback(CCObject* pSender)
{
    printf("%s", __FUNCTION__);
}