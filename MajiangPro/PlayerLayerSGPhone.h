//
//  PlayerLayerSGPhone.h
//  MajiangPro
//
//  Created by Kira on 9/26/13.
//
//  单人游戏，只显示一个进度条

#ifndef __MajiangPro__PlayerLayerSGPhone__
#define __MajiangPro__PlayerLayerSGPhone__

#include <iostream>
#include "PlayerLayer.h"

class PlayerLayerSGPhone : public PlayerLayer {
public:
    static PlayerLayer * create(const ccColor4B& color, GLfloat width, GLfloat height);
    virtual bool initWithColor(const ccColor4B& color, GLfloat width, GLfloat height);
    virtual void initLayout();
    virtual void setScore(const char *score);
};


#endif /* defined(__MajiangPro__PlayerLayerSGPhone__) */
