//
//  GameOverSceneSG.h
//  MaJiong
//
//  Created by Kira on 8/9/13.
//
//

#ifndef __MaJiong__GameOverSceneSG__
#define __MaJiong__GameOverSceneSG__

#include <iostream>
#include "GameLayerScene.h"

class GameOverSceneSG : public GameLayerScene {
    
public:
    GameOverSceneSG(){};
    virtual ~GameOverSceneSG(){};
    
    static GameLayerScene *createWithScore(int scoreSG);
    virtual bool initWithScore(int scoreSG);
    
    virtual void drawWin();
};


#endif /* defined(__MaJiong__GameOverSceneSG__) */
