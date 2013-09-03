//
//  MaJiongAppDelegate.cpp
//  MaJiong
//
//  Created by HalloWorld on 12-12-5.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//
#import <UIKit/UIKit.h>
#include "AppDelegate.h"

#include "cocos2d.h"
#include "MenuScene.h"
#include "MenuScenePad.h"
#include "DesktopScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        cocos2d::CCFileUtils::sharedFileUtils()->setResourceDirectory("HD");
    }
    else {
        if (pDirector->enableRetinaDisplay(true)) {
            cocos2d::CCFileUtils::sharedFileUtils()->setResourceDirectory("HD");
        }
    }
    
    const char *path = CCFileUtils::sharedFileUtils()->getResourceDirectory();
    printf("path -> %s\n", path);
    // turn on display FPS
//    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCSize ws = CCDirector::sharedDirector()->getWinSize();
    CCScene *pScene = NULL;
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        //Pad
        pScene = MenuScenePad::scene();
    } else {
        //Phone
        pScene = MenuScene::scene();
    }
    
    //加载音乐音效
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("select.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("disappear.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("gameover.mp3");
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
    CCDirector::sharedDirector()->stopAnimation();
    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
