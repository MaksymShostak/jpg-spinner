﻿

#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------

namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class Slider;
            }
        }
    }
}

namespace JPG_Spinner
{
    partial ref class SettingsFlyout : public ::Windows::UI::Xaml::Controls::SettingsFlyout, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::Slider^ SliderMemory;
        private: ::Windows::UI::Xaml::Controls::Slider^ SliderProcessor;
    };
}
