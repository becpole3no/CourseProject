#include "pch.h"
#include "InsertionSort.h"
#include <chrono>

std::wstring InsertionSort::GetName() const
{
    return L"Сортировка вставками";
}

std::vector<int> InsertionSort::Sort(const std::vector<int>& data, AlgorithmStats& stats)
{
    std::vector<int> result = data;
    stats = {};

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 1; i < result.size(); ++i)
    {
        int key = result[i];
        int j = static_cast<int>(i) - 1;

        while (j >= 0)
        {
            ++stats.comparisonCount;
            if (result[j] > key)
            {
                result[j + 1] = result[j];
                ++stats.swapCount;
                --j;
            }
            else
            {
                break;
            }
        }

        result[j + 1] = key;
    }

    auto end = std::chrono::high_resolution_clock::now();
    stats.executionTime = std::chrono::duration<double, std::milli>(end - start).count();

    return result;
}