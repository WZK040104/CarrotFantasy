#include "Tower_kind.h"

int tower0_upgrade_coins[MAXlevel+1] = { 20,40,60,100,0 };						//һ����������ǮΪtower0_upgrade_coins[1]		��ͨ��̨
int tower0_attack[MAXlevel + 1] = { 0,5,15,25,40 }; 						//һ�����˺�Ϊtower0_attack[1]
double tower0_timebetween_attack[MAXlevel + 1] = { 100,1,0.95,0.9,0.85 };	//һ���Ĺ������Ϊtower0_timebetween_attack[1]��
double tower0_attack_range[MAXlevel + 1] = { 0, 2.8, 2.9, 3, 3.1 };			//һ���Ĺ�����ΧΪtower0_attack_range[1]

int tower1_upgrade_coins[MAXlevel+1] = { 30,60,90,150,0 };						//һ����������ǮΪtower1_upgrade_coins[1]		�˺�ƫ�ߣ����ٽϿ죬��������϶�
int tower1_attack[MAXlevel + 1] = { 0,10,20,30,45 };						//һ�����˺�Ϊtower1_attack[1]
double tower1_timebetween_attack[MAXlevel + 1] = { 100,0.85 ,0.75, 0.7,0.65 };//һ���Ĺ������Ϊtower1_timebetween_attack[1]��
double tower1_attack_range[MAXlevel + 1] = { 0, 2, 2.1, 2.2 , 2.4 };		//һ���Ĺ�����ΧΪtower1_attack_range[1]

int tower2_upgrade_coins[MAXlevel+1] = { 15,35,55,80,0 };						//һ����������ǮΪtower2_upgrade_coins[1]		�˺��ϵͣ�����Զ�����ṩ����Ч������ûд��
int tower2_attack[MAXlevel + 1] = { 0,3,9,15,25 };							//һ�����˺�Ϊtower2_attack[1]
double tower2_timebetween_attack[MAXlevel + 1] = { 100,1,0.95,0.9,0.85 };	//һ���Ĺ������Ϊtower2_timebetween_attack[1]��
double tower2_attack_range[MAXlevel + 1] = { 0, 3.1, 3.3, 3.5 ,3.6 };		//һ���Ĺ�����ΧΪtower2_attack_range[1]

int tower3_upgrade_coins[MAXlevel+1] = { 30,60,90,150 ,0};						//һ����������ǮΪtower3_upgrade_coins[1]		�˺��ϵͣ�����Ⱥ���˺�
int tower3_attack[MAXlevel + 1] = { 0,3,6,12,18 };							//һ�����˺�Ϊtower3_attack[1]
double tower3_timebetween_attack[MAXlevel + 1] = { 100,1.5,1.3,1.1 ,1 };	//һ���Ĺ������Ϊtower3_timebetween_attack[1]��
double tower3_attack_range[MAXlevel + 1] = { 0, 2.8, 2.9, 3, 3.1 };			//һ���Ĺ�����ΧΪtower3_attack_range[1]

Tower0::Tower0(){
	initial(1, tower0_upgrade_coins, tower0_attack, tower0_timebetween_attack, tower0_attack_range, 0);
}
Tower0::~Tower0() {}

Tower1::Tower1() {
	initial(1, tower0_upgrade_coins, tower0_attack, tower0_timebetween_attack, tower0_attack_range, 0);
}
Tower1::~Tower1() {}

Tower2::Tower2() {
	initial(1, tower0_upgrade_coins, tower0_attack, tower0_timebetween_attack, tower0_attack_range, 0);
}
Tower2::~Tower2() {}

Tower3::Tower3() {
	initial(1, tower0_upgrade_coins, tower0_attack, tower0_timebetween_attack, tower0_attack_range, 0);
}
Tower3::~Tower3() {}