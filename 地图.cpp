#include "HelloWorldScene.h"

USING_NS_CC;
bool isbullet = false;

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
    
   // Size visibleSize = Director::getInstance()->getVisibleSize();
    
    map = TMXTiledMap::create("Mymap.tmx");
    this->addChild(map);

    
    //获取地图中的不能行走的层
    meta = map->getLayer("meta");
    meta->setVisible(false);
    fruit = map->getLayer("Fruit");
    //添加英雄精灵
    player = Sprite::create("www.png");
    //获取对象图层hero中的对象组
    TMXObjectGroup* objectsValue = map->getObjectGroup("hero");
    //获取地图上的设置好的英雄对象
    ValueMap spawnPoint = objectsValue->getObject("pa");
    //根据地图上设置好的英雄位置来设置当前精灵的位置
    player->setAnchorPoint(Vec2(0,0));
    player->setPosition(Vec2(spawnPoint.at("x").asFloat(),spawnPoint.at("y").asFloat()));
    this->addChild(player);
    
    //初始化存放敌人的数组
    enemyArray = __Array::create();
    enemyArray -> retain();
    //初始化存放子弹的数组
    bulletArray = __Array::create();
    bulletArray ->retain();
    
    for (auto element : objectsValue->getObjects() ) {
        if (!element.isNull()) {
            //获取vector中各个对象的名称
            auto nameStr = element.asValueMap().at("name").asString().c_str();
            auto keySrt = "enemy";
            if (strcmp(nameStr, keySrt) == 0) {
                //初始化敌人精灵，把地图中已经初始化好的移动初始化为要用的敌人精灵
                auto enemySpitet = Sprite::create("enemy1.png");
                float x = element.asValueMap().at("x").asFloat();
                float y = element.asValueMap().at("y").asFloat();
                enemySpitet->setPosition(Vec2(x,y));
                enemySpitet->setAnchorPoint(Vec2(0,0));
                map->addChild(enemySpitet,4);
                enemyArray->addObject(enemySpitet);
                
                auto fun = CallFuncN::create(CC_CALLBACK_1(HelloWorld::goon, this));
                enemySpitet->runAction(fun);
            }
        }
    }
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto toucheListener = EventListenerTouchOneByOne::create();
    toucheListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    toucheListener->onTouchMoved=CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    toucheListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(toucheListener, this);
    

        return true;
}

//敌人移动
void HelloWorld::goon(Node* sender)
{
    auto s = (Sprite *)sender;
    //X方向移动的距离
    float x = player->getPosition().x - s->getPosition().x >0?10 : -10;
    //Y方向移动的距离
    float y = player->getPosition().y - s->getPosition().y >0?10 : -10;
    auto move = MoveBy::create(0.5, Vec2(x,y));
    //递归调用，让敌人精灵移动
    auto fun = CallFuncN::create(CC_CALLBACK_1(HelloWorld::goon, this));
    s->runAction(Sequence::create(move,fun, NULL));
}



bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    //获取当前触摸到的点的位置，属于世界坐标系
    auto touchLocation = touch->getLocation();
    //将世界坐标系转化为节点坐标系
    beginPoint = this->convertToNodeSpace(touchLocation);
    log("%f,   %f",beginPoint.x,beginPoint.y);
    return true;
}
 void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{}
