#pragma once
#ifndef _PROPERTYGROUP_H_
#define _PROPERTYGROUP_H_

#include <vector>
#include <iterator>

namespace Makers
{
	namespace Computables { class IComputable; }
	namespace Items { class ItemBase; }
	namespace Properties
	{
		//@ type of property
		enum ePropertyType
		{
			eInputProperty,
			eStaticProperty,
			eOutputProperty,
		};

		class PropertyBase;
		
		//@ Class <PropertyGroup>
		//@ container of property base
		class __declspec(dllexport) PropertyGroup
		{
			friend class Makers::Items::ItemBase;

		private:
			//@ properties
			std::vector<PropertyBase*> properties_;
			//@ owner item
			Makers::Items::ItemBase* owner_item_;

		public:
			//@ owner item
			Makers::Items::ItemBase* owner_item() const;

		public:
			//@ constructor
			PropertyGroup(Items::ItemBase* owner_item);
			//@ destructor
			~PropertyGroup();

		public:
			//@ [name] operator
			PropertyBase* operator[](const std::string name);
			//@ count
			int Count();

		public:
			//@ add property with property
			void AddProperty(PropertyBase* property);
			//@ add property with property datas
			PropertyBase* AddProperty(
				std::string name,
				Computables::IComputable* computable,
				bool is_optional,
				ePropertyType property_type);
			
		public:
			//@ map iterator begin
			std::vector<PropertyBase*>::iterator Begin();
			//@ map iterator end
			std::vector<PropertyBase*>::iterator End();

		public:
			// TODO: nullable
			//@ query property with id
			PropertyBase* QueryPropertyID(std::string id);
			//@ query property with name
			PropertyBase* QueryPropertyName(std::string name);

		private:
			//@ clear all properties
			void Clear();
		};
		
	}
}

#endif // !_PROPERTYGROUP_H_
