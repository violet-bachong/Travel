#include "GameStart.h"
#include "SimpleAudioEngine.h"
#include "Loading.h"

USING_NS_CC;

Label* writer;
Scene* GameStart::createScene() {
	return GameStart::create();
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool GameStart::init() {

    if (!Scene::init()){
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //自动手写笔
    writer = Label::createWithSystemFont("", "Times New Roman", 26);

    if (writer != nullptr) {                                                                                      //自定义写笔
        writer->setTextColor(Color4B::RED);
        writer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        writer->setDimensions(400, 0);
        //writer->setScale(2);

        writer->setPosition(Vec2(visibleSize.width/2 + 30, visibleSize.height/2 + 30));

        this->addChild(writer, 2);
        this->schedule([&](float dlt) {
            std::string s = "Great works are performed not by strength but by perseverance.                                    Mumbers:                     Dai Zhenqi   Lu zhichen   Li bojing";
            std::string s2 = "";
            static int i = 0;
            s2 = s.substr(0, i);
            i++;

            if (i == s.size() + 1) {
                this->unschedule("w");
            }

            writer->setString(s2);
            }, 0.05f, "w");

    }

    //设置背景
    auto background = Sprite::create("GameInterface.png");
    if (background == nullptr) {
        problemLoading("GameInterface.png");
    }
    else {
        background->setScale(1.3f);
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(background, 0);
    }

    //显示游戏名字
    auto name = Label::createWithTTF("Travel", "fonts/Marker Felt.ttf", 100);
    name->setColor(ccc3(245, 222, 179));
    name->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.3));
    this->addChild(name, 1);

    //设置游戏关闭菜单
    auto exit = Label::createWithSystemFont("EXIT", "fonts/arial.ttf", 35);
    auto closeItem = MenuItemLabel::create(exit, CC_CALLBACK_1(GameStart::menuCloseCallback, this));  //根据标签创建菜单条目，设置回调函数
    auto menuClose = Menu::create(closeItem, NULL);    //创建菜单
    menuClose->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4));
    this->addChild(menuClose, 1);

    //设置游戏开始菜单
    auto start = Label::createWithSystemFont("START", "fonts/arial.ttf", 35);
    auto startItem = MenuItemLabel::create(start, CC_CALLBACK_1(GameStart::menuStartCallback, this));
    auto menuStart = Menu::create(startItem, NULL);
    menuStart->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3));
    this->addChild(menuStart, 1);

    return true;
}



void GameStart::menuCloseCallback(Ref* pSender){
    //Close the cocos2d-x game scene and quit the application
    MessageBox("Game exiting...", "Travel");
    Director::getInstance()->end();
}


void GameStart::menuStartCallback(Ref* pSender) {
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, Loading::createScene()));
}