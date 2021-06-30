#include "pch.h"

#include <algorithm>

#include "../../Include/Properties/PropertyGroup.h"
#include "../../Include/Properties/PropertyBase.h"

namespace Properties = Makers::Properties;

int Makers::Properties::PropertyGroup::Count()
{
	return properties_.size();
}

Makers::Properties::PropertyGroup::PropertyGroup()
{

}


Makers::Properties::PropertyGroup::~PropertyGroup()
{

}

Makers::Properties::PropertyBase& Makers::Properties::PropertyGroup::operator[](const std::string _name)
{
	return *QueryPropertyName(_name);
}

void Makers::Properties::PropertyGroup::AddProperty(PropertyBase& _property)
{
	// no same id and name
	auto property = QueryPropertyID(_property.id());
	if (property != nullptr)
	{
		throw std::exception("find same named property.");
	}

	properties_[_property.name()] = &_property;
}

std::map<std::string, Properties::PropertyBase*>::iterator Makers::Properties::PropertyGroup::Begin()
{
	return properties_.begin();
}

std::map<std::string, Properties::PropertyBase*>::iterator Makers::Properties::PropertyGroup::End()
{
	return properties_.end();
}

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

Properties::PropertyBase* Makers::Properties::PropertyGroup::QueryPropertyName(std::string _name)
{
	Properties::PropertyBase* property = properties_.count(_name) == 0 ? nullptr : properties_[_name];
	return property;
}

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
