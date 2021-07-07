#pragma once
#ifndef _INPUTPROPERTY_H_
#define _INPUTPROPERTY_H_

#include "PropertyBase.h"
#include "../IRunAble.h"

namespace Makers
{
	namespace Properties
	{
		class PropertyBase;

		class __declspec(dllexport) InputProperty : 
			public PropertyBase,
			public IRunAble
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
			void set_connected_property(PropertyBase* _connected_property);

		public:
			//@ default contructor
			InputProperty(
				std::string _name, 
				Items::ItemBase* _owner_item,
				Computables::IComputable* _data_object, 
				bool _is_optional = false);

			//@ default destructor
			~InputProperty();

		public:
			//@ query value -> overrided
			bool Run(
				Documents::Document* _document,
				Items::ItemBase* _sender = nullptr,
				long long _timestamp = 0) override;

			//@ to data -> overrided
			std::map<std::string, std::string> ToData() override;

		};
	}
}

#endif // !_INPUTPROPERTY_H_
