#pragma once
class StringUtility
{
};

namespace StringUtility {
	std::wstring ConvertString(const std::string& str);

	std::string ConvertString(const std::wstring& str);
};