#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../Algorithms/Sort/SortAlgorithm.h"

class SortManager
{
public:
    void SetAlgorithm(const std::wstring& algorithmName);
    std::vector<int> Sort(const std::vector<int>& data, AlgorithmStats& stats);

private:
    std::unique_ptr<SortAlgorithm> m_currentAlgorithm;
};