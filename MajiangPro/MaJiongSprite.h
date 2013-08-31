//
//  MaJiongSprite.h
//  MaJiong
//
//  Created by HalloWorld on 13-1-4.
//
//

#ifndef __MaJiong__MaJiongSprite__
#define __MaJiong__MaJiongSprite__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class DesktopLayer;

typedef enum {
    MaJiongColorTong = 0,
    MaJiongColorTiao,
    MaJiongColorWan
} MaJiongColorEnum;

class MaJiongSprite : public CCSprite, public CCTargetedTouchDelegate {
    bool isSelected;
    DesktopLayer *SelectedObserver;
    MaJiongColorEnum MJColor;
    uint16_t MJScore;
public:
    
    virtual bool initWithFile(const char *pszFilename);
    static MaJiongSprite *MaJiongWithFile(const char *pszFilename);
    CCPoint OringCoord;
    
    virtual void onEnter();
    virtual void onExit();
    CCRect rect();
    bool containsTouchLocation(CCTouch* touch);
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    //getter & setter
    bool getSelected();
    void setOriginCoord(int x, int y);
    void setOriginCoord(CCPoint p);
    CCPoint getOriginCoord();
    MaJiongColorEnum getMJColor();
    uint16_t getMJScore();
    //Actions
    void Select();
    void Diselect();
    void Disappear();
    void AddSelectedObserver(DesktopLayer *desktop);
    
    bool operator==(MaJiongSprite *mj);
    bool isEqualTo(MaJiongSprite *mj);
};
#endif /* defined(__MaJiong__MaJiongSprite__) */
