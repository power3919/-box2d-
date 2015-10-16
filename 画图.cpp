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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

      auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //初始化精灵
    sp = Sprite::create("2.png");
    sp->setScale(2, 2);
    sp->setPosition(Vec2(0,0));
    this->addChild(sp);
    
    //获取一个纹理缓冲 Texture纹理
    TextureCache* cache=Director::getInstance()->getTextureCache();
    //将图片添加到缓冲里面
    Texture2D* texture=cache->addImage("2.png");
    auto sp2 = Sprite::createWithTexture(texture);
    sp2->setPosition(Vec2(700,300));
    sp2->setScale(2,2);
    //this->addChild(sp2);

    
    return true;
}
//拷贝之后一个动作可以执行多个对象
void HelloWorld::menuCloseCallback(Ref* pSender){
    //3是持续时间，移动到绝对坐标
    //auto move = MoveTo::create(3,Vec2(500,500));
    //sp->runAction(move);
    //auto rotate = RotateBy::create(3, 90);
    //sp->runAction(rotate);
   /* auto by = RotateBy::create(5, -1000);
    sp->runAction(by);
    auto sp2 = Sprite::create("dog.png");
    sp2->setScale(2, 2);
    sp2->setPosition(Vec2(200,200));
    this->addChild(sp2);
    sp2->runAction(by->clone());
    */
    //scaleTo 是在原有的基础上，放大，就不能再改变了，scaleTo是在现有的基础上，可以一直变大
    //auto scale = ScaleBy::create(0.3, 2);
    //sp -> runAction(scale);
    //与缩放比列无关

  /*
    
    
    
    Size size = sp->getContentSize();
    log("width=%f,height=%f",size.width,size.height);
    Rect rect = sp->getBoundingBox();
    log("x=%f,y=%f,width->%f,he=%f",rect.origin.x,rect.origin.y,rect.size.width,rect.size.height);
    //跳动
    auto jump=JumpTo::create(5, Vec2(400,400),100, 5);
    //sp->runAction(jump);
    //闪烁,100跳的高度
    auto blink= Blink::create(5, 500);
    //sp->runAction(blink);
    auto seq = Sequence::create(jump,DelayTime::create(5),blink, NULL);//一序列动作连着
    //sp->runAction(seq);
    
    //同步合成动作
    auto spawn= Spawn::create(jump,blink, NULL);
    //sp->runAction(spawn);
    //旋转
    auto rotate=RotateBy::create(3, 700);
    auto repeat=RepeatForever::create(rotate);
    //auto repeat=Repeat::create(rotate, 2);
    //sp->runAction(repeat);
    
    //沿着曲线走，贝塞尔曲线
    ccBezierConfig config;
    config.controlPoint_1=Vec2(600,300);
    config.controlPoint_2=Vec2(400,200);
    config.endPosition=Vec2(800,600);
    BezierTo*bezier=BezierTo::create(10,config);
    //sp->runAction(bezier);

    //拉动转圈
    auto pointArray=PointArray::create(20);
    pointArray->addControlPoint(Point(0,0));
    pointArray->addControlPoint(Point(210,0));
    pointArray->addControlPoint(Point(210,240));
    pointArray->addControlPoint(Point(0,240));
    pointArray->addControlPoint(Point(0,0));
    auto cardinalSplineTo=CardinalSplineTo::create(3, pointArray, 3);//最后一个拉力系数
    //sp->runAction(cardinalSplineTo);
    
    //缓冲线
    //auto ease=EaseBounceInOut::create(MoveTo::create(3,Vec2(800,300)));
    auto ease=EaseExponentialInOut::create(MoveTo::create(3, Vec2(1300,600)));
    //sp->runAction(ease);
    
    auto target=TargetedAction::create(sp, ease);
    //this->runAction(target);
    //停止所有的行为
    //sp->stopAllActions();
    
    //旋转显示
    auto progressTo=ProgressTo::create(2, 100);
    auto timer=ProgressTimer::create(Sprite::create("3.png"));
    timer->setType(ProgressTimer::Type::RADIAL);
    timer->setPosition(Point(400,240));
    timer->setMidpoint(Point(0.5,0.5));
    //this->addChild(timer);
    //timer->runAction(progressTo);
    //log("%f",timer->getPercentage());
    
    //先移动在调用函数
    auto move=MoveTo::create(3, Vec2(500,500));
    //auto call=CallFunc::create(CC_CALLBACK_0(HelloWorld::callfunc, this));
    //auto call=CallFuncN::create(CC_CALLBACK_1(HelloWorld::callfuncN, this));
    //auto seq1=Sequence::create(move,call, NULL);
    //sp->runAction(seq1);
    
    //边移动，边加速
    //auto moveBy=MoveBy::create(2, Vec2(800,500));
    //auto speed=Speed::create(moveBy, 2);
    //sp->runAction(speed);
    
    //设置一个层跟随一个精灵，背景层在移动
    auto fl=Follow::create(sp);
    this->runAction(fl);
    auto mo=MoveBy::create(2, Vec2(800,500));
    //sp->runAction(mo);
    
    
//    Director::getInstance()->getActionManager()->pauseTarget(sp);//暂停sp的动作
//    Director::getInstance()->getActionManager()->resumeTarget(sp);//恢复sp的动作
//    Director::getInstance()->pause();//整个游戏暂停
//    Director::getInstance()->resume();//恢复
//    Director::getInstance()->end();//退出游戏
    
   
   */
    this->testArray();
    this->testDic();
    


    testAnimation();
}

