#ifndef __GAME_START_H__
#define __GAME_START_H__

#include "cocos2d.h"

class GameStart : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuStartCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameStart);
};

#endif // __GAME_START_H__