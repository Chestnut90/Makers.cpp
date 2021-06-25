#include "pch.h"
#include <combaseapi.h>
#include "GUIDGen.h"

std::string Utils::IDGenerators::GUIDGen::Generate()
{
	GUID guid;
	::CoCreateGuid(&guid);

	const int len = 60;
	char dst[len];
	memset(dst, 0, len);
	snprintf(dst, len,
		"%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	std::string out(dst);
	return std::move(out);

	//{b9e9a3f7 - 1be8 - 4a8c - 9ce7 - 3f51a3edfb12}
}
