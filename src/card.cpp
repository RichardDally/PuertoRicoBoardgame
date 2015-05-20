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

#include "card.hpp"

Card::Card(QWidget *p) : QLabel(p)
{
	setScaledContents(true);
}

MerchantShip::MerchantShip(quint8 n, QWidget *p) : Card(p)
{
	resize(81, 131);
	
	switch( n )
	{
		case 4:
		{
			setPixmap(QPixmap(":/res/bateaux/bateau_4.jpg"));
			
			BarrelSlot *b1 = new BarrelSlot(this);
			b1->move(21, 42);
			slotsList.push_back(b1);
			
			BarrelSlot *b2 = new BarrelSlot(this);
			b2->move(45, 42);
			slotsList.push_back(b2);
			
			BarrelSlot *b3 = new BarrelSlot(this);
			b3->move(21, 67);
			slotsList.push_back(b3);
			
			BarrelSlot *b4 = new BarrelSlot(this);
			b4->move(45, 67);
			slotsList.push_back(b4);
			break;
		}
		
		case 5:
		{
			setPixmap(QPixmap(":/res/bateaux/bateau_5.jpg"));
			
			BarrelSlot *b1 = new BarrelSlot(this);
			b1->move(20, 29);
			slotsList.push_back(b1);
			
			BarrelSlot *b2 = new BarrelSlot(this);
			b2->move(44, 29);
			slotsList.push_back(b2);
			
			BarrelSlot *b3 = new BarrelSlot(this);
			b3->move(20, 53);
			slotsList.push_back(b3);
			
			BarrelSlot *b4 = new BarrelSlot(this);
			b4->move(45, 53);
			slotsList.push_back(b4);
			
			BarrelSlot *b5 = new BarrelSlot(this);
			b5->move(33, 77);
			slotsList.push_back(b5);
			break;
		}
		
		case 6:
		{
			setPixmap(QPixmap(":/res/bateaux/bateau_6.jpg"));
			
			BarrelSlot *b1 = new BarrelSlot(this);
			b1->move(21, 28);
			slotsList.push_back(b1);
			
			BarrelSlot *b2 = new BarrelSlot(this);
			b2->move(45, 28);
			slotsList.push_back(b2);
			
			BarrelSlot *b3 = new BarrelSlot(this);
			b3->move(21, 53);
			slotsList.push_back(b3);
			
			BarrelSlot *b4 = new BarrelSlot(this);
			b4->move(45, 53);
			slotsList.push_back(b4);
			
			BarrelSlot *b5 = new BarrelSlot(this);
			b5->move(21, 77);
			slotsList.push_back(b5);
			
			BarrelSlot *b6 = new BarrelSlot(this);
			b6->move(45, 77);
			slotsList.push_back(b6);
			break;
		}
		
		case 7:
		{
			setPixmap(QPixmap(":/res/bateaux/bateau_7.jpg"));
			
			BarrelSlot *b1 = new BarrelSlot(this);
			b1->move(19, 17);
			slotsList.push_back(b1);
			
			BarrelSlot *b2 = new BarrelSlot(this);
			b2->move(43, 17);
			slotsList.push_back(b2);
			
			BarrelSlot *b3 = new BarrelSlot(this);
			b3->move(19, 40);
			slotsList.push_back(b3);
			
			BarrelSlot *b4 = new BarrelSlot(this);
			b4->move(43, 40);
			slotsList.push_back(b4);
			
			BarrelSlot *b5 = new BarrelSlot(this);
			b5->move(19, 64);
			slotsList.push_back(b5);
			
			BarrelSlot *b6 = new BarrelSlot(this);
			b6->move(43, 64);
			slotsList.push_back(b6);
			
			BarrelSlot *b7 = new BarrelSlot(this);
			b7->move(31, 88);
			slotsList.push_back(b7);
			break;
		}
		
		case 8:
		{
			setPixmap(QPixmap(":/res/bateaux/bateau_8.jpg"));
			
			BarrelSlot *b1 = new BarrelSlot(this);
			b1->move(20, 18);
			slotsList.push_back(b1);
			
			BarrelSlot *b2 = new BarrelSlot(this);
			b2->move(44, 18);
			slotsList.push_back(b2);
			
			BarrelSlot *b3 = new BarrelSlot(this);
			b3->move(20, 42);
			slotsList.push_back(b3);
			
			BarrelSlot *b4 = new BarrelSlot(this);
			b4->move(44, 42);
			slotsList.push_back(b4);
			
			BarrelSlot *b5 = new BarrelSlot(this);
			b5->move(20, 66);
			slotsList.push_back(b5);
			
			BarrelSlot *b6 = new BarrelSlot(this);
			b6->move(44, 66);
			slotsList.push_back(b6);
			
			BarrelSlot *b7 = new BarrelSlot(this);
			b7->move(20, 90);
			slotsList.push_back(b7);
			
			BarrelSlot *b8 = new BarrelSlot(this);
			b8->move(44, 90);
			slotsList.push_back(b8);
			break;
		}
		default:;
	}
}

bool MerchantShip::isFull()
{
	int size = slotsList.size();
	
	for(int i=0; i<size; i++)
	{
		if( slotsList[i]->isEmpty() )
		{
			return false;
		}
	}
	
	return true;
}

TradingHouse::TradingHouse(QWidget *p) : Card(p)
{
	resize(91, 141);
	setPixmap(QPixmap(":/res/divers/magasin.jpg"));
	
	BarrelSlot *b1 = new BarrelSlot(this);
	b1->move(23, 25);
	slotsList.push_back(b1);
	
	BarrelSlot *b2 = new BarrelSlot(this);
	b2->move(52, 24);
	slotsList.push_back(b2);
	
	BarrelSlot *b3 = new BarrelSlot(this);
	b3->move(23, 51);
	slotsList.push_back(b3);
	
	BarrelSlot *b4 = new BarrelSlot(this);
	b4->move(52, 50);
	slotsList.push_back(b4);
}

bool TradingHouse::isFull()
{
	int size = slotsList.size();
	
	for(int i=0; i<size; i++)
	{
		if( slotsList[i]->isEmpty() )
		{
			return false;
		}
	}
	
	return true;
}
