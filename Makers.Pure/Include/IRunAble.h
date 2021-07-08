#pragma once
#ifndef _IRUNABLE_H_
#define _IRUNABLE_H_

#include <string>

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

	//@ compute state
	enum class eComputeState
	{
		None = -1,

		Ready = 0,
		Running = 1,
		Completed = 2,
		Fail = 3,
	};

	//@ interface IRunable
	class __declspec(dllexport) IRunAble
	{
	protected:
		//@ error
		std::string error_;
		//@ is error
		bool is_error_;
		//@ last computed time
		long long last_computed_time_;
		//@ is last computed result
		eComputeState compute_state_;
	
	public:
		//@ get error
		std::string error() const;
		//@ get is error
		bool is_error() const;
		//@ get last computed time
		long long last_computed_time() const;
		//@ get is last computed result
		eComputeState compute_state() const;
	
	public:
		//@ constructor
		IRunAble();
		//@ destructor
		virtual ~IRunAble();

	public:
		
		//@ maker runable function
		virtual bool Run(
			Documents::Document* _document,
			Items::ItemBase* _sender = nullptr,
			long long _timestamp = 0) = 0;
		
		//@ reset error state
		void ResetState();

	};
}

#endif // !_IRUNABLE_H_
