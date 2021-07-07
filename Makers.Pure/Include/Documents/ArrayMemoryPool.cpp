#include "pch.h"

#include <future>

#include "ArrayMemoryPool.h"

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
			const std::string error = "initialize memory before usage.\nempty!.";
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


	// init memories
	AllocateMemory(_width, _height, _count);
}

//@ destructor
Makers::MemoryPools::ArrayMemoryPool::~ArrayMemoryPool()
{
	if (access_mutex_ != nullptr)
	{
		delete access_mutex_;
		access_mutex_ = nullptr;
	}

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

	if (_count == -1) _count = count();
	_AllocateMemory_Async(_width, _height, _count);
}

//@ allocate memories with async
void Makers::MemoryPools::ArrayMemoryPool::_AllocateMemory_Async(
	unsigned long _width,
	unsigned long _height,
	unsigned long _count)
{
	// same size
	if (_width == width_ && _height == height_ && _count == count())
	{
		return;
	}
	// just different number
	else if (_width == width_ && _height == height_)
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
