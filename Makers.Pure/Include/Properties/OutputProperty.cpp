#include "pch.h"
#include "OutputProperty.h"
#include "../Items/ItemBase.h"

//@ constructor
Makers::Properties::OutputProperty::OutputProperty(
	std::string name,
	Items::ItemBase* owner_item,
	Computables::IComputable* data_object,
	bool is_optional) : 
	PropertyBase(name, owner_item, data_object, is_optional), 
	IQueryAbleProperty()
{
}

//@ destructor
Makers::Properties::OutputProperty::~OutputProperty()
{
}

//@ Query value with async
bool Makers::Properties::OutputProperty::QueryProperty_Async(Documents::Document* document, Items::ItemBase* sender, long long timestamp)
{
	// TODO : log
	if (owner_item() == nullptr)
	{
		std::string error = "exception error in output property base.\n";
		error += name() + "(" + id() + ")" + " no owner item\n";
		throw std::exception(error.c_str());
	}
	return owner_item()->Run(document, sender, timestamp);
}

//@ Query value
bool Makers::Properties::OutputProperty::QueryProperty(Documents::Document* document, Items::ItemBase* sender, long long timestamp)
{
	// TODO : log
	if (owner_item() == nullptr)
	{
		std::string error = "exception error in output property base.\n";
		error += name() + "(" + id() + ")" + " no owner item\n";
		throw std::exception(error.c_str());
	}
	return owner_item()->Run(document, sender, timestamp);
}

//@ to data
std::map<std::string, std::string> Makers::Properties::OutputProperty::ToData()
{
	auto data = PropertyBase::ToData();

	// TODO : output property data

	return data;
}
