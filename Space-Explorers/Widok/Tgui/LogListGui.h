#pragma once
#include <TGUI\TGUI.hpp>
#include "PomocniczeTypyTGUI.h"

namespace tgui{

	/**
	* \brief Klasa kontrolki wy�wietlaj�cej logi.
	*
	* Klasa reprezentuje kontrolk� wy�wietlaj�cej logi.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuni�cie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 3
	* \date 13-11-2015
	*/
	class LogListGui :
		public ChatBox
	{
	public:
		typedef std::shared_ptr<LogListGui> Ptr; ///< Shared widget pointer
		typedef std::shared_ptr<const LogListGui> ConstPtr; ///< Shared constant widget pointer

		/**
		* \brief Klasa opisuj�ca typ kounikatu w logach.
		*
		* Klasa reprezentuje typ komunikatu wy�wietlanego w kontrolce log�w.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		struct MessageTypeDescription{

			/**
			* \brief Konstruktor obiektu.
			*
			* Konstruktor obiektu.
			* \param[in] pierwszyKolor - Pierwszy kolor komunikatu.
			* \param[in] drugiKolor - Drugi kolor komunikatu.
			* \param[in] pierwszyRozmiarCzcionki - Pierwszy rozmiar czcionki komunikatu.
			* \param[in] drugiRozmiarCzcionki - Drugi rozmiar czcionki komunikatu.
			* \author Daniel Wojdak
			* \version 2
			* \date 30-09-2014
			*/
			MessageTypeDescription(const sf::Color& pierwszyKolor, const sf::Color& drugiKolor, unsigned int pierwszyRozmiarCzcionki, unsigned int drugiRozmiarCzcionki)
				: pierwszyKolor_(pierwszyKolor), drugiKolor_(drugiKolor), pierwszyRozmiarCzcionki_(pierwszyRozmiarCzcionki), drugiRozmiarCzcionki_(drugiRozmiarCzcionki)
			{
			}
			
			sf::Color pierwszyKolor_; /// Pierwszy kolor komunikatu.
			sf::Color drugiKolor_; /// Drugi kolor komunikatu.
			unsigned int pierwszyRozmiarCzcionki_; /// Pierwszy rozmiar czcionki komunikatu.
			unsigned int drugiRozmiarCzcionki_; /// Drugi rozmiar czcionki komunikatu.
		};

		LogListGui();


		LogListGui(const LogListGui& copy);


		LogListGui& operator= (const LogListGui& right);

		static LogListGui::Ptr copy(LogListGui::ConstPtr chatBox);

		typedef std::vector<MessageTypeDescription>::size_type MessageType; /// Typ okre�laj�cy numer u�ytego komunikatu.
		
		/**
		* \brief Metoda dodaj�ca komunikat do listy.
		*
		* Metoda dodaje komunikat do listy wy�wietlanych komunikat�w.
		* \param[in] numer - Numer okre�laj�cy rodzaj komunikatu.
		* \param[in] tekst - Tekst komunikatu.
		* \return Zwracana jest warto�� true, je�eli uda�o sie doda� komunikat lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool addMessage( MessageType numer, std::string tekst);

		/**
		* \brief Metoda czyszcz�ca list� komunikat�w.
		*
		* Metoda czy�ci list� wy�wietlanych komunikat�w.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void clear();


	protected:
				
		virtual Widget::Ptr clone() const override
		{
			return std::make_shared<LogListGui>(*this);
		}
		
		std::vector<MessageTypeDescription> opisTypowKomunikatow_; /// Lista opis�w typ�w komunikat�w
		
	};

};
