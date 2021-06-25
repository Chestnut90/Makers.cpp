#pragma once

#include <iostream>

#include "../Makers.Pure/Include/Items/ItemFactory.h"
#include "../Makers.Pure/Include/Items/Samples/RandomFloatImageItem.h"

namespace Items
{
	static void ItemFactory_Test()
	{
		Makers::Items::ItemFactory item_factory;

		auto item = item_factory.Create("RandomFloatImageItem");
	
		auto random_float_image_item = dynamic_cast<Makers::Items::Samples::RandomFloatImageItem*>(item);

		std::cout << random_float_image_item->kOutputFloatImage << std::endl;

	}

}