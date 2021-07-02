#pragma once

#include <iostream>
#include <time.h>
#include <chrono>

namespace Test
{
	namespace RandomImageFloats
	{
		static float* CreateRandomFloatArray(unsigned long _width, unsigned long _height, bool _is_debug = false)
		{
			auto start = std::chrono::high_resolution_clock::now();
			srand((unsigned int)time(NULL));	//seed

			float* image = new float[_width * _height];

			for (unsigned long y = 0; y < _height; y++)
			{
				unsigned long row = y * _width;
				for (unsigned long x = 0; x < _width; x++)
				{
					image[row + x] = ((float)rand() / (float)RAND_MAX);
				}
			}

			auto end = std::chrono::high_resolution_clock::now();
			if (_is_debug)
			{
				std::chrono::duration<double> sec = end - start;
				std::cout << sec.count() << std::endl;
				std::cout << (end - start).count() << std::endl;
			}

			return image;
		}
	}
}
