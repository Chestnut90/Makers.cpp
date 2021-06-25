#include "pch.h"
#include "../../Include/Properties/StaticProperty.h"

//@ constructor
Makers::Properties::StaticProperty::StaticProperty(
	std::string _name,
	Items::ItemBase& _owner_item,
	Computables::IComputable& _data_object,
	bool _is_optional) : 
	PropertyBase(_name, _owner_item, _data_object, _is_optional)
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

