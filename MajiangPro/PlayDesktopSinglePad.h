//
//  PlayDesktopSinglePad.h
//  MaJiong
//
//  Created by Kira on 8/8/13.
//
//

#ifndef __MaJiong__PlayDesktopSinglePad__
#define __MaJiong__PlayDesktopSinglePad__

#include <iostream>
#include "DesktopLayer.h"
#include "PlayerLayerFTF.h"
#include <dispatch/dispatch.h>

class PlayDesktopSinglePad : public DesktopLayer
{
public:
    PlayDesktopSinglePad(){};
    virtual ~PlayDesktopSinglePad(){};
    
    virtual bool init();
    CREATE_FUNC(PlayDesktopSinglePad);
    
    virtual void initializeMajiong();
    virtual void initializePlayer();
    virtual void randMaJiang();             //随机麻将位置
    virtual void handdleTurnPlayer(PlayerLayer *player);
    virtual CCPoint PositionOfCoord(CCPoint p);
    //select majiong
    virtual void SelectMajiong(MaJiongSprite *mj);
    virtual void GameOver();
    void RestartGame();
    void setAllMJVisible();
};

#endif /* defined(__MaJiong__PlayDesktopSinglePad__) */
