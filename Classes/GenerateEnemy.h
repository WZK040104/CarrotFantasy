#ifndef __GENERATE__ENEMY__H__
#define __GENERATE__ENEMY__H__

#include"CEnemy.h"
#include"Enemy_kind.h"
#include<vector>
#include <chrono> // for std::chrono::seconds
#include <thread> // for std::this_thread::sleep_for

using namespace std;

extern vector<CEnemy*> EnemyExist;

class GenerateEnemy : public cocos2d::Node
{
public:
	void generateOneEnemy(vector<CEnemy*>& EnemyExist, int enemyType, double x, double y);
	void deleteEnemy(vector<CEnemy*>& EnemyExist);
	int numofEnemyAlive(vector<CEnemy*>& EnemyExist);
	void generateflag(int flag, vector<vector<int>> Enemyflag, double x, double y);//生成一个波次的怪物，起始坐标为xy

	cocos2d::Scene* _currentScene;
	vector<vector<int>> _enemyWaves;
	unsigned int _currentWave;
	unsigned int _currentEnemyIndex;
	double _startX, _startY;
	GenerateEnemy(cocos2d::Scene* scene, const vector<vector<int>>& waves, double startX, double startY)
		: _currentScene(scene), _enemyWaves(waves), _currentWave(0),
		_currentEnemyIndex(0), _startX(startX), _startY(startY){}
	void startGenerating()
	{
		this->schedule([this](float) {
			if (_currentWave < _enemyWaves.size())
			{
				if (_currentEnemyIndex < _enemyWaves[_currentWave].size())
				{
					generateOneEnemy(EnemyExist, _enemyWaves[_currentWave][_currentEnemyIndex], _startX, _startY);
					++_currentEnemyIndex;
				}
				else
				{
					++_currentWave;
					_currentEnemyIndex = 0;
				}
			}
		}, 0.5f, "generateEnemy_key");
	}
};
#endif