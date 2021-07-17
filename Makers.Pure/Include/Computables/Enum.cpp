#include "pch.h"
#include "Enum.h"

//@ get name
std::string Makers::Computables::Enum::name() const
{
	return name_;
}

//@ get selected index
int Makers::Computables::Enum::selected_index() const
{
	return selected_index_;
}

//@ get selected string
std::string Makers::Computables::Enum::selected_value() const
{
	return enumerations_.at(selected_index());
}

//@ get all enumeration list
std::vector<std::string> Makers::Computables::Enum::enumeration() const
{
	return enumerations_;
}

//@ set selected index
//@ exception : out of range
void Makers::Computables::Enum::set_selected_index(int index)
{
	if (index < 0 || Count() <= index)
	{
		throw std::exception("out of range index in enumerations In Enum class.");
	}

	selected_index_ = index;
}

//@ default constructor
Makers::Computables::Enum::Enum() :
	IComputable()
{
	instance_type_ = eInstanceType::Enum;
	data_type_ = eDataType::String;
	enumerations_.resize(0);
	selected_index_ = -1;
	name_ = "";
}

//@ contructor with enumeration
Makers::Computables::Enum::Enum(std::vector<std::string> enumeration) :
	Enum()
{
	enumerations_ = enumeration;
	selected_index_ = 0;
}

//@ contructor with name and enumeration
Makers::Computables::Enum::Enum(
	std::string name, 
	std::vector<std::string> enumeration) :
	Enum(enumeration)
{
	name_ = name;
}

//@ destructor
Makers::Computables::Enum::~Enum()
{
}

//@ max count of enumeration
int Makers::Computables::Enum::Count() const
{
	return enumerations_.size();
}

//@ Can attach input to this
bool Makers::Computables::Enum::CanAttachInto(IComputable * computable)
{
	// internal computable object
	return false;
}

//@ To string
std::string Makers::Computables::Enum::ToString()
{
	return "<class Enum> " + name() + ", "+ enumerations_.at(selected_index_);
}

//@ To data
std::map<std::string, std::string> Makers::Computables::Enum::ToData()
{
	auto data = IComputable::ToData();

	// selected index to string
	data["SelectedIndex"] = std::to_string(selected_index_);
	// selected value
	data["SelectedValue"] = selected_value();

	return data;
}
