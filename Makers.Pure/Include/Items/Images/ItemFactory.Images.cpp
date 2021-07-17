#include "pch.h"
#include "../ItemFactory.h"

#pragma region Include Images Items
#include "BinarizationItem.h"
#include "FillImageItem.h"
#include "InvertedImageItem.h"
#include "MorphologyFilterItem.h"
#include "NoiseFilterItem.h"
#pragma endregion

void Makers::Items::ItemFactory::InitItems_Images()
{
	item_images_.clear();

	// add binarization
	item_images_["BinarizationItem"] = []() 
	{return static_cast<ItemBase*>(new Makers::Items::Images::BinarizationItem()); };
	
	// add fill image
	item_images_["FillImageItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Images::FillImageItem()); };
	
	// add inverted image
	item_images_["InvertedImageItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Images::InvertedImageItem()); };
	
	// add morphology filter
	item_images_["MorphologyFilterItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Images::MorphologyFilterItem()); };
	
	// add noise filter
	item_images_["NoiseFilterItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Images::NoiseFilterItem()); };

	item_maps_["Images"] = item_images_;
}
