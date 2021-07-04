#pragma once

#include <iostream>

#include "../Makers.Pure/Include/Items/ItemFactory.h"
#include "../Makers.Pure/Include/Items/Samples/RandomFloatImageItem.h"

namespace Test
{
	namespace Items
	{
		static void ItemFactory_Test()
		{
			Makers::Items::ItemFactory item_factory;

			auto item = item_factory.Create("RandomFloatImageItem");

			auto random_float_image_item = dynamic_cast<Makers::Items::Samples::RandomFloatImageItem*>(item);

			std::cout << random_float_image_item->kOutputFloatImage << std::endl;

		}

		static void ItemFactory_Item_List()
		{
			Makers::Items::ItemFactory item_factory;

			auto items = item_factory.ContainingItems();

			for (auto pair : items)
			{
				std::cout << "group name : " << pair.first << std::endl;
				auto names = pair.second;
				for (auto name : names)
				{
					std::cout << "item name : " << name << std::endl;
				}
			}

		}
	}
}