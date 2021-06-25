#pragma once
#ifndef _FACOTRY_REGISTER_H_
#define _FACOTRY_REGISTER_H_

#include "ItemFactory.h"

namespace Makers
{
	namespace Items
	{
		template <typename T>
		class FactoryRegister
		{
		public:
			FactoryRegister(const std::string _name)
			{
				ItemFactory::instance().Register(_name, []()
				{
					return static_cast<ItemBase*>(new T());
				});
			}

			~FactoryRegister()
			{
			}
		};



	}
}

#endif // !_FACOTRY_REGISTER_H_
