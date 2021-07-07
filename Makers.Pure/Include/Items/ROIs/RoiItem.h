#pragma once
#ifndef _ROI_ITEM_H_
#define _ROI_ITEM_H_

#include "../ItemBase.h"

namespace Makers
{
	namespace Items
	{
		// TODO : enum or other


		namespace ROIs
		{
			// TODO : define it
			class __declspec(dllexport) RoiItem :
				public ItemBase
			{

				//@ input property 
			public:

				//@ static property names
			public:

				//@ static property name (first)
				//@ roi left
				const std::string kStaticRoiLeft = "static_roi_left";

				//@ static property name (second)
				//@ roi top
				const std::string kStaticRoiTop = "static_roi_top";

				//@ static property name (third)
				//@ roi right
				const std::string kStaticRoiRight = "static_roi_right";

				//@ static property name (fourth)
				//@ roi bottom
				const std::string kStaticRoiBottom = "static_roi_bottom";

				//@ output property names
			public:

				//@ output property name (first)
				//@ output roi
				const std::string kOutputRoi = "output_roi";

			public:
				RoiItem();
				~RoiItem();

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

#endif // !_ROI_ITEM_H_

