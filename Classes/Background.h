#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__
#include"ui/CocosGUI.h"
#include "cocos2d.h"

class Background : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();
    //Sprite* mysprite;
    virtual bool init();
    cocos2d::EventListenerKeyboard* listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    cocos2d::EventListenerKeyboard* listenerKeyboard2 = cocos2d::EventListenerKeyboard::create();
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void Background::update(float delta);
    void background_move(int direction, int speed);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(Background);

};

#endif // __BACKGROUND_H__
