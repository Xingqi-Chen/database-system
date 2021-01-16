#include <map>
#include <vector>
#include <string>
#include <string.h>
#include "set"
#include "ProcessFunc.h"
#include "StateNode.h"
#include "Execute_extend.h"
#include "Execute_Global.h"
#include "../sql/ddl.h"
using namespace std;

void dfs_buildPlanStateTree(PhyPlanNode* ppn_now, PlanStateNode* psn_now)
{
    // ��Ӳ���
    vector<string> paras = ppn_now->getParameters();
    for (int i = 0 ; i < paras.size() ; ++i)
        psn_now->getParameters().push_back(paras[i]);
    vector<string> adds = ppn_now->getAddition();
    for (int i = 0 ; i < adds.size() ; ++i)
        psn_now->getAdditions().push_back(adds[i]);

	PlanStateNode* left = NULL;
	PlanStateNode* right = NULL;
	if (ppn_now->left != NULL)
		left = returnPlanStateNode(ppn_now->left, psn_now->gstate);
	if (ppn_now->right != NULL)
		right = returnPlanStateNode(ppn_now->right, psn_now->gstate);
	psn_now->init(ppn_now, left, right);
	if (left != NULL)
		dfs_buildPlanStateTree(ppn_now->left, psn_now->left);
	if (right != NULL)
		dfs_buildPlanStateTree(ppn_now->right, psn_now->right);
}

PlanStateNode* buildPlanStateTree(PhyPlanNode* ppn, GlobalState* gstate)
{
	PlanStateNode* root = returnPlanStateNode(ppn, gstate);
	dfs_buildPlanStateTree(ppn, root);

	return root;
}

PlanStateNode * returnPlanStateNode(PhyPlanNode * ppn, GlobalState * gstate)
{
	if (ppn->methodName == "INSERT")
		return new InsertPlanStateNode(gstate);
	else if (ppn->methodName == "DELETE")
		return new DeletePlanStateNode(gstate);
	else if (ppn->methodName == "SELECT")
		return new SelectPlanStateNode(gstate);
	else if (ppn->methodName == "UPDATE")
		return new UpdatePlanStateNode(gstate);
	else if (ppn->methodName == "JOIN")
		return new JoinPlanStateNode(gstate);
	else if (ppn->methodName == "FILTER")
		return new FilterPlanStateNode(gstate);
	else if (ppn->methodName == "INDEXSCAN")
		return new IndexScanPlanStateNode(gstate);
	else if (ppn->methodName == "SEQSCAN")
		return new SeqScanPlanStateNode(gstate);
	else if (ppn->methodName == "SUM")
		return new SumPlanStateNode(gstate);
	else if (ppn->methodName == "MAX")
		return new MaxPlanStateNode(gstate);
	else if (ppn->methodName == "MIN")
		return new MinPlanStateNode(gstate);
	else if (ppn->methodName == "MEAN")
		return new MeanPlanStateNode(gstate);


	return NULL;
}

void dfs_initScanStateNode(PlanStateNode * psn_now)
{
	if (psn_now->type == SEQSCAN || psn_now->type == INDEXSCAN)
	{
		((ScanPlanStateNode*)psn_now)->resetFirstFlag();
        ((ScanPlanStateNode*)psn_now)->resolutions.clear();
        ((ScanPlanStateNode*)psn_now)->operators.clear();
	}
	else
	{
		if (psn_now->left != NULL)
			dfs_initScanStateNode(psn_now->left);
		if (psn_now->right != NULL)
			dfs_initScanStateNode(psn_now->right);
	}
}

