#pragma once
#ifndef _STATICPROPERTY_H_
#define _STATICPROPERTY_H_

#include "PropertyBase.h"

namespace Makers
{
	namespace Properties
	{
		//@ Class <StaticProperty>
		//@ Static property of item base
		//@ Inherit <PropertyBase>
		class __declspec(dllexport) StaticProperty 
			: public PropertyBase
		{

		public:
			//@ constructor
			StaticProperty(std::string name,
				Items::ItemBase* owner_item,
				Computables::IComputable* data_object,
				bool is_optional = false);
			
			//@ destructor
			~StaticProperty();

		public:

			//@ to data
			std::map<std::string, std::string> ToData() override;

		};
	}
}

#endif // !_STATICPROPERTY_H_
