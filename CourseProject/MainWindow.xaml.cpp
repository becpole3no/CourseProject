#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <algorithm>
#include <string>
#include <sstream>
#include <winrt/Microsoft.UI.Input.h>
#include <winrt/Microsoft.UI.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Windows.UI.h>
#include <microsoft.ui.xaml.window.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::CourseProject::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        Activated({ this, &MainWindow::MainWindow_Activated });

        SortAlgorithmComboBox().SelectedIndex(0);
        SearchAlgorithmComboBox().SelectedIndex(0);
        ResetDashboard();
    }

    void MainWindow::MainWindow_Activated(
        IInspectable const&,
        WindowActivatedEventArgs const&)
    {
        if (m_windowChromeConfigured)
        {
            return;
        }

        ConfigureWindowChrome();
        m_windowChromeConfigured = true;
    }

    void MainWindow::ConfigureWindowChrome()
    {
        auto windowNative = this->try_as<::IWindowNative>();
        if (!windowNative)
        {
            return;
        }

        HWND windowHandle{};
        if (FAILED(windowNative->get_WindowHandle(&windowHandle)))
        {
            return;
        }

        SetWindowPos(
            windowHandle,
            nullptr,
            0,
            0,
            1036,
            891,
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

        if (!winrt::Microsoft::UI::Windowing::AppWindowTitleBar::IsCustomizationSupported())
        {
            return;
        }

        auto windowId = winrt::Microsoft::UI::GetWindowIdFromWindow(windowHandle);
        auto appWindow = winrt::Microsoft::UI::Windowing::AppWindow::GetFromWindowId(windowId);
        auto backgroundColor = winrt::Windows::UI::ColorHelper::FromArgb(255, 245, 245, 247);
        auto hoverColor = winrt::Windows::UI::ColorHelper::FromArgb(255, 230, 230, 235);
        auto pressedColor = winrt::Windows::UI::ColorHelper::FromArgb(255, 220, 220, 225);
        auto inactiveTextColor = winrt::Windows::UI::ColorHelper::FromArgb(255, 120, 120, 125);

        ExtendsContentIntoTitleBar(true);
        SetTitleBar(AppTitleBar());

        auto titleBar = appWindow.TitleBar();
        titleBar.IconShowOptions(winrt::Microsoft::UI::Windowing::IconShowOptions::HideIconAndSystemMenu);
        titleBar.PreferredTheme(winrt::Microsoft::UI::Windowing::TitleBarTheme::Light);
        titleBar.PreferredHeightOption(
            winrt::Microsoft::UI::Windowing::TitleBarHeightOption::Tall);
        titleBar.BackgroundColor(backgroundColor);
        titleBar.ForegroundColor(winrt::Windows::UI::Colors::Black());
        titleBar.InactiveBackgroundColor(backgroundColor);
        titleBar.InactiveForegroundColor(winrt::Windows::UI::Colors::Black());
        titleBar.ButtonBackgroundColor(backgroundColor);
        titleBar.ButtonForegroundColor(winrt::Windows::UI::Colors::Black());
        titleBar.ButtonHoverBackgroundColor(hoverColor);
        titleBar.ButtonHoverForegroundColor(winrt::Windows::UI::Colors::Black());
        titleBar.ButtonPressedBackgroundColor(pressedColor);
        titleBar.ButtonPressedForegroundColor(winrt::Windows::UI::Colors::Black());
        titleBar.ButtonInactiveBackgroundColor(backgroundColor);
        titleBar.ButtonInactiveForegroundColor(inactiveTextColor);
    }

    void MainWindow::GenerateArrayButton_Click(
        IInspectable const&,
        RoutedEventArgs const&)
    {
        try
        {
            auto sizeText = ArraySizeTextBox().Text();
            int size = std::stoi(std::wstring(sizeText));

            auto data = m_dataManager.GenerateRandomData(size);
            InputArrayTextBox().Text(winrt::hstring(m_dataManager.ArrayToString(data)));
            RefreshDashboard();
        }
        catch (...)
        {
            RefreshDashboard();
        }
    }

    void MainWindow::Button_PointerEntered(
        IInspectable const& sender,
        Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const&)
    {
        if (auto element = sender.try_as<Microsoft::UI::Xaml::IUIElementProtected>())
        {
            element.ProtectedCursor(
                Microsoft::UI::Input::InputSystemCursor::Create(
                    Microsoft::UI::Input::InputSystemCursorShape::Hand));
        }
    }

    void MainWindow::Button_PointerExited(
        IInspectable const& sender,
        Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const&)
    {
        if (auto element = sender.try_as<Microsoft::UI::Xaml::IUIElementProtected>())
        {
            element.ProtectedCursor(nullptr);
        }
    }

    void MainWindow::FloatingTextBox_StateChanged(
        IInspectable const& sender,
        RoutedEventArgs const&)
    {
        if (auto textBox = sender.try_as<Microsoft::UI::Xaml::Controls::TextBox>())
        {
            UpdateFloatingTextBoxState(textBox);
        }
    }

    void MainWindow::FloatingTextBox_TextChanged(
        IInspectable const& sender,
        Microsoft::UI::Xaml::Controls::TextChangedEventArgs const&)
    {
        if (auto textBox = sender.try_as<Microsoft::UI::Xaml::Controls::TextBox>())
        {
            UpdateFloatingTextBoxState(textBox);
        }
    }

    void MainWindow::UpdateFloatingTextBoxState(
        Microsoft::UI::Xaml::Controls::TextBox const& textBox)
    {
        auto shouldFloat = textBox.FocusState() != Microsoft::UI::Xaml::FocusState::Unfocused
            || !textBox.Text().empty();

        Microsoft::UI::Xaml::VisualStateManager::GoToState(
            textBox,
            shouldFloat ? L"Floating" : L"Resting",
            true);
    }

    void MainWindow::ComboBox_Loaded(
        IInspectable const& sender,
        RoutedEventArgs const&)
    {
        if (auto comboBox = sender.try_as<Microsoft::UI::Xaml::Controls::ComboBox>())
        {
            UpdateComboBoxState(comboBox);
        }
    }

    void MainWindow::ComboBox_DropDownOpened(
        IInspectable const& sender,
        IInspectable const&)
    {
        if (auto comboBox = sender.try_as<Microsoft::UI::Xaml::Controls::ComboBox>())
        {
            UpdateComboBoxState(comboBox);
        }
    }

    void MainWindow::ComboBox_DropDownClosed(
        IInspectable const& sender,
        IInspectable const&)
    {
        if (auto comboBox = sender.try_as<Microsoft::UI::Xaml::Controls::ComboBox>())
        {
            UpdateComboBoxState(comboBox);
        }
    }

    void MainWindow::UpdateComboBoxState(
        Microsoft::UI::Xaml::Controls::ComboBox const& comboBox)
    {
        Microsoft::UI::Xaml::VisualStateManager::GoToState(
            comboBox,
            comboBox.IsDropDownOpen() ? L"Opened" : L"Closed",
            true);
    }

    void MainWindow::ClearButton_Click(
        IInspectable const&,
        RoutedEventArgs const&)
    {
        InputArrayTextBox().Text(L"");
        ArraySizeTextBox().Text(L"");
        SearchKeyTextBox().Text(L"");
        m_lastSortResult.reset();
        m_lastSearchResult.reset();
        m_lastOperationWasSearch = false;
        ResetDashboard();
    }

    void MainWindow::SortButton_Click(
        IInspectable const&,
        RoutedEventArgs const&)
    {
        std::wstring algorithmName =
            SortAlgorithmComboBox().SelectedItem().as<hstring>().c_str();

        auto analysisResult = m_analyzer.RunSortAnalysis(
            InputArrayTextBox().Text().c_str(),
            algorithmName);

        if (!analysisResult.normalizedArrayText.empty())
        {
            InputArrayTextBox().Text(winrt::hstring(analysisResult.normalizedArrayText));
        }

        m_lastSortResult = analysisResult;
        m_lastOperationWasSearch = false;
        RefreshDashboard();
    }

    void MainWindow::SearchButton_Click(
        IInspectable const&,
        RoutedEventArgs const&)
    {
        std::wstring algorithmName =
            SearchAlgorithmComboBox().SelectedItem().as<hstring>().c_str();

        auto analysisResult = m_analyzer.RunSearchAnalysis(
            InputArrayTextBox().Text().c_str(),
            algorithmName,
            SearchKeyTextBox().Text().c_str());

        if (!analysisResult.normalizedArrayText.empty())
        {
            InputArrayTextBox().Text(winrt::hstring(analysisResult.normalizedArrayText));
        }

        m_lastSearchResult = analysisResult;
        m_lastOperationWasSearch = true;
        RefreshDashboard();
    }

    void MainWindow::ResetDashboard()
    {
        MetricElementCountText().Text(winrt::to_hstring(TryGetCurrentElementCount()));
        MetricSortComplexityText().Text(L"-");
        MetricSearchComplexityText().Text(L"-");
        MetricComparisonCountText().Text(L"0");

        ResultHeaderText().Text(L"Результат операции");
        ResultContentText().Text(L"Здесь появится результат.");
        ResultStatusValueText().Text(L"Ожидание");
        ResultTimeValueText().Text(L"0 мс");
        ResultStepsValueText().Text(L"0");

        PerformancePrimaryNameText().Text(L"Сортировка");
        PerformancePrimaryPercentText().Text(L"0%");
        PerformancePrimaryBar().Value(0);

        PerformanceSecondaryNameText().Text(L"Перестановки");
        PerformanceSecondaryPercentText().Text(L"0%");
        PerformanceSecondaryBar().Value(0);

        PerformanceTertiaryNameText().Text(L"Поиск");
        PerformanceTertiaryPercentText().Text(L"0%");
        PerformanceTertiaryBar().Value(0);
    }

    void MainWindow::RefreshDashboard()
    {
        UpdateQuickMetrics();
        UpdateResultCard();
        UpdatePerformanceCard();
    }

    void MainWindow::UpdateQuickMetrics()
    {
        MetricElementCountText().Text(winrt::to_hstring(TryGetCurrentElementCount()));

        auto sortComplexity = m_lastSortResult
            ? m_lastSortResult->complexityText
            : L"-";

        auto searchComplexity = m_lastSearchResult
            ? m_lastSearchResult->complexityText
            : L"-";

        MetricSortComplexityText().Text(winrt::hstring(sortComplexity));
        MetricSearchComplexityText().Text(winrt::hstring(searchComplexity));

        int totalComparisons = 0;
        if (m_lastSortResult)
        {
            totalComparisons += m_lastSortResult->stats.comparisonCount;
        }
        if (m_lastSearchResult)
        {
            totalComparisons += m_lastSearchResult->stats.comparisonCount;
        }

        MetricComparisonCountText().Text(winrt::to_hstring(totalComparisons));
    }

    void MainWindow::UpdateResultCard()
    {
        AnalysisResult const* currentResult = nullptr;

        if (m_lastOperationWasSearch && m_lastSearchResult)
        {
            currentResult = &(*m_lastSearchResult);
        }
        else if (m_lastSortResult)
        {
            currentResult = &(*m_lastSortResult);
        }
        else if (m_lastSearchResult)
        {
            currentResult = &(*m_lastSearchResult);
        }

        if (currentResult == nullptr)
        {
            ResultHeaderText().Text(L"Результат операции");
            ResultContentText().Text(L"Здесь появится результат.");
            ResultStatusValueText().Text(L"Ожидание");
            ResultTimeValueText().Text(L"0 мс");
            ResultStepsValueText().Text(L"0");
            return;
        }

        ResultHeaderText().Text(winrt::hstring(ExtractResultHeader(currentResult->resultText)));
        ResultContentText().Text(winrt::hstring(ExtractResultBody(currentResult->resultText)));
        ResultStatusValueText().Text(currentResult->success ? L"Готово" : L"Ошибка");
        ResultTimeValueText().Text(winrt::hstring(FormatMilliseconds(currentResult->stats.executionTime)));

        int stepsValue = currentResult->stats.comparisonCount;
        if (!currentResult->isSearch)
        {
            stepsValue += currentResult->stats.swapCount;
        }

        ResultStepsValueText().Text(winrt::to_hstring(stepsValue));
    }

    void MainWindow::UpdatePerformanceCard()
    {
        int sortComparisons = m_lastSortResult ? m_lastSortResult->stats.comparisonCount : 0;
        int sortSwaps = m_lastSortResult ? m_lastSortResult->stats.swapCount : 0;
        int searchComparisons = m_lastSearchResult ? m_lastSearchResult->stats.comparisonCount : 0;
        int maxValue = (std::max)(
            (std::max)(sortComparisons, sortSwaps),
            (std::max)(searchComparisons, 1));

        auto sortName = m_lastSortResult
            ? m_lastSortResult->algorithmName
            : std::wstring(L"Сортировка");

        auto searchName = m_lastSearchResult
            ? m_lastSearchResult->algorithmName
            : std::wstring(L"Поиск");

        int sortPercent = ClampPercent(sortComparisons, maxValue);
        int swapPercent = ClampPercent(sortSwaps, maxValue);
        int searchPercent = ClampPercent(searchComparisons, maxValue);

        PerformancePrimaryNameText().Text(winrt::hstring(sortName));
        PerformancePrimaryPercentText().Text(winrt::to_hstring(sortPercent) + L"%");
        PerformancePrimaryBar().Value(sortPercent);

        PerformanceSecondaryNameText().Text(L"Перестановки");
        PerformanceSecondaryPercentText().Text(winrt::to_hstring(swapPercent) + L"%");
        PerformanceSecondaryBar().Value(swapPercent);

        PerformanceTertiaryNameText().Text(winrt::hstring(searchName));
        PerformanceTertiaryPercentText().Text(winrt::to_hstring(searchPercent) + L"%");
        PerformanceTertiaryBar().Value(searchPercent);
    }

    int MainWindow::TryGetCurrentElementCount()
    {
        try
        {
            auto text = InputArrayTextBox().Text();
            auto data = m_dataManager.ParseArray(text.c_str());
            return static_cast<int>(data.size());
        }
        catch (...)
        {
            return 0;
        }
    }

    int MainWindow::ClampPercent(int value, int maxValue)
    {
        if (maxValue <= 0 || value <= 0)
        {
            return 0;
        }

        return (std::max)(1, static_cast<int>((100.0 * value) / maxValue));
    }

    std::wstring MainWindow::FormatMilliseconds(double value)
    {
        std::wstringstream stream;
        stream << static_cast<int>(value + 0.5) << L" мс";
        return stream.str();
    }

    std::wstring MainWindow::ExtractResultHeader(std::wstring const& resultText)
    {
        auto separator = resultText.find(L"\r\n");
        if (separator == std::wstring::npos)
        {
            return L"Результат операции";
        }

        return resultText.substr(0, separator);
    }

    std::wstring MainWindow::ExtractResultBody(std::wstring const& resultText)
    {
        auto separator = resultText.find(L"\r\n");
        if (separator == std::wstring::npos)
        {
            return resultText;
        }

        auto body = resultText.substr(separator + 2);
        return body.empty() ? L"-" : body;
    }
}