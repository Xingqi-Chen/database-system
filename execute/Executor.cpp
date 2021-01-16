#include "Executor.h"
#include "StateNode.h"
#include "ProcessFunc.h"

void Executor::ExecutorStart(PhyPlanNode * ppn, RM_Manager* rm_mgr, DDL_Manager* ddl_mgr, IX_Manager* idxm, DML_Manager* dmlm)
{
	this->gstate = new GlobalState(rm_mgr, ddl_mgr, idxm, dmlm);
	this->root = buildPlanStateTree(ppn, this->gstate);
	aggregateBuild(this->root);
}

void Executor::ExecutorRun()
{
	// ���ж�Ӧ��ִ�к���
	root->Run();
}

void Executor::ExecutorEnd()
{

}
