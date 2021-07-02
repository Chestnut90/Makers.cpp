#pragma once
#ifndef _ARRAY_MEMORY_POOL_H_
#define _ARRAY__MEMORY_POOL_H_

#include <vector>

namespace Makers
{
	namespace MemoryPools
	{
		//@ sealed class -> do not inherit this class
		//@ using circular queue (deque)
		class __declspec(dllexport) ArrayMemoryPool
		{
		private:

			//@ memory access mutex
			//@ for multi-threading
			void* access_mutex_;

			//@ memory allocation mutext
			//@ for async allocation
			void* allocation_mutex_;

			//@ vector for memories
			//@ void pointer initialize with 8byte each data.
			std::vector<void*> memories_;

			//@ current index of memory
			unsigned long memory_index_;

			//@ array width
			unsigned long width_;
			
			//@ array height
			unsigned long height_;

			//@ is allocated
			bool is_allocated_;

		public:

			//@ get current memory index
			unsigned long memory_index() const;
			//@ get memory count
			unsigned long count() const;
			//@ get memory width
			unsigned long width() const;
			//@ get memory height
			unsigned long height() const;
			//@ get is allocated
			bool is_allocated() const;
			//@ get memory 
			void* memory();

		public:
			//@ set width
			void set_width(unsigned long);
			//@ set height
			void set_height(unsigned long);
			//@ set memory count
			void set_count(unsigned long);
		public:
			
			//@ constructor width memory infos
			ArrayMemoryPool(unsigned long _width = 0, unsigned long _height = 0, unsigned long _count = 0);
			
			//@ desturctor
			~ArrayMemoryPool();
		
		public:
			//@ allocateMemory
			void AllocateMemory(unsigned long _width, unsigned long _height, unsigned long _count = -1);
		
		private:
			void _AllocateMemory_Async(unsigned long _width, unsigned long _height, unsigned long _count);
			bool _AllocateMemory_Low(unsigned long _width, unsigned long _height, unsigned long _count);
			bool _AllocateMemory_High(unsigned long _width, unsigned long _height, unsigned long _count);

		public:
			//@ clear memories
			void Clear();

		};


	}
}

#endif // !_ARRAY__MEMORY_POOL_H_
