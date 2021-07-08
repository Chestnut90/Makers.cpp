#pragma once
#ifndef _STREAM_IMAGE_ITEM_H_
#define _STREAM_IMAGE_ITEM_H_

#include "../ItemBase.h"

namespace Makers
{
	namespace Items
	{
		namespace Images
		{
			//@ class stream image item
			class __declspec(dllexport) StreamImageItem :
				public ItemBase
			{
			//@ property names
			public:

				//@ output property name
				//@ stream image
				const std::string kOutputStreaImage = "Stream_Image";

			public:
				StreamImageItem();
				~StreamImageItem();

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

#endif // !_STREAM_IMAGE_ITEM_H_
