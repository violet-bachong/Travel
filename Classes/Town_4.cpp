#include"iostream"
#include "SimpleAudioEngine.h"
#include "string.h"
#include"ui/CocosGUI.h"
#include "my_sprites.h"
#include "Town_3.h"
#include "Town_5.h"
#include "Town_4.h"
#include "Pause.h"
#include "Data.h"


using namespace cocos2d;
using namespace std;
using namespace ui;

vector<my_sprites*> monsters;
vector<my_sprites*>monsters_attaccks;

bool can_create = true;//怪物生成判断
unordered_map<Sprite*, bool> mp;//怪物显示标记
unordered_map<my_sprites*, bool> mp_pao;//炮弹显示标记
unordered_map<Sprite*, pair<double, double > > monsters_d; //怪物的血量和攻击值
unordered_map< my_sprites*, Sprite*> pao_2_m;


int re_time = 0;//记录刷新次数用于怪物攻击任务


int refresh = 1;


Scene* Town_4::createScene()
{
    return Town_4::create();
}



bool Town_4::init()
{

    if (!Scene::init())
    {
        return false;
    }
    srand(1);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //设置背景
    background = Sprite::create("town/Town4.jpeg");
    //background->setScale(0.9f);
    background->setAnchorPoint(Vec2(0, 0.5));
    background->setPosition(Vec2(0, origin.y + visibleSize.height / 2));
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
    schedule(schedule_selector(Town_4::scheduleBlood), 0.1f);  //刷新函数，每隔0.1秒

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
    schedule(schedule_selector(Town_4::scheduleBlue), 0.1f);  //刷新函数，每隔0.1秒

    role = my_sprites::createSprite("sprites/1-8.png");
    //设置游戏主人翁
    role->setPosition(Vec2(origin.x + role->getContentSize().width, 200));
    role->setScale(2);
    this->addChild(role, 4);

    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Town_4::onKeyPressed, this);
    listenerKeyboard2->onKeyReleased = CC_CALLBACK_2(Town_4::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard2, this);
    this->scheduleUpdate();

    return true;
}

void Town_4::skillA(double distance) {           //人物技能A
    if (!can_create)return;
    can_create = false;
    auto role_s = role->getPosition();
    vector<my_sprites*>::iterator it = monsters.begin();
    int a = 0;
    int s = monsters.size();
    for (int i = 0; i < s; i++) {
        if (mp[monsters[i + a]])continue;
        auto npc_s = monsters[i + a]->getPosition();
        if (sqrt((role_s.x - npc_s.x) * (role_s.x - npc_s.x) + (role_s.y - npc_s.y) * (role_s.y - npc_s.y)) <= distance
            && ((is_left && (float)npc_s.x - role_s.x <= 0.5) || (!is_left && (float)npc_s.x - role_s.x >= 0.5))) {
            if (monsters[i + a] != nullptr && !mp[monsters[i + a]]) {
                mp[monsters[i + a]] = true;
                this->removeChild(monsters[i + a]);
                break;
            }
        }
    }
    can_create = true;
}


void Town_4::skillB(double distance) {              //人物技能B
    double need_energy = 30;
    if (role_energy < need_energy)return;
    role_energy -= need_energy;
    double attack = 15;   //技能B的伤害
    if (!can_create)return;
    can_create = false;
    auto role_s = role->getPosition();
    vector<my_sprites*>::iterator it = monsters.begin();
    int a = 0;
    int s = monsters.size();
    for (int i = 0; i < s; i++) {
        if (mp[monsters[i + a]])continue;
        auto npc_s = monsters[i + a]->getPosition();
        if (sqrt((role_s.x - npc_s.x) * (role_s.x - npc_s.x) + (role_s.y - npc_s.y) * (role_s.y - npc_s.y)) <= distance
            && ((is_left && (float)npc_s.x - role_s.x <= 0.5) || (!is_left && (float)npc_s.x - role_s.x >= 0.5))) {
            if (monsters[i + a] != nullptr && !mp[monsters[i + a]]) {
                monsters_d[monsters[i + a]].first -= attack;
                if (monsters_d[monsters[i + a]].first <= 0) {
                    mp[monsters[i + a]] = true;
                    this->removeChild(monsters[i + a]);
                }
            }
        }
    }
    can_create = true;
}

