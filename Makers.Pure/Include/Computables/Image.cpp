#include "pch.h"
#include <iostream>
#include <typeinfo>

#include "Image.h"

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
_image_type * Makers::Computables::Image<_image_type>::image() const
{
	return image_;
}

//@ set image
template<typename _image_type>
void Makers::Computables::Image<_image_type>::set_image(
	_image_type* image,
	long width,
	long height)
{
	if (is_buffer_)
	{
		image_ = image;
	}
	else
	{
		// empty size
		if (image_ != nullptr)
		{
			delete image_;
			image_ = nullptr;
		}

		// check size difference
		if (width_ != width || height_ != height)
		{
			image_ = new _image_type[width * height];
		}

		// copy image
		memcpy(image_, (void*)image, width * height * sizeof(_image_type));
	}

	// set width and height
	width_ = width;
	height_ = height;
}

//@ set image
//@ copy function
template<typename _image_type>
void Makers::Computables::Image<_image_type>::set_image(Image<_image_type>* image)
{
	set_image(image->image(), image->width_, image->height_);
}

#pragma endregion

//@ constructor
template<typename _image_type>
Makers::Computables::Image<_image_type>::Image() :
	IComputable()
{
	instance_type_ = eInstanceType::Image;	// set data type
	_SetDataType();							// set literal type
	set_image(nullptr, 0, 0);				// init image
	is_buffer_ = false;
}

template<typename _image_type>
Makers::Computables::Image<_image_type>::Image(bool is_buffer) :
	Image()
{
	is_buffer_ = is_buffer;
}

//@ destructor
template<typename _image_type>
Makers::Computables::Image<_image_type>::~Image()
{
	if (!is_buffer_)
	{
		delete image_;
		image_ = nullptr;
	}
}

//@ set data type
template<typename _image_type>
void Makers::Computables::Image<_image_type>::_SetDataType()
{
	if (typeid(unsigned char) == typeid(_image_type))	// check byte
	{
		data_type_ = eDataType::Byte;
		return;
	}
	if (typeid(float) == typeid(_image_type))			// check float
	{
		data_type_ = eDataType::Float;
		return;
	}
	if (typeid(double) == typeid(_image_type))			// check dobule
	{
		data_type_ = eDataType::Double;
		return;
	}
}

//@ Can attach input to this
template<typename _image_type>
bool Makers::Computables::Image<_image_type>::CanAttachInto(IComputable * computable)
{
	if (instance_type_ != computable->instance_type()) return false;

	// if it is buffer then only output.
	return !is_buffer_;
}

//@ to string
template<typename _image_type>
std::string Makers::Computables::Image<_image_type>::ToString()
{
	return "<class Image<" + DataType() + ">> " + std::to_string(width_) + ", " + std::to_string(height_);
}
