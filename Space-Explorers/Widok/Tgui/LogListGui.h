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
		typedef std::shared_ptr<LogListGui> Ptr;
		typedef std::shared_ptr<const LogListGui> ConstPtr;

		/**
		* \brief Klasa opisuj¹ca typ kounikatu w logach.
		*
		* Klasa reprezentuje typ komunikatu wyœwietlanego w kontrolce logów.
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

		typedef std::vector<MessageTypeDescription>::size_type MessageType; /// Typ okreœlaj¹cy numer u¿ytego komunikatu.

		LogListGui();

		LogListGui(const LogListGui& copy);

		LogListGui& operator= (const LogListGui& right);

		static LogListGui::Ptr copy(LogListGui::ConstPtr chatBox);

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

		bool wczytajOpisyTypowKomunikatow(const std::string &plik);
		const std::string& pobierzPlikOpisowTypowKomunikatow() const;
				
		virtual Widget::Ptr clone() const override{
			return std::make_shared<LogListGui>(*this);
		}
		std::string plikOpisowTypowKomunikatow_;

		std::vector<MessageTypeDescription> opisTypowKomunikatow_; /// Lista dostêpnych opisów komunikatów.
		
		std::vector<MessageType> powiazaniaKontrolek_; /// Lista powi¹zañ opisów komunikatów z kontrolkami wyœwietlaj¹cymi.

		friend std::shared_ptr<DataIO::Node> saveLogListGui(LogListGui::Ptr);
		friend Widget::Ptr loadLogListGui(std::shared_ptr<DataIO::Node>, Widget::Ptr);
	};
};
