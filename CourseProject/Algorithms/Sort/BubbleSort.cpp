#include "pch.h"
#include "BubbleSort.h"
#include <chrono>
#include <utility>

std::wstring BubbleSort::GetName() const
{
    return L"Пузырьковая сортировка";
}

std::vector<int> BubbleSort::Sort(const std::vector<int>& data, AlgorithmStats& stats)
{
    std::vector<int> result = data;
    stats = {};

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < result.size(); ++i)
    {
        for (size_t j = 0; j + 1 < result.size() - i; ++j)
        {
            ++stats.comparisonCount;
            if (result[j] > result[j + 1])
            {
                std::swap(result[j], result[j + 1]);
                ++stats.swapCount;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    stats.executionTime = std::chrono::duration<double, std::milli>(end - start).count();

    return result;
}