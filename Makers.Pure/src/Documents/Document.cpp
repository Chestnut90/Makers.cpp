#include "pch.h"

#include <future>
#include <set>

// documents
#include "../../Include/Documents/Document.h"
#include "../../Include/Documents/ArrayMemoryPool.h"
// props
#include "../../Include/Properties/PropertyGroup.h"
#include "../../Include/Properties/InputProperty.h"
// items
#include "../../Include/Items/ItemFactory.h"
#include "../../Include/Items/ItemBase.h"
// id
#include "../../Utils/UniqueIDs/GUIDGen.h"

namespace Documents = Makers::Documents;
namespace Items = Makers::Items;

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

//@ title setter
void Makers::Documents::Document::set_title(std::string _title) 
{
	title_ = _title;
}

//@ constructor
Makers::Documents::Document::Document() :
	IMapableData()
{
	memory_pool_ = new MemoryPools::ArrayMemoryPool();
	id_ = Utils::IDGenerators::GUIDGen().Generate();
	title_ = "";
}

//@ constructor with id
Makers::Documents::Document::Document(std::string _id) : 
	Document()
{
	id_ = _id;
}

//@ constructor with id and items
Makers::Documents::Document::Document(std::string _id, std::vector<Items::ItemBase*> _items) : 
	Document(_id)
{
	items_ = _items;
}

//@ desturctor
Makers::Documents::Document::~Document()
{
	ClearItems();
}

//@ items count
int Makers::Documents::Document::Count()
{
	return items_.size();
}

//@ TODO : memory handling 
//@ add item
void Makers::Documents::Document::AddItem(Items::ItemBase * _itembase)
{
	if (SearchItem(_itembase->id()) != nullptr)
	{
		throw std::exception("an existing item");
	}

	items_.push_back(_itembase);
}

//@ remove item with item reference
void Makers::Documents::Document::RemoveItem(Items::ItemBase * _itembase)
{
	RemoveItem(_itembase->id());
}

//@ remove item with item id
void Makers::Documents::Document::RemoveItem(std::string _id)
{
	int index = SearchItemIndex(_id);
	if (index == -1) return;

	// delete
	auto item = items_.at(index);
	// TODO : 
	//Items::ItemFactory::instance().DeleteItem(item);
	
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

Items::ItemBase * Makers::Documents::Document::SearchItem(int _index)
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
		index++;
	}

	if (index >= items_.size()) return -1;
	return index;
}

//@ find rootable items
std::vector<Items::ItemBase*> Makers::Documents::Document::FindRootItems()
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
		std::for_each(input_properties.Begin(), input_properties.End(),
			[&id_set](std::pair<std::string, Properties::PropertyBase*> pair)
		{
			auto input_property = *dynamic_cast<Properties::InputProperty*>(pair.second);

			auto connected_item_id = input_property.connected_property().owner_item()->id();
			id_set.erase(connected_item_id);
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
		// TODO 
		//Items::ItemFactory::instance().DeleteItem(item);
	});
	items_.clear();
	items_.resize(0);
}

//@ runable
bool Makers::Documents::Document::RunAsync(std::vector<Items::ItemBase*> _items, void * _stream)
{
	if (_items.size() == 0)
	{
		_items = FindRootItems();
	}

	std::vector<std::future<bool>> futures;
	std::for_each(_items.begin(), _items.end(),
		[this, &futures, _stream](Items::ItemBase* item)
	{
		// TODO : if item need stream

		auto future = std::async(std::launch::async, 
			&Items::ItemBase::Run, item,	// func and instance
			this, nullptr, 0				// arguments
		);
		futures.push_back(std::move(future));
	});

	std::vector<bool> results;
	for (auto &future : futures)
	{
		results.push_back(future.get());
	}

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
