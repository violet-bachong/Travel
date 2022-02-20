#include<string>
#include "my_sprites.h"



Action* testAction;

my_sprites* my_sprites::createSprite(const char* picFileName) {

    my_sprites* sprite = new my_sprites();

    if (sprite && sprite->initWithFile(picFileName))

    {
        auto listener = EventListenerKeyboard::create();
        listener->onKeyPressed = CC_CALLBACK_2(my_sprites::onKeyPressed, sprite);
        listener->onKeyReleased = CC_CALLBACK_2(my_sprites::onKeyReleased, sprite);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
        // testAction = sprite->createMyAction(0, 4, 0.1);
        sprite->now = false;
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;

}

void my_sprites::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (action_listener) {
        log("Key with keycode %d pressed", keyCode);
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_A:
            animate_A = createMyAction(role_id, 4, 8, 0.2);
            runAction(animate_A);
            now = true;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            animate_D = createMyAction(role_id, 8, 12, 0.2);
            runAction(animate_D);
            now = true;
            break;
        case EventKeyboard::KeyCode::KEY_W:
            animate_W = createMyAction(role_id, 12, 16, 0.2);
            runAction(animate_W);
            now = true;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            animate_S = createMyAction(role_id, 0, 4, 0.2);
            runAction(animate_S);
            now = true;
            break;
        case EventKeyboard::KeyCode::KEY_F:
            if (this == testAction->getTarget()) {
                log("TRUE");
            }
            //        runAction(testAction->clone());
            now = true;
            break;
        default:
            break;
        }
    }

}

void my_sprites::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{


    if (action_listener) {
        switch (keyCode)
        {
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            if (now) {
                stopAction(animate_W);
                log("W stop");
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            if (now) {
                stopAction(animate_A);
                log("A stop");
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            if (now) {
                stopAction(animate_S);
                log("S stop");
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            if (now) {
                stopAction(animate_D);
                log("D stop");
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_F:
            /* if (now) {
                 stopAction(testAction);
             }*/
            break;
        default:
            break;
        }
        log("Key with keycode %d released", keyCode);
    }
}
Action* my_sprites::createMyAction(int role_id, int start, int end, float f)  //创建动画输入为图片起始到结束和播放间隔，间隔一半0.1到0.5
{
    CCAnimation* animation = CCAnimation::create();
    for (int i = start; i < end; i++)
    {
        char str[100];
        sprintf(str, "sprites/%d-%d.png", role_id, i);
        //getContentSize 得到精灵的宽和高。
        CCRect rect = CCRect(0, 0, this->getContentSize().width, this->getContentSize().height);
        //第二个参数指定截取第一个参数指定的图片的一部分。
        CCSpriteFrame* frame = CCSpriteFrame::create(str, rect);//添加精灵帧
        animation->addSpriteFrame(frame);
    }
    //设置帧间隔时间，此参数必须设置，无此参数支画不会播放。
    if (f > 0) {
        animation->setDelayPerUnit(f);
    }
    else {
        animation->setDelayPerUnit(0.1f);
    }
    //动画播放完毕后，帧序是否重设为默认第一帧。
    animation->setRestoreOriginalFrame(true);
    //循环次数。
    animation->setLoops(-1);
    animation = animation;
    //形成动画效果
    Action* animate = CCAnimate::create(animation);
    return animate;
}
