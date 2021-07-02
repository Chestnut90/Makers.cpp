#include "pch.h"
#include "../../../Include/Items/Samples/SampleItem0.h"

// props
#include "../../../Include/Properties/PropertyGroup.h"
#include "../../../Include/Properties/InputProperty.h"
#include "../../../Include/Properties/OutputProperty.h"
#include "../../../Include/Properties/StaticProperty.h"

#include "../../../Include/Computables/Image.h"
#include "../../../Include/Computables/Real.h"

Makers::Items::Samples::SampleItem0::SampleItem0() :
	ItemBase(
		SetItemName(),
		SetCompute(),
		SetInputProperties(),
		SetStaticProperties(),
		SetOutputProperties())
{

}

Makers::Items::Samples::SampleItem0::~SampleItem0()
{
}

std::string Makers::Items::Samples::SampleItem0::SetItemName()
{
	return "SampleItem0";
}

Makers::Items::Compute Makers::Items::Samples::SampleItem0::SetCompute()
{
	return Compute();
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::SampleItem0::SetInputProperties()
{
	/*auto inputs =  new Makers::Properties::PropertyGroup();
	auto property = new Makers::Properties::InputProperty("null", nullptr, new Makers::Computables::Real<int>());
	inputs->AddProperty(property);
*/
	return nullptr;
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::SampleItem0::SetStaticProperties()
{
	return nullptr;
	//new Makers::Properties::PropertyGroup();
}

Makers::Properties::PropertyGroup * Makers::Items::Samples::SampleItem0::SetOutputProperties()
{
	return nullptr;
	//new Makers::Properties::PropertyGroup();
}
