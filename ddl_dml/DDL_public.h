#ifndef DDL_PUBLIC_H
#define DDL_PUBLIC_H
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <malloc.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "SqlGlobal.h"
#include <cstring>
using namespace std;
extern void strcopy(char*& src, char*& dest);
#ifdef DML_TEST

enum AttrType {
	INT,
	FLOAT,
	STRING,
	VARCHAR
};
struct AttrInfo {
	char* attrName;
	AttrType AttrType;
	int attrLength;
};

#endif // DML_TEST

class DROPTYPE {
public:
	static const int TABLE = 1;
	static const int DATABASE = 2;
};


class ALTERTYPE {
public:
	static const int DROP_COL = 1;
	static const int DROP_CONSTRAINT = 2;
	static const int ALTER_COL = 3;
	static const int ADD_CONSTRAINT = 4;
	static const int ADD_COL = 5;
	static const int MODIFY_COL = 6;
};

class DDL_SQL_TYPE {
public:
	static const int DDL_TYPE_CREATE_TABLE = 1;
	static const int DDL_TYPE_CREATE_DATABASE = 2;
	static const int DDL_TYPE_CREATE_INDEX = 3;
	static const int DDL_TYPE_DROP = 4;
	static const int DDL_TYPE_ALTER = 5;
	static const int DDL_TYPE_OPEN_DB = 6;
	static const int DDL_TYPE_CONNECT_RESET = 7;
};

class DDL_DATA_TYPE {
public:
	static const int DDL_INT = 1;
	static const int DDL_FLOAT = 2;
	static const int DDL_STRING = 3;
	string static trans(int type) {
		string res;
		switch (type)
		{
		case 1:res = "INT"; return res;
		case 2:res = "FLOAT"; return res;
		case 3:res = "STRING"; return res;
		default:if (type < 0) {
			res = "VARCHAR";
			res += "(";
			res += to_string(-type);
			res += ")";
		}
		else res = "";
			return res;
		}
	}
};

class DDL_CONS_TYPE {
public:
	static const int DDL_CONS_PRIKEY = 1;
	static const int DDL_CONS_NOTNULL = 2;
	static const int DDL_CONS_UNIQUE = 4;
	//4 8 16 32
	string static trans(int type) {
		string res;
		switch (type)
		{
		case 1:res = "PRIMARY KEY"; return res;
		case 2:res = "NOT NULL"; return res;
		case 4:res = "UNIQUE"; return res;
		default:return "";
		}
	}
};

struct ColDef{
	char* name;  //����
	int datatype;  //��������
	vector<int> constypes;  //Լ������
};

struct CreateTableStmt {
	char* tablename;
	vector<ColDef> cols;
};

struct CreateDatabaseStmt{
	char* databasename;
};

struct DropStmt {
	char* dropname;
	int dropType; 
};

struct CreateIndex{
	char* tablename;
	char* indexname;
	vector<string> colnames;
};

struct AlterStmt {
	char* tablename;
	int altertype;
	vector<ColDef> cols; 
	int constrainttype;
	char* constraintname;
	int modifytype;
};

struct OpenDBStmt {
	char* dbName;
};

static AttrInfo* transDatatype2AttrInfo(vector<ColDef>& cols) {
	AttrInfo* res = new AttrInfo[cols.size()];
	for (int i = 0; i < cols.size(); i++) {
		strcopy(cols[i].name, res[i].attrName);
		switch (cols[i].datatype)
		{
		case 1:res[i].attrType = AttrType::INT; break;
		case 2:res[i].attrType = AttrType::FLOAT; break;
		case 3:res[i].attrType = AttrType::STRING; break;
		default:if (cols[i].datatype < 0) {
			res[i].attrType = AttrType::VARCHAR;
			res[i].attrLength = -cols[i].datatype;
		}
			   else cout << "ת����������";
			break;
		}
	}
	return res;
};

