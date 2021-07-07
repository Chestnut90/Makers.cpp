#include "pch.h"
#include "ItemFactory.h"

#pragma region Include Numericals Item
#include "Numericals/BlobItem.h"
#include "Numericals/EdgeDetectItem.h"
#pragma endregion

void Makers::Items::ItemFactory::InitItems_Numericals()
{
	item_numericals_.clear();

	item_numericals_["BlobItem"] = []()
	{ return static_cast<ItemBase*>(new Makers::Items::Numericals::BlobItem()); };

	item_numericals_["EdgeDetectItem"] = []()
	{ return static_cast<ItemBase*>(new Makers::Items::Numericals::EdgeDetectItem()); };


	item_maps_["Numericals"] = item_numericals_;
}
