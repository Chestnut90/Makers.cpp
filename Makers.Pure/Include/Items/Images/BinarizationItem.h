#pragma once
#ifndef _BINARIZATION_ITEM_H_
#define _BINARIZATION_ITEM_H_

#include "../ItemBase.h"

namespace Makers
{
	namespace Items
	{
		namespace Images
		{
			class __declspec(dllexport) BinarizationItem:
				public ItemBase
			{
				//@ input property names
			public:

				//@ input property name (first)
				//@ float image
				const std::string kInputFloatImage = "Input_Image";

				//@ input property name (second)
				//@ roi
				const std::string kInputRoi = "ROI";

				//@ static property names
			public:
				
				//@ static property name (second)
				//@ threshold value
				const std::string kStaticThresholdValue = "Threshold_Value";

				//@ static property name (third)
				//@ is reseverd
				const std::string kStaticIsReversed = "Is_Reversed";

				//@ output property names
			public:

				//@ output property name (first)
				//@ binarized image
				const std::string kOutputBinarizedImage = "Binarized_Image";

			public:
				//@ constructor
				BinarizationItem();
				//@ destructor
				~BinarizationItem();

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

#endif // !_BINARIZATION_ITEM_H_

