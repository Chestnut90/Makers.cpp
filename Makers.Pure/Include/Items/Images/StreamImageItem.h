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

			class __declspec(dllexport) StreamImageItem :
				public ItemBase
			{
			//@ property names
			public:

				//@ static property name (first)
				//@ image width
				const std::string kStaticImageWidth = "static_image_width";
				//@ static property name (second)
				//@ image height)
				const std::string kStaticImageHeight= "static_image_height";
				//@ output property name (first)
				//@ number of zero in binary image
				const std::string kOutputStreaImage = "output_stream_image";

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