void aggregateBuild(PlanStateNode* psn)
{
    // ֻ��select�ڵ���д���
    if (psn->type != SELECT)
        return;

    // ����additions�������Ծۼ�������ؽڵ���д���
    for (int i = 0 ; i < psn->getAdditions().size() ; ++i)
    {
        // ����Ǿۼ�����
        NodeType type;
        string attrName;
        aggregateType(psn->getAdditions()[i], type, attrName);
        if (type != NOTYPE)
        {
            // ɾ��select�еľۼ���������
            for (int j = i ; j < psn->getAdditions().size()-1 ; ++j)
                psn->getAdditions()[j] = psn->getAdditions()[j+1];
            psn->getAdditions().pop_back();

            vector<string> paras;
            vector<string> adds;
            if (type == MAX)
            {
                PlanStateNode* aggNode = new MaxPlanStateNode(psn->gstate);
                aggNode->left = psn->left;
                aggNode->right = psn->right;
                paras.push_back(psn->getParameters()[0]);
                aggNode->addParameters(paras);
                adds.push_back(attrName);
                aggNode->addAdditions(adds);

                psn->left = aggNode;
                psn->right = NULL;
            }
            else if (type == MIN)
            {
                PlanStateNode* aggNode = new MinPlanStateNode(psn->gstate);
                aggNode->left = psn->left;
                aggNode->right = psn->right;
                paras.push_back(psn->getParameters()[0]);
                aggNode->addParameters(paras);
                adds.push_back(attrName);
                aggNode->addAdditions(adds);

                psn->left = aggNode;
                psn->right = NULL;
            }
            else if (type == SUM)
            {
                PlanStateNode* aggNode = new SumPlanStateNode(psn->gstate);
                aggNode->left = psn->left;
                aggNode->right = psn->right;
                paras.push_back(psn->getParameters()[0]);
                aggNode->addParameters(paras);
                adds.push_back(attrName);
                aggNode->addAdditions(adds);

                psn->left = aggNode;
                psn->right = NULL;
            }
            else if (type == MEAN)
            {
                PlanStateNode* aggNode = new MeanPlanStateNode(psn->gstate);
                aggNode->left = psn->left;
                aggNode->right = psn->right;
                paras.push_back(psn->getParameters()[0]);
                aggNode->addParameters(paras);
                adds.push_back(attrName);
                aggNode->addAdditions(adds);

                psn->left = aggNode;
                psn->right = NULL;
            }
        }
    }
}

void aggregateType(string s, NodeType &type, string &attrName)
{
    // ȷ���Ƿ��Ǿۼ�����
    int idx = s.find('(');
    if (idx == s.npos)
    {
        type = NOTYPE;
        return;
    }

    // ��ȡ�ۼ�������������
    // 012345 6-3-2=1
    // max(a)
    string aggName = s.substr(0, idx);
    attrName = s.substr(idx+1, s.size()-aggName.size()-2);
    if (aggName == "max")
        type = MAX;
    else if (aggName == "min")
        type = MIN;
    else if (aggName == "sum")
        type = SUM;
    else if (aggName == "mean")
        type = MEAN;
    else
        type = NOTYPE;
}

bool isProper(Record * record1, Record * record2, vector<string> paramters, vector<string> additions, GlobalState* gstate)
{
	// ���ɱ�������parameters�У����¼��ӳ��
	map<string, Record*> records;
	for (int i = 0; i < paramters.size(); ++i)
	{
		Record* tem_record = NULL;

		if (record1->type == 0)
		{
			if (record1->tablename == paramters[i]) // ���޸�
				tem_record = record1;
		}
		else if (record1->type == 1)
		{
			if (record1->get_record_left()->tablename == paramters[i]) // ���޸�
				tem_record = record1->get_record_left();
			if (record1->get_record_right()->tablename == paramters[i]) // ���޸�
				tem_record = record1->get_record_right();
		}
		if (record2->type == 0)
		{
			if (record2->tablename == paramters[i]) // ���޸�
				tem_record = record2;
		}
		else if (record2->type == 1)
		{
			if (record2->get_record_left()->tablename == paramters[i]) // ���޸�
				tem_record = record2->get_record_left();
			if (record2->get_record_right()->tablename == paramters[i]) // ���޸�
				tem_record = record2->get_record_right();
		}

		records[paramters[i]] = tem_record;
	}

////	cout << "��� ������¼ӳ�� ����" << endl;
//	cout << records.size() << endl;
//	cout << additions[0] << endl;

	// ����Լ������������������һһ�ж��Ƿ�����
	bool flag = true;
	// ��ȡ��¼����
	char* data1;
	record1->record->getData(data1);
	char* data2;
	record2->record->getData(data2);

	for (int i = 0; i < additions.size(); ++i)
    {
		// �������������ɱ��������Եļ���
		vector<string> tablesnames;
		vector<string> attributes;
		vector<string> values;
		constraintResolution(additions[i], tablesnames, attributes, values);

//		for (int i = 0 ; i < tablesnames.size() ; ++i)
//		    cout << tablesnames[i] << " " << attributes[i] << endl;

		// �ж��Ƿ�����
		if (tablesnames.size() == 1) // ֻ�漰һ�ű�
		{
			cout << "���������д���" << endl;
		}
		else // �漰���ű�
		{
			AttrcatRecord attrinfo1;
			gstate->manager_ddl->getAttrInfo(tablesnames[0].c_str(), attributes[0].c_str(), attrinfo1);
			AttrcatRecord attrinfo2;
			gstate->manager_ddl->getAttrInfo(tablesnames[0].c_str(), attributes[0].c_str(), attrinfo2);

			// ������
			// �ж�ֵ�������� 
			if (attrinfo1.attrType != attrinfo2.attrType) // ���Ͳ�ƥ��
			{
				flag = false;
				break;
			}
			if (attrinfo1.attrType == INT && *(int*)(data1 + attrinfo1.offset) != *(int*)(data2 + attrinfo2.offset))
			{
				flag = false;
				break;
			}
			else if (attrinfo1.attrType == FLOAT && *(float*)(data1 + attrinfo1.offset) != *(float*)(data2 + attrinfo2.offset))
			{
				flag = false;
				break;
			}
			else if (attrinfo1.attrType == STRING && strcmp((char*)(data1 + attrinfo1.offset), (char*)(data2 + attrinfo2.offset)) != 0)
			{
				flag = false;
				break;
			}
			else if (attrinfo1.attrType == VARCHAR && strcmp((char*)(data1 + attrinfo1.offset), (char*)(data2 + attrinfo2.offset)) != 0)
			{
				flag = false;
				break;
			}
		}
	}

	return flag;
}

