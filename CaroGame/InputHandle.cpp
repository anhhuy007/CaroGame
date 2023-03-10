#include "InputHandle.h"
using namespace std;

// this function is used for get the input from keyboard
// there are 6 main types of input: UP, DOWN, LEFT, RIGHT, ENTER, ESC
wstring InputHandle::Get() {
	wchar_t ch = _getwch();
	
	if (ch == 0 || ch == 224) {
		wchar_t temp = _getwch();
		switch (temp) {
		case 59:
			return L"F1";
		case 60:
			return L"F2";
		case 61:
			return L"F3";
		case 62:
			return L"F4";
		case 63:
			return L"F5";
		case 64:
			return L"F6";
		case 65:
			return L"F7";
		case 66:
			return L"F8";
		case 67:
			return L"F9";
		case 68:
			return L"F10";
		case 71:
			return L"HOME";
		case 72:
			return L"UP";
		case 80:
			return L"DOWN";
		case 75:
			return L"LEFT";
		case 77:
			return L"RIGHT";
		}
	}

	switch (ch) {
	case 13:
		return L"ENTER";
	case 27:
		return L"ESC";
	}
	
	if (ch > 127 || ch < 8) {
		return L"";
	}

	return wstring(1, ch);
}