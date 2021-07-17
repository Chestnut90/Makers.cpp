#pragma once
#ifndef _ITEM_EXCEPTION_H_
#define _ITEM_EXCEPTION_H_

#include <iostream>

namespace Makers
{
	namespace Items
	{
		class ItemBase;
		//@ Class <ItemException>
		class __declspec(dllexport) ItemException :
			public std::exception
		{
		public:
			ItemException(std::string);
			~ItemException();
		};
	}
}

#endif // !_ITEM_EXCEPTION_H_
