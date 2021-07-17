#pragma once

#include "../Makers.Pure/Include/Documents/Document.h"
#include "../Makers.Pure/Include/Properties/PropertyBase.h"
#include "../Makers.Pure/Include/Properties/PropertyGroup.h"
#include "../Makers.Pure/Include/Properties/StaticProperty.h"
#include "../Makers.Pure/Include/Properties/OutputProperty.h"
#include "../Makers.Pure/Include/Properties/InputProperty.h"

#include "../Makers.Pure/Include/Computables/Real.h"
#include "../Makers.Pure/Include/Computables/Image.h"

#include "../Makers.Pure/Include/Items/Samples/FloatThresholdingItem.h"
#include "../Makers.Pure/Include/Items/Samples/SampleItem0.h"

using namespace Makers::Items::Samples;
using namespace Makers::Computables;
using Document_ = Makers::Documents::Document;

namespace Test
{
	namespace Instances
	{
		static void Test_FreeDocument()
		{
			Document_* doc = new Document_();

			doc->AddItem(*new Makers::Items::Samples::SampleItem0());

			delete doc;
		}

		static void Test_FreeItem()
		{
			auto sample = new Makers::Items::Samples::SampleItem0();

			delete sample;
			//Makers::Items::ItemFactory().DeleteItem(sample);


		}

		static void Test_FreePropertyGroup()
		{
			auto property_group = new Makers::Properties::PropertyGroup(nullptr);
			auto property = new Makers::Properties::InputProperty("null", nullptr, new Real<int>());
			property_group->AddProperty(property);

			delete property_group;

			if (property != nullptr)
			{


			}

		}

		static void Test_FreePropertyBase()
		{
			auto property = new Makers::Properties::InputProperty("null", nullptr, new Real<int>());


			delete property;
		}

		static void Test_FreeIComputable()
		{
			auto real = new Makers::Computables::Real<int>();
			real->set_value(100);

			delete real;
		}

		static void Test_FreeImageComputable()
		{
			float* a = new float[10];

			auto image = new Makers::Computables::Image<float>();
			image->set_image(a, 10, 1);

			auto image2 = new Makers::Computables::Image<float>();
			image2->set_image(image);

			auto res = dynamic_cast<Makers::Computables::Image<unsigned char>*>(image);

			delete a;
			delete image;
			delete image2;
		}

		static void Test_FreeItemsInDocument()
		{
			Document_* doc = new Document_();

			FloatThreshodingItem* item = new FloatThreshodingItem();
			doc->AddItem(*item);

			// run
			doc->Run_Async();

			doc->RemoveItem(*item);

			delete doc;
		}
	}
}