#include "Tower_kind.h"

int tower0_upgrade_coins[MAXlevel+1] = { 20,40,60,100,0 };						//一级升二级的钱为tower0_upgrade_coins[1]		普通炮台
int tower0_attack[MAXlevel + 1] = { 0,5,15,25,40 }; 						//一级的伤害为tower0_attack[1]
double tower0_timebetween_attack[MAXlevel + 1] = { 100,1,0.95,0.9,0.85 };	//一级的攻击间隔为tower0_timebetween_attack[1]秒
double tower0_attack_range[MAXlevel + 1] = { 0, 2.8, 2.9, 3, 3.1 };			//一级的攻击范围为tower0_attack_range[1]

int tower1_upgrade_coins[MAXlevel+1] = { 30,60,90,150,0 };						//一级升二级的钱为tower1_upgrade_coins[1]		伤害偏高，射速较快，攻击距离较短
int tower1_attack[MAXlevel + 1] = { 0,10,20,30,45 };						//一级的伤害为tower1_attack[1]
double tower1_timebetween_attack[MAXlevel + 1] = { 100,0.85 ,0.75, 0.7,0.65 };//一级的攻击间隔为tower1_timebetween_attack[1]秒
double tower1_attack_range[MAXlevel + 1] = { 0, 2, 2.1, 2.2 , 2.4 };		//一级的攻击范围为tower1_attack_range[1]

int tower2_upgrade_coins[MAXlevel+1] = { 15,35,55,80,0 };						//一级升二级的钱为tower2_upgrade_coins[1]		伤害较低，距离远但能提供减速效果（还没写）
int tower2_attack[MAXlevel + 1] = { 0,3,9,15,25 };							//一级的伤害为tower2_attack[1]
double tower2_timebetween_attack[MAXlevel + 1] = { 100,1,0.95,0.9,0.85 };	//一级的攻击间隔为tower2_timebetween_attack[1]秒
double tower2_attack_range[MAXlevel + 1] = { 0, 3.1, 3.3, 3.5 ,3.6 };		//一级的攻击范围为tower2_attack_range[1]

int tower3_upgrade_coins[MAXlevel+1] = { 30,60,90,150 ,0};						//一级升二级的钱为tower3_upgrade_coins[1]		伤害较低，但是群体伤害
int tower3_attack[MAXlevel + 1] = { 0,3,6,12,18 };							//一级的伤害为tower3_attack[1]
double tower3_timebetween_attack[MAXlevel + 1] = { 100,1.5,1.3,1.1 ,1 };	//一级的攻击间隔为tower3_timebetween_attack[1]秒
double tower3_attack_range[MAXlevel + 1] = { 0, 2.8, 2.9, 3, 3.1 };			//一级的攻击范围为tower3_attack_range[1]

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