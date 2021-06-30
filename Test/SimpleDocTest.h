#pragma once

#include <iostream>
#include <time.h>
#include <vector>
#include <chrono>

#include "../Makers.Pure/Include/Documents/Document.h"
#include "../Makers.Pure/Include/Items/Samples/FloatThresholdingItem.h"
#include "../Makers.Pure/Include/Items/Samples/RandomFloatImageItem.h"
#include "../Makers.Pure/Include/Properties/PropertyBase.h"
#include "../Makers.Pure/Include/Properties/PropertyGroup.h"
#include "../Makers.Pure/Include/Properties/StaticProperty.h"
#include "../Makers.Pure/Include/Properties/OutputProperty.h"
#include "../Makers.Pure/Include/Properties/InputProperty.h"
#include "../Makers.Pure/Include/Computables/Real.h"
#include "../Makers.Pure/Include/Computables/Image.h"

using namespace Makers;
using namespace Makers::Items::Samples;
using namespace Makers::Computables;

namespace Serials_Test
{
	static float* CreateImage(unsigned long _width, unsigned long _height)
	{
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
		return image;
	}

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

	static void ThresholdingWithoutBuffers(bool is_take_image_creations = false)
	{
		auto start = std::chrono::high_resolution_clock::now();
		auto image = Serials_Test::CreateImage(5120, 5120);
		if (!is_take_image_creations)
		{
			start = std::chrono::high_resolution_clock::now();
		}
		for (int i = 0; i < 5; i++)
		{
			Serials_Test::Thresholding(image, 5120, 5120, 0.2f);// , buffers[i]);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> sec = end - start;
		std::cout << sec.count() << std::endl;
		std::cout << (end - start).count() << std::endl;

		delete image;
	}

	static void ThresholdingWithBuffers(bool is_take_image_creations = false)
	{
		// serial with buffers
		std::vector<unsigned char*> buffers;
		for (int i = 0; i < 5; i++)
		{
			unsigned char* buffer = new unsigned char[5120 * 5120];
			buffers.push_back(buffer);
		}

		auto start = std::chrono::high_resolution_clock::now();
		auto image = Serials_Test::CreateImage(5120, 5120);
		if (!is_take_image_creations)
		{
			start = std::chrono::high_resolution_clock::now();
		}
		for (int i = 0; i < 5; i++)
		{
			Serials_Test::Thresholding(image, 5120, 5120, 0.2f, buffers[i]);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> sec = end - start;
		std::cout << sec.count() << std::endl;
		std::cout << (end - start).count() << std::endl;

		delete image;
		for (auto buffer : buffers)
		{
			delete buffer;
		}
	}
}

namespace Documents_Test
{
	FloatThreshodingItem* CreateFloatThresholdingItem(Properties::OutputProperty* _connection, std::string _custom_name)
	{
		auto thresholding_image = new Makers::Items::Samples::FloatThreshodingItem();
		thresholding_image->set_custom_name(_custom_name);

		auto threshold =
			dynamic_cast<Computables::Real<float>*>(
			(thresholding_image->static_properties())[thresholding_image->kStaticFloatThreshold].data_object());
		threshold->set_value(0.2f);

		auto input_image =
			dynamic_cast<Properties::InputProperty*>(
				&(thresholding_image->input_properties())[thresholding_image->kInputFloatImage]);
		input_image->connected_property_ = _connection;

		return thresholding_image;
	}

	static Documents::Document* CreateDocument(unsigned long _width, unsigned long _height)
	{
		// create items

		// random
		auto random_image_item = new Makers::Items::Samples::RandomFloatImageItem();

		// set width
		auto width =
			dynamic_cast<Computables::Real<unsigned long>*>(
			(random_image_item->static_properties())[random_image_item->kStaticImageWidth].data_object());
		width->set_value(_width);
		// set height
		auto height =
			dynamic_cast<Computables::Real<unsigned long>*>(
			(random_image_item->static_properties())[random_image_item->kStaticImageHeight].data_object());
		height->set_value(_height);

		auto output_random =
			dynamic_cast<Properties::OutputProperty*>(
				&(random_image_item->output_properties())[random_image_item->kOutputFloatImage]);

		// thresholding

		Documents::Document* document = new Documents::Document();
		document->AddItem(random_image_item);
		document->AddItem(CreateFloatThresholdingItem(output_random, "th1"));
		document->AddItem(CreateFloatThresholdingItem(output_random, "th2"));
		document->AddItem(CreateFloatThresholdingItem(output_random, "th3"));
		document->AddItem(CreateFloatThresholdingItem(output_random, "th4"));
		document->AddItem(CreateFloatThresholdingItem(output_random, "th5"));

		return document;
	}

	static std::string ToString_RandomImageItem(Makers::Items::Samples::RandomFloatImageItem& _item)
	{
		std::string result = _item.ToString();

		// static data
		result += "static\n";
		auto data_width = dynamic_cast<Real<unsigned long>*>(_item.static_properties()[_item.kStaticImageWidth].data_object());
		auto width = data_width->value();
		result += "width : " + std::to_string(width) + "\n";
		auto data_height = dynamic_cast<Real<unsigned long>*>(_item.static_properties()[_item.kStaticImageHeight].data_object());
		auto height = data_height->value();
		result += "height : " + std::to_string(height) + "\n";

		// output
		if (width * height < 25)
		{
			auto data_image = dynamic_cast<Image<float>*>(_item.output_properties()[_item.kOutputFloatImage].data_object());
			auto image = data_image->image();
			std::string image_string;
			result += "float image\n";
			for (unsigned long y = 0; y < height; y++)
			{
				for (unsigned long x = 0; x < width; x++)
				{
					long index = y * height + x;
					image_string += std::to_string(image[index]) + " ";
				}
				image_string += "\n";
			}
			result += image_string;
		}
		return result;
	}

	static std::string ToString_ThresholdingItem(Makers::Items::Samples::FloatThreshodingItem& _item)
	{
		std::string result = _item.ToString();

		// static data
		result += "static\n";
		auto data_threshold = dynamic_cast<Real<float>*>(_item.static_properties()[_item.kStaticFloatThreshold].data_object());
		auto threshold = data_threshold->value();
		result += "threshold : " + std::to_string(threshold) + "\n";
		auto data_is_reversed = dynamic_cast<Real<bool>*>(_item.static_properties()[_item.kStaticIsReversed].data_object());
		auto is_reversed = data_is_reversed->value();
		result += "reversed : " + std::to_string(is_reversed) + "\n";

		// output
		result += "\noutput\n";
		auto data_thresholded_image =
			dynamic_cast<Image<unsigned char>*>(_item.output_properties()[_item.kOutputThresholdedImage].data_object());
		auto thresholded_image = data_thresholded_image->image();
		auto width = data_thresholded_image->width();
		auto height = data_thresholded_image->height();

		if (width * height < 25)
		{
			std::string image_string;
			result += "float image\n";
			for (unsigned long y = 0; y < height; y++)
			{
				for (unsigned long x = 0; x < width; x++)
				{
					long index = y * height + x;
					image_string += std::to_string(thresholded_image[index]) + " ";
				}
				image_string += "\n";
			}
			result += image_string;
		}

		// output zero count
		auto data_zero_count =
			dynamic_cast<Real<long>*>((_item.output_properties())[_item.kOutputZeroCount].data_object());
		auto zero_count = data_zero_count->value();
		result += "zero count : " + std::to_string(zero_count);

		return result;
	}

	static void Run_Test()
	{
		auto doc = CreateDocument(5120, 5120);
		auto start = std::chrono::high_resolution_clock::now();

		doc->RunAsync();

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> sec = end - start;
		std::cout << sec.count() << std::endl;
		std::cout << (end - start).count() << std::endl;

		delete doc;
		//// item 0
		//auto randomImageItem = dynamic_cast<Makers::Items::Samples::RandomFloatImageItem*>(doc->SearchItem(0));
		//std::cout << ToString_RandomImageItem(*randomImageItem) << std::endl;

		//// item 1
		//auto thresholdItem = dynamic_cast<Makers::Items::Samples::FloatThreshodingItem*>(doc->SearchItem(1));
		//std::cout << ToString_ThresholdingItem(*thresholdItem) << std::endl;

		//delete doc;
	}
}