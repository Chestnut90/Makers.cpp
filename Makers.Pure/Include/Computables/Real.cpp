#include "pch.h"

#include <typeinfo>

#include "Real.h"

using namespace Makers::Computables;

//@ get value
template<typename _real_type>
_real_type Makers::Computables::Real<_real_type>::value() const
{
	_real_type value = *static_cast<_real_type*>(data_);
	return value;
	//return static_cast<_real_type*>(data_);
}

template<typename _real_type>
void Makers::Computables::Real<_real_type>::set_value(_real_type value)
{
	if (data_ != nullptr)
	{
		delete data_;
	}
	data_ = new _real_type(value);
}

template<typename _real_type>
RealType Makers::Computables::Real<_real_type>::real_type() const
{
	return real_type_;
}

//@ constructor
template<typename _real_type>
Real<_real_type>::Real()
{
	data_ = new _real_type;

	/*if (std::is_same_v(_real_type, char))
	{
		real_type_ = RealType::CHAR;
	}
*/
}

//@ constructor
template<typename _real_type>
Makers::Computables::Real<_real_type>::Real(_real_type value) : Real()
{
	set_value(value);
}

//@ destructor
template<typename _real_type>
Makers::Computables::Real<_real_type>::~Real()
{
}

//@ TODO :
//@ deprecated
template<typename _real_type>
IComputable & Makers::Computables::Real<_real_type>::operator=(IComputable & _computable)
{
	// cast
	Real<_real_type>* real = reinterpret_cast<Real<_real_type>*>(&_computable);
	if (real == nullptr)
	{
		throw std::exception("cannot convert to real type instance.");
	}

	memcpy(data_, real->data_, sizeof(_real_type));
	return *this;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

//@ deep copy into
//template<typename _real_type>
//void Makers::Computables::Real<_real_type>::CopyInto(IComputable & _computable)
//{
//	Real<_real_type>* real = reinterpret_cast<Real<_real_type>*>(&_computable);
//	if (real == nullptr)
//	{
//		throw std::exception("Cannnot convert to real type instance.");
//	}
//
//	if (typeid(this) != typeid(real))
//	{
//		throw std::exception("Invalid copy. different objects");
//	}
//	set_value(real->value());
//}

template<typename _real_type>
bool Makers::Computables::Real<_real_type>::CanAttachable(IComputable * _computable)
{
	return false;
}

//@ TODO :
//@ to string 
template<typename _real_type>
std::string Makers::Computables::Real<_real_type>::ToString()
{
	//std::string to_string = std::to_string(this) + " " + std::to_string(GetValue());
	return "";
}
