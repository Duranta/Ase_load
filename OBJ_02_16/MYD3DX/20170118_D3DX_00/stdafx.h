// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hWnd;

#define SAFE_DELETE(p) { if (p) delete (p); }
#define SAFE_RELEASE(p) { if (p) (p)->Release(); }
#define SAFE_ADDREF(p) { if(p) (p)->AddRef(); }

#define SINGLETON(class_name) \
private:\
	class_name();\
	~class_name();\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SYNTHESIZE(varType, varName, funName) \
private:\
	varType varName;\
public:\
	inline varType Get##funName() const { return varName; }\
	inline void Set##funName(varType var) { varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName) \
private:\
	varType varName;\
public:\
	inline varType& Get##funName() { return varName; }\
	inline void Set##funName(varType& var) { varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName) \
private:\
	varType varName;\
public:\
	inline varType Get##funName() const { return varName; }\
	inline void Set##funName(varType var)\
	{\
		if(varName != var)\
		{\
			SAFE_ADDREF(var);\
			varName = var;\
		}\
	}

#include <vector>
#include <assert.h>
#include <time.h>
#include <map>
#include <list>
#include <set>

using namespace std;

#include "cDeviceManager.h"
#include "cTextureManager.h"
#include "cTimeManager.h"
#include "cObject.h"
#include "cObjectManager.h"
#include "cGameObject.h"
#include "cAutoReleasePool.h"
#include "D3DUtility.h"

using namespace D3DUTILITY;