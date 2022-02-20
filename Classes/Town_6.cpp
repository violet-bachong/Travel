/*
#include "SimpleAudioEngine.h"
#include "Town_6.h"
#include "Town_5.h"

USING_NS_CC;

Scene* Town_6::createScene() {
    return Town_6::create();
}


bool Town_6::init() {

    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //设置背景
    auto background = Sprite::create("town/Town6.jpeg");
    background->setScale(2.3f);
    background->setAnchorPoint(Vec2(1, 0.5));
    background->setPosition(Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height / 2));
    this->addChild(background, 0);

    /*
    //场景跳转
    if (role->getPosition().x == background->getPosition().x - background->getContentSize().width + 50) {
        Director::getInstance()->pushScene(TransitionFade::create(0.5f, Town_5::createScene()));
    }
    

    return true;
}


void Town_6::menuChangeToFiveCallback(Ref* pSender) {
    Director::getInstance()->pushScene(TransitionFade::create(0.5f, Town_5::createScene()));
}*/




#include"iostream"
#include "SimpleAudioEngine.h"
#include "string.h"
#include"ui/CocosGUI.h"
#include "my_sprites.h"
#include "Town_5.h"
#include "Town_6.h"
#include "Pause.h"
#include "Data.h"

using namespace cocos2d;
using namespace std;
using namespace ui;



Scene* Town_6::createScene()
{
    return Town_6::create();
}
//int   begin_jump = bottom;
/*Sprite* role;
Sprite* background;
bool is_left = true;
Action* animate;
Sprite* frameAni;
bool can_frame = true;
std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;*/



bool Town_6::init()
{

    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //设置背景
    background = Sprite::create("town/Town6.jpeg");
    background->setScale(2.3f);
    background->setAnchorPoint(Vec2(1, 0.5));
    background->setPosition(Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height / 2));
    background->setTag(1);
    this->addChild(background, 0);

    //血条
    auto blood = Sprite::create("ui/bar.png");   //创建进度框
    blood->setPosition(Point(blood->getContentSize().width / 2, visibleSize.height - 20)); //设置框的位置
    this->addChild(blood);            //加到默认图层里面去
    auto sprBlood = Sprite::create("ui/blood.png");  //创建血条
    ProgressTimer* progressBlood = ProgressTimer::create(sprBlood); //创建progress对象
    progressBlood->setType(ProgressTimer::Type::BAR);        //类型：条状
    progressBlood->setPosition(Point(blood->getContentSize().width / 2, visibleSize.height - 20));
    //从右到左减少血量
    progressBlood->setMidpoint(Point(0, 0.5));     //如果是从左到右的话，改成(1,0.5)即可
    progressBlood->setBarChangeRate(Point(1, 0));
    progressBlood->setTag(5);       //做一个标记
    this->addChild(progressBlood);
    schedule(schedule_selector(Town_6::scheduleBlood), 0.1f);  //刷新函数，每隔0.1秒

    //蓝条
    auto blue = Sprite::create("ui/bar.png");   //创建进度框
    blue->setPosition(Point(blue->getContentSize().width / 2, visibleSize.height - 40)); //设置框的位置
    this->addChild(blue);            //加到默认图层里面去
    auto sprBlue = Sprite::create("ui/blue.png");  //创建蓝条
    ProgressTimer* progressBlue = ProgressTimer::create(sprBlue); //创建progress对象
    progressBlue->setType(ProgressTimer::Type::BAR);        //类型：条状
    progressBlue->setPosition(Point(blue->getContentSize().width / 2, visibleSize.height - 40));
    progressBlue->setMidpoint(Point(0, 0.5));     //如果是从左到右的话，改成(1,0.5)即可
    progressBlue->setBarChangeRate(Point(1, 0));
    progressBlue->setTag(6);       //做一个标记
    this->addChild(progressBlue);
    schedule(schedule_selector(Town_6::scheduleBlue), 0.1f);  //刷新函数，每隔0.1秒


    //Action* scale = ScaleTo::create(.1, 1.2, 1.6);                                                                                    //背景缩放设置
    //background->runAction(scale);

    // role = Sprite::create("role.jpg");     
    role = my_sprites::createSprite("sprites/1-4.png");
    //设置游戏主人翁
    role->setPosition(Vec2(visibleSize.width - 200, 250));
    role->setScale(2);
    this->addChild(role, 2);

    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Town_6::onKeyPressed, this);
    listenerKeyboard2->onKeyReleased = CC_CALLBACK_2(Town_6::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard2, this);
    this->scheduleUpdate();

    return true;
}

void Town_6::scheduleBlood(float delta) {
    auto progress = (ProgressTimer*)this->getChildByTag(5);
    progress->setPercentage((((float)role_blood) / 10000) * 100);  //这里是百分制显示
    if (progress->getPercentage() < 0) {
        this->unschedule(schedule_selector(Town_6::scheduleBlood));
    }
}

void Town_6::scheduleBlue(float delta) {
    auto progress = (ProgressTimer*)this->getChildByTag(6);
    progress->setPercentage((((float)role_energy) / 10000) * 100);  //这里是百分制显示
    if (progress->getPercentage() < 0) {
        this->unschedule(schedule_selector(Town_6::scheduleBlood));
    }
}

