#pragma once
#ifndef _IMAGE_POINTER_H_
#define _IMAGE_POINTER_H_

#include "IComputable.h"

namespace Makers
{
	namespace Computables
	{
		template <typename _image_type>
		class __declspec(dllexport) ImagePointer :
			public IComputable
		{
		private:
			//@ array_pool_pointer
			void* array_pool_pointer_;

		protected:
			//@ width
			long width_;
			//@ height
			long height_;

		public:
			//@ get width
			long width() const;
			//@ get height
			long height() const;
			//@ get image
			_image_type* image() const;
			
		public:
			//@ set buffer
			void set_buffer(void* _buffer, unsigned long _width, unsigned long _height);

		public:
			//@ constructor
			ImagePointer();
			//@ destructor
			virtual ~ImagePointer();

		private:

			//@ set data type
			void _SetDataType();

		public:
			
			//@ Can attach input to this
			bool CanAttachInto(IComputable* _computable) override;
			//@ To String
			virtual std::string ToString() override;
		};

		// template classes for dll exports

		//template class ImagePointer<char>;
		template class ImagePointer<unsigned char>;
		
		//template class ImagePointer<int>;
		//template class ImagePointer<unsigned int>;

		//template class ImagePointer<long>;
		//template class ImagePointer<unsigned long>;

		template class ImagePointer<float>;
		template class ImagePointer<double>;
	}
}

#endif // !_IMAGE_POINTER_H_
