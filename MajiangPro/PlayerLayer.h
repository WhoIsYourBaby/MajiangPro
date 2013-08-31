//
//  PlayerLayer.h
//  MaJiong
//
//  Created by HalloWorld on 13-2-26.
//
//

#ifndef __MaJiong__PlayerLayer__
#define __MaJiong__PlayerLayer__

#include <iostream>
#include "cocos2d.h"
#include "ProgressLayer.h"
using namespace cocos2d;

typedef enum {
    PlayerCategaryPerson,
    PlayerCategaryBot,
} PlayerCategary;

class PlayerLayer : public CCLayerColor {
    
protected:
    CCLabelBMFont *ScoreLabel;  //显示分数
    CCLabelBMFont *UserInfoLabel;//显示玩家信息
    uint16_t myScore;
    ProgressLayer *progressTimer;
    bool iscurrent;
    PlayerCategary categary;
    CCObject *stopTarget;
    SEL_CallFuncO handdleStopCall;
public:
    PlayerLayer();
    virtual ~PlayerLayer();
    virtual bool init();
    CREATE_FUNC(PlayerLayer);
    static PlayerLayer * create(const ccColor4B& color, GLfloat width, GLfloat height);
    virtual bool initWithColor(const ccColor4B& color, GLfloat width, GLfloat height);
    
    virtual void initLayout();
    virtual void setScore(const char *score);
    virtual void setScore(uint16_t sc);
    virtual void setUserName(const char *name);
    virtual void addScore(uint16_t sc);
    uint16_t getScore();
    
    virtual void animateScore(uint16_t sc);     //加分动画
    
    void addTargetAndSelector(CCObject *tar, SEL_CallFuncO stopSel);
    
    //计时器
    virtual void startProgress(uint8_t s);
    virtual void stopProgressTimer();
    virtual void handdleProgressStoped(CCObject *obj);
    virtual void handdleProgressSecond(CCObject *obj);
    virtual void animateScoreEnd(CCNode *scLabel);
    
    //set & get是否是当前玩家
    bool isCurrent();
    void setCurrent(bool cur);
    virtual void currentSwitch();   //改变current状态
    
    PlayerCategary getCategary();
    uint8_t getCurrentProgressSecond();
    void startProgressAdded(uint8_t added);
};

#endif /* defined(__MaJiong__PlayerLayer__) */
