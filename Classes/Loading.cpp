#include "Loading.h"
#include "Town_6.h"

USING_NS_CC;

Scene* Loading::createScene() {
	return Loading::create();
}

bool Loading::init() {
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto label = Label::createWithSystemFont("Laoding...", "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5));
	this->addChild(label, 1);



	auto loadBg = Sprite::create("ui/sliderTrack.png");//进程条的底图
	loadBg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(loadBg, 1);

	loadProgress = ProgressTimer::create(Sprite::create("ui/sliderProgress.png"));//创建一个进程条
	loadProgress->setBarChangeRate(Point(1, 0));//设置进程条的变化速率
	loadProgress->setType(ProgressTimer::Type::BAR);//设置进程条的类型
	loadProgress->setMidpoint(Point(0, 1));//设置进度的运动方向
	loadProgress->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	loadProgress->setPercentage(0.0f);//设置初始值为0
	this->addChild(loadProgress, 2);

	schedule(schedule_selector(Loading::onScheduleCallBack), 0.1f);


	return true;
}

void Loading::onScheduleCallBack(float dt) {
	loadProgress->setPercentage(loadProgress->getPercentage() + 2);

	//加载完成，停止计时器，进入下一个场景
	if (loadProgress->getPercentage() >= 100) {
		unscheduleAllSelectors();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, Town_6::createScene()));
	}
}