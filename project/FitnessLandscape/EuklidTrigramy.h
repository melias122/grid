#pragma once
#include "FitnessFunctionss.h"
#include <vector>


class EuklidTrigramy :public FitnessFunctionss
{
public:
	std::vector<std::vector<std::vector<double>>>trigramy;
	std::string nazov;

	EuklidTrigramy();
	~EuklidTrigramy();
	EuklidTrigramy(std::string nazov);
	void fit();
};

