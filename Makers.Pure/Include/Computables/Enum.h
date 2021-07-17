#pragma once
#ifndef _ENUM_H_
#define _ENUM_H_

#include <vector>
#include <string>

#include "IComputable.h"

namespace Makers
{
	namespace Computables
	{
		//@ Class <Enum>
		//@ enum strings
		//@ Inherit <IComputable>
		class __declspec(dllexport) Enum :
			public IComputable
		{
		private:
			//@ name
			std::string name_;
			//@ selected value
			int selected_index_;
			//@ enumerations
			std::vector<std::string> enumerations_;

		public:
			//@ get name
			std::string name() const;
			//@ get selected index
			int selected_index() const;
			//@ get selected value in enumeration
			std::string selected_value() const;
			//@ get enumeration
			std::vector<std::string> enumeration() const;
		
		public:
			//@ set selected index
			void set_selected_index(int index);

		public:
			//@ constructor
			//@ default
			Enum();
			//@ constructor
			//@ with enumerations
			Enum(std::vector<std::string> enumeration);
			//@ constructor
			//@ with name and enumerations
			Enum(std::string name, std::vector<std::string> enumeration);
			//@ destructor
			virtual ~Enum();

		public:
			//@ get max enum count
			int Count() const;

		// implement <IComputable> abstract functions
		public:
			//@ Can attach input to this
			virtual bool CanAttachInto(IComputable* computable) override;
			//@ To string
			virtual std::string ToString() override;

		// override virtual functions <IMapableData>
		public:
			//@ To data
			std::map<std::string, std::string> ToData() override;

		};
	}
}

#endif // !_ENUM_H_
