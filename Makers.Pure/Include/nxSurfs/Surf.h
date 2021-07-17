#pragma once
#ifndef _NX_SURF_H_
#define _NX_SURF_H_

#include <string>

//@ byte as unsigned char
typedef unsigned char byte;

// TODO : define image format
namespace NEXENSORSDK { class CZmapFormat; }
namespace nXSDK
{
	class _declspec(dllexport) Surf 
	{
		// private members
	private:
		mutable bool is_gray_allocated_;
		mutable bool is_rgb_allocated_;

		// protected member
	protected:
		long width_;
		long height_;
		float* zmap_;	
		byte* mask_;
		mutable byte* gray_;
		mutable byte* red_;
		mutable byte* green_;
		mutable byte* blue_;

		// getters
	public:
		long width() const;
		long height() const;
		float* zmap() const;
		byte* mask() const;
		byte* gray() const;
		byte* red() const;
		byte* green() const;
		byte* blue() const;

		// ctors
	public:
		//@ Constructor
		Surf();
		//@ Destructor
		~Surf();

		// operators
	public:

		//@ insert operator
		//Surf& operator=(Surf surf);

		// array initializers
	private:
		//@ Convert float zmap to byte gray
		void _ConvertGray() const;
		//@ Convert float zmap to byte reg, green, blue
		void _ConvertRGB() const;
		//@ Initialize inner memory and data
		void _Init();

		// Surf I/O
	public:
		//@ Save surf to binary file with filename
		bool Save(std::string filename);
		//@ Save surf to binary file with filename
		//@ Static
		static bool Save(Surf surf, std::string filename);
		
		//@ Load surf file
		void Load(std::string filename);
		//@ Load surf
		void Load(NEXENSORSDK::CZmapFormat& zmap_format, bool is_mask_init = true);
		//@ Open surf file
		//@ return Surf instance
		static Surf& Open(std::string filename);

		//@ Surf I/O sub functions
	private:
		//@ open zmap format file
		NEXENSORSDK::CZmapFormat* _OpenSurf(std::string filename);

	};
}

#endif // !_NX_SURF_H_

