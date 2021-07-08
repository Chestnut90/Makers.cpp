#include "pch.h"
#include "ItemFactory.h"

#pragma region Include Images Items
#include "Images/BinarizationItem.h"
#include "Images/FillImageItem.h"
#include "Images/InvertedImageItem.h"
#include "Images/MorphologyFilterItem.h"
#include "Images/NoiseFilterItem.h"
#include "Images/StreamImageItem.h"
#include "Images/ZmapItem.h"
#pragma endregion

void Makers::Items::ItemFactory::InitItems_Images()
{
	item_images_.clear();
	item_images_["BinarizationItem"] = []() 
	{return static_cast<ItemBase*>(new Makers::Items::Images::BinarizationItem()); };
	
	item_images_["FillImageItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Images::FillImageItem()); };
	
	item_images_["InvertedImageItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Images::InvertedImageItem()); };
	
	item_images_["MorphologyFilterItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Images::MorphologyFilterItem()); };
	
	item_images_["NoiseFilterItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Images::NoiseFilterItem()); };
	
	item_images_["StreamImageItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Images::StreamImageItem()); };

	item_images_["ZmapItem"] = []()
	{return static_cast<ItemBase*>(new Makers::Items::Images::ZmapItem()); };

	item_maps_["Images"] = item_images_;
}
