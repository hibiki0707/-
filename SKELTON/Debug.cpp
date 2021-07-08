#include<DxLib.h>
#include "Debug.h"
#include"Singleton.h"

int test = 0;

void Debug::Output(const char* str){
	OutputDebugStringA(str);
	test++;
	++test2;
}