class DDLStmt {
public:
	//!!!!!!!!!!!!!!!!!!ִ����Ҫ�޸����������������Ҫ����Ϣ�Ҷ�cout�ˣ�ֱ�Ӵ���ִ�к���
	int transform() {
		int i,j;
		switch (stmttype)
		{
		case DDL_SQL_TYPE::DDL_TYPE_CREATE_TABLE:
#ifndef DML_TEST
            SqlGlobal::getInstance()->ddl_mgr->createTable(createtable->tablename, createtable->cols.size(),
			transDatatype2AttrInfo(createtable->cols));

#endif // !DML_TEST


			cout << "�������" << endl;
			cout << "�����ǣ�" << createtable->tablename << endl;
			if (createtable->cols.size() > 0) {
				cout << "�����������ԣ�" << endl;
			}
			for (i = 0; i < createtable->cols.size(); i++) {
				cout << "������" << createtable->cols[i].name << " ";
				cout << "�������ͣ�" << DDL_DATA_TYPE::trans(createtable->cols[i].datatype).c_str() << " ";
				if (createtable->cols[i].constypes.size() > 0)
					cout << "Լ����";
				for (j = 0; j < createtable->cols[i].constypes.size(); j++)
					cout << DDL_CONS_TYPE::trans(createtable[i].cols[i].constypes[j]).c_str() << " ";
				cout << endl;
			}

			break;
		case DDL_SQL_TYPE::DDL_TYPE_CREATE_DATABASE:
#ifndef DML_TEST
		    SqlGlobal::getInstance()->ddl_mgr->createDb(createdatabase->databasename);
#endif
			cout << "�������ݿ����" << endl;
			cout << "���ݿ�����:" << createdatabase->databasename << endl;

			break;
		case DDL_SQL_TYPE::DDL_TYPE_CREATE_INDEX:

#ifndef DML_TEST
		    SqlGlobal::getInstance()->ddl_mgr->dropIndex(createindex->tablename,createindex->indexname);
#endif // !DML_TEST

			cout << "�����������" << endl;
			cout << "������" <<createindex->tablename<< endl;
			cout << "��������" << createindex->indexname << endl;
			if (createindex->colnames.size() > 0) {
				cout << "����:" << endl;
			}
			for (i = 0; i < createindex->colnames.size(); i++) {
				cout << createindex->colnames[i].c_str() << " ";
			}
			cout << endl;
			
			break;
		case DDL_SQL_TYPE::DDL_TYPE_DROP:
			
			cout << "ɾ�����" << endl;
			switch (dropstmt->dropType)
			{
			case DROPTYPE::TABLE:
#ifndef DML_TEST
                    SqlGlobal::getInstance()->ddl_mgr->dropTable(dropstmt->dropname);
#endif // !DML_TEST

				cout << "ɾ��������" << dropstmt->dropname << endl; break;
			case DROPTYPE::DATABASE:
#ifndef DML_TEST
                    SqlGlobal::getInstance()->ddl_mgr->destroyDb(dropstmt->dropname);
#endif // !DML_TEST
				cout << "ɾ�����ݿ�����" << dropstmt->dropname << endl; break;
			default:
				break;
			}

			break;
		case DDL_SQL_TYPE::DDL_TYPE_ALTER:
			
			cout << "ALTER���" << endl;
			cout << "������" << alterstmt->tablename << endl;
			switch (alterstmt->altertype)
			{
			case ALTERTYPE::DROP_COL:
				cout << "ɾ����" << endl;
				cout << "������";
				for (i = 0; i < alterstmt->cols.size(); i++) {
					cout << alterstmt->cols[i].name << endl;
				}
				break;
			case ALTERTYPE::DROP_CONSTRAINT:
				cout << "ɾ��Լ��" << endl;
				cout << "Լ������" << alterstmt->constraintname << endl;
				break;
			case ALTERTYPE::ADD_COL:
				cout << "������" << alterstmt->cols[0].name << " ";
				cout << "�������ͣ�" << DDL_DATA_TYPE::trans(alterstmt->cols[0].datatype).c_str() << " ";
				break;
			case ALTERTYPE::ADD_CONSTRAINT:
				cout << "Լ������" << alterstmt->constraintname << " ";
				cout << "Լ�����ͣ�" << DDL_CONS_TYPE::trans(alterstmt->constrainttype).c_str() << " ";
				cout << "����: ";
				for (i = 0; i < alterstmt->cols.size(); i++) {
					cout << alterstmt->cols[i].name << " ";
				}
				cout << endl;
				break;
			case ALTERTYPE::ALTER_COL:
				cout << "�޸��е���������" << endl; 
				cout << "������" << alterstmt->cols[0].name << " ";
				cout << "�������ͣ�" << DDL_DATA_TYPE::trans(alterstmt->cols[0].datatype).c_str() << " ";
				break;
			case ALTERTYPE::MODIFY_COL:
				cout << "�������Լ��" << endl;
				cout << "������" << alterstmt->cols[0].name << " ";
				cout << "Լ�����ͣ�" << DDL_CONS_TYPE::trans(alterstmt->modifytype).c_str() << " ";
				break;
			default:
				break;
			}
			
			break;
		case DDL_SQL_TYPE::DDL_TYPE_OPEN_DB:
			cout << "�������ݿ�" << endl;
			cout << "���ݿ����ƣ�" << opendbstmt->dbName << endl;
#ifndef DML_TEST
			SqlGlobal::getInstance()->ddl_mgr->openDb(opendbstmt->dbName);
#endif // !DML_TEST
			break;
		case DDL_SQL_TYPE::DDL_TYPE_CONNECT_RESET:
			cout << "�Ͽ����ݿ�����" << endl;
#ifndef DML_TEST
            SqlGlobal::getInstance()->ddl_mgr->closeDb();
#endif // !DML_TEST
			break;
		default:
			//cout << "SQL�����ִ���" << endl;
			return -1;
			break;
		}
		return 1;
	}

	int stmttype;   //SQL�������
	CreateTableStmt *createtable;
	CreateDatabaseStmt *createdatabase;
	CreateIndex *createindex;
	DropStmt *dropstmt;
	AlterStmt *alterstmt;
	OpenDBStmt *opendbstmt;
};




#endif // !DDL_PUBLIC_H
