#include "stdafx.h"
#include "LogicalLayer.h"
#include "algorithmex.h"

using namespace std;

LogicalLayer::LogicalLayer()
{
}


LogicalLayer::~LogicalLayer()
{
}

vector<tstring> LogicalLayer::getPathList()
{
	tstring path = getPath();
	auto v = split(path, tstring(TEXT(";")));
	return v;
}

tstring LogicalLayer::getPath()
{
	const size_t size = 32767;
	vector<TCHAR> buffer(size);
	auto got = GetEnvironmentVariable(TEXT("PATH"), &buffer[0], size);
	assert(got > 0);
	return &buffer[0];
}

bool LogicalLayer::setPathList(std::vector<tstring>& list)
{
	tstring ts;
	for (auto s : list)
		ts += s + TEXT(";");
	SetEnvironmentVariable(TEXT("PATH"), ts.c_str());
	return true;
}
