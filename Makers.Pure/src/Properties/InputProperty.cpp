#include "pch.h"
#include "../../Include/Properties/InputProperty.h"
#include "../../Include/Computables/IComputable.h"
#include "../../Include/Items/ItemBase.h"

//@ get connected property
Makers::Properties::PropertyBase& Makers::Properties::InputProperty::connected_property() const
{
	return *connected_property_;
}

//@ set connected property
void Makers::Properties::InputProperty::set_connected_property(PropertyBase & _connected_property)
{
	connected_property_ = &_connected_property;
}

//@ constructor
Makers::Properties::InputProperty::InputProperty(
	std::string _name, 
	Items::ItemBase& _owner_item, 
	Computables::IComputable& _data_object, 
	bool _is_optional) :
	PropertyBase(_name, _owner_item, _data_object, _is_optional),
	IRunAble()
{
	connected_property_ = nullptr;
}

//@ destructor
Makers::Properties::InputProperty::~InputProperty()
{
}

//@ query value
bool Makers::Properties::InputProperty::Run(
	Documents::Document * _document, 
	Items::ItemBase * _sender, 
	long long _timestamp)
{
	if (connected_property_ == nullptr) return false;

	auto runable_property = dynamic_cast<IRunAble*>(connected_property_);
	if (runable_property == nullptr) return false;

	return runable_property->Run(_document, _sender, _timestamp);
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
