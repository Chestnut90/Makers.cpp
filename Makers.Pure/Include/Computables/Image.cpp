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
void Makers::Computables::Image<_image_type>::set_image(_image_type * _image, long _width, long _height)
{
	// empty size
	if (image_ != nullptr)
	{
		delete image_;
		image_ = nullptr;
	}

	// check size difference
	if (width_ != _width || height_ != _height)
	{
		image_ = new _image_type[_width * _height];
	}

	// copy image
	memcpy(image_, (void*)_image, _width * _height * sizeof(_image_type));

	// set width and height
	width_ = _width;
	height_ = _height;
}

//@ set image
//@ copy function
template<typename _image_type>
void Makers::Computables::Image<_image_type>::set_image(Image<_image_type>* _image)
{
	set_image(_image->image(), _image->width_, _image->height_);
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
}

//@ destructor
template<typename _image_type>
Makers::Computables::Image<_image_type>::~Image()
{
	delete image_;
	image_ = nullptr;
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
bool Makers::Computables::Image<_image_type>::CanAttachInto(IComputable * _computable)
{
	if (data_type_ != _computable->data_type()) return false;

	auto data_type = _computable->instance_type();
	// image or image pointer are able to be connected
	if (data_type == eInstanceType::Image || data_type == eInstanceType::ImagePointer) return true;
	return false;
}

//@ to string
template<typename _image_type>
std::string Makers::Computables::Image<_image_type>::ToString()
{
	return "<class Image<" + DataType() + ">> " + std::to_string(width_) + ", " + std::to_string(height_);
}
