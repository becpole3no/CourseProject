#include "pch.h"
#include "QuickSort.h"
#include <chrono>
#include <utility>

std::wstring QuickSort::GetName() const
{
    return L"Быстрая сортировка";
}

std::vector<int> QuickSort::Sort(const std::vector<int>& data, AlgorithmStats& stats)
{
    std::vector<int> result = data;
    stats = {};

    auto start = std::chrono::high_resolution_clock::now();

    if (!result.empty())
    {
        QuickSortRecursive(result, 0, static_cast<int>(result.size() - 1), stats);
    }

    auto end = std::chrono::high_resolution_clock::now();
    stats.executionTime = std::chrono::duration<double, std::milli>(end - start).count();

    return result;
}

void QuickSort::QuickSortRecursive(std::vector<int>& arr, int low, int high, AlgorithmStats& stats)
{
    if (low < high)
    {
        int pivotIndex = Partition(arr, low, high, stats);
        QuickSortRecursive(arr, low, pivotIndex - 1, stats);
        QuickSortRecursive(arr, pivotIndex + 1, high, stats);
    }
}

int QuickSort::Partition(std::vector<int>& arr, int low, int high, AlgorithmStats& stats)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j)
    {
        ++stats.comparisonCount;
        if (arr[j] < pivot)
        {
            ++i;
            std::swap(arr[i], arr[j]);
            ++stats.swapCount;
        }
    }

    std::swap(arr[i + 1], arr[high]);
    ++stats.swapCount;

    return i + 1;
}