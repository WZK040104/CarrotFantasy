#ifndef __MUSIC_SCENE_H__
#define __MUSIC_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"//������������ͷ�ļ�
#include "ui/CocosGUI.h"
using namespace CocosDenshion;//ʹ�ø���������������ռ�  

class SoundManager : public cocos2d::Scene
{
public:
	/* ���ű������� */
	void BackgroundMusic(Ref* pSender);
};
#endif