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

#include "mainwidget.hpp"
#include "tokens.hpp"
#include "tokenslot.hpp"

MainWidget::MainWidget(QWidget *p) : QWidget(p), 
harbor(0), tradinghouse(0), currentJob(0), 
remainingColonists(0), remainingVictoryPoints(0)
{
	ui.setupUi(this);
	running = false;
	
   //removeDesignerLabels();
   //setRemainingValues(2);
	
	
   //createJobTokens(2);
   //createJobSlot();
	
   //createTradingHouse();
   //createMerchantShips(5);
	
   //createBuildingTokens(2);
   //createBuildingSlots();
	
   //createHarbor();
   //createPlantationTokens(2);
   //createPlantationSlots();
	
   //ColonistToken *ct1 = new ColonistToken(this, QSize(21, 21));
   //ct1->move(740, 290);
	
   //ColonistToken *ct2 = new ColonistToken(this, QSize(21, 21));
   //ct2->move(790, 270);
	
   //ColonistSlot *cs = new ColonistSlot(0, this);
   //cs->move(770, 440);
}


MainWidget::~MainWidget()
{
}

QString MainWidget::buildToolTip(quint8 id, quint8 quantity, QString toInsert)
{
	QString firstPart
		("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
		"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
		"p, li { white-space: pre-wrap; }\n"
		"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
		"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
		"<img src=\"");
	
	QString pixPath;
	
	switch( id )
	{
		case SETTLER: pixPath = ":/res/metiers/intendant.jpg"; break;
		case MAYOR: pixPath = ":/res/metiers/maire.jpg"; break;
		case BUILDER: pixPath = ":/res/metiers/batisseur.jpg"; break;
		case CRAFTSMAN: pixPath = ":/res/metiers/contremaitre.jpg"; break;
		case TRADER: pixPath = ":/res/metiers/marchand.jpg"; break;
		case CAPTAIN: pixPath = ":/res/metiers/armateur.jpg"; break;
		case PROSPECTOR: pixPath = ":/res/metiers/chercheur_or.jpg"; break;
		
		case PETITE_TEINTUTERIE_INDIGO: pixPath = ":/res/batiments/petite_teinturerie_indigo.jpg"; break;
		case PETITE_RAFFINERIE_SUCRE: pixPath = ":/res/batiments/petite_raffinerie_sucre.jpg"; break;
		case PETIT_MARCHE: pixPath = ":/res/batiments/petit_marche.jpg"; break;
		case HACIENDA: pixPath = ":/res/batiments/hacienda.jpg"; break;
		case BARAQUE_CHANTIER: pixPath = ":/res/batiments/baraque_chantier.jpg"; break;
		case PETIT_ENTREPOT: pixPath = ":/res/batiments/petit_entrepot.jpg"; break;
		case TEINTURERIE_INDIGO: pixPath = ":/res/batiments/teinturerie_indigo.jpg"; break;
		case RAFFINERIE_SUCRE: pixPath = ":/res/batiments/raffinerie_sucre.jpg"; break;
		case DISPENSAIRE: pixPath = ":/res/batiments/dispensaire.jpg"; break;
		case COMPTOIR: pixPath = ":/res/batiments/comptoir.jpg"; break;
		case GRAND_MARCHE: pixPath = ":/res/batiments/grand_marche.jpg"; break;
		case GRAND_ENTREPOT: pixPath = ":/res/batiments/grand_entrepot.jpg"; break;
		case SECHOIR_TABAC: pixPath = ":/res/batiments/sechoir_tabac.jpg"; break;
		case BRULERIE_CAFE: pixPath = ":/res/batiments/brulerie_cafe.jpg"; break;
		case MANUFACTURE: pixPath = ":/res/batiments/manufacture.jpg"; break;
		case UNIVERSITE: pixPath = ":/res/batiments/universite.jpg"; break;
		case PORT: pixPath = ":/res/batiments/port.jpg"; break;
		case QUAI: pixPath = ":/res/batiments/quai.jpg"; break;
		case GUILDE: pixPath = ":/res/batiments/guilde.jpg"; break;
		case RESIDENCE: pixPath = ":/res/batiments/residence.jpg"; break;
		case FORTERESSE: pixPath = ":/res/batiments/forteresse.jpg"; break;
		case DOUANE: pixPath = ":/res/batiments/douane.jpg"; break;
		case HOTEL_VILLE: pixPath = ":/res/batiments/hotel_ville.jpg"; break;
		default:;
	}
	
	
	QString thirdPart("\" /></p>");
	QString lastPart;
	
	if( id <= PROSPECTOR )
	{
		lastPart = "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">";
		lastPart += tr("Il y a");
		lastPart += " "+ QString::number((int)quantity) +" ";
		(quantity > 1)? lastPart += tr("doublons sur ce métier.") : lastPart += tr("doublon sur ce métier.");
		lastPart += "</p></body></html>";
	}
	else
		if( id <= QUAI )
		{
			lastPart = "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">";
			lastPart += QString::number((int)quantity) +" ";
			(quantity > 1)? lastPart += tr("bâtiments restants.") : lastPart += tr("bâtiment restant.");
			lastPart += "</p></body></html>";
		}
		else
			if( id <= HOTEL_VILLE )
			{
				lastPart = "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">";
				lastPart += tr("Ce type de bâtiment est unique.");
				lastPart += "</p></body></html>";
			}
	
	if( !toInsert.isNull() )
	{
		lastPart += toInsert;
	}
	
	firstPart.append(pixPath + thirdPart + lastPart);
	
	return firstPart;
}


