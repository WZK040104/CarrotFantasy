#include "Tower_kind.h"

int tower0_upgrade_coins[MAXlevel + 1] = { 20,40,60,100,0 };				//һ����������ǮΪtower0_upgrade_coins[1]		��ͨ��̨
int tower0_attack[MAXlevel + 1] = { 0,5,15,25,35 }; 						//һ�����˺�Ϊtower0_attack[1]
double tower0_attack_range[MAXlevel + 1] = { 0, 70, 75, 80, 85 };			//һ���Ĺ�����ΧΪtower0_attack_range[1]

int tower1_upgrade_coins[MAXlevel + 1] = { 30,60,90,150,0 };				//һ����������ǮΪtower1_upgrade_coins[1]		�˺�ƫ�ߣ���������϶�
int tower1_attack[MAXlevel + 1] = { 0,10,20,30,45 };						//һ�����˺�Ϊtower1_attack[1]
double tower1_attack_range[MAXlevel + 1] = { 0, 50, 55 , 60 ,65};			//һ���Ĺ�����ΧΪtower1_attack_range[1]

int tower2_upgrade_coins[MAXlevel + 1] = { 15,35,55,80,0 };					//һ����������ǮΪtower2_upgrade_coins[1]		�˺��ϵͣ�����Զ�����ṩ����Ч������ûд��
int tower2_attack[MAXlevel + 1] = { 0,3,8,15,25 };							//һ�����˺�Ϊtower2_attack[1]
double tower2_attack_range[MAXlevel + 1] = { 0, 80,90,100,110 };			//һ���Ĺ�����ΧΪtower2_attack_range[1]

int tower3_upgrade_coins[MAXlevel + 1] = { 30,60,90,150 ,0 };				//һ����������ǮΪtower3_upgrade_coins[1]		�˺��ϵͣ�����Ⱥ���˺�
int tower3_attack[MAXlevel + 1] = { 0,2,6,12,18 };							//һ�����˺�Ϊtower3_attack[1]
double tower3_attack_range[MAXlevel + 1] = { 0, 70, 75, 80, 85 };			//һ���Ĺ�����ΧΪtower3_attack_range[1]

Tower0::Tower0() {
	initial(0,1, tower0_upgrade_coins, tower0_attack, tower0_attack_range, 0);
}
Tower0::~Tower0() {}

Tower1::Tower1() {
	initial(1,1, tower1_upgrade_coins, tower1_attack, tower1_attack_range, 0);
}
Tower1::~Tower1() {}

Tower2::Tower2() {
	initial(2,1, tower2_upgrade_coins, tower2_attack, tower2_attack_range, 0);
}
Tower2::~Tower2() {}

Tower3::Tower3() {
	initial(3,1, tower3_upgrade_coins, tower3_attack, tower3_attack_range, 1);
}
Tower3::~Tower3() {}