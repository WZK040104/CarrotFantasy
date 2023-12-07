#ifndef __MUSIC_SCENE_H__
#define __MUSIC_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"//包含声音引擎头文件
#include "ui/CocosGUI.h"
using namespace CocosDenshion;//使用该声音引擎的命名空间  

class SoundManager : public cocos2d::Scene
{
public:
	/* 播放背景音乐 */
	void BackgroundMusic(Ref* pSender);
};
#endif