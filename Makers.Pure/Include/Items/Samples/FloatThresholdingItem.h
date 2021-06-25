#pragma once
#ifndef _FLOATTHRESHODINGITEM_H_
#define _FLOATTHRESHODINGITEM_H_

#include "../ItemBase.h"
//#include "../ItemFactories/FactoryRegister.h"

namespace Makers
{
	namespace Items
	{
		namespace Samples
		{

			class __declspec(dllexport) FloatThreshodingItem :
				public ItemBase
			{
			//@ property names
			public:

				//@ input property name (fisrt)
				//@ float image
				const std::string kInputFloatImage = "input_float_image";
				//@ static property name (first)
				//@ threshold value (float)
				const std::string kStaticFloatThreshold = "static_float_threshold";
				//@ static property name (second)
				//@ is reversed threshold
				const std::string kStaticIsReversed = "static_is_reversed";
				//@ output property name (first)
				//@ thresholded image (unsigned char)
				const std::string kOutputThresholdedImage = "output_thresholded_image";
				//@ output property name (second)
				//@ number of zero in binary image
				const std::string kOutputZeroCount = "output_zero_count";

			public:
				FloatThreshodingItem();
				~FloatThreshodingItem();

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

#endif // !_FLOATTHRESHODINGITEM_H_
