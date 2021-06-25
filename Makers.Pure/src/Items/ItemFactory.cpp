#include "pch.h"
#include "../../Include/Items/ItemFactory.h"
#include "../../Include/Items/ItemBase.h"

#pragma region Include Sample Item
#include "../../Include/Items/Samples/FloatThresholdingItem.h"
#include "../../Include/Items/Samples/RandomFloatImageItem.h"
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
	item_maps_["Criterias"] = item_criterias_;

}

void Makers::Items::ItemFactory::InitItems_Images()
{
	item_maps_["Images"] = item_images_;

}

void Makers::Items::ItemFactory::InitItems_InspInfos()
{
	item_maps_["InspInfos"] = item_inspinfos_;

}

void Makers::Items::ItemFactory::InitItems_Numericals()
{
	item_maps_["Numericals"] = item_numericals_;

}

void Makers::Items::ItemFactory::InitItems_Rois()
{
	item_maps_["Rois"] = item_rois_;

}

void Makers::Items::ItemFactory::InitItems_Symbols()
{
	item_maps_["Symbols"] = item_symbols_;

}

void Makers::Items::ItemFactory::InitItems_Samples()
{

	item_samples_["RandomFloatImageItem"] = []() {return static_cast<ItemBase*>(new Makers::Items::Samples::RandomFloatImageItem()); };
	item_samples_["FloatThresholdingItem"] = []() {return static_cast<ItemBase*>(new Makers::Items::Samples::FloatThreshodingItem()); };
	
	item_maps_["Samples"] = item_samples_;
}
#pragma endregion


Makers::Items::ItemBase * Makers::Items::ItemFactory::Create(std::string _item_name)
{
	for (auto itemGroup : item_maps_)
	{
		auto group = itemGroup.second;

		if (group.count(_item_name) == 1)
		{
			return group[_item_name]();
		}
	}
	return nullptr;
}
//
////@ deprecated
//void Makers::Items::ItemFactory::Register(std::string _item_name, ItemCreator _item_creator)
//{
//
//	// TODO : error handling
//	//item_maps_[_item_name] = _item_creator;
//
//}
//
////@ deprecated
//void Makers::Items::ItemFactory::Register(void * _instance, std::string _item_name, ItemCreator _item_creator)
//{
//	//registers_.push_back(_instance);
//	Register(_item_name, _item_creator);
//
//}
//
////@ deprecated
//void Makers::Items::ItemFactory::UnRegister(std::string _item_name)
//{
//	// TODO : error handling
//	item_maps_.erase(_item_name);
//}
