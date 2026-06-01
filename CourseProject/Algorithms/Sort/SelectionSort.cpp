#include "pch.h"
#include "SelectionSort.h"
#include <chrono>
#include <utility>

std::wstring SelectionSort::GetName() const
{
    return L"Сортировка выбором";
}

std::vector<int> SelectionSort::Sort(const std::vector<int>& data, AlgorithmStats& stats)
{
    std::vector<int> result = data;
    stats = {};

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < result.size(); ++i)
    {
        size_t minIndex = i;

        for (size_t j = i + 1; j < result.size(); ++j)
        {
            ++stats.comparisonCount;
            if (result[j] < result[minIndex])
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            std::swap(result[i], result[minIndex]);
            ++stats.swapCount;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    stats.executionTime = std::chrono::duration<double, std::milli>(end - start).count();

    return result;
}