#ifndef STATENODE_H
#define STATENODE_H

#include <vector>
#include <string>
#include <cfloat>
#include "Execute_extend.h"
#include "Execute_Global.h"
#include "../storage/ix.h"
#include "../storage/rm.h"
#include "../sql/ddl.h"
#include "../sql/dml.h"
#include "../ddl_dml/PhysicalPlan.h"
using namespace std;

// �ƻ�״̬�ڵ�����typeö��
enum NodeType {
    NOTYPE=0, // �����κ���������
	INSERT=1,DELETE,SELECT,UPDATE, // ��ɾ��� ��Ӧ�Ľڵ���������Ϊ1��2��3��4
	SCAN=11,SEQSCAN,INDEXSCAN, // ˳��������������� ��Ӧ�Ľڵ���������Ϊ11��12
	FILTER=21,SUM,MAX,MIN,MEAN, // ���ˡ���͡������С��ƽ��ֵ ��Ӧ�ڵ���������Ϊ21��22��23��24��25
	JOIN=41, // ���� ��Ӧ�ڵ���������Ϊ41
};

//// ��ʱ����
/*class PhyPlanNode {
public:
	PhyPlanNode* left;
	PhyPlanNode* right;
};*/

// TO DO
// ���ݲ�ѯ���ݵ�ȫ��״̬
class GlobalState {
private:
	Record* record; // ��ǰ�����ļ�¼
public:
	RM_Manager* manager; // ͳһ�������е��ļ��ӿ�
	DDL_Manager* manager_ddl; // ͳһ��������ϵͳ����ļ��ӿ�
	IX_Manager* manager_idx; // ͳһ���������������ļ��ӿ�
	DML_Manager* manager_dml; // ���ڲ�����ļ��ӿ�
public:
	GlobalState(RM_Manager* rmm, DDL_Manager* ddlm, IX_Manager* idxm, DML_Manager* dmlm);
	void setRecord(Record* record) { this->record = record; };
	Record* getRecord(void) { return this->record; };
	void show(); // ��ʽ�������ǰ��¼
	void show_0(Record* record); // �������1�ļ�¼
};

// TO DO
// �ƻ�״̬�ڵ㣬����ƻ��ڵ��ӳ��ڵ㣬�����˵�ǰ�Ѿ���ѯ������
class PlanStateNode {
private:
	vector<string> parameters; // �����������ʾ�������ƣ�
	vector<string> additions; // �������ݣ������ʾ������Ӧ��ֵ��

public:
	int type; // �ڵ������
	GlobalState *gstate; // ȫ��״̬��һ�żƻ�״̬����Ӧһ��ȫ��״̬
	PlanStateNode* left;
	PlanStateNode* right;
	bool firstFlag; // ��һ�η��ʸýڵ�ı�ǣ���δ���ʹ���ֵΪ1

public:
	PlanStateNode(GlobalState* gstate, int type);
	vector<string>& getParameters() { return this->parameters; };
	vector<string>& getAdditions() { return this->additions; };
	void addParameters(vector<string> parameters);
	void addAdditions(vector<string> additions);

	// ��������ƻ��ڵ��ʼ���ƻ�״̬�ڵ�
	void init(PhyPlanNode* ppn, PlanStateNode* left, PlanStateNode* right); 
	// ���к�����ÿһ�ֽڵ��Ӧ���������з�ʽ
	virtual void Run() = 0;
	// ��ʽ���������
	virtual void show() = 0;
    // ���ó��η��ʱ��
    void resetFirstFlag() { this->firstFlag = true; };
    // ��ȡ���Զ�Ӧ�ļ�¼ֵ
    void getDoubleValue(Record *record,double &value, AttrcatRecord attrinfo);
};

// ���ƽڵ㣬��Ϊ���ڵ���о���Ŀ���
class ControlPlanStateNode :public PlanStateNode {
private:

public:
	ControlPlanStateNode(GlobalState* gstate, int type) :PlanStateNode(gstate, type) {};
	virtual void Run() = 0;
	virtual void show() = 0;
};

class InsertPlanStateNode :public ControlPlanStateNode {
private:

public:
	InsertPlanStateNode(GlobalState* gstate) :ControlPlanStateNode(gstate, INSERT) {};
	virtual void Run();
	virtual void show();
};

