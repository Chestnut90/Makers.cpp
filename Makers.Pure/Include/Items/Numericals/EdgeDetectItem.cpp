#include "pch.h"
#include "EdgeDetectItem.h"

#include "../../Documents/Document.h"

#include "../../Properties/PropertyGroup.h"
#include "../../Properties/InputProperty.h"
#include "../../Properties/StaticProperty.h"
#include "../../Properties/OutputProperty.h"

#include "../../Computables/Image.h"
#include "../../Computables/ImagePointer.h"
#include "../../Computables/Real.h"
#include "../../Computables/ROI.h"



Makers::Items::Numericals::EdgeDetectItem::EdgeDetectItem() :
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

Makers::Items::Numericals::EdgeDetectItem::~EdgeDetectItem()
{
}

std::string Makers::Items::Numericals::EdgeDetectItem::SetItemName()
{
	return "EdgeDetectItem";
}

Makers::Items::Compute Makers::Items::Numericals::EdgeDetectItem::SetCompute()
{
	return [](
		ItemBase* _reference,
		Properties::PropertyGroup* _inputs,
		Properties::PropertyGroup* _statics,
		Properties::PropertyGroup* _outputs) -> bool
	{
		// cast to this
		auto here = dynamic_cast<EdgeDetectItem*>(_reference);
		return false;
	};
}

Makers::Properties::PropertyGroup * Makers::Items::Numericals::EdgeDetectItem::SetInputProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();

	// add input float image
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::InputProperty(
			"input_float_image",
			this,
			new Makers::Computables::Image<float>()));

	// add input roi
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::InputProperty(
			"input_roi",
			this,
			new Makers::Computables::ROI(), true));

	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Numericals::EdgeDetectItem::SetStaticProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();

	// add static morphology type
	// init with 0 -> median
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_noise_filter_type",
			this,
			new Makers::Computables::Real<unsigned int>(0)));


	// add static filter size
	// init with 3
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_filter_size",
			this,
			new Makers::Computables::Real<unsigned int>(3)));

	return properties;
}

Makers::Properties::PropertyGroup * Makers::Items::Numericals::EdgeDetectItem::SetOutputProperties()
{
	auto output_properties = new Makers::Properties::PropertyGroup();

	output_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::OutputProperty(
			"output_filtered_image",
			this,
			new Makers::Computables::ImagePointer<float>()));

	return output_properties;
}
