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
		GrammerNode* transform2Grammer();//��Nodeת��Ϊ�﷨���ڵ�
		int type;
	};

	class Name :public Node {
		//����
	public:
		string attrName;//����
		string alias = "";//����
		string tableName = "";//��������
		bool isDistinct = false;//�Ƿ���distinct
		string aggFunc = "";//�ۼ�������
		void showInfo() {}
	};

	class Attribute :public Node {
		//����
	public:
		string attrName;//������
		string alias = "";//����
		string tableName = "";//��������
		bool isDistinct = false;//�Ƿ���distinct
		string aggFunc = "";//�Ƿ񱻾ۼ�����������
		void setName(string attrName, string tableName);
		void setName(string name);//name�ȿ���Ϊa.bҲ����Ϊb��ʽ
		void setName(M_DML::Name* name);
		void showInfo();
		string getAttributes();//��ȡ�ַ�����ʽ��������Ϣ
	};

	class Number :public M_DML::Node {
		//��ֵ
	public:
		string number;//��ֵ�ַ���
		void showInfo();
	};

	class ParaString :public M_DML::Node {
		//�ַ�������
	public:
		string parameter;
		void showInfo();
	};

	class OrderNode :public M_DML::Node {
		//orderList�ڵĽڵ�
	public:
		M_DML::Attribute attr;
		string rule = "asc";//�������Ĭ��Ϊasc
		void showInfo();
	};

	class Relation :public M_DML::Node {
		//��ϵ(��/��ͼ...)
	public:
		string relationName;//��ϵ��
		string alias = "";//����
		int type;//����-��/��ͼ...
		void showInfo();
	};

	class Operator :public M_DML::Node {
		//������
	public:
		string opName;//������:==/and...
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
		vector<M_DML::Relation*> fromList;//���relation��query(�Ӳ�ѯ)
		vector<M_DML::Query*> queryList;
	public:
		void addNode(M_DML::Relation* node);
		void addNode(M_DML::Query* node);
		void showInfo();
		GrammerNode* transform2Grammer();
	};


	class Condition :public M_DML::Node {
		//��whereList

	public:
		M_DML::Attribute* Lattr;//���������
		M_DML::Operator* soperator;//������
		M_DML::Attribute* Rattr;//�������Ҳ�

		M_DML::Condition* lCnode;
		M_DML::Condition* rCnode;

		M_DML::Number* rNumber;//����Ϊ����
		M_DML::ParaString* pString;//����Ϊ�ַ���

		M_DML::Query* query;//�Ӳ�ѯ

		void showInfo();

		GrammerNode* transform2Grammer();
		string getInfo();//��ȡ���ӽڵ��condition�ַ�����Ϣ
		string getLoopInfo();//ѭ����ȡcondition��ȫ�����ݲ����ַ�����ʽ����
		string setGrammerVec(vector<string>& infos, int count, int leafCount);//�ú�������ķ�ʽ�������
		int getCount();//��ȡ�ڵ���Ŀ

		vector<M_DML::Condition*>* getSubQueryCondition();//��ȡӵ���Ӳ�ѯ��condition���

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
		GrammerNode* transform2GrammerWithSubQuery(vector<M_DML::Condition*>* conditionWithSub);//condition�ں����Ӳ�ѯ��ת��
		GrammerNode* transform2GrammerWithSimple();//conditionΪ������
		GrammerNode* solveConnect(GrammerNode* root);//��condition�е�a.b=c.e������connector��
		void turnCondition2Connect(GrammerNode* sroot, string condition);//��condition�ڵ�����ת������Ӧ��connector��

	};

	class Insert :public M_DML::Node {
	public:
		string tableName;//����ı���
		vector<string> attributes;//�����ֵ��Ϣ
	public:
		void showInfo();
		GrammerNode* transform2Grammer();
	};

	class Delete :public M_DML::Node {
	public:
		string tableName;//ɾ���ı���
		M_DML::Condition* condition;//��ɾ���ı�����Ҫ���������
	public:
		void showInfo();
		GrammerNode* transform2Grammer();
	};

	class Update :public M_DML::Node {
	public:
		string tableName;//���µı���
		map<string, string> attr_indexs;//�洢������-����ֵ
		M_DML::Condition* condition;//���µı���Ҫ���������
	public:
		void showInfo();
		GrammerNode* transform2Grammer();
	};

}



class NodeStorage {
public:
	//��ѯ
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
	//�ݴ�name_node��Ϣ
	string text;
	//�洢�ֶ���Ϣ
	vector<M_DML::Name*> nameList;
	int type;
	
	//����
	M_DML::Insert* insert;
	vector<string> values;//����ֵ

	//ɾ��
	M_DML::Delete* del;

	//����
	M_DML::Update* upd;
	string attr_index[2];//��ֵ��
	map<string, string> attr_indexs;

	//���յ�����ƻ���
	PhyPlanNode* phyNode;//����ƻ����ڵ�
	vector<PhyPlanNode*> phyNodes;//����ƻ����ڵ�����
};