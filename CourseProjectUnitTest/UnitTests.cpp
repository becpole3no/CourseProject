#include "pch.h"

#include "CppUnitTest.h"
#include "../CourseProject/Managers/SearchManager.h"
#include "../CourseProject/Managers/SortManager.h"
#include "../CourseProject/Services/Analyzer.h"
#include "../CourseProject/Services/DataManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CourseProjectUnitTest
{
    namespace
    {
        constexpr wchar_t kBubbleSortName[] =
            L"Пузырьковая сортировка";

        constexpr wchar_t kQuickSortName[] =
            L"Быстрая сортировка";

        constexpr wchar_t kLinearSearchName[] =
            L"Линейный поиск";

        constexpr wchar_t kBinarySearchName[] =
            L"Бинарный поиск";

        constexpr wchar_t kSortedArrayResult[] =
            L"Отсортированный массив:\r\n1, 4, 7, 9";

        constexpr wchar_t kInvalidArrayMessage[] =
            L"Введите корректный массив.";
    }

    TEST_CLASS(CourseProjectLogicTests)
    {
    private:
        static void AssertVectorEquals(
            std::vector<int> const& expected,
            std::vector<int> const& actual)
        {
            Assert::AreEqual(expected.size(), actual.size(), L"Размеры массивов различаются.");

            for (size_t index = 0; index < expected.size(); ++index)
            {
                Assert::AreEqual(expected[index], actual[index], L"Элемент массива отличается.");
            }
        }

    public:
        TEST_METHOD(ParseArray_ParsesDifferentSeparators)
        {
            DataManager dataManager;

            auto result = dataManager.ParseArray(L"5, 3;8 1,9");

            AssertVectorEquals({ 5, 3, 8, 1, 9 }, result);
        }

        TEST_METHOD(ArrayToString_FormatsArrayWithCommas)
        {
            DataManager dataManager;

            auto result = dataManager.ArrayToString({ 1, 2, 3, 4 });

            Assert::AreEqual(L"1, 2, 3, 4", result.c_str());
        }

        TEST_METHOD(GenerateRandomData_ReturnsCorrectSizeAndRange)
        {
            DataManager dataManager;

            auto result = dataManager.GenerateRandomData(25, 10, 20);

            Assert::AreEqual(static_cast<size_t>(25), result.size());
            for (int value : result)
            {
                Assert::IsTrue(value >= 10 && value <= 20);
            }
        }

        TEST_METHOD(SortManager_BubbleSort_SortsAscending)
        {
            SortManager sortManager;
            AlgorithmStats stats;

            sortManager.SetAlgorithm(kBubbleSortName);
            auto result = sortManager.Sort({ 5, 1, 4, 2, 8 }, stats);

            AssertVectorEquals({ 1, 2, 4, 5, 8 }, result);
            Assert::IsTrue(stats.comparisonCount > 0);
        }

        TEST_METHOD(SearchManager_LinearSearch_ReturnsFoundIndex)
        {
            SearchManager searchManager;
            AlgorithmStats stats;

            searchManager.SetAlgorithm(kLinearSearchName);
            auto index = searchManager.Search({ 7, 3, 9, 1 }, 9, stats);

            Assert::AreEqual(2, index);
            Assert::IsTrue(stats.found);
            Assert::AreEqual(2, stats.resultIndex);
        }

        TEST_METHOD(Analyzer_RunSortAnalysis_ReturnsSortedResult)
        {
            Analyzer analyzer;

            auto result = analyzer.RunSortAnalysis(L"9, 4, 1, 7", kQuickSortName);

            Assert::IsTrue(result.success);
            Assert::AreEqual(L"O(n log n)", result.complexityText.c_str());
            Assert::AreEqual(L"1, 4, 7, 9", result.normalizedArrayText.c_str());
            Assert::AreEqual(kSortedArrayResult, result.resultText.c_str());
        }

        TEST_METHOD(Analyzer_RunSearchAnalysis_SortsForBinarySearch)
        {
            Analyzer analyzer;

            auto result = analyzer.RunSearchAnalysis(L"9, 1, 7, 4", kBinarySearchName, L"7");

            Assert::IsTrue(result.success);
            Assert::AreEqual(L"O(log n)", result.complexityText.c_str());
            Assert::AreEqual(L"1, 4, 7, 9", result.normalizedArrayText.c_str());
            Assert::IsTrue(result.stats.found);
            Assert::AreEqual(2, result.stats.resultIndex);
        }

        TEST_METHOD(Analyzer_RunSortAnalysis_HandlesInvalidInput)
        {
            Analyzer analyzer;

            auto result = analyzer.RunSortAnalysis(L"", kBubbleSortName);

            Assert::IsFalse(result.success);
            Assert::AreEqual(kInvalidArrayMessage, result.resultText.c_str());
        }
    };
}