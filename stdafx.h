// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <regex>
#include <algorithm>

// TODO: reference additional headers your program requires here
#if defined(_MSC_VER) && !defined(_DEBUG)
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <nana/filesystem/filesystem_ext.hpp>
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/toolbar.hpp>

#include "labelbox.h"
#include "stdext.h"
