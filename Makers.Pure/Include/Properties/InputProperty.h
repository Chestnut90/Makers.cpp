#pragma once
#ifndef _INPUTPROPERTY_H_
#define _INPUTPROPERTY_H_

#include "PropertyBase.h"
#include "IQueryAbleProperty.h"

namespace Makers
{
	namespace Properties
	{
		class PropertyBase;

		//@ class <InputProperty>
		//@ inherit <PropertyBase>
		//@ inherit <IQueryAbleProperty>
		class __declspec(dllexport) InputProperty : 
			public PropertyBase,
			public IQueryAbleProperty
		{
		public:
			//@ connected property
			PropertyBase* connected_property_;

		//@ getter
		public:
			//@ get connected property
			PropertyBase* connected_property() const;

		public:
			//@ set connected property
			void set_connected_property(PropertyBase* connected_property);

		public:
			//@ default contructor
			InputProperty(
				std::string name, 
				Items::ItemBase* owner_item,
				Computables::IComputable* data_object, 
				bool is_optional = false);

			//@ default destructor
			~InputProperty();

		public:
			//@ query value -> overrided
			bool QueryProperty_Async(
				Documents::Document* document,
				Items::ItemBase* sender = nullptr,
				long long timestamp = 0) override;

			//@ query value
			bool QueryProperty(
				Documents::Document* document,
				Items::ItemBase* sender = nullptr,
				long long timestamp = 0) override;

			//@ to data -> overrided
			std::map<std::string, std::string> ToData() override;

		};
	}
}

#endif // !_INPUTPROPERTY_H_
