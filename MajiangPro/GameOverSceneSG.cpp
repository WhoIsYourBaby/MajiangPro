//
//  GameOverSceneSG.cpp
//  MaJiong
//
//  Created by Kira on 8/9/13.
//
//

#include "GameOverSceneSG.h"


GameLayerScene *GameOverSceneSG::createWithScore(int scoreSG)
{
    GameLayerScene *go = new GameOverSceneSG;
    if (go && go->initWithScore(scoreSG)) {
        return go;
    }
    CC_SAFE_DELETE(go);
    return NULL;
}

bool GameOverSceneSG::initWithScore(int scoreSG)
{
    if (GameLayerScene::initWithScore(scoreSG)) {
        return true;
    }
    return false;
}

void GameOverSceneSG::drawWin()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetIpad) {
        CCLabelBMFont *labelWin = CCLabelBMFont::create("GAME OVER", "Fonts/bitmapFontTest4.fnt");
        labelWin->setColor(ccRED);
        labelWin->setAlignment(kCCTextAlignmentCenter);
        labelWin->setScale(4.0);
        CCSize sl = labelWin->getContentSize();
        labelWin->setPosition(ccp(s.width/2.0,s.height/4 * 3));
        addChild(labelWin);
        labelWin->setScale(11);
        CCAction *act = CCScaleTo::create(0.7, 3);
        labelWin->runAction(act);
        
        char score[20];
        sprintf(score, "You got\n%d", scorePlayer1);
        CCLabelBMFont *labelScore = CCLabelBMFont::create(score, "Fonts/bitmapFontTest4.fnt");
        labelScore->setColor(ccRED);
        labelScore->setAlignment(kCCTextAlignmentCenter);
        labelScore->setScale(4.0);
        labelScore->setPosition(ccp(s.width/2.0,s.height/4 + 100));
        addChild(labelScore);
        labelScore->setScale(11);
        CCAction *act2 = CCScaleTo::create(0.7, 3);
        labelScore->runAction(act2);
    } else {
        CCLabelBMFont *labelWin = CCLabelBMFont::create("GAME OVER", "Fonts/bitmapFontTest4.fnt");
        labelWin->setColor(ccRED);
        labelWin->setAlignment(kCCTextAlignmentCenter);
        labelWin->setScale(4.0);
        CCSize sl = labelWin->getContentSize();
        labelWin->setPosition(ccp(s.width/2.0,s.height/4 * 3.3));
        addChild(labelWin);
        labelWin->setScale(11);
        CCAction *act = CCScaleTo::create(0.7, 3);
        labelWin->runAction(act);
        
        char score[20];
        sprintf(score, "You got\n%d", scorePlayer1);
        CCLabelBMFont *labelScore = CCLabelBMFont::create(score, "Fonts/bitmapFontTest4.fnt");
        labelScore->setColor(ccRED);
        labelScore->setAlignment(kCCTextAlignmentCenter);
        labelScore->setScale(4.0);
        labelScore->setPosition(ccp(s.width/2.0,s.height/4 *2.6));
        addChild(labelScore);
        labelScore->setScale(11);
        CCAction *act2 = CCScaleTo::create(0.7, 3);
        labelScore->runAction(act2);
    }
    
}