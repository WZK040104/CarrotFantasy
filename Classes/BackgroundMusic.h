#ifndef __MUSIC_SCENE_H__
#define __MUSIC_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
using namespace cocos2d::experimental;

class SoundManager : public cocos2d::Scene
{
public:
	/* ≤•∑≈±≥æ∞“Ù¿÷ */
	void BackgroundMusic(Ref* pSender)
	{
		auto backgroundAudioID = AudioEngine::play2d("BackgroundMusic.mp3", true);
	}
};
#endif