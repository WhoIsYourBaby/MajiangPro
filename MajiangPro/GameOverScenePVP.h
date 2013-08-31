//
//  GameOverScenePVP.h
//  MaJiong
//
//  Created by HalloWorld on 13-4-10.
//
//

#ifndef __MaJiong__GameOverSceneFTF__
#define __MaJiong__GameOverSceneFTF__

#include <iostream>
#include "GameLayerScene.h"


class GameOverScenePVP : public GameLayerScene {
    
public:
    GameOverScenePVP();
    virtual ~GameOverScenePVP();
    
    static GameLayerScene *createWithScore(int score1, int score2);
    virtual bool initWithScore(int score1, int score2);
    
    virtual void drawWin();
};

#endif /* defined(__MaJiong__GameOverSceneFTF__) */
