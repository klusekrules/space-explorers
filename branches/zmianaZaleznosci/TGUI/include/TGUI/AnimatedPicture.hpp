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


#ifndef TGUI_ANIMATED_PICTURE_HPP
#define TGUI_ANIMATED_PICTURE_HPP

#include <TGUI/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief Load multiple images and add then behind each other to create a simple animation or even a movie.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class TGUI_API AnimatedPicture : public ClickableWidget
	{
	public:

		static Widget* createWidget(Container*, const std::string& name);

		typedef SharedWidgetPtr<AnimatedPicture> Ptr;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimatedPicture();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Copy constructor
		///
		/// \param copy  Instance to copy
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimatedPicture(const AnimatedPicture& copy);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Destructor
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual ~AnimatedPicture();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Overload of assignment operator
		///
		/// \param right  Instance to assign
		///
		/// \return Reference to itself
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimatedPicture& operator= (const AnimatedPicture& right);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \internal
		// Makes a copy of the widget by calling the copy constructor.
		// This function calls new and if you use this function then you are responsible for calling delete.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual AnimatedPicture* clone();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Load another image/frame from a file.
		///
		/// \param filename       The filename of the image that you want to use as next frame.
		/// \param frameDuration  The amount of time that the frame will be displayed on the screen.
		///                       When the duration is 0 (default) then the animation will be blocked at that frame.
		///
		/// \return True when the frame was loaded.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool addFrame(const std::string& filename, sf::Time frameDuration = sf::Time());


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Changes the size of the displayed image.
		///
		/// \param width   The new width of the picture
		/// \param height  The new height of the picture
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setSize(float width, float height);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the size of the the displayed image.
		///
		/// \return Size of the picture
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual sf::Vector2f getSize() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Starts or resumes playing the animation.
		///
		/// \see pause
		/// \see stop
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void play();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Pauses the animation.
		///
		/// You can continue the animation with the start() function.
		///
		/// \see play
		/// \see stop
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void pause();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Stops the animation.
		///
		/// When calling start() after calling this function, the animation will restart from the first frame.
		///
		/// \see play
		/// \see pause
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void stop();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Sets the animation at a specific frame.
		///
		/// \param frame  The frame that should be displayed
		///
		/// The number is the index of the frame, so the first frame is number 0.
		///
		/// \return True when the frame was selected.
		///         False when the index was too high.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool setFrame(unsigned int frame);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the current displayed frame.
		///
		/// \return Number of the frame that is currently displayed.
		///
		/// The number is the index of the frame, so the first frame is number 0.
		/// If no frames were loaded then this function will return -1.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int getCurrentFrame() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the duration of the currently displayed frame.
		///
		/// \return Duration of the frame that is currently displayed.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		sf::Time getCurrentFrameDuration() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the amount of frames in the animation.
		///
		/// \return Number of frames
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		unsigned int getFrames() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Removes a frame from the animation.
		///
		/// \param frame  The number of the frame to remove
		///
		/// The number is the index of the frame, so the first frame is number 0.
		///
		/// \return True when the frame was removed.
		///         False if the index was too high.
		///
		/// \see removeAllFrames
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool removeFrame(unsigned int frame);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Remove all frames from the animation.
		///
		/// \see removeFrame
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void removeAllFrames();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Turn the looping of the animation on or off.
		///
		/// By default, when this function isn't called, the animation will not loop.
		///
		/// \param loop  Should the animation start over from the beginning when it finishes?
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setLooping(bool loop = true);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns whether the looping of the animation is on or off.
		///
		/// By default, the animation will not loop.
		///
		/// \return Will the animation start over from the beginning when it finishes?
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool getLooping() const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns whether the animation is still playing.
		///
		/// \return Is the animation still playing?
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isPlaying() const;


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
		// When the elapsed time changes then this function is called.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void update();


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \internal
		// Draws the widget on the render target.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Defines specific triggers to AnimatedPicture.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		enum AnimatedPictureCallbacks
		{
			AnimationFinished = ClickableWidgetCallbacksCount * 1,               ///< Animation ended
			AllAnimatedPictureCallbacks = ClickableWidgetCallbacksCount * 2 - 1, ///< All triggers defined in AnimatedPicture and its base classes
			AnimatedPictureCallbacksCount = ClickableWidgetCallbacksCount * 2
		};

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	protected:

		std::vector<Texture>  m_Textures;
		std::vector<sf::Time> m_FrameDuration;

		int m_CurrentFrame;

		bool m_Playing;
		bool m_Looping;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_ANIMATED_PICTURE_HPP

