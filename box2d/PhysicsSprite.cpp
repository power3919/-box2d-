//
//  PhysicsSprite.cpp
//  TestBox2D
//
//  Created by student on 15/8/31.
//
//

#include "PhysicsSprite.h"

PhysicsSprite::PhysicsSprite():m_pBody(NULL)
{
    this->initWithFile("bird3.png");
    hp=5;
}

void PhysicsSprite::setPhysicsBody(b2Body* body)
{
    m_pBody = body;
}