void constraintResolution(string s, vector<string>& tablesname, vector<string>& attributes, vector<string> values)
{
	int off = -1;
	while ((off = s.find(".", off + 1)) != string::npos)
	{
		// ��ñ���
		string tablename;
		for (int j = off - 1; (j >= 0 && s[j] != ' '); --j)
		{
			string tem(1, s[j]);
			tablename = tem.append(tablename);
		}
		tablesname.push_back(tablename);

		// ���������
		string attribute;
		for (int j = off + 1; (j < s.size() && s[j] != ' '); ++j)
		{
			attribute.push_back(s[j]);
		}
		attributes.push_back(attribute);
	}

	// ����зǱ�����
	if (tablesname.size() == 1)
	{
		string value;
		for (int j = s.size() - 1; s[j] != ' '; --j)
		{
			string tem(1, s[j]);
			value = tem.append(value);
		}
		values.push_back(value);
	}
}

void constraintOutputResolution(string s, string &tablename, string &attribute)
{
	int idx = -1;
	for (int i = 0 ; i < s.size() ; ++i)
		if (s[i] == '.')
		{
			idx = i;
			break;
		}
	if (idx == -1)
    {
	    attribute = s;
    }
	else
    {
        tablename = s.substr(0, idx);
        attribute = s.substr(idx + 1, s.size() - 1 - idx);
    }
}

void constraintResolution(PlanStateNode* psn, vector<Resolution>& resolutions, vector<Operator>& operators)
{
	// Ĭ�ϵ�һ��Ϊ����
	vector<string> ss = psn->getAdditions();
	for (int i = 0; i < ss.size(); ++i)
	{
		if (i % 2 == 0) // ���������ʽ���н���
		{
			string s = ss[i];
			Resolution* reso = new Resolution();
			// ������
			int idx1 = 0;
			while (true)
			{
				if (s[idx1] == ' ')
					break;
				idx1++;
			}
			reso->attrName = s.substr(0, idx1);
			// �����
			int idx2 = idx1 + 1;
			while (true)
			{
				if (s[idx2] == ' ')
					break;
				idx2++;
			}
			string op = s.substr(idx1 + 1, idx2 - idx1 - 1);
			getRelatedOperator(op, reso->compOp);
			// ֵ
			string val = s.substr(idx2 + 1, s.size() - idx2 - 1);
			AttrcatRecord attrinfo;
			psn->gstate->manager_ddl->getAttrInfo(psn->getParameters()[0].c_str(), reso->attrName.c_str(), attrinfo); // ��ȡ������Ϣ
			getRelatedValue(val, reso->value, attrinfo);

			resolutions.push_back(*reso);
		}
		else // ���߼���������н���
		{
			string s = ss[i];
			Operator oper;
			getRelatedLogicalOperator(s, oper);

			operators.push_back(oper);
		}
	}
}

