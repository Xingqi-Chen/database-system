#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "StateNode.h"
#include "../storage/rm.h"

// ��ѯִ�����壬����ִ�о���Ĳ�ѯ����
class Executor {
private:
	PlanStateNode* root;
	GlobalState* gstate;
public:
	void ExecutorStart(PhyPlanNode * ppn, RM_Manager* manager, DDL_Manager* manager_ddl, IX_Manager* idxm, DML_Manager* dmlm);
	void ExecutorRun();
	void ExecutorEnd();

	PlanStateNode* getRoot(void) { return this->root; };
};

#endif // !EXECUTOR_H
