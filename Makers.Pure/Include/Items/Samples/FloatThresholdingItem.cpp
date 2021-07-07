#include "pch.h"

#include "FloatThresholdingItem.h"

// props
#include "../../Properties/PropertyGroup.h"
#include "../../Properties/InputProperty.h"
#include "../../Properties/OutputProperty.h"
#include "../../Properties/StaticProperty.h"

#include "../../Computables/ImagePointer.h"
#include "../../Computables/Image.h"
#include "../../Computables/Real.h"

//@ constructor
Makers::Items::Samples::FloatThreshodingItem::FloatThreshodingItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{
	buffer_counts_ = 1;
}

Makers::Items::Samples::FloatThreshodingItem::~FloatThreshodingItem()
{
}

std::string Makers::Items::Samples::FloatThreshodingItem::SetItemName()
{
	return "FloatThreshodingItem";
}

Makers::Items::Compute Makers::Items::Samples::FloatThreshodingItem::SetCompute()
{
	return [] (ItemBase* _reference,
		Properties::PropertyGroup* _inputs, 
		Properties::PropertyGroup* _statics, 
		Properties::PropertyGroup* _outputs) -> bool
	{
		// cast to this
		auto here = dynamic_cast<FloatThreshodingItem*>(_reference);

		// get inputs
		auto image_property = dynamic_cast<Properties::InputProperty*>(
			_inputs->QueryPropertyName(here->kInputFloatImage));
		auto com_image = dynamic_cast<Computables::Image<float>*>(
			image_property->connected_property()->data_object());
		auto image = com_image->image();
		auto height = com_image->height();
		auto width = com_image->width();

		// get statics
		auto com_treshold = dynamic_cast<Makers::Computables::Real<float>*>(
			_statics->QueryPropertyName(here->kStaticFloatThreshold)->data_object());
		auto threshold = com_treshold->value();

		auto com_is_reversed = dynamic_cast<Makers::Computables::Real<bool>*>(
			_statics->QueryPropertyName(here->kStaticIsReversed)->data_object());
		auto is_reversed = com_is_reversed->value();

		// generate image
		// send to output
		auto com_binary_image = dynamic_cast<Makers::Computables::ImagePointer<unsigned char>*>(
			_outputs->QueryPropertyName(here->kOutputThresholdedImage)->data_object());
		com_binary_image->set_point(here->buffers_.at(0), width, height);
		auto binary = com_binary_image->image();
		
		// thresholding
		unsigned char upper = is_reversed ? 0 : 255;
		unsigned char lower = is_reversed ? 255 : 0;
		long zero_count = 0;
		for (long y = 0; y < height; y++)
		{
			long row = y * width;
			for (long x = 0; x < width; x++)
			{
				long index = row + x;
				auto value = image[index] >= threshold ? upper : lower;
				if (value == 0) zero_count++;
				binary[index] = value;
			}
		}

		auto com_zero_count = dynamic_cast<Makers::Computables::Real<long>*>(
			_outputs->QueryPropertyName(here->kOutputZeroCount)->data_object());
		com_zero_count->set_value(zero_count);
		return true;
	};
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::FloatThreshodingItem::SetInputProperties()
{
	Makers::Properties::PropertyGroup* input_properties = new Makers::Properties::PropertyGroup();

	// input image property
	input_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::InputProperty(
			"input_float_image",
			this, 
			new Makers::Computables::Image<float>()));

	return input_properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::FloatThreshodingItem::SetStaticProperties()
{
	Makers::Properties::PropertyGroup* static_properties = new Makers::Properties::PropertyGroup();

	static_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_float_threshold",
			this,
			new Makers::Computables::Real<float>()));

	static_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_is_reversed",
			this,
			new Makers::Computables::Real<bool>()));

	return static_properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::FloatThreshodingItem::SetOutputProperties()
{
	Makers::Properties::PropertyGroup* output_properties = new Makers::Properties::PropertyGroup();

	output_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::OutputProperty(
			"output_thresholded_image",
			this,
			new Makers::Computables::ImagePointer<unsigned char>()));

	output_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::OutputProperty(
			"output_zero_count",
			this,
			new Makers::Computables::Real<long>()));

	return output_properties;
}
