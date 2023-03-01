#include "InputHandle.h"
using namespace std;

wstring InputHandle::Get() {
	wchar_t ch = _getwch();
	
	if (ch == 0 || ch == 224) {
		wchar_t temp = _getwch();
		switch (temp) {
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

	if (ch == L'\x1b') {
		return L"ESC";
	}

	if (ch == '\r') {
		return L"ENTER";
	}

	if (ch > 127 || ch < 8) {
		return L"";
	}

	return wstring(1, ch);
}