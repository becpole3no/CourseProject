#pragma once

#include <vector>
#include <string>

class DataManager
{
public:
    std::vector<int> ParseArray(const std::wstring& text) const;
    std::vector<int> GenerateRandomData(int size, int minValue = 0, int maxValue = 100) const;
    std::wstring ArrayToString(const std::vector<int>& data) const;
};