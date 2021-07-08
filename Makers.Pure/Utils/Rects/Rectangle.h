#pragma once
#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include <string>

// TODO : move other namespace
namespace Utils
{
	namespace Rects
	{
		class __declspec(dllexport) Rectangle
		{
		private:

			long left_;
			long top_;
			long right_;
			long bottom_;

		public:

			long left() const;
			long top() const;
			long right() const;
			long bottom() const;

			void set_left(long);
			void set_top(long);
			void set_right(long);
			void set_bottom(long);

		public:
			Rectangle();
			Rectangle(long _left, long _top, long _right, long _bottom);
			~Rectangle();

		public:
			long Width();
			long Height();

		};
	}
}

#endif // !_RECTANGLE_H_
