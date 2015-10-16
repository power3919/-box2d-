//
//  Contact.h
//  TestBox2D
//
//  Created by student on 15/8/31.
//
//

#ifndef __TestBox2D__Contact__
#define __TestBox2D__Contact__
USING_NS_CC;
#include <stdio.h>
using namespace cocos2d;
class Contact:public Layer
{
public:
    virtual void onEnter();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Contact);
    
    void setPhyWorld(PhysicsWorld* world){m_world = world;}
    void addNewSpriteAtPosition(Point p);
    bool onContactBegin(PhysicsContact& contact);
    
    //virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    //virtual void onTouchMoved(Touch *touch, Event *unused_event);
    //virtual void onTouchEnded(Touch *touch, Event *unused_event);
    //virtual void onTouchCancelled(Touch *touch, Event *unused_event);

    
private:
    PhysicsWorld* m_world;
};


#endif /* defined(__TestBox2D__Contact__) */
