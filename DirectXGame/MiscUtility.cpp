#include "MiscUtility.h"
#include <Windows.h>
#include <string>

std::wstring ConvertString(const std::string& str) { 
	// string => wstrung 文字列変換
	if (str.empty()) {
		return std::wstring();
	}
	auto sizeNeede = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), 
		static_cast<int>(str.size()), NULL, 0);
	if (sizeNeede == 0) {
		return std::wstring();
	}
	std::wstring result(sizeNeede, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), 
		static_cast<int>(str.size()), &result[0], sizeNeede);
	return result;
}

std::string ConvertString(const std::wstring& str) { 
	// wstrung  => string 文字列変換
	if (str.empty()) {
		return std::string();
	}
	auto sizeNeede = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), NULL, 0);
	if (sizeNeede == 0) {
		return std::string();
	}
	std::string result(sizeNeede, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), &result[0], sizeNeede);
	return result;
}
