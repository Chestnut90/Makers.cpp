#include "pch.h"
#include "Surf.h"

#include "SurfIOException.h"

#include "C:\Program Files\Nexensor\NEXENSORSDK\include\BaseMethod\ZmapFormat.h"
#include "C:\Program Files\Nexensor\NEXENSORSDK\include\Algorithm\ImageProcessing.h"
using Zmap_ = NEXENSORSDK::CZmapFormat;

#pragma region getters

//@ get width
long nXSDK::Surf::width() const
{
	return width_;
}

//@ get height
long nXSDK::Surf::height() const
{
	return height_;
}

//@ zmap array
float * nXSDK::Surf::zmap() const
{
	return zmap_;
}

//@ get mask array
byte * nXSDK::Surf::mask() const
{
	return mask_;
}

//@ get gray array
byte * nXSDK::Surf::gray() const
{
	_ConvertGray();
	return gray_;
}

//@ get red array
byte * nXSDK::Surf::red() const
{
	_ConvertRGB();
	return red_;
}

//@ get green array
byte * nXSDK::Surf::green() const
{
	_ConvertRGB();
	return green_;
}

//@ get blue array
byte * nXSDK::Surf::blue() const
{
	_ConvertRGB();
	return blue_;
}

#pragma endregion
#pragma region ctors
// TODO :
//@ constructor
nXSDK::Surf::Surf()
{
	width_ = 0;
	height_ = 0;

	zmap_ = new float[0];
	mask_ = new byte[0];
	gray_ = new byte[0];
	red_ = new byte[0];
	green_ = new byte[0];
	blue_ = new byte[0];

	is_gray_allocated_ = false;
	is_rgb_allocated_ = false;
}

//@ desturctor
nXSDK::Surf::~Surf()
{
	_Init();
}

#pragma endregion
#pragma region array initializers
//@ convert float zmap to byte gray
void nXSDK::Surf::_ConvertGray() const
{
	if (is_gray_allocated_) return;

	gray_ = new byte[width() * height()];
	is_gray_allocated_ = true;
	NXSIP::Convert3Dto2D1CHImage(zmap(), width(), height(), gray_);

	is_gray_allocated_ = true;
}

//@ convert float zmap to byte reg, green, blue
void nXSDK::Surf::_ConvertRGB() const
{
	if (is_rgb_allocated_) return;

	long size = width() * height();
	red_ = new byte[size];
	green_ = new byte[size];
	blue_ = new byte[size];

	NXSIP::Convert3Dto2D3CHImage(zmap(), width(), height(), red_, green_, blue_);

	is_rgb_allocated_ = true;
}

//@ clear memories
//@ zmap format
//@ gray
//@ red
//@ green
//@ blue
void nXSDK::Surf::_Init()
{
	if (is_gray_allocated_)
	{
		delete gray_;
		gray_ = nullptr;

		is_gray_allocated_ = false;
	}

	if (is_rgb_allocated_)
	{
		delete red_;
		red_ = nullptr;
	
		delete green_;
		green_ = nullptr;
		
		delete blue_;
		blue_ = nullptr;

		is_rgb_allocated_ = false;
	}
}

#pragma endregion
#pragma region Surf I/O

//@ Save surf
bool nXSDK::Surf::Save(std::string filename)
{
	Zmap_ zmap_format;
	
	// set zmap
	float* zmap = zmap_format.GetZmap();
	zmap = zmap_;

	// set mask
	byte* mask = zmap_format.GetMask();
	mask = mask_;

	zmap_format.SetHeader(width_, height_, 0, 0, 0, 0, 0);	// TODO: 
	return zmap_format.SaveBinFile(CString(filename.c_str()));
}

//@ static function
//@ Save Surf
bool nXSDK::Surf::Save(Surf surf, std::string filename)
{
	return surf.Save(filename);
}

//@ load surf file
void nXSDK::Surf::Load(std::string filename)
{
	auto zmap_format = _OpenSurf(filename);
	Load(*zmap_format);
	delete zmap_format;
}

//@ load zmap format
void nXSDK::Surf::Load(NEXENSORSDK::CZmapFormat& zmap_format, bool is_mask_init)
{
	// init memory
	_Init();

	width_ = zmap_format.GetImageWidth();
	height_ = zmap_format.GetImageHeight();
	long size = width_ * height_;

	// allocate zmap
	zmap_ = new float[size];
	memcpy(zmap_, zmap_format.GetZmap(), size * sizeof(float));

	// allocate mask
	mask_ = new byte[size];
	memcpy(mask_, zmap_format.GetMask(), size);
	// init mask
	if (is_mask_init)
	{
		for (long i = 0; i < size; ++i)
		{
			auto &mask_point = mask_[i];
			mask_point = mask_point == 2 ? 0 : 255;
		}
	}
}

//@ Open zmap 
nXSDK::Surf& nXSDK::Surf::Open(std::string filename)
{
	Surf surf;// = new Surf();
	auto zmap_format = surf._OpenSurf(filename);
	surf.Load(*zmap_format);

	delete zmap_format;
	return surf;
}

NEXENSORSDK::CZmapFormat* nXSDK::Surf::_OpenSurf(std::string filename)
{
	auto zmap_format = new NEXENSORSDK::CZmapFormat();
	if (!zmap_format->OpenBinFile(CString(filename.c_str())))
	{
		throw SurfIOException("Surf open error.\n filename [" + filename + "]");
	}
	return zmap_format;
}

#pragma endregion
