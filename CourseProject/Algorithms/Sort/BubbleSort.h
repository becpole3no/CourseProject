#pragma once

#include "SortAlgorithm.h"

class BubbleSort : public SortAlgorithm
{
public:
    std::wstring GetName() const override;
    std::vector<int> Sort(const std::vector<int>& data, AlgorithmStats& stats) override;
};