#include "pch.h"
#include "InvertedImageItem.h"

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

Makers::Items::Images::InvertedImageItem::InvertedImageItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{
	buffer_counts_ = 1;
}

Makers::Items::Images::InvertedImageItem::~InvertedImageItem()
{
}

std::string Makers::Items::Images::InvertedImageItem::SetItemName()
{
	return "InvertedImageItem";
}

Makers::Items::Compute Makers::Items::Images::InvertedImageItem::SetCompute()
{
	return [](
		ItemBase* _reference,
		Properties::PropertyGroup* _inputs,
		Properties::PropertyGroup* _statics,
		Properties::PropertyGroup* _outputs) -> bool
	{
		// cast to this
		auto here = dynamic_cast<InvertedImageItem*>(_reference);

		// get float source image from input
		auto image_property = dynamic_cast<Properties::InputProperty*>(
			_inputs->QueryPropertyName(here->kInputFloatImage));
		if (image_property->connected_property() == nullptr) { return false; }

		auto com_image = dynamic_cast<Computables::Image<float>*>(
			image_property->connected_property()->data_object());
		auto image = com_image->image();
		auto height = com_image->height();
		auto width = com_image->width();

		// send to output
		auto com_inverted_image = dynamic_cast<Makers::Computables::ImagePointer<float>*>(
			_outputs->QueryPropertyName(here->KOutputInvertedImage)->data_object());
		com_inverted_image->set_point(here->buffers_.at(0), width, height);
		auto inverted_image = com_inverted_image->image();

		float max_value(0.f);
		NXSIP::GetMax(image, width, height, max_value);
		NXSIP::ImageFill(width, height, max_value, inverted_image);
		return retStatus::success == NXSIP::Subtract(image, width, height, inverted_image);
	};
}

Makers::Properties::PropertyGroup * Makers::Items::Images::InvertedImageItem::SetInputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();

	// add input float image
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::InputProperty(
			"input_float_image",
			this,
			new Makers::Computables::Image<float>()));

	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Images::InvertedImageItem::SetStaticProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();
	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Images::InvertedImageItem::SetOutputProperties()
{
	auto output_properties = new Makers::Properties::PropertyGroup();

	// output filled image
	output_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::OutputProperty(
			"output_inverted_image",
			this,
			new Makers::Computables::ImagePointer<float>()));

	return output_properties;
}
