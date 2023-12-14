#ifndef __MUSIC_SCENE_H__
#define __MUSIC_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"//������������ͷ�ļ�
#include "ui/CocosGUI.h"
using namespace CocosDenshion;//ʹ�ø���������������ռ�  
using namespace cocos2d;

class SoundManager : public cocos2d::Scene
{
public:
	/* ���ű������� */
	void BackgroundMusic(Ref* pSender)
	{
		auto audio = SimpleAudioEngine::getInstance();
		// Ԥ����
		audio->preloadBackgroundMusic("BackgroundMusic.mp3");
		// ��������
		audio->setEffectsVolume(0.5);
		audio->setBackgroundMusicVolume(0.5);
		// ��������
		audio->playBackgroundMusic("BackgroundMusic.mp3", true);
	}
};
#endif