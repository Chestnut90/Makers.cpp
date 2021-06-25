#pragma once
#ifndef _ITEMBASE_H_
#define _ITEMBASE_H_

#include <memory>
#include "../IMapableData.h"
#include "../IRunAble.h"

namespace Makers
{
	// forward declaration
	namespace Documents { __declspec(dllexport) class Document; }
	namespace Properties { __declspec(dllexport) class PropertyGroup; }

	namespace Items
	{
		//@ computing method
		__declspec(dllexport) typedef bool(*Compute)(
			ItemBase& _reference,
			Properties::PropertyGroup& _input_properties,
			Properties::PropertyGroup& _static_properties,
			Properties::PropertyGroup& _output_properties);

		class __declspec(dllexport) ItemBase :
			public IMapableData,
			public IRunAble
		{
			//@ access all of ItemBase
			friend class ItemFactory;
		public:
			
#pragma region members

		private:
			//@ unique id
			std::string id_;	
			//@ last computed result
			bool is_last_computed_result_;	

		protected:
			//@ name of item
			std::string item_name_;	
			//@ compute for item.
			Compute compute_;	
			//@ input properties
			Properties::PropertyGroup* input_properties_;	
			//@ static properties
			Properties::PropertyGroup* static_properties_;	
			//@ output properties
			Properties::PropertyGroup* output_properties_;	

		public:
			//@ user defined name
			std::string custom_name_;	
			//@ time for query.
			long long last_computed_time_;

#pragma endregion
#pragma region Getters 
		public:
			std::string id() const;
			std::string item_name() const;
			std::string custom_name() const;
			long long last_computed_time() const;
			bool is_last_computed_result() const;
			Properties::PropertyGroup& input_properties();
			Properties::PropertyGroup& static_properties();
			Properties::PropertyGroup& output_properties();

#pragma endregion
#pragma region Setters
		public:
			void set_custom_name(std::string _name);
#pragma endregion
#pragma region Constructor & Destructors

		protected:
			//@ constructor (default)
			ItemBase();

			//@ contructor with data
			ItemBase(
				std::string _item_name,
				Compute _compute,
				Properties::PropertyGroup* _input_properties,
				Properties::PropertyGroup* _static_properties,
				Properties::PropertyGroup* _output_properties);

			//@ destructor (default)
			virtual ~ItemBase();

#pragma endregion

		// implemented in inherited item
		private:
			//virtual ItemBase* CreateItem() = 0;

		protected:
			virtual std::string SetItemName() = 0;
			virtual Compute SetCompute() = 0;
			virtual Properties::PropertyGroup* SetInputProperties() = 0;
			virtual Properties::PropertyGroup* SetStaticProperties() = 0;
			virtual Properties::PropertyGroup* SetOutputProperties() = 0;
#pragma region Runable

		public:
			//@ run
			virtual bool Run(
				Documents::Document* _document, 
				Items::ItemBase* _sender = nullptr, 
				long long _timestamp = 0) override;

		private:
			//@ collect inputs
			bool CollectInputs(
				Documents::Document* _document, 
				ItemBase* _caller, 
				long long _timestamp);

#pragma endregion

		public:
			//@ to data -> overrided
			virtual std::map<std::string, std::string> ToData() override;
			//@ to string
			virtual std::string ToString();
		};
	}
}

#endif // !_ITEMBASE_H_
