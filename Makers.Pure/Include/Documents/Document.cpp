#include "pch.h"

#include <future>
#include <set>

// documents
#include "Document.h"
#include "ArrayMemoryPool.h"
// props
#include "../Properties/PropertyGroup.h"
#include "../Properties/InputProperty.h"
// items
#include "../Items/ItemFactory.h"
#include "../Items/ItemBase.h"
// computables - image
#include "../Computables/IComputable.h"
#include "../Computables/Image.h"
// id
#include "../../Utils/UniqueIDs/GUIDGen.h"

#pragma region getters

//@ id getter
std::string Makers::Documents::Document::id() const
{
	return id_;
}

//@ title getter
std::string Makers::Documents::Document::title() const
{
	return title_;
}

//@ get memory pool
Makers::MemoryPools::ArrayMemoryPool * Makers::Documents::Document::memory_pool() const
{
	return memory_pool_;
}

//@ get stream image
Makers::Computables::Image<float>* Makers::Documents::Document::stream_image() const
{
	return stream_image_;
}

//@ get width of stream image
unsigned long Makers::Documents::Document::width() const
{
	return stream_image_->width();
}

//@ get height of stream image
unsigned long Makers::Documents::Document::height() const
{
	return stream_image_->height();
}

#pragma endregion
#pragma region setters

//@ title setter
void Makers::Documents::Document::set_title(std::string _title) 
{
	title_ = _title;
}

//@ set stream image
void Makers::Documents::Document::set_stream_image(Makers::Computables::Image<float>* _stream_image)
{
	stream_image_->set_image(_stream_image);
	memory_pool_->AllocateMemory(_stream_image->width(), _stream_image->height());
}

//@ set stream image
void Makers::Documents::Document::set_stream_image(float * _image, unsigned long _width, unsigned long _height)
{
	stream_image_->set_image(_image, _width, _height);
	memory_pool_->AllocateMemory(_width, _height);
}

#pragma endregion
#pragma region ctors

//@ constructor
Makers::Documents::Document::Document() :
	IMapableData()
{
	memory_pool_ = nullptr;// = new MemoryPools::ArrayMemoryPool();
	stream_image_ = new Makers::Computables::Image<float>();
	id_ = Utils::IDGenerators::GUIDGen().Generate();
	title_ = "";
}

//@ !deprecated
//@ constructor with id
Makers::Documents::Document::Document(std::string _id) : 
	Document()
{
	id_ = _id;
}

//@ !deprecated
//@ constructor with id and items
Makers::Documents::Document::Document(
	std::string _id, 
	std::vector<Items::ItemBase*> _items) : 
	Document(_id)
{
	for (auto item : _items)
	{
		AddItem(item);
	}
}

//@ desturctor
Makers::Documents::Document::~Document()
{
	if (memory_pool_ != nullptr) { delete memory_pool_; }
	delete stream_image_;
	ClearItems();
}

#pragma endregion

//@ items count
int Makers::Documents::Document::Count()
{
	return items_.size();
}

//@ add item
void Makers::Documents::Document::AddItem(Items::ItemBase * _itembase)
{
	if (SearchItem(_itembase->id()) != nullptr)
	{
		throw std::exception("an existing item");
	}

	// set owner document into item base
	_itembase->set_document(this);
	items_.push_back(_itembase);
}

//@ remove item with item reference
void Makers::Documents::Document::RemoveItem(Items::ItemBase * _itembase)
{
	if (_itembase == nullptr) { return; }
	RemoveItem(_itembase->id());
}

//@ remove item with item id
void Makers::Documents::Document::RemoveItem(std::string _id)
{
	int index = SearchItemIndex(_id);
	if (index == -1) return;

	auto item = items_.at(index);
	if (item == nullptr) { return; }
	
	// delete
	Makers::Items::ItemFactory().DeleteItem(item);
	
	// erase from vector
	items_.erase(items_.begin() + index);
}

//@ search item with item id
Makers::Items::ItemBase * Makers::Documents::Document::SearchItem(std::string _id)
{
	int index = SearchItemIndex(_id);
	if (index == -1) return nullptr;
	return items_[index];
}

