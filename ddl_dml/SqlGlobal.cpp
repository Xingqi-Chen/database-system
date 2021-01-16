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
	string index = DB_Name + "/" + r + "/" + a;//map的key
	if (vmap.find(index) != vmap.end()) {
		//说明已查询过V值，则直接返回即可
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
	vmap.insert(pair<string, int>(index, v));//插入map
	return v;
}


vector<string> SqlGlobal::getAttribute(string tableName)
{
	vector<string> attributes;
#ifdef DML_TEST
	if (tableName == "R") {
		//测试1数据
		attributes.push_back("b");
	}
	else if (tableName == "S") {
		//测试2数据
		attributes.push_back("b");
		attributes.push_back("c");
	}
	else if (tableName == "student") {
		attributes.push_back("age");
	}
	else {
		//其他测试数据
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
	cout << "错误码：" << rc << endl;
}

void SqlGlobal::useDB(string DB_Name)
{
	//调用接口函数....
#ifndef DML_TEST
	ddl_mgr->openDb(DB_Name.c_str());
#endif

	this->DB_Name = DB_Name;
	cout << "Database changed" << endl;
}

void SqlGlobal::turnPnode2Exec(PhyPlanNode* root)
{
	int errCode = 0;//errCode为接口函数返回值
#ifndef DML_TEST
	//调用接口函数
	// 编译执行模块基础变量
	Executor* executor = new Executor();

	// 调用时，按照start、run、end的顺序进行调用
	// start调用时，传入物理计划根节点，以及上面定义的一些存储接口，
	executor->ExecutorStart(root, rmManager, ddl_mgr, ixManager, dml_mgr); // ①
	// run、end调用时，直接调用就可以

	// 测试函数
	// 测试转换后树的结构
	PlanStateNode* psn = executor->getRoot(); // 转换后树的根节点，调用式右可以获得
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
	vector<long long int> costs;//统计代价
	long long int size = cnode->T;//连接大小
	for (int m = 1;m < connect.size();m++) {
		ConnectorNode* nenode = connect.at(m);//下一个node,此node与cnode进行比较
		size *= nenode->T;
		map<string, int>::iterator iter = cnode->Vs.begin();
		int divisor = 1;//除数
		for (;iter != cnode->Vs.end();iter++) {
			//计算除数
			string attrName = iter->first;//元素名
			if (nenode->Vs.count(attrName)) {
				//nenode同样存在此属性
				divisor *= max(nenode->Vs[attrName], cnode->Vs[attrName]);//得到较大值
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
