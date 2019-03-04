#pragma once
#include <vector>


class LogicalLayer
{
private:
	LogicalLayer();
	~LogicalLayer();
public:
	static std::vector<tstring> getPathList();
	static bool setPathList(std::vector<tstring>&);
private:
	static tstring getPath();

};

