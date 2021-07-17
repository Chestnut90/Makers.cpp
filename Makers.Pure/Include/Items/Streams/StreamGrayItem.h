#pragma once
#ifndef _STREAM_GRAY_ITEM_H_
#define _STREAM_GRAY_ITEM_H_

#include "../ItemBase.h"

namespace Makers
{
	namespace Items
	{
		namespace Streams
		{
			//@ Class <StreamGrayItem>
			//@ Gray scale image interface with document
			class __declspec(dllexport) StreamGrayItem :
				public ItemBase
			{
			public:
				const std::string kOutputGrayImage = "Gray";

			public:
				StreamGrayItem();
				~StreamGrayItem();

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

#endif // !_STREAM_GRAY_ITEM_H_
