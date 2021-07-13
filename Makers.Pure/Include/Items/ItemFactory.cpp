#include "pch.h"
#include "ItemFactory.h"
#include "ItemBase.h"

#include "../Documents/Document.h"
#include "../Properties/PropertyBase.h"

//@ Constructor
Makers::Items::ItemFactory::ItemFactory()
{
	InitItems();
}

//@ Destructor
Makers::Items::ItemFactory::~ItemFactory()
{
	// remove maps
	for (auto group : item_maps_)
	{
		for (auto creator : group.second)
		{
			auto func = creator.second;
			func = nullptr;
		}
	}
}

//@ Destroy item
void Makers::Items::ItemFactory::DestroyItem(ItemBase* item)
{
	delete item;
	item = nullptr;
}

//@ Create item
Makers::Items::ItemBase * Makers::Items::ItemFactory::Create(std::string item_name)
{
	for (auto item_group : item_maps_)
	{
		auto group = item_group.second;

		if (group.count(item_name) == 1)
		{
			return group[item_name]();
		}
	}
	const std::string error = "not matched item : " + item_name;
	throw std::exception(error.c_str());
}

//@ Init Items
void Makers::Items::ItemFactory::InitItems()
{
	item_maps_.clear();
	InitItems_Criterias();
	InitItems_Images();
	InitItems_InspInfos();
	InitItems_Numericals();
	InitItems_Rois();
	InitItems_Symbols();
	InitItems_Samples();
}

std::map<std::string, std::vector<std::string>> Makers::Items::ItemFactory::ContainingItems()
{
	std::map<std::string, std::vector<std::string>> items;

	for (auto item_group : item_maps_)
	{
		std::string group_name = item_group.first;
		std::vector<std::string> names;
		auto group = item_group.second;
		for (auto pair : group)
		{
			names.push_back(pair.first); // push back item name
		}

		items[group_name] = names;
	}

	return items;
}

void Makers::Items::ItemFactory::IDHandle(Makers::Documents::Document& document, std::string id)
{
	document.id_ = id;
}

//@ TODO : other ways -> hidden
void Makers::Items::ItemFactory::IDHandle(ItemBase& item_base, std::string id)
{
	item_base.id_ = id;
}

//@ TODO : other ways
void Makers::Items::ItemFactory::IDHandle(Makers::Properties::PropertyBase& property_base, std::string id)
{
	property_base.id_ = id;
}

