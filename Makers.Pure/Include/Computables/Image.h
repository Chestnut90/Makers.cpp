#pragma once
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "IComputable.h"

namespace Makers
{
	namespace Computables
	{
		//@ Class <Image>
		//@ template class for literal image
		//@ Inherit <IComputable>
		template <typename _image_type>
		class __declspec(dllexport) Image :
			public IComputable
		{
		protected:
			//@ is buffer image
			bool is_buffer_;
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
			//@ when is buffer, just point memory location
			void set_image(_image_type* image, long width, long height);
			//@ set image -> copy
			void set_image(Image<_image_type>* image);

		public:
			//@ Constructor 
			//@ with buffer flag
			Image(bool is_buffer = false);
			//@ destructor
			virtual ~Image();

		private:
			//@ set data type
			void _SetDataType();

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
