#pragma once

#include "SortAlgorithm.h"

class MergeSort : public SortAlgorithm
{
public:
    std::wstring GetName() const override;
    std::vector<int> Sort(const std::vector<int>& data, AlgorithmStats& stats) override;

private:
    void MergeSortRecursive(std::vector<int>& arr, int left, int right, AlgorithmStats& stats);
    void Merge(std::vector<int>& arr, int left, int mid, int right, AlgorithmStats& stats);
};