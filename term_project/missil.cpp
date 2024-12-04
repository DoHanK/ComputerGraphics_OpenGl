#include "crushcheck.h"
#include "missil.h"


void MISSIL::update(){
	
	pos.x+=dir.x * missilspeed;
	pos.z+=dir.z * missilspeed;
	pos.y += dir.y * missilspeed;

}