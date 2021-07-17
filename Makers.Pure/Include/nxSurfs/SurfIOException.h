#pragma once
#ifndef _SURF_IO_EXCEPTION_H_
#define _SURF_IO_EXCEPTION_H_

#include <iostream>

namespace nXSDK
{
	class _declspec(dllexport) SurfIOException :
		public std::exception
	{
	private:

	public:
		SurfIOException(std::string);
		~SurfIOException();


	};

}


#endif // !_SURF_IO_EXCEPTION_H_

