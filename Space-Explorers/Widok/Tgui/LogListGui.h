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
			Color pierwszyKolor_ = Color(0, 0, 0); /// Pierwszy kolor komunikatu.
			Color drugiKolor_ = Color(0, 0, 0); /// Drugi kolor komunikatu.
			unsigned int pierwszyRozmiarCzcionki_ = 0; /// Pierwszy rozmiar czcionki komunikatu.
			unsigned int drugiRozmiarCzcionki_ = 0; /// Drugi rozmiar czcionki komunikatu.
		};

		typedef std::vector<MessageTypeDescription>::size_type MessageType; /// Typ określający numer użytego komunikatu.

		LogListGui();

		LogListGui(const LogListGui& copy);

		LogListGui& operator= (const LogListGui& right);

		static LogListGui::Ptr copy(LogListGui::ConstPtr chatBox);

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

		bool wczytajOpisyTypowKomunikatow(const std::string &plik);
		const std::string& pobierzPlikOpisowTypowKomunikatow() const;
				
		virtual Widget::Ptr clone() const override{
			return std::make_shared<LogListGui>(*this);
		}
		std::string plikOpisowTypowKomunikatow_;

		std::vector<MessageTypeDescription> opisTypowKomunikatow_; /// Lista dostępnych opisów komunikatów.
		
		std::vector<MessageType> powiazaniaKontrolek_; /// Lista powiązań opisów komunikatów z kontrolkami wyświetlającymi.

		friend std::shared_ptr<DataIO::Node> saveLogListGui(LogListGui::Ptr);
		friend Widget::Ptr loadLogListGui(std::shared_ptr<DataIO::Node>, Widget::Ptr);
	};
};
