#include "pch.h"
#include "../../Include/Properties/OutputProperty.h"
#include "../../Include/Items/ItemBase.h"

//@ TODO : to be protected 
//@ constructor
Makers::Properties::OutputProperty::OutputProperty(
	std::string _name,
	Items::ItemBase* _owner_item,
	Computables::IComputable* _data_object,
	bool _is_optional) : 
	PropertyBase(_name, _owner_item, _data_object, _is_optional), 
	IRunAble()
{
}

//@ TODO : to be protected
//@ destructor
Makers::Properties::OutputProperty::~OutputProperty()
{
}

//@ TODO : log?
//@ Query value in owner item
bool Makers::Properties::OutputProperty::Run(
	Documents::Document * _document, 
	Items::ItemBase * _sender, 
	long long _timestamp)
{
	return owner_item()->Run(_document, _sender, _timestamp);
}

//@ to data -> overrided
std::map<std::string, std::string> Makers::Properties::OutputProperty::ToData()
{
	auto data = PropertyBase::ToData();

	// TODO : output property data

	return data;
}