void HelloWorld::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw,this, transform, flags);
    renderer->addCommand(&_customCommand);
    
}

void HelloWorld::onDraw (const cocos2d::Mat4 &transform,uint32_t flags)
{
    //初始化
    auto s = Director::getInstance()->getVisibleSize();
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    //画线
    CHECK_GL_ERROR_DEBUG();
    glLineWidth(5.0f);
    DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
    DrawPrimitives::drawLine(Vec2(s.width,0), Vec2(0,s.height));
    //画点
    CHECK_GL_ERROR_DEBUG();
    DrawPrimitives::setPointSize(64);//设置点大小
    DrawPrimitives::setDrawColor4B(0, 255, 255, 255);//设置颜色
    DrawPrimitives::drawPoint(Vec2(300,300));//参数vec2对象，表示圆心的位置
    
    //画多个点
    CHECK_GL_ERROR_DEBUG();
    Vec2 points[] = {Vec2(60,160),Vec2(70,170),Vec2(60,170), Vec2(70,160)};
    DrawPrimitives::setPointSize(4);
    DrawPrimitives::setDrawColor4B(0, 255, 255, 255);
    DrawPrimitives::drawPoints(points,4);//参数依次为圆心vec2和点的个数
    
    //画圆圈
    CHECK_GL_ERROR_DEBUG();
    glLineWidth(16);
    DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
    DrawPrimitives::drawCircle(Vec2(300,300), 100, 0, 100, false);//参数依次为：圆心，半径，角度，段落，是否画出一条半径  。段落大小决定是什么形状
    
    //画圆圈
    CHECK_GL_ERROR_DEBUG();
    glLineWidth(2);
    DrawPrimitives::setDrawColor4B(0, 255, 255, 255);
    DrawPrimitives::drawCircle(Vec2(200,200), 50, CC_DEGREES_TO_RADIANS(45), 50, true);
    
    //画多边形，不闭合
    CHECK_GL_ERROR_DEBUG();
    glLineWidth(10);
    Vec2 vertices[] = {Vec2(0,0),Vec2(50,50),Vec2(100,50),Vec2(100,100),Vec2(50,100)};
    DrawPrimitives::drawPoly(vertices, 5, false);//参数依次为多边形的顶点，定点数，是否闭合
    
    //绘制填充多边形
    CHECK_GL_ERROR_DEBUG();
    glLineWidth(1);
    Vec2 filledVertices[] = {Vec2(0,120),Vec2(50,120),Vec2(50,170),Vec2(25,200),Vec2(0,170)};
    DrawPrimitives::drawSolidPoly(filledVertices, 5, Color4F(0.5f, 0.5f, 1, 1));//依次给顶点，顶点个数，填充颜色
    
    //绘制多边形，闭合。把false改成true
    //绘制白塞尔曲线
    CHECK_GL_ERROR_DEBUG();
    //参数依次为起点，控制点，终点，段落
    DrawPrimitives::drawQuadBezier(Vec2(0,0), Vec2(s.width/2, s.height/2), Vec2(s.width, 0), 50);
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
}

