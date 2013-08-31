//
//  MenuScene.h
//  MaJiong
//
//  Created by HalloWorld on 12-12-28.
//
//

#ifndef __MaJiong__MenuScene__
#define __MaJiong__MenuScene__

#include <iostream>
#include "cocos2d.h"

#include "DesktopLayer.h"

class MenuScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void menuPVPCallback(CCObject* pSender);
    void menuPVECallback(CCObject* pSender);
    void menuHelpCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(MenuScene);
};


#endif /* defined(__MaJiong__MenuScene__) */
