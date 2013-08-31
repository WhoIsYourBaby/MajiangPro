//
//  MyTreeNode.cpp
//  MaJiong
//
//  Created by Kira on 10/9/12.
//  Copyright (c) 2012 Kira. All rights reserved.
//

#include "MyTreeNode.h"
//getter & setter

MyTreeNode::~MyTreeNode()
{//destroy me 
}
MyTreeNode *MyTreeNode::FirstChild()
{
    return firstChild;
}
MyTreeNode *MyTreeNode::NextBrother()
{
    return nextBrother;
}

MyTreeNode *MyTreeNode::ParentNode()
{
    return parentNode;
}

MyTreeNode *MyTreeNode::SuperParent()
{
    MyTreeNode *sp = this;
    while (sp->ParentNode()) {
        sp = sp->ParentNode();
    }
    return sp;
}

void MyTreeNode::setFirstChild(MyTreeNode *node)
{
    firstChild = node;
}
void MyTreeNode::setNextBrother(MyTreeNode *node)
{
    nextBrother = node;
}
void MyTreeNode::setParentNode(MyTreeNode *node)
{
    parentNode = node;
}

//add child & brother
void MyTreeNode::addChildNode(MyTreeNode *child)
{
    if (child == NULL) {
        std::cout<<"child == NULL"<<std::endl;
        return;
    }
    if (firstChild == NULL) {
        firstChild = child;
        firstChild->setParentNode(this);
    } else {
        firstChild->addBrother(child);
    }
}
void MyTreeNode::addBrother(MyTreeNode *brother)
{
    if (brother == NULL) {
        std::cout<<"brother == NULL"<<std::endl;
    }
    if (nextBrother == NULL) {
        nextBrother = brother;
        nextBrother->setParentNode(parentNode);
    } else {
        MyTreeNode *tempNode = nextBrother;
        while (tempNode->NextBrother()) {
            tempNode = tempNode->NextBrother();
        }
        tempNode->setNextBrother(brother);
        tempNode->NextBrother()->setParentNode(parentNode);
    }
}


MyTreeNode *MyTreeNode::NodeForValue(cocos2d::CCPoint p)
{
    printf("p(%f,%f)\n",p.x,p.y);
    if (Position.equals(p)) {
        return this;
    }
    MyTreeNode *tempNode = this;
    if (tempNode->NextBrother() != NULL) {
        MyTreeNode *findNode = tempNode->NextBrother()->NodeForValue(p);
        if (findNode) {
            return findNode;
        }
    }
    if (tempNode->FirstChild() != NULL) {
        MyTreeNode *findNode = tempNode->FirstChild()->NodeForValue(p);
        if (findNode) {
            return findNode;
        }
    }
    return NULL;
}

bool MyTreeNode::isEqualTo(MyTreeNode *node)
{
    if (Position.equals(node->Position)) {
        return true;
    } else return false;
}

bool MyTreeNode::isEqualPP(CCPoint p1, CCPoint p2)
{
    if (fabsf(p1.x-p2.x) < 0.001 && fabsf(p1.y-p2.y) < 0.001) {
        return true;
    } else return false;
}

bool MyTreeNode::isHasBrotherValue(CCPoint p)
{
    MyTreeNode *tempNode = this;
    while (tempNode) {
        if (tempNode->Position.equals(p)) {
            return true;
        }
        tempNode = tempNode->NextBrother();
    }
    return false;
}

void MyTreeNode::display()
{
    printf("\nP(%f,%f)",Position.x, Position.y);
}
