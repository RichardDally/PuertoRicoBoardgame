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

#include "tokenslot.hpp"
#include <QtGui>


TokenSlot::TokenSlot(QWidget *p) : QLabel(p)
{
	setScaledContents(true);
	setAcceptDrops(true);
	
	lowestValue = highestValue = 255;
	token = NULL;
	locked = false;
	empty = true;
}

TokenSlot::~TokenSlot()
{
}

void TokenSlot::lock()
{
	locked = true;
}

void TokenSlot::unlock()
{
	locked = false;
}

void TokenSlot::toggleLock()
{
	locked? locked=false : locked=true;
}


bool TokenSlot::isLocked()
{
	return locked;
}


void TokenSlot::setEmpty(bool empty)
{
	this->empty = empty;
}

bool TokenSlot::isEmpty()
{
	return empty;
}


void TokenSlot::dropEvent(QDropEvent *event)
{
	event->ignore();
}


void TokenSlot::dragEnterEvent(QDragEnterEvent *event)
{
	if( empty == false )
	{
		event->ignore();
		return;
	}
	
	if (event->mimeData()->hasFormat("application/tokendata")) 
	{
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
	else
	{
		event->ignore();
    }
}

void TokenSlot::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat("application/tokendata"))
	{
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
	else
	{
        event->ignore();
    }
}


void TokenSlot::mousePressEvent(QMouseEvent *event)
{
	qDebug() << "TokenSlot::mousePressEvent";
}


/*********************************************************************************/


JobSlot::JobSlot(QWidget *p) : TokenSlot(p)
{
	resize(111, 171);
	
	// Set the range
	lowestValue = SETTLER;
	highestValue = PROSPECTOR;
	
	// Tool tip
	setText(tr("Déposez ici le métier\n que vous désirez."));
}


void JobSlot::fillSlot(quint8 id)
{
	empty = false;
	token = NULL;
	
	switch( id )
	{
		case SETTLER: setPixmap(QPixmap(":/res/metiers/intendant.jpg")); break;
		case MAYOR: setPixmap(QPixmap(":/res/metiers/maire.jpg")); break;
		case BUILDER: setPixmap(QPixmap(":/res/metiers/batisseur.jpg")); break;
		case CRAFTSMAN: setPixmap(QPixmap(":/res/metiers/contremaitre.jpg")); break;
		case TRADER: setPixmap(QPixmap(":/res/metiers/marchand.jpg")); break;
		case CAPTAIN: setPixmap(QPixmap(":/res/metiers/armateur.jpg")); break;
		case PROSPECTOR: setPixmap(QPixmap(":/res/metiers/chercheur_or.jpg")); break;
		default: empty = true; qDebug() << "Issue @ JobSlot::fillSlot("<<(int)id<<").";
	}
}

