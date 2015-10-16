#include "HelloWorldScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "tinyxml2/tinyxml2.h"

using namespace rapidjson;
using namespace tinyxml2;
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}




void HelloWorld::testUserDefault()
{
    //获取单例对象
    UserDefault *de = UserDefault::getInstance();
    //FileUtils文件工具类
    std::string path = FileUtils::getInstance()->getWritablePath();
    log("path=%s",path.c_str());
    
    de->setStringForKey("NAME", "zhangsan");
    de->setStringForKey("PWD", "123456");
    //将修改写入文件
    de->flush();//确保安全
    std::string name=de->getStringForKey("NAME","defaultname");
    log("name=%s",name.c_str());
    
    
}

void HelloWorld::testXmlParse()
{
    //获取可以写的路径
    std::string path = FileUtils::getInstance()->getWritablePath();
    //拼接路径
    std::string xmlPath = path+std::string("Chapters.xml");
    //加载文档
    XMLDocument* myDocument = new XMLDocument();
    XMLError errorID = myDocument->LoadFile(xmlPath.c_str());
    //判断是否解析错误
    if(errorID != 0)
    {
        log("parse Error");
        return;
    }
    //获取节点
    XMLElement* rootElement = myDocument->RootElement();
    CCLOG("rootKey=%s",rootElement->Value());//获取键
    log("rootValue=%s",rootElement->GetText());//获取值
    
    XMLElement *chapterElement = rootElement->FirstChildElement();
    log("chapterElement=%s",chapterElement->Value());
    log("chapterElement=%s",chapterElement->GetText());//获得键
    
    XMLElement *element = chapterElement->NextSiblingElement();
    log("2chapterELement=%s",element->Value());//第二层
    log("2chapterElement=%s",element->GetText());
    
    XMLElement *nameElement = chapterElement->FirstChildElement();
    log("nameELement:%s",nameElement->Value());//这里是第三层
    log("nameELementValue:%s",nameElement->GetText());
    
    XMLElement *numElement = nameElement->NextSiblingElement();
    log("num%s",numElement->Value());
    log("numValue%s",numElement->GetText());
    

    
    
    XMLElement *numELement = nameElement->NextSiblingElement();
    log("num%s",numElement->Value());
    log("numValue%s",numElement->GetText());
    int a  = atoi(numElement->GetText());//转换成整型
    //修改节点
    XMLNode *oldNode = numElement->FirstChild();
    log("oldNodeValue:%s",oldNode->Value());
    oldNode->SetValue("xiugaileaaa");
    myDocument->SaveFile(xmlPath.c_str());//保存文件
    
    
    
    //添加节点，需要使用其父类的节点调用，若使用等同级的子节点，则会作为其子节点添加
    XMLElement *Broadcast_Pid = myDocument->NewElement("AGE");//<SGE></AGE>
    XMLText *text1 = myDocument->NewText("3333");
    Broadcast_Pid->SetAttribute("info", "the pid");//<AGE info=the pid>333</AGE>
    Broadcast_Pid->LinkEndChild(Broadcast_Pid);//最后把这个节点加上了
    myDocument->SaveFile(xmlPath.c_str());
    CCLOG("finished");
    
    //移除节点
    XMLElement* nameNode = chapterElement->FirstChildElement();
    chapterElement->DeleteChild(nameNode);
    myDocument->SaveFile(xmlPath.c_str());//记得保存
    
    
    
    
    

}

void HelloWorld::testJsonParse()
{
    //DOM SAX
    FileUtils *fu = FileUtils::getInstance();
    std::string wrPath = fu->getWritablePath();
    wrPath += "aa.json";
    //创建repidson::document类：用于操作Jason代码
    rapidjson::Document doc;
    std::string data = FileUtils::getInstance()->getStringFromFile(wrPath);
    //乱码问题的解决
    std::string clearData(data);
    size_t pos = clearData.rfind("}");//查找最后一个大括号
    clearData =clearData.substr(0,pos+1);
    //解析json文件内容
    doc.Parse<kParseDefaultFlags>(clearData.c_str());//解析用默认的标志
    //判断解析是否出错
    if(doc.HasParseError())
    {
        log("GetParseError %s\n",doc.GetParseError());
        return;
    }
    rapidjson::Value &array = doc["Tollgate"];//程序里面也有个valu要加域名
    for(int i = 0;i<array.Size();i++)
    {
        rapidjson::Value &first = array[i];//一层一层进行取值
        rapidjson::Value &type = first["Type2"];
        rapidjson::Value &time=type["RefreshTime"];
        printf("%f",time.GetDouble());
    }
    
    //修改值
    if(array.IsArray())
    {
        int i = 1;
        rapidjson::Value & first = array[i];
        rapidjson::Value & type = first["Type2"];
        rapidjson::Value & time = type["RefreshTime"];
        
        time.SetInt(10);
        printf("%d",time.GetInt());
    }
    
    //修改json内容之后重新写入
    StringBuffer buffer;//在内存上开辟了一块缓冲区，栈，
    Writer<rapidjson::StringBuffer>  //写入器
    writer(buffer);//初始化写入器
    doc.Accept(writer); //将doc内容放到writer里面的buffer
    FILE* file = fopen(wrPath.c_str(), "wb");//wb读写，二进制类型
    if(file){
        fputs(buffer.GetString(),file);
        fclose(file);
    }

    
    
    
}

bool HelloWorld::copyFileToPath(std::string fileName)
{
    //获取文件复制的源路径和目的路径
    FileUtils* fu = FileUtils::getInstance();
    std::string wrPath = fu->getWritablePath();
    wrPath += fileName;
    log("%s",wrPath.c_str());
    //判断文件是否存在，不存在去复制，存在则不做处理
    if(!fu->isFileExist(wrPath))
    {
        //获取app里面的路径
        std::string dataPath = fu->fullPathForFilename(fileName.c_str());
        log("dataPath=%s",dataPath.c_str());
        std::string pFileContent=fu->getStringFromFile(dataPath);
        //CCLOG("%s",pFileContent.c_str());
        CCLOG("%s",pFileContent.c_str());
        //将文件内容读出，写入到沙盒
        FILE* file  = fopen(wrPath.c_str(), "w");
        if(file)
        {
            fputs(pFileContent.c_str(), file);
            fclose(file);
        }
    }
    return true;
}






void HelloWorld::menuCloseCallback(Ref* pSender)
{
  //  testUserDefault();
    copyFileToPath("Chapters.xml");
    //testJsonParse();
    testXmlParse();
    
    /*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
     */
}
