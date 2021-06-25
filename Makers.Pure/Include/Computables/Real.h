#pragma once
#ifndef _REALS_H_
#define _REALS_H_

#include "IComputable.h"

namespace Makers
{
	namespace Computables
	{
		enum RealType
		{
			CHAR,
			UCHAR,
			INT,
			UINT,
			LONG,
			ULONG,
			FLOAT,
			DOUBLE,
			BOOL,

		};

		// TODO : prevent different template type.
		template <typename _real_type>
		class __declspec(dllexport) Real :
			public IComputable
		{

		private:
			RealType real_type_;

		public:

			_real_type value() const;
			void set_value(_real_type value);
			RealType real_type() const;

		public:
			Real();
			Real(_real_type value);
			virtual ~Real();
		
		private:
			void Check();

		//@ implement
		public:

			virtual IComputable& operator=(IComputable& _computable);

		public:

			//@ deep copy into
			virtual void CopyInto(IComputable& _computable) override;

			std::string ToString() override;
		};

		template class Real<char>;
		//template IComputable& Real<char>::operator=(IComputable& _computable);

		template class Real<unsigned char>;

		template class Real<int>;
		template class Real<unsigned int>;

		template class Real<long>;
		template class Real<unsigned long>;

		template class Real<float>;
		template class Real<double>;

		template class Real<bool>;
		
	}
}

#endif // !_REALS_H_
