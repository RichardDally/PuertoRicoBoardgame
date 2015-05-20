/*************************************************************************
*       Puerto Rico by Andreas Seyfarth - Boardgame's Adaptation in C++/Qt4
*           		Copyright (C) 2008  Dally Richard.
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see http://www.gnu.org/licenses/.
*
*
************************************************************************/

#ifndef CARD_HPP
#define CARD_HPP

#include "tokenslot.hpp"

#include <QLabel>
#include <QList>

class Card : public QLabel
{
	public:
		Card(QWidget *parent=0);
};

class MerchantShip : public Card
{
	public:
		MerchantShip(quint8 slots, QWidget *parent=0);
		bool isFull();
		
		QList<BarrelSlot*> slotsList;
};

class TradingHouse : public Card
{
	public:
		TradingHouse(QWidget *parent=0);
		bool isFull();
		
		QList<BarrelSlot*> slotsList;
};


#endif
