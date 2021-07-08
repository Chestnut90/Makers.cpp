#include "pch.h"
#include "Combo.h"

//@ get name
std::string Makers::Computables::Combo::name() const
{
	return name_;
}

//@ get selected index
int Makers::Computables::Combo::selected_index() const
{
	return 0;
}

//@ get selected string
std::string Makers::Computables::Combo::selected_value() const
{
	return std::string();
}

//@ get all enumeration list
std::vector<std::string> Makers::Computables::Combo::enumeration() const
{
	return std::vector<std::string>();
}

//@ set selected index
//@ exception : out of range
void Makers::Computables::Combo::set_selected_index(int _index)
{
	if (_index < 0 || Count() <= _index)
	{
		throw std::exception("out of range index in enumerations In Combo class.");
	}

	selected_index_ = _index;
}

//@ contructor with enumeration
Makers::Computables::Combo::Combo(std::vector<std::string> _enumeration) :
	IComputable()
{
	instance_type_ = eInstanceType::Combo;
	data_type_ = eDataType::String;
	enumerations_ = _enumeration;
	name_ = "";
}

//@ contructor with name
Makers::Computables::Combo::Combo(
	std::string _name, 
	std::vector<std::string> _enumeration) :
	Combo(_enumeration)
{
	name_ = _name;
}

//@ destructor
Makers::Computables::Combo::~Combo()
{
}

//@ max count of enumeration
int Makers::Computables::Combo::Count() const
{
	return enumerations_.size();
}

//@ Can attach input to this
bool Makers::Computables::Combo::CanAttachInto(IComputable * _computable)
{
	// internal computable object
	return false;
}

//@ To string
std::string Makers::Computables::Combo::ToString()
{
	return "<class Combo> " + name() + ", "+ enumerations_.at(selected_index_);
}
