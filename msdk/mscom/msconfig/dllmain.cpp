// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "msconfig.h"
USE_DEFAULT_DLL_MAIN;
BEGIN_CLIDMAP
	CLIDMAPENTRY_BEGIN
		CLIDMAPENTRY(CLSID_MsConfig,CMsConfig)
	CLIDMAPENTRY_END
END_CLIDMAP_AND_EXPORTFUN;
