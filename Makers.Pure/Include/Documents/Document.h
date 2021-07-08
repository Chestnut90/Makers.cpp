#pragma once

#include "../IMapableData.h"
#include <vector>

namespace Makers
{
	namespace Computables { template <typename _image_type>class Image; }
	namespace MemoryPools { class ArrayMemoryPool; }
	namespace Items { class ItemBase; class ItemFactory; }

	namespace Documents
	{
		class __declspec(dllexport) Document :
			public IMapableData
		{
			friend class Makers::Items::ItemFactory;

			// TODO : input images
			
			
			//@ stream image red
			//Makers::Computables::Image<unsigned char>* stream_image_red_;
			//@ stream image green
			//Makers::Computables::Image<unsigned char>* stream_image_green_;
			//@ stream image blue
			//Makers::Computables::Image<unsigned char>* stream_image_blue_;

#pragma region members
		private:
			//@ memory pool
			MemoryPools::ArrayMemoryPool* memory_pool_;
			//@ stream image float
			Makers::Computables::Image<float>* stream_image_;
			
			//@ unique id 
			std::string id_;
			//@ item collection
			std::vector<Items::ItemBase*> items_;
			//@ last computed time
			long long last_computed_time_;

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
			//@ get stream image
			Makers::Computables::Image<float>* stream_image() const;
			//@ stream image width
			unsigned long width() const;
			//@ stream image height
			unsigned long height() const;
			//@ last computed time
			long long last_computed_time() const;
#pragma endregion

#pragma region Setters

		public:
			//@ set title
			void set_title(std::string _title);
			//@ set stream image
			void set_stream_image(Makers::Computables::Image<float>* _stream_image);
			//@ set stream image
			void set_stream_image(float* _image, unsigned long _width, unsigned long _height);

#pragma endregion
#pragma region Constructors & Destructors

		public:
			//@ constructor
			Document();
			//@ constructor with id
			Document(std::string _id);
			//@ constructor with id and items
			Document(std::string _id, std::vector<Items::ItemBase*> _items);
			//@ destructor
			virtual ~Document();

#pragma endregion
#pragma region item collection methods

		public:
			//@ items count
			int Count();
			//@ add item
			void AddItem(Items::ItemBase* _itembase);
			//@ remove item
			void RemoveItem(Items::ItemBase* _itembase);
			//@ remove item
			void RemoveItem(std::string _id);
			//@ search item with id
			Items::ItemBase* SearchItem(std::string _id);
			//@ search item with index
			Items::ItemBase* SearchItem(int _index);
			//@ serach index
			int SearchItemIndex(Items::ItemBase* _itembase);
			//@ search index
			int SearchItemIndex(std::string _id);
			//@ find root items
			std::vector<Items::ItemBase*> FindRootItems();
			//@ clear all items
			void ClearItems();

#pragma endregion

		public:

			//@ initialize memory pool
			//@ 
			void InitMemoryPool();

		public:

			//@ runable
			bool RunAsync(
				std::vector<Items::ItemBase*> _items = std::vector<Items::ItemBase*>(),	// default size 0
				Makers::Computables::Image<float>* _stream = nullptr // default nullptr
			);

			//@ to data -> IMapableData override 
			std::map<std::string, std::string> ToData() override;
		};
	}
}

