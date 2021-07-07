#pragma once
#ifndef _IMAPABLEDATA_H_
#define _IMAPABLEDATA_H_

#include <map>
#include <string>

namespace Makers
{
	//@ Interface (pure abstract class)
	//@ data with convertable to map 
	class __declspec(dllexport) IMapableData
	{
	public:
		IMapableData();
		virtual ~IMapableData();

	public:
		virtual std::map<std::string, std::string> ToData() = 0;
	};
}

#endif // !_IMAPABLEDATA_H_
