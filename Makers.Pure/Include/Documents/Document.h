#pragma once

#include "../IMapableData.h"
#include "../IRunAble.h"
#include <vector>

namespace nXSDK { class Surf; }
namespace Makers
{
	namespace Computables { template <typename _image_type>class Image; }
	namespace MemoryPools { class ArrayMemoryPool; }
	namespace Items { class ItemBase; class ItemFactory; }

	namespace Documents
	{
		// TODO : need to define input image
		//@ Class <Document>
		//@ Root of items
		//@ Contain items and memory pool
		//@ Inherit <IMapableData>
		class __declspec(dllexport) Document :
			public IMapableData,
			public IRunAble
		{
			friend class Makers::Items::ItemFactory;

			// TODO : input images
		protected:
			//@ surf
			nXSDK::Surf* surf_;

		public:
			//@ get surf
			nXSDK::Surf& surf() const;

#pragma region members
		private:
			//@ memory pool
			MemoryPools::ArrayMemoryPool* memory_pool_;
			//@ unique id 
			std::string id_;
			//@ item collection
			std::vector<Items::ItemBase*> items_;

		public:
			//@ title
			std::string title_;

#pragma endregion
#pragma region Getters
		public:
			//@ get id
			std::string id() const;
			//@ get title
			std::string title() const;
			//@ get memory pool
			MemoryPools::ArrayMemoryPool* memory_pool() const;
#pragma endregion

#pragma region Setters
		public:
			//@ set title
			void set_title(std::string title);

#pragma endregion
#pragma region Constructors & Destructors

		public:
			//@ constructor
			Document();
			//@ deprecated
			//@ constructor with id
			Document(std::string id);
			//@ deprecated
			//@ constructor with id and items
			Document(std::string id, std::vector<Items::ItemBase*> items);
			//@ destructor
			virtual ~Document();

#pragma endregion
#pragma region item collection methods

		public:
			//@ items count
			int Count();
			//@ add item
			void AddItem(Items::ItemBase& itembase);
			//@ remove item
			void RemoveItem(Items::ItemBase& itembase);
			//@ remove item
			void RemoveItem(std::string id);
			//@ search item with id
			Items::ItemBase* SearchItem(std::string id);
			//@ search item with index
			Items::ItemBase* SearchItem(int index);
			//@ serach index
			int SearchItemIndex(Items::ItemBase* itembase);
			//@ search index
			int SearchItemIndex(std::string id);
			//@ find root items
			std::vector<Items::ItemBase*> FindRootItems();
			//@ clear all items
			void ClearItems();

#pragma endregion

		public:
			// TODO : memory initialized
			//@ initialize memory pool
			//@ 
			void InitMemoryPool();
			//@ runable
			bool Run_Async(
				std::vector<Items::ItemBase*> items = std::vector<Items::ItemBase*>()	// default size 0
			);

			// implement <IRunAble>
		public:
			//@ !deprecated
			//@ runable method
			bool Run(
				Document* document = nullptr, 
				Items::ItemBase* sender = nullptr, 
				long long timestampe = 0) override;

		public:
			//@ to data -> IMapableData override 
			std::map<std::string, std::string> ToData() override;
		};
	}
}

