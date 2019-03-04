#pragma once

#include <string>
#include <vector>
#include <algorithm>

template<typename T>
std::vector<std::basic_string<T>> split(const std::basic_string<T>& input, const std::basic_string<T>& sign)
{
	auto beginning = 0;
	auto ending = input.find(sign);
	std::vector<std::basic_string<T>> v;
	while (ending != input.npos)
	{
		auto s = input.substr(beginning, ending - beginning);
		v.push_back(s);
		beginning = ending + 1;
		ending = input.find(sign, beginning );
	}
	v.push_back(input.substr(beginning, ending));
	return v;
}