void MainWidget::removeDesignerLabels()
{
	delete ui.label_ToRemove_1; delete ui.label_ToRemove_2; delete ui.label_ToRemove_3;
	delete ui.label_ToRemove_4; delete ui.label_ToRemove_5; delete ui.label_ToRemove_6;
	delete ui.label_ToRemove_7; delete ui.label_ToRemove_8; delete ui.label_ToRemove_9;
	delete ui.label_ToRemove_10; delete ui.label_ToRemove_11; delete ui.label_ToRemove_12;
	delete ui.label_ToRemove_13; delete ui.label_ToRemove_14; delete ui.label_ToRemove_15;
	delete ui.label_ToRemove_16; delete ui.label_ToRemove_17; delete ui.label_ToRemove_18;
	delete ui.label_ToRemove_19; delete ui.label_ToRemove_20; delete ui.label_ToRemove_21;
	delete ui.label_ToRemove_22; delete ui.label_ToRemove_23; delete ui.label_ToRemove_24;
	delete ui.label_ToRemove_25; delete ui.label_ToRemove_26; delete ui.label_ToRemove_27;
	delete ui.label_ToRemove_28; delete ui.label_ToRemove_29; delete ui.label_ToRemove_30;
	delete ui.label_ToRemove_31; delete ui.label_ToRemove_32; delete ui.label_ToRemove_33;
	delete ui.label_ToRemove_34; delete ui.label_ToRemove_35; delete ui.label_ToRemove_36;
	delete ui.label_ToRemove_37; delete ui.label_ToRemove_38; delete ui.label_ToRemove_39;
	delete ui.label_ToRemove_40; delete ui.label_ToRemove_41; delete ui.label_ToRemove_42;
	delete ui.label_ToRemove_43; delete ui.label_ToRemove_44; delete ui.label_ToRemove_45;
	delete ui.label_ToRemove_46; delete ui.label_ToRemove_47; delete ui.label_ToRemove_48;
	delete ui.label_ToRemove_49; delete ui.label_ToRemove_50; delete ui.label_ToRemove_51;
	delete ui.label_ToRemove_52; delete ui.label_ToRemove_53; delete ui.label_ToRemove_54;
	delete ui.label_ToRemove_55; delete ui.label_ToRemove_56; delete ui.label_ToRemove_57;
	delete ui.label_ToRemove_58; delete ui.label_ToRemove_59; delete ui.label_ToRemove_60;
}


void MainWidget::createQuickGame()
{
	if( running ) 
	{
		qDebug() << "a game is already running";
		return;
	}
	
	qDebug() << "creating QuickGame...";
	setRemainingValues(2);
	createHarbor();
	createPlantationTokens(2);
	createPlantationSlots();
	createMerchantShips(2);
	createTradingHouse();
	createJobTokens(2);
	createJobSlot();
	createBuildingTokens(2);
	createBuildingSlots();
	createReserve();
	fillColonistShips(2);
	
	running = true;
}


