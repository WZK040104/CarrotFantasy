#include "Enemy_kind.h"

Enemy0::Enemy0() {
	initial(0, 1500, 0.3f, 100, 0, 0);
}
Enemy0::~Enemy0() {}

Enemy1::Enemy1() {
	initial(1,30, 0.5, 10, 0, 0);
}
Enemy1::~Enemy1() {}

Enemy2::Enemy2() {
	initial(2,50, 0.5, 15, 0, 0);
}
Enemy2::~Enemy2() {}


Enemy3::Enemy3() {
	initial(3,100, 1, 15, 0, 0);
}
Enemy3::~Enemy3() {}

Enemy4::Enemy4() {
	initial(4,200, 0.75f, 30, 0, 0);
}
Enemy4::~Enemy4() {}