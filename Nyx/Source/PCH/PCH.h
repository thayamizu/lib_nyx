/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_PCH_H_ 
#define NYX_CORE_INCLUDED_PCH_H_

///// define
//#define WIN32_LEAN_AND_MEAN
//#define WINVER           0x600
//#define _WIN32_WINNT     0x600

//Windows
#ifdef _WIN32
//header
#include <windows.h>
#include <mmsystem.h>
//#include <winsock2.h>
#pragma warning(disable:4996)
#pragma warning(disable:4800)

//Windows Library
#pragma comment( lib, "msimg32.lib" )
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "comdlg32.lib" )
#pragma comment( lib, "advapi32.lib" )
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "shell32.lib" )
#endif

//インライン関数の深さ
#pragma inline_depth ( 16 )
#pragma inline_recursion ( on )

//warning抑制
#pragma warning ( disable : 4201 )
#pragma warning ( disable : 4995 )

//STL 
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <deque>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <memory>

//Common
#include "Utility/Common.h"
#include "Utility/Type.h"
#include "Utility/Limits.h"
#include "Utility/Math.h"
#include "Utility/Random.h"

//DirectX
#include "Graphics/DirectXDefinition.h"

#endif