void MainWidget::destroyGame()
{
	qDebug() << "destroying Game...";

	// Deleting Harbor
	delete harbor; harbor = NULL;
	
	// Deleting PlantationsTokens
	qDeleteAll(plantations);
	plantations.resize(0);
	
	// Deleting PlantationSlots
	qDeleteAll(island);
	island.resize(0);
	
	// Deleting MerchantShips
	qDeleteAll(ships);
	ships.resize(0);
	
	// Deleting TradingHouse
	delete tradinghouse; tradinghouse = NULL;
	
	// Deleting JobTokens
	qDeleteAll(jobs);
	jobs.resize(0);
	
	// Deleting Job Slot
	delete currentJob; currentJob = NULL;
	
	// Deleting Building Tokens
	qDeleteAll(buildings);
	buildings.clear();
	
	// Deleting Building Slots
	qDeleteAll(town);
	town.resize(0);
	
	// Deleting Goods
	qDeleteAll(goods);
	goods.resize(0);
	
	// Cleaning Reserve
	qDeleteAll(cornBarrels);
	cornBarrels.resize(0);
	qDeleteAll(indigoBarrels);
	indigoBarrels.resize(0);
	qDeleteAll(sugarBarrels);
	sugarBarrels.resize(0);
	qDeleteAll(tobaccoBarrels);
	tobaccoBarrels.resize(0);
	qDeleteAll(coffeeBarrels);
	coffeeBarrels.resize(0);
	
	// Deleting Colonists currently in game.
	qDeleteAll(colonistsInGame);
	colonistsInGame.resize(0);
	
	running = false;
}


void MainWidget::createHarbor()
{
	harbor = new SanJuan(this, QSize(111, 51));
	harbor->move(20, 500);
	harbor->show();
}

void MainWidget::setRemainingValues(quint8 players)
{
	// For any number of players:
	remainingBarrels[CORN] = 10;
	remainingBarrels[INDIGO] = 12;
	remainingBarrels[SUGAR] = 11;
	remainingBarrels[TOBACCO] = 9;
	remainingBarrels[COFFEE] = 8;
	
	
	if( players == 2 )
	{
		remainingPlantations[CORN] = 7;
		remainingPlantations[INDIGO] = 9;
		remainingPlantations[SUGAR] = 8;
		remainingPlantations[TOBACCO] = 6;
		remainingPlantations[COFFEE] = 5;
		remainingPlantations[QUARRY] = 5;
	}
	else
	{
		remainingPlantations[CORN] = 10;
		remainingPlantations[INDIGO] = 12;
		remainingPlantations[SUGAR] = 11;
		remainingPlantations[TOBACCO] = 9;
		remainingPlantations[COFFEE] = 8;
		remainingPlantations[QUARRY] = 8;
	}
	
	/*** BUILDINGS ***/
	
	// Single Slot Buildings
	for(int i=PETITE_TEINTUTERIE_INDIGO; i<=QUAI; i++)
	{
		if( (i == PETITE_TEINTUTERIE_INDIGO) ||
			(i == PETITE_RAFFINERIE_SUCRE) )
		{
			if( players == 2 )
				remainingBuildings[i] = 2;
			else
				remainingBuildings[i] = 4;
				
			continue;
		}
		
		if( (i == TEINTURERIE_INDIGO) ||
			(i == RAFFINERIE_SUCRE) )
		{
			if( players == 2 )
				remainingBuildings[i] = 2;
			else
				remainingBuildings[i] = 3;
			
			continue;
		}
		
		if( (i == SECHOIR_TABAC) ||
			(i == BRULERIE_CAFE) )
		{
			if( players == 2 )
				remainingBuildings[i] = 2;
			else
				remainingBuildings[i] = 3;
			
			continue;
		}
		
		if( players == 2 )
			remainingBuildings[i] = 1;
		else
			remainingBuildings[i] = 2;
	}
	
	// Double Slot Buildings
	for(int i=GUILDE; i<=HOTEL_VILLE; i++)
	{
		remainingBuildings[i] = 1;
	}
	
	switch( players )
	{
		case 2:
			remainingVictoryPoints = 65;
			remainingColonists = 40;
			break;
		case 3:
			remainingVictoryPoints = 75;
			remainingColonists = 55;
			break;
		case 4:
			remainingVictoryPoints = 100;
			remainingColonists = 75;
			break;
		case 5:
			remainingVictoryPoints = 122;
			remainingColonists = 95;
			break;
		default:;
	}
}


