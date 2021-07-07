#pragma once
#ifndef _ROI_H_
#define _ROI_H_

#include "IComputable.h"

namespace Makers
{
	namespace Computables
	{
		class __declspec(dllexport) ROI :
			public IComputable
		{

		public:

			unsigned int left() const;
			unsigned int top() const;
			unsigned int right() const;
			unsigned int bottom() const;

		public:
			void set_left(unsigned int);
			void set_top(unsigned int);
			void set_right(unsigned int);
			void set_bottom(unsigned int);

			void set_roi(
				unsigned int,
				unsigned int,
				unsigned int,
				unsigned int);

		public:
			ROI(
				unsigned int = 0,
				unsigned int = 0,
				unsigned int = 0,
				unsigned int = 0);
			virtual ~ROI();
		
		public:

			bool CanAttachable(IComputable* _computable) override;

			std::string ToString() override;
		};
	}
}

#endif // !_ROI_H_
