#include <iostream>
#include <vector>
#include "StateNode.h"
#include "Execute_extend.h"
#include "ProcessFunc.h"
#include "../storage/rm.h"
using namespace std;

PlanStateNode::PlanStateNode(GlobalState * gstate, int type)
{
	this->gstate = gstate;
	this->type = type;
	this->firstFlag = true;
	this->left = NULL;
	this->right = NULL;
}

void PlanStateNode::addParameters(vector<string> parameters)
{
	for (int i = 0; i < parameters.size(); ++i)
		this->parameters.push_back(parameters[i]);
}

void PlanStateNode::addAdditions(vector<string> additions)
{
	for (int i = 0; i < additions.size(); ++i)
		this->additions.push_back(additions[i]);
}


void PlanStateNode::init(PhyPlanNode * ppn, PlanStateNode * left, PlanStateNode * right)
{
	//------------------------------
	cout << "δ��ʼ������" << endl;
	this->parameters = ppn->getParameters();
	this->additions = ppn->getAddition();
	this->left = left;
	this->right = right;
}

void PlanStateNode::getDoubleValue(Record *record, double &value, AttrcatRecord attrInfo)
{
    char* data;
    record->record->getData(data);
    value = *(int*)(data + attrInfo.offset);
}

//Run�����߼���
//	��������������ᱣ����gstate�У�
//	��ȡgstate����һ����¼��
//	����ǿգ������¼��
//	���Ϊ�գ�����ѭ��
void SelectPlanStateNode::Run()
{
	while (true)
	{
		// ��������
		if (this->left != NULL)
			this->left->Run();
		if (this->right != NULL)
			this->right->Run();

		Record* record = gstate->getRecord();
		if (record == NULL) // û�к�����¼
			break;
		else
		{
            if (this->firstFlag == true)
            {
                this->firstFlag = false;
                Attr_Show(this, record);
                cout << endl;
            }
		    Record_Show(this, record);
		    cout << endl;
		}
	}
}

void SelectPlanStateNode::show()
{
	cout << "method name: Select" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}

void SeqScanPlanStateNode::scanInit(RM_FileScan* scan)
{
	this->scan = scan;
}

void SeqScanPlanStateNode::Run()
{
	if (this->firstFlag == true)
	{
		this->firstFlag = false;

		// ȷ�����ļ�
		RM_FileHandle rm_fh;
		this->gstate->manager->openFile(this->getParameters()[0].c_str(), rm_fh);

		// ��������
		constraintResolution(this, this->resolutions, this->operators);

		// ����һ��û�������ĵ�����
		RM_FileScan* scan = new RM_FileScan();
		scan->openScan(rm_fh, INT, 4, 0, NO_OP, (void*)(new int));
		this->scanInit(scan);
	}

	// TO DO
	// ��ȡ��һ����¼���ж�����������񣬷���ȫ��״̬��
	// �������getNextRec����û���ҵ�ƥ����᷵�� NULL
	Record *record;
    RC rc;
    while (true)
	{
		RM_Record* rm_record = new RM_Record();
		rc = this->scan->getNextRec(*rm_record);
		record = new Record(rm_record, this->getParameters()[0]);
		// �ж������������
		if (rc != 0 || recordSatisfied(record, this->resolutions, this->operators, this->gstate, this->getParameters()[0]) == true)
			break;
	}
	if (rc != 0) // û��ƥ�����ʾ��������
		record = NULL;
	this->gstate->setRecord(record);
}

void SeqScanPlanStateNode::show()
{
	cout << "method name: SeqScan" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}

GlobalState::GlobalState(RM_Manager * pfm, DDL_Manager* ddlm, IX_Manager* idxm, DML_Manager* dmlm)
{
	this->manager = pfm;
	this->manager_ddl = ddlm;
	this->manager_idx = idxm;
	this->manager_dml = dmlm;
	this->record = NULL;
}

void GlobalState::show()
{
    if (this->record == NULL)
        cout << "��������" << endl;
    else
    {
        if (record->type == 0)
        {
            show_0(this->record);
        }
        else
        {
            cout << "�����ӱ�" << endl;
            show_0(this->record->get_record_left());
            cout << "�����ӱ�" << endl;
            show_0(this->record->get_record_right());
        }
    }
}

