//
//  Created by HalloWorld on 13-1-29.
//  双人面面游戏
//  Fight face to face    面对面对战
//

#ifndef __MaJiong__PlayDesktopScenePad__
#define __MaJiong__PlayDesktopScenePad__

#include <iostream>
#include "DesktopLayer.h"
#include "MaJiongSprite.h"


class PlayDesktopLayerPad : public DesktopLayer {
public:
    PlayDesktopLayerPad();
    virtual ~PlayDesktopLayerPad();
    virtual bool init();
    CREATE_FUNC(PlayDesktopLayerPad);
    
    virtual void initializeMajiong();
    virtual void initializePlayer();
    virtual void randMaJiang();             //随机麻将位置
    //select majiong
    virtual void SelectMajiong(MaJiongSprite *mj);
    
    virtual CCPoint PositionOfCoord(CCPoint p);
    
    //Player完成一次选择后或者可用时间用完发出通知, 子类须重写此函数定制自己的行为
    virtual void handdleTurnPlayer(PlayerLayer *player);
    
    virtual void GameOver();
};
#endif /* defined(__MaJiong__PlayDesktopScenePad__) */
