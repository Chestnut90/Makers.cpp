#include "pch.h"
#include "ZmapItem.h"

#include "../../Documents/Document.h"

#include "../../Properties/PropertyGroup.h"
#include "../../Properties/StaticProperty.h"
#include "../../Properties/OutputProperty.h"

#include "../../Computables/Image.h"

Makers::Items::Images::ZmapItem::ZmapItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{
}

Makers::Items::Images::ZmapItem::~ZmapItem()
{
}

std::string Makers::Items::Images::ZmapItem::SetItemName()
{
	return "ZmapItem";
}

Makers::Items::Compute Makers::Items::Images::ZmapItem::SetCompute()
{
	return [](
		ItemBase* _reference,
		Properties::PropertyGroup* _inputs,
		Properties::PropertyGroup* _statics,
		Properties::PropertyGroup* _outputs) -> bool
	{
		auto here = dynamic_cast<ZmapItem*>(_reference);

		// read zmap
		auto com_zmap = dynamic_cast<Makers::Computables::Image<float>*>(
			_statics->QueryPropertyName(here->kStaticZmap)->data_object());
		auto zmap = com_zmap->image();
		auto width = com_zmap->width();
		auto height = com_zmap->height();

		if (zmap == nullptr) return false;	// TODO : propagate exception

		// read red
		auto com_red = dynamic_cast<Makers::Computables::Image<unsigned char>*>(
			_statics->QueryPropertyName(here->kStaticRed)->data_object());
		auto red = com_red->image();

		// read green
		auto com_green = dynamic_cast<Makers::Computables::Image<unsigned char>*>(
			_statics->QueryPropertyName(here->kStaticGreen)->data_object());
		auto green = com_green->image();

		// read blue
		auto com_blue = dynamic_cast<Makers::Computables::Image<unsigned char>*>(
			_statics->QueryPropertyName(here->kStaticBlue)->data_object());
		auto blue = com_blue->image();

		// set to output
		// zmap
		auto com_output_zmap = dynamic_cast<Makers::Computables::Image<float>*>(
			_outputs->QueryPropertyName(here->kOutputZmapImage)->data_object());
		com_output_zmap->set_image(zmap, width, height);
		// red
		auto com_output_red = dynamic_cast<Makers::Computables::Image<unsigned char>*>(
			_outputs->QueryPropertyName(here->kOutputRedImage)->data_object());
		com_output_red->set_image(red, width, height);
		// green
		auto com_output_green = dynamic_cast<Makers::Computables::Image<unsigned char>*>(
			_outputs->QueryPropertyName(here->kOutputGreenImage)->data_object());
		com_output_green->set_image(green, width, height);
		// blue
		auto com_output_blue = dynamic_cast<Makers::Computables::Image<unsigned char>*>(
			_outputs->QueryPropertyName(here->kOutputBlueImage)->data_object());
		com_output_blue->set_image(blue, width, height);

		return true;
	};
}

Makers::Properties::PropertyGroup * Makers::Items::Images::ZmapItem::SetInputProperties()
{
	// non - inputs
	return new Makers::Properties::PropertyGroup(this);
}

Makers::Properties::PropertyGroup * Makers::Items::Images::ZmapItem::SetStaticProperties()
{
	auto properties = new Makers::Properties::PropertyGroup(this);
	// add static zmap
	properties->AddProperty("Zmap", new Makers::Computables::Image<float>(), false, Properties::eStaticProperty);
	// add static red
	properties->AddProperty("Red", new Makers::Computables::Image<unsigned char>(), false, Properties::eStaticProperty);
	// add static green
	properties->AddProperty("Green", new Makers::Computables::Image<unsigned char>(), false, Properties::eStaticProperty);
	// add static blue
	properties->AddProperty("Blue", new Makers::Computables::Image<unsigned char>(), false, Properties::eStaticProperty);

	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Images::ZmapItem::SetOutputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup(this);
	// add output zmap
	properties->AddProperty("Out_Zmap_Image", new Makers::Computables::Image<float>(), false, Properties::eOutputProperty);
	// add output red
	properties->AddProperty("Out_Red_Image", new Makers::Computables::Image<unsigned char>(), false, Properties::eOutputProperty);
	// add output green
	properties->AddProperty("Out_Green_Image", new Makers::Computables::Image<unsigned char>(), false, Properties::eOutputProperty);
	// add output blue
	properties->AddProperty("Out_Blue_Image", new Makers::Computables::Image<unsigned char>(), false, Properties::eOutputProperty);

	return properties;
}