void constraintEqual(PlanStateNode* psn, string s, AttrcatRecord &attrinfo, Value &value)
{
    // idx��ʶ�Ⱥŵ��±�
    // 01234��idx=2
    // a = c
    int idx = s.find('=');
    string attrname = string(s.substr(0, idx-1));
    string v = string(s.substr(idx+2, s.size()-idx-2));

    psn->gstate->manager_ddl->getAttrInfo(psn->getParameters()[0].c_str(), attrname.c_str(), attrinfo);
    value.type = attrinfo.attrType;
    if (value.type == INT)
        value.value = (void*)(new int(atoi(v.c_str())));
    else if (value.type == INT)
        value.value = (void*)(new float(atof(v.c_str())));
    else if (value.type == STRING)
        value.value = (void*)(v.substr(1, v.size()-2).c_str());
    else if (value.type == STRING)
        value.value = (void*)(v.substr(1, v.size()-2).c_str());
}

void dfs_show(PlanStateNode * psn_now)
{
	if (psn_now == NULL)
		return;

	dfs_show(psn_now->left);
	dfs_show(psn_now->right);
	psn_now->show();
}

void Attr_Show(PlanStateNode* psn, Record* record)
{
    if (record->type == 0) // û�����ӣ�����ֱ�ӽ������
    {
        for (int i = 0 ; i < psn->getAdditions().size() ; ++i)
        {
            // ������Ҫ�����Щ������
            string relName;
            string attriName;
            constraintOutputResolution(psn->getAdditions()[i], relName, attriName);

            // ��������� additions[i] �����������Ӧ��ǰ��¼���ڵı��򲻿���������
            if (relName != "" && record->tablename != relName)
                continue;

            // ��ȡtablename���е�����������
            relName = record->tablename;
            DDL_Manager* manager = psn->gstate->manager_ddl;
            vector<string> attributes;
            manager->getAttributes(relName, attributes);

            // ��ȡ����
            char *data;
            record->record->getData(data);

            // ˫��ѭ���ж�������������������
            for (int j = 0; j < attributes.size(); ++j)
            {
                // ��ȡ���������Ϣ
                AttrcatRecord attrInfo;
                psn->gstate->manager_ddl->getAttrInfo(relName.c_str(), attributes[j].c_str(), attrInfo);

                // �����¼
                int format_len = attributes[j].size()+relName.size()+1;
                getColSize(format_len, data, attrInfo);
                if (attriName == "*" || attriName == attributes[j])
                {
                    printf("%s.%s  ", relName.c_str(), attributes[j].c_str());
                    // ����հ�
                    for (int k = 0 ; k < format_len-relName.size()-attributes[j].size()-1 ; ++k)
                        cout << " ";
                }
            }
        }
    }
    else if (record->type == 1) // ������ڵ�һ������ͨ��¼�������Ǿۺϼ�¼
    {
        Attr_Show(psn, record->get_record_left());
        Attr_Show(psn, record->get_record_right());
    }
}

void Record_Show(PlanStateNode* psn, Record* record)
{
	if (record->type == 0) // û�����ӣ�����ֱ�ӽ������
	{
        for (int i = 0 ; i < psn->getAdditions().size() ; ++i)
        {
            // ������Ҫ�����Щ������
            string relName;
            string attriName;
            constraintOutputResolution(psn->getAdditions()[i], relName, attriName);

            // ��������� additions[i] �����������Ӧ��ǰ��¼���ڵı��򲻿���������
            if (relName != "" && record->tablename != relName)
                continue;

            // ��ȡtablename���е�����������
            relName = record->tablename;
            DDL_Manager* manager = psn->gstate->manager_ddl;
            vector<string> attributes;
            manager->getAttributes(relName, attributes);

            // ��ȡ����
            char *data;
            record->record->getData(data);

            // ˫��ѭ���ж���������Ӧ����
            for (int j = 0; j < attributes.size(); ++j)
            {
                if (attriName == "*" || attriName == attributes[j])
                {
                    // ��ȡ���������Ϣ
                    AttrcatRecord attrInfo;
                    psn->gstate->manager_ddl->getAttrInfo(relName.c_str(), attributes[j].c_str(), attrInfo);

                    // �����¼
                    char format[20];
                    int format_len = attributes[j].size()+relName.size()+1;
                    getColSize(format_len, data, attrInfo);
                    if (attrInfo.attrType == INT)
                    {
                        sprintf(format, "%%-%dd  ", format_len);
                        printf(format, *(int*)(data + attrInfo.offset));
                    }
                    else if (attrInfo.attrType == FLOAT)
                    {
                        sprintf(format, "%%-%df  ", format_len);
                        printf(format, *(float*)(data + attrInfo.offset));
                    }
                    else if (attrInfo.attrType == STRING)
                    {
                        sprintf(format, "%%-%ds  ", format_len);
                        printf(format, data + attrInfo.offset);
                    }
                    else if (attrInfo.attrType == VARCHAR)
                    {
                        sprintf(format, "%%-%ds  ", format_len);
                        printf(format, data + attrInfo.offset);
                    }
                }
            }
        }
	}
	else if (record->type == 1) // ������ڵ�һ������ͨ��¼�������Ǿۺϼ�¼
	{
		Record_Show(psn, record->get_record_left());
		Record_Show(psn, record->get_record_right());
	}
}

