/********************************************************
	* File: CView.h
	* Discription: Create View.
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

#ifndef VIEW_H
#define VIEW_H

#include <QFile>

#include <QStandardItem>
#include <QStandardItemModel>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

//компаненты:

#include <QtWidgets/QTableView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>
#include <QRadioButton>
#include <QComboBox>
#include <QListWidget>
#include <QListWidgetItem>

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include <string>
#include <qdialog.h>

#include "../Model/CModel.h"
#include <QListView>

/********************************************************/

	class CView : public QMainWindow
	{

		Q_OBJECT

	public:

		explicit CView(QWidget *parent = 0);

		QStandardItem       *m_pData;
		QStandardItemModel  *m_model;
		QTableView          *m_table; //main , tab's
		QTableView          *m_access_tab;
		QTableView          *m_objs_tab;
		QTableView          *m_verwin_tab;

		QTabWidget          *m_boxtab;
		QMdiArea            *m_mdi;
		QRadioButton        *m_radioButton;
		QComboBox           *m_comboBox;

		CModel				model_tab_data;
		QListWidgetItem*	fselect_Obj;
		VERWIN				fselect_Ver;
		TYPEACCESS			ftypeaccess;

	private:

		QPushButton		*btnExit;
		QPushButton		*btnParserObjs;
		QPushButton		*btnParserMapWin;
		QPushButton		*btnParserAccess;

		QRadioButton	*m_rbtn_winNT;
		QRadioButton	*m_rbtn_win2000;
		QRadioButton	*m_rbtn_winXP;
		QListView		*m_list;
		QModelIndex		selected_model;
		QString			selected_str;

		QRadioButton	*m_rbtn_std;
		QRadioButton	*m_rbtn_spec;
		QRadioButton	*m_rbtn_base;
	
		void allBtnRepaint();

	public slots:

		void tableViewObjs();                       //parser and out all obj's
		void tableViewMapWin();                     //
		void tableViewMapObjAccess();//
	
		void onLOFlag(const QModelIndex& item);		//set's flags gui
		void onWMapFlag();
		void onWAccessFlag();

		void allBtnDisabled();
		void allBtnEnabled();

	};

#endif // VIEW_H