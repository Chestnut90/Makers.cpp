#include "pch.h"

// standard
#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>
#include <future>
#include <mutex>

#include "../../Include/Items/ItemBase.h"
#include "../../Include/Properties/PropertyGroup.h"
#include "../../Include/Properties/InputProperty.h"

#include "../../Include/Documents/Document.h"
#include "../../Include/Documents/ArrayMemoryPool.h"
#include "../../Utils/UniqueIDs/GUIDGen.h"

#pragma region getter

//@ get id
std::string Makers::Items::ItemBase::id() const
{
	return id_;
}

//@ get item name
std::string Makers::Items::ItemBase::item_name() const
{
	return item_name_;
}

//@ get custom name - user defined
std::string Makers::Items::ItemBase::custom_name() const
{
	return custom_name_;
}

//@ get owner document
Makers::Documents::Document* Makers::Items::ItemBase::document() const
{
	return document_;
}

//@ get input properties
Makers::Properties::PropertyGroup* Makers::Items::ItemBase::input_properties() const
{
	return input_properties_;
}

//@ get static properties
Makers::Properties::PropertyGroup* Makers::Items::ItemBase::static_properties() const
{
	return static_properties_;
}

//@ get output properties
Makers::Properties::PropertyGroup* Makers::Items::ItemBase::output_properties() const
{
	return output_properties_;
}

//@ get buffer counts
int Makers::Items::ItemBase::buffer_count() const
{
	return buffer_counts_;
}
#pragma endregion
#pragma region setters

//@ set custom name
void Makers::Items::ItemBase::set_custom_name(std::string name)
{
	custom_name_ = name;
}

//@ set document
void Makers::Items::ItemBase::set_document(Makers::Documents::Document* document)
{
	document_ = document;
}

#pragma endregion

//@ propected constructor (default)
Makers::Items::ItemBase::ItemBase() :
	IMapableData(),
	IRunAble()
{
	id_ = Utils::IDGenerators::GUIDGen().Generate();
	item_name_ = ""; // TODO : sub class set.
	custom_name_ = "";	// user defined
	compute_ = nullptr;	// sub class
	document_ = nullptr; // user defined

	// mutex and lock
	std::mutex* mutex = new std::mutex();
	wait_mutex_ = (void*)mutex;

	buffer_counts_ = 0;
}

//@ constructor with setters
Makers::Items::ItemBase::ItemBase(
	std::string item_name,
	Compute compute,
	Properties::PropertyGroup* input_properties,
	Properties::PropertyGroup* static_properties,
	Properties::PropertyGroup* output_properties) :
	ItemBase()
{
	item_name_ = item_name;
	compute_ = compute;
	input_properties_ = input_properties;
	static_properties_ = static_properties;
	output_properties_ = output_properties;
}

//@ public destructor
Makers::Items::ItemBase::~ItemBase()
{
	compute_ = nullptr;
	// release input properties
	delete input_properties_;
	input_properties_ = nullptr;

	// release static properties
	delete static_properties_;
	static_properties_ = nullptr;

	// release output properties
	delete output_properties_;
	output_properties_ = nullptr;

	// release mutex
	if (wait_mutex_ != nullptr)
	{
		delete wait_mutex_;
		wait_mutex_ = nullptr;
	}

	// release owner document
	// delete document_; // not delete
	document_ = nullptr;
}

//@ item run
bool Makers::Items::ItemBase::Run(
	Documents::Document* document,
	ItemBase* caller,
	long long timestamp)
{
	auto wait_mutex = std::move((std::mutex*)wait_mutex_);
	std::lock_guard<std::mutex> lock(*wait_mutex);
	{	// lock scope

		if (timestamp == 0.0)
		{
			auto now = std::chrono::high_resolution_clock::now();
			auto current_long_long = now.time_since_epoch().count();
			timestamp = current_long_long;
		}

		// not computed yet
		if (last_computed_time_ < timestamp)
		{
			ResetState();	// reset error state
			compute_state_ = eComputeState::Running;	// set current state to running

			if (CollectInputs(document, caller, timestamp))	// collect inputs
			{
				// TODO : more efficiently
				// set buffer
				buffers_.clear();
				for (int i = 0; i < buffer_counts_; i++)
				{
					buffers_.push_back(document->memory_pool()->memory());
				}

				// compute
				compute_state_ = compute_(this, input_properties_, static_properties_, output_properties_)
					? eComputeState::Completed : eComputeState::Fail;
			}
			// set current time
			last_computed_time_ = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		}
	}	// lock released automatically
	return compute_state_ == eComputeState::Completed;
}

//@ collect data from input properties
bool Makers::Items::ItemBase::CollectInputs(
	Documents::Document * document,
	ItemBase * caller,
	long long timestamp)
{
	// create futures
	std::vector<std::future<bool>> futures;
	std::for_each(input_properties_->Begin(), input_properties_->End(),
		[&futures, &document, &caller, &timestamp](Properties::PropertyBase* property)
	{
		// cast to input property
		auto input_property = dynamic_cast<Properties::InputProperty*>(property);	// not nullptr
		
		// launch task with async
		auto future = std::async(std::launch::async,
			&Properties::InputProperty::QueryProperty_Async, input_property, // call func and instance
			document, caller, timestamp);
		futures.push_back(std::move(future));
	});

	// wait all
	std::vector<bool> future_results;
	for (auto &future : futures)
	{
		try
		{
			future_results.push_back(future.get());
		}
		catch (const std::exception& e)
		{
			// set error string
			error_ += e.what();
			error_ += "\n";
			future_results.push_back(false);
		}
	}

	// check all of result
	return std::all_of(future_results.begin(), future_results.end(), [](bool res) { return res; });
}

//@ to data
std::map<std::string, std::string> Makers::Items::ItemBase::ToData()
{
	std::map<std::string, std::string> data;

	data["ID"] = id_;
	data["ItemName"] = item_name_;
	data["CustomName"] = custom_name_;
	data["InputPropertiesCount"] = std::to_string(input_properties_->Count());
	data["StaticPropertiesCount"] = std::to_string(static_properties_->Count());
	data["OutputPropertiesCount"] = std::to_string(output_properties_->Count());

	return data;
}

//@ to string
std::string Makers::Items::ItemBase::ToString()
{
	std::string result;
	auto data = ToData();
	// TODO : implement with others. such as string builder
	std::for_each(data.begin(), data.end(), [&result](std::pair<std::string, std::string> pair)
	{
		result += pair.first + " : " + pair.second + "\n";
	});

	return result;
}
