#pragma once
#ifndef _OUTPUTPROPERTY_H_
#define _OUTPUTPROPERTY_H_

#include "PropertyBase.h"
#include "../IRunAble.h"

namespace Makers
{
	namespace Properties
	{
		class __declspec(dllexport) OutputProperty : 
			public PropertyBase, 
			public IRunAble
		{
		public:
			//@ constructor
			OutputProperty(
				std::string _name, 
				Items::ItemBase* _owner_item, 
				Computables::IComputable* _data_object, 
				bool _is_optional = false);
			
			//@ destructor
			~OutputProperty();

		public:

			//@ query value
			bool Run(
				Documents::Document* _document, 
				Items::ItemBase* _sender = nullptr, 
				long long _timestamp = 0) override;

			//@ to data
			std::map<std::string, std::string> ToData() override;

		};
	}
}

#endif // !_OUTPUTPROPERTY_H_
