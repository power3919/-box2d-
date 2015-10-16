//
//  MyContactListener.h
//  TestBox2D
//
//  Created by student on 15/8/31.
//
//

#ifndef __TestBox2D__MyContactListener__
#define __TestBox2D__MyContactListener__

#include <stdio.h>
#include "Box2D/Box2D.h"
#include "cocos2d.h"
USING_NS_CC;

class MyContactListener:public b2ContactListener
{
public:
    MyContactListener(){};
    MyContactListener(b2World* world,Layer* layer):w(world),l(layer){}
    ~MyContactListener(){}
    
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
   
    
private:
    b2World* w;
    Layer* l;
};

#endif /* defined(__TestBox2D__MyContactListener__) */
