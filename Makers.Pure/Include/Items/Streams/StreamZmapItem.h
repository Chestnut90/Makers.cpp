#pragma once
#ifndef _STREAM_ZMAP_ITEM_H_
#define _STREAM_ZMAP_ITEM_H_

#include "../ItemBase.h"

namespace Makers
{
	namespace Items
	{
		namespace Streams
		{
			//@ Class <StreamZmapItem>
			//@ zmap scale image interface with document
			class __declspec(dllexport) StreamZmapItem :
				public ItemBase
			{
			public:
				const std::string kOutputZmap = "Zmap";

			public:
				StreamZmapItem();
				~StreamZmapItem();

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

#endif // !_STREAM_ZMAP_ITEM_H_
