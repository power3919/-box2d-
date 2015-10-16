//
//  Contact.cpp
//  TestBox2D
//
//  Created by student on 15/8/31.
//
//

#include "Contact.h"

Scene* Contact::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//调试
    
    auto layer = Contact::create();
    layer->setPhyWorld(scene->getPhysicsWorld());//将创建的物理世界传递到子层中
    
    auto size = Director::getInstance()->getVisibleSize();
    auto body = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, 3);//设置要添加到节点中的物理body
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(size.width/2,size.height/2));
    edgeNode ->setPhysicsBody(body);
    scene->addChild(edgeNode);
    scene->addChild(layer);
    return scene;
    
}

bool Contact::init()
{
    if (!Layer::init()) {
        return false;
    }
    EventListenerTouchOneByOne* one = EventListenerTouchOneByOne::create();
    one->onTouchBegan = [this](Touch* touch,Event* unused_event){
        return true;
    };
    one->onTouchEnded = [this](Touch* touch,Event* unused_event){
        addNewSpriteAtPosition(touch->getLocation());
    };
    auto dis = Director::getInstance()->getEventDispatcher();
    dis->addEventListenerWithSceneGraphPriority(one, this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Contact::onContactBegin, this);
    contactListener->onContactSeperate = [this](PhysicsContact& contact){
        auto node1 = contact.getShapeA()->getBody()->getNode();
        auto node2 = contact.getShapeB()->getBody()->getNode();
        log("seprated");
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    

    
    return true;
}


bool Contact::onContactBegin(PhysicsContact& contact)
{
    log("began");
    return true;
}

void Contact::addNewSpriteAtPosition(Point p)
{
    auto sprite = Sprite::create("bird3.png");
    sprite->setTag(1);
   auto body = PhysicsBody::createCircle(sprite->getContentSize().width/4);
    body->setCategoryBitmask(1);//类别
    body->setCollisionBitmask(1);//碰撞
    body->setContactTestBitmask(1);//接触
    
    sprite->setPhysicsBody(body);
    sprite->setPosition(p);
    this->addChild(sprite);
}

void Contact::onEnter()
{
    Layer::onEnter();
}

