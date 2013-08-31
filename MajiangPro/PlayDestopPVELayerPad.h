//
//  PlayDestopPVELayerPad.h
//  MaJiong
//
//  Created by HalloWorld on 13-4-22.
//
//

#ifndef __MaJiong__PlayDestopPVELayerPad__
#define __MaJiong__PlayDestopPVELayerPad__

#include <iostream>
#include "DesktopLayer.h"
#include "MaJiongSprite.h"
#include "PlayerLayerFTF.h"
#include "PlayerLayerBot.h"
#include <dispatch/dispatch.h>
#include "GameOverScenePVP.h"
#include "GameOverScenePVE.h"

class PlayDestopPVELayerPad : public DesktopLayer {
    
public:
    PlayDestopPVELayerPad();
    virtual ~PlayDestopPVELayerPad();
    virtual bool init();
    CREATE_FUNC(PlayDestopPVELayerPad);
    
    virtual void initializeMajiong();
    virtual void initializePlayer();
    virtual void randMaJiang();             //随机麻将位置
    
    virtual void SelectMajiong(MaJiongSprite *mj);
    
    virtual CCPoint PositionOfCoord(CCPoint p);
    
    virtual void handdleTurnPlayer(PlayerLayer *player);
    
    virtual void GameOver();
};

#endif /* defined(__MaJiong__PlayDestopPVELayerPad__) */
