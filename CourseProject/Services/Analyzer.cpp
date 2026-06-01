#include "pch.h"
#include "Analyzer.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>

AnalysisResult Analyzer::RunSortAnalysis(
    const std::wstring& inputText,
    const std::wstring& algorithmName)
{
    AnalysisResult result;
    result.algorithmName = algorithmName;
    result.complexityText = GetComplexityText(algorithmName, false);

    try
    {
        auto data = m_dataManager.ParseArray(inputText);
        if (data.empty())
        {
            result.resultText = L"Введите корректный массив.";
            return result;
        }

        m_sortManager.SetAlgorithm(algorithmName);

        AlgorithmStats stats;
        auto sortedData = m_sortManager.Sort(data, stats);

        result.success = true;
        result.stats = stats;
        result.normalizedArrayText = m_dataManager.ArrayToString(sortedData);
        result.resultText = L"Отсортированный массив:\r\n" + result.normalizedArrayText;
    }
    catch (std::exception const&)
    {
        result.resultText = L"Ошибка при выполнении сортировки.";
    }
    catch (...)
    {
        result.resultText = L"Ошибка при выполнении сортировки.";
    }

    return result;
}

AnalysisResult Analyzer::RunSearchAnalysis(
    const std::wstring& inputText,
    const std::wstring& algorithmName,
    const std::wstring& keyText)
{
    AnalysisResult result;
    result.isSearch = true;
    result.algorithmName = algorithmName;
    result.complexityText = GetComplexityText(algorithmName, true);

    try
    {
        auto data = m_dataManager.ParseArray(inputText);
        if (data.empty())
        {
            result.resultText = L"Введите корректный массив.";
            return result;
        }

        int key = std::stoi(keyText);

        if (algorithmName == L"Бинарный поиск")
        {
            std::sort(data.begin(), data.end());
        }

        m_searchManager.SetAlgorithm(algorithmName);

        AlgorithmStats stats;
        int index = m_searchManager.Search(data, key, stats);

        std::wstringstream resultStream;
        resultStream << L"Результат поиска:\r\n";
        if (index >= 0)
        {
            resultStream << L"Элемент найден. Индекс: " << index;
        }
        else
        {
            resultStream << L"Элемент не найден.";
        }

        if (algorithmName == L"Бинарный поиск")
        {
            resultStream << L"\r\nПоиск выполнен по отсортированному массиву.";
        }

        result.success = true;
        result.stats = stats;
        result.normalizedArrayText = m_dataManager.ArrayToString(data);
        result.resultText = resultStream.str();
    }
    catch (std::exception const&)
    {
        result.resultText = L"Ошибка при выполнении поиска.";
    }
    catch (...)
    {
        result.resultText = L"Ошибка при выполнении поиска.";
    }

    return result;
}

std::wstring Analyzer::GetComplexityText(
    const std::wstring& algorithmName,
    bool isSearch) const
{
    if (isSearch)
    {
        if (algorithmName == L"Бинарный поиск")
        {
            return L"O(log n)";
        }

        return L"O(n)";
    }

    if (algorithmName == L"Быстрая сортировка" || algorithmName == L"Сортировка слиянием")
    {
        return L"O(n log n)";
    }

    return L"O(n²)";
}