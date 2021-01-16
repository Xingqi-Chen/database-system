#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "SqlGrammer.h"
#include "Translator.h"
#include "PhysicalPlan.h"
#include <algorithm>

using namespace std;

namespace M_DML {

	class Query;
	class Node
	{
	public:

		virtual void showInfo() = 0;
		GrammerNode* transform2Grammer();//将Node转换为语法树节点
		int type;
	};

	class Name :public Node {
		//名字
	public:
		string attrName;//名字
		string alias = "";//别名
		string tableName = "";//所属表名
		bool isDistinct = false;//是否定义distinct
		string aggFunc = "";//聚集函数名
		void showInfo() {}
	};

	class Attribute :public Node {
		//属性
	public:
		string attrName;//属性名
		string alias = "";//别名
		string tableName = "";//所属表名
		bool isDistinct = false;//是否定义distinct
		string aggFunc = "";//是否被聚集函数所作用
		void setName(string attrName, string tableName);
		void setName(string name);//name既可能为a.b也可能为b形式
		void setName(M_DML::Name* name);
		void showInfo();
		string getAttributes();//获取字符串形式的属性信息
	};

	class Number :public M_DML::Node {
		//数值
	public:
		string number;//数值字符串
		void showInfo();
	};

	class ParaString :public M_DML::Node {
		//字符串参数
	public:
		string parameter;
		void showInfo();
	};

	class OrderNode :public M_DML::Node {
		//orderList内的节点
	public:
		M_DML::Attribute attr;
		string rule = "asc";//排序规则，默认为asc
		void showInfo();
	};

	class Relation :public M_DML::Node {
		//关系(表/视图...)
	public:
		string relationName;//关系名
		string alias = "";//别名
		int type;//类型-表/视图...
		void showInfo();
	};

	class Operator :public M_DML::Node {
		//操作符
	public:
		string opName;//操作名:==/and...
		void showInfo();
	};

	class SelList :public M_DML::Node {
	private:
		vector<M_DML::Attribute*> selList;
	public:
		void addAttribute(M_DML::Attribute* attr);
		void showInfo();
		GrammerNode* transform2Grammer();
	};

	class FromList :public M_DML::Node {
	private:
		vector<M_DML::Relation*> fromList;//存放relation与query(子查询)
		vector<M_DML::Query*> queryList;
	public:
		void addNode(M_DML::Relation* node);
		void addNode(M_DML::Query* node);
		void showInfo();
		GrammerNode* transform2Grammer();
	};


	class Condition :public M_DML::Node {
		//即whereList

	public:
		M_DML::Attribute* Lattr;//操作符左侧
		M_DML::Operator* soperator;//操作符
		M_DML::Attribute* Rattr;//操作符右侧

		M_DML::Condition* lCnode;
		M_DML::Condition* rCnode;

		M_DML::Number* rNumber;//可能为数字
		M_DML::ParaString* pString;//可能为字符串

		M_DML::Query* query;//子查询

		void showInfo();

		GrammerNode* transform2Grammer();
		string getInfo();//获取无子节点的condition字符串信息
		string getLoopInfo();//循环获取condition的全部数据并以字符串形式返回
		string setGrammerVec(vector<string>& infos, int count, int leafCount);//用后根遍历的方式填充容器
		int getCount();//获取节点数目

		vector<M_DML::Condition*>* getSubQueryCondition();//获取拥有子查询的condition结点

	};

	class OrderList :public M_DML::Node {
	private:
		vector<M_DML::OrderNode*> orderList;
	public:
		void addOrderNode(M_DML::OrderNode* ornode);
		void showInfo();
		GrammerNode* transform2Grammer();
	};

	class GroupList :public M_DML::Node {
	private:
		vector<M_DML::Attribute*> groupList;
	public:
		void addAttribute(M_DML::Attribute* attr);
		GrammerNode* transform2Grammer();
	};

	class Query :public M_DML::Node {
	public:
		M_DML::SelList* selList;
		M_DML::FromList* fromList;
		M_DML::Condition* condition = nullptr;
		M_DML::OrderList* orderList = nullptr;
		M_DML::GroupList* groupList = nullptr;
		void showInfo();
		GrammerNode* transform2Grammer();

	private:
		GrammerNode* transform2GrammerWithSubQuery(vector<M_DML::Condition*>* conditionWithSub);//condition内含有子查询的转换
		GrammerNode* transform2GrammerWithSimple();//condition为简单条件
		GrammerNode* solveConnect(GrammerNode* root);//将condition中的a.b=c.e调整到connector处
		void turnCondition2Connect(GrammerNode* sroot, string condition);//将condition内的条件转移至对应的connector下

	};

	class Insert :public M_DML::Node {
	public:
		string tableName;//插入的表名
		vector<string> attributes;//具体的值信息
	public:
		void showInfo();
		GrammerNode* transform2Grammer();
	};

	class Delete :public M_DML::Node {
	public:
		string tableName;//删除的表名
		M_DML::Condition* condition;//所删除的表名需要满足的条件
	public:
		void showInfo();
		GrammerNode* transform2Grammer();
	};

	class Update :public M_DML::Node {
	public:
		string tableName;//更新的表名
		map<string, string> attr_indexs;//存储属性名-具体值
		M_DML::Condition* condition;//更新的表需要满足的条件
	public:
		void showInfo();
		GrammerNode* transform2Grammer();
	};

}



class NodeStorage {
public:
	//查询
	M_DML::Attribute *attribute;
	M_DML::OrderNode *orderNode;
	M_DML::Relation *relation;
	M_DML::Operator *soperator;
	M_DML::SelList	*selList;
	M_DML::FromList *fromList;
	M_DML::Condition *condision;
	M_DML::OrderList *orderList;
	M_DML::GroupList *groupList;
	M_DML::Query *query;
	M_DML::Number* rNumber;
	M_DML::ParaString* pString;

	M_DML::Name* name;
	//暂存name_node信息
	string text;
	//存储字段信息
	vector<M_DML::Name*> nameList;
	int type;
	
	//插入
	M_DML::Insert* insert;
	vector<string> values;//插入值

	//删除
	M_DML::Delete* del;

	//更新
	M_DML::Update* upd;
	string attr_index[2];//键值对
	map<string, string> attr_indexs;

	//最终的物理计划树
	PhyPlanNode* phyNode;//物理计划树节点
	vector<PhyPlanNode*> phyNodes;//物理计划树节点容器
};