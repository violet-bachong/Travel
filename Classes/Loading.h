#ifndef __LOADING_H__
#define __LOADING_H__

#include "cocos2d.h"

using namespace cocos2d;

class Loading : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void onScheduleCallBack(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(Loading);

private:
    cocos2d::ProgressTimer* loadProgress;
};

#endif // __LOADING_H__