#include "pch.h"
#include "MergeSort.h"
#include <chrono>
#include <vector>

std::wstring MergeSort::GetName() const
{
    return L"Сортировка слиянием";
}

std::vector<int> MergeSort::Sort(const std::vector<int>& data, AlgorithmStats& stats)
{
    std::vector<int> result = data;
    stats = {};

    auto start = std::chrono::high_resolution_clock::now();

    if (!result.empty())
    {
        MergeSortRecursive(result, 0, static_cast<int>(result.size() - 1), stats);
    }

    auto end = std::chrono::high_resolution_clock::now();
    stats.executionTime = std::chrono::duration<double, std::milli>(end - start).count();

    return result;
}

void MergeSort::MergeSortRecursive(std::vector<int>& arr, int left, int right, AlgorithmStats& stats)
{
    if (left >= right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    MergeSortRecursive(arr, left, mid, stats);
    MergeSortRecursive(arr, mid + 1, right, stats);
    Merge(arr, left, mid, right, stats);
}

void MergeSort::Merge(std::vector<int>& arr, int left, int mid, int right, AlgorithmStats& stats)
{
    std::vector<int> leftPart(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightPart(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < static_cast<int>(leftPart.size()) && j < static_cast<int>(rightPart.size()))
    {
        ++stats.comparisonCount;
        if (leftPart[i] <= rightPart[j])
        {
            arr[k++] = leftPart[i++];
        }
        else
        {
            arr[k++] = rightPart[j++];
        }
        ++stats.swapCount;
    }

    while (i < static_cast<int>(leftPart.size()))
    {
        arr[k++] = leftPart[i++];
        ++stats.swapCount;
    }

    while (j < static_cast<int>(rightPart.size()))
    {
        arr[k++] = rightPart[j++];
        ++stats.swapCount;
    }
}