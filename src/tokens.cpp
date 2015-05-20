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

#include "tokens.hpp"


Token::Token(QWidget *p) : QLabel(p)
{
	setScaledContents(true);
	locked = false;
	my_id = 255;
}


Token::~Token()
{
}

void Token::lock()
{
	locked = true;
}

void Token::unlock()
{
	locked = false;
}

void Token::toggleLock()
{
	locked? locked=false : locked=true;
}




void Token::mousePressEvent(QMouseEvent *event)
{
	if( locked )
	{
		qDebug() << "Token::mousePressEvent, locked == true";
		return;
	}
	
	if( pixmap() == NULL )
	{
		qDebug() << "Token::mousePressEvent, pixmap() == NULL";
		return;
	}
	
	QPixmap pxm = *pixmap();
	
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QPoint(event->pos()) << my_id;
	//dataStream << pxm << my_id;
	
	
	// We add some grey on original token
	QPixmap tempPixmap = pxm;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pxm.rect(), QColor(127, 127, 127, 127));
    painter.end();
	
	// We scale pixmap (reduce size)
	QPixmap scaled = pxm.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/tokendata", itemData);
	
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(scaled);
    drag->setHotSpot(event->pos());
	
    setPixmap(tempPixmap);
	
	
    if (drag->exec(Qt::MoveAction, Qt::MoveAction) == Qt::MoveAction)
	{
		qDebug() << "event accepted.";
		//setEnabled(true);
		//show();
		setPixmap(pxm);
		//qDebug() << "close() @ TokenMousePressEvent" << close();
        //close();
	}
	else
	{
		qDebug() << "event ignored.";
		show();
		setPixmap(pxm);
	}
}


JobToken::JobToken(quint8 id, QWidget *p) : Token(p)
{
	if( id <= PROSPECTOR )
	{
		resize(50, 80);
		
		switch( id )
		{
			case SETTLER: setPixmap(QPixmap(":/res/metiers/intendant.jpg")); break;
			case MAYOR: setPixmap(QPixmap(":/res/metiers/maire.jpg")); break;
			case BUILDER: setPixmap(QPixmap(":/res/metiers/batisseur.jpg")); break;
			case CRAFTSMAN: setPixmap(QPixmap(":/res/metiers/contremaitre.jpg")); break;
			case TRADER: setPixmap(QPixmap(":/res/metiers/marchand.jpg")); break;
			case CAPTAIN: setPixmap(QPixmap(":/res/metiers/armateur.jpg")); break;
			case PROSPECTOR: setPixmap(QPixmap(":/res/metiers/chercheur_or.jpg")); break;
			default:;
		}
		
		my_id = id;
	}
}

