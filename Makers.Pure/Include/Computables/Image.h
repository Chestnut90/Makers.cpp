#pragma once
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "IComputable.h"

namespace Makers
{
	namespace Computables
	{
		//@ used in input property
		//@ Image class with template
		//@ exported with data type
		template <typename _image_type>
		class __declspec(dllexport) Image :
			public IComputable
		{
		protected:
			//@ width
			long width_;
			//@ height
			long height_;
			//@ image data
			//@ void for type casting
			_image_type* image_;

		public:
			//@ get width
			long width() const;
			//@ get heigh
			long height() const;
			//@ get image
			_image_type* image() const;
			
			//@ set image
			void set_image(_image_type* _image, long _width, long _height);
			//@ set image -> copy
			void set_image(Image<_image_type>* _image);

		public:
			//@ constructor
			Image();
			//@ destructor
			virtual ~Image();

		private:
			//@ set data type
			void _SetDataType();

		public:

			//@ Can attach input to this
			virtual bool CanAttachInto(IComputable* _computable) override;

			//@ To string
			virtual std::string ToString() override;

		};

		// template classes for dll exports

		//template class Image<char>;
		template class Image<unsigned char>;
		
		//template class Image<int>;
		//template class Image<unsigned int>;

		//template class Image<long>;
		//template class Image<unsigned long>;

		template class Image<float>;
		template class Image<double>;
	}
}

#endif // !_IMAGE_H_
