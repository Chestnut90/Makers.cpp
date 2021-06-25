#pragma once
#ifndef _RANDOMFLOATIMAGEITEM_H_
#define _RANDOMFLOATIMAGEITEM_H_

#include "../ItemBase.h"
//#include "../ItemFactories/FactoryRegister.h"

namespace Makers
{
	namespace Items
	{
		namespace Samples
		{

			class __declspec(dllexport) RandomFloatImageItem :
				public ItemBase
			{
			//@ property names
			public:
				// no inputs

				//@ static property name (first)
				//@ image width (unsigned long)
				const std::string kStaticImageWidth = "static_image_width";
				//@ static property name (second)
				//@ image height (unsigned long)
				const std::string kStaticImageHeight = "static_image_height";
				//@ output property name
				//@ float image
				const std::string kOutputFloatImage = "output_float_image";

			public:
				RandomFloatImageItem();
				~RandomFloatImageItem();

			protected:

				std::string SetItemName() override;
				Compute SetCompute() override;
				Properties::PropertyGroup* SetInputProperties() override;
				Properties::PropertyGroup* SetStaticProperties() override;
				Properties::PropertyGroup* SetOutputProperties() override;

			public:
				std::string ToString() override;
			};


			// TODO : auto register
			//std::unique_ptr<FactoryRegister<RandomFloatImageItem>> _FloatThresholdingItem(new FactoryRegister<RandomFloatImageItem>("RandomFloatImageItem"));
			//FactoryRegister<RandomFloatImageItem> _RandomFloatImageItem("RandomFloatImageItem");
		}
	}
}

#endif // !_RANDOMFLOATIMAGEITEM_H_
