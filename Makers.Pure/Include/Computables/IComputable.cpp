#include "pch.h"
#include "IComputable.h"

Makers::Computables::eComputableType Makers::Computables::IComputable::computable_type() const
{
	return computable_type_;
}

void * Makers::Computables::IComputable::data() const
{
	return data_;
}

Makers::Computables::IComputable::IComputable()
{
	computable_type_ = eComputableType::IComputable;
}

Makers::Computables::IComputable::~IComputable()
{
	if (data_ != nullptr)
	{
		//free(data_);
		delete data_;
	}
}
