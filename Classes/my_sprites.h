#ifndef __my_sprites_H__
#define __my_sprites_H__
#include "cocos2d.h"

using namespace cocos2d;

class my_sprites : public cocos2d::Sprite
{
public:
    int role_id = 1;
    CCAnimation* animation;
    Action* animate_W;
    Action* animate_A;
    Action* animate_S;
    Action* animate_D;
    Action* animate_J;
    bool now;

    bool attacking = false;
    int role_derection;
    bool action_listener = true;
    bool alive = true;

    int x_add;
    int y_add;
    int derection = 1;


    static my_sprites* createSprite(const char* picFileName);
    Action* createMyAction(int role_id, int strat, int end, float f);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);


    CREATE_FUNC(my_sprites);
};

#endif // __my_sprites_H__