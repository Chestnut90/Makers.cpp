#include "pch.h"
#include "../../Include/Items/ItemFactory.h"
#include "../../Include/Items/ItemBase.h"

#pragma region Include Sample Item
#include "../../Include/Items/Samples/FloatThresholdingItem.h"
#include "../../Include/Items/Samples/RandomFloatImageItem.h"
#pragma endregion


void Makers::Items::ItemFactory::InitItems_Samples()
{

	//item_samples_["RandomFloatImageItem"] = []() {return static_cast<ItemBase*>(new Makers::Items::Samples::RandomFloatImageItem()); };
	item_samples_["FloatThresholdingItem"] = []() {return static_cast<ItemBase*>(new Makers::Items::Samples::FloatThreshodingItem()); };
	
	item_maps_["Samples"] = item_samples_;
}

