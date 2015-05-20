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

#include "mainform.hpp"


MainForm::MainForm(QWidget *p, Qt::WindowFlags f) : QMainWindow(p, f)
{
	ui.setupUi(this);
	boardgame = new MainWidget(this);
	setCentralWidget(boardgame);
	
	connect(ui.actionQuickGame, SIGNAL(triggered()), this, SLOT(quickGame()));
	connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(destroyGame()));
	
	connect(ui.actionLoadGame, SIGNAL(triggered()), this, SLOT(test()));
	connect(ui.actionSaveGame, SIGNAL(triggered()), this, SLOT(test2()));
}


MainForm::~MainForm()
{
	delete boardgame;
}

void MainForm::quickGame()
{
	//QMessageBox::warning(this, "blabla", "olol ?", QMessageBox::Yes | QMessageBox::Default, QMessageBox::No);
	boardgame->createQuickGame();
}

void MainForm::destroyGame()
{
	boardgame->destroyGame();
}

void MainForm::test()
{
	boardgame->addBarrelToReserve(SUGAR_BARREL, 3);
}

void MainForm::test2()
{
	boardgame->removeBarrelFromReserve(SUGAR_BARREL, 2);
}
