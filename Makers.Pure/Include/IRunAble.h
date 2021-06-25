#pragma once
#ifndef _IRUNABLE_H_
#define _IRUNABLE_H_

namespace Makers
{
	namespace Documents
	{
		class Document;
	}

	namespace Items
	{
		class ItemBase;
	}

	class __declspec(dllexport) IRunAble
	{
	public:
		IRunAble() {}
		virtual ~IRunAble() {}
	public:

		virtual bool Run(
			Documents::Document* _document,
			Items::ItemBase* _sender = nullptr,
			long long _timestamp = 0) = 0;

	};
}

#endif // !_IRUNABLE_H_
