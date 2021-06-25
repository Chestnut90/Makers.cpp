#pragma once
#ifndef _ICOMPUTABLE_H_
#define _ICOMPUTABLE_H_

#include <string>

namespace Makers
{
	namespace Computables
	{
		//@ interface of data
		class __declspec(dllexport) IComputable
		{
		private:
			// @ TODO : type of data object

		protected:
			//@ rootable data object pointer
			void* data_;

		public:
			inline void* data() const
			{
				return data_;
			}

		public:
			
			//@ constructor
			IComputable() {}

			//@ destructor
			virtual ~IComputable() 
			{
				if (data_ != nullptr)
					delete data_;
			}

		// operators
		public:

			//virtual IComputable& operator=(IComputable& _computable) = 0;

		public:

			virtual void CopyInto(IComputable& _computable) = 0;
			//virtual void DeepCopy(IComputable& _computable) = 0;

			//@ To string
			virtual std::string ToString() = 0;

		
		};
	}
}

#endif // !_ICOMPUTABLE_H_
