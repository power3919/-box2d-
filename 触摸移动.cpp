#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    funEventCustom();
    schedule(schedule_selector(HelloWorld::disparcherCustomEvents), 3.0f);
    testKeypadDispatcher();
    return true;
}

void HelloWorld::testKeypadDispatcher()
{
    //分发器是一个容器，将分发者发送出去
    this->getEventDispatcher()->removeAllEventListeners();
    auto listrner = EventListenerKeyboard::create();
    listrner->onKeyPressed=[](EventKeyboard::KeyCode keycode,Event* ev)
    {
        char txt[100]={};
        sprintf(txt, "key %d is pressed",(int) keycode);
        
    };
    listrner->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listrner ,this);
}

void HelloWorld::onKeyPressedss(EventKeyboard::KeyCode keycode, Event* ev)
{
    char txt[100];
    sprintf(txt, "key %d is pressed",(int)keycode);
    
}

void HelloWorld::onKeyReleasedss(EventKeyboard::KeyCode keycode, Event * ev)
{
    
}

void HelloWorld::testEventListenMouse()
{
    this->getEventDispatcher()->removeAllEventListeners();
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDownss, this);
    listener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMovess,this);
    listener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUpss, this);
    listener->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScrollss, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onMouseDownss(Event* ev)
{
    log("down");
}
void HelloWorld::onMouseMovess(Event* ev)
{
    log("move");
    
}
void HelloWorld::onMouseUpss(Event* ev)
{
    log("up");
}
void HelloWorld::onMouseScrollss(Event* ev)
{
    log("scroll");
}

void HelloWorld::funEventCustom()
{
    auto listener = EventListenerCustom::create("custom_enent_1", CC_CALLBACK_1(HelloWorld::onEventCustom, this));
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);//添加到事件分发器
}

void HelloWorld::disparcherCustomEvents(float )
{
    //派发时间
    this->getEventDispatcher()->dispatchCustomEvent("custom_event_1",(char*)"test");
    
}

void HelloWorld::onEventCustom(EventCustom* event)
{
    auto data = static_cast<char*>(event->getUserData());
    log("data = %s",data);
}

void HelloWorld::testAcceletation()
{
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onAcceleration(Acceleration* acc, Event* event)
{
    char str[100];
    sprintf(str, "x:%2f,y:%2f,z:%2f,timestamp:%2f",acc->x,acc->y,acc->z,acc->timestamp);
    log("%s",str);
}