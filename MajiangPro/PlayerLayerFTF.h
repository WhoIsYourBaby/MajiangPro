//
//  PlayerLayerFTF.h
//  MaJiong
//
//  Created by HalloWorld on 13-3-4.
//
//  面对面对战Player

#ifndef __MaJiong__PlayerLayerFTF__
#define __MaJiong__PlayerLayerFTF__

#include <iostream>
#include "PlayerLayer.h"

class PlayerLayerFTF : public PlayerLayer {
public:
    static PlayerLayer * create(const ccColor4B& color, GLfloat width, GLfloat height);
    virtual bool initWithColor(const ccColor4B& color, GLfloat width, GLfloat height);
    virtual void initLayout();
    virtual void setScore(const char *score);
};

#endif /* defined(__MaJiong__PlayerLayerFTF__) */
