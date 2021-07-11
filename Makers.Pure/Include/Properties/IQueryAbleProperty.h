#pragma once
#ifndef _IQUERYABLE_PROPERTY__H_
#define _IQUERYABLE_PROPERTY__H_


namespace Makers
{
	namespace Documents { class Document; }
	namespace Items { class ItemBase; }
	namespace Properties
	{
		//@ Interface of runable property
		//@ class <IRunAbleProperty>
		class __declspec(dllexport) IQueryAbleProperty 
		{

		public:
			//@ constructor
			IQueryAbleProperty();
			
			//@ destructor
			~IQueryAbleProperty();

		public:

			// TODO : arguments
			//@ query property async
			virtual bool QueryProperty_Async(
				Makers::Documents::Document* document,
				Makers::Items::ItemBase* item_base,
				long long time_stamp) = 0;

			//@ query property
			virtual bool QueryProperty(
				Makers::Documents::Document* document,
				Makers::Items::ItemBase* item_base,
				long long timestamp
			) = 0;

		};
	}
}

#endif // !_IQUERYABLE_PROPERTY__H_
