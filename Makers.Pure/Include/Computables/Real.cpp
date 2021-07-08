#include "pch.h"

#include <typeinfo>

#include "Real.h"

using namespace Makers::Computables;

//@ get value
template<typename _real_type>
_real_type Makers::Computables::Real<_real_type>::value() const
{
	return value_;
}

//@ set value
template<typename _real_type>
void Makers::Computables::Real<_real_type>::set_value(_real_type _value)
{
	value_ = _value;
}

//@ constructor
template<typename _real_type>
Real<_real_type>::Real()
{
	instance_type_ = eInstanceType::Real;	// set data type
	_SetDataType();				// set literal type
	value_ = 0;
}

//@ constructor
template<typename _real_type>
Makers::Computables::Real<_real_type>::Real(_real_type _value) : Real()
{
	set_value(_value);
}

//@ destructor
template<typename _real_type>
Makers::Computables::Real<_real_type>::~Real()
{
}

//@ set data type
template<typename _real_type>
void Makers::Computables::Real<_real_type>::_SetDataType()
{
	if (typeid(_real_type) == typeid(bool))				// check bool
	{
		data_type_ = eDataType::Bool;
		return;
	}
	if (typeid(_real_type) == typeid(unsigned char))	// check byte
	{
		data_type_ = eDataType::Byte;
		return;
	}
	if (typeid(_real_type) == typeid(int))				// check int
	{
		data_type_ = eDataType::Int;
		return;
	}
	if (typeid(_real_type) == typeid(long))				// check long
	{
		data_type_ = eDataType::Long;
		return;
	}
	if (typeid(_real_type) == typeid(float))			// check float
	{
		data_type_ = eDataType::Float;
		return;
	}
	if (typeid(_real_type) == typeid(double))			// check double
	{
		data_type_ = eDataType::Double;
		return;
	}
}

template<typename _real_type>
bool Makers::Computables::Real<_real_type>::CanAttachInto(IComputable * _computable)
{
	if (instance_type() != _computable->instance_type()) return false;
	// only same data type
	return data_type() == _computable->data_type();
}

//@ to string 
template<typename _real_type>
std::string Makers::Computables::Real<_real_type>::ToString()
{
	return "<class Real<" + DataType() + ">> " + std::to_string(value_);
}
