#include "pch.h"
#include <iostream>
#include <typeinfo>

#include "Image.h"

using namespace Makers::Computables;
#pragma region getters and setters

//@ get width
template<typename _image_type>
long Makers::Computables::Image<_image_type>::width() const
{
	return width_;
}

//@ get height
template<typename _image_type>
long Makers::Computables::Image<_image_type>::height() const
{
	return height_;
}

//@ get image
template<typename _image_type>
_image_type * Image<_image_type>::image() const
{
	return static_cast<_image_type*>(data_);
}

template<typename _image_type>
void Image<_image_type>::set_image(_image_type * _image, long _width, long _height)
{
	if (data_ != nullptr)
	{
		delete (_image_type*)data_;

		//free(data_);
		data_ = nullptr;
	}

	width_ = _width;
	height_ = _height;

	data_ = new _image_type[width_ * height_];
	memcpy(data_, (void*)_image, width_ * height_ * sizeof(_image_type));
}

template<typename _image_type>
void Makers::Computables::Image<_image_type>::set_image(Image<_image_type>* _image)
{
	set_image(_image->image(), _image->width_, _image->height_);
}

#pragma endregion

//@ constructor
template<typename _image_type>
Image<_image_type>::Image() : 
	IComputable()
{
	_SetComputableType();
	set_image(nullptr, 0, 0);
}

//@ destructor
template<typename _image_type>
Image<_image_type>::~Image()
{
}

template<typename _image_type>
void Makers::Computables::Image<_image_type>::_SetComputableType()
{
	if (typeid(unsigned char) == typeid(_image_type))
	{
		computable_type_ = eComputableType::Image_Byte;
		return;
	}
	if (typeid(float) == typeid(_image_type))
	{
		computable_type_ = eComputableType::Image_Float;
		return;
	}
	if (typeid(double) == typeid(_image_type))
	{
		computable_type_ = eComputableType::Image_Double;
		return;
	}
}

template<typename _image_type>
bool Makers::Computables::Image<_image_type>::CanAttachable(IComputable * computable)
{
	computable->computable_type();
	return false;
}

template<typename _image_type>
std::string Image<_image_type>::ToString()
{
	return "float image " + std::to_string(width_) + " x " + std::to_string(height_);
}
