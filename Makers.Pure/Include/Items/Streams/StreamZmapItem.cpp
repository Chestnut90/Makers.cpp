#include "pch.h"
#include "StreamZmapItem.h"

#include "../../Documents/Document.h"

// props
#include "../../Properties/PropertyGroup.h"
#include "../../Properties/InputProperty.h"
#include "../../Properties/OutputProperty.h"
#include "../../Properties/StaticProperty.h"

#include "../../Computables/Image.h"
#include "../../Computables/Real.h"

#include "../../nxSurfs/Surf.h"

Makers::Items::Streams::StreamZmapItem::StreamZmapItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{
	buffer_counts_ = 0;
}

Makers::Items::Streams::StreamZmapItem::~StreamZmapItem()
{
}

std::string Makers::Items::Streams::StreamZmapItem::SetItemName()
{
	return "StreamZmapItem";
}

Makers::Items::Compute Makers::Items::Streams::StreamZmapItem::SetCompute()
{
	return [](ItemBase* reference,
		Properties::PropertyGroup* inputs,
		Properties::PropertyGroup* statics,
		Properties::PropertyGroup* outputs) -> bool
	{
		auto here = dynamic_cast<StreamZmapItem*>(reference);

		std::string error = "";
		auto document = here->document();
		if (document == nullptr)
		{
			error = "Error : owner document is nullptr.\n";
			throw std::exception(error.c_str());
		}

		auto zmap = document->surf().zmap();
		auto width = document->surf().width();
		auto height = document->surf().height();

		auto com_zmap_image = dynamic_cast<Makers::Computables::Image<float>*>(
			outputs->QueryPropertyName(here->kOutputZmap)->data_object());
		com_zmap_image->set_image(zmap, width, height);	// set buffer handle

		return true;
	};
}

Makers::Properties::PropertyGroup* Makers::Items::Streams::StreamZmapItem::SetInputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup(this);
	return properties;
}

Makers::Properties::PropertyGroup* Makers::Items::Streams::StreamZmapItem::SetStaticProperties()
{
	auto properties = new Makers::Properties::PropertyGroup(this);
	return properties;
}

Makers::Properties::PropertyGroup* Makers::Items::Streams::StreamZmapItem::SetOutputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup(this);

	properties->AddProperty("Zmap", new Makers::Computables::Image<float>(true), false, Properties::eOutputProperty);

	return properties;
}
