#ifndef PROCESSFUNC_H
#define PROCESSFUNC_H

#include "StateNode.h"
#include "Execute_Global.h"
#include "../sql/ddl.h"


// buildPlanStateTree调用，用于深搜生成相似树
void dfs_buildPlanStateTree(PhyPlanNode* ppn_now, PlanStateNode* psn_now);

// 根据物理计划树生成计划状态树
PlanStateNode* buildPlanStateTree(PhyPlanNode* ppn, GlobalState* gstate);

// 根据类型生成对应的节点
PlanStateNode* returnPlanStateNode(PhyPlanNode* ppn, GlobalState* gstate);

//  JoinPlanStateNode::Run()调用，用于深搜重置遍历节点的迭代器
void dfs_initScanStateNode(PlanStateNode* psn_now);

// 将参数中的聚集函数转换为聚集函数节点
void aggregateBuild(PlanStateNode* psn);

// 判断聚集类型，及参数
void aggregateType(string s, NodeType &type, string &attrName);

// 待修改
// 判断记录是否满足条件
bool isProper(Record* record1, Record* record2, vector<string> paramters, vector<string> additions, GlobalState* gstate); // 两条记录判断

// 解析涉及表和属性
void constraintResolution(string s, vector<string> &tablesname, vector<string> &attributes, vector<string> values);
// 解析输出条件
void constraintOutputResolution(string s, string &tablename, string &attribute);
// 解析约束条件
void constraintResolution(PlanStateNode* psn, vector<Resolution> &resolutions, vector<Operator> &operators);
// 解析 attrname = value 表达式
void constraintEqual(PlanStateNode* psn, string s, AttrcatRecord &attrinfo, Value &value);

// 输出树结构
void dfs_show(PlanStateNode* psn_now);

// 输出所有的属性
void Attr_Show(PlanStateNode* psn, Record* record);

// 输出一个行
void Record_Show(PlanStateNode* psn, Record* record);

// 运算符转换，字符串 -> CompOp
void getRelatedOperator(string op, CompOp &compOp);

// 值转换，字符串 -> Value
void getRelatedValue(string val, Value &value, AttrcatRecord attrinfo);

// 逻辑运算符转换，字符串 -> Operator
void getRelatedLogicalOperator(string op, Operator& oper);

// 判断记录是否满足条件
bool recordSatisfied(Record* record_, vector<Resolution> &resolutions, vector<Operator> operators, GlobalState* gstate, string tablename);

// 判断记录是否满足条件
bool isSatisfied(RM_Record* record, Resolution resolutions, GlobalState* gstate, string tablename);

// 逻辑运算
bool logicalOperate(bool n1, bool n2, Operator op);

// 获取给定属性在表中为第几个属性
int getRelatedAttrNo(DDL_Manager* manager_file, IX_Manager* manager_idx, string tablename, string attrname);

// 确定索引扫描的边界
void constraintBorder(vector<Resolution> resolutions, string indexname, string &lv, string &rv);

// 输出时，列的宽度
int getColSize(int &len, char* data, AttrcatRecord attrInfo);

#endif // !PROCESSFUNC_H

