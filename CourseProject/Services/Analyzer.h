#pragma once

#include <string>
#include "../Models/AlgorithmStats.h"
#include "DataManager.h"
#include "../Managers/SortManager.h"
#include "../Managers/SearchManager.h"

struct AnalysisResult
{
    bool success = false;
    bool isSearch = false;
    std::wstring algorithmName;
    std::wstring complexityText;
    std::wstring normalizedArrayText;
    std::wstring resultText;
    AlgorithmStats stats;
};

class Analyzer
{
public:
    AnalysisResult RunSortAnalysis(
        const std::wstring& inputText,
        const std::wstring& algorithmName);

    AnalysisResult RunSearchAnalysis(
        const std::wstring& inputText,
        const std::wstring& algorithmName,
        const std::wstring& keyText);

private:
    std::wstring GetComplexityText(
        const std::wstring& algorithmName,
        bool isSearch) const;

    DataManager m_dataManager;
    SortManager m_sortManager;
    SearchManager m_searchManager;
};