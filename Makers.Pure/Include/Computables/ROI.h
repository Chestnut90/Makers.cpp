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
		private:
			//@ left
			long left_;
			//@ top
			long top_;
			//@ right
			long right_;
			//@ bottom
			long bottom_;

		public:
			//@ get left
			long left() const;
			//@ get top
			long top() const;
			//@ get right
			long right() const;
			//@ get bottom
			long bottom() const;

		public:
			//@ set roi
			void set_roi(long, long, long, long);

		public:
			//@ constructor with 0
			ROI();
			//@ constructor
			//@ left - top - right - bottom
			ROI(long, long, long, long);
			//@ destructor
			virtual ~ROI();
		
		public:

			//@ Can attach input to this
			bool CanAttachInto(IComputable* _computable) override;

			//@ To String
			std::string ToString() override;
		};
	}
}

#endif // !_ROI_H_