void getRelatedOperator(string op, CompOp & compOp)
{
	if (op == "=")
		compOp = EQ_OP;
	else if (op == "<>" || op == "!=")
		compOp = NE_OP;
	else if (op == "<")
		compOp = LT_OP;
	else if (op == ">")
		compOp = GT_OP;
	else if (op == "<=")
		compOp = LE_OP;
	else if (op == ">=")
		compOp = GE_OP;
}

void getRelatedValue(string val, Value & value, AttrcatRecord attrinfo)
{
	value.type = attrinfo.attrType;
	if (attrinfo.attrType == INT)
	{
		int* temval = new int(atoi(val.c_str()));
		value.type = INT;
		value.value = (void*)temval;
	}
	else if (attrinfo.attrType == FLOAT)
	{
		float* temval = new float(atof(val.c_str()));
        value.type = FLOAT;
		value.value = (void*)temval;
	}
	else if (attrinfo.attrType == STRING)
	{
		string* temval = new string(val.substr(1, val.size() - 2));
        value.type = STRING;
		value.value = (void*)temval;
	}
	else if (attrinfo.attrType == VARCHAR)
	{
		string* temval = new string(val.substr(1, val.size() - 2));
        value.type = VARCHAR;
		value.value = (void*)temval;
	}
	else
    {
	    cout << "����ʱ�޷�ʶ��" << endl;
    }
}

void getRelatedLogicalOperator(string op, Operator &oper)
{
	if (op == "and" || op == "AND")
		oper = AND;
	else if (op == "or" || op == "OR")
		oper = OR;
	else
		cout << "�߼����������" << endl;
}

bool recordSatisfied(Record * record_, vector<Resolution>& resolutions, vector<Operator> operators, GlobalState* gstate, string tablename)
{
	RM_Record* record = record_->record;
	if (record == NULL) // ������ֹ
		return true;

	bool res = true;
	for (int i = 0; i < resolutions.size(); ++i)
	{
		if (i == 0)
			res = isSatisfied(record, resolutions[i], gstate, tablename);
		else
			res = logicalOperate(res, isSatisfied(record, resolutions[i], gstate, tablename), operators[i - 1]);
	}
	return res;
}

bool isSatisfied(RM_Record * record, Resolution resolution, GlobalState* gstate, string tablename)
{
	// ���������Ϣ
	AttrcatRecord attrInfo;
	gstate->manager_ddl->getAttrInfo(tablename.c_str(), resolution.attrName.c_str(), attrInfo);

	// �Ƚ�
	char *data;
	record->getData(data);
	if (attrInfo.attrType == INT)
	{
		int leftval = *(int*)(data + attrInfo.offset);
		int rightval = *(int*)(resolution.value.value);
		if (resolution.compOp == EQ_OP)
		{
			if (leftval == rightval)
				return true;
			else
				return false;
		}
		else if (resolution.compOp == NE_OP)
		{
			if (leftval != rightval)
				return true;
			else
				return false;
		}
		else if (resolution.compOp == LT_OP)
		{
			if (leftval < rightval)
				return true;
			else
				return false;
		}
		else if (resolution.compOp == GT_OP)
		{
			if (leftval > rightval)
				return true;
			else
				return false;
		}
		else if (resolution.compOp == LE_OP)
		{
			if (leftval <= rightval)
				return true;
			else
				return false;
		}
		else if (resolution.compOp == GE_OP)
		{
			if (leftval >= rightval)
				return true;
			else
				return false;
		}
	}
	else if (attrInfo.attrType == FLOAT)
	{
		float leftval = *(float*)(data + attrInfo.offset);
		float rightval = *(float*)(resolution.value.value);
		if (resolution.compOp == EQ_OP)
		{
			if (leftval == rightval)
				return true;
			else
				return false;
		}
		else if (resolution.compOp == NE_OP)
		{
			if (leftval != rightval)
				return true;
			else
				return false;
		}
		else if (resolution.compOp == LT_OP)
		{
			if (leftval < rightval)
				return true;
			else
				return false;
		}
		else if (resolution.compOp == GT_OP)
		{
			if (leftval > rightval)
				return true;
			else
				return false;
		}
		else if (resolution.compOp == LE_OP)
		{
			if (leftval <= rightval)
				return true;
			else
				return false;
		}
		else if (resolution.compOp == GE_OP)
		{
			if (leftval >= rightval)
				return true;
			else
				return false;
		}
	}
	else if (attrInfo.attrType == STRING || attrInfo.attrType == VARCHAR)
	{
		char* leftval = new char[attrInfo.attrLength];
		char* rightval = new char[attrInfo.attrLength+20]; // ����û�б��泤��
		strcpy(leftval, data + attrInfo.offset);
		strcpy(rightval, (char*)resolution.value.value + attrInfo.offset);
		if (resolution.compOp == EQ_OP)
		{
			if (strcmp(leftval, rightval) == 0)
				return true;
			else
				return false;
		}
		else if (resolution.compOp == NE_OP)
		{
			if (strcmp(leftval, rightval) != 0)
				return true;
			else
				return false;
		}
	}
	return false;
}

