//
//  MyContactListener.cpp
//  TestBox2D
//
//  Created by student on 15/8/31.
//
//

#include "MyContactListener.h"
#include "PhysicsSprite.h"

 void MyContactListener::BeginContact(b2Contact* contact){}
 void MyContactListener::EndContact(b2Contact* contact){}
 void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){}
 void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
     float force = impulse->normalImpulses[0];
     if (force > 2) {
         PhysicsSprite* spriteA = (PhysicsSprite*) contact->GetFixtureA()->GetBody()->GetUserData();
         PhysicsSprite* spriteB = (PhysicsSprite*) contact->GetFixtureB()->GetBody()->GetUserData();
         if (spriteA && spriteB) {  //精灵与地面
             spriteA->hp--;
             spriteB->hp--;
         }
     }
}