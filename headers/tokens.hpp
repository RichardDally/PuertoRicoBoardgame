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

#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <QtGui>
#include <QLabel>


// Puerto Rico Token

/*** Jobs Translations
*
*	SETTLER = INTENDANT.
*	MAYOR = MAIRE.
*	BUILDER = BATISSEUR.
*	CRAFTSMAN = CONTREMAITRE.
*	TRADER = MARCHAND.
*	CAPTAIN = ARMATEUR.
*	PROSPECTOR = CHERCHEUR_OR.
*		
***/

/*** Plantations Translations
*
*	CORN = MAIS.
*	SUGAR = SUCRE.
*	TOBACCO = CAFE.
*	COFFEE = CAFE.
*	QUARRY = CARRIERE.
*
***/

class BuildingSlot;
class PlantationSlot;
class ColonistSlot;

enum{ 	// Job TokenTypes
		SETTLER, // == 0
		MAYOR, BUILDER, CRAFTSMAN, 
		TRADER, CAPTAIN, PROSPECTOR, 
		
		// Building Token Types
		
		PETITE_TEINTUTERIE_INDIGO, // == 7
		PETITE_RAFFINERIE_SUCRE, 
		PETIT_MARCHE, HACIENDA,
		BARAQUE_CHANTIER, 
		PETIT_ENTREPOT,
		TEINTURERIE_INDIGO,
		RAFFINERIE_SUCRE,
		DISPENSAIRE, COMPTOIR,
		GRAND_MARCHE, GRAND_ENTREPOT,
		SECHOIR_TABAC, BRULERIE_CAFE,
		MANUFACTURE, UNIVERSITE,
		PORT, QUAI, // == 24
		GUILDE, RESIDENCE,
		FORTERESSE, DOUANE,
		HOTEL_VILLE, // == 29
		
		// Plantation Token Types
		CORN, INDIGO, SUGAR, TOBACCO,
		COFFEE, QUARRY, // == 35
		
		// Colonist Token
		COLONIST, // == 36
		
		// Barrel Token Types
		CORN_BARREL, INDIGO_BARREL,
		SUGAR_BARREL, TOBACCO_BARREL,
		COFFEE_BARREL, // == 41
		
		// Misc TokenTypes
	};

class Token : public QLabel
{
	public:
		Token(QWidget *parent=0);
		virtual ~Token();
		
		void lock();
		void unlock();
		void toggleLock();
		
		quint8 my_id;
		
	protected:
		void mousePressEvent(QMouseEvent *event);
		//void dragMoveEvent(QDragMoveEvent *event);
		//void dragEnterEvent(QDragEnterEvent *event);
		//void dropEvent(QDropEvent *event);
		
		bool locked; // user cannot use token when its locked.
};


class JobToken : public Token
{
	public:
		JobToken(quint8 id, QWidget *parent);
};


class BuildingToken : public Token
{
	public:
		BuildingToken(quint8 id, QWidget *parent);
		BuildingSlot *occupiedSlot;
		QVector<ColonistSlot*> my_slots;
};

class PlantationToken : public Token
{
	public:
		PlantationToken(quint8 id, QWidget *parent);
		PlantationSlot *occupiedSlot;
		ColonistSlot *my_slot;
};

class ColonistToken : public Token
{
	public:
		ColonistToken(QWidget *parent, QSize s);
		ColonistSlot *occupiedSlot;
};

class BarrelToken : public Token
{
	public:
		BarrelToken(quint8 id, QWidget *parent);
};

#endif
