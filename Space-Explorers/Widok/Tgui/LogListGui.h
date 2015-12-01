#pragma once
#include <TGUI\TGUI.hpp>
#include "PomocniczeTypyTGUI.h"

namespace tgui{

	/**
	* \brief Klasa kontrolki wyœwietlaj¹cej logi.
	*
	* Klasa reprezentuje kontrolkê wyœwietlaj¹cej logi.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuniêcie refaktoryzacji do czasu migracji do TGUI v7.
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
		* \brief Klasa opisuj¹ca typ kounikatu w logach.
		*
		* Klasa reprezentuje typ komunikatu wyœwietlanego w kontrolce logów.
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

		typedef std::vector<MessageTypeDescription>::size_type MessageType; /// Typ okreœlaj¹cy numer u¿ytego komunikatu.
		
		/**
		* \brief Metoda dodaj¹ca komunikat do listy.
		*
		* Metoda dodaje komunikat do listy wyœwietlanych komunikatów.
		* \param[in] numer - Numer okreœlaj¹cy rodzaj komunikatu.
		* \param[in] tekst - Tekst komunikatu.
		* \return Zwracana jest wartoœæ true, je¿eli uda³o sie dodaæ komunikat lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool addMessage( MessageType numer, std::string tekst);

		/**
		* \brief Metoda czyszcz¹ca listê komunikatów.
		*
		* Metoda czyœci listê wyœwietlanych komunikatów.
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
		
		std::vector<MessageTypeDescription> opisTypowKomunikatow_; /// Lista opisów typów komunikatów
		
	};

};
