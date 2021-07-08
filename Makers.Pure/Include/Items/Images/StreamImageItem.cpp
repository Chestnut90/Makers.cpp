#include "pch.h"
#include "StreamImageItem.h"

#include "../../Documents/Document.h"

#include "../../Properties/PropertyGroup.h"
#include "../../Properties/StaticProperty.h"
#include "../../Properties/OutputProperty.h"

#include "../../Computables/ImagePointer.h"
#include "../../Computables/Image.h"

Makers::Items::Images::StreamImageItem::StreamImageItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{
}

Makers::Items::Images::StreamImageItem::~StreamImageItem()
{
}

std::string Makers::Items::Images::StreamImageItem::SetItemName()
{
	return "StreamImageItem";
}

Makers::Items::Compute Makers::Items::Images::StreamImageItem::SetCompute()
{
	return [](
		ItemBase* _reference,
		Properties::PropertyGroup* _inputs,
		Properties::PropertyGroup* _statics,
		Properties::PropertyGroup* _outputs) -> bool
	{
		auto here = dynamic_cast<StreamImageItem*>(_reference);

		auto stream_image = here->document()->stream_image();
		auto image = stream_image->image();
		auto width = stream_image->width();
		auto height = stream_image->height();
		if (stream_image == nullptr) return false;

		auto com_stream_image = dynamic_cast<Makers::Computables::ImagePointer<float>*>(
			_outputs->QueryPropertyName(here->kOutputStreaImage)->data_object());
		com_stream_image->set_buffer(image, width, height);
		return true;
	};
}

Makers::Properties::PropertyGroup * Makers::Items::Images::StreamImageItem::SetInputProperties()
{
	// non - inputs
	return new Makers::Properties::PropertyGroup();
}

Makers::Properties::PropertyGroup * Makers::Items::Images::StreamImageItem::SetStaticProperties()
{
	// non - statics
	return new Makers::Properties::PropertyGroup();
}

Makers::Properties::PropertyGroup * Makers::Items::Images::StreamImageItem::SetOutputProperties()
{
	auto output_properties = new Makers::Properties::PropertyGroup();

	output_properties->AddProperty("Stream_Image", new Makers::Computables::ImagePointer<float>(), false, Properties::eOutputProperty);

	return output_properties;
}
