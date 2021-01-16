#ifndef PROCESSFUNC_H
#define PROCESSFUNC_H

#include "StateNode.h"
#include "Execute_Global.h"
#include "../sql/ddl.h"


// buildPlanStateTree���ã�������������������
void dfs_buildPlanStateTree(PhyPlanNode* ppn_now, PlanStateNode* psn_now);

// ��������ƻ������ɼƻ�״̬��
PlanStateNode* buildPlanStateTree(PhyPlanNode* ppn, GlobalState* gstate);

// �����������ɶ�Ӧ�Ľڵ�
PlanStateNode* returnPlanStateNode(PhyPlanNode* ppn, GlobalState* gstate);

//  JoinPlanStateNode::Run()���ã������������ñ����ڵ�ĵ�����
void dfs_initScanStateNode(PlanStateNode* psn_now);

// �������еľۼ�����ת��Ϊ�ۼ������ڵ�
void aggregateBuild(PlanStateNode* psn);

// �жϾۼ����ͣ�������
void aggregateType(string s, NodeType &type, string &attrName);

// ���޸�
// �жϼ�¼�Ƿ���������
bool isProper(Record* record1, Record* record2, vector<string> paramters, vector<string> additions, GlobalState* gstate); // ������¼�ж�

// �����漰�������
void constraintResolution(string s, vector<string> &tablesname, vector<string> &attributes, vector<string> values);
// �����������
void constraintOutputResolution(string s, string &tablename, string &attribute);
// ����Լ������
void constraintResolution(PlanStateNode* psn, vector<Resolution> &resolutions, vector<Operator> &operators);
// ���� attrname = value ���ʽ
void constraintEqual(PlanStateNode* psn, string s, AttrcatRecord &attrinfo, Value &value);

// ������ṹ
void dfs_show(PlanStateNode* psn_now);

// ������е�����
void Attr_Show(PlanStateNode* psn, Record* record);

// ���һ����
void Record_Show(PlanStateNode* psn, Record* record);

// �����ת�����ַ��� -> CompOp
void getRelatedOperator(string op, CompOp &compOp);

// ֵת�����ַ��� -> Value
void getRelatedValue(string val, Value &value, AttrcatRecord attrinfo);

// �߼������ת�����ַ��� -> Operator
void getRelatedLogicalOperator(string op, Operator& oper);

// �жϼ�¼�Ƿ���������
bool recordSatisfied(Record* record_, vector<Resolution> &resolutions, vector<Operator> operators, GlobalState* gstate, string tablename);

// �жϼ�¼�Ƿ���������
bool isSatisfied(RM_Record* record, Resolution resolutions, GlobalState* gstate, string tablename);

// �߼�����
bool logicalOperate(bool n1, bool n2, Operator op);

// ��ȡ���������ڱ���Ϊ�ڼ�������
int getRelatedAttrNo(DDL_Manager* manager_file, IX_Manager* manager_idx, string tablename, string attrname);

// ȷ������ɨ��ı߽�
void constraintBorder(vector<Resolution> resolutions, string indexname, string &lv, string &rv);

// ���ʱ���еĿ��
int getColSize(int &len, char* data, AttrcatRecord attrInfo);

#endif // !PROCESSFUNC_H