void Town_4::skillC() {              //人物技能C
    double need_energy = 200;
    if (role_energy < need_energy)return;
    role_energy -= need_energy;
    if (!can_create)return;
    can_create = false;
    vector<my_sprites*>::iterator it = monsters.begin();
    int a = 0;
    int s = monsters.size();
    for (int i = 0; i < s; i++) {
        if (mp[monsters[i + a]])continue;
        auto npc_s = monsters[i + a]->getPosition();
        if (monsters[i + a] != nullptr && !mp[monsters[i + a]]) {
            mp[monsters[i + a]] = true;
            this->removeChild(monsters[i + a]);
        }
    }
    can_create = true;
}

void Town_4::scheduleBlood(float delta) {
    auto progress = (ProgressTimer*)this->getChildByTag(5);
    progress->setPercentage((((float)role_blood) / 10000) * 100);  //这里是百分制显示
    if (progress->getPercentage() < 0) {
        this->unschedule(schedule_selector(Town_4::scheduleBlood));
    }
}

void Town_4::scheduleBlue(float delta) {
    auto progress = (ProgressTimer*)this->getChildByTag(6);
    progress->setPercentage((((float)role_energy) / 10000) * 100);  //这里是百分制显示
    if (progress->getPercentage() < 0) {
        this->unschedule(schedule_selector(Town_4::scheduleBlood));
    }
}

void Town_4::background_move(int direction, int speed) {                                                                                 //背景移动
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

void Town_4::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)                                  //按下按键&&跳跃
{
    auto role_p = role->getPosition();
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
        if (background_p.x + back_size.width >= window_size.width - 100) {
            Director::getInstance()->pushScene(Town_3::createScene());
        }
        break;
    }
    case EventKeyboard::KeyCode::KEY_ESCAPE:
    {
        Director::getInstance()->pushScene(Pause::createScene());
        break;
    }
    case EventKeyboard::KeyCode::KEY_J:
    {
        skillA(100);
        CCParticleSystemQuad* particle = CCParticleSystemQuad::create("expsion4.plist");
        particle->setPosition(Vec2(role_p.x, role_p.y));
        particle->setAutoRemoveOnFinish(true);
        particle->setScale(0.5);
        this->addChild(particle, 3);
        break;
    }
    case EventKeyboard::KeyCode::KEY_K:
    {
        skillB(100);
        break;
    }
    case EventKeyboard::KeyCode::KEY_L:
    {
        skillC();
        CCParticleSystemQuad* particle = CCParticleSystemQuad::create("explation3.plist");
        particle->setPosition(Vec2(role_p.x, role_p.y));
        particle->setAutoRemoveOnFinish(true);
        //particle->setScale(0.2);
        this->addChild(particle, 3);
        break;
    }
    default:
        break;
    }

}

void Town_4::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)                              //释放按键
{

    log("onKeyReleased");
    keyMap[keyCode] = false;

}