void Town_6::background_move(int direction, int speed) {                                                                                 //背景移动
    auto role_size = role->getContentSize();
    auto back_p = background->getPosition();
    auto back_size = background->getContentSize();
    auto window_size = this->getContentSize();
    if (direction == 1) {
        if (back_p.x <= window_size.width + role_size.width)return;
        Action* go_right = MoveBy::create(.1, Vec2(0 - speed, 0));
        background->runAction(go_right);
    }
    else {
        if (back_p.x - back_size.width > (back_size.width + 0.5 * window_size.width) / 2 - role_size.width)return;
        Action* go_left = MoveBy::create(.1, Vec2(speed, 0));
        background->runAction(go_left);
    }
}

/*void Town_6::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)                                  //按下按键&&跳跃
{

    log("onKeyPressed");
    keyMap[keyCode] = true;
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_SPACE:
    {
        auto role_p1 = role->getPosition();
        int role_x = role_p1.x;
        int role_y = role_p1.y;
        int  delta_h = role_y - bottom;
        CCLOG("SPACE current height:  %d,jump_begin: %d", role_y, begin_jump);

        if (role_y > begin_jump && role_y <= begin_jump + jump_height + 1 && can_jump_twice && jump_twice_num) {
            jump_twice_num = false;
            Action* jump2 = JumpBy::create(.5, Vec2(0, 0), 2 * jump_height, 1);
            role->runAction(jump2);
            break;
        }
        if (role_y > begin_jump) {
            break;
        }
        if (role_y <= begin_jump) {
            jump_twice_num = true;
            Action* jump = JumpBy::create(.5, Vec2(0, 0), jump_height, 1);
            role->runAction(jump);
        }

        break;
    }
    default:
        break;
    }

}*/


void Town_6::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)                                  //按下按键&&跳跃
{
    auto  background_p = background->getPosition();
    auto back_size = background->getContentSize();
    log("onKeyPressed");
    keyMap[keyCode] = true;
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_SPACE: 
    {
        Action* jump = JumpBy::create(.5, Vec2(0, 0), 100, 1);  
        role->runAction(jump);
        break;
    }
    case EventKeyboard::KeyCode::KEY_Q:
    {
        if (background_p.x > back_size.width * 1.6) {
            Director::getInstance()->pushScene(Town_5::createScene());
        }
        break;
    }
    case EventKeyboard::KeyCode::KEY_ESCAPE:
    {
        Director::getInstance()->pushScene(Pause::createScene());
        break;
    }
    default:
        break;
    }

}

void Town_6::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)                              //释放按键
{

    log("onKeyReleased");
    keyMap[keyCode] = false;

}


void Town_6::update(float delta)                                                                                                         //左右移动
{
    auto w = EventKeyboard::KeyCode::KEY_W;
   
    auto s = EventKeyboard::KeyCode::KEY_S;
    auto a = EventKeyboard::KeyCode::KEY_A;
    auto d = EventKeyboard::KeyCode::KEY_D;
    auto f = EventKeyboard::KeyCode::KEY_F;
    auto role_p1 = role->getPosition();
    auto visible = Director::getInstance()->getOpenGLView()->getFrameSize();
    int role_x = role_p1.x;
    int role_y = role_p1.y;
    auto  background_p = background->getPosition();
    int background_x = background_p.x;
    int background_y = background_p.y;

    auto role_size = role->getContentSize();
    int   role_size_w = role_size.width;
    int   role_size_h = role_size.height;

    auto back_size = background->getContentSize();
    int   back_size_w = back_size.width;
    int   back_size_h = back_size.height;
    //CCLOG("  %d,back_begin: %d", background_y, back_y_begin);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    if (keyMap[a])
    {

        is_left = true;
        if (role_x > role_size_w * 2) {
            Action* go_left = MoveBy::create(.01, Vec2(-4, 0));
            role->runAction(go_left);
        }
        else {
            if (background_x < back_size_w * 1.6) {
                this->background_move(2, 5);
            }
        }
    }
    if (keyMap[d])
    {

        role->setScaleX(2);
        is_left = false;

        if (role_x < visible.width - role_size_w * 2) {
            Action* go_right = MoveBy::create(.01, Vec2(4, 0));
            role->runAction(go_right);
        }
        else {
            this->background_move(1, 5);
        }
    }
    if (keyMap[w])                                                                                                                                                               //上下移动
    {
        // CCLOG("SBack_y:  %d,back_begin: %d", background_y, back_y_begin);
        if (role_y <= visibleSize.height/2 + 20) {
            Action* go_up = MoveBy::create(.1, Vec2(0, 3));
            role->runAction(go_up);
        }
    }
    if (keyMap[s])
    {
        //CCLOG("WBack_y:  %d,back_begin: %d", background_y, back_y_begin);
        if (role_y >= visibleSize.height / 2 - 50) {
            Action* go_down = MoveBy::create(.1, Vec2(0, -3));
            role->runAction(go_down);
        }
    }

    if (keyMap[f])
    {
        if (is_left) {
            if (role_x > 100) {
                Action* go_left = MoveBy::create(.1, Vec2(-10, 0));
                role->runAction(go_left);
            }
            else {
                this->background_move(2, 10);
            }
        }
        else {
            if (role_x < 400) {
                Action* go_right = MoveBy::create(.1, Vec2(10, 0));
                role->runAction(go_right);
            }
            else {
                this->background_move(1, 10);
            }
        }
    }


}