#include "pch.h"

#include "../../Include/Documents/ArrayMemoryPool.h"

unsigned long Makers::MemoryPools::ArrayMemoryPool::count() const
{
	return count_;
}

unsigned long Makers::MemoryPools::ArrayMemoryPool::width() const
{
	return width_;
}

unsigned long Makers::MemoryPools::ArrayMemoryPool::height() const
{
	return height_;
}

void * Makers::MemoryPools::ArrayMemoryPool::memory()
{
	// mutex for multi threading
	std::lock_guard<std::mutex> lock(access_mutex_);

	if (memory_deque_.empty()) throw std::exception("Empty memory.");

	// get empty index
	auto index = memory_deque_.front();
	memory_deque_.pop_front();

	// TODO : check reused
	// access memory
	auto memory = memories_[index];

	// push back to circular
	memory_deque_.push_back(index);
	return memory;
}

void Makers::MemoryPools::ArrayMemoryPool::set_count(unsigned long _count)
{
	if (count_ == _count) return;
	count_ = _count;
	AllocateMemory(width_, height_, count_);
}

void Makers::MemoryPools::ArrayMemoryPool::set_width(unsigned long _width)
{
	if (width_ == _width) return;
	width_ = _width;
	AllocateMemory(width_, height_, count_);
}

void Makers::MemoryPools::ArrayMemoryPool::set_height(unsigned long _height)
{
	if (height_ == _height) return;
	height_ = _height;
	AllocateMemory(width_, height_, count_);
}

Makers::MemoryPools::ArrayMemoryPool::ArrayMemoryPool(
	unsigned long _width, 
	unsigned long _height, 
	unsigned long _count)
{
	count_ = _count;
	width_ = _width;
	height_ = _height;
	AllocateMemory(width_, height_, count_);
}

Makers::MemoryPools::ArrayMemoryPool::~ArrayMemoryPool()
{
	Clear();
}

void Makers::MemoryPools::ArrayMemoryPool::AllocateMemory(
	unsigned long _width, 
	unsigned long _height, 
	unsigned long _count)
{
	Clear();
	
	// TODO : calculate available capacity of memory
	// TODO : async

	memories_ = new void*[_count];
	long size = width_ * height_ * sizeof(void*);
	for (int i = 0; i < _count; i++)
	{
		memories_[i] = malloc(size);
		memory_deque_.push_back(i);
	}
}

void Makers::MemoryPools::ArrayMemoryPool::Clear()
{
	for (int i = 0; i < count_; i++)
	{
		delete memories_[i];
		memories_[i] = nullptr;
	}

	delete memories_;
	memories_ = nullptr;

	// deque
	memory_deque_.clear();
}
