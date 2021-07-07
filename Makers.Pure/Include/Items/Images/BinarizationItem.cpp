#include "pch.h"
#include "BinarizationItem.h"

#include "../../Documents/Document.h"

#include "../../Properties/PropertyGroup.h"
#include "../../Properties/InputProperty.h"
#include "../../Properties/StaticProperty.h"
#include "../../Properties/OutputProperty.h"

#include "../../Computables/Image.h"
#include "../../Computables/Real.h"
#include "../../Computables/ROI.h"
#include "../../Computables/ImagePointer.h"

// nexensor
#include "C:\Program Files\Nexensor\NEXENSORSDK\include\Algorithm\ImageProcessing.h"

Makers::Items::Images::BinarizationItem::BinarizationItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{

	buffer_counts_ = 1;
}

Makers::Items::Images::BinarizationItem::~BinarizationItem()
{
}

std::string Makers::Items::Images::BinarizationItem::SetItemName()
{
	return "BinarizationItem";
}

Makers::Items::Compute Makers::Items::Images::BinarizationItem::SetCompute()
{
	return [](
		ItemBase* _reference,
		Properties::PropertyGroup* _inputs,
		Properties::PropertyGroup* _statics,
		Properties::PropertyGroup* _outputs) -> bool
	{
		// cast to this
		auto here = dynamic_cast<BinarizationItem*>(_reference);

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
		
		// get threshold value from static
		auto com_treshold = dynamic_cast<Makers::Computables::Real<float>*>(
			_statics->QueryPropertyName(here->kStaticThresholdValue)->data_object());
		auto threshold = com_treshold->value();

		// get is reversed value from static
		auto com_is_reversed = dynamic_cast<Makers::Computables::Real<bool>*>(
			_statics->QueryPropertyName(here->kStaticIsReversed)->data_object());
		auto is_reversed = com_is_reversed->value();
		
		// send to output
		auto com_binary_image = dynamic_cast<Makers::Computables::ImagePointer<unsigned char>*>(
			_outputs->QueryPropertyName(here->kOutputBinarizedImage)->data_object());
		com_binary_image->set_point(here->buffers_.at(0), width, height);
		auto binary = com_binary_image->image();
		
		return retStatus::success == NXSIP::Binarization(image, width, height, roi, threshold, is_reversed, binary);
	};
}

Makers::Properties::PropertyGroup * Makers::Items::Images::BinarizationItem::SetInputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();

	// add input float image
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::InputProperty(
			"input_float_image",
			this,
			new Makers::Computables::Image<float>()));

	// add input roi
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::InputProperty(
			"input_roi",
			this,
			new Makers::Computables::ROI(), true));

	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Images::BinarizationItem::SetStaticProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();

	// add static threshold value
	// init with 0.f
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_threshold_value",
			this,
			new Makers::Computables::Real<float>(0.f)));

	// add static is reversed
	// init with false
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_is_reversed",
			this,
			new Makers::Computables::Real<bool>(false)));

	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Images::BinarizationItem::SetOutputProperties()
{
	auto output_properties = new Makers::Properties::PropertyGroup();

	// add output binarized image
	output_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::OutputProperty(
			"output_binarized_image",
			this,
			new Makers::Computables::ImagePointer<unsigned char>()));

	return output_properties;
}