BuildingToken::BuildingToken(quint8 id, QWidget *p) : Token(p)
{
	occupiedSlot = NULL;

	if( (id >= PETITE_TEINTUTERIE_INDIGO) && (id <= HOTEL_VILLE) )
	{
		if(id <= QUAI )
		{
			switch( id )
			{
				case TEINTURERIE_INDIGO: my_slots.resize(3); break;
				case RAFFINERIE_SUCRE: my_slots.resize(3); break;
				case SECHOIR_TABAC: my_slots.resize(3); break;
				case BRULERIE_CAFE: my_slots.resize(2); break;
				default: my_slots.resize(1);
			}
			resize(65, 37);
		}
		else
		{
			my_slots.resize(1);
			resize(65, 77);
		}
		
		switch( id )
		{
			case PETITE_TEINTUTERIE_INDIGO: setPixmap(QPixmap(":/res/batiments/petite_teinturerie_indigo.jpg")); break;
			case PETITE_RAFFINERIE_SUCRE: setPixmap(QPixmap(":/res/batiments/petite_raffinerie_sucre.jpg")); break;
			case PETIT_MARCHE: setPixmap(QPixmap(":/res/batiments/petit_marche.jpg")); break;
			case HACIENDA: setPixmap(QPixmap(":/res/batiments/hacienda.jpg")); break;
			case BARAQUE_CHANTIER: setPixmap(QPixmap(":/res/batiments/baraque_chantier.jpg")); break;
			case PETIT_ENTREPOT: setPixmap(QPixmap(":/res/batiments/petit_entrepot.jpg")); break;
			case TEINTURERIE_INDIGO: setPixmap(QPixmap(":/res/batiments/teinturerie_indigo.jpg")); break;
			case RAFFINERIE_SUCRE: setPixmap(QPixmap(":/res/batiments/raffinerie_sucre.jpg")); break;
			case DISPENSAIRE: setPixmap(QPixmap(":/res/batiments/dispensaire.jpg")); break;
			case COMPTOIR: setPixmap(QPixmap(":/res/batiments/comptoir.jpg")); break;
			case GRAND_MARCHE: setPixmap(QPixmap(":/res/batiments/grand_marche.jpg")); break;
			case GRAND_ENTREPOT: setPixmap(QPixmap(":/res/batiments/grand_entrepot.jpg")); break;
			case SECHOIR_TABAC: setPixmap(QPixmap(":/res/batiments/sechoir_tabac.jpg")); break;
			case BRULERIE_CAFE: setPixmap(QPixmap(":/res/batiments/brulerie_cafe.jpg")); break;
			case MANUFACTURE: setPixmap(QPixmap(":/res/batiments/manufacture.jpg")); break;
			case UNIVERSITE: setPixmap(QPixmap(":/res/batiments/universite.jpg")); break;
			case PORT: setPixmap(QPixmap(":/res/batiments/port.jpg")); break;
			case QUAI: setPixmap(QPixmap(":/res/batiments/quai.jpg")); break;
			case GUILDE: setPixmap(QPixmap(":/res/batiments/guilde.jpg")); break;
			case RESIDENCE: setPixmap(QPixmap(":/res/batiments/residence.jpg")); break;
			case FORTERESSE: setPixmap(QPixmap(":/res/batiments/forteresse.jpg")); break;
			case DOUANE: setPixmap(QPixmap(":/res/batiments/douane.jpg")); break;
			case HOTEL_VILLE: setPixmap(QPixmap(":/res/batiments/hotel_ville.jpg")); break;
			default:;
		}
		
		my_id = id;
	}
}


PlantationToken::PlantationToken(quint8 id, QWidget *p) : Token(p)
{
	occupiedSlot = NULL;
	my_slot = NULL;
	
	if( (id >= CORN) && (id <= QUARRY))
	{
		resize(50, 50);
		
		switch( id )
		{
			case CORN: setPixmap(QPixmap(":/res/plantations/mais.jpg")); break;
			case INDIGO: setPixmap(QPixmap(":/res/plantations/indigo.jpg")); break;
			case SUGAR: setPixmap(QPixmap(":/res/plantations/sucre.jpg")); break;
			case TOBACCO: setPixmap(QPixmap(":/res/plantations/tabac.jpg")); break;
			case COFFEE: setPixmap(QPixmap(":/res/plantations/cafe.jpg")); break;
			case QUARRY: setPixmap(QPixmap(":/res/plantations/carriere.jpg")); break;
			default:;
		}
		
		my_id = id;
		
	}
}

ColonistToken::ColonistToken(QWidget *p, QSize s) : Token(p)
{
	occupiedSlot = NULL;
	resize(s);
	setPixmap(QPixmap(":/res/divers/colon.png"));
	my_id = COLONIST;
}


BarrelToken::BarrelToken(quint8 id, QWidget *p) : Token(p)
{
	if( (id >= CORN_BARREL) && (id <= COFFEE_BARREL))
	{
		resize(21, 31);
		
		switch( id )
		{
			case CORN_BARREL: setPixmap(QPixmap(":/res/tonneaux/tonneau_mais.png")); break;
			case INDIGO_BARREL: setPixmap(QPixmap(":/res/tonneaux/tonneau_indigo.png")); break;
			case SUGAR_BARREL: setPixmap(QPixmap(":/res/tonneaux/tonneau_sucre.png")); break;
			case TOBACCO_BARREL: setPixmap(QPixmap(":/res/tonneaux/tonneau_tabac.png")); break;
			case COFFEE_BARREL: setPixmap(QPixmap(":/res/tonneaux/tonneau_cafe.png")); break;
			default:;
		}
		
		my_id = id;
	}
}
