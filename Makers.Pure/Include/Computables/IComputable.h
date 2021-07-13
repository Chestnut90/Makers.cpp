#pragma once
#ifndef _ICOMPUTABLE_H_
#define _ICOMPUTABLE_H_

#include <string>

namespace Makers
{
	namespace Computables
	{
		enum class eInstanceType : int
		{
			None = -1,

			Image = 0,
			Real = 1,
			ROI = 2,
			Enum = 3,
		};

		enum class eDataType :int
		{
			None = -1,

			Void = 0,
			Bool = 1,
			Byte = 2,
			Int = 3,
			Long = 4,
			Float = 5,
			Double = 6,
			String = 7,
		};

		//@ interface of data
		class __declspec(dllexport) IComputable
		{
		protected:
			//@ intance type of IComputable
			eInstanceType instance_type_;
			//@ data type 
			eDataType data_type_;

		public:
			//@ get computable type
			eInstanceType instance_type() const;
			//@ get data literal
			eDataType data_type() const;

		public:
			//@ constructor
			IComputable();
			//@ destructor
			virtual ~IComputable();

		public:
			//@ instance type to string
			std::string InstanceType() const;
			//@ data type to string
			std::string DataType() const;

		public:
			//@ Can attach input to this
			virtual bool CanAttachInto(IComputable* _computable) = 0;
			//@ To string
			virtual std::string ToString() = 0;
		};
	}
}

#endif // !_ICOMPUTABLE_H_
