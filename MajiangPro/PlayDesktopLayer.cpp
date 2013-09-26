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
    if (!DesktopLayer::init()) {
        return false;
    }
    
    return true;
}

void PlayDesktopLayer::initializePlayer()
{
    //两人同玩一pad对战
//    Player1 = PlayerLayer::create(ccc4(200, 200, 200, 100), 150, 60);
//    Player1->setPosition(ccp(500,20));
//    this->addChild(Player1);
//    Player1->setScore((uint16_t)0);
//    Player1->setCurrent(false);
//    Player1->setUserName("Player1");
//    Player1->addTargetAndSelector(this, callfuncO_selector(PlayDesktopLayer::handdleTurnPlayer));
//    
//    Player1->setCurrent(true);
//    Player1->startProgress(10);
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

void PlayDesktopLayer::randMaJiang()
{
    srand(time(NULL));
    int count = MajiongsArray->count();
    //产生一个0~72的随机序列数组
    int randIndex[72] = {0};
    int temp[72] = {0};
    for (int i = 0; i < 72; i++) {
        temp[i] = i;
    }
    
    int l = 71;
    for (int i = 0; i < 72; i ++) {
        int t = rand() % (72 - i);
        randIndex[i] = temp[t];
        temp[t] = temp[l];
        l --;
    }
    
    /*/输出
     printf("\n{");
     for (int i = 0; i < 72; i ++) {
     printf("%d, ", randIndex[i]);
     }
     printf("}\n");
     //*/
    
    //打乱所有麻将位置
    for (int i = 0; i < kMaxX; i ++) {
        for (int j = 0; j < kMaxY; j ++) {
            MaJiongSprite *majiong = (MaJiongSprite *)MajiongsArray->objectAtIndex(randIndex[i * kMaxY + j]);
            int x = i+1;
            int y = j+1;
            majiong->setOriginCoord(x, y);
            if (majiong->isVisible()) {
                DesktopMap[x][y] = DesktopStateMaJiong;
            } else {
                DesktopMap[x][y] = DesktopStateNone;
            }
            MJWidth = majiong->boundingBox().size.width;
            MJHeight = majiong->boundingBox().size.height;
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            if (fabs(winSize.width - 768) < 0.01) {
                //ipad
                majiong->setPosition(ccp(OriginRootPad.x + MJWidth * x, OriginRootPad.y + MJHeight * y));
            } else {
                majiong->setPosition(ccp(OriginRoot.x + MJWidth * x, OriginRoot.y + MJHeight * y));
            }
            if (getChildByTag(i * kMaxY + j) == NULL) {
                this->addChild(majiong, 0, i * kMaxY + j);
            }
            count --;
        }
    }
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
