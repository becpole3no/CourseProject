#pragma once

#include "SortAlgorithm.h"

class QuickSort : public SortAlgorithm
{
public:
    std::wstring GetName() const override;
    std::vector<int> Sort(const std::vector<int>& data, AlgorithmStats& stats) override;

private:
    void QuickSortRecursive(std::vector<int>& arr, int low, int high, AlgorithmStats& stats);
    int Partition(std::vector<int>& arr, int low, int high, AlgorithmStats& stats);
};