void JobSlot::dropEvent(QDropEvent *event)
{
	if( empty == true )
	if (event->mimeData()->hasFormat("application/tokendata"))
	{
        QByteArray itemData = event->mimeData()->data("application/tokendata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		QPoint offset;
		quint8 type;
        dataStream >> offset >> type;
		
		if( (type >= lowestValue) && (type <= highestValue) )
		{
			JobToken *jt = static_cast<JobToken*>(event->source());
			
			if( jt )
			{
				token = jt;
				jt->move(pos());
				jt->resize(111, 171);
				empty = false;
				clear();
				
				event->accept();
				return;
			}
		}
    }
	
	event->ignore();
}


/*********************************************************************************/


// Plantation == 0
// Building == 1
ColonistSlot::ColonistSlot(quint8 destination, QWidget *p) : TokenSlot(p)
{
	switch( destination )
	{
		case 0: resize(16, 16); ownerType = 0; break;
		case 1: resize(27, 27); ownerType = 1; break;
		default: qDebug() << "Issue @ ColonistSlot::ColonistSlot("<<(int)destination<<").";
	}
	
	lowestValue = highestValue = COLONIST;
}

void ColonistSlot::fillSlot()
{
	empty = false;
	token = NULL;
	setPixmap(QPixmap(":/res/divers/colon.png"));
}


void ColonistSlot::dropEvent(QDropEvent *event)
{
	if( token == NULL )
	if (event->mimeData()->hasFormat("application/tokendata"))
	{
        QByteArray itemData = event->mimeData()->data("application/tokendata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		QPoint offset;
		quint8 type;
        dataStream >> offset >> type;
		
		if( type == COLONIST )
		{
			ColonistToken *ct = static_cast<ColonistToken*>(event->source());
			
			if( ct )
			{
				if( ct->occupiedSlot )
				{
					ct->occupiedSlot->token = NULL;
					ct->occupiedSlot->show();
					ct->occupiedSlot->setEmpty();
				}
				
				hide();
				token = ct;
				ct->move(pos());
				
				if( ownerType == 0 )
					ct->resize(16, 16);
				else
					ct->resize(27, 27);
				
				ct->occupiedSlot = this;
				ct->show();
				empty = false;
				
				
				event->accept();
				return;
			}
		}
    }
	
	event->ignore();
}

void ColonistSlot::mousePressEvent(QMouseEvent *event)
{
	qDebug() << "ColonistSlot::mousePressEvent, yop";
}


/*********************************************************************************/


BuildingSlot::BuildingSlot(QWidget *p) : TokenSlot(p)
{
	resize(103, 58);
	below_slot = NULL;
	
	// Set the range
	lowestValue = PETITE_TEINTUTERIE_INDIGO;
	highestValue = HOTEL_VILLE;
}

int BuildingSlot::fillSlot(quint8 id)
{
	if( id>=PETITE_TEINTUTERIE_INDIGO && id<=QUAI )
	{
		empty = false;
	
		switch( id )
		{
			case PETITE_TEINTUTERIE_INDIGO: setPixmap(QPixmap(":/res/batiments/petite_teintuterie_indigo.jpg")); break;
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
			default: empty = true; qDebug() << "Issue @ BuildingSlot::fillSlot("<<(int)id<<").";;
		}
		
		return 0;
	}
	
	if( id>=GUILDE && id<=HOTEL_VILLE )
	{
		// this slot has no below_slot.
		if( !below_slot )
			return 1;
		
		// this slot has a below_slot but its occupied.
		if( !below_slot->isEmpty() )
			return 1;
		
		empty = false;
		below_slot->setEmpty(false);
		
		switch( id )
		{
			case GUILDE: setPixmap(QPixmap(":/res/batiments/guilde.jpg")); break;
			case RESIDENCE: setPixmap(QPixmap(":/res/batiments/residence.jpg")); break;
			case FORTERESSE: setPixmap(QPixmap(":/res/batiments/forteresse.jpg")); break;
			case DOUANE: setPixmap(QPixmap(":/res/batiments/douane.jpg")); break;
			case HOTEL_VILLE: setPixmap(QPixmap(":/res/batiments/hotel_ville.jpg")); break;
			default: empty = true;
		}
		
		return 0;
	}
	
	return 2;
}

void BuildingSlot::linkBelowSlot(BuildingSlot *below)
{
	below_slot = below;
}


void BuildingSlot::dropEvent(QDropEvent *event)
{
	if( token == NULL ) // this slot is empty ?
	if (event->mimeData()->hasFormat("application/tokendata"))
	{
        QByteArray itemData = event->mimeData()->data("application/tokendata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		QPoint offset;
		quint8 type;
        dataStream >> offset >> type;
		
		if( (type >= lowestValue) && (type <= highestValue) )
		{
			BuildingToken *bt = static_cast<BuildingToken*>(event->source());
			
			if( bt )
			{
				if( type>=PETITE_TEINTUTERIE_INDIGO && type<=QUAI )
				{
					// if occupiedSlot != NULL
					// it means bt has been moved from another BuildingSlot
					// so we need to unlink the last slot, its now free.
					if( bt->occupiedSlot )
					{
						bt->occupiedSlot->token = NULL;
						bt->occupiedSlot->show();
						bt->occupiedSlot->setEmpty();
						//qDebug() << "bt->occupiedSlot->token = NULL";
						
						// If there are slots + tokens in slots
						// we need to move its.
						for(int i=0; i<bt->my_slots.size(); i++)
						{
							if( bt->my_slots[i] )
							{
								bt->my_slots[i]->move(pos().x()+5+(27*i), pos().y()+27);
								
								if( bt->my_slots[i]->token )
									bt->my_slots[i]->token->move(pos().x()+5+(27*i), pos().y()+27);
							}
						}
					}
					else // BuildingToken comes from MainBoardGame
					{
						for(int i=0; i < bt->my_slots.size(); i++)
						{
							if( bt->my_slots[i] == NULL )
							{
								bt->my_slots[i] = new ColonistSlot(1, parentWidget());
								bt->my_slots[i]->move(pos().x()+5+(27*i), pos().y()+27);
								bt->my_slots[i]->show();
								bt->my_slots[i]->setEnabled(true);
							}
						}
					}
					
					token = bt;
					bt->move(pos());
					bt->resize(103, 58);
					bt->occupiedSlot = this;
					setEmpty(false);
					hide();
					
					event->accept();
					return;
				}
				else
				{
					// We need to check if below slot is occupied or not.
					if( below_slot ) // it got below slot ?
					if( below_slot->token == NULL ) // below_slot hasnt any token ?
					{
						//qDebug() << "below_slot != NULL";
						//qDebug() << "below_slot->token == NULL\n";
						
						if( bt->occupiedSlot )
						{
							//qDebug() << "bt->occupiedSlot != NULL";
							bt->occupiedSlot->token = NULL;
							bt->occupiedSlot->below_slot->token = NULL;
							bt->occupiedSlot->setEmpty();
							bt->occupiedSlot->below_slot->setEmpty();
							bt->occupiedSlot->show();
							
							if( bt->my_slots.size() )
							{
								if( bt->my_slots[0] )
								{
									bt->my_slots[0]->move(pos().x()+7, pos().y()+90);
								
									if( bt->my_slots[0]->token )
										bt->my_slots[0]->token->move(pos().x()+7, pos().y()+90);
								}
							}
						}
						else // BuildingToken comes from MainBoardGame
						{
							if( bt->my_slots.size() )
							if( bt->my_slots[0] == NULL )
							{
								bt->my_slots[0] = new ColonistSlot(1, parentWidget());
								bt->my_slots[0]->move(pos().x()+7, pos().y()+90);
								bt->my_slots[0]->show();
								bt->my_slots[0]->setEnabled(true);
							}
						}
						
						token = bt;
						below_slot->token = bt;
						bt->move(pos());
						bt->resize(103, 121);
						bt->occupiedSlot = this;
						setEmpty(false);
						below_slot->setEmpty(false);
						hide();
						
						
						event->accept();
						return;
					}
				}
			}
		}
    }
	
	event->ignore();
}


/*********************************************************************************/


PlantationSlot::PlantationSlot(QWidget *p) : TokenSlot(p)
{
	resize(43, 43);
	
	// Set the range
	lowestValue = CORN;
	highestValue = QUARRY;
}

void PlantationSlot::fillSlot(quint8 id)
{
	empty = false;
	
	switch( id )
	{
		case CORN: setPixmap(QPixmap(":/res/plantations/mais.jpg")); break;
		case INDIGO: setPixmap(QPixmap(":/res/plantations/indigo.jpg")); break;
		case SUGAR: setPixmap(QPixmap(":/res/plantations/sucre.jpg")); break;
		case TOBACCO: setPixmap(QPixmap(":/res/plantations/tabac.jpg")); break;
		case COFFEE: setPixmap(QPixmap(":/res/plantations/cafe.jpg")); break;
		case QUARRY: setPixmap(QPixmap(":/res/plantations/carriere.jpg")); break;
		default: empty = true; qDebug() << "Issue @ BuildingSlot::fillSlot("<<(int)id<<").";
	}
}

void PlantationSlot::dropEvent(QDropEvent *event)
{
	if( token == NULL )
	if (event->mimeData()->hasFormat("application/tokendata"))
	{
        QByteArray itemData = event->mimeData()->data("application/tokendata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		QPoint offset;
		quint8 type;
        dataStream >> offset >> type;
		
		if( (type >= lowestValue) && (type <= highestValue) )
		{
			PlantationToken *pt = static_cast<PlantationToken*>(event->source());
			
			if( pt == NULL )
				return;
			
			if( pt->occupiedSlot ) // This token comes from Island's or City's board.
			{
				qDebug() << "pt->occupiedSlot != NULL";
				pt->occupiedSlot->token = NULL;
				pt->occupiedSlot->show();
				pt->occupiedSlot->setEmpty();
				
				if( pt->my_slot ) // This token created a slot, so we move it too.
				{
					qDebug() << "my_slot != NULL";
					pt->my_slot->move(pos().x()+7, pos().y()+21);
					
					if( pt->my_slot->token ) // This token's slot owns a token, we move owned token.
					{
						pt->my_slot->token->move(pos().x()+7, pos().y()+21);
					}
				}
			}
			else // this plantation token comes from availables plantations area.
			{
				if( pt->my_slot == NULL )
				{
					qDebug() << "Creating ColonistSlot";
					pt->my_slot = new ColonistSlot(0, parentWidget());
					pt->my_slot->move(pos().x()+7, pos().y()+21);
					pt->my_slot->show();
					pt->my_slot->setEnabled(true);
				}
			}
			
			token = pt;
			//pt->lock();
			pt->occupiedSlot = this;
			pt->resize(43, 43);
			pt->move(pos());
			setEmpty(false);
			hide();
			
			//qDebug() << "PlantationSlot, pos() = " << pos();
			//qDebug() << "my_slot, pos() = " << my_slot->pos();
			
			event->accept();
			return;
		}
    }
	
	event->ignore();
}

/*
void PlantationSlot::mouseDoubleClickEvent(QMouseEvent *event)
{
	// Slot is filled.
	if( empty == false )
	{
		if( my_slot )
			if( !my_slot->isEmpty() )
			{
				qDebug() << "The colonist has been moved to San Juan.";
				my_slot->removeTokenFromSlot();
			}
	}
}
*/


/*********************************************************************************/


BarrelSlot::BarrelSlot(QWidget *p) : TokenSlot(p)
{
	resize(16, 21);
	
	// Set the range
	lowestValue = CORN_BARREL;
	highestValue = COFFEE_BARREL;
}

void BarrelSlot::fillSlot(quint8 id)
{
	empty = false;
	
	switch( id )
	{
		case CORN_BARREL: setPixmap(QPixmap(":/res/tonneaux/tonneau_mais.png")); break;
		case INDIGO_BARREL: setPixmap(QPixmap(":/res/tonneaux/tonneau_indigo.png")); break;
		case SUGAR_BARREL: setPixmap(QPixmap(":/res/tonneaux/tonneau_sucre.png")); break;
		case TOBACCO_BARREL: setPixmap(QPixmap(":/res/tonneaux/tonneau_tabac.png")); break;
		case COFFEE_BARREL: setPixmap(QPixmap(":/res/tonneaux/tonneau_cafe.png")); break;
		default:empty = true;
	}
}

void BarrelSlot::restrictBarrelType(quint8 id)
{
	if( (id >= CORN_BARREL) && (id <= COFFEE_BARREL) )
	{
		lowestValue = highestValue = id;
	}
}

void BarrelSlot::dropEvent(QDropEvent *event)
{
	if( empty == true )
	if (event->mimeData()->hasFormat("application/tokendata"))
	{
        QByteArray itemData = event->mimeData()->data("application/tokendata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		QPoint offset;
		quint8 type;
        dataStream >> offset >> type;
		
		if( (type >= lowestValue) && (type <= highestValue) )
		{
			BarrelToken *bt = static_cast<BarrelToken*>(event->source());
			
			if( bt )
			{
				bt->move(pos());
				bt->resize(16, 21);
				setEmpty(false);
				
				event->accept();
				return;
			}
		}
    }
	
	event->ignore();
}

/*********************************************************************************/


SanJuan::SanJuan(QWidget *p, QSize s) : QFrame(p)
{
	setAcceptDrops(true);
	resize(s);
}

void SanJuan::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("application/tokendata")) 
	{
		if (event->source() == this)
		{
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
		else
		{
			event->acceptProposedAction();
        }
    }
	else
	{
		event->ignore();
    }
}

void SanJuan::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat("application/tokendata"))
	{
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
	else
	{
        event->ignore();
    }
}

void SanJuan::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat("application/tokendata"))
	{
        QByteArray itemData = event->mimeData()->data("application/tokendata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		QPoint offset;
		quint8 type;
        dataStream >> offset >> type;
		
		if( type == COLONIST )
		{
			ColonistToken *ct = static_cast<ColonistToken*>(event->source());
			
			if( ct )
			{
				if( ct->occupiedSlot )
				{
					ct->occupiedSlot->token = NULL;
					ct->occupiedSlot->show();
					ct->occupiedSlot->setEmpty();
				}
				
				ct->move(event->pos()+pos()-offset);
				ct->resize(16, 16);
				
				qDebug() << "childrenRegion =>" << childrenRegion();
				
				if( !idleColonists.contains(ct) )
					idleColonists.push_back(ct);
					
				event->accept();
				return;
			}
		}
    }
	
	event->ignore();
}

