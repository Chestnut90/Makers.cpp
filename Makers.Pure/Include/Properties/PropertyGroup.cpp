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
	// release onwer item
	// delete owner_item_;
	owner_item_ = nullptr;

	// relase properties
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

	properties_.push_back(_property);
}

//@ TODO : 
//@ add property
Properties::PropertyBase* Makers::Properties::PropertyGroup::AddProperty(
	std::string _name,
	Computables::IComputable * _computable,
	bool _is_optional,
	ePropertyType _property_type)
{
	throw std::exception("not implemented");

	PropertyBase* property_base = nullptr;
	switch (_property_type)
	{
	case Makers::Properties::eInputProperty:
		property_base = new InputProperty(_name, owner_item_, _computable, _is_optional);
		break;
	case Makers::Properties::eStaticProperty:
		property_base = new StaticProperty(_name, owner_item_, _computable, _is_optional);
		break;
	case Makers::Properties::eOutputProperty:
		property_base = new OutputProperty(_name, owner_item_, _computable, _is_optional);
		break;
	default:
		break;
	}
	AddProperty(property_base);
	return property_base;
}

//@ properties iterator begin
std::vector<Properties::PropertyBase*>::iterator Makers::Properties::PropertyGroup::Begin()
{
	return properties_.begin();
}

//@ properties iterator end
std::vector<Properties::PropertyBase*>::iterator Makers::Properties::PropertyGroup::End()
{
	return properties_.end();
}

//@ query property with id
Properties::PropertyBase* Makers::Properties::PropertyGroup::QueryPropertyID(std::string _id)
{
	for (auto property : properties_)
	{
		if (property->id() == _id)
		{
			return property;
		}
	}
	return nullptr;
}

//@ query property with name
Properties::PropertyBase* Makers::Properties::PropertyGroup::QueryPropertyName(std::string _name)
{
	for (auto property : properties_)
	{
		if (property->name() == _name)
		{
			return property;
		}
	}

	return nullptr;
}

//@ clear all properties
void Makers::Properties::PropertyGroup::Clear()
{
	for (auto property : properties_)
	{
		delete property;
		property = nullptr;
	}
	properties_.clear();
}
