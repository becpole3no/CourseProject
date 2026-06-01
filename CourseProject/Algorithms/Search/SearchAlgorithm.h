#pragma once

#include <vector>
#include <string>
#include "../../Models/AlgorithmStats.h"

class SearchAlgorithm
{
public:
    virtual ~SearchAlgorithm() = default;

    virtual std::wstring GetName() const = 0;
    virtual int Search(const std::vector<int>& data, int key, AlgorithmStats& stats) = 0;
};