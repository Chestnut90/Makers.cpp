#include "pch.h"
#include "InputProperty.h"
#include "../Computables/IComputable.h"
#include "../Items/ItemBase.h"

//@ get connected property
Makers::Properties::PropertyBase* Makers::Properties::InputProperty::connected_property() const
{
	return connected_property_;
}

//@ set connected property
void Makers::Properties::InputProperty::set_connected_property(PropertyBase* connected_property)
{
	connected_property_ = connected_property;
}

//@ constructor
Makers::Properties::InputProperty::InputProperty(
	std::string name, 
	Items::ItemBase* owner_item, 
	Computables::IComputable* data_object, 
	bool is_optional) :
	PropertyBase(name, owner_item, data_object, is_optional),
	IQueryAbleProperty()
{
	connected_property_ = nullptr;
}

//@ destructor
Makers::Properties::InputProperty::~InputProperty()
{
	//@ TODO : unique or shared pointer
	//delete connected_property_; // not delete connected property
}

//@ query value with async
bool Makers::Properties::InputProperty::QueryProperty_Async(Documents::Document* document, Items::ItemBase* sender, long long timestamp)
{
	std::string error = "exception error input property.\n";
	error += name() + "(" + id() + ")\n";

	// TODO : log
	if (connected_property_ == nullptr)
	{
		error += "no connected property.\n";
		throw std::exception(error.c_str());
	}

	auto queryable_property = dynamic_cast<IQueryAbleProperty*>(connected_property_);
	if (queryable_property == nullptr)
	{
		error += "critical error occured no cast to IRunAble object. please to ask manager.";
		throw std::exception(error.c_str());
	}

	return queryable_property->QueryProperty(document, sender, timestamp);
}

//@ query value 
bool Makers::Properties::InputProperty::QueryProperty(Documents::Document* document, Items::ItemBase* sender, long long timestamp)
{
	std::string error = "exception error input property.\n";
	error += name() + "(" + id() + ")\n";

	// TODO : log
	if (connected_property_ == nullptr)
	{
		error += "no connected property.\n";
		throw std::exception(error.c_str());
	}

	auto runable_property = dynamic_cast<IRunAble*>(connected_property_);
	if (runable_property == nullptr)
	{
		error += "critical error occured no cast to IRunAble object. please to ask manager.";
		throw std::exception(error.c_str());
	}

	return runable_property->Run(document, sender, timestamp);
}

//@ to data -> overrided
std::map<std::string, std::string> Makers::Properties::InputProperty::ToData()
{
	auto data = PropertyBase::ToData();

	// connected info
	data["ConnectedItemID"] = connected_property_ == nullptr ? "" : connected_property_->owner_item()->id();
	data["ConnectedPropertyID"] = connected_property_ == nullptr ? "" : connected_property_->id();

	return data;
}
