#include "pch.h"
#include "StreamGrayItem.h"

#include "../../Documents/Document.h"

// props
#include "../../Properties/PropertyGroup.h"
#include "../../Properties/InputProperty.h"
#include "../../Properties/OutputProperty.h"
#include "../../Properties/StaticProperty.h"

#include "../../Computables/Image.h"
#include "../../Computables/Real.h"

#include "../../nxSurfs/Surf.h"

Makers::Items::Streams::StreamGrayItem::StreamGrayItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{
	buffer_counts_ = 0;
}

Makers::Items::Streams::StreamGrayItem::~StreamGrayItem()
{
}

std::string Makers::Items::Streams::StreamGrayItem::SetItemName()
{
	return "StreamGrayItem";
}

Makers::Items::Compute Makers::Items::Streams::StreamGrayItem::SetCompute()
{
	return [](ItemBase* reference,
		Properties::PropertyGroup* inputs,
		Properties::PropertyGroup* statics,
		Properties::PropertyGroup* outputs) -> bool
	{
		auto here = dynamic_cast<StreamGrayItem*>(reference);

		std::string error = "";
		auto document = here->document();
		if (document == nullptr)
		{
			error = "Error : owner document is nullptr.\n";
			throw std::exception(error.c_str());
		}

		auto gray = document->surf().gray();
		auto width = document->surf().width();
		auto height = document->surf().height();

		auto com_gray_image = dynamic_cast<Makers::Computables::Image<byte>*>(
			outputs->QueryPropertyName(here->kOutputGrayImage)->data_object());
		com_gray_image->set_image(gray, width, height);
		
		return true;
	};
}

Makers::Properties::PropertyGroup* Makers::Items::Streams::StreamGrayItem::SetInputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup(this);
	return properties;
}

Makers::Properties::PropertyGroup* Makers::Items::Streams::StreamGrayItem::SetStaticProperties()
{
	auto properties = new Makers::Properties::PropertyGroup(this);
	return properties;
}

Makers::Properties::PropertyGroup* Makers::Items::Streams::StreamGrayItem::SetOutputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup(this);

	properties->AddProperty("Gray", new Makers::Computables::Image<byte>(true), false, Properties::eOutputProperty);

	return properties;
}
