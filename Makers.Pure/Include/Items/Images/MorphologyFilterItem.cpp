#include "pch.h"
#include "MorphologyFilterItem.h"

#include "../../Documents/Document.h"

#include "../../Properties/PropertyGroup.h"
#include "../../Properties/InputProperty.h"
#include "../../Properties/StaticProperty.h"
#include "../../Properties/OutputProperty.h"

#include "../../Computables/Image.h"
#include "../../Computables/ImagePointer.h"
#include "../../Computables/Real.h"
#include "../../Computables/ROI.h"

//nexensor
#include "C:\Program Files\Nexensor\NEXENSORSDK\include\Algorithm\ImageProcessing.h"

Makers::Items::Images::MorphologyFilterItem::MorphologyFilterItem() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{
	buffer_counts_ = 1;
}

Makers::Items::Images::MorphologyFilterItem::~MorphologyFilterItem()
{
}

std::string Makers::Items::Images::MorphologyFilterItem::SetItemName()
{
	return "MorphologyFilterItem";
}

Makers::Items::Compute Makers::Items::Images::MorphologyFilterItem::SetCompute()
{
	return [](
		ItemBase* _reference,
		Properties::PropertyGroup* _inputs,
		Properties::PropertyGroup* _statics,
		Properties::PropertyGroup* _outputs) -> bool
	{
		// cast to this
		auto here = dynamic_cast<MorphologyFilterItem*>(_reference);

		// get float source image from input
		auto image_property = dynamic_cast<Properties::InputProperty*>(
			_inputs->QueryPropertyName(here->kInputFloatImage));
		if (image_property->connected_property() == nullptr) { return false; }

		auto com_image = dynamic_cast<Computables::Image<float>*>(
			image_property->connected_property()->data_object());
		auto image = com_image->image();
		auto height = com_image->height();
		auto width = com_image->width();

		// get roi from input
		auto roi_property = dynamic_cast<Properties::InputProperty*>(
			_inputs->QueryPropertyName(here->kInputRoi));
		CRect roi(0, 0, width, height);
		if (roi_property->connected_property() != nullptr)
		{
			auto com_roi = dynamic_cast<Computables::ROI*>(
				roi_property->connected_property()->data_object());
			roi = CRect(com_roi->left(), com_roi->top(), com_roi->right(), com_roi->bottom());
		}

		// get morphology type from static
		auto com_morphology_type = dynamic_cast<Makers::Computables::Real<unsigned int>*>(
			_statics->QueryPropertyName(here->KStaticMorphologyType)->data_object());
		auto morphology_type = com_morphology_type->value();

		// get filter size value from static
		auto com_filter_size = dynamic_cast<Makers::Computables::Real<unsigned int>*>(
			_statics->QueryPropertyName(here->KStaticFilterSize)->data_object());
		auto filter_size = com_filter_size->value();

		// send to output
		auto com_filtered_image = dynamic_cast<Makers::Computables::ImagePointer<float>*>(
			_outputs->QueryPropertyName(here->kOutputFilteredImage)->data_object());
		com_filtered_image->set_point(here->buffers_.at(0), width, height);
		auto filtered_image = com_filtered_image->image();

		retStatus res = retStatus::errorAacAdtsSyncWordErr;	// default
		switch (morphology_type)
		{
		case 0: //dilate
			res = NXSIP::Dilate(image, width, height, roi, filter_size, filter_size, true, true, filtered_image);
			break;
		case 1: // erode
			res = NXSIP::Erode(image, width, height, roi, filter_size, filter_size, true, true, filtered_image);
			break;
		case 2: // opening
			res = NXSIP::Opening(image, width, height, roi, filter_size, filter_size, true, true, filtered_image);
			break;
		case 3: // closing
			res = NXSIP::Closing(image, width, height, roi, filter_size, filter_size, true, true, filtered_image);
			break;
		case 4: // top hat
			res = NXSIP::TopHat(image, width, height, roi, filter_size, filter_size, true, true, filtered_image);
			break;
		case 5: // black hat
			res = NXSIP::BlackHat(image, width, height, roi, filter_size, filter_size, true, true, filtered_image);
			break;
		}
		return res == retStatus::success;
	};
}

Makers::Properties::PropertyGroup * Makers::Items::Images::MorphologyFilterItem::SetInputProperties()
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

Makers::Properties::PropertyGroup * Makers::Items::Images::MorphologyFilterItem::SetStaticProperties()
{
	auto properties = new Makers::Properties::PropertyGroup();

	// add static morphology type
	// init with 0 -> dilate
	properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::StaticProperty(
			"static_morphology_type",
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

Makers::Properties::PropertyGroup * Makers::Items::Images::MorphologyFilterItem::SetOutputProperties()
{
	auto output_properties = new Makers::Properties::PropertyGroup();

	output_properties->AddProperty(
		(Makers::Properties::PropertyBase*) new Makers::Properties::OutputProperty(
			"output_filtered_image",
			this,
			new Makers::Computables::ImagePointer<float>()));

	return output_properties;
}