bool logicalOperate(bool n1, bool n2, Operator op)
{
	if (op == AND)
		return n1 and n2;
	else if (op == OR)
		return n1 or n2;
	else
		cout << "��֧�������߼������" << endl;
	return false;
}

int getRelatedAttrNo(DDL_Manager * manager_ddl, IX_Manager * manager_idx, string tablename, string attrname)
{
	vector<string> attrnames;
	manager_ddl->getAttributes(tablename, attrnames);

	for (int i = 0; i < attrnames.size(); ++i)
		if (attrnames[i] == attrname)
			return i;
    return 0;
}

void constraintBorder(vector<Resolution> resolutions, string indexname, string &lv, string &rv)
{
    cout << "�������������߽�" << indexname << endl;

	// Ѱ����߽��Ӧ���ʽ��resolutions��ĳһ�
	int lv_idx = -1;
	for (int i = 0; i < resolutions.size(); ++i)
	{
		if (resolutions[i].attrName == indexname && resolutions[i].compOp == GT_OP)
		{
			lv_idx = i;
			break;
		}
	}
	// Ѱ���ұ߽��Ӧ���ʽ��resolutions��ĳһ�
	int rv_idx = -1;
	for (int i = 0; i < resolutions.size(); ++i)
    {
		if (resolutions[i].attrName == indexname && resolutions[i].compOp == LT_OP)
		{
			rv_idx = i;
			break;
		}
	}

	// ת����߽�
    if (lv_idx != -1)
    {
        Value value_lv = resolutions[lv_idx].value;
        if (value_lv.type == INT)
            lv = to_string(*(int*)value_lv.value);
        else if (value_lv.type == FLOAT)
            lv = to_string(*(float*)value_lv.value);
        else if (value_lv.type == STRING)
            lv = to_string(*(char*)value_lv.value);
        else if (value_lv.type == VARCHAR)
            lv = to_string(*(char*)value_lv.value);
    }
	// ת���ұ߽�
    if (rv_idx != -1)
    {
        Value value_rv = resolutions[rv_idx].value;
        if (value_rv.type == INT)
            rv = to_string(*(int*)value_rv.value);
        else if (value_rv.type == FLOAT)
            rv = to_string(*(float*)value_rv.value);
        else if (value_rv.type == STRING)
            rv = to_string(*(char*)value_rv.value);
        else if (value_rv.type == VARCHAR)
            rv = to_string(*(char*)value_rv.value);
    }
}

int getColSize(int &len, char* data, AttrcatRecord attrInfo)
{
    if (attrInfo.attrType == INT)
    {
        if (to_string(*(int*)(data + attrInfo.offset)).size() > len)
            len = to_string(*(int*)(data + attrInfo.offset)).size();
    }
    else if (attrInfo.attrType == FLOAT)
    {
        if (to_string(*(float*)(data + attrInfo.offset)).size() > len)
            len = to_string(*(float*)(data + attrInfo.offset)).size();
    }
    else if (attrInfo.attrType == STRING)
    {
        if (strlen((char*)(data + attrInfo.offset)) > len)
            len = strlen((char*)(data + attrInfo.offset));
    }
    else if (attrInfo.attrType == VARCHAR)
    {
        if (to_string(*(int*)(data + attrInfo.offset)).size() > len)
            len = to_string(*(char*)(data + attrInfo.offset)).size();
    }
}