#pragma once
#ifndef _ARRAY_MEMORY_POOL_H_
#define _ARRAY__MEMORY_POOL_H_

#include <deque>
#include <mutex>

namespace Makers
{
	namespace MemoryPools
	{
		//@ sealed class -> do not inherit this class
		//@ using circular queue (deque)
		class __declspec(dllexport) ArrayMemoryPool
		{
		private:

			std::mutex access_mutex_;

			std::deque<unsigned int> memory_deque_;
			void** memories_;

			unsigned long count_;
			unsigned long width_;
			unsigned long height_;

		public:

			unsigned long count() const;
			unsigned long width() const;
			unsigned long height() const;
			void* memory();

			void set_count(unsigned long);
			void set_width(unsigned long);
			void set_height(unsigned long);

		public:
			
			//@ constructor width memory infos
			ArrayMemoryPool(unsigned long _width = 0, unsigned long _height = 0, unsigned long _count = 0);
			
			//@ desturctor
			~ArrayMemoryPool();
		
		private:

			//@ allocateMemory
			void AllocateMemory(unsigned long _width, unsigned long _height, unsigned long _count);

		public:

			void Clear();
		
		};


	}
}

#endif // !_ARRAY__MEMORY_POOL_H_
