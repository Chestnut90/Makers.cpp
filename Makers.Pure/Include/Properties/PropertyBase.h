#pragma once
#ifndef _PROPERTYBASE_H_
#define _PROPERTYBASE_H_

#include "../IMapableData.h"

namespace Makers
{
	namespace Computables { class IComputable; }
	namespace Items { class ItemBase; }
	namespace Properties
	{
		class __declspec(dllexport) PropertyBase : public IMapableData
		{
			friend class ItemBase;

		private:
			//@ id
			std::string id_;
			//@ name
			std::string name_;
			//@ owner item
			Items::ItemBase* owner_item_;
			
		protected:
			//@ data object
			Computables::IComputable* data_object_;
			//@ optional
			bool is_optional_;
		public:
			//@ used
			bool is_used_;

		// getters
		public:
			
			//@ get id
			std::string id() const;
			//@ get name
			std::string name() const;
			//@ get owner item
			Items::ItemBase* owner_item() const;	
			//@ get is optional
			bool is_optional() const;
			//@ get data object
			Computables::IComputable* data_object() const;

		// setters
		public:
			//@ set is used
			void set_is_used(bool _is_used);

		protected:
			PropertyBase(
				std::string _name, 
				Items::ItemBase& _owner_item, 
				Computables::IComputable& _data_object, 
				bool _is_optional = false);
			
		public:
			virtual ~PropertyBase();
		
		public:

			//@ implement IMapableData ToData
			virtual std::map<std::string, std::string> ToData() override;

		};
	}
}

#endif // !_PROPERTYBASE_H_
