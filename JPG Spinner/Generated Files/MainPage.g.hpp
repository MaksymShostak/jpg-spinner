﻿

//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "MainPage.xaml.h"




void ::JPG_Spinner::MainPage::InitializeComponent()
{
    if (_contentLoaded)
        return;

    _contentLoaded = true;

    // Call LoadComponent on ms-appx:///MainPage.xaml
    ::Windows::UI::Xaml::Application::LoadComponent(this, ref new ::Windows::Foundation::Uri(L"ms-appx:///MainPage.xaml"), ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);

    // Get the Grid named 'LeftPane'
    LeftPane = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"LeftPane"));
    // Get the StackPanel named 'imagePanel'
    imagePanel = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"imagePanel"));
    // Get the Image named 'displayImage'
    displayImage = safe_cast<::Windows::UI::Xaml::Controls::Image^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"displayImage"));
    // Get the GridView named 'GridViewSelection'
    GridViewSelection = safe_cast<::Windows::UI::Xaml::Controls::GridView^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"GridViewSelection"));
    // Get the TextBlock named 'filePath'
    filePath = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"filePath"));
    // Get the TextBlock named 'OrientationFlag'
    OrientationFlag = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"OrientationFlag"));
    // Get the TextBlock named 'DebugText'
    DebugText = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"DebugText"));
    // Get the StackPanel named 'FooterPanel'
    FooterPanel = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"FooterPanel"));
    // Get the Border named 'StatusBorder'
    StatusBorder = safe_cast<::Windows::UI::Xaml::Controls::Border^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"StatusBorder"));
    // Get the TextBlock named 'StatusBlock'
    StatusBlock = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"StatusBlock"));
    // Get the CheckBox named 'CheckBoxProgressive'
    CheckBoxProgressive = safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"CheckBoxProgressive"));
    // Get the TextBlock named 'TextBlockProgressive'
    TextBlockProgressive = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"TextBlockProgressive"));
    // Get the CheckBox named 'CheckBoxTrim'
    CheckBoxTrim = safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"CheckBoxTrim"));
    // Get the TextBlock named 'TextBlockTrim'
    TextBlockTrim = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"TextBlockTrim"));
    // Get the TextBlock named 'SampleTitle'
    SampleTitle = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"SampleTitle"));
}

void ::JPG_Spinner::MainPage::Connect(int connectionId, Platform::Object^ target)
{
    switch (connectionId)
    {
    case 1:
        (safe_cast<::Windows::UI::Xaml::Controls::Primitives::ButtonBase^>(target))->Click +=
            ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::JPG_Spinner::MainPage::*)(Platform::Object^, Windows::UI::Xaml::RoutedEventArgs^))&MainPage::Button_Click);
        break;
    }
    (void)connectionId; // Unused parameter
    (void)target; // Unused parameter
    _contentLoaded = true;
}

