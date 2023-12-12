#pragma once

class CEnemy	//��������� ����
{
private:
	int enemy_HP;				//������������ֵ����
	int HP;						//��ǰ��������ֵ
	int velocity;				//�ƶ��ٶ�
	int add_coins;				//������֮�����ӵĽ��
	double enemy_position_x;	//����ĺ�����
	double enemy_position_y;	//�����������

public:
	//���캯��
	CEnemy();
	
	// ��������
	virtual ~CEnemy();
	//��ʼ�����������ֵ,�ٶȣ����
	void initial(int input_HP, int input_velocity, int input_coins, int x, int y); 
	//�Ƿ����
	bool alive(int& gold_coins); 

	double EnemyPositionX()const;
	double EnemyPositionY()const;

	void HP_calculate(int damage_per_time);
};
