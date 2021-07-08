#pragma once
#ifndef _COMBO_H
#define _COMBO_H

#include <vector>
#include <string>

#include "IComputable.h"

namespace Makers
{
	namespace Computables
	{
		class __declspec(dllexport) Combo :
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
			void set_selected_index(int _index);

		public:
			//@ constructor
			Combo(std::vector<std::string> _enumeration);
			//@ named constructor
			Combo(std::string _name, std::vector<std::string> _enumeration);
			//@ destructor
			virtual ~Combo();

		public:

			//@ get max enum count
			int Count() const;

		// implement IComputable abstract functions
		public:
			
			//@ Can attach input to this
			virtual bool CanAttachInto(IComputable* _computable) override;

			//@ To string
			virtual std::string ToString() override;


		};
	}
}

#endif // !_COMBO_H
