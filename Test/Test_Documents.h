#pragma once

#include <iostream>
#include <vector>
#include <chrono>

#include "../Makers.Pure/Include/Documents/Document.h"
#include "../Makers.Pure/Include/Properties/PropertyBase.h"
#include "../Makers.Pure/Include/Properties/PropertyGroup.h"
#include "../Makers.Pure/Include/Properties/StaticProperty.h"
#include "../Makers.Pure/Include/Properties/OutputProperty.h"
#include "../Makers.Pure/Include/Properties/InputProperty.h"

#include "../Makers.Pure/Include/Computables/Real.h"
#include "../Makers.Pure/Include/Computables/Image.h"

#include "../Makers.Pure/Include/Items/Streams/StreamZmapItem.h"
#include "../Makers.Pure/Include/Items/Samples/FloatThresholdingItem.h"
#include "../Makers.Pure/Include/Items/Samples/SampleItem0.h"

#include "../Makers.Pure/Include/nxSurfs/Surf.h"

using namespace Makers;
using namespace Makers::Items::Samples;
using namespace Makers::Computables;

using Document_ = Makers::Documents::Document;

namespace Test
{
	namespace Documents
	{
		FloatThreshodingItem* CreateFloatThresholdingItem(
			Properties::OutputProperty* _connection, 
			std::string _custom_name)
		{
			auto thresholding_image = new Makers::Items::Samples::FloatThreshodingItem();
			thresholding_image->set_custom_name(_custom_name);

			auto threshold =
				dynamic_cast<Computables::Real<float>*>(
					thresholding_image->static_properties()->
					QueryPropertyName(thresholding_image->kStaticFloatThreshold)->data_object());
			threshold->set_value(0.2f);

			auto threshold_reverse =
				dynamic_cast<Computables::Real<bool>*>(
					thresholding_image->static_properties()->
					QueryPropertyName(thresholding_image->kStaticIsReversed)->data_object());
			threshold_reverse->set_value(true);

			auto input_image =
				dynamic_cast<Properties::InputProperty*>(
					thresholding_image->input_properties()->
					QueryPropertyName(thresholding_image->kInputFloatImage));
			input_image->connected_property_ = _connection;

			return thresholding_image;
		}

		static Document_* CreateDocument()
		{
			// create document
			Document_* document = new Document_();

			// streams
			auto stream_image_item = new Makers::Items::Streams::StreamZmapItem();

			auto output_stream_image_property =
				dynamic_cast<Properties::OutputProperty*>(
					stream_image_item->output_properties()->
					QueryPropertyName(stream_image_item->kOutputZmap));

			// add items
			document->AddItem(*stream_image_item);
			document->AddItem(*CreateFloatThresholdingItem(output_stream_image_property, "th1"));
			document->AddItem(*CreateFloatThresholdingItem(output_stream_image_property, "th2"));
			document->AddItem(*CreateFloatThresholdingItem(output_stream_image_property, "th3"));
			document->AddItem(*CreateFloatThresholdingItem(output_stream_image_property, "th4"));
			document->AddItem(*CreateFloatThresholdingItem(output_stream_image_property, "th5"));

			return document;
		}

		static std::string ToString_ThresholdingItem(Makers::Items::Samples::FloatThreshodingItem& _item)
		{
			std::string result = _item.ToString();

			// static data
			result += "static\n";
			auto data_threshold = dynamic_cast<Real<float>*>(
				_item.static_properties()->QueryPropertyName(_item.kStaticFloatThreshold)->data_object());
			auto threshold = data_threshold->value();
			result += "threshold : " + std::to_string(threshold) + "\n";
			auto data_is_reversed = dynamic_cast<Real<bool>*>(
				_item.static_properties()->QueryPropertyName(_item.kStaticIsReversed)->data_object());
			auto is_reversed = data_is_reversed->value();
			result += "reversed : " + std::to_string(is_reversed) + "\n";

			// output
			result += "\noutput\n";
			auto data_thresholded_image = dynamic_cast<Image<unsigned char>*>(
				_item.output_properties()->QueryPropertyName(_item.kOutputThresholdedImage)->data_object());
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
			auto data_zero_count = dynamic_cast<Real<long>*>(
				_item.output_properties()->QueryPropertyName(_item.kOutputZeroCount)->data_object());
			auto zero_count = data_zero_count->value();
			result += "zero count : " + std::to_string(zero_count);

			return result;
		}

		static void Run_Test(float* _image, unsigned long _width, unsigned long _height)
		{
			auto doc = CreateDocument();
			auto start = std::chrono::high_resolution_clock::now();

			doc->surf().Load("E:\\Test\\SDK.NET\\sample.surf");
			doc->Run_Async();

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> sec = end - start;
			std::cout << sec.count() << std::endl;
			std::cout << (end - start).count() << std::endl;

			for (int i = 0; i < 6; i++)
			{
				auto item = doc->SearchItem(i);
				std::cout << item->item_name() << ", "<< item->custom_name() << ", " << item->last_computed_time() << std::endl;
			
				auto thresholding_item = dynamic_cast<Makers::Items::Samples::FloatThreshodingItem*>(item);
				if (thresholding_item != nullptr)
				{
					auto com_zero_count = dynamic_cast<Makers::Computables::Real<long>*>(
						thresholding_item->output_properties()->
						QueryPropertyName(thresholding_item->kOutputZeroCount)->data_object());
					std::cout << "zero count : " << com_zero_count->value() << std::endl;
				}
			}

			delete doc;
		}
		
	}
}
