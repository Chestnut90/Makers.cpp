#include "pch.h"
#include "SurfIOException.h"

nXSDK::SurfIOException::SurfIOException(std::string error) :
	std::exception(error.c_str())
{

}

nXSDK::SurfIOException::~SurfIOException()
{
}
