#pragma once

#include <iostream>

#include "../Makers.Pure/Include/nxSurfs/Surf.h"
#include "C:\Program Files\Nexensor\NEXENSORSDK\include\BaseMethod\ZmapFormat.h"
#pragma comment(lib, "C:/Program Files/Nexensor/NEXENSORSDK/lib/NexensorSDK.Library.BaseMethod.lib")

namespace Test
{
	namespace Surf
	{
		static void Load_Surf()
		{
			auto surf = nXSDK::Surf::Open("E:\\Test\\SDK.NET\\sample.surf");
				
			std::cout << surf.width() << std::endl;
			std::cout << surf.height() << std::endl;

			surf.Save("E:\\Test\\SDK.NET\\sample2.surf");

		}


	}
}