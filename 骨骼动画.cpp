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
    if ( !Layer::init() )
    {
        return false;
    }
    Size size = Director::getInstance()->getVisibleSize();
    //资源异步加载
    Director::getInstance()->getTextureCache()->addImageAsync("Plist.png", [this](Texture2D* texture){  //异步加载
        log("加载成功");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist.plist");
        auto levelSelection = CSLoader::createNode("LevelSelection.csb");
        this->addChild(levelSelection);
        
    
        //依次获取各个界面， getchildbyname 根据这个来获取
        auto pageView = levelSelection->getChildByName<ui::PageView*>("PageView_SelectPage");
        auto levelNumber = levelSelection->getChildByName<ui::TextAtlas*>("LabelAtlas_CurrentScene");
        auto leftButton = levelSelection->getChildByName<ui::Button*>("Button_Left");
        auto rightButton = levelSelection->getChildByName<ui::Button*>("Button_Right");
        auto enter = levelSelection->getChildByName<ui::Button*>("Button_Enter");
        enter->addClickEventListener([this](Ref*){
            //杰克船长动画
            auto node = CSLoader::createNode("captain_jack.csb");
            this->addChild(node);
            auto time = CSLoader::createTimeline("captain_jack.csb");
            time->gotoFrameAndPlay(0,54,true);
            node->setPosition(Vec2(150,200));
            node->runAction(time);
            //鲨鱼动画
            auto node2 = CSLoader::createNode("generalshark.csb");
            this->addChild(node2);
            auto time2= CSLoader::createTimeline("generalshark.csb");
            time2->gotoFrameAndPlay(0,151,true);
            node2->setPosition(Vec2(200,400));
            node2->runAction(time2);
   
            
        });
        
        //翻页增加事件
        pageView->addEventListener([levelNumber,pageView](Ref* ref,ui::PageView::EventType type){
            if(type==ui::PageView::EventType::TURNING){
                levelNumber->setString(StringUtils::format("%zd/3",pageView->getCurPageIndex()+1));
                
            }
         });
        //左边按钮
        leftButton->addClickEventListener([pageView](Ref* ref){
            auto index = pageView->getCurPageIndex();
            index--;
            if(index<0)   {return ;}
            pageView->scrollToPage(index);
         });
        //右边按钮
        rightButton->addClickEventListener([pageView](Ref* ref){
            auto index = pageView->getCurPageIndex();
            index++;
            if(index>2){return ;}
            pageView->scrollToPage(index);
        });
        
     
        
    });
    log("正在加载");//是异步函数，先执行下面这句，在执行内部的
                                                              
    
    
    
    
  /*
    //Size visibleSize = Director::getInstance()->getVisibleSize();
   //将动画转换过来
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto node = CSLoader::createNode("MainScene.csb");
    this->addChild(node);
    //运行帧动画
    auto time = CSLoader::createTimeline("MainScene.csb");
    time->gotoFrameAndPlay(0,30, true);
    time->setFrameEventCallFunc(CC_CALLBACK_1(HelloWorld::frameListener, this));
    
    node->runAction(time);
    
 */
    return true;
}

//帧事件，打印帧事件
void HelloWorld::frameListener(Frame* frame)
{
    EventFrame* event = dynamic_cast<EventFrame*>(frame);
    if(!event)
    {
        return;
    }
    std::string str = event->getEvent();
    if(str == "test")
    {
        CCLOG("test");
    }
    log("over");
}
