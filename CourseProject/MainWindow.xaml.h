#pragma once

#include "MainWindow.g.h"
#include <optional>
#include "Services/DataManager.h"
#include "Services/Analyzer.h"

namespace winrt::CourseProject::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void MainWindow_Activated(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& e);

        void GenerateArrayButton_Click(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void Button_PointerEntered(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);

        void Button_PointerExited(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);

        void FloatingTextBox_StateChanged(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void FloatingTextBox_TextChanged(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);

        void ComboBox_Loaded(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void ComboBox_DropDownOpened(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::Foundation::IInspectable const& e);

        void ComboBox_DropDownClosed(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::Foundation::IInspectable const& e);

        void ClearButton_Click(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void SortButton_Click(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void SearchButton_Click(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        void ConfigureWindowChrome();
        void UpdateFloatingTextBoxState(
            winrt::Microsoft::UI::Xaml::Controls::TextBox const& textBox);
        void UpdateComboBoxState(
            winrt::Microsoft::UI::Xaml::Controls::ComboBox const& comboBox);
        void ResetDashboard();
        void RefreshDashboard();
        void UpdateQuickMetrics();
        void UpdateResultCard();
        void UpdatePerformanceCard();
        int TryGetCurrentElementCount();
        int ClampPercent(int value, int maxValue);
        std::wstring FormatMilliseconds(double value);
        std::wstring ExtractResultHeader(std::wstring const& resultText);
        std::wstring ExtractResultBody(std::wstring const& resultText);

        DataManager m_dataManager;
        Analyzer m_analyzer;
        std::optional<AnalysisResult> m_lastSortResult;
        std::optional<AnalysisResult> m_lastSearchResult;
        bool m_lastOperationWasSearch{ false };
        bool m_windowChromeConfigured{ false };
    };
}

namespace winrt::CourseProject::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}