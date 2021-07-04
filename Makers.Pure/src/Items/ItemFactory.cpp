#include "pch.h"
#include "../../Include/Items/ItemFactory.h"
#include "../../Include/Items/ItemBase.h"

#include "../../Include/Documents/Document.h"
#include "../../Include/Properties/PropertyBase.h"

#pragma region Include Sample Item
#include "../../Include/Items/Samples/FloatThresholdingItem.h"
#include "../../Include/Items/Samples/RandomFloatImageItem.h"
#include "../../Include/Items/Samples/SampleItem0.h"
#pragma endregion

Makers::Items::ItemFactory::ItemFactory()
{
	InitItems();
}

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

void Makers::Items::ItemFactory::DeleteItem(ItemBase * _item)
{
	// TODO : properties handling
	delete _item;
	_item = nullptr;
}

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

#pragma region Init Items

void Makers::Items::ItemFactory::InitItems_Criterias()
{
	item_criterias_.clear();
	item_maps_["Criterias"] = item_criterias_;
}

void Makers::Items::ItemFactory::InitItems_Images()
{
	item_images_.clear();
	item_maps_["Images"] = item_images_;
}

void Makers::Items::ItemFactory::InitItems_InspInfos()
{
	item_inspinfos_.clear();
	item_maps_["InspInfos"] = item_inspinfos_;
}

void Makers::Items::ItemFactory::InitItems_Numericals()
{
	item_numericals_.clear();
	item_maps_["Numericals"] = item_numericals_;
}

void Makers::Items::ItemFactory::InitItems_Rois()
{
	item_rois_.clear();
	item_maps_["Rois"] = item_rois_;
}

void Makers::Items::ItemFactory::InitItems_Symbols()
{
	item_symbols_.clear();
	item_maps_["Symbols"] = item_symbols_;
}

void Makers::Items::ItemFactory::InitItems_Samples()
{
	item_samples_.clear();
	//item_samples_["RandomFloatImageItem"] = []() {return static_cast<ItemBase*>(new Makers::Items::Samples::RandomFloatImageItem()); };
	item_samples_["FloatThresholdingItem"] = []() {return static_cast<ItemBase*>(new Makers::Items::Samples::FloatThreshodingItem()); };

	item_maps_["Samples"] = item_samples_;
}

#pragma endregion


Makers::Items::ItemBase * Makers::Items::ItemFactory::Create(std::string _item_name)
{
	for (auto item_group : item_maps_)
	{
		auto group = item_group.second;

		if (group.count(_item_name) == 1)
		{
			return group[_item_name]();
		}
	}
	const std::string error = "not matched item : " + _item_name;
	throw std::exception(error.c_str());
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

void Makers::Items::ItemFactory::IDHandle(Makers::Documents::Document* _document, std::string _id)
{
	_document->id_ = _id;
}

//@ TODO : other ways -> hidden
void Makers::Items::ItemFactory::IDHandle(ItemBase& _item_base, std::string _id)
{
	_item_base.id_ = _id;
}

//@ TODO : other ways
void Makers::Items::ItemFactory::IDHandle(Makers::Properties::PropertyBase& _property_base, std::string _id)
{
	_property_base.id_ = _id;
}

