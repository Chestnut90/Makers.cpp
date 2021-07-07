#include "pch.h"
#include "OutputProperty.h"
#include "../Items/ItemBase.h"

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

//@ destructor
Makers::Properties::OutputProperty::~OutputProperty()
{
}

//@ Query value in owner item
bool Makers::Properties::OutputProperty::Run(
	Documents::Document * _document, 
	Items::ItemBase * _sender, 
	long long _timestamp)
{
	// TODO : log
	if (owner_item() == nullptr) { return false; }
	return owner_item()->Run(_document, _sender, _timestamp);
}

//@ to data
std::map<std::string, std::string> Makers::Properties::OutputProperty::ToData()
{
	auto data = PropertyBase::ToData();

	// TODO : output property data

	return data;
}
