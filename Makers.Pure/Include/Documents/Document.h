#pragma once

#include "../IMapableData.h"

#include <vector>

namespace Makers
{
	namespace Computables { class IComputable; template <typename _image_type>class Image; }
	namespace MemoryPools { class ArrayMemoryPool; }
	namespace Items { class ItemBase;}

	//@ TODO : memory pool access
	namespace Documents
	{
		class __declspec(dllexport) Document :
			public IMapableData
		{
			// access to stream_image_;
			friend class Makers::Items::ItemBase;

#pragma region members
		private:
			//@ memory pool
			MemoryPools::ArrayMemoryPool* memory_pool_;

			//@ stream image
			Makers::Computables::Image<float>* stream_image_;

		private:
			//@ unique id 
			std::string id_;
			//@ item collection
			std::vector<Items::ItemBase*> items_;

		public:
			//@ title
			std::string title_;

#pragma endregion
#pragma region Getters & Setters

		// getters
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
		// setters
		public:
			void set_title(std::string _title);
			void set_stream_image(Makers::Computables::Image<float>* _stream_image);
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

			//@ runable
			bool RunAsync(
				std::vector<Items::ItemBase*> _items = std::vector<Items::ItemBase*>(),	// default size 0
				Makers::Computables::Image<float>* _stream = nullptr // default nullptr
			);

			//@ to data -> IMapableData override 
			std::map<std::string, std::string> ToData() override;

		private:

			//@ compute additional buffer numbers
			int _ComputeImageBufferCounts(Makers::Items::ItemBase*);
			//@ is it image type
			bool _IsImageType(Makers::Computables::IComputable*);
		};
	}
}