void GlobalState::show_0(Record *record)
{
    vector<string> attrnames;
    this->manager_ddl->getAttributes(record->tablename.c_str(), attrnames);
    char* data;
    record->record->getData(data);
    for (int i = 0 ; i < attrnames.size(); ++i)
    {
        AttrcatRecord attrInfo;
        this->manager_ddl->getAttrInfo(record->tablename.c_str(), attrnames[i].c_str(), attrInfo);

        // ���
        cout << attrnames[i] << ": ";
        if (attrInfo.attrType == INT)
            cout << *(int*)(data+attrInfo.offset);
        else if (attrInfo.attrType == FLOAT)
            cout << *(float*)(data+attrInfo.offset);
        else if (attrInfo.attrType == STRING)
            cout << *(char*)(data+attrInfo.offset);
        else if (attrInfo.attrType == VARCHAR)
            cout << *(char*)(data+attrInfo.offset);
        cout << endl;
    }
}

void InsertPlanStateNode::Run()
{
	// TO DO
	// �򿪶�Ӧ�ı��ļ����rm_fh��Ȼ�����һ����¼
	// ����additions���ԣ���һ��Ԫ��Ϊ�����ƣ��ڶ���Ԫ��Ϊ����ļ�¼
	// ridΪ������¼��id
	RM_FileHandle rm_fh;
	this->gstate->manager->openFile(this->getParameters()[0].c_str(), rm_fh);

	// ��ȡ�����Ϣ
    RelcatRecord relInfo;
    this->gstate->manager_ddl->getRelInfo(this->getParameters()[0].c_str(), relInfo);
    vector<string> attrNames;
    this->gstate->manager_ddl->getAttributes(this->getParameters()[0].c_str(), attrNames);

    // ��ȡ�������Ե���Ϣ
    vector<AttrcatRecord> attrinfos;
    for (int i = 0 ; i < attrNames.size() ; ++i)
    {
        AttrcatRecord attrinfo;
        this->gstate->manager_ddl->getAttrInfo(this->getParameters()[0].c_str(), attrNames[i].c_str(), attrinfo);
        attrinfos.push_back(attrinfo);
    }

    // ����value
    Value *values = new Value[relInfo.attrCount];
    int idx = 0;
    for (int i = 0 ; i < this->getAdditions().size() ; ++i)
    {
        values[idx].type = attrinfos[idx].attrType;
        if (values[idx].type == INT)
        {
            int* value = new int(atoi(this->getAdditions()[i].c_str()));
            values[idx].value = (void*)value;
        }
        else if (values[idx].type == FLOAT)
        {
            float* value = new float(atof(this->getAdditions()[i].c_str()));
            values[idx].value = (void*)value;
        }
        else if (values[idx].type == STRING)
        {
            values[idx].value = (void*)this->getAdditions()[i].c_str();
        }
        else if (values[idx].type == VARCHAR)
        {
            values[idx].value = (void*)this->getAdditions()[i].c_str();
        }

        // �����������
        idx++;
        if (idx == attrinfos.size())
        {
            idx = 0;
            this->gstate->manager_dml->insert(this->getParameters()[0].c_str(), attrinfos.size(), values);
        }
    }
}

void InsertPlanStateNode::show()
{
	cout << "method name: Insert" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}

void DeletePlanStateNode::Run()
{
	// TO DO
	// �򿪲����ı��ļ�
	// �ӽڵ������ɾ������������Ԫ��
	// ����additions���ԣ���һ��Ԫ��Ϊ������
	RM_FileHandle rm_fh;
	this->gstate->manager->openFile(this->getParameters()[0].c_str(), rm_fh);
	while (true)
	{
		// ��������
		if (this->left != NULL)
			this->left->Run();
		if (this->right != NULL)
			this->right->Run();

		Record* record = gstate->getRecord();
		if (record == NULL) // û�к�����¼
			break;
		else
		{
			// ��ȡRID��Ȼ��ɾ��RID��Ӧ�ļ�¼
			RID rid;
			record->record->getRid(rid);
			rm_fh.deleteRec(rid);
            this->gstate->manager->closeFile(rm_fh);
		}
	}
}

