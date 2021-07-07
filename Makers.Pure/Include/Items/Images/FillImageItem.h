#pragma once
#ifndef _FILL_IMAGE_ITEM_H_
#define _FILL_IMAGE_ITEM_H_

#include "../ItemBase.h"

namespace Makers
{
	namespace Items
	{
		namespace Images
		{
			// TODO : define it
			class __declspec(dllexport) FillImageItem :
				public ItemBase
			{
				//@ input property names
			public:

				//@ input property name (first)
				//@ float image
				const std::string kInputFloatImage = "input_float_image";

				//@ input property name (second)
				//@ roi
				const std::string kInputRoi = "input_roi";

				//@ static property names
			public:

				//@ static property name (second)
				//@ fill value
				const std::string kStaticFillValue = "static_fill_value";

				//@ output property names
			public:

				//@ output property name (first)
				//@ output filled image
				const std::string kOutputFloatImage = "output_filled_image";

			public:
				FillImageItem();
				~FillImageItem();

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

#endif // !_FILL_IMAGE_ITEM_H_

