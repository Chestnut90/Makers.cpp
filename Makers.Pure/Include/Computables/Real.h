#pragma once
#ifndef _REALS_H_
#define _REALS_H_

#include "IComputable.h"

namespace Makers
{
	namespace Computables
	{
		//@ Class <Real>
		//@ template class for literal type
		//@ Inherit <IComputable>
		template <typename _real_type>
		class __declspec(dllexport) Real :
			public IComputable
		{
		private:
			//@ value
			_real_type value_;

		public:
			//@ get value
			_real_type value() const;
			//@ set value
			void set_value(_real_type value);

		public:
			//@ Constructor
			Real();
			//@ Constructor with value
			Real(_real_type value);
			//@ destructor
			virtual ~Real();

		private:
			//@ set data type
			void _SetDataType();

		public:
			//@ Can attach input to this
			bool CanAttachInto(IComputable* computable) override;
			//@ To string
			std::string ToString() override;
		};

		template class Real<bool>;

		//template class Real<char>;
		template class Real<unsigned char>;

		template class Real<int>;
		//template class Real<unsigned int>;

		template class Real<long>;
		//template class Real<unsigned long>;

		template class Real<float>;
		template class Real<double>;

		
	}
}

#endif // !_REALS_H_
