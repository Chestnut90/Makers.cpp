#pragma once
#ifndef _EDGE_DETECT_ITEM_H_
#define _EDGE_DETECT_ITEM_H_

#include "../ItemBase.h"

namespace Makers
{
	namespace Items
	{
		// TODO : enum or other


		namespace Numericals
		{
			// TODO : define it
			class __declspec(dllexport) EdgeDetectItem :
				public ItemBase
			{

				//@ input property 
			public:

				//@ input property name (first)
				//@ float image
				const std::string kInputFloatImage = "input_float_image";

				//@ input property name (second)
				//@ roi
				const std::string kInputRoi = "input_roi";

				//@ static property names
			public:

				//@ static property name (first)
				//@ noise filter type
				const std::string KNoiseFilterType = "static_noise_filter_type";

				//@ static property name (second)
				//@ filter size
				const std::string KStaticFilterSize = "static_filter_size";

				//@ output property names
			public:

				//@ output property name (first)
				//@ output filtered image
				const std::string kOutputFilteredImage = "output_filtered_image";

			public:
				EdgeDetectItem();
				~EdgeDetectItem();

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

#endif // !_EDGE_DETECT_ITEM_H_

