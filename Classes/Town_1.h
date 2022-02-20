#ifndef __TOWN_1_H__
#define __TOWN_1_H__

#include"ui/CocosGUI.h"
#include "cocos2d.h"

class Town_1 : public cocos2d::Scene
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
    cocos2d::EventListenerKeyboard* listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    cocos2d::EventListenerKeyboard* listenerKeyboard2 = cocos2d::EventListenerKeyboard::create();
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void Town_1::update(float delta);
    void background_move(int direction, int speed);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void scheduleBlood(float dt);
    void scheduleBlue(float dt);
    CREATE_FUNC(Town_1);

};

#endif // __TOWN_1_H__
