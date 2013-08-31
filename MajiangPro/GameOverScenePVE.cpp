//
//  GameOverScenePVE.cpp
//  MaJiong
//
//  Created by HalloWorld on 13-7-3.
//
//

#include "GameOverScenePVE.h"

GameOverScenePVE::GameOverScenePVE()
{}

GameOverScenePVE::~GameOverScenePVE()
{}

GameLayerScene *GameOverScenePVE::createWithScore(int score1, int score2)
{
    GameLayerScene *go = new GameOverScenePVE;
    if (go && go->initWithScore(score1, score2)) {
        return go;
    }
    CC_SAFE_DELETE(go);
    return NULL;
}

bool GameOverScenePVE::initWithScore(int score1, int score2)
{
    if (GameLayerScene::initWithScore(score1, score2)) {
        return true;
    }
    return false;
}

void GameOverScenePVE::drawWin()
{
    if (scorePlayer1 > scorePlayer2) {
        //玩家1赢
        CCLabelBMFont *labelWin = CCLabelBMFont::create("YOU WIN", "Fonts/bitmapFontTest4.fnt");
        labelWin->setColor(ccRED);
        labelWin->setAlignment(kCCTextAlignmentCenter);
        labelWin->setScale(3.0);
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        CCSize sl = labelWin->getContentSize();
        labelWin->setPosition(ccp(s.width/2.0,sl.height*3+100));
        addChild(labelWin);
        labelWin->setScale(11);
        CCAction *act = CCScaleTo::create(0.7, 3);
        labelWin->runAction(act);
        
        char sc[10];
        sprintf(sc, "%d : %d", scorePlayer1, scorePlayer2);
        CCLabelBMFont *labelScore1 = CCLabelBMFont::create(sc, "Fonts/bitmapFontTest4.fnt");
        labelScore1->setScale(5.0);
        labelScore1->setPosition(s.width/2,350);
        addChild(labelScore1);
    }
    else if (scorePlayer1 < scorePlayer2) {
        //玩家1输
        CCLabelBMFont *labelWin = CCLabelBMFont::create("YOU LOST", "Fonts/bitmapFontTest4.fnt");
        labelWin->setColor(ccRED);
        labelWin->setAlignment(kCCTextAlignmentCenter);
        labelWin->setScale(3.0);
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        CCSize sl = labelWin->getContentSize();
        labelWin->setPosition(ccp(s.width/2.0,sl.height*3+100));
        addChild(labelWin);
        labelWin->setScale(11);
        CCAction *act = CCScaleTo::create(0.7, 3);
        labelWin->runAction(act);
        
        char sc[10];
        sprintf(sc, "%d : %d", scorePlayer1, scorePlayer2);
        CCLabelBMFont *labelScore1 = CCLabelBMFont::create(sc, "Fonts/bitmapFontTest4.fnt");
        labelScore1->setScale(5.0);
        labelScore1->setPosition(s.width/2,350);
        addChild(labelScore1);
    }
    else {
        //平手
        CCLabelBMFont *labelWin = CCLabelBMFont::create("No body win", "Fonts/bitmapFontTest4.fnt");
        labelWin->setColor(ccRED);
        labelWin->setAlignment(kCCTextAlignmentCenter);
        labelWin->setScale(3.0);
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        CCSize sl = labelWin->getContentSize();
        labelWin->setPosition(ccp(s.width/2.0,sl.height*3+100));
        addChild(labelWin);
        
        char sc[10];
        sprintf(sc, "%d : %d", scorePlayer1, scorePlayer2);
        CCLabelBMFont *labelScore1 = CCLabelBMFont::create(sc, "Fonts/bitmapFontTest4.fnt");
        labelScore1->setScale(5.0);
        labelScore1->setPosition(s.width/2,350);
        addChild(labelScore1);
    }
}