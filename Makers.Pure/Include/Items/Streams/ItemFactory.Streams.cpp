#include "pch.h"
#include "../ItemFactory.h"

#pragma region Include Symbols Item
#include "StreamGrayItem.h"
#include "StreamRGBItem.h"
#include "StreamZmapItem.h"
#pragma endregion

void Makers::Items::ItemFactory::InitItems_Streams()
{
	item_streams_.clear();

	// add gray item
	item_streams_["StreamGrayItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Streams::StreamGrayItem()); };

	// add rgb item
	item_streams_["StreamRGBItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Streams::StreamRGBItem()); };

	// add zmap item
	item_streams_["StreamZampItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Streams::StreamZmapItem()); };

	item_maps_["Streams"] = item_streams_;
}
