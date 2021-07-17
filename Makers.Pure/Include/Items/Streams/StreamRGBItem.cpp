#include "pch.h"
#include "StreamRGBItem.h"

#include "../../Documents/Document.h"

// props
#include "../../Properties/PropertyGroup.h"
#include "../../Properties/InputProperty.h"
#include "../../Properties/OutputProperty.h"
#include "../../Properties/StaticProperty.h"

#include "../../Computables/Image.h"
#include "../../Computables/Real.h"

#include "../../nxSurfs/Surf.h"

Makers::Items::Streams::StreamRGBItem::StreamRGBItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{
	buffer_counts_ = 0;
}

Makers::Items::Streams::StreamRGBItem::~StreamRGBItem()
{
}

std::string Makers::Items::Streams::StreamRGBItem::SetItemName()
{
	return "StreamRGBItem";
}

Makers::Items::Compute Makers::Items::Streams::StreamRGBItem::SetCompute()
{
	return [](ItemBase* reference,
		Properties::PropertyGroup* inputs,
		Properties::PropertyGroup* statics,
		Properties::PropertyGroup* outputs) -> bool
	{
		auto here = dynamic_cast<StreamRGBItem*>(reference);

		auto document = here->document();
		if (document == nullptr)
		{
			std::string error = "Error : owner document is nullptr.\n";
			throw std::exception(error.c_str());
		}
		
		// width and height
		auto width = document->surf().width();
		auto height = document->surf().height();

		// set red
		auto red = document->surf().red();
		auto com_red = dynamic_cast<Makers::Computables::Image<byte>*>(
			outputs->QueryPropertyName(here->kOutputRed)->data_object());
		com_red->set_image(red, width, height);

		// set green
		auto green = document->surf().green();
		auto com_green = dynamic_cast<Makers::Computables::Image<byte>*>(
			outputs->QueryPropertyName(here->kOutputGreen)->data_object());
		com_green->set_image(green, width, height);

		// set blue
		auto blue = document->surf().blue();
		auto com_blue = dynamic_cast<Makers::Computables::Image<byte>*>(
			outputs->QueryPropertyName(here->kOutputBlue)->data_object());
		com_blue->set_image(blue, width, height);

		return true;
	};
}

Makers::Properties::PropertyGroup* Makers::Items::Streams::StreamRGBItem::SetInputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup(this);
	return properties;
}

Makers::Properties::PropertyGroup* Makers::Items::Streams::StreamRGBItem::SetStaticProperties()
{
	auto properties = new Makers::Properties::PropertyGroup(this);
	return properties;
}

Makers::Properties::PropertyGroup* Makers::Items::Streams::StreamRGBItem::SetOutputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup(this);

	properties->AddProperty("Red", new Makers::Computables::Image<byte>(true), false, Properties::eOutputProperty);
	properties->AddProperty("Green", new Makers::Computables::Image<byte>(true), false, Properties::eOutputProperty);
	properties->AddProperty("Blue", new Makers::Computables::Image<byte>(true), false, Properties::eOutputProperty);

	return properties;
}
