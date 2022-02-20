#include"iostream"
#include "SimpleAudioEngine.h"
#include "string.h"
#include"ui/CocosGUI.h"
#include "my_sprites.h"
#include "Town_3.h"
#include "Town_2.h"
#include "Town_4.h"
#include "Pause.h"
#include "Data.h"

using namespace cocos2d;
using namespace std;
using namespace ui;
Scene* Town_3::createScene()
{
    return Town_3::create();
}



bool Town_3::init()
{

    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //���ñ���
    background = Sprite::create("town/Town3.jpeg");
    background->setScale(1.7);
    background->setAnchorPoint(Vec2(0, 0.5));
    background->setPosition(Vec2(0, origin.y + visibleSize.height / 2));
    this->addChild(background, 0);

    //Ѫ��
    auto blood = Sprite::create("ui/bar.png");   //�������ȿ�
    blood->setPosition(Point(blood->getContentSize().width / 2, visibleSize.height - 20)); //���ÿ��λ��
    this->addChild(blood);            //�ӵ�Ĭ��ͼ������ȥ
    auto sprBlood = Sprite::create("ui/blood.png");  //����Ѫ��
    ProgressTimer* progressBlood = ProgressTimer::create(sprBlood); //����progress����
    progressBlood->setType(ProgressTimer::Type::BAR);        //���ͣ���״
    progressBlood->setPosition(Point(blood->getContentSize().width / 2, visibleSize.height - 20));
    //���ҵ������Ѫ��
    progressBlood->setMidpoint(Point(0, 0.5));     //����Ǵ����ҵĻ����ĳ�(1,0.5)����
    progressBlood->setBarChangeRate(Point(1, 0));
    progressBlood->setTag(5);       //��һ�����
    this->addChild(progressBlood);
    schedule(schedule_selector(Town_3::scheduleBlood), 0.1f);  //ˢ�º�����ÿ��0.1��

    //����
    auto blue = Sprite::create("ui/bar.png");   //�������ȿ�
    blue->setPosition(Point(blue->getContentSize().width / 2, visibleSize.height - 40)); //���ÿ��λ��
    this->addChild(blue);            //�ӵ�Ĭ��ͼ������ȥ
    auto sprBlue = Sprite::create("ui/blue.png");  //��������
    ProgressTimer* progressBlue = ProgressTimer::create(sprBlue); //����progress����
    progressBlue->setType(ProgressTimer::Type::BAR);        //���ͣ���״
    progressBlue->setPosition(Point(blue->getContentSize().width / 2, visibleSize.height - 40));
    progressBlue->setMidpoint(Point(0, 0.5));     //����Ǵ����ҵĻ����ĳ�(1,0.5)����
    progressBlue->setBarChangeRate(Point(1, 0));
    progressBlue->setTag(6);       //��һ�����
    this->addChild(progressBlue);
    schedule(schedule_selector(Town_3::scheduleBlue), 0.1f);  //ˢ�º�����ÿ��0.1��

    role = my_sprites::createSprite("sprites/1-8.png");
    //������Ϸ������
    role->setPosition(Vec2(origin.x + role->getContentSize().width, 200));
    role->setScale(2);
    this->addChild(role, 2);

    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Town_3::onKeyPressed, this);
    listenerKeyboard2->onKeyReleased = CC_CALLBACK_2(Town_3::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard2, this);
    this->scheduleUpdate();

    return true;
}
void Town_3::scheduleBlood(float delta) {
    auto progress = (ProgressTimer*)this->getChildByTag(5);
    progress->setPercentage((((float)role_blood) / 10000) * 100);  //�����ǰٷ�����ʾ
    if (progress->getPercentage() < 0) {
        this->unschedule(schedule_selector(Town_3::scheduleBlood));
    }
}

void Town_3::scheduleBlue(float delta) {
    auto progress = (ProgressTimer*)this->getChildByTag(6);
    progress->setPercentage((((float)role_energy) / 10000) * 100);  //�����ǰٷ�����ʾ
    if (progress->getPercentage() < 0) {
        this->unschedule(schedule_selector(Town_3::scheduleBlood));
    }
}


void Town_3::background_move(int direction, int speed) {                                                                                 //�����ƶ�
    auto role_size = role->getContentSize();
    auto back_p = background->getPosition();
    auto back_size = background->getContentSize();
    auto window_size = this->getContentSize();
    if (direction == 1) {
        if (back_p.x + back_size.width <= window_size.width + role_size.width)return;
        Action* go_right = MoveBy::create(.1, Vec2(0 - speed, 0));
        background->runAction(go_right);
    }
    else {
        if (back_p.x > (back_size.width + 0.5 * window_size.width) / 2 - role_size.width)return;
        Action* go_left = MoveBy::create(.1, Vec2(speed, 0));
        background->runAction(go_left);
    }
}

void Town_3::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)                                  //���°���&&��Ծ
{
    auto  background_p = background->getPosition();
    auto back_size = background->getContentSize();
    auto window_size = this->getContentSize();
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
        if (background_p.x + back_size.width >= window_size.width - 200) {
            Director::getInstance()->pushScene(Town_2::createScene());
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

void Town_3::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)                              //�ͷŰ���
{

    log("onKeyReleased");
    keyMap[keyCode] = false;

}


void Town_3::update(float delta)                                                                                                         //�����ƶ�
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
            if (background_x >= 0) {
                Director::getInstance()->popScene();
            }
            else {
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
    if (keyMap[w])                                                                                                                                                               //�����ƶ�
    {
        // CCLOG("SBack_y:  %d,back_begin: %d", background_y, back_y_begin);
        if (role_y <= 270) {
            Action* go_up = MoveBy::create(.1, Vec2(0, 3));
            role->runAction(go_up);
        }
    }
    if (keyMap[s])
    {
        //CCLOG("WBack_y:  %d,back_begin: %d", background_y, back_y_begin);
        if (role_y >= role_size_h + 20) {
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