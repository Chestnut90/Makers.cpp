#pragma once
#ifndef _ROI_H_
#define _ROI_H_

#include "IComputable.h"

namespace Makers
{
	namespace Computables
	{
		//@ Class <ROI>
		//@ Computable roi
		//@ Inherit <IComputable>
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
			//@ constructor 
			//@ default, init with 0
			ROI();
			//@ constructor
			//@ left - top - right - bottom
			ROI(long, long, long, long);
			//@ destructor
			virtual ~ROI();
		
			// implement <IComputable> abstract functions
		public:
			//@ Can attach input to this
			bool CanAttachInto(IComputable* computable) override;
			//@ To string
			std::string ToString() override;

			// override virtual functions <IMapableData>
		public:
			//@ To data
			std::map<std::string, std::string> ToData() override;
		};
	}
}

#endif // !_ROI_H_