void MainWidget::createPlantationSlots()
{
	island.resize(12);
	
	for(int i=0; i<12; i++)
	{
		island[i] = new PlantationSlot(this);
		island[i]->show();
	}
	
	// First column
	island[0]->move(83, 551);
	island[1]->move(83, 598);
	island[2]->move(83, 646);
	
	// 2nd.
	island[3]->move(130, 530);
	island[4]->move(130, 577);
	island[5]->move(130, 625);
	
	// 3th
	island[6]->move(178, 545);
	island[7]->move(178, 593);
	island[8]->move(178, 640);
	
	// 4th
	island[9]->move(226, 567);
	island[10]->move(226, 615);
	
	// 5th
	island[11]->move(274, 589);
}


// remainingPlantations[CORN] = 7;
// remainingPlantations[INDIGO] = 9;
// remainingPlantations[SUGAR] = 8;
// remainingPlantations[TOBACCO] = 6;
// remainingPlantations[COFFEE] = 5;

void MainWidget::createPlantationTokens(quint8 players)
{
	if( (players < 2) || (players > 5) )
	{
		qDebug() << "This amount is not allowed: " << players;
		return;
	}
	
	// players + 1 + 1 QUARRY
	// => players+1 random plantations + choice of quarry.
	plantations.resize(players+2);
	
	
	int totalOfTokens = 0;
	for(int h=CORN; h<=COFFEE; h++)
		totalOfTokens += remainingPlantations[h];
	
	
	// We generate players+1 plantations
	for(int i=0; i<players+1; i++)
	{
		int rndInt = rnd(totalOfTokens);
		int ceiling = remainingPlantations[CORN] - 1;
		
		for(int j=CORN; j<COFFEE; j++)
		{
			if( rndInt <= ceiling )
			{
				totalOfTokens -= 1;
				remainingPlantations[j] -= 1;
				plantations[i] = new PlantationToken(j, this);
				plantations[i]->show();
				break;
			}	
			ceiling += remainingPlantations[j+1];
		}
		
		if( plantations[i] == NULL )
		{
			totalOfTokens -= 1;
			remainingPlantations[COFFEE] -= 1;
			plantations[i] = new PlantationToken(COFFEE, this);
			plantations[i]->show();
		}
	}
	
	qDebug() << "total of tokens: " << totalOfTokens;
	
	// We insert at last quarry plantation token.
	plantations[players+1] = new PlantationToken(QUARRY, this);
	plantations[players+1]->show();
	
	// 6 Slots:
	QPoint slot1(20, 360);
	QPoint slot2(80, 360);
	QPoint slot3(140, 360);
	QPoint slot4(200, 360);
	// New line
	QPoint slot5(20, 420);
	QPoint slot6(80, 420);
	QPoint slot7(140, 420);
	QPoint slot8(200, 420);
	
	// Moves.
	switch( players )
	{
		case 2:
			plantations[0]->move(slot5);
			plantations[1]->move(slot6);
			plantations[2]->move(slot7);
			plantations[3]->move(slot8);
			break;
		
		case 3:
			plantations[0]->move(slot1);
			plantations[1]->move(slot2);
			plantations[2]->move(slot5);
			plantations[3]->move(slot6);
			plantations[4]->move(slot7);
			break;
		
		case 4:
			plantations[0]->move(slot1);
			plantations[1]->move(slot2);
			plantations[2]->move(slot3);
			plantations[3]->move(slot5);
			plantations[4]->move(slot6);
			plantations[5]->move(slot7);
			break;
		
		case 5:
			plantations[0]->move(slot1);
			plantations[1]->move(slot2);
			plantations[2]->move(slot3);
			plantations[3]->move(slot5);
			plantations[4]->move(slot6);
			plantations[5]->move(slot7);
			plantations[6]->move(slot8);
			break;
		default:;
	}
}


void MainWidget::createMerchantShips(quint8 players)
{
	switch( players )
	{
		case 2:
			ships.resize(2);
			ships[0] = new MerchantShip(4, this);
			ships[1] = new MerchantShip(6, this);
			break;
		
		case 3:
			ships.resize(3);
			ships[0] = new MerchantShip(4, this);
			ships[1] = new MerchantShip(5, this);
			ships[2] = new MerchantShip(6, this);
			break;
		
		case 4:
			ships.resize(3);
			ships[0] = new MerchantShip(5, this);
			ships[1] = new MerchantShip(6, this);
			ships[2] = new MerchantShip(7, this);
			break;
		
		case 5:
			ships.resize(3);
			ships[0] = new MerchantShip(6, this);
			ships[1] = new MerchantShip(7, this);
			ships[2] = new MerchantShip(8, this);
			break;
		
		default: 
			qDebug() << "Issue @ MainWidget::createMerchantShips("<<players<<")";
			return;
	}
	
	ships[0]->move(19, 30);
	ships[1]->move(100, 30);
	ships[0]->show();
	ships[1]->show();
	
	if( players>2 )
	{
		ships[2]->move(181, 30);
		ships[0]->show();
	}
}