//@ search item with index
Makers::Items::ItemBase * Makers::Documents::Document::SearchItem(int _index)
{
	return items_[_index];
}

//@ search index of item with item reference
int Makers::Documents::Document::SearchItemIndex(Items::ItemBase * _itembase)
{
	return SearchItemIndex(_itembase->id());
}

//@ search index of item with item id
int Makers::Documents::Document::SearchItemIndex(std::string _id)
{
	int index = 0;

	for (auto item : items_)
	{
		if (item->id() == _id) break;
		++index;
	}

	if (index >= items_.size()) return -1;
	return index;
}

//@ find rootable items
std::vector<Makers::Items::ItemBase*> Makers::Documents::Document::FindRootItems()
{
	// init id set
	std::set<std::string> id_set;
	std::for_each(items_.begin(), items_.end(), [&id_set](Items::ItemBase* item)
	{
		id_set.insert(item->id());
	});

	// remove connected item id from id set
	std::for_each(items_.begin(), items_.end(),
		[&id_set](Items::ItemBase* item)
	{
		auto input_properties = item->input_properties();
		std::for_each(input_properties->Begin(), input_properties->End(),
			[&id_set](std::pair<std::string, Properties::PropertyBase*> pair)
		{
			auto input_property = dynamic_cast<Properties::InputProperty*>(pair.second);

			// check connected null
			auto connected_property = input_property->connected_property();
			if (connected_property != nullptr)
			{
				auto connected_item_id = input_property->connected_property()->owner_item()->id();
				id_set.erase(connected_item_id);
			}
		});
	});

	// left ids
	std::vector<Items::ItemBase*> result;
	std::for_each(id_set.begin(), id_set.end(),
		[this, &result](const std::string id)
	{
		result.push_back(SearchItem(id));
	});

	return result;
}

//@ clear all items
void Makers::Documents::Document::ClearItems()
{
	std::for_each(items_.begin(), items_.end(), [](Items::ItemBase* item)
	{
		Makers::Items::ItemFactory().DeleteItem(item);
	});
	items_.clear();
	items_.resize(0);
}

void Makers::Documents::Document::InitMemoryPool()
{
	if (memory_pool_ == nullptr)
	{
		memory_pool_ = new Makers::MemoryPools::ArrayMemoryPool();
	}

	int buffer_counts = 0;
	std::for_each(items_.begin(), items_.end(), [&buffer_counts](Makers::Items::ItemBase* item)
	{
		buffer_counts += item->buffer_count();
	});

	// init memory_pool
	auto width = stream_image_->width();
	auto height = stream_image_->height();
	memory_pool_->AllocateMemory(width, height, buffer_counts);
}

//@ runable
bool Makers::Documents::Document::RunAsync(
	std::vector<Items::ItemBase*> _items, 
	Makers::Computables::Image<float>* _stream)
{
	// init memory pool
	if (memory_pool_ == nullptr) { InitMemoryPool(); }	

	// find end items
	if (_items.size() == 0) { _items = FindRootItems(); }			

	// copy stream into document
	if (_stream != nullptr) { stream_image_->set_image(_stream); }	

	std::vector<std::future<bool>> futures;
	std::for_each(_items.begin(), _items.end(),
		[this, &futures, _stream](Items::ItemBase* item)
	{
		auto future = std::async(std::launch::async, 
			&Items::ItemBase::Run, item,	// func and instance
			this, nullptr, 0				// arguments
		);
		futures.push_back(std::move(future));
	});

	// wait futures
	std::vector<bool> results;
	for (auto &future : futures) { results.push_back(future.get()); }

	return std::all_of(results.begin(), results.end(), [](const bool res) { return res; });
}

//@ to data
std::map<std::string, std::string> Makers::Documents::Document::ToData()
{
	std::map<std::string, std::string> data;

	data["ID"] = id_;
	data["Title"] = title_;
	data["ItemCount"] = std::to_string(items_.size());

	return data;
}