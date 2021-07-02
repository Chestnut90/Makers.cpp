#include "pch.h"
#include <type_traits>
#include <iostream>
#include <typeinfo>

#include "../../Include/Computables/Image.h"

using namespace Makers::Computables;
#pragma region getters and setters

//@ width
template<typename _image_type>
long Makers::Computables::Image<_image_type>::width() const
{
	return width_;
}

template<typename _image_type>
long Makers::Computables::Image<_image_type>::height() const
{
	return height_;
}

template<typename _image_type>
_image_type * Image<_image_type>::image() const
{
	// TODO: check convertable type.

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
	set_image(nullptr, 0, 0);
}

//@ destructor
template<typename _image_type>
Image<_image_type>::~Image()
{
}

//@ TODO : 
//@ deprecated
template<typename _image_type>
IComputable & Makers::Computables::Image<_image_type>::operator=(IComputable & _computable)
{
	Image<_image_type>* image = reinterpret_cast<Image<_image_type>*>(&_computable);
	if (image == nullptr)
	{
		throw std::exception("Cannot convert to image type instance.");
	}

	set_image(image->image(), image->width(), image->height());
	return *this;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

//@ copy into with deepcopy
//template<typename _image_type>
//void Makers::Computables::Image<_image_type>::CopyInto(IComputable & _computable)
//{
//	Image<_image_type>* image = reinterpret_cast<Image<_image_type>*>(&_computable);
//	if (image == nullptr)
//	{
//		throw std::exception("Cannot convert to image type instance.");
//	}
//
//	if (typeid(this) != typeid(image))
//	{
//		throw std::exception("Invalid copy. different objects");
//	}
//
//	set_image(image->image(), image->width(), image->height());
//}

//@ TODO : 
template<typename _image_type>
std::string Image<_image_type>::ToString()
{
	return /*std::to_string(this) + " " +*/ std::to_string(width_) + " " + std::to_string(height_);
}
