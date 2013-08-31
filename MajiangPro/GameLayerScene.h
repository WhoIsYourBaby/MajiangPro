//
//  GameLayerScene.h
//  MaJiong
//
//  Created by HalloWorld on 13-3-21.
//
//

#ifndef __MaJiong__GameLayerScene__
#define __MaJiong__GameLayerScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

#include "DesktopScene.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class GameLayerScene : public cocos2d::CCScene
{
    CC_SYNTHESIZE(DesktopLayerCategary, PlayAgainCategary, PlayAgainCategary);
    CC_SYNTHESIZE(int, scorePlayer1, scorePlayer1);
    CC_SYNTHESIZE(int, scorePlayer2, scorePlayer2);
public:
    GameLayerScene();
    virtual ~GameLayerScene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    static GameLayerScene *createWithScore(int score1, int score2);
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool initWithScore(int score1, int score2);
    virtual bool initWithScore(int scoreSG);
    
    // a selector callback
    void btnPlayAgainCallback(CCObject* pSender, CCControlEvent event);
    void btnMenuCallback(CCObject* pSender, CCControlEvent event);
    
    virtual void onEnterTransitionDidFinish();  //输赢动画
    virtual void drawWin();
};

#endif /* defined(__MaJiong__GameLayerScene__) */
