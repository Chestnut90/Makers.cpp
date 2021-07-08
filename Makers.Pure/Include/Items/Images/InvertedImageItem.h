#pragma once
#ifndef _INVERTED_IMAGE_ITEM_H_
#define _INVERTED_IMAGE_ITEM_H_

#include "../ItemBase.h"

namespace Makers
{
	namespace Items
	{
		namespace Images
		{
			// TODO : roi
			//@ class inverted image item
			class __declspec(dllexport) InvertedImageItem :
				public ItemBase
			{
				//@ input property names
			public:

				//@ input property name (first)
				//@ float image
				const std::string kInputFloatImage = "Input_Image";

				//@ input property name (second)
				//@ roi
				//const std::string kInputROI = "ROI";

				//@ static property names
			public:

				//@ output property names
			public:

				//@ output property name (first)
				//@ output inverted image
				const std::string KOutputInvertedImage = "Inverted_Image";

			public:
				InvertedImageItem();
				~InvertedImageItem();

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

#endif // !_INVERTED_IMAGE_ITEM_H_

