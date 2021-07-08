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
		enum ePropertyType
		{
			eInputProperty,
			eStaticProperty,
			eOutputProperty,
		};

		class PropertyBase;
		//@ class Property Group
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
			//@ count
			int Count();

			//@ owner item
			Makers::Items::ItemBase* owner_item() const;

		public:
			//@ constructor
			PropertyGroup();
			//@ destructor
			~PropertyGroup();

		public:
			//@ [name] operator
			PropertyBase* operator[](const std::string _name);
		public:
			//@ add property
			void AddProperty(PropertyBase* _property);
			
			//@ TODO : implement
			//@ add property
			PropertyBase* AddProperty(
				std::string _name,
				Computables::IComputable* _computable,
				bool _is_optional,
				ePropertyType _property_type);
			
			//@ map iterator begin
			std::vector<PropertyBase*>::iterator Begin();
			//@ map iterator end
			std::vector<PropertyBase*>::iterator End();

			// TODO: nullable
			//@ query property with id
			PropertyBase* QueryPropertyID(std::string _id);
			//@ query property with name
			PropertyBase* QueryPropertyName(std::string _name);

		private:
			//@ clear all properties
			void Clear();
		};
		
	}
}

#endif // !_PROPERTYGROUP_H_
