#include "CView.h"

CView::CView(QWidget *parent) : QMainWindow(parent)
{

	m_access_tab = nullptr;
	m_objs_tab = nullptr;
	m_verwin_tab = nullptr;
//Main Window
    m_mdi = new QMdiArea;
    setCentralWidget(m_mdi);
    this->setWindowTitle("WSI 0.0.1 (Windows System Information)");
    QSize MinSize(900,600);
    this->resize(MinSize);
    this->setMinimumSize(MinSize);
//info panel
    QGroupBox *info = new QGroupBox("Add Tab");
    info->setTitle("GetInfo");
    info->setFixedWidth(220);
//button info panel
    btnExit = new QPushButton("Exit");
    btnParserObjs = new QPushButton("view obj's");
    btnParserMapWin = new QPushButton("view map win");
	btnParserAccess = new QPushButton("view map access");
//groupbox -> windows version
    QGroupBox *m_gb_winVer = new QGroupBox("Windows version:");
    //radiobutton info panel
        m_rbtn_winNT = new QRadioButton("winNT");
        m_rbtn_win2000 = new QRadioButton("win2000");
        m_rbtn_winXP = new QRadioButton("winXP");
        m_rbtn_winXP->setChecked(true);
    //layout version windows
        QHBoxLayout *h_lay_winVer = new QHBoxLayout;
        h_lay_winVer->addWidget(m_rbtn_winNT);
        h_lay_winVer->addWidget(m_rbtn_winXP);
        h_lay_winVer->addWidget(m_rbtn_win2000);
        h_lay_winVer->addStretch(1);
    m_gb_winVer->setLayout(h_lay_winVer);
//groupbox -> windows obj's
    //list info panel
    QGroupBox *m_gb_allobj = new QGroupBox("Windows obj's:");
        m_list = new QListView();
		m_list->resizeMode();
        m_rbtn_std = new QRadioButton("std");
        m_rbtn_spec = new QRadioButton("spec");
        m_rbtn_base = new QRadioButton("base");
        m_rbtn_spec->setChecked(true);
    //layout version windows
        QVBoxLayout *h_lay_winObjs = new QVBoxLayout;
        h_lay_winObjs->addWidget(m_list);
		h_lay_winObjs->addWidget(m_rbtn_std);
		h_lay_winObjs->addWidget(m_rbtn_spec);
		h_lay_winObjs->addWidget(m_rbtn_base);
//set geometry
    m_gb_allobj->setLayout(h_lay_winObjs);
//TableView display
    m_boxtab = new QTabWidget;

//layout info panel
    QVBoxLayout *v_info = new QVBoxLayout;

    v_info->addWidget(btnParserObjs);
    v_info->addSpacing(1);
    v_info->addWidget(m_gb_winVer);
    v_info->addSpacing(1);
    v_info->addWidget(btnParserMapWin);
    v_info->addSpacing(1);
    v_info->addWidget(m_gb_allobj);
    v_info->addSpacing(1);
	v_info->addWidget(btnParserAccess);
    v_info->addSpacing(1);
    v_info->addWidget(btnExit);
    //v_info->addSpacing(800);
    info->setLayout(v_info);

//Layout main window
    QHBoxLayout *h_lay = new QHBoxLayout;
    h_lay->addWidget(m_boxtab);
    h_lay->addWidget(info);
    m_mdi->setLayout(h_lay);
//Connect
    //exit
    connect(btnExit,SIGNAL(clicked()),this,SLOT(close()));
    //out tab item = all obj's
    connect(btnParserObjs,SIGNAL(clicked()),this,SLOT(tableViewObjs()));
    //out tab item =  obj
    connect(btnParserMapWin,SIGNAL(clicked()),this,SLOT(tableViewMapWin()));
    //out tab item = access
    connect(btnParserAccess,SIGNAL(clicked()),this,SLOT(tableViewMapObjAccess()));
    //choose an object from the object map ... list
	//QListView::clicked
	connect(m_list, SIGNAL(clicked(QModelIndex)),this, SLOT(onLOFlag(QModelIndex)));
    //version map
    connect(m_rbtn_winNT, SIGNAL(clicked()), this, SLOT(onWMapFlag()));
    connect(m_rbtn_win2000, SIGNAL(clicked()), this, SLOT(onWMapFlag()));
    connect(m_rbtn_winXP, SIGNAL(clicked()), this, SLOT(onWMapFlag()));
	//selected access
    connect(m_rbtn_std, SIGNAL(clicked()), this, SLOT(onWAccessFlag()));
    connect(m_rbtn_spec, SIGNAL(clicked()), this, SLOT(onWAccessFlag()));
    connect(m_rbtn_base, SIGNAL(clicked()), this, SLOT(onWAccessFlag()));

	ftypeaccess = SpecialAR;
	fselect_Ver = WinXP;

	m_table = new QTableView;
	model_tab_data.genMapWin(fselect_Ver);
	QStandardItemModel* pSim = model_tab_data.getStandartModel();
	m_list->setModel(pSim);

	btnParserAccess->setDisabled(true);
}

