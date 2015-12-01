/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2015 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_SLIDER2D_HPP
#define TGUI_SLIDER2D_HPP


#include <TGUI/Widgets/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
namespace ext
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief 2D Slider widget
    ///
    /// Signals:
    ///     - ValueChanged (The value of the slider has changed)
    ///         * Optional parameter sf::Vector2f: New value
    ///         * Uses Callback member 'value2d'
    ///
    ///     - ThumbReturnedToCenter
    ///         * Optional parameter sf::Vector2f: New value
    ///         * Uses Callback member 'value2d'
    ///
    ///     - Inherited signals from ClickableWidget
    ///
    /// This widget may be removed in a future release of TGUI.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Slider2d : public ClickableWidget
    {
    public:

        typedef std::shared_ptr<Slider2d> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const Slider2d> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Slider2d(const Texture& trackNormal, const Texture& thumbNormal, const Texture& trackHover = {}, const Texture& thumbHover = {});


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another slider
        ///
        /// @param slider  The other slider
        ///
        /// @return The new slider
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Slider2d::Ptr copy(Slider2d::ConstPtr slider);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a minimum value.
        ///
        /// @param minimum  The new minimum value
        ///
        /// When the value is too small then it will be changed to this minimum.
        /// The default minimum value is (-1, -1).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMinimum(const sf::Vector2f& minimum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a maximum value.
        ///
        /// @param maximum  The new maximum value
        ///
        /// When the value is too big then it will be changed to this maximum.
        /// The default maximum value is (1, 1).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximum(const sf::Vector2f& maximum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the current value.
        ///
        /// @param value  The new value
        ///
        /// The value can't be smaller than the minimum or bigger than the maximum.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setValue(sf::Vector2f value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the minimum value.
        ///
        /// @return The current minimum value
        ///
        /// The default minimum value (-1, -1).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getMinimum() const
        {
            return m_minimum;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum value.
        ///
        /// @return The current maximum value
        ///
        /// The default maximum value (1, 1).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getMaximum() const
        {
            return m_maximum;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current value.
        ///
        /// @return The current value
        ///
        /// The default value is (0, 0).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getValue() const
        {
            return m_value;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change whether the thumb size changes when you change the size of the slider.
        ///
        /// @param fixedSize  If true then the size of the thumb doesn't change when calling setSize
        ///
        /// When fixedSize is set to false then the thumb will change size together with the slider.
        /// So if the slider is two times bigger than the loaded image, the thumb will also be two times bigger as its image.
        /// When fixedSize is set to true then the size of the thumb will always stay the same as the loaded image.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFixedThumbSize(bool fixedSize)
        {
            m_fixedThumbSize = fixedSize;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the thumb size changes when you change the size of the slider.
        ///
        /// @return whether the thumb size changes when you change the size of the slider
        ///
        /// @see setFixedThumbSize
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getFixedThumbSize() const
        {
            return m_fixedThumbSize;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Decide whether or not the thumb will jump back to the center when the mouse is released.
        ///
        /// @param autoCenterThumb  Place the thumb in the center on mouse release?
        ///
        /// This behavior is disabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void enableThumbCenter(bool autoCenterThumb);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Places the thumb back in the center.
        ///
        /// When enableThumbCenter(true) was called then this will happen automatically when the mouse is released.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void centerThumb();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetFocused() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() const override
        {
            return std::make_shared<Slider2d>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        sf::Vector2f m_minimum = {-1, -1};
        sf::Vector2f m_maximum = {1, 1};
        sf::Vector2f m_value = {0, 0};

        bool m_returnThumbToCenter = false;
        bool m_fixedThumbSize = true;

        Texture m_textureThumbNormal;
        Texture m_textureThumbHover;
        Texture m_textureTrackNormal;
        Texture m_textureTrackHover;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // ext
} // tgui

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SLIDER2D_HPP
