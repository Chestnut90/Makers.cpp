#include "pch.h"
#include "IComputable.h"

//@ get data type
Makers::Computables::eInstanceType Makers::Computables::IComputable::instance_type() const
{
	return instance_type_;
}

//@ get literal type
Makers::Computables::eDataType Makers::Computables::IComputable::data_type() const
{
	return data_type_;
}

//@ constructor
Makers::Computables::IComputable::IComputable()
{
	instance_type_ = eInstanceType::None;
	data_type_ = eDataType::Void;
}

//@ destructor
Makers::Computables::IComputable::~IComputable()
{
}

//@ instance type to string
std::string Makers::Computables::IComputable::InstanceType() const
{
	switch (instance_type_)
	{
	case eInstanceType::None:
		return "None";
	case eInstanceType::Image:
		return "Image";
	case eInstanceType::ImagePointer:
		return "ImagePointer";
	case eInstanceType::Real:
		return "Real";
	case eInstanceType::ROI:
		return "ROI";
	case eInstanceType::Combo:
		return "Combo";
	}
	throw std::exception("not defined instance type");
}

//@ data type to string
std::string Makers::Computables::IComputable::DataType() const
{
	switch (data_type_)
	{
	case eDataType::None:
		return "None";
	case eDataType::Void:
		return "Void";
	case eDataType::Bool:
		return "Bool";
	case eDataType::Byte:
		return "Byte";
	case eDataType::Int:
		return "Int";
	case eDataType::Long:
		return "Long";
	case eDataType::Float:
		return "Float";
	case eDataType::Double:
		return "Double";
	case eDataType::String:
		return "String";
	}
	throw std::exception("not defined data type");
}

