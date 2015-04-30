﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
#include "pch.h"
#include "XamlTypeInfo.g.h"

#include "ExplanationCrop.xaml.h"
#include "ExplanationProgressive.xaml.h"
#include "ItemViewer.xaml.h"
#include "App.xaml.h"
#include "MainPage.xaml.h"
#include "Scenario_AfterPick.xaml.h"
#include "WebPage.xaml.h"

#include "ExplanationCrop.g.hpp"
#include "ExplanationProgressive.g.hpp"
#include "ItemViewer.g.hpp"
#include "App.g.hpp"
#include "MainPage.g.hpp"
#include "Scenario_AfterPick.g.hpp"
#include "WebPage.g.hpp"

::Platform::Collections::Vector<::Windows::UI::Xaml::Markup::IXamlMetadataProvider^>^ ::XamlTypeInfo::InfoProvider::XamlTypeInfoProvider::OtherProviders::get()
{
    if(_otherProviders == nullptr)
    {
        _otherProviders = ref new ::Platform::Collections::Vector<::Windows::UI::Xaml::Markup::IXamlMetadataProvider^>();
    }
    return _otherProviders;
}

::Windows::UI::Xaml::Markup::IXamlType^ ::XamlTypeInfo::InfoProvider::XamlTypeInfoProvider::CheckOtherMetadataProvidersForName(::Platform::String^ typeName)
{
    ::Windows::UI::Xaml::Markup::IXamlType^ foundXamlType = nullptr;
    for (unsigned int i = 0; i < OtherProviders->Size; i++)
    {
        auto xamlType = OtherProviders->GetAt(i)->GetXamlType(typeName);
        if(xamlType != nullptr)
        {
            if(xamlType->IsConstructible)    // not Constructible means it might be a Return Type Stub
            {
                return xamlType;
            }
            foundXamlType = xamlType;
        }
    }
    return foundXamlType;
}

::Windows::UI::Xaml::Markup::IXamlType^ ::XamlTypeInfo::InfoProvider::XamlTypeInfoProvider::CheckOtherMetadataProvidersForType(::Windows::UI::Xaml::Interop::TypeName t)
{
    ::Windows::UI::Xaml::Markup::IXamlType^ foundXamlType = nullptr;
    for (unsigned int i = 0; i < OtherProviders->Size; i++)
    {
        auto xamlType = OtherProviders->GetAt(i)->GetXamlType(t);
        if(xamlType != nullptr)
        {
            if(xamlType->IsConstructible)    // not Constructible means it might be a Return Type Stub
            {
                return xamlType;
            }
            foundXamlType = xamlType;
        }
    }
    return foundXamlType;
}

