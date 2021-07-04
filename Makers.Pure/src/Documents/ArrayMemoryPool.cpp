#include "pch.h"

#include <future>

#include "../../Include/Documents/ArrayMemoryPool.h"

#pragma region getters

//@ get current memory index
unsigned long Makers::MemoryPools::ArrayMemoryPool::memory_index() const
{
	return memory_index_;
}

//@ get capacity of memories
unsigned long Makers::MemoryPools::ArrayMemoryPool::count() const
{
	return memories_.size();
}

//@ width of each memory
unsigned long Makers::MemoryPools::ArrayMemoryPool::width() const
{
	return width_;
}

//@ height of each memory
unsigned long Makers::MemoryPools::ArrayMemoryPool::height() const
{
	return height_;
}

//@ get is allocated 
//@ all memories were allocated then return true
bool Makers::MemoryPools::ArrayMemoryPool::is_allocated() const
{
	return is_allocated_;
}

//@ get empty memory
void* Makers::MemoryPools::ArrayMemoryPool::memory()
{
	// mutex for multi threading
	void* allocated_memory = nullptr;
	auto access_mutex = (std::mutex*)access_mutex_;
	
	// lock guard
	std::lock_guard<std::mutex> lock(*access_mutex);	
	{
		// empty
		if (count() == 0)
		{
			const std::string error = "cannot access to memory.\nempty!.";
			throw std::exception(error.c_str());
		}

		allocated_memory = memories_.at(memory_index_);
		++memory_index_;
		if (memory_index_ >= count())
		{
			memory_index_ = 0;
		}
	}
	return allocated_memory;
}

#pragma endregion
#pragma region setters

void Makers::MemoryPools::ArrayMemoryPool::set_width(unsigned long _width)
{
	AllocateMemory(_width, height_, count());
}

void Makers::MemoryPools::ArrayMemoryPool::set_height(unsigned long _height)
{
	AllocateMemory(width_, _height, count());
}

void Makers::MemoryPools::ArrayMemoryPool::set_count(unsigned long _count)
{
	AllocateMemory(width_, height_, _count);
}

#pragma endregion

//@ constructor
Makers::MemoryPools::ArrayMemoryPool::ArrayMemoryPool(
	unsigned long _width,
	unsigned long _height,
	unsigned long _count)
{
	// init access mutex
	auto access_mutex = new std::mutex();
	access_mutex_ = (void*)access_mutex;
	
	// init allocation mutex
	auto allocation_mutex = new std::mutex();
	allocation_mutex_ = (void*)allocation_mutex;

	// init memories
	AllocateMemory(_width, _height, _count);
}

//@ destructor
Makers::MemoryPools::ArrayMemoryPool::~ArrayMemoryPool()
{
	if (access_mutex_ != nullptr) { delete access_mutex_; }
	if (allocation_mutex_ != nullptr) { delete allocation_mutex_; }

	Clear();
}

//@ allocate memories
//@ width of image
//@ height of image
//@ number of images
void Makers::MemoryPools::ArrayMemoryPool::AllocateMemory(
	unsigned long _width,
	unsigned long _height,
	unsigned long _count)
{
	auto allocation_mutex = (std::mutex*)allocation_mutex_;
	std::lock_guard<std::mutex> lock(*allocation_mutex);
	{
		// TODO : calculate available capacity of memory

		is_allocated_ = false;

		if (_count == -1) _count = count();
		auto future = std::async(std::launch::async,
			&Makers::MemoryPools::ArrayMemoryPool::_AllocateMemory_Async, this, _width, _height, _count);
		future.get();
	}
	is_allocated_ = true;
}

//@ allocate memories with async
void Makers::MemoryPools::ArrayMemoryPool::_AllocateMemory_Async(
	unsigned long _width, 
	unsigned long _height, 
	unsigned long _count)
{
	// same size
	// just different number
	if (_width == width_ && _height == height_)
	{
		auto res = _count >= count() ?
			_AllocateMemory_High(_width, _height, _count) :
			_AllocateMemory_Low(_width, _height, _count);
	}
	else
	{
		Clear();
		long size = _width * _height * sizeof(void*);
		for (int i = 0; i < _count; i++)
		{
			auto memory = malloc(size);
			memories_.push_back(memory);
		}
	}
	width_ = _width;
	height_ = _height;
}

//@ when resize to less count
bool Makers::MemoryPools::ArrayMemoryPool::_AllocateMemory_Low(
	unsigned long _width, 
	unsigned long _height, 
	unsigned long _count)
{
	auto count = memories_.size();
	auto diff = count - _count;

	for (int i = 0; i < diff; i++)
	{
		auto memory = memories_.at(count - i + 1);
		delete memory;
		memory = nullptr;
	}
	memories_.resize(_count);

	return true;
}

//@ when resize to high count
bool Makers::MemoryPools::ArrayMemoryPool::_AllocateMemory_High(
	unsigned long _width, 
	unsigned long _height, 
	unsigned long _count)
{
	auto count = memories_.size();
	auto diff = _count - count;
	long size = _width * _height * sizeof(void*);
	for (int i = 0; i < diff; i++)
	{
		auto memory = malloc(size);
		memories_.push_back(memory);
	}

	return true;
}

//@ clear all memories
void Makers::MemoryPools::ArrayMemoryPool::Clear()
{
	for (auto memory : memories_)
	{
		delete memory;
	}
	memories_.resize(0);
	memory_index_ = 0;
}
