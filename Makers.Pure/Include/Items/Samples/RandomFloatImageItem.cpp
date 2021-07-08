#include "pch.h"

#include <time.h>

#include "RandomFloatImageItem.h"

// props
#include "../../Properties/PropertyGroup.h"
#include "../../Properties/InputProperty.h"
#include "../../Properties/OutputProperty.h"
#include "../../Properties/StaticProperty.h"

#include "../../Computables/Image.h"
#include "../../Computables/Real.h"

Makers::Items::Samples::RandomFloatImageItem::RandomFloatImageItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{

}

Makers::Items::Samples::RandomFloatImageItem::~RandomFloatImageItem()
{
}

std::string Makers::Items::Samples::RandomFloatImageItem::SetItemName()
{
	return "RandomFloatImageItem";
}

Makers::Items::Compute Makers::Items::Samples::RandomFloatImageItem::SetCompute()
{
	return [] (
		ItemBase* _reference,
		Properties::PropertyGroup* _inputs,
		Properties::PropertyGroup* _statics,
		Properties::PropertyGroup* _outputs) -> bool
	{
		// cast to this
		auto here = dynamic_cast<RandomFloatImageItem*>(_reference);

		// get inputs

		// get statics
		auto com_width = dynamic_cast<Makers::Computables::Real<long>*>
			(_statics->QueryPropertyName(here->kStaticImageWidth)->data_object());
		auto width = com_width->value();

		auto com_height = dynamic_cast<Makers::Computables::Real<long>*>
			(_statics->QueryPropertyName(here->kStaticImageHeight)->data_object());
		auto height = com_height->value();

		// generate image
		srand((unsigned int)time(NULL));	//seed
		
		float* image = new float[width * height];

		for (unsigned long y = 0; y < height; y++)
		{
			unsigned long row = y * width;
			for (unsigned long x = 0; x < width; x++)
			{
				image[row + x] = ((float)rand() / (float)RAND_MAX);
			}
		}

		// send to output
		auto com_random_image = dynamic_cast<Makers::Computables::Image<float>*>
			(_outputs->QueryPropertyName(here->kOutputFloatImage)->data_object());
		com_random_image->set_image(image, width, height);

		delete image;
		return true;
	};
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::RandomFloatImageItem::SetInputProperties()
{
	return new Makers::Properties::PropertyGroup();
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::RandomFloatImageItem::SetStaticProperties()
{
	Makers::Properties::PropertyGroup* static_properties = new Makers::Properties::PropertyGroup();

	static_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_image_width",
			this,
			new Makers::Computables::Real<long>()));

	static_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_image_height",
			this,
			new Makers::Computables::Real<long>()));

	return static_properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::RandomFloatImageItem::SetOutputProperties()
{
	Makers::Properties::PropertyGroup* output_properties = new Makers::Properties::PropertyGroup();

	output_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::OutputProperty(
			"output_float_image",
			this,
			new Makers::Computables::Image<float>()));

	return output_properties;
}

std::string Makers::Items::Samples::RandomFloatImageItem::ToString()
{
	auto result = ItemBase::ToString();

	return result;
}
