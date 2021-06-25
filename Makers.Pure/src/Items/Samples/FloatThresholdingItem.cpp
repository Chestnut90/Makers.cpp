#include "pch.h"

#include "../../../Include/Items/Samples/FloatThresholdingItem.h"

// props
#include "../../../Include/Properties/PropertyGroup.h"
#include "../../../Include/Properties/InputProperty.h"
#include "../../../Include/Properties/OutputProperty.h"
#include "../../../Include/Properties/StaticProperty.h"

#include "../../../Include/Computables/Image.h"
#include "../../../Include/Computables/Real.h"

Makers::Items::Samples::FloatThreshodingItem::FloatThreshodingItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{

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
	return [] (ItemBase& _reference,
		Properties::PropertyGroup& _inputs, 
		Properties::PropertyGroup& _statics, 
		Properties::PropertyGroup& _outputs) -> bool
	{
		// cast to this
		auto here = dynamic_cast<FloatThreshodingItem*>(&_reference);

		// get inputs
		auto image_property = dynamic_cast<Properties::InputProperty*>(&_inputs[here->kInputFloatImage]);
		auto com_image = dynamic_cast<Computables::Image<float>*>(image_property->connected_property().data_object());
		auto image = com_image->image();
		auto height = com_image->height();
		auto width = com_image->width();

		// get statics
		auto com_treshold = dynamic_cast<Makers::Computables::Real<float>*>
			((_statics[here->kStaticFloatThreshold].data_object()));
		auto threshold = com_treshold->value();

		auto com_is_reversed = dynamic_cast<Makers::Computables::Real<bool>*>
			(_statics[here->kStaticIsReversed].data_object());
		auto is_reversed = com_is_reversed->value();

		// generate image
		unsigned char* binary = new unsigned char[width * height];

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

		// send to output
		auto com_binary_image = dynamic_cast<Makers::Computables::Image<unsigned char>*>
			(_outputs[here->kOutputThresholdedImage].data_object());
		com_binary_image->set_image(binary, width, height);

		auto com_zero_count = dynamic_cast<Makers::Computables::Real<long>*>
			(_outputs[here->kOutputZeroCount].data_object());
		com_zero_count->set_value(zero_count);
		return true;
	};
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::FloatThreshodingItem::SetInputProperties()
{
	Makers::Properties::PropertyGroup* input_properties = new Makers::Properties::PropertyGroup();

	// input image property
	input_properties->AddProperty(
		*(Makers::Properties::PropertyBase*) new Makers::Properties::InputProperty(
			"input_float_image",
			*this, 
			*new Makers::Computables::Image<float>()));

	return input_properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::FloatThreshodingItem::SetStaticProperties()
{
	Makers::Properties::PropertyGroup* static_properties = new Makers::Properties::PropertyGroup();

	static_properties->AddProperty(
		*(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_float_threshold",
			*this,
			*new Makers::Computables::Real<float>()));

	static_properties->AddProperty(
		*(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_is_reversed",
			*this,
			*new Makers::Computables::Real<bool>()));

	return static_properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::FloatThreshodingItem::SetOutputProperties()
{
	Makers::Properties::PropertyGroup* output_properties = new Makers::Properties::PropertyGroup();

	output_properties->AddProperty(
		*(Makers::Properties::PropertyBase*) new Makers::Properties::OutputProperty(
			"output_thresholded_image",
			*this,
			*new Makers::Computables::Image<unsigned char>()));

	output_properties->AddProperty(
		*(Makers::Properties::PropertyBase*) new Makers::Properties::OutputProperty(
			"output_zero_count",
			*this,
			*new Makers::Computables::Real<long>()));

	return output_properties;
}
