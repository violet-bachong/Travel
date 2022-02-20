#ifndef __TOWN_4_H__
#define __TOWN_4_H__

#include"ui/CocosGUI.h"
#include "cocos2d.h"

class Town_4 : public cocos2d::Scene
{
public:

    Sprite* role;
    Sprite* background;
    bool is_left = true;
    Action* animate;
    Sprite* frameAni;
    bool can_frame = true;
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;

    static cocos2d::Scene* createScene();
    //Sprite* mysprite;
    virtual bool init();
    void Town_4::skillA(double distance);
    void Town_4::skillB(double distance);
    void Town_4::skillC();
    cocos2d::EventListenerKeyboard* listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    cocos2d::EventListenerKeyboard* listenerKeyboard2 = cocos2d::EventListenerKeyboard::create();
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void Town_4::update(float delta);
    void background_move(int direction, int speed);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void scheduleBlood(float dt);
    void scheduleBlue(float dt);
    void addMonster();
    CREATE_FUNC(Town_4);

};

#endif // __TOWN_4_H__
