//
//  PhysicsSprite.h
//  TestBox2D
//
//  Created by student on 15/8/31.
//
//

#ifndef __TestBox2D__PhysicsSprite__
#define __TestBox2D__PhysicsSprite__

#include <stdio.h>
#include "Box2D/Box2D.h"
using namespace cocos2d;
class PhysicsSprite:public Sprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body* body);
    int hp;//血量
private:
    b2Body* m_pBody;//刚体（不能相互穿透的物体）
    
};


#endif /* defined(__TestBox2D__PhysicsSprite__) */
