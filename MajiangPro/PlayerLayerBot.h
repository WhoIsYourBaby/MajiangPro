//
//  PlayerLayerBot.h
//  MaJiong
//
//  Created by HalloWorld on 13-4-22.
//
//

#ifndef __MaJiong__PlayerLayerBot__
#define __MaJiong__PlayerLayerBot__

#include <iostream>
#include "PlayerLayer.h"
#include "MaJiongSprite.h"

class PlayerLayerBot : public PlayerLayer {
    MaJiongSprite *mj1;
    MaJiongSprite *mj2;
    DesktopLayer *AutoSelectDelegate;
public:
    static PlayerLayer * create(const ccColor4B& color, GLfloat width, GLfloat height);
    virtual bool initWithColor(const ccColor4B& color, GLfloat width, GLfloat height);
    virtual void initLayout();
    virtual void setScore(const char *score);
    virtual void currentSwitch();
    virtual ~PlayerLayerBot();
    void optimalMJs(MaJiongSprite *m1, MaJiongSprite *m2);
    virtual void handdleProgressSecond(CCObject *obj);
    void setAutoSelectDelegate(DesktopLayer *del);
};


#endif /* defined(__MaJiong__PlayerLayerBot__) */
