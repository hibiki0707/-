#include <DxLib.h>
#include "Singleton.h"

void Singleton::Out(){
	wchar_t outstr[32];
	wsprintf(outstr, L"Singleton Count=%d\n", counter);
	OutputDebugString(outstr);
	++counter;
}