void DeletePlanStateNode::show()
{
	cout << "method name: Delete" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}

void UpdatePlanStateNode::Run()
{
	// TO DO
	// �򿪲����ı��ļ�
	// �ӽڵ��������������������Ԫ��
	// ����additions���ԣ���һ��Ԫ��Ϊ�����ƣ��ڶ�������Ϊ�޸ĺ�ļ�¼
	RM_FileHandle rm_fh;
	this->gstate->manager->openFile(this->getParameters()[0].c_str(), rm_fh);
	while (true)
	{
		// ��������
		if (this->left != NULL)
			this->left->Run();
		if (this->right != NULL)
			this->right->Run();

		Record* record = gstate->getRecord();
		if (record == NULL) // û�к�����¼
			break;
		else
        {
		    // ��ȡ�޸ĵ�����
            AttrcatRecord attrinfo;
		    Value value;
            for (int i = 0 ; i < this->getAdditions().size() ; ++i)
            {
                constraintEqual(this, this->getAdditions()[i], attrinfo, value);
                // ���Ƶ�ָ���ռ�
                char* data;
                this->gstate->getRecord()->record->getData(data);
                cout << *(int*)(data+attrinfo.offset) << endl;
                memcpy(data + attrinfo.offset, (char*)(value.value), attrinfo.attrLength);
                this->gstate->getRecord()->record->getData(data);
                cout << *(int*)(data+attrinfo.offset) << endl;
            }
			// �޸����ݣ���������rid��Ȼ���ڱ��ļ����޸ļ�¼
			rm_fh.updateRec(*(record->record));
            this->gstate->manager->closeFile(rm_fh);
		}
	}
}

void UpdatePlanStateNode::show()
{
	cout << "method name: Update" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}

void FilterPlanStateNode::Run()
{
	// ���˽ڵ��Ӧֻ��һ�������������˵������³�����һ��ڵ���д���
	if (this->left != NULL)
	{
		if (this->firstFlag == true)
		{
			this->left->addParameters(this->getParameters());
			this->left->addAdditions(this->getAdditions());
			this->firstFlag = false;
		}
		this->left->Run();
	}
	else if (this->right != NULL)
	{
		if (this->firstFlag == true)
		{
			this->right->addParameters(this->getParameters());
            this->right->addAdditions(this->getAdditions());
			this->firstFlag = false;
		}
		this->right->Run();
	}
}

void FilterPlanStateNode::show()
{
	cout << "method name: Filter" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}

JoinPlanStateNode::JoinPlanStateNode(GlobalState * gstate) :PlanStateNode(gstate, JOIN)
{
	this->record_left = NULL;
	this->record_right = NULL;
	this->first_flag = true;
}

void JoinPlanStateNode::Run()
{
	// ������˵��JoinPlanStateNode�ڵ������������Ϊ��
	if (this->left == NULL || this->right == NULL)
		cout << "�쳣��JoinPlanStateNode�����п�" << endl;

	// ѭ���ҵ�����Լ�������ļ�¼
	while (true)
	{
		// ��һ��ִ�У����ҵ�������ִ��һ��
		if (this->record_left == NULL && this->record_right == NULL && this->first_flag == true)
		{
		    this->first_flag = false;

			this->left->Run();
			this->record_left = this->gstate->getRecord();

			this->right->Run();
			this->record_right = this->gstate->getRecord();
		}
		// �ظ�ִ���ҵ�����
		else if (this->record_left != NULL && this->record_right != NULL)
		{
			this->right->Run();
			this->record_right = this->gstate->getRecord();
        }
		// ������ִ�н���
		// To Do
		// ִ���������
		// �е���������
		else if (this->record_left != NULL && this->record_right == NULL) {
            this->left->Run();
            this->record_left = this->gstate->getRecord();

            dfs_initScanStateNode(this->right);
            this->right->Run();
            this->record_right = this->gstate->getRecord();
        }

		// ִ�н�����
		if (this->record_left == NULL && this->first_flag == false)
		{
			this->record_left = NULL;
			this->record_right = NULL;
			break;
		}
		// �п�
		if (this->record_left == NULL || this->record_right == NULL)
		    continue;

		// �����������¼������������
		if (this->getAdditions().size() == 0 || isProper(this->record_left, this->record_right, this->getParameters(), this->getAdditions(), this->gstate))
			break;
	}

	if (this->record_left != NULL && this->record_right != NULL)
        this->gstate->setRecord(new Record(this->record_left, this->record_right));
	else
		this->gstate->setRecord(NULL);
}

