//
//  DesktopScene.h
//  MaJiong
//
//  Created by HalloWorld on 13-1-29.
//
//

#ifndef __MaJiong__DesktopScene__
#define __MaJiong__DesktopScene__

#include <iostream>
#include "cocos2d.h"
#include "DesktopLayer.h"

typedef enum {
    DesktopLayerPVP = 0,
    DesktopLayerPVE,
    DesktopLayerSG,
    DesktopLayerGC,
    DesktopLayerNone
}DesktopLayerCategary;

using namespace cocos2d;
class DesktopScene : public CCScene {
    
public:
    DesktopScene();
    virtual ~DesktopScene();
    virtual bool init();
    CREATE_FUNC(DesktopScene);
    static DesktopScene *createWithCategary(DesktopLayerCategary cate);
    virtual bool initWithCategary(DesktopLayerCategary cate);
    void layoutWithCategary(DesktopLayerCategary cate);
    void layoutPVPLayer();
    void layoutPVELayer();
    void layoutSGLayer();
};

#endif /* defined(__MaJiong__DesktopScene__) */
