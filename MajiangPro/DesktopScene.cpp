//
//  DesktopScene.cpp
//  MaJiong
//
//  Created by HalloWorld on 13-1-29.
//
//

#include "DesktopScene.h"

//PVP Layer
#include "PlayDesktopLayer.h"
#include "PlayDesktopLayerPad.h"

//PVE Layer
#include "PlayDestopPVELayerPad.h"

//SG Layer
#include "PlayDesktopSinglePad.h"

DesktopScene::DesktopScene()
{}
DesktopScene::~DesktopScene()
{}
bool DesktopScene::init()
{
    if (CCScene::init()) {
        CCSize ws = CCDirector::sharedDirector()->getWinSize();
        if (fabsf(ws.width - 768.0) < 0.1) {
            //iPad
            DesktopLayer *des = PlayDesktopLayerPad::create();
            this->addChild(des);
        } else {
            //iPhone
            DesktopLayer *des = PlayDesktopLayer::create();
            this->addChild(des);
        }
        return true;
    } else return false;
}

DesktopScene *DesktopScene::createWithCategary(DesktopLayerCategary cate)
{
    DesktopScene *pScene = new DesktopScene();
    if (pScene && pScene->initWithCategary(cate)) {
        pScene->autorelease();
        return pScene;
    } else {
        delete pScene;
        pScene = NULL;
        return NULL;
    }
}

bool DesktopScene::initWithCategary(DesktopLayerCategary cate)
{
    if (CCScene::init()) {
        //创建背景
        CCSprite *back = CCSprite::create("background2.png");
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        back->setPosition(ccp(s.width/2.0, s.height/2.0));
        this->addChild(back);
        
        layoutWithCategary(cate);
        return true;
    } else return false;
}

void DesktopScene::layoutWithCategary(DesktopLayerCategary cate)
{
    switch (cate) {
        case DesktopLayerPVP:
            layoutPVPLayer();
            break;
        case DesktopLayerPVE:
            layoutPVELayer();
            break;
        case DesktopLayerSG:
            layoutSGLayer();
            break;
        default:
            break;
    }
}

void DesktopScene::layoutPVPLayer()
{
    CCSize ws = CCDirector::sharedDirector()->getWinSize();
    if (fabsf(ws.width - 768.0) < 0.1) {
        //iPad
        DesktopLayer *des = PlayDesktopLayerPad::create();
        this->addChild(des);
    } else {
        //iPhone
        DesktopLayer *des = PlayDesktopLayer::create();
        this->addChild(des);
    }
}

void DesktopScene::layoutPVELayer()
{
    CCSize ws = CCDirector::sharedDirector()->getWinSize();
    if (fabsf(ws.width - 768.0) < 0.1) {
        //iPad
        DesktopLayer *des = PlayDestopPVELayerPad::create();
        this->addChild(des);
    } else {
        //iPhone
        DesktopLayer *des = PlayDesktopLayer::create();
        this->addChild(des);
    }
}

void DesktopScene::layoutSGLayer()
{
    CCSize ws = CCDirector::sharedDirector()->getWinSize();
    if (fabsf(ws.width - 768.0) < 0.1) {
        //iPad
        DesktopLayer *des = PlayDesktopSinglePad::create();
        this->addChild(des);
    } else {
        //iPhone
        DesktopLayer *des = PlayDesktopLayer::create();
        this->addChild(des);
    }
}
