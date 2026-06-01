#pragma once

#include <vector>
#include <string>
#include "../../Models/AlgorithmStats.h"

class SortAlgorithm
{
public:
    virtual ~SortAlgorithm() = default;

    virtual std::wstring GetName() const = 0;
    virtual std::vector<int> Sort(const std::vector<int>& data, AlgorithmStats& stats) = 0;
};