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

#ifndef TOKENSLOT_HPP
#define TOKENSLOT_HPP

#include "tokens.hpp"
#include <QLabel>
#include <QFrame>

// Puerto Rico Token' Slot

/*** Types of tokens:
*
*	job token == ID 0
*	building token == ID 1
*	plantation token == ID 2
*	colon token == ID 3
*	barrel token == ID 4
*	
***/

// Types of Token slots
//enum{	JOB, BUILDING, PLANTATION, COLON, BARREL, LAST_TOKEN_SLOT };


class TokenSlot : public QLabel
{
	public:
		TokenSlot(QWidget *parent);
		virtual ~TokenSlot();
		
		void lock();
		void unlock();
		void toggleLock();
		bool isLocked();
		
		void setEmpty(bool empty=true);
		bool isEmpty();
		
		Token *token;
		
	protected:
		virtual void dropEvent(QDropEvent *event);
		void dragEnterEvent(QDragEnterEvent *event);
		void dragMoveEvent(QDragMoveEvent *event);
		
		// Debug
		void mousePressEvent(QMouseEvent *event);
		
		quint8 lowestValue, highestValue; // id range
		bool locked; // user cannot use token when its locked.
		bool empty;
};

class ColonistSlot : public TokenSlot
{
	public:
		ColonistSlot(quint8 destination, QWidget *parent);
		void fillSlot();
		
		//ColonistToken *token;
		
	protected:
		void dropEvent(QDropEvent *event);
		void mousePressEvent(QMouseEvent *event);
		
	private:
		quint8 ownerType; // Plantation == 0, Building == 1
};

class JobSlot : public TokenSlot
{
	public:
		JobSlot(QWidget *parent);
		void fillSlot(quint8 id);
		
	protected:
		void dropEvent(QDropEvent *event);
};

class BuildingSlot : public TokenSlot
{
	public:
		BuildingSlot(QWidget *parent);
		int fillSlot(quint8 id);
		void linkBelowSlot(BuildingSlot *below);
		
		//BuildingToken *token;
		BuildingSlot *below_slot;
	
	protected:
		void dropEvent(QDropEvent *event);
};

class PlantationSlot : public TokenSlot
{
	public:
		PlantationSlot(QWidget *parent);
		void fillSlot(quint8 id);
	
	protected:
		void dropEvent(QDropEvent *event);
		//void mouseDoubleClickEvent(QMouseEvent *event);
};

class BarrelSlot : public TokenSlot
{
	public:
		BarrelSlot(QWidget *parent);
		void fillSlot(quint8 id);
		void restrictBarrelType(quint8 id);
	
	protected:
		void dropEvent(QDropEvent *event);
};

class SanJuan : public QFrame
{
	public:
		SanJuan(QWidget *parent, QSize s);
		
		QList<ColonistToken*> idleColonists;
	
	protected:
		void dragEnterEvent(QDragEnterEvent *event);
		void dragMoveEvent(QDragMoveEvent *event);
		void dropEvent(QDropEvent *event);
};

#endif
