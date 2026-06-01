#pragma once

#include "SearchAlgorithm.h"

class LinearSearch : public SearchAlgorithm
{
public:
    std::wstring GetName() const override;
    int Search(const std::vector<int>& data, int key, AlgorithmStats& stats) override;
};