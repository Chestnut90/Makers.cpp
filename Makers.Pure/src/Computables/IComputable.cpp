#include "pch.h"
#include "../../Include/Computables/IComputable.h"

void * Makers::Computables::IComputable::data() const
{
	return data_;
}

Makers::Computables::IComputable::IComputable()
{

}

Makers::Computables::IComputable::~IComputable()
{
	if (data_ != nullptr)
	{
		//free(data_);
		delete data_;
	}
}
