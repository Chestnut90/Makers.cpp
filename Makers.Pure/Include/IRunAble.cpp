#include "pch.h"
#include "IRunAble.h"

std::string Makers::IRunAble::error() const
{
	return error_;
}

bool Makers::IRunAble::is_error() const
{
	return error_ != "";
}

long long Makers::IRunAble::last_computed_time() const
{
	return last_computed_time_;
}

Makers::eComputeState Makers::IRunAble::compute_state() const
{
	return compute_state_;
}

Makers::IRunAble::IRunAble()
{
	compute_state_ = eComputeState::None;
	last_computed_time_ = 0;
	error_ = "";
}

Makers::IRunAble::~IRunAble()
{
}

void Makers::IRunAble::ResetState()
{
	error_ = "";
	last_computed_time_ = 0;
	compute_state_ = eComputeState::Ready;
}