::Windows::UI::Xaml::Markup::IXamlType^ ::XamlTypeInfo::InfoProvider::XamlTypeInfoProvider::CreateXamlType(::Platform::String^ typeName)
{
    if (typeName == L"Windows.UI.Xaml.Controls.Page")
    {
        return ref new XamlSystemBaseType(typeName);
    }

    if (typeName == L"Windows.UI.Xaml.Controls.UserControl")
    {
        return ref new XamlSystemBaseType(typeName);
    }

    if (typeName == L"Int32")
    {
        return ref new XamlSystemBaseType(typeName);
    }

    if (typeName == L"Object")
    {
        return ref new XamlSystemBaseType(typeName);
    }

    if (typeName == L"Windows.UI.Xaml.Media.ImageSource")
    {
        return ref new XamlSystemBaseType(typeName);
    }

    if (typeName == L"String")
    {
        return ref new XamlSystemBaseType(typeName);
    }

    if (typeName == L"UInt32")
    {
        return ref new XamlSystemBaseType(typeName);
    }

    if (typeName == L"Windows.UI.Xaml.Media.Imaging.WriteableBitmap")
    {
        return ref new XamlSystemBaseType(typeName);
    }

    if (typeName == L"JPG_Spinner.ExplanationCrop")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, GetXamlTypeByName(L"Windows.UI.Xaml.Controls.Page"));
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Custom;
        userType->Activator =
            []() -> Platform::Object^ 
            {
                return ref new ::JPG_Spinner::ExplanationCrop(); 
            };
        userType->SetIsLocalType();
        return userType;
    }

    if (typeName == L"JPG_Spinner.ExplanationProgressive")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, GetXamlTypeByName(L"Windows.UI.Xaml.Controls.Page"));
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Custom;
        userType->Activator =
            []() -> Platform::Object^ 
            {
                return ref new ::JPG_Spinner::ExplanationProgressive(); 
            };
        userType->SetIsLocalType();
        return userType;
    }

    if (typeName == L"JPG_Spinner.ItemViewer")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, GetXamlTypeByName(L"Windows.UI.Xaml.Controls.UserControl"));
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Custom;
        userType->Activator =
            []() -> Platform::Object^ 
            {
                return ref new ::JPG_Spinner::ItemViewer(); 
            };
        userType->SetIsLocalType();
        return userType;
    }

    if (typeName == L"JPG_Spinner.MainPage")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, GetXamlTypeByName(L"Windows.UI.Xaml.Controls.Page"));
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Custom;
        userType->Activator =
            []() -> Platform::Object^ 
            {
                return ref new ::JPG_Spinner::MainPage(); 
            };
        userType->AddMemberName(L"cts");
        userType->AddMemberName(L"ProgressiveChecked");
        userType->AddMemberName(L"CropChecked");
        userType->SetIsLocalType();
        return userType;
    }

    if (typeName == L"Windows.Foundation.IReference`1<Int32>")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, nullptr);
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Metadata;
        userType->SetIsReturnTypeStub();
        return userType;
    }

    if (typeName == L"JPG_Spinner.Scenario_AfterPick")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, GetXamlTypeByName(L"Windows.UI.Xaml.Controls.Page"));
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Custom;
        userType->Activator =
            []() -> Platform::Object^ 
            {
                return ref new ::JPG_Spinner::Scenario_AfterPick(); 
            };
        userType->SetIsLocalType();
        return userType;
    }

    if (typeName == L"JPG_Spinner.WebPage")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, GetXamlTypeByName(L"Windows.UI.Xaml.Controls.Page"));
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Custom;
        userType->Activator =
            []() -> Platform::Object^ 
            {
                return ref new ::JPG_Spinner::WebPage(); 
            };
        userType->SetIsLocalType();
        return userType;
    }

    if (typeName == L"JPG_Spinner.Item")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, GetXamlTypeByName(L"Object"));
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Custom;
        userType->Activator =
            []() -> Platform::Object^ 
            {
                return ref new ::JPG_Spinner::Item(); 
            };
        userType->AddMemberName(L"OrientationFlag");
        userType->AddMemberName(L"Image");
        userType->AddMemberName(L"Error");
        userType->AddMemberName(L"Title");
        userType->AddMemberName(L"MRUToken");
        userType->AddMemberName(L"ID");
        userType->AddMemberName(L"StorageFile");
        userType->SetIsBindable();
        userType->SetIsLocalType();
        return userType;
    }

    if (typeName == L"Byte")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, GetXamlTypeByName(L"System.ValueType"));
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Metadata;
        userType->SetIsReturnTypeStub();
        return userType;
    }

    if (typeName == L"System.ValueType")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, GetXamlTypeByName(L"Object"));
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Metadata;
        return userType;
    }

    if (typeName == L"Windows.Storage.StorageFile")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, GetXamlTypeByName(L"Object"));
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Metadata;
        userType->SetIsReturnTypeStub();
        return userType;
    }

    if (typeName == L"JPG_Spinner.ProgressiveDataItem")
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(this, typeName, GetXamlTypeByName(L"Object"));
        userType->KindOfType = ::Windows::UI::Xaml::Interop::TypeKind::Custom;
        userType->AddMemberName(L"Image");
        userType->AddMemberName(L"Caption");
        userType->SetIsBindable();
        userType->SetIsLocalType();
        return userType;
    }

    return nullptr;
}

