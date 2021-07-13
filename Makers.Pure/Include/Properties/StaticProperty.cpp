#include "pch.h"
#include "StaticProperty.h"

//@ constructor
Makers::Properties::StaticProperty::StaticProperty(
	std::string name,
	Items::ItemBase* owner_item,
	Computables::IComputable* data_object,
	bool is_optional) : 
	PropertyBase(name, owner_item, data_object, is_optional)
{
}

//@ destructor
Makers::Properties::StaticProperty::~StaticProperty()
{
}

//@ to data
std::map<std::string, std::string> Makers::Properties::StaticProperty::ToData()
{
	auto data = PropertyBase::ToData();
	
	// TODO : static property data

	return data;
}

