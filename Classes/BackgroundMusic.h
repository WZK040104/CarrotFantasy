#ifndef __MUSIC_SCENE_H__
#define __MUSIC_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"//包含声音引擎头文件
#include "ui/CocosGUI.h"
using namespace CocosDenshion;//使用该声音引擎的命名空间  
using namespace cocos2d;

class SoundManager : public cocos2d::Scene
{
public:
	/* 播放背景音乐 */
	void BackgroundMusic(Ref* pSender)
	{
		auto audio = SimpleAudioEngine::getInstance();
		// 预加载
		audio->preloadBackgroundMusic("BackgroundMusic.mp3");
		// 控制音量
		audio->setEffectsVolume(0.5);
		audio->setBackgroundMusicVolume(0.5);
		// 反复播放
		audio->playBackgroundMusic("BackgroundMusic.mp3", true);
	}
	/* 设置音乐控制按钮 */
	/*void MusicSet(Ref* pSender)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto startItem = MenuItemImage::create("SoundButton.png",
			"SoundButton.png", CC_CALLBACK_1(BackgroundMusic, this));

		float x = origin.x;
		float y = origin.y;
		startItem->setPosition(Vec2(x, y));
	}*/
};
#endif