class DeletePlanStateNode :public ControlPlanStateNode {
private:

public:
	DeletePlanStateNode(GlobalState* gstate) :ControlPlanStateNode(gstate, DELETE) {};
	virtual void Run();
	virtual void show();
};

class SelectPlanStateNode :public ControlPlanStateNode {
private:
public:
	SelectPlanStateNode(GlobalState* gstate) :ControlPlanStateNode(gstate, SELECT) {};
	virtual void Run();
	virtual void show();
};

class UpdatePlanStateNode :public ControlPlanStateNode {
private:

public:
	UpdatePlanStateNode(GlobalState* gstate) :ControlPlanStateNode(gstate, UPDATE) {};
	virtual void Run();
	virtual void show();
};

// �����ڵ㣬���ڱ�����صı�
class ScanPlanStateNode :public PlanStateNode {
private:
public:
    vector<Resolution> resolutions; // �������
    vector<Operator> operators; // �߼������

	ScanPlanStateNode(GlobalState* gstate, int type) :PlanStateNode(gstate, type) {};
	virtual void Run() = 0;
	virtual void show() = 0;
};

class SeqScanPlanStateNode :public ScanPlanStateNode {
private:
	RM_FileScan* scan;
public:
	SeqScanPlanStateNode(GlobalState* gstate) :ScanPlanStateNode(gstate, SEQSCAN) {};
	void scanInit(RM_FileScan* scan);
	virtual void Run();
	virtual void show();
};

class IndexScanPlanStateNode :public ScanPlanStateNode {
private: 
	IX_IndexScan* scan;
public:
	IndexScanPlanStateNode(GlobalState* gstate) :ScanPlanStateNode(gstate, INDEXSCAN) {};
	void scanInit(IX_IndexScan* scan) { this->scan = scan; };
	virtual void Run();
	virtual void show();
};

// �ﻯ�ڵ㣬��������Ĵ���
class MeterializationPlanStateNode :public PlanStateNode {
private:
public:
    vector<AttrcatRecord> attrInfos; // �漰������
public:
	MeterializationPlanStateNode(GlobalState* gstate, int type) :PlanStateNode(gstate, type) {};
    vector<double> MerializationRun();
	virtual void Run() = 0;
	virtual void show() = 0;
	virtual void init(int size) = 0;
};

class FilterPlanStateNode :public MeterializationPlanStateNode {
private:
public:
	FilterPlanStateNode(GlobalState* gstate) :MeterializationPlanStateNode(gstate, FILTER) {};
	virtual void Run();
	virtual void show();
    virtual void init(int size){};
};

class SumPlanStateNode :public MeterializationPlanStateNode {
private:
	vector<double> temSums;
public:
	SumPlanStateNode(GlobalState* gstate) :MeterializationPlanStateNode(gstate, SUM) {};
	virtual void Run();
	virtual void show();
	virtual void init(int size){this->temSums = vector<double>(size,0);};
};

class MaxPlanStateNode :public MeterializationPlanStateNode {
private:
	vector<double> temMaxs;
public:
	MaxPlanStateNode(GlobalState* gstate) :MeterializationPlanStateNode(gstate, MAX) {};
	virtual void Run();
	virtual void show();
    virtual void init(int size){this->temMaxs = vector<double>(size,DBL_MIN);};
};

class MinPlanStateNode :public MeterializationPlanStateNode {
private:
	vector<double> temMins;
public:
	MinPlanStateNode(GlobalState* gstate) :MeterializationPlanStateNode(gstate, MIN) {};
	virtual void Run();
	virtual void show();
    virtual void init(int size){this->temMins = vector<double>(size,DBL_MAX);};
};

class MeanPlanStateNode :public MeterializationPlanStateNode {
private:
	vector<double> temSums;
	long long size;
public:
	MeanPlanStateNode(GlobalState* gstate) :MeterializationPlanStateNode(gstate, MEAN) { this->size = 0; };
	virtual void Run();
	virtual void show();
    virtual void init(int size){this->temSums = vector<double>(size,0);};
};

// ���ӽڵ㣬�������Ӷ�Ӧ�ļ�¼
class JoinPlanStateNode :public PlanStateNode {
private:
	Record* record_left;
	Record* record_right;
	bool first_flag; // ���ڱ�ǵ�һ�θýڵ㣨first_flag == true��
public:
	JoinPlanStateNode(GlobalState* gstate);
	virtual void Run();
	virtual void show();
};

#endif // !STATENODE_H
