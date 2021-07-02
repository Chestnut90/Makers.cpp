#pragma once
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "IComputable.h"

namespace Makers
{
	namespace Computables
	{
		template <typename _image_type>
		class __declspec(dllexport) Image :
			public IComputable
		{
		protected:
			long width_;
			long height_;

		public:
			long width() const;
			long height() const;

		public:
			_image_type* image() const;
			void set_image(_image_type* _image, long _width, long _height);
			void set_image(Image<_image_type>* _image);

		public:
			Image();
			virtual ~Image();

		// implement
		// operators
		public:
			virtual IComputable& operator=(IComputable& _computable);

			//template<typename _image_type2>
			//bool operator==(const Image<_image_type2>& _image);
			//
			//template<typename _image_type2>
			//Image& operator=(const Image<_image_type2>& _image);	// copy assignment

		public:

			//virtual void CopyInto(IComputable& _computable) override;

			virtual std::string ToString() override;

		};

		// template classes for dll exports

		template class Image<char>;
		//template __declspec(dllexport) IComputable& Image<char>::operator=(IComputable& _computable);

		template class Image<unsigned char>;
		
		template class Image<int>;
		template class Image<unsigned int>;

		template class Image<long>;
		template class Image<unsigned long>;

		template class Image<float>;
		template class Image<double>;
	}
}

#endif // !_IMAGE_H_
