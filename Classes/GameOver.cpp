#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "Town_6.h"

USING_NS_CC;

Scene* GameOver::createScene() {
    return GameOver::create();
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool GameOver::init() {

    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


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

    //显示游戏结束
    auto over = Label::createWithSystemFont("game over!!!", "fonts/arial.ttf", 50);
    over->setTextColor(Color4B::RED);
    over->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(over, 1);

    //设置游戏关闭按钮
    auto exit = Label::createWithSystemFont("EXIT", "fonts/arial.ttf", 35);
    auto closeItem = MenuItemLabel::create(exit, CC_CALLBACK_1(GameOver::menuCloseCallback, this));  //根据标签创建菜单条目，设置回调函数
    auto menuClose = Menu::create(closeItem, NULL);    //创建菜单
    menuClose->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4));
    this->addChild(menuClose, 1);

    //设置游戏继续按钮
    auto start = Label::createWithSystemFont("RESTART", "fonts/arial.ttf", 35);
    auto startItem = MenuItemLabel::create(start, CC_CALLBACK_1(GameOver::menuStartCallback, this));
    auto menuStart = Menu::create(startItem, NULL);
    menuStart->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3));
    this->addChild(menuStart, 1);

    return true;
}



void GameOver::menuCloseCallback(Ref* pSender) {
    //Close the cocos2d-x game scene and quit the application
    MessageBox("Game exiting...", "Travel");
    Director::getInstance()->end();
}


void GameOver::menuStartCallback(Ref* pSender) {
    Director::getInstance()->replaceScene(Town_6::createScene());
}