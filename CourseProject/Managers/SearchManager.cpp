#include "pch.h"
#include "SearchManager.h"
#include "../Algorithms/Search/LinearSearch.h"
#include "../Algorithms/Search/BinarySearch.h"
#include <stdexcept>

void SearchManager::SetAlgorithm(const std::wstring& algorithmName)
{
    if (algorithmName == L"Линейный поиск")
    {
        m_currentAlgorithm = std::make_unique<LinearSearch>();
    }
    else if (algorithmName == L"Бинарный поиск")
    {
        m_currentAlgorithm = std::make_unique<BinarySearch>();
    }
    else
    {
        throw std::runtime_error("Неизвестный алгоритм поиска");
    }
}

int SearchManager::Search(const std::vector<int>& data, int key, AlgorithmStats& stats)
{
    if (!m_currentAlgorithm)
    {
        throw std::runtime_error("Алгоритм поиска не выбран");
    }

    return m_currentAlgorithm->Search(data, key, stats);
}