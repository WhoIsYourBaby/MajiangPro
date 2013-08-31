//
//  DesktopLayer.h
//  MaJiong
//
//  Created by HalloWorld on 13-1-29.
//
//

#ifndef __MaJiong__DesktopLayer__
#define __MaJiong__DesktopLayer__

#include <iostream>
#include "cocos2d.h"
#include "MaJiongSprite.h"
#include "PlayerLayer.h"
#include "Definition.h"
#include "MyTree.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

typedef enum {
    DesktopStateNone = 0,
    DesktopStateMaJiong,
} DesktopState;

class DesktopLayer : public CCLayerColor{
protected:
    MaJiongSprite *tempSelectMajiong;
    CCArray *MajiongsArray;
    DesktopState DesktopMap[kMatrixMaxX][kMatrixMaxY] = {DesktopStateNone};
    float MJWidth;
    float MJHeight;
    //是player1 + player2好呢还是单独currentPlayer?
    PlayerLayer *Player1;//玩家对象在子类初始化
    PlayerLayer *Player2;
    std::vector<CCPoint> *tempDrawList;
public:
    DesktopLayer();
    virtual ~DesktopLayer();
    virtual bool init();
    virtual void onEnter(); //onEnterTransitionDidFinish
    virtual void onEnterTransitionDidFinish(); 
    CREATE_FUNC(DesktopLayer);
    virtual void initializeMajiong();       //初始化麻将到layer上来,随即显示, 子类必须重写
    virtual void initializePlayer();        //初始化player,子类重写
    virtual void randMaJiang();             //随机麻将位置
    virtual void SelectMajiong(MaJiongSprite *mj);  //选中麻将,子类必须重写,是否能消除麻将
    
    void menuBackCallback(CCObject *pSender);
    
    //后台计算是否能有解
    
    //连连看算法  18941860078
    virtual CCPoint PositionOfCoord(CCPoint p);
    virtual void MaJiongDrawLinkPath(std::vector<CCPoint> *arr);             //绘制连线效果
    virtual void draw();
    void particleDispear(void *par);
    virtual MaJiongSprite *MaJiongOfOrigin(int x, int y);       //返回坐标为(x, y)的麻将
    virtual MaJiongSprite *MaJiongOfOrigin(CCPoint origin);
    virtual std::vector<CCPoint> *link(CCPoint pFrom, CCPoint pTo);  //返回pFrom->pTo的可连接路径,CCPoint
    DesktopState DesktopMapState(CCPoint p);
    virtual void SetDesktopState(CCPoint p, DesktopState state);
    bool canLinkOnLine(const CCPoint &pf, const CCPoint &pt);   //是否直线相连
    bool canLinkOnLineOnX(const CCPoint &pf, const CCPoint &pt);//直线x轴相连
    bool canLinkOnLineOnY(const CCPoint &pf, const CCPoint &pt);//直线Y轴相连
    
    //Player完成一次选择后或者可用时间用完发出通知, 子类须重写此函数定制自己的行为
    virtual void handdleTurnPlayer(PlayerLayer *player);
    virtual PlayerLayer *getCurrentPlayer();
    //智能寻解
    virtual std::vector<CCPoint> *thereIsLink();
    //返回的路径方向是反的,读取的时候注意
    virtual std::vector<CCPoint> *thereIsLinkOfMJ(MaJiongSprite *mj);
    /** 递归搜索最优可连
     void addChildrenLine(MyTreeNode *pNode, int turnTime);
     @param MyTreeNode *pNode 要搜索的节点
     @param int turnTime 当前的拐点个数,如果超过2则不会搜索
     @returns void
     */
    MyTreeNode *addChildrenLine(MyTreeNode *pNode, int turnTime =0);
    
    virtual void GameOver();    //游戏结束
};

#endif /* defined(__MaJiong__DesktopLayer__) */