void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    //获取当前用户触摸到的位置
    Point touchLocation = touch->getLocation();
    //将当前最后的位置转化为节点坐标系
    Point endPoint = this->convertToNodeSpace(touchLocation);
    if(!isbullet)
    {
        //如果开始与结束点是同一个点，当用户抬起手指的时候触发
        if (beginPoint.equals(endPoint)) {
            //获取精灵当前的位置
            auto playerpos = player->getPosition();
            //得到用户触摸点与当前精灵点的位置的差距
            auto dispos = endPoint - playerpos;
            if (abs(dispos.x) >= abs(dispos.y)) {
                if (dispos.x>0) {
                    playerpos.x += map->getTileSize().width;
                    
                }else{
                    playerpos.x -= map->getTileSize().width;
                }
            }
            else{
                if (dispos.y > 0) {
                    //每次偏移一个图块的宽度
                    playerpos.y += map->getTileSize().height;
                }else{
                    playerpos.y -= map->getTileSize().height;
                }
            }
           movePlayer(playerpos);
            setViewpointCenter(player->getPosition());
        }
    }else{
        //发射飞镖
        auto bullet = Sprite::create("Projectile.png");
        bullet->setPosition(player->getPosition());
        map->addChild(bullet,4);
        bulletArray->addObject(bullet);
    //当前手触摸与英雄精灵X轴的差值
        float dx = endPoint.x - player->getPosition().x;
        float dy = endPoint.y - player->getPosition().y;
        //向前发子弹
        if (dx > 0)
        {
            auto size = Director::getInstance()->getWinSize();
            float lx = map->getTileSize().width * map->getMapSize().width - player->getPosition().x;
            float ly = dy / dx * lx;
            auto move = MoveBy::create(3, Vec2(lx + bullet->getContentSize().width,ly));
            //子弹发射完毕之后执行回收子弹的函数
            auto ff = CallFuncN::create(CC_CALLBACK_1(HelloWorld::targetFinish, this));;
            bullet->runAction(Sequence::create(move,ff, NULL));
                                        
        }
    }
}

void HelloWorld::targetFinish(Node* sender)
{
    sender->removeFromParent();
    bulletArray->removeObject(sender);
    
}
void HelloWorld::movePlayer(Point p)
{
    //map->getMapSize();地图的图块数
    //map->getTileSize();每一个图块的宽高
    int x = p.x / map->getTileSize().width;  //定位在X轴的第几块
    int y =  map->getMapSize().height - (p.y/map->getTileSize().height);
    Point currentPoint = Point(x,y); //得到当前定位点
    //判断是否在地图范围内
    if (x != map->getMapSize().width && y != map->getMapSize().height) {
        //是否获取到目标，根据制定的电获取到瓦片的id
        int tilegId = meta->getTileGIDAt(currentPoint);
        //返回的类型是value根据图块id获取当前图块上的各个属性
        Value value = map->getPropertiesForGID(tilegId);
        //以字符串的形式获取value中的内容
        auto valueStr = value.getDescription();
        //如果瓦片存在
        if (tilegId) {
            //如果是遇到了障碍物，且不是西瓜，就不让精灵移动
            if (!value.isNull()) {
                if (valueStr.find("Collidable") != -1) {
                    return;
                }else if
                    (valueStr.find("Collection") != -1){
                        meta->removeTileAt(currentPoint);
                        //获得当前的水果，并将其从视图中移除
                        auto fruitSprite = fruit->getTileAt(currentPoint);
                        fruitSprite->removeFromParent();
                    }
            }
        }
        //让英雄移到点击的瓦片
        player->setPosition(p);
        
    }
}

void HelloWorld::setViewpointCenter(Point position)
{
    auto size = Director::getInstance()->getWinSize();
    //如果精灵在屏幕的1/2~2/3，X的值就是精灵的当前的X值
    int x = MAX(position.x, size.width/2);
    int y = MAX(position.y, size.height/2);
    //获取整个地图的尺寸
    auto mapSize = map->getMapSize();
    auto titleSize = map->getTileSize();
    //重新规划x,y的值
    x = MIN(x, mapSize.width * titleSize.width - size.width /2);
    y = MIN(y, mapSize.height * titleSize.height - size.height /2);
    //获取屏幕中心点的位置
    auto centerPoint = Point(size.width/2,size.height/2);
    auto actualPoint = Point(x,y);
    auto viewPoint = centerPoint - actualPoint;
    //重新规划当前视图的位置
    this->setPosition(viewPoint);
}







