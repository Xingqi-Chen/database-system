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

// 计划状态节点类型type枚举
enum NodeType {
    NOTYPE=0, // 不是任何其他类型
	INSERT=1,DELETE,SELECT,UPDATE, // 增删查改 对应的节点类型数字为1，2，3，4
	SCAN=11,SEQSCAN,INDEXSCAN, // 顺序遍历、索引遍历 对应的节点类型数字为11、12
	FILTER=21,SUM,MAX,MIN,MEAN, // 过滤、求和、最大、最小，平均值 对应节点类型数字为21、22、23、24、25
	JOIN=41, // 连接 对应节点类型数字为41
};

//// 临时类型
/*class PhyPlanNode {
public:
	PhyPlanNode* left;
	PhyPlanNode* right;
};*/

// TO DO
// 传递查询内容的全局状态
class GlobalState {
private:
	Record* record; // 当前处理到的记录
public:
	RM_Manager* manager; // 统一管理所有的文件接口
	DDL_Manager* manager_ddl; // 统一管理所有系统表的文件接口
	IX_Manager* manager_idx; // 统一管理所有索引的文件接口
	DML_Manager* manager_dml; // 用于插入的文件接口
public:
	GlobalState(RM_Manager* rmm, DDL_Manager* ddlm, IX_Manager* idxm, DML_Manager* dmlm);
	void setRecord(Record* record) { this->record = record; };
	Record* getRecord(void) { return this->record; };
	void show(); // 格式化输出当前记录
	void show_0(Record* record); // 输出类型1的记录
};

// TO DO
// 计划状态节点，物理计划节点的映射节点，保存了当前已经查询的内容
class PlanStateNode {
private:
	vector<string> parameters; // 参数（这里表示属性名称）
	vector<string> additions; // 附加内容（这里表示参数对应的值）

public:
	int type; // 节点的类型
	GlobalState *gstate; // 全局状态，一颗计划状态树对应一个全局状态
	PlanStateNode* left;
	PlanStateNode* right;
	bool firstFlag; // 第一次访问该节点的标记，如未访问过，值为1

public:
	PlanStateNode(GlobalState* gstate, int type);
	vector<string>& getParameters() { return this->parameters; };
	vector<string>& getAdditions() { return this->additions; };
	void addParameters(vector<string> parameters);
	void addAdditions(vector<string> additions);

	// 根据物理计划节点初始化计划状态节点
	void init(PhyPlanNode* ppn, PlanStateNode* left, PlanStateNode* right); 
	// 运行函数，每一种节点对应了他的运行方式
	virtual void Run() = 0;
	// 格式化输出函数
	virtual void show() = 0;
    // 重置初次访问标记
    void resetFirstFlag() { this->firstFlag = true; };
    // 获取属性对应的记录值
    void getDoubleValue(Record *record,double &value, AttrcatRecord attrinfo);
};

// 控制节点，作为根节点进行具体的控制
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

// 遍历节点，用于遍历相关的表
class ScanPlanStateNode :public PlanStateNode {
private:
public:
    vector<Resolution> resolutions; // 解析结果
    vector<Operator> operators; // 逻辑运算符

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

// 物化节点，用于特殊的处理
class MeterializationPlanStateNode :public PlanStateNode {
private:
public:
    vector<AttrcatRecord> attrInfos; // 涉及的属性
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

// 连接节点，用于连接对应的记录
class JoinPlanStateNode :public PlanStateNode {
private:
	Record* record_left;
	Record* record_right;
	bool first_flag; // 用于标记第一次该节点（first_flag == true）
public:
	JoinPlanStateNode(GlobalState* gstate);
	virtual void Run();
	virtual void show();
};

#endif // !STATENODE_H
