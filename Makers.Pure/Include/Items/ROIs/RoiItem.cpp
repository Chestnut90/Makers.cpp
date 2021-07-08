#include "pch.h"
#include "ROIItem.h"

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
	return "ROIItem";
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
		auto com_left = dynamic_cast<Computables::Real<long>*>(
			_statics->QueryPropertyName(here->kStaticLeft)->data_object());
		auto left = com_left->value();

		// get roi top
		auto com_top = dynamic_cast<Computables::Real<long>*>(
			_statics->QueryPropertyName(here->kStaticTop)->data_object());
		auto top = com_top->value();

		// get roi right
		auto com_right = dynamic_cast<Computables::Real<long>*>(
			_statics->QueryPropertyName(here->kStaticRight)->data_object());
		auto right = com_right->value();

		// get roi bottom
		auto com_bottom = dynamic_cast<Computables::Real<long>*>(
			_statics->QueryPropertyName(here->kStaticBottom)->data_object());
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
	properties->AddProperty("Left", new Makers::Computables::Real<long>(0), false, Properties::eStaticProperty);
	properties->AddProperty("Right", new Makers::Computables::Real<long>(0), false, Properties::eStaticProperty);
	properties->AddProperty("Top", new Makers::Computables::Real<long>(0), false, Properties::eStaticProperty);
	properties->AddProperty("Bottom", new Makers::Computables::Real<long>(0), false, Properties::eStaticProperty);

	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::ROIs::RoiItem::SetOutputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();
	properties->AddProperty("Out_ROI", new Makers::Computables::ROI(), false, Properties::eOutputProperty);

	return properties;
}
