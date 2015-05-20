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

#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include "QWidget"
#include "QString"
#include "QVector"
#include "QMap"
#include "QDebug"

#include "ui_MainWidget.h"
#include "dragwidget.hpp"
#include "tokenslot.hpp"
#include "opponent.hpp"
#include "card.hpp"
#include "rnd.hpp"


// Puerto Rico Main Widget
// This is main board game.

class MainWidget : public QWidget
{
	public:
		MainWidget(QWidget *parent=0);
		~MainWidget();
		
		QString buildToolTip(quint8 id=255, quint8 quantity=255, QString toInsert=0);
		
		void removeDesignerLabels();
		void createQuickGame();
		void destroyGame();
		
		void setRemainingValues(quint8 players);
		void createHarbor();
		void createPlantationTokens(quint8 players);
		void createPlantationSlots();
		void createMerchantShips(quint8 players);
		void createTradingHouse();
		void createJobTokens(quint8 players);
		void createJobSlot();
		void createBuildingTokens(quint8 players);
		void createBuildingSlots();
		void createReserve();
		
		void addBarrelToReserve(quint8 id, quint8 quantity=1);
		void removeBarrelFromReserve(quint8 id, quint8 quantity=1);
		
		void fillColonistShips(quint8 tokens=0);
		
	//public:
	private:
		Ui::MainWidget ui;
		bool running;
		
		QVector<Opponent*> opponents;
		QVector<ColonistToken*> colonistsInGame;
		
		// Place to stock colonists
		SanJuan *harbor;
		
		// Island Area
		QVector<PlantationSlot*> island; // size() == 12
		
		// Plantations availables
		QVector<PlantationToken*> plantations;
		
		// Merchant Ships
		QVector<MerchantShip*> ships;
		
		// Trading House
		TradingHouse *tradinghouse;
		
		// Jobs
		QVector<JobToken*> jobs;
		JobSlot *currentJob;
		
		// Building Tokens availables
		QMap<int, BuildingToken*> buildings;
		
		// Buildings built
		QVector<BuildingSlot*> town; // size() == 12
		
		// Goods producted
		QVector<BarrelToken*> goods;
		
		// Reserve (remaining barrels)
		QVector<QLabel*> cornBarrels;
		QVector<QLabel*> indigoBarrels;
		QVector<QLabel*> sugarBarrels;
		QVector<QLabel*> tobaccoBarrels;
		QVector<QLabel*> coffeeBarrels;
		
	private:
		QMap<int, quint8> remainingBuildings;
		QMap<int, quint8> remainingPlantations;
		QMap<int, quint8> remainingBarrels;
		quint8 remainingColonists;
		quint8 remainingVictoryPoints;
};

#endif
