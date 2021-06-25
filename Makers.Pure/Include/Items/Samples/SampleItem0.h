#pragma once
#ifndef _SAMPLEITEM0_H_
#define _SAMPLEITEM0_H_

#include "../ItemBase.h"

namespace Makers
{
	namespace Items
	{
		namespace Samples
		{

			class __declspec(dllexport) SampleItem0 :
				public ItemBase
			{

			public:
				SampleItem0();
				~SampleItem0();

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

#endif // !_SAMPLEITEM0_H_
