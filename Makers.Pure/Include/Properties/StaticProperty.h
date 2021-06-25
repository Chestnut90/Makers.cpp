#pragma once
#ifndef _STATICPROPERTY_H_
#define _STATICPROPERTY_H_

#include "PropertyBase.h"

namespace Makers
{
	namespace Properties
	{
		class __declspec(dllexport) StaticProperty : public PropertyBase
		{
		public:
			//@ constructor
			StaticProperty(std::string _name,
				Items::ItemBase& _owner_item,
				Computables::IComputable& _data_object,
				bool _is_optional = false);
			
			//@ destructor
			~StaticProperty();

		public:

			//@ to data
			std::map<std::string, std::string> ToData() override;

		};
	}
}

#endif // !_STATICPROPERTY_H_
