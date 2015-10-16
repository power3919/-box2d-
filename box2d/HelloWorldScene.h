#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
using namespace cocos2d;
class HelloWorld : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
    
    void initPhysical();  //初始化物理世界
    void addNewSpriteAtPosition(Point p);
    b2World* world;//物理世界
    void update(float de);
    
//    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
//
//    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
};

#endif // __HELLOWORLD_SCENE_H__
