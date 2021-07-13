#include "pch.h"

#include <algorithm>

#include "PropertyGroup.h"

#include "PropertyBase.h"
#include "InputProperty.h"
#include "StaticProperty.h"
#include "OutputProperty.h"

namespace Properties = Makers::Properties;


//@ get owner item
Makers::Items::ItemBase * Makers::Properties::PropertyGroup::owner_item() const
{
	return owner_item_;
}

//@ constructor
Makers::Properties::PropertyGroup::PropertyGroup(Items::ItemBase* owner_item)
{
	owner_item_ = owner_item;
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
Makers::Properties::PropertyBase* Makers::Properties::PropertyGroup::operator[](const std::string name)
{
	return QueryPropertyName(name);
}

//@ get properties count
int Makers::Properties::PropertyGroup::Count()
{
	return properties_.size();
}

//@ add property
void  Makers::Properties::PropertyGroup::AddProperty(PropertyBase* property)
{
	// no same id and name
	auto query_property = QueryPropertyID(property->id());
	if (query_property != nullptr)
	{
		throw std::exception("find same named property.");
	}

	// insert arg
	properties_.push_back(property);
}

//@ add property with property data
Properties::PropertyBase* Makers::Properties::PropertyGroup::AddProperty(
	std::string name,
	Computables::IComputable* computable,
	bool is_optional,
	ePropertyType property_type)
{
	PropertyBase* property_base = nullptr;
	switch (property_type)
	{
	case Makers::Properties::eInputProperty:
		property_base = new InputProperty(name, owner_item_, computable, is_optional);
		break;
	case Makers::Properties::eStaticProperty:
		property_base = new StaticProperty(name, owner_item_, computable, is_optional);
		break;
	case Makers::Properties::eOutputProperty:
		property_base = new OutputProperty(name, owner_item_, computable, is_optional);
		break;
	default:
		std::string error = "Error occured in PropertyGroup.\n";
		error += "not handled property type.\n";
		throw std::exception(error.c_str());
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
Properties::PropertyBase* Makers::Properties::PropertyGroup::QueryPropertyID(std::string id)
{
	for (auto property : properties_)
	{
		if (property->id() == id)
		{
			return property;
		}
	}
	return nullptr;
}

//@ query property with name
Properties::PropertyBase* Makers::Properties::PropertyGroup::QueryPropertyName(std::string name)
{
	for (auto property : properties_)
	{
		if (property->name() == name)
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
