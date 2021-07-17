#include "pch.h"
#include "../ItemFactory.h"

#pragma region Include Sample Item
#include "../Samples/FloatThresholdingItem.h"
#include "../Samples/RandomFloatImageItem.h"
#include "../Samples/SampleItem0.h"
#pragma endregion

void Makers::Items::ItemFactory::InitItems_Samples()
{
	item_samples_.clear();
	//item_samples_["RandomFloatImageItem"] = []() {return static_cast<ItemBase*>(new Makers::Items::Samples::RandomFloatImageItem()); };
	item_samples_["FloatThresholdingItem"] = []() {return static_cast<ItemBase*>(new Makers::Items::Samples::FloatThreshodingItem()); };

	item_maps_["Samples"] = item_samples_;
}

