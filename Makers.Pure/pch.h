// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"
//#include <mfapi.h>
//#include <atltypes.h>
//#include <afxwin.h>

#pragma region Nexensor SDK Dependencies

#pragma region ALGORITHMS
#include "C:\Program Files\Nexensor\NEXENSORSDK\include\Algorithm\ImageProcessing.h"
#include "C:\Program Files\Nexensor\NEXENSORSDK\include\Algorithm\ImageProcessingHelper.h"
#include "C:\Program Files\Nexensor\NEXENSORSDK\include\Algorithm\Geometry.h"
#include "C:\Program Files\Nexensor\NEXENSORSDK\include\Algorithm\ImageCondition.h"
#include "C:\Program Files\Nexensor\NEXENSORSDK\include\Algorithm\BlobInfo.h"
//#include "C:\Program Files\Nexensor\NEXENSORSDK\include\Algorithm\EdgeDetect.h"
//#include "C:\Program Files\Nexensor\NEXENSORSDK\include\Algorithm\MultiProcessing.h"

#pragma comment(lib, "C:/Program Files/Nexensor/NEXENSORSDK/lib/NexensorSDK.Library.Algorithm.lib")


#pragma region BASEMETHODS
#include "C:\Program Files\Nexensor\NEXENSORSDK\include\BaseMethod\ZmapFormat.h"
//#include "C:\Program Files\Nexensor\NEXENSORSDK\include\BaseMethod\IniReadWriter.h"
//#include "C:\Program Files\Nexensor\NEXENSORSDK\include\BaseMethod\GraphControl.h"
//#include "C:\Program Files\Nexensor\NEXENSORSDK\include\BaseMethod\ShareMemory.h"
//#include "C:\Program Files\Nexensor\NEXENSORSDK\include\BaseMethod\ImageInterface.h"
//#include "C:\Program Files\Nexensor\NEXENSORSDK\include\BaseMethod\CrashDump.h"
//#include "C:\Program Files\Nexensor\NEXENSORSDK\include\BaseMethod\FileOperation.h"
//#include "C:\Program Files\Nexensor\NEXENSORSDK\include\BaseMethod\FileVersion.h"
//#include "C:\Program Files\Nexensor\NEXENSORSDK\include\BaseMethod\TimeCheck.h"

#pragma comment(lib, "C:/Program Files/Nexensor/NEXENSORSDK/lib/NexensorSDK.Library.BaseMethod.lib")

#pragma endregion



#endif //PCH_H
