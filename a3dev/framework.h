// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <strsafe.h>

#include <atlconv.h>


#include <vector>
#include <iostream>  
#include <string>  
#include <fstream>  
#include <sstream> 



#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "ImGuiFileDialog.h"
#include <d3d9.h>
#include <d3dx9.h>


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "Winmm.lib")


#include "draw.h"
#include "triangle.h"
#include "rect.h"
#include "cube.h"
#include "mesh.h"
#include "chara.h"




#include "dx9settings.h"

VOID TRACE(LPCTSTR pszFormat, ...);


