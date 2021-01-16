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

//#define DML_TEST  //测试阶段则define
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
	map<string, int> vmap;//<数据库名/表名/属性名,V值>

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
	int getRandom(int min);//获取>min的随机数
public:
	//以下函数均待调用接口函数
	int getB(string r);//获取容纳关系r所有元组所需的块数
	int getT(string r);//获取关系r的元组数
	int getV(string r, string a);//获取关系r中属性a不同值的数目
	vector<string> getAttribute(string tableName);//获取tableName所具有的属性
	bool hasIndex(string tablename, string attribute);//判断是否拥有索引
	void printError(int rc);//输出错误信息
	void useDB(string DB_Name);//使用的数据库发生改变
	void turnPnode2Exec(PhyPlanNode* root);//将物理计划树根节点进行传递

	long long int calConnect(vector<ConnectorNode*>& connect);//计算表连接所需代价,连接方式按vector顺序进行
	bool preCheck();//预判断，如判断是否已选择数据库
public:
	string DB_Name;//当前所使用的数据库名
};