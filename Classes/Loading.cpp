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



	auto loadBg = Sprite::create("ui/sliderTrack.png");//�������ĵ�ͼ
	loadBg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(loadBg, 1);

	loadProgress = ProgressTimer::create(Sprite::create("ui/sliderProgress.png"));//����һ��������
	loadProgress->setBarChangeRate(Point(1, 0));//���ý������ı仯����
	loadProgress->setType(ProgressTimer::Type::BAR);//���ý�����������
	loadProgress->setMidpoint(Point(0, 1));//���ý��ȵ��˶�����
	loadProgress->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	loadProgress->setPercentage(0.0f);//���ó�ʼֵΪ0
	this->addChild(loadProgress, 2);

	schedule(schedule_selector(Loading::onScheduleCallBack), 0.1f);


	return true;
}

void Loading::onScheduleCallBack(float dt) {
	loadProgress->setPercentage(loadProgress->getPercentage() + 2);

	//������ɣ�ֹͣ��ʱ����������һ������
	if (loadProgress->getPercentage() >= 100) {
		unscheduleAllSelectors();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, Town_6::createScene()));
	}
}