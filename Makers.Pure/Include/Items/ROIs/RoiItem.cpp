#include "pch.h"
#include "RoiItem.h"

#include "../../Documents/Document.h"

#include "../../Properties/PropertyGroup.h"
#include "../../Properties/StaticProperty.h"
#include "../../Properties/OutputProperty.h"

#include "../../Computables/Real.h"
#include "../../Computables/ROI.h"

Makers::Items::ROIs::RoiItem::RoiItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{
	buffer_counts_ = 0;
}

Makers::Items::ROIs::RoiItem::~RoiItem()
{
}

std::string Makers::Items::ROIs::RoiItem::SetItemName()
{
	return "RoiItem";
}

Makers::Items::Compute Makers::Items::ROIs::RoiItem::SetCompute()
{
	return [](
		ItemBase* _reference,
		Properties::PropertyGroup* _inputs,
		Properties::PropertyGroup* _statics,
		Properties::PropertyGroup* _outputs) -> bool
	{
		// cast to this
		auto here = dynamic_cast<RoiItem*>(_reference);

		// get roi left
		auto com_left = dynamic_cast<Computables::Real<unsigned int>*>(
			_statics->QueryPropertyName(here->kStaticRoiLeft)->data_object());
		auto left = com_left->value();

		// get roi top
		auto com_top = dynamic_cast<Computables::Real<unsigned int>*>(
			_statics->QueryPropertyName(here->kStaticRoiTop)->data_object());
		auto top = com_top->value();

		// get roi right
		auto com_right = dynamic_cast<Computables::Real<unsigned int>*>(
			_statics->QueryPropertyName(here->kStaticRoiRight)->data_object());
		auto right = com_right->value();

		// get roi bottom
		auto com_bottom = dynamic_cast<Computables::Real<unsigned int>*>(
			_statics->QueryPropertyName(here->kStaticRoiBottom)->data_object());
		auto bottom = com_bottom->value();

		// set output
		auto com_roi = dynamic_cast<Computables::ROI*>(
			_outputs->QueryPropertyName(here->kOutputRoi)->data_object());
		com_roi->set_roi(left, top, right, bottom);
		
		return true;
	};
}

Makers::Properties::PropertyGroup * Makers::Items::ROIs::RoiItem::SetInputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();
	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::ROIs::RoiItem::SetStaticProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();

	// add static roi left
	// init with 0
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_roi_left",
			this,
			new Makers::Computables::Real<unsigned int>(0)));
	// add static roi top
	// init with 0
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_roi_top",
			this,
			new Makers::Computables::Real<unsigned int>(0)));
	// add static roi right
	// init with 0
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_roi_right",
			this,
			new Makers::Computables::Real<unsigned int>(0)));
	// add static roi bottom
	// init with 0
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_roi_bottom",
			this,
			new Makers::Computables::Real<unsigned int>(0)));

	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::ROIs::RoiItem::SetOutputProperties()
{
	auto output_properties = new Makers::Properties::PropertyGroup();

	output_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::OutputProperty(
			"output_roi",
			this,
			new Makers::Computables::ROI()));

	return output_properties;
}
