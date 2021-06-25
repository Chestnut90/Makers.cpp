#pragma once
#ifndef _ITEM_FACOTRY_H_
#define _ITEM_FACOTRY_H_

#include <map>
#include <string>

namespace Makers
{
	namespace Items
	{
		__declspec(dllexport) class ItemBase;

		class __declspec(dllexport) ItemFactory
		{
			typedef ItemBase* (*ItemCreator)();

		private:
			std::map<std::string, std::map<std::string, ItemCreator>> item_maps_;

			std::map<std::string, ItemCreator> item_criterias_;
			std::map<std::string, ItemCreator> item_images_;
			std::map<std::string, ItemCreator> item_inspinfos_;
			std::map<std::string, ItemCreator> item_numericals_;
			std::map<std::string, ItemCreator> item_rois_;
			std::map<std::string, ItemCreator> item_symbols_;
			std::map<std::string, ItemCreator> item_samples_;

		//@ initializers
		public:
			void InitItems();
			void InitItems_Criterias();
			void InitItems_Images();
			void InitItems_InspInfos();
			void InitItems_Numericals();
			void InitItems_Rois();
			void InitItems_Symbols();
			void InitItems_Samples();

		public:
			ItemFactory();
			~ItemFactory();

		public:

			void DeleteItem(ItemBase*);
			ItemBase* Create(std::string);

		};
	}
}


#endif // !_ITEM_FACOTRY_H_
