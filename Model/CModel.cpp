#include "CModel.h"

CModel::CModel()
{
    QString         file("../../../../WSI/model.dll");

    //get all objs from current windows, with attr
    SetListCurrObjs = (getListCurrObjs)QLibrary::resolve(file,"getListCurrObjs");

    //@ -- getListMapObjsWin(list<STBASE>& data, VERWIN ver)
    //get only map version (xp, 2000, nt)
    SetListMapObjsWin = (getListMapObjsWin)QLibrary::resolve(file,"getListMapObjsWin");

    //@ -- getListAccess(list<STBASE>& data, TYPEACCESS type, string& objType)
    //get only map access
    SetListMapAccess = (getListAccess)QLibrary::resolve(file,"getListAccess");
}

//генераторы: data view to QStandardItemModel

void CModel::genMapWin(VERWIN& ver)
{

	SetListMapObjsWin( m_base_data, ver );
	int count_item = 2;
	m_pSim = new QStandardItemModel(m_base_data.size(),count_item);

	m_pSim->setHeaderData(0,Qt::Horizontal,"ObjName");
    m_pSim->setHeaderData(1,Qt::Horizontal,"ID");

	QString str_NameObj;
	QStandardItem *item;
	list<STBASE>::iterator pIter = m_base_data.begin();

	for (int row=0; row<m_base_data.size(); row++)
	{	
		str_NameObj = QString::fromStdString(pIter->text);

		for (int column=0; column<count_item; column++)
		{			
			switch (column)
			{
				case 0:
					item = new QStandardItem(str_NameObj);
				break;
				case 1:
					item = new QStandardItem(QString::number(pIter->val));
				break;
			}
			m_pSim->setItem(row, column, item);
		}
		++pIter;
	}
}

void CModel::genAccessTab(TYPEACCESS type, string& objType)
{
	SetListMapAccess(m_base_data, type, objType);
	int count_item = 2;
	m_pSim = new QStandardItemModel(m_base_data.size(),count_item);

	m_pSim->setHeaderData(0,Qt::Horizontal,"AccessName");
    m_pSim->setHeaderData(1,Qt::Horizontal,"ID");

	QString str_AccessName;
	QStandardItem *item;
	list<STBASE>::iterator pIter = m_base_data.begin();

	for (int row=0; row<m_base_data.size(); row++)
	{	
		str_AccessName = QString::fromStdString(pIter->text);
		for (int column=0; column<count_item; column++)
		{			
			switch (column)
			{
				case 0:
					item = new QStandardItem(str_AccessName);
				break;
				case 1:
					item = new QStandardItem(QString::number(pIter->val));
				break;
			}
			m_pSim->setItem(row, column, item);
		}
		++pIter;
	}
}

void CModel::genCurrObjs()
{
	SetListCurrObjs(m_pack_data);
	//m_pack_data.begin()->Base; m_pack_data.begin()->Handle; m_pack_data.begin()->id;
	//m_pack_data.begin()->ObjName; m_pack_data.begin()->Sandart; m_pack_data.begin()->Special;

	int count_item = 6;
	m_pSim = new QStandardItemModel(m_pack_data.size(),count_item);

	m_pSim->setHeaderData(0,Qt::Horizontal,"Handle");
    m_pSim->setHeaderData(1,Qt::Horizontal,"ID");
	m_pSim->setHeaderData(2,Qt::Horizontal,"ObjName");
	m_pSim->setHeaderData(3,Qt::Horizontal,"Base");
	m_pSim->setHeaderData(4,Qt::Horizontal,"Sandart");
	m_pSim->setHeaderData(5,Qt::Horizontal,"Special");

	QString str_Base; QString str_ObjName; 
	QString str_Sandart; QString str_Special;
	QStandardItem *item;
	list<PACKAGE>::iterator pIter = m_pack_data.begin();

	for (int row=0; row<m_pack_data.size(); row++)//m_pack_data.size(); row++)
	{	
		str_ObjName = QString::fromStdString(pIter->ObjName);
		str_Base = QString::fromStdString(pIter->Base);
		str_Sandart = QString::fromStdString(pIter->Sandart);
		str_Special = QString::fromStdString(pIter->Special);

		for (int column=0; column<count_item; column++)
		{			
			int str_Handle = m_pack_data.begin()->Handle;

			switch (column)
			{
				case 0:
					item = new QStandardItem(QString::number(pIter->Handle));
				break;
				case 1:
					item = new QStandardItem(QString::number(pIter->id));
				break;
				case 2:
					item = new QStandardItem(str_ObjName);
				break;
				case 3:
					item = new QStandardItem(str_Base);
				break;
				case 4:
					item = new QStandardItem(str_Sandart);
				break;
				case 5:
					item = new QStandardItem(str_Special);
				break;
			}
			m_pSim->setItem(row, column, item);
		}
		++pIter;
	}
}

QStandardItemModel* CModel::getStandartModel()
{
	return m_pSim;
}