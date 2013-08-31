//
//  MyTree.h
//  MaJiong
//
//  Created by Kira on 10/9/12.
//  Copyright (c) 2012 Kira. All rights reserved.
//

#ifndef __MaJiong__MyTree__
#define __MaJiong__MyTree__

#include <iostream>

#include "MyTreeNode.h"

class MyTree {
    MyTreeNode *rootNode;
    void deleteSubTree(MyTreeNode *subTree);
public:
    MyTree(MyTreeNode *node = NULL):rootNode(node){};
    virtual ~MyTree();
    
    //getter & setter
    MyTreeNode *RootNode();
    void setRootNode(MyTreeNode *node);
    
    //add & delete
//    void addChild(MyTreeNode *subNode, MyTreeNode *child);      //给subNode添加child
//    void addBrother(MyTreeNode *subNode, MyTreeNode *brother);      //给subNode添加child
    MyTreeNode *subtreeBeforeDestroy(MyTreeNode *subTree);      //删除子树之前，先改变整个树的结构，使subtree的哥哥指向subtree的弟弟
    void destroySubTree(MyTreeNode *subTree);                   //删除子树
    void displaySubTree(MyTreeNode *subTree);                   //遍历子树,->子节点->兄弟节点
};

#endif /* defined(__MaJiong__MyTree__) */
