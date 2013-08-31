//
//  PlayDesktopScene.cpp
//  MaJiong
//
//  Created by HalloWorld on 12-12-28.
//
//

#include "PlayDesktopLayer.h"
#include "MaJiongSprite.h"
#include "Definition.h"

using namespace cocos2d;

PlayDesktopLayer::PlayDesktopLayer()
{
}
PlayDesktopLayer::~PlayDesktopLayer()
{}


bool PlayDesktopLayer::init()
{
    if (!CCLayerColor::init()) {
        return false;
    }
    
    this->initializeMajiong();
    
    return true;
}

void PlayDesktopLayer::initializeMajiong()
{
    MajiongsArray = CCArray::createWithCapacity(72);
    MajiongsArray->retain();
    for (int i = 9; i > 0; i --) {
        for (int j = 0; j < 4; j ++) {
            char name[111];
            sprintf(name, "1%d.png", i);
            MaJiongSprite *mj = MaJiongSprite::MaJiongWithFile(name);
            mj->AddSelectedObserver(this);
            MajiongsArray->addObject(mj);
            
            sprintf(name, "3%d.png", i);
            MaJiongSprite *mj1 = MaJiongSprite::MaJiongWithFile(name);
            mj1->AddSelectedObserver(this);
            MajiongsArray->addObject(mj1);
        }
    }
    
    randMaJiang();
}

void PlayDesktopLayer::SelectMajiong(MaJiongSprite *mj)
{
    if (tempSelectMajiong && mj) {
        if (tempSelectMajiong->isEqualTo(mj) && tempSelectMajiong != mj) {
            //1 在这个条件里面判断两麻将是否能联通
            //前后选择的两个麻将花色与大小相同
            
            //2 能联通则消除
            
            //3 消除后tempSelectMajiong = NULL;
        } else {
            tempSelectMajiong->Diselect();
            tempSelectMajiong = mj;
        }
    } else tempSelectMajiong = mj;
}
