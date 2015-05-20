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

#ifndef MAINFORM_HPP
#define MAINFORM_HPP

#include <QtGui>
#include "QMainWindow"
#include "ui_MainForm.h"
#include "mainwidget.hpp" // central widget class

// This form includes menus/status bar etc...

class MainForm : public QMainWindow
{
	Q_OBJECT

	public:
		MainForm(QWidget *parent=0, Qt::WindowFlags flags=0);
		~MainForm();
		
	private:
		Ui::MainForm ui;
		MainWidget *boardgame;
		
	private slots:
		void quickGame();
		void test();
		void test2();
		void destroyGame();
};

#endif