void JoinPlanStateNode::show()
{
	cout << "method name: Join" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}

void IndexScanPlanStateNode::Run()
{
	// ȷ�����ļ�
	RM_FileHandle rm_fh;
	this->gstate->manager->openFile(this->getParameters()[0].c_str(), rm_fh);

	if (this->firstFlag == true)
	{
		this->firstFlag = false;

		// ����������Զ�Ӧ��indexNo
		int idxNo = getRelatedAttrNo(this->gstate->manager_ddl, this->gstate->manager_idx, this->getParameters()[0], this->getParameters()[1]);

		// ȷ���������ļ�
		IX_IndexHandle id_ih;
		this->gstate->manager_idx->openIndex(this->getParameters()[0].c_str(), idxNo, id_ih);

		// ��������
		constraintResolution(this, this->resolutions, this->operators);

		// �������������ұ߽�
		string lv, rv;
		constraintBorder(this->resolutions, this->getParameters()[1], lv, rv);

		cout << "lv:" << lv << endl << "rv:" << rv << endl;

        // ����������
		IX_IndexScan* scan = new IX_IndexScan();
		scan->openScan(id_ih, NO_OP, (void*)(new int), lv, rv);
		this->scanInit(scan);
	}

	// TO DO
	// ��ȡ��һ����¼���ж�����������񣬷���ȫ��״̬��
	// �������getNextRec����û���ҵ�ƥ����᷵�� NULL
	Record *record;
    RC rc;
	while (true)
	{
		// ��ȡrid���ҵ���Ӧ�ļ�¼
		RID rid;
		rc = this->scan->getNextEntry(rid);
		RM_Record* rm_record = new RM_Record();
		rm_fh.getRec(rid, *rm_record);
		record = new Record(rm_record, this->getParameters()[0]);

		// �ж������������
        if (rc != 0 || recordSatisfied(record, this->resolutions, this->operators, this->gstate, this->getParameters()[0]) == true)
			break;
	}
	if (rc != 0) // û��ƥ�����ʾ��������
		record = NULL;
	this->gstate->setRecord(record);
}

void IndexScanPlanStateNode::show()
{
	cout << "method name: IndexScan" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}

vector<double> MeterializationPlanStateNode::MerializationRun()
{
    if (this->firstFlag == true)
    {
        this->firstFlag = false;

        // �����漰�� relName�� attrName����
        string relName;
        string attrName;
        for (int i = 0 ; i < this->getAdditions().size() ; ++i)
        {
            // ������Ҫ�ﻯ����
            constraintOutputResolution(this->getAdditions()[i], relName, attrName);

            if (relName == "")
                relName = this->getParameters()[0];

            // ������������ԣ���ͨ�����������������
            if (attrName == "*")
            {
                vector<string> attrNames;
                this->gstate->manager_ddl->getAttributes(relName, attrNames);

                for (int j = 0 ; j < attrNames.size() ; ++j)
                {
                    attrName = attrNames[j];
                    AttrcatRecord attrinfo;
                    this->gstate->manager_ddl->getAttrInfo(relName.c_str(), attrName.c_str(), attrinfo);
                    this->attrInfos.push_back(attrinfo);

                    // ֻ�ܶ� INT �� FLOAT �������оۼ�����
                    if (attrinfo.attrType != INT && attrinfo.attrType != FLOAT)
                    {
                        cout << "�޷���" << attrinfo.attrName << "���оۼ�����" << endl;
                        return vector<double>();
                    }
                }

                break;
            }
            else
            {
                AttrcatRecord attrinfo;
                this->gstate->manager_ddl->getAttrInfo(relName.c_str(), attrName.c_str(), attrinfo);
                this->attrInfos.push_back(attrinfo);

                // ֻ�ܶ� INT �� FLOAT �������оۼ�����
                if (attrinfo.attrType != INT && attrinfo.attrType != FLOAT)
                {
                    cout << "�޷���" << attrinfo.attrName << "���оۼ�����" << endl;
                    return vector<double>();
                }
            }
        }
        // ��ʼ������
        this->init(this->attrInfos.size());
    }

    // ִ���ӽڵ㣬��ȡ��¼
    if (this->left != NULL)
        this->left->Run();
    if (this->right != NULL)
        this->right->Run();

    // ��������
    if (this->gstate->getRecord() == NULL) // ��������
    {
        return vector<double>();
    }

    vector<double> ret;
    for (int i = 0 ; i < this->attrInfos.size() ; ++i)
    {
        double tem;
        this->getDoubleValue(this->gstate->getRecord(), tem, attrInfos[i]);
        ret.push_back(tem);
    }

    return ret;
}

