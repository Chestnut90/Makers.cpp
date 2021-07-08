#pragma once
#ifndef _ZMAP_ITEM_H_
#define _ZMAP_ITEM_H_

#include "../ItemBase.h"

namespace Makers
{
	namespace Items
	{
		namespace Images
		{
			//@ class stream image item
			class __declspec(dllexport) ZmapItem :
				public ItemBase
			{
			public:

				//@ static property name
				//@ float image
				const std::string kStaticZmap = "Zmap";

				//@ static property name
				//@ red
				const std::string kStaticRed = "Red";

				//@ static property name
				//@ green
				const std::string kStaticGreen = "Green";

				//@ static property name
				//@ blue
				const std::string kStaticBlue = "Blue";

			public:

				//@ output property name
				//@ zmap
				const std::string kOutputZmapImage = "Out_Zmap_Image";

				//@ output property name
				//@ red
				const std::string kOutputRedImage = "Out_Red_Image";

				//@ output property name
				//@ green
				const std::string kOutputGreenImage = "Out_Green_Image";

				//@ output property name
				//@ blue
				const std::string kOutputBlueImage = "Out_Blue_Image";

			public:
				ZmapItem();
				~ZmapItem();

			protected:

				std::string SetItemName() override;
				Compute SetCompute() override;
				Properties::PropertyGroup* SetInputProperties() override;
				Properties::PropertyGroup* SetStaticProperties() override;
				Properties::PropertyGroup* SetOutputProperties() override;
			};

			// TODO : auto register
			//std::unique_ptr<FactoryRegister<FloatThreshodingItem>> _FloatThresholdingItem(new FactoryRegister<FloatThreshodingItem>("FloatThresholdingItem"));
			//FactoryRegister<FloatThreshodingItem> _FloatThresholdingItem("FloatThresholdingItem");
		}

	}
}

#endif // !_ZMAP_ITEM_H_
