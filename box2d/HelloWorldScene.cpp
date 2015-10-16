#include "HelloWorldScene.h"
USING_NS_CC;

#include "PhysicsSprite.h"
#include "MyContactListener.h"
#define PTM_RATIO 32.0

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
       if ( !Layer::init() )
    {
        return false;
    }

    
    auto  size = Director::getInstance()->getVisibleSize();
    
    auto sp = Sprite::create("bg_about.png");
    sp->setPosition(Vec2(size.width/2,size.height/2));
    addChild(sp);
    
    auto dispatcher=Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan=[](Touch *touch,Event *event)
    {
        return true;
    };
    
    touchListener->onTouchEnded=[this](Touch *touch,Event *event)
    {
        this->addNewSpriteAtPosition(touch->getLocation());
    };
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    initPhysical();
    this->scheduleUpdate();
    
    MyContactListener *con= new MyContactListener(world,this);
    world->SetContactListener(con);

    return true;
}

void HelloWorld::initPhysical()
{
    auto size = Director::getInstance()->getVisibleSize();
    //b2Vec2   一个结构体（2D 容器）
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
    //设置可以休眠（物体到达边界的时候，停止对这个物体的计算，节约CPU）
    world->SetContinuousPhysics(true);
    //b2BodyDef 一个结构体 包含一个刚体（不能穿透），创建的时候需要所有的数据
    b2BodyDef groundBodyDef;
    world->SetContinuousPhysics(true);
    groundBodyDef.position.Set(0, 0);
    b2Body* groundBody = world->CreateBody(& groundBodyDef);
    //定义边界
    b2EdgeShape groundBox;
    //bottom
    groundBox.Set(b2Vec2(size.width/PTM_RATIO,0),b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);
   
    //top
    groundBox.Set(b2Vec2(0,size.height/PTM_RATIO),b2Vec2(size.width/PTM_RATIO,size.height/PTM_RATIO));
     groundBody->CreateFixture(&groundBox,0);
    //left
    groundBox.Set(b2Vec2(0,size.height/PTM_RATIO), b2Vec2(0,0));
     groundBody->CreateFixture(&groundBox,0);
    //right
    groundBox.Set(b2Vec2(size.width/PTM_RATIO,size.height/PTM_RATIO),b2Vec2(size.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
  
    
  }


void HelloWorld::addNewSpriteAtPosition(Point p)
{
    
    PhysicsSprite* sprite = new PhysicsSprite(); //精灵
    sprite->setPosition(p);
    this->addChild(sprite);
    
    b2BodyDef bodyDef;  //一个结构体，创建一个有刚体需要的所有属性
    bodyDef.type = b2_dynamicBody;   //动态刚体
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    
    bodyDef.userData = sprite; //刚体和精灵关联起来
    b2Body *body = world->CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox;   //方形的形状
    dynamicBox.SetAsBox(1.0f, 0.5f); // 半长，半宽
    
    b2FixtureDef fixtureDef;   //物理属性
    //fixtureDef.isSensor = true;  //设置为传感器
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f; //密度
    fixtureDef.friction = 0.5;//摩擦
    fixtureDef.restitution = 0.5f;  //恢复
    body->CreateFixture(&fixtureDef);  //物理属性传递到body
    
   }


void HelloWorld::update(float dt)
{
  
    int velocityIterations = 8;  //速度的迭代
    int positionIterations = 1;   //位置的迭代
    world->Step(dt, velocityIterations, positionIterations);//可以下落
    b2Body* b = world->GetBodyList();
    
    while (b) {
        b2Body* p=b;
        b=b->GetNext();
        if (p->GetUserData() != NULL) {
            PhysicsSprite* myActor = (PhysicsSprite*) p->GetUserData();
            if (myActor->hp<0) {
                myActor->removeFromParent();
                world->DestroyBody(p);
            }
            myActor->setPosition(Point(p->GetPosition().x * PTM_RATIO,p->GetPosition().y*PTM_RATIO));//这里设置错了，就会很大问题
            myActor->setRotation(-1*CC_RADIANS_TO_DEGREES(p->GetAngle()));
        }
    }
   
   
}