void SumPlanStateNode::Run()
{
    // ִ�г�ʼ������ �Լ� �ӽڵ�ִ�У�����ȡ����ֵ
    vector<double> values = this->MerializationRun();

    // ����ﻯ���Ե�ֵ
    if (this->gstate->getRecord() == NULL) // ��������
    {
        for (int i = 0 ; i < this->temSums.size() ; ++i)
            cout << "sum(" << this->getAdditions()[i] << "): " << this->temSums[i] << endl;
    }

    // ��ӵ��ﻯ������
    for (int i = 0 ; i < values.size() ; ++i)
    {
        this->temSums[i] += values[i];
    }
}

void SumPlanStateNode::show()
{
	cout << "method name: Sum" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}

void MaxPlanStateNode::Run()
{
    // ִ�г�ʼ������ �Լ� �ӽڵ�ִ�У�����ȡ����ֵ
    vector<double> values = this->MerializationRun();

    // ����ﻯ����
    if (this->gstate->getRecord() == NULL) // ��������
    {
        for (int i = 0 ; i < this->temMaxs.size() ; ++i)
            cout << "max(" << this->getAdditions()[i] << "): " << this->temMaxs[i] << endl;
    }

    // ��ӵ��ﻯ������
    for (int i = 0 ; i < values.size() ; ++i)
    {
        if (this->temMaxs[i] < values[i])
            this->temMaxs[i] = values[i];
    }
}

void MaxPlanStateNode::show()
{
	cout << "method name: Max" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}

void MinPlanStateNode::Run()
{
    // ִ�г�ʼ������ �Լ� �ӽڵ�ִ�У�����ȡ����ֵ
    vector<double> values = this->MerializationRun();

    // ����ﻯ���Ե�ֵ
    if (this->gstate->getRecord() == NULL) // ��������
    {
        for (int i = 0 ; i < this->temMins.size() ; ++i)
            cout << "min(" << this->getAdditions()[i] << "): " << this->temMins[i] << endl;
    }

    // ��ӵ��ﻯ������
    for (int i = 0 ; i < values.size() ; ++i)
    {
        if (this->temMins[i] > values[i])
            this->temMins[i] = values[i];
    }
}

void MinPlanStateNode::show()
{
	cout << "method name: Min" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}

void MeanPlanStateNode::Run()
{
    // ִ�г�ʼ������ �Լ� �ӽڵ�ִ�У�����ȡ����ֵ
    vector<double> values = this->MerializationRun();

    // ����ﻯ���Ե�ֵ
    if (this->gstate->getRecord() == NULL) // ��������
    {
        for (int i = 0 ; i < this->temSums.size() ; ++i)
            cout << "mean(" << this->getAdditions()[i] << "): " << this->temSums[i]/this->size << endl;
    }

    // ��ӵ��ﻯ������
    for (int i = 0 ; i < values.size() ; ++i)
    {
        this->temSums[i] += values[i];
        this->size++;
    }
}

void MeanPlanStateNode::show()
{
	cout << "method name: Mean" << endl;
	cout << "parameters:" << endl;
	for (int i = 0; i < this->getParameters().size(); ++i)
		cout << this->getParameters()[i] << endl;
	cout << "additions:" << endl;
	for (int i = 0; i < this->getAdditions().size(); ++i)
		cout << this->getAdditions()[i] << endl;
}