//删除数组，数组的遍历，单线程
void HelloWorld::testArray()
{
    auto str1 = __String::create("string1");
    auto str2 = __String::create("string2");
    auto str3 = __String::create("string3");
    auto str4 = __String::create("string4");
    auto str5 = __String::create("string5");
    __Array* array = __Array::create();
    array->addObject(str1);
    array->addObject(str2);
    array->addObject(str3);
    array->addObject(str4);
   array->addObject(str5);
    array->removeLastObject();
    auto temp=__Array::create();
    for(int i =0;i<array->count();i++)
    {
        auto str=(__String*)array->getObjectAtIndex(i);
        log("%s",str->getCString());
        if(i==2)
        {
            temp->addObject(array->getObjectAtIndex(i));
        }
    }
    for(int i=0;i<temp->count();i++)
    {
        array->removeObject(temp->getObjectAtIndex(i));
    }
    log("%zd",array->count());
}

//字典
void HelloWorld::testDic()
{
    std::string a="sss";
    log("a=%s",a.c_str());

    auto pDict=__Dictionary::create();
    auto pValue1=__String::create("100");
    auto pvalue2=__String::create("120");
    auto pvalue3=Integer::create(200);
    pDict->setObject(pValue1, "key1");
    pDict->setObject(pvalue2, "key2");
    pDict->setObject(pvalue3, "key3");
    auto pstr1=(__String*)pDict->objectForKey("key1");
    log("{key1:%s}",pstr1->getCString());
    auto pInteger=(Integer*)pDict->objectForKey("key3");
    log("{key3:%d}",pInteger->getValue());
    
    auto name=__String::create("zhangsan");
    auto pass=__String::create("password");
    auto dic=__Dictionary::create();
    dic->setObject(name,"NAME");
    dic->setObject(pass, "PWD");

}


//一个小孩一直在走动  帧动画
void HelloWorld::testAnimation()
{
    auto sc=SpriteFrameCache::getInstance();
    sc->addSpriteFramesWithFile("test.plist","test.png");
    auto lu=Sprite::createWithSpriteFrameName("s_1.png");
    lu->setPosition(Vec2(200,200));
    this->addChild(lu);
    
    Vector<AnimationFrame*>vec;
    
    for(int i=1; i<=8;i++)
    {
        //设置每张图片的间隔
        float delay[8]={0.2,0.4,0.3,0.2,0.1,0.2,0.2,0.1};
        std::string str= StringUtils::format("s_%d.png",i);
        auto frame=sc->getSpriteFrameByName(str);
        auto aniframe=AnimationFrame::create(frame, delay[i-1], ValueMap());
        vec.pushBack(aniframe);
        
    }
    //使得动画一直在动的步骤
    auto animation=Animation::create(vec,1);
    auto animate=Animate::create(animation);
    lu->runAction(RepeatForever::create(animate));
    
}


void HelloWorld::callfunc()
{
    log("callfunc is called");
}

void HelloWorld::callfuncN(Node *sender)
{
    log("CN is called");
    sender->removeFromParent();
}



