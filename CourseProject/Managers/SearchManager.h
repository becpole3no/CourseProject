#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../Algorithms/Search/SearchAlgorithm.h"

class SearchManager
{
public:
    void SetAlgorithm(const std::wstring& algorithmName);
    int Search(const std::vector<int>& data, int key, AlgorithmStats& stats);

private:
    std::unique_ptr<SearchAlgorithm> m_currentAlgorithm;
};