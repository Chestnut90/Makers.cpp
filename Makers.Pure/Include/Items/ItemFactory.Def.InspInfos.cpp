#include "pch.h"
#include "ItemFactory.h"

#pragma region Include InspInfos Item
#pragma endregion

void Makers::Items::ItemFactory::InitItems_InspInfos()
{
	item_inspinfos_.clear();
	item_maps_["InspInfos"] = item_inspinfos_;
}