void MainWidget::createTradingHouse()
{
	tradinghouse = new TradingHouse(this);
	tradinghouse->move(280, 30);
	tradinghouse->show();
}

/*** Players - Jobs
*
*	2 Players = 6 jobs
*	3 Players = 6 jobs
*	4 Players = 7 jobs
*	5 Players = 8 jobs
*
***/
void MainWidget::createJobTokens(quint8 players)
{
	jobs.resize(6);
	
	for(int i=0; i<6; i++)
	{
		jobs[i] = new JobToken(i, this);
		jobs[i]->setToolTip(buildToolTip(i, 0));
		jobs[i]->show();
	}
	
	jobs[0]->move(732, 30);
	jobs[1]->move(790, 30);
	jobs[2]->move(847, 30);
	jobs[3]->move(903, 30);
	jobs[4]->move(732, 120);
	jobs[5]->move(790, 120);
	
	if( players == 4 )
	{
		jobs.resize(7);
		jobs[6] = new JobToken(PROSPECTOR, this);
		jobs[6]->move(847, 120);
		jobs[6]->setToolTip(buildToolTip(PROSPECTOR, 0));
		jobs[6]->show();
	}
	else
		if( players == 5 )
		{
			jobs.resize(8);
			jobs[6] = new JobToken(PROSPECTOR, this);
			jobs[6]->move(847, 120);
			jobs[6]->setToolTip(buildToolTip(PROSPECTOR, 0));
			jobs[6]->show();
			
			jobs[7] = new JobToken(PROSPECTOR, this);
			jobs[7]->move(903, 120);
			jobs[7]->setToolTip(buildToolTip(PROSPECTOR, 0));
			jobs[7]->show();
		}
}

void MainWidget::createJobSlot()
{
	currentJob = new JobSlot(this);
	currentJob->move(850, 240);
	currentJob->show();
}


void MainWidget::createBuildingTokens(quint8 players)
{
	int x, y;
	
	x = 394; y = 61;
	for(int i=PETITE_TEINTUTERIE_INDIGO; i<=QUAI; i++)
	{
		buildings[i] = new BuildingToken(i, this);
		buildings[i]->setToolTip( buildToolTip(i, remainingBuildings[i]) );
		buildings[i]->move(x, y);
		buildings[i]->show();
		
		if( (i == PETIT_ENTREPOT) || (i == GRAND_ENTREPOT) )
		{
			x += 80; y = 61;
			continue;
		}
		
		if( i == QUAI )
		{
			x += 80; y = 61;
			continue;
		}
		
		y += 40;
	}
	
	x = 634; y = 61;
	for(int i=GUILDE; i<=HOTEL_VILLE; i++)
	{
		buildings[i] = new BuildingToken(i, this);
		buildings[i]->setToolTip( buildToolTip(i, remainingBuildings[i]) );
		buildings[i]->move(x, y);
		buildings[i]->show();
		y += 80;
	}
}

void MainWidget::createBuildingSlots()
{
	int k=0;
	town.resize(12);
	
	for(int i=0; i<3; i++)
	for(int j=0; j<4; j++)
	{
		town[k] = new BuildingSlot(this);
		town[k]->move(525+(j*109), 514+(i*63));
		town[k]->show();
		k++;
	}
	
	// Link upper slots with below slots.
	for(k=0; k<8; k++)
	{
		town[k]->linkBelowSlot(town[k+4]);
	}
}

