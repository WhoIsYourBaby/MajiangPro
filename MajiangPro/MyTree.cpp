//
//  MyTree.cpp
//  MaJiong
//
//  Created by Kira on 10/9/12.
//  Copyright (c) 2012 Kira. All rights reserved.
//

#include "MyTree.h"


MyTree::~MyTree()
{//delete rootNode
    destroySubTree(rootNode);
}

MyTreeNode *MyTree::RootNode()
{
    return rootNode;
}
void MyTree::setRootNode(MyTreeNode *node)
{
    if (rootNode != NULL) {
        destroySubTree(rootNode);
    }
    rootNode = node;
}

void MyTree::deleteSubTree(MyTreeNode *subTree)
{
    if (subTree == NULL) {
        return;
    }
    
    if (subTree->NextBrother() != NULL) {
        deleteSubTree(subTree->NextBrother());
    }
    if (subTree->FirstChild() != NULL) {
        deleteSubTree(subTree->FirstChild());
    }
    delete subTree;
    subTree = NULL;
}

void MyTree::destroySubTree(MyTreeNode *subTree)                   //调整整个树结构及删除子树
{
    if (subTree == NULL) {
        return;
    }
    // 修正树结构
    if (subTree->ParentNode()) {
        MyTreeNode *bigBrother = subTree->ParentNode()->FirstChild();
        if (bigBrother->isEqualTo(subTree)) {
            subTree->ParentNode()->setFirstChild(bigBrother->NextBrother());
        } else {
            MyTreeNode *tempNode = bigBrother;
            while (tempNode) {
                if (tempNode->NextBrother()->isEqualTo(subTree)) {
                    tempNode->setNextBrother(tempNode->NextBrother()->NextBrother());
                    break;
                }
                tempNode = tempNode->NextBrother();
            }
        }
    }
    
    deleteSubTree(subTree);
}

void MyTree::displaySubTree(MyTreeNode *subTree)                    //打印树节点内容
{
    if (subTree == NULL) {
        return;
    }
    subTree->display();
    if (subTree->NextBrother() != NULL) {
        displaySubTree(subTree->NextBrother());
    }
    printf("\n");
    if (subTree->FirstChild() != NULL) {
        displaySubTree(subTree->FirstChild());
    }
}