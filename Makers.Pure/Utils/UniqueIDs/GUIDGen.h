#pragma once
#ifndef _GUIDGEN_H_
#define _GUIDGEN_H_

#include <string>

namespace Utils
{
	namespace IDGenerators
	{
		class __declspec(dllexport) GUIDGen
		{
		public:
			static std::string Generate();
		};
	}
}

#endif // !_GUIDGEN_H_
