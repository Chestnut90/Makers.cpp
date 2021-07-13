#pragma once
#ifndef _OUTPUTPROPERTY_H_
#define _OUTPUTPROPERTY_H_

#include "PropertyBase.h"
#include "IQueryAbleProperty.h"

namespace Makers
{
	namespace Properties
	{
		//@ Class <OutputProperty>
		//@ output property of item
		//@ Inherit <PropertyBase>
		//@ Inherit <IQueryAbleProperty>
		class __declspec(dllexport) OutputProperty : 
			public PropertyBase, 
			public IQueryAbleProperty
		{
		public:
			//@ constructor
			OutputProperty(
				std::string name, 
				Items::ItemBase* owner_item, 
				Computables::IComputable* data_object, 
				bool is_optional = false);
			
			//@ destructor
			~OutputProperty();

		public:

			//@ query value async
			bool QueryProperty_Async(
				Documents::Document* document, 
				Items::ItemBase* sender = nullptr, 
				long long timestamp = 0) override;

			//@ query value
			bool QueryProperty(
				Documents::Document* document,
				Items::ItemBase* sender = nullptr,
				long long timestamp = 0) override;

			//@ to data
			std::map<std::string, std::string> ToData() override;

		};
	}
}

#endif // !_OUTPUTPROPERTY_H_