::Windows::UI::Xaml::Markup::IXamlMember^ ::XamlTypeInfo::InfoProvider::XamlTypeInfoProvider::CreateXamlMember(::Platform::String^ longMemberName)
{
    if (longMemberName == L"JPG_Spinner.MainPage.cts")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"cts", L"Windows.Foundation.IReference`1<Int32>");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::MainPage^)instance;
                return that->cts;
            };

        xamlMember->SetIsReadOnly();
        return xamlMember;
    }

    if (longMemberName == L"JPG_Spinner.MainPage.ProgressiveChecked")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"ProgressiveChecked", L"Int32");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::MainPage^)instance;
                auto value = ref new ::Platform::Box<::default::int32>(that->ProgressiveChecked);
                return value;
            };

        xamlMember->Setter =
            [](Object^ instance, Object^ value) -> void
            {
                auto that = (::JPG_Spinner::MainPage^)instance;
                auto boxedValue = (::Platform::IBox<::default::int32>^)value;
                that->ProgressiveChecked = boxedValue->Value;
            };
        return xamlMember;
    }

    if (longMemberName == L"JPG_Spinner.MainPage.CropChecked")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"CropChecked", L"Int32");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::MainPage^)instance;
                auto value = ref new ::Platform::Box<::default::int32>(that->CropChecked);
                return value;
            };

        xamlMember->Setter =
            [](Object^ instance, Object^ value) -> void
            {
                auto that = (::JPG_Spinner::MainPage^)instance;
                auto boxedValue = (::Platform::IBox<::default::int32>^)value;
                that->CropChecked = boxedValue->Value;
            };
        return xamlMember;
    }

    if (longMemberName == L"JPG_Spinner.Item.OrientationFlag")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"OrientationFlag", L"Byte");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::Item^)instance;
                auto value = ref new ::Platform::Box<::default::uint8>(that->OrientationFlag);
                return value;
            };

        xamlMember->Setter =
            [](Object^ instance, Object^ value) -> void
            {
                auto that = (::JPG_Spinner::Item^)instance;
                auto boxedValue = (::Platform::IBox<::default::uint8>^)value;
                that->OrientationFlag = boxedValue->Value;
            };
        return xamlMember;
    }

    if (longMemberName == L"JPG_Spinner.Item.Image")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"Image", L"Windows.UI.Xaml.Media.ImageSource");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::Item^)instance;
                return that->Image;
            };

        xamlMember->Setter =
            [](Object^ instance, Object^ value) -> void
            {
                auto that = (::JPG_Spinner::Item^)instance;
                that->Image = (::Windows::UI::Xaml::Media::ImageSource^)value;
            };
        return xamlMember;
    }

    if (longMemberName == L"JPG_Spinner.Item.Error")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"Error", L"String");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::Item^)instance;
                return that->Error;
            };

        xamlMember->Setter =
            [](Object^ instance, Object^ value) -> void
            {
                auto that = (::JPG_Spinner::Item^)instance;
                that->Error = (::Platform::String^)value;
            };
        return xamlMember;
    }

    if (longMemberName == L"JPG_Spinner.Item.Title")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"Title", L"String");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::Item^)instance;
                return that->Title;
            };

        xamlMember->Setter =
            [](Object^ instance, Object^ value) -> void
            {
                auto that = (::JPG_Spinner::Item^)instance;
                that->Title = (::Platform::String^)value;
            };
        return xamlMember;
    }

    if (longMemberName == L"JPG_Spinner.Item.MRUToken")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"MRUToken", L"String");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::Item^)instance;
                return that->MRUToken;
            };

        xamlMember->Setter =
            [](Object^ instance, Object^ value) -> void
            {
                auto that = (::JPG_Spinner::Item^)instance;
                that->MRUToken = (::Platform::String^)value;
            };
        return xamlMember;
    }

    if (longMemberName == L"JPG_Spinner.Item.ID")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"ID", L"UInt32");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::Item^)instance;
                auto value = ref new ::Platform::Box<::default::uint32>(that->ID);
                return value;
            };

        xamlMember->Setter =
            [](Object^ instance, Object^ value) -> void
            {
                auto that = (::JPG_Spinner::Item^)instance;
                auto boxedValue = (::Platform::IBox<::default::uint32>^)value;
                that->ID = boxedValue->Value;
            };
        return xamlMember;
    }

    if (longMemberName == L"JPG_Spinner.Item.StorageFile")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"StorageFile", L"Windows.Storage.StorageFile");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::Item^)instance;
                return that->StorageFile;
            };

        xamlMember->Setter =
            [](Object^ instance, Object^ value) -> void
            {
                auto that = (::JPG_Spinner::Item^)instance;
                that->StorageFile = (::Windows::Storage::StorageFile^)value;
            };
        return xamlMember;
    }

    if (longMemberName == L"JPG_Spinner.ProgressiveDataItem.Image")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"Image", L"Windows.UI.Xaml.Media.Imaging.WriteableBitmap");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::ProgressiveDataItem^)instance;
                return that->Image;
            };

        xamlMember->Setter =
            [](Object^ instance, Object^ value) -> void
            {
                auto that = (::JPG_Spinner::ProgressiveDataItem^)instance;
                that->Image = (::Windows::UI::Xaml::Media::Imaging::WriteableBitmap^)value;
            };
        return xamlMember;
    }

    if (longMemberName == L"JPG_Spinner.ProgressiveDataItem.Caption")
    {
        ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(this, L"Caption", L"String");
        xamlMember->Getter =
            [](Object^ instance) -> Object^
            {
                auto that = (::JPG_Spinner::ProgressiveDataItem^)instance;
                return that->Caption;
            };

        xamlMember->Setter =
            [](Object^ instance, Object^ value) -> void
            {
                auto that = (::JPG_Spinner::ProgressiveDataItem^)instance;
                that->Caption = (::Platform::String^)value;
            };
        return xamlMember;
    }

    return nullptr;
}

