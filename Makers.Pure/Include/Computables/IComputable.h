#pragma once
#ifndef _ICOMPUTABLE_H_
#define _ICOMPUTABLE_H_

#include <string>

namespace Makers
{
	namespace Computables
	{
		enum class eComputableType : int
		{
			IComputable = -1,

			// Image Type
			Image_Byte = 0,
			Image_Float = 1,
			Image_Double = 2,

			// Image Pointer Type
			Image_Pointer_Byte = 3,
			Image_Pointer_Float = 4,
			Image_Pointer_Double = 5,

			// Real
			Real_Bool = 6,
			Real_Byte = 7,
			Real_Int = 8,
			Real_Float = 9,
			Real_Long = 10,
			Real_Double = 11,
			
			// ROI
			ROI = 12,
		};

		//@ interface of data
		class __declspec(dllexport) IComputable
		{
		protected:
			
			//@ computable type
			eComputableType computable_type_;
			
			//@ rootable data object pointer
			void* data_;

		public:
			
			//@ get computable type
			eComputableType computable_type() const;

			//@ get data
			void* data() const;

		public:
			
			//@ constructor
			IComputable();

			//@ destructor
			virtual ~IComputable();

		public:

			//@ compare types
			virtual bool CanAttachable(IComputable* _computable) = 0;

			//@ To string
			virtual std::string ToString() = 0;

		
		};
	}
}

#endif // !_ICOMPUTABLE_H_