void CView::tableViewObjs()
{

	if (m_objs_tab) delete m_objs_tab;

	this->allBtnDisabled();

		m_objs_tab = new QTableView;
		model_tab_data.genCurrObjs();

		m_objs_tab->setModel(model_tab_data.getStandartModel());
		m_objs_tab->resizeRowsToContents();

		m_boxtab->addTab(m_objs_tab,"ObjsInfo"); //add TabWidget

	this->allBtnEnabled();
}

void CView::tableViewMapWin()  // to return QStandardItemModel in active tabWidget
{

	if (m_verwin_tab) delete m_verwin_tab;

	this->allBtnDisabled();

		m_verwin_tab = new QTableView;
		model_tab_data.genMapWin(fselect_Ver);

		m_verwin_tab->setModel(model_tab_data.getStandartModel());
		m_verwin_tab->resizeRowsToContents();

		m_boxtab->addTab(m_verwin_tab,"Windows Objs"); //add TabWidget

	this->allBtnEnabled();
}

void CView::tableViewMapObjAccess()
{

	if (m_access_tab) delete m_access_tab;
	if (selected_str.isEmpty())
	{
		btnParserAccess->setDisabled(true);
	}
	else
	{
		allBtnDisabled();

			m_access_tab = new QTableView;
			model_tab_data.genAccessTab(ftypeaccess, selected_str.toStdString());

			m_access_tab->setModel(model_tab_data.getStandartModel());
			m_access_tab->resizeRowsToContents();

			m_boxtab->addTab(m_access_tab,"Windows Access"); //add TabWidget

		allBtnEnabled();
	}
}

void CView::onWMapFlag()
{
	if (m_rbtn_win2000->isChecked())		fselect_Ver = Win2000;
	if (m_rbtn_winNT->isChecked())		fselect_Ver = WinNT;
	if (m_rbtn_winXP->isChecked())		fselect_Ver = WinXP;
}

void CView::onWAccessFlag()
{
	if (m_rbtn_std->isChecked())		ftypeaccess = StandardAR;
	if (m_rbtn_spec->isChecked())	ftypeaccess = SpecialAR;
	if (m_rbtn_base->isChecked())	ftypeaccess = BasicAR;
}

void CView::onLOFlag(const QModelIndex& item)
{
	btnParserAccess->setEnabled(true);
	selected_str = item.data().toString();
}

void CView::allBtnDisabled()
{
	btnExit->setDisabled(true); 
    btnParserObjs->setDisabled(true);
    btnParserMapWin->setDisabled(true);
	btnParserAccess->setDisabled(true);
	allBtnRepaint();
}

void CView::allBtnEnabled()
{
	btnExit->setDisabled(false); 
    btnParserObjs->setDisabled(false);
    btnParserMapWin->setDisabled(false);
	if (selected_str.isEmpty())
		btnParserAccess->setDisabled(true);
	else
		btnParserAccess->setDisabled(false);
	allBtnRepaint();
}

void CView::allBtnRepaint()
{
	btnExit->repaint();
	btnParserObjs->repaint();
	btnParserMapWin->repaint();
	btnParserAccess->repaint();
}
