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

// surf interface
#include "../nxSurfs/Surf.h"

// id
#include "../../Utils/UniqueIDs/GUIDGen.h"

#pragma region getters

nXSDK::Surf & Makers::Documents::Document::surf() const
{
	return *surf_;
}

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

#pragma endregion
#pragma region setters

//@ title setter
void Makers::Documents::Document::set_title(std::string title) 
{
	title_ = title;
}

#pragma endregion
#pragma region ctors

//@ constructor
Makers::Documents::Document::Document() :
	IMapableData(),
	IRunAble()
{
	memory_pool_ = nullptr;// = new MemoryPools::ArrayMemoryPool();
	surf_ = new nXSDK::Surf();	// init surf
	id_ = Utils::IDGenerators::GUIDGen().Generate();
	title_ = "";
}

//@ !deprecated
//@ constructor with id
Makers::Documents::Document::Document(std::string id) : 
	Document()
{
	id_ = id;
}

//@ !deprecated
//@ constructor with id and items
Makers::Documents::Document::Document(
	std::string id, 
	std::vector<Items::ItemBase*> items) : 
	Document(id)
{
	for (auto item : items)
	{
		AddItem(*item);
	}
}

//@ desturctor
Makers::Documents::Document::~Document()
{
	if (memory_pool_ != nullptr) { delete memory_pool_; }
	delete surf_;
	ClearItems();
}

#pragma endregion
#pragma region item collection methods
//@ items count
int Makers::Documents::Document::Count()
{
	return items_.size();
}

//@ add item
void Makers::Documents::Document::AddItem(Items::ItemBase& itembase)
{
	if (SearchItem(itembase.id()) != nullptr)
	{
		throw std::exception("an existing item");
	}

	// set owner document into item base
	itembase.set_document(this);
	items_.push_back(&itembase);
}

//@ remove item with item reference
void Makers::Documents::Document::RemoveItem(Items::ItemBase& itembase)
{
	RemoveItem(itembase.id());
}

//@ remove item with item id
void Makers::Documents::Document::RemoveItem(std::string id)
{
	int index = SearchItemIndex(id);
	if (index == -1) return;

	auto item = items_.at(index);
	if (item == nullptr) { return; }
	
	// delete
	Makers::Items::ItemFactory().DestroyItem(item);
	
	// erase from vector
	items_.erase(items_.begin() + index);
}

//@ search item with item id
Makers::Items::ItemBase * Makers::Documents::Document::SearchItem(std::string id)
{
	int index = SearchItemIndex(id);
	if (index == -1) return nullptr;
	return items_[index];
}

//@ search item with index
Makers::Items::ItemBase * Makers::Documents::Document::SearchItem(int index)
{
	return items_[index];
}

//@ search index of item with item reference
int Makers::Documents::Document::SearchItemIndex(Items::ItemBase* itembase)
{
	return SearchItemIndex(itembase->id());
}

//@ search index of item with item id
int Makers::Documents::Document::SearchItemIndex(std::string id)
{
	int index = 0;

	for (auto item : items_)
	{
		if (item->id() == id) break;
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
			[&id_set](Properties::PropertyBase* property)
		{
			auto input_property = dynamic_cast<Properties::InputProperty*>(property);

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
		Makers::Items::ItemFactory().DestroyItem(item);
	});
	items_.clear();
	items_.resize(0);
}

#pragma endregion

//@ Init memory pool
void Makers::Documents::Document::InitMemoryPool()
{
	// init memory pool
	if (memory_pool_ == nullptr) { memory_pool_ = new Makers::MemoryPools::ArrayMemoryPool(); }

	// aggregate buffer counts
	int buffer_counts = 0;
	std::for_each(items_.begin(), items_.end(), [&buffer_counts](Makers::Items::ItemBase* item)
	{
		buffer_counts += item->buffer_count();
	});

	auto width = surf_->width();
	auto height = surf_->height();
	
	// allocate memory pool
	memory_pool_->AllocateMemory(width, height, buffer_counts);
}

//@ runable
bool Makers::Documents::Document::Run_Async(
	std::vector<Items::ItemBase*> items)
{
	// reset IRunAble state
	ResetState();

	// init memory pool
	if (memory_pool_ == nullptr) { InitMemoryPool(); }	

	// find end items
	if (items.size() == 0) { items = FindRootItems(); }			

	// set current time
	auto current_time = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	// run items with async
	std::vector<std::future<bool>> futures;
	std::for_each(items.begin(), items.end(),
		[this, &futures, current_time](Items::ItemBase* item)
	{
		auto future = std::async(std::launch::async, 
			&Items::ItemBase::Run, item,	// func and instance
			this, nullptr, current_time				// arguments
		);
		futures.push_back(std::move(future));
	});

	// wait futures
	std::vector<bool> results;
	for (auto &future : futures) { results.push_back(future.get()); }

	// set last computed time
	last_computed_time_ = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	return std::all_of(results.begin(), results.end(), [](const bool res) { return res; });
}

//@ !deprecated
//@ runable method
bool Makers::Documents::Document::Run(Document * document, Items::ItemBase * sender, long long timestampe)
{
	// not use
	return false;
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