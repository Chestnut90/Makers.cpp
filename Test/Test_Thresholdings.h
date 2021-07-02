#pragma once

#include <iostream>
#include <chrono>
#include <vector>

namespace Test
{
	namespace Thresholdings
	{
		static long Thresholding(float* _image, unsigned long _width, unsigned long _height, float _threshold,
			unsigned char* destination = nullptr)
		{
			if (destination == nullptr)
			{
				destination = new unsigned char[_width * _height];
			}

			long zero_count = 0;
			bool is_reversed = true;
			unsigned char upper = is_reversed ? 0 : 255;
			unsigned char lower = is_reversed ? 255 : 0;
			for (long y = 0; y < _height; y++)
			{
				long row = y * _width;
				for (long x = 0; x < _width; x++)
				{
					long index = row + x;
					auto value = _image[index] >= _threshold ? upper : lower;
					if (value == 0) zero_count++;
					destination[index] = value;
				}
			}

			return zero_count;
		}

		static void ThresholdingWithoutBuffers(float* _image, bool _is_debug = false)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < 5; i++)
			{
				Thresholding(_image, 5120, 5120, 0.2f);// , buffers[i]);
			}
			auto end = std::chrono::high_resolution_clock::now();
			if (_is_debug)
			{
				std::chrono::duration<double> sec = end - start;
				std::cout << sec.count() << std::endl;
				std::cout << (end - start).count() << std::endl;
			}

		}

		static void ThresholdingWithBuffers(float* _image, bool _is_debug = false)
		{
			// serial with buffers
			std::vector<unsigned char*> buffers;
			for (int i = 0; i < 5; i++)
			{
				unsigned char* buffer = new unsigned char[5120 * 5120];
				buffers.push_back(buffer);
			}

			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < 5; i++)
			{
				Thresholding(_image, 5120, 5120, 0.2f, buffers[i]);
			}
			auto end = std::chrono::high_resolution_clock::now();

			// release memory
			for (auto buffer : buffers)
			{
				delete buffer;
			}

			if (_is_debug)
			{
				std::chrono::duration<double> sec = end - start;
				std::cout << sec.count() << std::endl;
				std::cout << (end - start).count() << std::endl;
			}
		}
	}
}
