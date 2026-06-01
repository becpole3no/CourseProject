#include "pch.h"
#include "SortManager.h"
#include "../Algorithms/Sort/BubbleSort.h"
#include "../Algorithms/Sort/SelectionSort.h"
#include "../Algorithms/Sort/InsertionSort.h"
#include "../Algorithms/Sort/QuickSort.h"
#include "../Algorithms/Sort/MergeSort.h"
#include <stdexcept>

void SortManager::SetAlgorithm(const std::wstring& algorithmName)
{
    if (algorithmName == L"Пузырьковая сортировка")
    {
        m_currentAlgorithm = std::make_unique<BubbleSort>();
    }
    else if (algorithmName == L"Сортировка выбором")
    {
        m_currentAlgorithm = std::make_unique<SelectionSort>();
    }
    else if (algorithmName == L"Сортировка вставками")
    {
        m_currentAlgorithm = std::make_unique<InsertionSort>();
    }
    else if (algorithmName == L"Быстрая сортировка")
    {
        m_currentAlgorithm = std::make_unique<QuickSort>();
    }
    else if (algorithmName == L"Сортировка слиянием")
    {
        m_currentAlgorithm = std::make_unique<MergeSort>();
    }
    else
    {
        throw std::runtime_error("Неизвестный алгоритм сортировки");
    }
}

std::vector<int> SortManager::Sort(const std::vector<int>& data, AlgorithmStats& stats)
{
    if (!m_currentAlgorithm)
    {
        throw std::runtime_error("Алгоритм сортировки не выбран");
    }

    return m_currentAlgorithm->Sort(data, stats);
}