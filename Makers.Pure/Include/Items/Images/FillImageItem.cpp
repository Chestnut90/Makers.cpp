#include "pch.h"
#include "FillImageItem.h"

#include "../../Documents/Document.h"

#include "../../Properties/PropertyGroup.h"
#include "../../Properties/InputProperty.h"
#include "../../Properties/StaticProperty.h"
#include "../../Properties/OutputProperty.h"

#include "../../Computables/Image.h"
#include "../../Computables/Real.h"
#include "../../Computables/ROI.h"
#include "../../Computables/ImagePointer.h"

//nexensor
#include "C:\Program Files\Nexensor\NEXENSORSDK\include\Algorithm\ImageProcessing.h"

Makers::Items::Images::FillImageItem::FillImageItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{
	buffer_counts_ = 1;
}

Makers::Items::Images::FillImageItem::~FillImageItem()
{
}

std::string Makers::Items::Images::FillImageItem::SetItemName()
{
	return "FillImageItem";
}

Makers::Items::Compute Makers::Items::Images::FillImageItem::SetCompute()
{
	return [](
		ItemBase* _reference,
		Properties::PropertyGroup* _inputs,
		Properties::PropertyGroup* _statics,
		Properties::PropertyGroup* _outputs) -> bool
	{
		// cast to this
		auto here = dynamic_cast<FillImageItem*>(_reference);

		// get float source image from input
		auto image_property = dynamic_cast<Properties::InputProperty*>(
			_inputs->QueryPropertyName(here->kInputFloatImage));
		if (image_property->connected_property() == nullptr) { return false; }

		auto com_image = dynamic_cast<Computables::Image<float>*>(
			image_property->connected_property()->data_object());
		auto image = com_image->image();
		auto height = com_image->height();
		auto width = com_image->width();

		// get roi from input
		auto roi_property = dynamic_cast<Properties::InputProperty*>(
			_inputs->QueryPropertyName(here->kInputRoi));

		CRect roi(0, 0, width, height);
		if (roi_property->connected_property() != nullptr)
		{
			auto com_roi = dynamic_cast<Computables::ROI*>(
				roi_property->connected_property()->data_object());
			roi = CRect(com_roi->left(), com_roi->top(), com_roi->right(), com_roi->bottom());
		}
		
		// get filled value from static
		auto com_fill = dynamic_cast<Makers::Computables::Real<float>*>(
			_statics->QueryPropertyName(here->kStaticFillValue)->data_object());
		auto filled = com_fill->value();

		// send to output
		auto com_filled_image = dynamic_cast<Makers::Computables::ImagePointer<float>*>(
			_outputs->QueryPropertyName(here->kOutputFloatImage)->data_object());
		com_filled_image->set_buffer(here->buffers_.at(0), width, height);
		auto filled_image = com_filled_image->image();

		return retStatus::success == NXSIP::ImageFill(roi, width, height, filled, filled_image);
	};
}

Makers::Properties::PropertyGroup * Makers::Items::Images::FillImageItem::SetInputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();

	// add input float image
	properties->AddProperty("Input_Image", new Makers::Computables::Image<float>(), false, Properties::eInputProperty);
	// add input roi
	properties->AddProperty("ROI", new Makers::Computables::ROI(), false, Properties::eInputProperty);

	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Images::FillImageItem::SetStaticProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();

	// add static filled value, init with 0.f
	properties->AddProperty("Filled_Value", new Makers::Computables::Real<float>(0.f), false, Properties::eStaticProperty);

	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Images::FillImageItem::SetOutputProperties()
{
	auto output_properties = new Makers::Properties::PropertyGroup();

	// add output filled image
	output_properties->AddProperty("Filled_Image", new Makers::Computables::ImagePointer<float>(), false, Properties::eOutputProperty);

	return output_properties;
}
