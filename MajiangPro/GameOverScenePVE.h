//
//  GameOverScenePVE.h
//  MaJiong
//
//  Created by HalloWorld on 13-7-3.
//
//

#ifndef __MaJiong__GameOverScenePVE__
#define __MaJiong__GameOverScenePVE__

#include <iostream>
#include "GameLayerScene.h"


class GameOverScenePVE : public GameLayerScene {
    
public:
    GameOverScenePVE();
    virtual ~GameOverScenePVE();
    
    static GameLayerScene *createWithScore(int score1, int score2);
    virtual bool initWithScore(int score1, int score2);
    
    virtual void drawWin();
};

#endif /* defined(__MaJiong__GameOverScenePVE__) */
