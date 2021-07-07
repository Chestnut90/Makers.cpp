#include "pch.h"

#include <algorithm>

#include "PropertyGroup.h"

#include "PropertyBase.h"
#include "InputProperty.h"
#include "StaticProperty.h"
#include "OutputProperty.h"

namespace Properties = Makers::Properties;

//@ get properties count
int Makers::Properties::PropertyGroup::Count()
{
	return properties_.size();
}

//@ get owner item
Makers::Items::ItemBase * Makers::Properties::PropertyGroup::owner_item() const
{
	return owner_item_;
}

//@ constructor
Makers::Properties::PropertyGroup::PropertyGroup()
{
	owner_item_ = nullptr;
}

//@ destructor
Makers::Properties::PropertyGroup::~PropertyGroup()
{
	// not delete onwer item
	//delete owner_item_;

	Clear();
}

//@ operator
Makers::Properties::PropertyBase* Makers::Properties::PropertyGroup::operator[](const std::string _name)
{
	return QueryPropertyName(_name);
}

//@ add property
void  Makers::Properties::PropertyGroup::AddProperty(PropertyBase* _property)
{
	// no same id and name
	auto property = QueryPropertyID(_property->id());
	if (property != nullptr)
	{
		throw std::exception("find same named property.");
	}

	properties_[_property->name()] = _property;
}

//@ TODO : 
//@ add property
Properties::PropertyBase* Makers::Properties::PropertyGroup::AddProperty(
	std::string _name,
	Computables::IComputable * _computable,
	bool _is_optional,
	PropertyType _property_type)
{
	throw std::exception("not implemented");

	PropertyBase* property_base = nullptr;
	switch (_property_type)
	{
	case Makers::Properties::ePropertyBase:
		break;
	case Makers::Properties::eInputProperty:
		break;
	case Makers::Properties::eStaticProperty:
		break;
	case Makers::Properties::eOutputProperty:
		break;
	default:
		break;
	}
	AddProperty(property_base);
	return property_base;
}

//@ properties iterator begin
std::map<std::string, Properties::PropertyBase*>::iterator Makers::Properties::PropertyGroup::Begin()
{
	return properties_.begin();
}

//@ properties iterator end
std::map<std::string, Properties::PropertyBase*>::iterator Makers::Properties::PropertyGroup::End()
{
	return properties_.end();
}

//@ query property with id
Properties::PropertyBase* Makers::Properties::PropertyGroup::QueryPropertyID(std::string _id)
{
	for (auto pair : properties_)
	{
		if (pair.second->id() == _id)
		{
			return pair.second;
		}
	}
	return nullptr;
}

//@ query property with name
Properties::PropertyBase* Makers::Properties::PropertyGroup::QueryPropertyName(std::string _name)
{
	Properties::PropertyBase* property = properties_.count(_name) == 0 ? nullptr : properties_[_name];
	return property;
}

//@ clear all properties
void Makers::Properties::PropertyGroup::Clear()
{
	for (auto pair : properties_)
	{
		auto property = pair.second;
		delete property;
		property = nullptr;
	}
	properties_.clear();
}
