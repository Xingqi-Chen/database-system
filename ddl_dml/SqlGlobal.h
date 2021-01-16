#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include "ConnectorOptimizer.h"
#include "PhysicalPlan.h"

//#define DML_TEST  //���Խ׶���define
#ifndef DML_TEST

#include "../sql/ddl.h"
#include "../sql/dml.h"
#include "../execute/Executor.h"
#include "../execute/ProcessFunc.h"
//#include "../error_message/all_error.h"

#endif
using namespace std;

class ConnectorNode;
class SqlGlobal {
private:
	SqlGlobal();
	static SqlGlobal* instance;
	map<string, int> vmap;//<���ݿ���/����/������,Vֵ>

#ifndef DML_TEST
public:
	PF_Manager* pfManager;
	RM_Manager* rmManager;
	IX_Manager* ixManager;
	DDL_Manager* ddl_mgr;
	DML_Manager* dml_mgr;
#endif

public:
	bool exit = false;
	static SqlGlobal* getInstance();
private:
	int getRandom(int min);//��ȡ>min�������
public:
	//���º����������ýӿں���
	int getB(string r);//��ȡ���ɹ�ϵr����Ԫ������Ŀ���
	int getT(string r);//��ȡ��ϵr��Ԫ����
	int getV(string r, string a);//��ȡ��ϵr������a��ֵͬ����Ŀ
	vector<string> getAttribute(string tableName);//��ȡtableName�����е�����
	bool hasIndex(string tablename, string attribute);//�ж��Ƿ�ӵ������
	void printError(int rc);//���������Ϣ
	void useDB(string DB_Name);//ʹ�õ����ݿⷢ���ı�
	void turnPnode2Exec(PhyPlanNode* root);//������ƻ������ڵ���д���

	long long int calConnect(vector<ConnectorNode*>& connect);//����������������,���ӷ�ʽ��vector˳�����
	bool preCheck();//Ԥ�жϣ����ж��Ƿ���ѡ�����ݿ�
public:
	string DB_Name;//��ǰ��ʹ�õ����ݿ���
};