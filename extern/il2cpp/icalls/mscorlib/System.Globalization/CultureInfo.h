#pragma once

#include <stdint.h>

struct Il2CppString;
struct Il2CppCultureInfo;

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{
namespace Globalization
{

class CultureInfo
{
public:
	static void construct_datetime_format(Il2CppCultureInfo* cultureInfo);
	static bool construct_internal_locale_from_current_locale(Il2CppCultureInfo* cultureInfo);
	static bool construct_internal_locale_from_lcid(Il2CppCultureInfo* cultureInfo, int lcid);
	static bool construct_internal_locale_from_name(Il2CppCultureInfo* cultureInfo, Il2CppString* name);
	static bool construct_internal_locale_from_specific_name (Il2CppCultureInfo* cultureInfo, Il2CppString* name);
	static Il2CppArray* internal_get_cultures (bool neutral, bool specific, bool installed);
	static bool internal_is_lcid_neutral (int32_t lcid, bool* is_neutral);
	static void construct_number_format(Il2CppCultureInfo* cultureInfo);
};

} /* namespace Diagnostics */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