void Town_4::update(float delta)                                                                                                         //左右移动
{
    //Sleep(1000);
    if (!can_create)CCLOG("dycj");
    auto w = EventKeyboard::KeyCode::KEY_W;
    auto s = EventKeyboard::KeyCode::KEY_S;
    auto a = EventKeyboard::KeyCode::KEY_A;
    auto d = EventKeyboard::KeyCode::KEY_D;
    auto f = EventKeyboard::KeyCode::KEY_F;
    auto role_p = role->getPosition();
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
    if (keyMap[w])                                                                                                                                                               //上下移动
    {
        // CCLOG("SBack_y:  %d,back_begin: %d", background_y, back_y_begin);
        if (role_y <= 300) {
            Action* go_up = MoveBy::create(.1, Vec2(0, 3));
            role->runAction(go_up);
        }
    }
    if (keyMap[s])
    {
        //CCLOG("WBack_y:  %d,back_begin: %d", background_y, back_y_begin);
        if (role_y >= role_size_h + 50) {
            Action* go_down = MoveBy::create(.1, Vec2(0, -3));
            role->runAction(go_down);
        }
    }


    //role失血
    CCLOG("%lf", role_blood);
    re_time = (re_time + 1) % 10000000;
    if (re_time % 10 == 0) {
        role_energy += 5;
    }                                                                                                                                                        //能量增加
    double m_dis = 10;
    auto role_s = role->getPosition();
    for (auto p : monsters_attaccks) {
        if (mp_pao[p])continue;
        mp_pao[p] = true;
        auto npc_s = p->getPosition();
        mp_pao[p] = false;
        if (sqrt((role_s.x - npc_s.x) * (role_s.x - npc_s.x) + (role_s.y - npc_s.y) * (role_s.y - npc_s.y)) <= m_dis) {
            role_blood -= monsters_d[pao_2_m[p]].second;
            if (role_blood <= 0) {

                role->setScale(0.001);  
                auto over = Label::createWithTTF("game over!!!", "fonts/Marker Felt.ttf", 100);
                over->setTextColor(Color4B::RED);
                over->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
                this->addChild(over, 5);
                
                //游戏结束
            }
        }

    }



    //移动所有炮弹
    for (auto attack1 : monsters_attaccks) {
        if (mp_pao[attack1] == true)continue;
        mp_pao[attack1] = true;
        auto attack_p = attack1->getPosition();
        mp_pao[attack1] = false;
        if (attack_p.x + attack1->x_add > 400 || attack_p.x + attack1->y_add < 0 || attack_p.y + attack1->y_add > 400 || attack_p.y + attack1->y_add < 0) {
            mp_pao[attack1] = true;
            this->removeChild(attack1);
            // monsters_attaccks.erase(monsters_attaccks.find(attack));
        }
        else {
            mp_pao[attack1] = true;
            attack1->setPosition(Vec2(attack_p.x + attack1->x_add, attack_p.y + attack1->y_add));
            mp_pao[attack1] = false;;
        }
    }


    //移动所有怪物
    for (auto monster : monsters) {

        if (mp[monster])continue;
        mp[monster] = true;
        auto monster_p = monster->getPosition();

        //怪物攻击
        if (rand() % 100 == 0) {
            my_sprites* paodan = my_sprites::createSprite("paodan.png");
            pao_2_m[paodan] = monster;
            double x_sub = role_p.x - monster_p.x;
            double y_sub = role_p.y - monster_p.y;
            mp_pao[paodan] = true;
            paodan->x_add = 4 * x_sub / (fabs(x_sub) + fabs(y_sub));
            paodan->y_add = 4 * y_sub / (fabs(x_sub) + fabs(y_sub));
            paodan->action_listener = false;
            paodan->setPosition(monster_p);
            paodan->setScale(0.3);
            this->addChild(paodan, 2);
            monsters_attaccks.push_back(paodan);
            mp_pao[paodan] = false;
        }




        mp[monster] = false;
        if (monster_p.x - role_p.x > 20 || monster_p.x - role_p.x < -20) {
            monster_p.x = monster_p.x + (role_p.x - monster_p.x) / fabs(monster_p.x - role_p.x) / 4;

            if (monster_p.x < role_p.x && !monster->derection) {
                monster->setScaleX(1);
                monster->derection = 1;
            }
            else if (monster_p.x > role_p.x && monster->derection) {
                monster->setScaleX(-1);
                monster->derection = 0;
            }

        }
        if (monster_p.y != role_p.y) {
            monster_p.y = monster_p.y + (role_p.y - monster_p.y) / fabs(monster_p.y - role_p.y) / 4;
        }
        mp[monster] = true;
        monster->setPosition(monster_p);
        mp[monster] = false;
    }


    // 生成新的怪物
    if (rand() % 100 == 1 && monsters.size() <= 1000) {
        my_sprites* monster = my_sprites::createSprite("3-0.png");
        mp[monster] = true;
        monsters_d[monster].first = 20;
        monsters_d[monster].second = 10;
        monster->role_id = 3;
        monster->action_listener = false;
        Action* monster_move = monster->createMyAction(3, 0, 7, 0.1);
        mp[monster] = false;
        if (monster != nullptr) {
            mp[monster] = true;

            int X_position = rand() % (int)(Director::getInstance()->getVisibleSize().width);
            int Y_position = rand() % (int)(Director::getInstance()->getVisibleSize().width) / 2;
            if (X_position > role_p.x) {
                monster->setScaleX(-1);
            }
            monster->setPosition(Vec2(X_position, Y_position));

            //monster->setScale(2);
            mp[monster] = false;
            if (monster_move != nullptr) {
                mp[monster] = true;
                monster->runAction(monster_move);
                this->addChild(monster, 2);
                monsters.push_back(monster);
                log("add");
                mp[monster] = false;
            }

            else {
                log("move isnull""");
            }
        }
        else {
            log("monster is null::::::");
        }
    }

}