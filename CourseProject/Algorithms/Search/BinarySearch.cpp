#include "pch.h"
#include "BinarySearch.h"
#include <chrono>

std::wstring BinarySearch::GetName() const
{
    return L"Бинарный поиск";
}

int BinarySearch::Search(const std::vector<int>& data, int key, AlgorithmStats& stats)
{
    stats = {};

    auto start = std::chrono::high_resolution_clock::now();

    int left = 0;
    int right = static_cast<int>(data.size()) - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        ++stats.comparisonCount;

        if (data[mid] == key)
        {
            auto end = std::chrono::high_resolution_clock::now();
            stats.executionTime = std::chrono::duration<double, std::milli>(end - start).count();
            stats.resultIndex = mid;
            stats.found = true;
            return mid;
        }

        ++stats.comparisonCount;
        if (data[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    stats.executionTime = std::chrono::duration<double, std::milli>(end - start).count();
    stats.resultIndex = -1;
    stats.found = false;

    return -1;
}