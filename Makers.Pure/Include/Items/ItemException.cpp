#include "pch.h"
#include "ItemException.h"

Makers::Items::ItemException::ItemException(std::string error) :
	std::exception(error.c_str())
{
}

Makers::Items::ItemException::~ItemException()
{
}
