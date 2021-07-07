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

//@ get last computed time 
long long Makers::Items::ItemBase::last_computed_time() const
{
	return last_computed_time_;
}

//@ get last computed result
bool Makers::Items::ItemBase::is_last_computed_result() const
{
	return is_last_computed_result_;
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
void Makers::Items::ItemBase::set_custom_name(std::string _name)
{
	custom_name_ = _name;
}

//@ set document
void Makers::Items::ItemBase::set_document(Makers::Documents::Document* _document)
{
	document_ = _document;
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
	last_computed_time_ = 0.0; 
	is_last_computed_result_ = false;
	document_ = nullptr; // user defined
	
	// mutex and lock
	std::mutex* mutex = new std::mutex();
	wait_mutex_ = (void*)mutex;
	
	buffer_counts_ = 0;
	// properties
	// input_properties_ = new Properties::PropertyGroup();
	// static_properties_ = new Properties::PropertyGroup();
	// output_properties_ = new Properties::PropertyGroup();
}

//@ constructor with setters
Makers::Items::ItemBase::ItemBase(
	std::string _item_name, 
	Compute _compute, 
	Properties::PropertyGroup * _input_properties, 
	Properties::PropertyGroup * _static_properties, 
	Properties::PropertyGroup * _output_properties) :
	ItemBase()
{
	item_name_ = _item_name;
	compute_ = _compute;
	input_properties_ = _input_properties;
	input_properties_->owner_item_ = this;
	static_properties_ = _static_properties;
	static_properties_->owner_item_ = this;
	output_properties_ = _output_properties;
	output_properties_->owner_item_ = this;
}

//@ TODO :?
//@ protected or public destructor
Makers::Items::ItemBase::~ItemBase()
{
	compute_ = nullptr;
	delete input_properties_;
	delete static_properties_;
	delete output_properties_;
	if (wait_mutex_ != nullptr)
	{
		delete wait_mutex_;
	}
	// delete document_; // not delete
}

//@ item run
bool Makers::Items::ItemBase::Run(
	Documents::Document * _document, 
	ItemBase * _caller, 
	long long _timestamp)
{
	auto wait_mutex = std::move((std::mutex*)wait_mutex_);
	std::lock_guard<std::mutex> lock(*wait_mutex);
	{	// lock scope

		if (_timestamp == 0.0)
		{
			auto now = std::chrono::high_resolution_clock::now();
			auto current_long_long = now.time_since_epoch().count();
			_timestamp = current_long_long;
		}

		// not computed yet
		if (last_computed_time_ < _timestamp)
		{
			is_last_computed_result_ = false;

			// collect inputs
			if (CollectInputs(_document, _caller, _timestamp))
			{
				// set buffer
				buffers_.clear();
				for (int i = 0; i < buffer_counts_; i++)
				{
					buffers_.push_back(_document->memory_pool()->memory());
				}

				// compute
				if (compute_ == nullptr) { throw std::exception("compute nullptr error"); }
				is_last_computed_result_ = compute_(this, input_properties_, static_properties_, output_properties_);
			}
			// set current time
			last_computed_time_ = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		}
	}	// lock released automatically
	return is_last_computed_result_;
}

//@ collect data from input properties
bool Makers::Items::ItemBase::CollectInputs(
	Documents::Document * _document, 
	ItemBase * _caller, 
	long long _timestamp)
{
	// create futures
	std::vector<std::future<bool>> futures;
	std::for_each(input_properties_->Begin(), input_properties_->End(),
		[&futures, &_document, &_caller, &_timestamp](std::pair<std::string, Properties::PropertyBase*> pair)
	{
		// cast to input property
		auto input_property = dynamic_cast<Properties::InputProperty*>(pair.second);
		if (input_property == nullptr)
		{
			return false;
		}

		// launch task with async
		auto future = std::async(std::launch::async,
			&Properties::InputProperty::Run, input_property, // call func and instance
			_document, _caller, _timestamp);
		futures.push_back(std::move(future));
	});

	// wait all
	std::vector<bool> input_result_collection;
	for (auto &future : futures)
	{
		input_result_collection.push_back(future.get());
	}

	// check all results
	bool total_result = true;
	for (auto result : input_result_collection)
	{
		total_result &= result;
	}

	return total_result;
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
