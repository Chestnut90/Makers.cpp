#include "pch.h"
#include "PropertyBase.h"

#include "../Items/ItemBase.h"
#include "../Computables/IComputable.h"

#include "../../Utils/UniqueIDs/GUIDGen.h"

#pragma region getters

//@ get id
std::string Makers::Properties::PropertyBase::id() const
{
	return id_;
}

//@ get name
std::string Makers::Properties::PropertyBase::name() const
{
	return name_;
}

//@ get owner item
Makers::Items::ItemBase* Makers::Properties::PropertyBase::owner_item() const
{
	return owner_item_;
}

//@ get is optional
bool Makers::Properties::PropertyBase::is_optional() const
{
	return is_optional_;
}

//@ get is used
bool Makers::Properties::PropertyBase::is_used() const
{
	return is_used_;
}

//@ get data object
Makers::Computables::IComputable* Makers::Properties::PropertyBase::data_object() const
{
	return data_object_;
}

#pragma endregion

#pragma region setters

//@ set is used
void Makers::Properties::PropertyBase::set_is_used(bool is_used)
{
	if (!is_optional_) return;

	is_used_ = is_used;
}

#pragma endregion

//@ protected Constructor (default)
Makers::Properties::PropertyBase::PropertyBase(
	std::string name,
	Items::ItemBase* owner_item,
	Computables::IComputable* data_object,
	bool is_optional) :
	IMapableData()
{
	id_ = Utils::IDGenerators::GUIDGen().Generate(); 
	name_ = name;
	owner_item_ = owner_item;
	data_object_ = data_object;
	is_optional_ = is_optional;
	is_used_ = true;
}

//@ public Destructor
Makers::Properties::PropertyBase::~PropertyBase()
{
	// release data object
	delete data_object_;
	data_object_ = nullptr;

	// release onwer item
	// do not delete parent item. memory error.
	owner_item_ = nullptr;
}

//@ To Data
std::map<std::string, std::string> Makers::Properties::PropertyBase::ToData()
{
	std::map<std::string, std::string> data;
	// property info
	data["ID"] = id_;
	data["Name"] = name_;
	data["OwnerID"] = std::string(owner_item_->id());
	data["Optional"] = std::to_string(is_optional_);
	data["Used"] = std::to_string(is_used_);

	// data_object
	data["DataType"] = "";	// TODO : 


	return data;
}
