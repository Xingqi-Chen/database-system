#include "SqlGlobal.h"

SqlGlobal* SqlGlobal::instance = nullptr;
SqlGlobal* SqlGlobal::getInstance()
{
	if (instance == nullptr)
		instance = new SqlGlobal();
	return instance;
}

int SqlGlobal::getB(string r)
{
#ifdef DML_TEST
	return getRandom(60);
#else
	int B;
	ddl_mgr->getRelBlockNum(r, B);
	return B;
#endif
}

int SqlGlobal::getT(string r)
{
#ifdef DML_TEST
	if (r == "R")
		return 1000;
	else if (r == "S")
		return 2000;
	else if (r == "U")
		return 5000;
	return getRandom(10000);
#else
	int T;
	ddl_mgr->getRelTupleNum(r, T);
	return T;
#endif
}

int SqlGlobal::getV(string r, string a)
{
	string index = DB_Name + "/" + r + "/" + a;//map��key
	if (vmap.find(index) != vmap.end()) {
		//˵���Ѳ�ѯ��Vֵ����ֱ�ӷ��ؼ���
		return vmap[index];
	}
	int v;
#ifdef DML_TEST
	if (r == "R" && a == "b")
		v = 20;
	else if (r == "S" && a == "b")
		v = 50;
	else if (r == "S" && a == "c")
		v = 100;
	else if (r == "U" && a == "c")
		v = 500;
	else
		v = getRandom(7000);
#else
	ddl_mgr->getAttrDiffNum(r, a, v);
#endif
	vmap.insert(pair<string, int>(index, v));//����map
	return v;
}


vector<string> SqlGlobal::getAttribute(string tableName)
{
	vector<string> attributes;
#ifdef DML_TEST
	if (tableName == "R") {
		//����1����
		attributes.push_back("b");
	}
	else if (tableName == "S") {
		//����2����
		attributes.push_back("b");
		attributes.push_back("c");
	}
	else if (tableName == "student") {
		attributes.push_back("age");
	}
	else {
		//������������
		attributes.push_back("d");
	}
#else
	ddl_mgr->getAttributes(tableName, attributes);
#endif
	return attributes;
}

bool SqlGlobal::hasIndex(string tablename, string attribute)
{
#ifdef DML_TEST
	if (tablename == "A" && attribute == "b")
		return true;
	else if (tablename == "A" && attribute == "c")
		return true;
	else
	    return false;
#else
    /*tablename = "student";
    attribute = "id";*/
    cout<<tablename<<" "<<attribute<<endl;
    int result = ddl_mgr->indexExists(tablename.c_str(),attribute.c_str());
    cout<<"index:";
    cout<<result<<endl;
    if(result == 0)
        return true;
    else
        return false;
#endif
}

void SqlGlobal::printError(int rc)
{
	cout << "�����룺" << rc << endl;
}

void SqlGlobal::useDB(string DB_Name)
{
	//���ýӿں���....
#ifndef DML_TEST
	ddl_mgr->openDb(DB_Name.c_str());
#endif

	this->DB_Name = DB_Name;
	cout << "Database changed" << endl;
}

void SqlGlobal::turnPnode2Exec(PhyPlanNode* root)
{
	int errCode = 0;//errCodeΪ�ӿں�������ֵ
#ifndef DML_TEST
	//���ýӿں���
	// ����ִ��ģ���������
	Executor* executor = new Executor();

	// ����ʱ������start��run��end��˳����е���
	// start����ʱ����������ƻ����ڵ㣬�Լ����涨���һЩ�洢�ӿڣ�
	executor->ExecutorStart(root, rmManager, ddl_mgr, ixManager, dml_mgr); // ��
	// run��end����ʱ��ֱ�ӵ��þͿ���

	// ���Ժ���
	// ����ת�������Ľṹ
	PlanStateNode* psn = executor->getRoot(); // ת�������ĸ��ڵ㣬����ʽ�ҿ��Ի��
	dfs_show(psn);

	executor->ExecutorRun();
	executor->ExecutorEnd();
	delete executor;
#endif
	printError(errCode);
}

long long int SqlGlobal::calConnect(vector<ConnectorNode*>& connect)
{
	ConnectorNode* cnode = connect.front();
	vector<long long int> costs;//ͳ�ƴ���
	long long int size = cnode->T;//���Ӵ�С
	for (int m = 1;m < connect.size();m++) {
		ConnectorNode* nenode = connect.at(m);//��һ��node,��node��cnode���бȽ�
		size *= nenode->T;
		map<string, int>::iterator iter = cnode->Vs.begin();
		int divisor = 1;//����
		for (;iter != cnode->Vs.end();iter++) {
			//�������
			string attrName = iter->first;//Ԫ����
			if (nenode->Vs.count(attrName)) {
				//nenodeͬ�����ڴ�����
				divisor *= max(nenode->Vs[attrName], cnode->Vs[attrName]);//�õ��ϴ�ֵ
			}
		}
		size /= divisor;
		costs.push_back(size);
		cnode = nenode;
	}

	long long int result = 0;
	for (int m = 0;m < costs.size() - 1;m++) {
		result += costs.at(m);
	}
	return result;
}

bool SqlGlobal::preCheck()
{
	if (DB_Name == "") {
		cout << "No database selected" << endl;
		return false;
	}
	return true;
}

int SqlGlobal::getRandom(int min)
{
	srand((unsigned)time(NULL));
	return min + int(rand());
}

SqlGlobal::SqlGlobal() {
	//ddl_mgr
#ifndef DML_TEST
	pfManager = new PF_Manager();
	rmManager = new RM_Manager(*pfManager);
	ixManager = new IX_Manager(*pfManager);
	ddl_mgr = new DDL_Manager(*rmManager, *ixManager);
	dml_mgr = new DML_Manager(*rmManager, *ddl_mgr, *ixManager);
#endif
}
