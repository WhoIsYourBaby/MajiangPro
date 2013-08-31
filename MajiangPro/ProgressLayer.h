//
//  ProgressLayer.h
//  MaJiong
//
//  Created by HalloWorld on 13-3-5.
//
//

#ifndef __MaJiong__ProgressLayer__
#define __MaJiong__ProgressLayer__

#include <iostream>
#include "cocos2d.h"
#include "Definition.h"
using namespace cocos2d;

class ProgressLayer : public CCLayerColor {
    uint8_t ProgressSeconds;
    CCProgressTimer *progress;
    CCLabelBMFont *labelSeconds;
    //设置停止回调函数
    CCObject *target;
    SEL_CallFuncO stopCall;
    SEL_CallFuncO secondCall;
public:
    virtual ~ProgressLayer();
    CREATE_FUNC(ProgressLayer);
    virtual bool init();
    uint8_t getCurrentProgressSecond();
    void startProgress(uint8_t s);
    void startProgressAdd(uint8_t s);
    void stopProgress();
    void stopProgressByPlayer();
    void callFunProgress();
    void updateLabel();
    
    void addTargetAndSelector(CCObject *tar, SEL_CallFuncO sel, SEL_CallFuncO secSel);
};

#endif /* defined(__MaJiong__ProgressLayer__) */
