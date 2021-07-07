#include "pch.h"
#include "BlobItem.h"

#include "../../Documents/Document.h"

#include "../../Properties/PropertyGroup.h"
#include "../../Properties/InputProperty.h"
#include "../../Properties/StaticProperty.h"
#include "../../Properties/OutputProperty.h"

#include "../../Computables/Image.h"

Makers::Items::Numericals::BlobItem::BlobItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{
	buffer_counts_ = 1;
	throw std::exception("not implemented");
}

Makers::Items::Numericals::BlobItem::~BlobItem()
{
}

std::string Makers::Items::Numericals::BlobItem::SetItemName()
{
	return "BlobItem";
}

Makers::Items::Compute Makers::Items::Numericals::BlobItem::SetCompute()
{
	return [](
		ItemBase* _reference,
		Properties::PropertyGroup* _inputs,
		Properties::PropertyGroup* _statics,
		Properties::PropertyGroup* _outputs) -> bool
	{
		auto here = dynamic_cast<BlobItem*>(_reference);

		return true;
	};
}

Makers::Properties::PropertyGroup * Makers::Items::Numericals::BlobItem::SetInputProperties()
{
	// non - inputs
	return new Makers::Properties::PropertyGroup();
}

Makers::Properties::PropertyGroup * Makers::Items::Numericals::BlobItem::SetStaticProperties()
{
	// non - statics
	return new Makers::Properties::PropertyGroup();
}

Makers::Properties::PropertyGroup * Makers::Items::Numericals::BlobItem::SetOutputProperties()
{
	auto output_properties = new Makers::Properties::PropertyGroup();

	output_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::OutputProperty(
			"output_stream_image",
			this,
			new Makers::Computables::Image<float>()));

	return output_properties;
}