void MainWidget::createReserve()
{
	qDebug() << "Creating reserve...";

	// Corn
	QPoint cornPos(140, 200);
	QLabel *label;
	
	for(int i=0; i<10; i++)
	{
		label = new QLabel(this);
		label->resize(16, 20);
		label->setScaledContents(true);
		label->setPixmap(QPixmap(":/res/tonneaux/tonneau_mais.png"));
		label->setToolTip(tr("Maïs"));
		label->move(cornPos);
		label->show();
		cornBarrels.push_back(label);
		
		cornPos.setX( cornPos.x()+20 );
	}
	
	// Indigo
	QPoint indigoPos(140, 222);
	indigoBarrels.resize(12);
	
	for(int i=0; i<12; i++)
	{
		indigoBarrels[i] = new QLabel(this);
		indigoBarrels[i]->resize(16, 20);
		indigoBarrels[i]->setScaledContents(true);
		indigoBarrels[i]->setPixmap(QPixmap(":/res/tonneaux/tonneau_indigo.png"));
		indigoBarrels[i]->setToolTip(tr("Indigo"));
		indigoBarrels[i]->move(indigoPos);
		indigoBarrels[i]->show();
		
		indigoPos.setX( indigoPos.x()+20 );
	}
	
	// Sugar
	QPoint sugarPos(140, 244);
	sugarBarrels.resize(11);
	
	for(int i=0; i<11; i++)
	{
		sugarBarrels[i] = new QLabel(this);
		sugarBarrels[i]->resize(16, 20);
		sugarBarrels[i]->setScaledContents(true);
		sugarBarrels[i]->setPixmap(QPixmap(":/res/tonneaux/tonneau_sucre.png"));
		sugarBarrels[i]->setToolTip(tr("Sucre"));
		sugarBarrels[i]->move(sugarPos);
		sugarBarrels[i]->show();
		
		sugarPos.setX( sugarPos.x()+20 );
	}
	
	// Tobacco
	QPoint tobaccoPos(140, 266);
	tobaccoBarrels.resize(9);
	
	for(int i=0; i<9; i++)
	{
		tobaccoBarrels[i] = new QLabel(this);
		tobaccoBarrels[i]->resize(16, 20);
		tobaccoBarrels[i]->setScaledContents(true);
		tobaccoBarrels[i]->setPixmap(QPixmap(":/res/tonneaux/tonneau_tabac.png"));
		tobaccoBarrels[i]->setToolTip(tr("Tabac"));
		tobaccoBarrels[i]->move(tobaccoPos);
		tobaccoBarrels[i]->show();
		
		tobaccoPos.setX( tobaccoPos.x()+20 );
	}
	
	// Coffee
	QPoint coffeePos(140, 290);
	coffeeBarrels.resize(8);
	
	for(int i=0; i<8; i++)
	{
		coffeeBarrels[i] = new QLabel(this);
		coffeeBarrels[i]->resize(16, 20);
		coffeeBarrels[i]->setScaledContents(true);
		coffeeBarrels[i]->setPixmap(QPixmap(":/res/tonneaux/tonneau_cafe.png"));
		coffeeBarrels[i]->setToolTip(tr("Café"));
		coffeeBarrels[i]->move(coffeePos);
		coffeeBarrels[i]->show();
		
		coffeePos.setX( coffeePos.x()+20 );
	}
}


// remainingBarrels[CORN] = 10;
	// remainingBarrels[INDIGO] = 12;
	// remainingBarrels[SUGAR] = 11;
	// remainingBarrels[TOBACCO] = 9;
	// remainingBarrels[COFFEE] = 8;

