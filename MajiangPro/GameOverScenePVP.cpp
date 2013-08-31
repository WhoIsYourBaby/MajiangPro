//
//  GameOverSceneFTF.cpp
//  MaJiong
//
//  Created by HalloWorld on 13-4-10.
//
//

#include "GameOverScenePVP.h"
GameOverScenePVP::GameOverScenePVP()
{}

GameOverScenePVP::~GameOverScenePVP()
{}

GameLayerScene *GameOverScenePVP::createWithScore(int score1, int score2)
{
    GameLayerScene *go = new GameOverScenePVP;
    if (go && go->initWithScore(score1, score2)) {
        return go;
    }
    CC_SAFE_DELETE(go);
    return NULL;
}

bool GameOverScenePVP::initWithScore(int score1, int score2)
{
    if (GameLayerScene::initWithScore(score1, score2)) {
        return true;
    }
    return false;
}

void GameOverScenePVP::drawWin()
{
    if (scorePlayer1 > scorePlayer2) {
        //玩家1赢
        CCLabelBMFont *labelWin = CCLabelBMFont::create("WIN", "Fonts/bitmapFontTest4.fnt");
        labelWin->setColor(ccRED);
        labelWin->setAlignment(kCCTextAlignmentCenter);
        labelWin->setScale(3.0);
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        CCSize sl = labelWin->getContentSize();
        labelWin->setPosition(ccp(s.width-sl.width *3, sl.height*3));
        labelWin->setRotation(-45);
        addChild(labelWin);
        labelWin->setScale(11);
        CCAction *act = CCScaleTo::create(0.7, 3);
        labelWin->runAction(act);
        
        CCLabelBMFont *labelWin1 = CCLabelBMFont::create("LOST", "Fonts/bitmapFontTest4.fnt");
        labelWin1->setColor(ccRED);
        labelWin1->setAlignment(kCCTextAlignmentCenter);
        labelWin1->setScale(3.0);
        labelWin1->setPosition(ccp(sl.width *3,s.height - sl.height*3));
        labelWin1->setRotation(-225);
        addChild(labelWin1);
        labelWin1->setScale(11);
        CCAction *act1 = CCScaleTo::create(0.7, 3);
        labelWin1->runAction(act1);
        
        char sc[10];
        sprintf(sc, "%d", scorePlayer1);
        CCLabelBMFont *labelScore1 = CCLabelBMFont::create(sc, "Fonts/bitmapFontTest4.fnt");
        labelScore1->setScale(5.0);
        labelScore1->setPosition(s.width/2,200);
        addChild(labelScore1);
        
        sprintf(sc, "%d", scorePlayer2);
        CCLabelBMFont *labelScore2 = CCLabelBMFont::create(sc, "Fonts/bitmapFontTest4.fnt");
        labelScore2->setScale(5.0);
        labelScore2->setPosition(s.width/2,s.height-200);
        labelScore2->setRotation(180);
        addChild(labelScore2);
    }
    else if (scorePlayer1 < scorePlayer2) {
        //玩家1输
        CCLabelBMFont *labelWin = CCLabelBMFont::create("WIN", "Fonts/bitmapFontTest4.fnt");
        labelWin->setColor(ccRED);
        labelWin->setAlignment(kCCTextAlignmentCenter);
        labelWin->setScale(3.0);
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        CCSize sl = labelWin->getContentSize();
        labelWin->setPosition(ccp(sl.width *3,s.height - sl.height*3));
        labelWin->setRotation(-225);
        addChild(labelWin);
        labelWin->setScale(11);
        CCAction *act = CCScaleTo::create(0.7, 3);
        labelWin->runAction(act);
        
        CCLabelBMFont *labelWin1 = CCLabelBMFont::create("LOST", "Fonts/bitmapFontTest4.fnt");
        labelWin1->setColor(ccRED);
        labelWin1->setAlignment(kCCTextAlignmentCenter);
        labelWin1->setScale(3.0);
        labelWin1->setPosition(ccp(s.width-sl.width *3, sl.height*3));
        labelWin1->setRotation(-45);
        addChild(labelWin1);
        labelWin1->setScale(11);
        CCAction *act1 = CCScaleTo::create(0.7, 3);
        labelWin1->runAction(act1);
        
        char sc[10];
        sprintf(sc, "%d", scorePlayer1);
        CCLabelBMFont *labelScore1 = CCLabelBMFont::create(sc, "Fonts/bitmapFontTest4.fnt");
        labelScore1->setScale(5.0);
        labelScore1->setPosition(s.width/2,200);
        addChild(labelScore1);
        
        sprintf(sc, "%d", scorePlayer2);
        CCLabelBMFont *labelScore2 = CCLabelBMFont::create(sc, "Fonts/bitmapFontTest4.fnt");
        labelScore2->setScale(5.0);
        labelScore2->setPosition(s.width/2,s.height-200);
        labelScore2->setRotation(180);
        addChild(labelScore2);
    }
    else {
        //平手
        CCLabelBMFont *labelWin = CCLabelBMFont::create("No body win", "Fonts/bitmapFontTest4.fnt");
        labelWin->setColor(ccRED);
        labelWin->setAlignment(kCCTextAlignmentCenter);
        labelWin->setScale(3.0);
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        CCSize sl = labelWin->getContentSize();
        labelWin->setPosition(ccp(s.width/2.0,sl.height*3 +100));
        addChild(labelWin);
        
        char sc[10];
        sprintf(sc, "%d : %d", scorePlayer1, scorePlayer2);
        CCLabelBMFont *labelScore1 = CCLabelBMFont::create(sc, "Fonts/bitmapFontTest4.fnt");
        labelScore1->setScale(5.0);
        labelScore1->setPosition(s.width/2,350);
        addChild(labelScore1);
    }
}