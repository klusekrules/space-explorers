#pragma once
#include <TGUI\TGUI.hpp>
#include "PomocniczeTypyTGUI.h"

namespace tgui{

	/**
	* \brief Klasa kontrolki wyświetlającej logi.
	*
	* Klasa reprezentuje kontrolkę wyświetlającej logi.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesunięcie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 3
	* \date 13-11-2015
	*/
	class LogListGui :
		public ChatBox
	{
	public:
		typedef std::shared_ptr<LogListGui> Ptr;
		typedef std::shared_ptr<const LogListGui> ConstPtr;

		/**
		* \brief Klasa opisująca typ kounikatu w logach.
		*
		* Klasa reprezentuje typ komunikatu wyświetlanego w kontrolce logów.
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

		typedef std::vector<MessageTypeDescription>::size_type MessageType; /// Typ określający numer użytego komunikatu.
		
		/**
		* \brief Metoda dodająca komunikat do listy.
		*
		* Metoda dodaje komunikat do listy wyświetlanych komunikatów.
		* \param[in] numer - Numer określający rodzaj komunikatu.
		* \param[in] tekst - Tekst komunikatu.
		* \return Zwracana jest wartość true, jeżeli udało sie dodać komunikat lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool addMessage( MessageType numer, std::string tekst);

		/**
		* \brief Metoda czyszcząca listę komunikatów.
		*
		* Metoda czyści listę wyświetlanych komunikatów.
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
		
		std::vector<MessageTypeDescription> opisTypowKomunikatow_; /// Lista dostępnych opisów komunikatów.
		
		std::vector<MessageType> powiazaniaKontrolek_; /// Lista powiązań opisów komunikatów z kontrolkami wyświetlającymi.
	};

};
