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


#ifndef TGUI_SCROLLBAR_HPP
#define TGUI_SCROLLBAR_HPP


#include <TGUI/Slider.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Scrollbar : public Widget
    {
      public:

		static Widget* createWidget(Container*, const std::string& name);

        typedef SharedWidgetPtr<Scrollbar> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Scrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Scrollbar(const Scrollbar& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Scrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Scrollbar& operator= (const Scrollbar& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget by calling the copy constructor.
        // This function calls new and if you use this function then you are responsible for calling delete.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Scrollbar* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads the widget.
        ///
        /// \param configFileFilename  Filename of the config file.
        /// \param sectionName         Name of the section in the file to load
        ///
        /// The config file must contain a Scrollbar section with the needed information.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool load(const std::string& configFileFilename, const std::string& sectionName = "Scrollbar");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the filename of the config file that was used to load the widget.
        ///
        /// \return Filename of loaded config file.
        ///         Empty string when no config file was loaded yet.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::string& getLoadedConfigFile() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the scrollbar.
        ///
        /// \param width   The new width of the scrollbar
        /// \param height  The new height of the scrollbar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(float width, float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the scrollbar.
        ///
        /// \return Size of the scrollbar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets a maximum value.
        ///
        /// \param maximum  The new maximum value
        ///
        /// When the value is bigger than (maximum - low value), the value is set to maximum - low value.
        /// The default maximum value is 10.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximum(unsigned int maximum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the current value.
        ///
        /// \param value  The new value
        ///
        /// The value has to be smaller than maximum - low value.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setValue(unsigned int value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the 'low value'.
        ///
        /// \param lowValue  The new low value.
        ///                  In e.g. a list box, this value is the amount of items that fit inside the list box.
        ///
        /// Until the maximum is bigger than this value, no scrollbar will be drawn.
        /// You can however choose to always draw the scrollbar by calling setAutoHide(false).
        /// The default low value is 6.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setLowValue(unsigned int lowValue);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes whether the scrollbar lies vertical or horizontal.
        ///
        /// \param verticallScroll  Does the scrollbar lie vertically?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setVerticalScroll(bool verticallScroll);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the maximum value.
        ///
        /// \return The current maximum value
        ///
        /// The default maximum value is 10.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getMaximum() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the current value.
        ///
        /// \return The current value
        ///
        /// The default value is 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getValue() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the low value.
        ///
        /// \see setLowValue
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getLowValue() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns whether the scrollbar lies vertical or horizontal.
        ///
        /// \return Does the scrollbar lie vertically?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getVerticalScroll() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes how much the value changes when pressing one of the arrows of the scrollbar
        ///
        /// \param scrollAmount  How far should the scrollbar scroll when an arrow is clicked?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setArrowScrollAmount(unsigned int scrollAmount);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns how much the value changes when pressing one of the arrows of the scrollbar
        ///
        /// \return How far should the scrollbar scroll when an arrow is clicked?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getArrowScrollAmount();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes whether the scrollbar should hide automatically or not.
        ///
        /// When true (default), the scrollbar will not be drawn when the maximum is smaller than the low value.
        ///
        /// \param autoHide  Should the scrollbar be invisible when you can't scroll?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setAutoHide(bool autoHide);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns whether the scrollbar is hiding automatically or not.
        ///
        /// When true (default), the scrollbar will not be drawn when the maximum is smaller than the low value.
        /// So when you can't scroll, the scrollbar won't be drawn.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getAutoHide() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the transparency of the widget.
        ///
        /// \param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelMoved(int delta, int x, int y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetFocused();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is a (slow) way to set properties on the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool setProperty(std::string property, const std::string& value);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is a (slow) way to get properties of the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool getProperty(std::string property, std::string& value) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Returns a list of all properties that can be used in setProperty and getProperty.
        // The second value in the pair is the type of the property (e.g. int, uint, string, ...).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the position and size of the thumb
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::FloatRect getThumbRect() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to Scrollbar.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum ScrollbarCallbacks
        {
            ValueChanged = WidgetCallbacksCount * 1,              ///< Value changed (thumb moved)
            AllScrollbarCallbacks = WidgetCallbacksCount * 2 - 1, ///< All triggers defined in Scrollbar and its base classes
            ScrollbarCallbacksCount = WidgetCallbacksCount * 2
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::string m_LoadedConfigFile;

        // When the mouse went down, did it go down on top of the thumb? If so, where?
        bool m_MouseDownOnThumb;
        sf::Vector2f m_MouseDownOnThumbPos;
        sf::Vector2f m_lastMousePos;

        unsigned int m_Maximum;
        unsigned int m_Value;

        // Maximum should be above this value before the scrollbar is needed
        unsigned int m_LowValue;

        // Is the scrollbar draw vertically?
        bool m_VerticalScroll;

        // Does the image lie vertically?
        bool m_VerticalImage;

        // How far should the value change when pressing one of the arrows?
        unsigned int m_ScrollAmount;

        // When no scrollbar is needed, should the scrollbar be drawn or stay hidden?
        bool m_AutoHide;

        // Did the mouse went down on one of the arrows?
        bool m_MouseDownOnArrow;

        // If this is true then the L, M and R images will be used.
        // If it is false then the scrollbar is just one big image that will be stored in the M image.
        bool m_SplitImage;

        // Is there a separate hover image, or is it a semi-transparent image that is drawn on top of the others?
        bool m_SeparateHoverImage;

        // The size of the scrollbar and its thumb
        sf::Vector2f m_Size;
        sf::Vector2f m_ThumbSize;

        Texture m_TextureTrackNormal_L;
        Texture m_TextureTrackHover_L;
        Texture m_TextureTrackNormal_M;
        Texture m_TextureTrackHover_M;
        Texture m_TextureTrackNormal_R;
        Texture m_TextureTrackHover_R;

        Texture m_TextureThumbNormal;
        Texture m_TextureThumbHover;

        Texture m_TextureArrowUpNormal;
        Texture m_TextureArrowUpHover;

        Texture m_TextureArrowDownNormal;
        Texture m_TextureArrowDownHover;

        // ListBox, ComboBox and TextBox can access the scrollbar directly
        friend class ListBox;
        friend class ComboBox;
        friend class TextBox;
        friend class ChatBox;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SCROLLBAR_HPP
