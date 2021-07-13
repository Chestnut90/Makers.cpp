#include "pch.h"
#include "../ItemFactory.h"

#pragma region Include ROIs Item
#include "../ROIs/RoiItem.h"
#pragma endregion

void Makers::Items::ItemFactory::InitItems_Rois()
{
	item_rois_.clear();

	// add roi item in factory
	item_rois_["RoiItem"] = []()
	{ return (Makers::Items::ItemBase*) new Makers::Items::ROIs::RoiItem(); };

	item_maps_["Rois"] = item_rois_;
}
