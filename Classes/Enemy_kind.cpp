#include "Enemy_kind.h"

Enemy0::Enemy0() {
	initial(0,1000, 8, 100, 0, 0);//ÔİÊ±ÏÈĞ´Îª0,0
}
Enemy0::~Enemy0() {}

Enemy1::Enemy1() {
	initial(1,30, 10, 10, 0, 0);
}
Enemy1::~Enemy1() {}

Enemy2::Enemy2() {
	initial(2,50, 10, 15, 0, 0);
}
Enemy2::~Enemy2() {}

Enemy3::Enemy3() {
	initial(3,30, 25, 15, 0, 0);
}
Enemy3::~Enemy3() {}

Enemy4::Enemy4() {
	initial(4,100, 15, 30, 0, 0);
}
Enemy4::~Enemy4() {}