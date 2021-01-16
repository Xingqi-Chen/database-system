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
	cout << "未初始化参数" << endl;
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

//Run运行逻辑：
//	运行子树，结果会保存在gstate中，
//	获取gstate的下一个记录，
//	如果非空，输出记录，
//	如果为空，跳出循环
void SelectPlanStateNode::Run()
{
	while (true)
	{
		// 运行子树
		if (this->left != NULL)
			this->left->Run();
		if (this->right != NULL)
			this->right->Run();

		Record* record = gstate->getRecord();
		if (record == NULL) // 没有后续记录
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

		// 确定表文件
		RM_FileHandle rm_fh;
		this->gstate->manager->openFile(this->getParameters()[0].c_str(), rm_fh);

		// 解析参数
		constraintResolution(this, this->resolutions, this->operators);

		// 创建一个没有条件的迭代器
		RM_FileScan* scan = new RM_FileScan();
		scan->openScan(rm_fh, INT, 4, 0, NO_OP, (void*)(new int));
		this->scanInit(scan);
	}

	// TO DO
	// 获取下一条记录，判断满足条件与否，放在全局状态中
	// 这里假设getNextRec函数没有找到匹配项会返回 NULL
	Record *record;
    RC rc;
    while (true)
	{
		RM_Record* rm_record = new RM_Record();
		rc = this->scan->getNextRec(*rm_record);
		record = new Record(rm_record, this->getParameters()[0]);
		// 判断满足条件与否
		if (rc != 0 || recordSatisfied(record, this->resolutions, this->operators, this->gstate, this->getParameters()[0]) == true)
			break;
	}
	if (rc != 0) // 没有匹配项，表示遍历结束
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
        cout << "迭代结束" << endl;
    else
    {
        if (record->type == 0)
        {
            show_0(this->record);
        }
        else
        {
            cout << "左连接表" << endl;
            show_0(this->record->get_record_left());
            cout << "右连接表" << endl;
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

        // 输出
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
	// 打开对应的表文件句柄rm_fh，然后插入一条记录
	// 假设additions属性，第一个元素为表名称，第二个元素为插入的记录
	// rid为插入后记录的id
	RM_FileHandle rm_fh;
	this->gstate->manager->openFile(this->getParameters()[0].c_str(), rm_fh);

	// 获取表的信息
    RelcatRecord relInfo;
    this->gstate->manager_ddl->getRelInfo(this->getParameters()[0].c_str(), relInfo);
    vector<string> attrNames;
    this->gstate->manager_ddl->getAttributes(this->getParameters()[0].c_str(), attrNames);

    // 获取所有属性的信息
    vector<AttrcatRecord> attrinfos;
    for (int i = 0 ; i < attrNames.size() ; ++i)
    {
        AttrcatRecord attrinfo;
        this->gstate->manager_ddl->getAttrInfo(this->getParameters()[0].c_str(), attrNames[i].c_str(), attrinfo);
        attrinfos.push_back(attrinfo);
    }

    // 解析value
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

        // 插入具体数据
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
	// 打开操作的表文件
	// 子节点遍历，删除满足条件的元组
	// 假设additions属性，第一个元素为表名称
	RM_FileHandle rm_fh;
	this->gstate->manager->openFile(this->getParameters()[0].c_str(), rm_fh);
	while (true)
	{
		// 运行子树
		if (this->left != NULL)
			this->left->Run();
		if (this->right != NULL)
			this->right->Run();

		Record* record = gstate->getRecord();
		if (record == NULL) // 没有后续记录
			break;
		else
		{
			// 获取RID，然后删除RID对应的记录
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
	// 打开操作的表文件
	// 子节点遍历，更改满足条件的元组
	// 假设additions属性，第一个元素为表名称，第二个属性为修改后的记录
	RM_FileHandle rm_fh;
	this->gstate->manager->openFile(this->getParameters()[0].c_str(), rm_fh);
	while (true)
	{
		// 运行子树
		if (this->left != NULL)
			this->left->Run();
		if (this->right != NULL)
			this->right->Run();

		Record* record = gstate->getRecord();
		if (record == NULL) // 没有后续记录
			break;
		else
        {
		    // 获取修改的数据
            AttrcatRecord attrinfo;
		    Value value;
            for (int i = 0 ; i < this->getAdditions().size() ; ++i)
            {
                constraintEqual(this, this->getAdditions()[i], attrinfo, value);
                // 复制到指定空间
                char* data;
                this->gstate->getRecord()->record->getData(data);
                cout << *(int*)(data+attrinfo.offset) << endl;
                memcpy(data + attrinfo.offset, (char*)(value.value), attrinfo.attrLength);
                this->gstate->getRecord()->record->getData(data);
                cout << *(int*)(data+attrinfo.offset) << endl;
            }
			// 修改数据，但不更改rid，然后在表文件中修改记录
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
	// 过滤节点的应只有一个子树，将过滤的条件下沉到下一层节点进行处理
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
	// 正常来说，JoinPlanStateNode节点的左右子树不为空
	if (this->left == NULL || this->right == NULL)
		cout << "异常：JoinPlanStateNode子树有空" << endl;

	// 循环找到满足约束条件的记录
	while (true)
	{
		// 第一次执行，左右迭代器都执行一次
		if (this->record_left == NULL && this->record_right == NULL && this->first_flag == true)
		{
		    this->first_flag = false;

			this->left->Run();
			this->record_left = this->gstate->getRecord();

			this->right->Run();
			this->record_right = this->gstate->getRecord();
		}
		// 重复执行右迭代器
		else if (this->record_left != NULL && this->record_right != NULL)
		{
			this->right->Run();
			this->record_right = this->gstate->getRecord();
        }
		// 右子树执行结束
		// To Do
		// 执行左迭代器
		// 有迭代器重置
		else if (this->record_left != NULL && this->record_right == NULL) {
            this->left->Run();
            this->record_left = this->gstate->getRecord();

            dfs_initScanStateNode(this->right);
            this->right->Run();
            this->record_right = this->gstate->getRecord();
        }

		// 执行结束，
		if (this->record_left == NULL && this->first_flag == false)
		{
			this->record_left = NULL;
			this->record_right = NULL;
			break;
		}
		// 有空
		if (this->record_left == NULL || this->record_right == NULL)
		    continue;

		// 如果这两个记录满足连接条件
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
	// 确定表文件
	RM_FileHandle rm_fh;
	this->gstate->manager->openFile(this->getParameters()[0].c_str(), rm_fh);

	if (this->firstFlag == true)
	{
		this->firstFlag = false;

		// 获得索引属性对应的indexNo
		int idxNo = getRelatedAttrNo(this->gstate->manager_ddl, this->gstate->manager_idx, this->getParameters()[0], this->getParameters()[1]);

		// 确定索引表文件
		IX_IndexHandle id_ih;
		this->gstate->manager_idx->openIndex(this->getParameters()[0].c_str(), idxNo, id_ih);

		// 解析参数
		constraintResolution(this, this->resolutions, this->operators);

		// 解析索引的左右边界
		string lv, rv;
		constraintBorder(this->resolutions, this->getParameters()[1], lv, rv);

		cout << "lv:" << lv << endl << "rv:" << rv << endl;

        // 声明迭代器
		IX_IndexScan* scan = new IX_IndexScan();
		scan->openScan(id_ih, NO_OP, (void*)(new int), lv, rv);
		this->scanInit(scan);
	}

	// TO DO
	// 获取下一条记录，判断满足条件与否，放在全局状态中
	// 这里假设getNextRec函数没有找到匹配项会返回 NULL
	Record *record;
    RC rc;
	while (true)
	{
		// 获取rid后，找到对应的记录
		RID rid;
		rc = this->scan->getNextEntry(rid);
		RM_Record* rm_record = new RM_Record();
		rm_fh.getRec(rid, *rm_record);
		record = new Record(rm_record, this->getParameters()[0]);

		// 判断满足条件与否
        if (rc != 0 || recordSatisfied(record, this->resolutions, this->operators, this->gstate, this->getParameters()[0]) == true)
			break;
	}
	if (rc != 0) // 没有匹配项，表示遍历结束
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

        // 解析涉及的 relName表 attrName属性
        string relName;
        string attrName;
        for (int i = 0 ; i < this->getAdditions().size() ; ++i)
        {
            // 解析需要物化的列
            constraintOutputResolution(this->getAdditions()[i], relName, attrName);

            if (relName == "")
                relName = this->getParameters()[0];

            // 如果是所有属性，即通配符，则处理所有属性
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

                    // 只能对 INT 和 FLOAT 变量进行聚集操作
                    if (attrinfo.attrType != INT && attrinfo.attrType != FLOAT)
                    {
                        cout << "无法对" << attrinfo.attrName << "进行聚集操作" << endl;
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

                // 只能对 INT 和 FLOAT 变量进行聚集操作
                if (attrinfo.attrType != INT && attrinfo.attrType != FLOAT)
                {
                    cout << "无法对" << attrinfo.attrName << "进行聚集操作" << endl;
                    return vector<double>();
                }
            }
        }
        // 初始化变量
        this->init(this->attrInfos.size());
    }

    // 执行子节点，获取记录
    if (this->left != NULL)
        this->left->Run();
    if (this->right != NULL)
        this->right->Run();

    // 迭代结束
    if (this->gstate->getRecord() == NULL) // 迭代结束
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
    // 执行初始化操作 以及 子节点执行，并获取所需值
    vector<double> values = this->MerializationRun();

    // 输出物化属性的值
    if (this->gstate->getRecord() == NULL) // 迭代结束
    {
        for (int i = 0 ; i < this->temSums.size() ; ++i)
            cout << "sum(" << this->getAdditions()[i] << "): " << this->temSums[i] << endl;
    }

    // 添加到物化属性中
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
    // 执行初始化操作 以及 子节点执行，并获取所需值
    vector<double> values = this->MerializationRun();

    // 输出物化属性
    if (this->gstate->getRecord() == NULL) // 迭代结束
    {
        for (int i = 0 ; i < this->temMaxs.size() ; ++i)
            cout << "max(" << this->getAdditions()[i] << "): " << this->temMaxs[i] << endl;
    }

    // 添加到物化属性中
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
    // 执行初始化操作 以及 子节点执行，并获取所需值
    vector<double> values = this->MerializationRun();

    // 输出物化属性的值
    if (this->gstate->getRecord() == NULL) // 迭代结束
    {
        for (int i = 0 ; i < this->temMins.size() ; ++i)
            cout << "min(" << this->getAdditions()[i] << "): " << this->temMins[i] << endl;
    }

    // 添加到物化属性中
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
    // 执行初始化操作 以及 子节点执行，并获取所需值
    vector<double> values = this->MerializationRun();

    // 输出物化属性的值
    if (this->gstate->getRecord() == NULL) // 迭代结束
    {
        for (int i = 0 ; i < this->temSums.size() ; ++i)
            cout << "mean(" << this->getAdditions()[i] << "): " << this->temSums[i]/this->size << endl;
    }

    // 添加到物化属性中
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
