#include "pch.h"
#include "DataManager.h"
#include <sstream>
#include <random>
#include <stdexcept>

std::vector<int> DataManager::ParseArray(const std::wstring& text) const
{
    std::wstring normalized = text;

    for (auto& ch : normalized)
    {
        if (ch == L',' || ch == L';')
        {
            ch = L' ';
        }
    }

    std::wstringstream stream(normalized);
    std::vector<int> result;
    int value = 0;

    while (stream >> value)
    {
        result.push_back(value);
    }

    return result;
}

std::vector<int> DataManager::GenerateRandomData(int size, int minValue, int maxValue) const
{
    if (size <= 0)
    {
        return {};
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minValue, maxValue);

    std::vector<int> data;
    data.reserve(static_cast<size_t>(size));

    for (int i = 0; i < size; ++i)
    {
        data.push_back(dist(gen));
    }

    return data;
}

std::wstring DataManager::ArrayToString(const std::vector<int>& data) const
{
    std::wstringstream stream;

    for (size_t i = 0; i < data.size(); ++i)
    {
        stream << data[i];
        if (i + 1 < data.size())
        {
            stream << L", ";
        }
    }

    return stream.str();
}