#include "pch.h"
#include "LinearSearch.h"
#include <chrono>

std::wstring LinearSearch::GetName() const
{
    return L"Линейный поиск";
}

int LinearSearch::Search(const std::vector<int>& data, int key, AlgorithmStats& stats)
{
    stats = {};

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < data.size(); ++i)
    {
        ++stats.comparisonCount;
        if (data[i] == key)
        {
            auto end = std::chrono::high_resolution_clock::now();
            stats.executionTime = std::chrono::duration<double, std::milli>(end - start).count();
            stats.resultIndex = static_cast<int>(i);
            stats.found = true;
            return static_cast<int>(i);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    stats.executionTime = std::chrono::duration<double, std::milli>(end - start).count();

    stats.resultIndex = -1;
    stats.found = false;
    return -1;
}