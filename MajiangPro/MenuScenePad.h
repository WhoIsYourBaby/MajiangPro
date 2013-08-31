//
//  MenuScenePad.h
//  MaJiong
//
//  Created by HalloWorld on 13-1-29.
//
//

#ifndef __MaJiong__MenuScenePad__
#define __MaJiong__MenuScenePad__

#include <iostream>
#include "cocos2d.h"

#include "DesktopScene.h"
#include "cocos-ext.h"


class MenuScenePad : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuPVPCallback(CCObject* pSender);
    void menuPVECallback(CCObject* pSender);
    void menuSingleCallback(CCObject* pSender);
    
    void menuSinaShareCallback(CCObject* pSender);
    void menuTwitterShareCallback(CCObject* pSender);
    void menuNoiadCallback(CCObject* pSender);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(MenuScenePad);
};


#endif /* defined(__MaJiong__MenuScenePad__) */