void MainWidget::addBarrelToReserve(quint8 id, quint8 quantity)
{
	QVector<QLabel*> *vect;
	QString pixPath, toolTip;
	QPoint initialPos;
	quint8 maxQuantity;
	
	switch( id )
	{
		case CORN_BARREL:
			qDebug() << "CORN_BARREL";
			vect = &cornBarrels;
			pixPath = ":/res/tonneaux/tonneau_mais.png";
			toolTip = tr("Maïs");
			initialPos = QPoint(140, 200);
			maxQuantity = 10;
			break;
		case INDIGO_BARREL:
			qDebug() << "INDIGO_BARREL";
			vect = &indigoBarrels;
			pixPath = ":/res/tonneaux/tonneau_indigo.png";
			toolTip = tr("Indigo");
			initialPos = QPoint(140, 222);
			maxQuantity = 12;
			break;
		case SUGAR_BARREL:
			qDebug() << "SUGAR_BARREL";
			vect = &sugarBarrels;
			pixPath = ":/res/tonneaux/tonneau_sucre.png";
			toolTip = tr("Sucre");
			initialPos = QPoint(140, 244);
			maxQuantity = 11;
			break;
		case TOBACCO_BARREL:
			qDebug() << "TOBACCO_BARREL";
			vect = &tobaccoBarrels;
			pixPath = ":/res/tonneaux/tonneau_tabac.png";
			toolTip = tr("Tabac");
			initialPos = QPoint(140, 266);
			maxQuantity = 9;
			break;
		case COFFEE_BARREL:
			qDebug() << "COFFEE_BARREL";
			vect = &coffeeBarrels;
			pixPath = ":/res/tonneaux/tonneau_cafe.png";
			toolTip = tr("Café");
			initialPos = QPoint(140, 290);
			maxQuantity = 8;
			break;
		default: qDebug() << "Bad barrel id."; return;
	}

	
	quint8 size = vect->size();
	qDebug() << "Size == " << size;
		
	if( size == 0 ) // There is no barrel in this vect.
	{
		// There is not enough room to add asked barrels.
		// So we add the maximum.
		// Else we add asked quantity.
		if( quantity > maxQuantity )
		{
			qDebug() << "Asked quantity ("<<quantity<<") is > to " << maxQuantity;
			quantity = maxQuantity;
		}
		
		qDebug() << "We fill " << quantity << " barrels.";
		
		QLabel *label;
		for(int i=0; i<quantity; i++)
		{
			label = new QLabel(this);
			label->resize(16, 20);
			label->setScaledContents(true);
			label->setPixmap(QPixmap(pixPath));
			label->setToolTip(toolTip);
			label->move(initialPos);
			label->show();
			
			vect->push_back(label);
			
			initialPos.setX( initialPos.x()+20 );
		}
	}
	else
	{
		qDebug() << "size != 0";
		quint8 freeSlots = maxQuantity - size;
		
		// There is not enough room to add asked barrels.
		if( quantity > freeSlots )
		{
			qDebug() << "Asked quantity ("<<quantity<<") is > to freeSlots ("<<freeSlots<<").";
			qDebug() << "Finally we fill "<<freeSlots<<" slots...";
			quantity = freeSlots;
		}
		
		QLabel *label;
		initialPos = vect->at(size-1)->pos() + QPoint(20, 0);
		
		for(int i=size; i<quantity+size; i++)
		{
			label = new QLabel(this);
			label->resize(16, 20);
			label->setScaledContents(true);
			label->setPixmap(QPixmap(pixPath));
			label->setToolTip(toolTip);
			label->move(initialPos);
			label->show();
			
			vect->push_back(label);
			
			initialPos.setX( initialPos.x()+20 );
		}
	}
}

void MainWidget::removeBarrelFromReserve(quint8 id, quint8 quantity)
{
	QVector<QLabel*> *vect;

	switch( id )
	{
		case CORN_BARREL:
			vect = &cornBarrels;
			break;
		case INDIGO_BARREL:
			vect = &indigoBarrels;
			break;
		case SUGAR_BARREL:
			vect = &sugarBarrels;
			break;
		case TOBACCO_BARREL:
			vect = &tobaccoBarrels;
			break;
		case COFFEE_BARREL:
			vect = &coffeeBarrels;
			break;
		default: qDebug() << "Bad barrel id."; return;
	}

	quint8 size = vect->size();
	
	// Vect isnt empty.
	if( size )
	{
		qDebug() << "Vect size == "<< size;
	
		// Asked quantity to remove > barrels
		// => we remove all barrels
		if( quantity > size )
		{
			qDeleteAll(*vect);
			vect->resize(0);
		}
		else // barrels > asked quantity to remove
		{
			quint8 remainingBarrels = size - quantity;
		
			for(int i=size; i > remainingBarrels; i-- )
			{
				delete vect->at(i-1);
			}
			
			vect->resize(remainingBarrels);
			qDebug() << "\nNow, Vect size == " << vect->size();
		}
	}
	else
	{
		qDebug() << "No barrel to remove here...";
	}
}


void MainWidget::fillColonistShips(quint8 n)
{
	if( n > 0 ) // We fill n tokens on Colonist' Ship
	{
		ColonistToken *ct = 0;
		
		for(int i=0; i<n; i++)
		{
			ct = new ColonistToken(this, QSize(21, 21));
			ct->move(730+rnd(80), 250+rnd(150));
			ct->show();
			colonistsInGame.push_back(ct);
		}
	}
}
