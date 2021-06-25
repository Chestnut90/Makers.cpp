#pragma once
#ifndef _PROPERTYGROUP_H_
#define _PROPERTYGROUP_H_

#include <map>
#include <vector>
#include <iterator>

namespace Makers
{
	namespace Items { class ItemBase; }
	namespace Properties
	{
		class PropertyBase;

		class __declspec(dllexport) PropertyGroup 
		{
		private:
			//@ properties
			std::map<std::string, PropertyBase*> properties_;

		public:
			//@ count
			int Count();

		public:
			//@ constructor
			PropertyGroup();
			//@ destructor
			~PropertyGroup();

		public:
			//@ [name] operator
			PropertyBase& operator[](const std::string _name);

		public:
			//@ add property
			void AddProperty(PropertyBase& _property);

			//@ map iterator begin
			std::map<std::string, PropertyBase*>::const_iterator Begin();
			//@ map iterator end
			std::map<std::string, PropertyBase*>::const_iterator End();

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
