#pragma once
#ifndef _STREAM_RBG_ITEM_H_
#define _STREAM_RBG_ITEM_H_

#include "../ItemBase.h"

namespace Makers
{
	namespace Items
	{
		namespace Streams
		{
			//@ Class <StreamRGBItem>
			//@ zmap scale image interface with document
			class __declspec(dllexport) StreamRGBItem :
				public ItemBase
			{
			public:
				const std::string kOutputRed = "Red";
				const std::string kOutputGreen = "Green";
				const std::string kOutputBlue = "Blue";

			public:
				StreamRGBItem();
				~StreamRGBItem();

			protected:

				std::string SetItemName() override;
				Compute SetCompute() override;
				Properties::PropertyGroup* SetInputProperties() override;
				Properties::PropertyGroup* SetStaticProperties() override;
				Properties::PropertyGroup* SetOutputProperties() override;


			};
		}
	}
}

#endif // !_STREAM_RBG_ITEM_H_
