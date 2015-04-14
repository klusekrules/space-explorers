/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_CHILD_WINDOW_HPP
#define TGUI_CHILD_WINDOW_HPP


#include <TGUI/Container.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
	class Button;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief Movable Panel with title bar.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class TGUI_API ChildWindow : public Container, public WidgetBorders
	{
	public:

		static Widget* createWidget(Container*, const std::string& name);

		typedef SharedWidgetPtr<ChildWindow> Ptr;


		/// Title alignments, possible options for the setTitleAlignment function
		enum TitleAlignment
		{
			/// Places the title on the left side of the title bar
			TitleAlignmentLeft,

			/// Places the title in the middle of the title bar
			TitleAlignmentCentered,

			/// Places the title on the right side of the title bar
			TitleAlignmentRight
		};


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ChildWindow();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Copy constructor
		///
		/// \param copy  Instance to copy
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ChildWindow(const ChildWindow& copy);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Destructor
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual ~ChildWindow();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Overload of assignment operator
		///
		/// \param right  Instance to assign
		///
		/// \return Reference to itself
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ChildWindow& operator= (const ChildWindow& right);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \internal
		// Makes a copy of the widget by calling the copy constructor.
		// This function calls new and if you use this function then you are responsible for calling delete.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual ChildWindow* clone();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Loads the widget.
		///
		/// \param configFileFilename  Filename of the config file.
		///
		/// The config file must contain a ChildWindow section with the needed information.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool load(const std::string& configFileFilename);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the filename of the config file that was used to load the widget.
		///
		/// \return Filename of loaded config file.
		///         Empty string when no config file was loaded yet.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const std::string& getLoadedConfigFile() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Changes the size of the child window.
		///
		/// \param width   Sets the new width of the child window
		/// \param height  Sets the new height of the child window
		///
		/// The width and height are the size of the child window, without the title bar nor the borders.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setSize(float width, float height);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the size of the drawable area of the child window.
		///
		/// \return Size of the child window
		///
		/// The size returned by this function is the size of the child window, without the title bar nor the borders.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual sf::Vector2f getSize() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the size of the full child window.
		///
		/// \return Size of the child window
		///
		/// The size returned by this function is the size of the child window, including the title bar and the borders.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual sf::Vector2f getFullSize() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Changes the background texture of the child window.
		///
		/// \param texture  Pointer to the texture that should be used as background of the child window
		///
		/// \warning You should make sure that the texture stays alive.
		///
		/// If the texture has a different size than the child window then it will be scaled to fill the whole window.
		/// Pass nullptr to this function to remove the background texture.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setBackgroundTexture(sf::Texture *const texture = nullptr);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the background texture of the child window.
		///
		/// \return Pointer to the texture that is being used as background of the child window.
		///         This pointer is nullptr when no background texture was set.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		sf::Texture* getBackgroundTexture();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Change the height of the title bar.
		///
		/// \param height  New height of the title bar
		///
		/// The default height is the height of the title bar image that is loaded with the load function.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setTitleBarHeight(unsigned int height);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the height of the title bar.
		///
		/// \return Height of the title bar
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		unsigned int getTitleBarHeight() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Changes the background color of the child window.
		///
		/// \param backgroundColor  New background color
		///
		/// The background is fully transparent by default.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setBackgroundColor(const sf::Color& backgroundColor);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the background color of the panel.
		///
		/// The background is fully transparent by default.
		///
		/// \return The current background color
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const sf::Color& getBackgroundColor() const;


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
		/// \brief Changes the title that is displayed in the title bar of the child window.
		///
		/// \param title  New title for the child window
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setTitle(const sf::String& title);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the title that is displayed in the title bar of the child window.
		///
		/// \return Title of the child window
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const sf::String& getTitle() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Changes the color of the title that is displayed in the title bar of the child window.
		///
		/// \param color  New title color for the child window
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setTitleColor(const sf::Color& color);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the color of the title that is displayed in the title bar of the child window.
		///
		/// \return Title color of the child window
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const sf::Color& getTitleColor() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Set the border color.
		///
		/// \param borderColor  The color of the borders
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setBorderColor(const sf::Color& borderColor);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the borde color.
		///
		/// \return The color of the borders
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const sf::Color& getBorderColor() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Changes the size of the borders.
		///
		/// \param leftBorder    The width of the left border
		/// \param topBorder     The height of the top border
		/// \param rightBorder   The width of the right border
		/// \param bottomBorder  The height of the bottom border
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void setBorders(unsigned int leftBorder = 0,
			unsigned int topBorder = 0,
			unsigned int rightBorder = 0,
			unsigned int bottomBorder = 0);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Changes the distance between the title and the side of the title bar.
		///
		/// \param distanceToSide  distance between the title and the side of the title bar
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setDistanceToSide(unsigned int distanceToSide);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the distance between the title and the side of the title bar.
		///
		/// \return distance between the title and the side of the title bar
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		unsigned int getDistanceToSide() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Changes the title alignment.
		///
		/// \param alignment  How should the title be aligned in the title bar?
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setTitleAlignment(TitleAlignment alignment);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the title alignment.
		///
		/// \return How the title is aligned in the title bar
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		TitleAlignment getTitleAlignment() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Changes the icon in the top left corner of the child window.
		///
		/// \param filename  Filename of the icon image
		///
		/// There is no icon by default.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setIcon(const std::string& filename);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Removes the icon in the top left corner of the child window.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void removeIcon();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Destroys the window.
		///
		/// When no callback is requested when closing the window, this function will be called automatically.
		///
		/// When you requested a callback then you get the opportunity to cancel the closure of the window.
		/// If you want to keep it open then don't do anything, if you want to close it then just call this function.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void destroy();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Set the child window to be kept inside its parent.
		///
		/// \param enabled  When it's set to true, the child window will always be kept automatically inside its parent.
		///                 It will be fully kept on left, right and top.
		///                 At the bottom of the parent only the title bar will be kept inside.
		///                 It's set to false by default.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void keepInParent(bool enabled);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Tells whether the child window is kept inside its parent.
		///
		/// \return  When it's set to true, the child window will always be kept automatically inside its parent.
		///          It will be fully kept on left, right and top.
		///          At the bottom of the parent only the title bar will be kept inside.
		///          It's set to false by default.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isKeptInParent();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Set the position of the widget
		///
		/// This function completely overwrites the previous position.
		/// See the move function to apply an offset based on the previous position instead.
		/// The default position of a transformable widget is (0, 0).
		///
		/// \param x X coordinate of the new position
		/// \param y Y coordinate of the new position
		///
		/// \see move, getPosition
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setPosition(float x, float y);
		using Transformable::setPosition;


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
		virtual void mouseNoLongerDown();


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
	protected:

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \internal
		// This function is called when the widget is added to a container.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void initialize(Container *const container);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \internal
		// Draws the widget on the render target.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Defines specific triggers to ChildWindow.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		enum ChildWindowCallbacks
		{
			LeftMousePressed = WidgetCallbacksCount * 1,             ///< The left mouse button was pressed (child window was thus brough to front)
			Closed = WidgetCallbacksCount * 2,                       ///< Child window was closed
			Moved = WidgetCallbacksCount * 4,                        ///< Child window was moved
			//            Resized = WidgetCallbacksCount * 8,
			AllChildWindowCallbacks = WidgetCallbacksCount * 16 - 1, ///< All triggers defined in ChildWindow and its base classes
			ChildWindowCallbacksCount = WidgetCallbacksCount * 16
		};


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	protected:

		std::string    m_LoadedConfigFile;

		sf::Vector2f   m_Size;

		sf::Color      m_BackgroundColor;
		sf::Texture*   m_BackgroundTexture;
		sf::Sprite     m_BackgroundSprite;

		Texture        m_IconTexture;

		sf::Text       m_TitleText;
		unsigned int   m_TitleBarHeight;
		bool           m_SplitImage;
		sf::Vector2f   m_DraggingPosition;
		unsigned int   m_DistanceToSide;
		TitleAlignment m_TitleAlignment;
		sf::Color      m_BorderColor;

		Texture   m_TextureTitleBar_L;
		Texture   m_TextureTitleBar_M;
		Texture   m_TextureTitleBar_R;

		Button*  m_CloseButton;

		bool m_KeepInParent;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CHILD_WINDOW_HPP
