#ifndef EXECUTE_EXTEND
#define EXECUTE_EXTEND

#include <string>
using namespace std;

#include "../storage/rm.h"


// 扩展存储管理部分的RM_Record，用于连接节点 JoinPlanStateNode
class Record {
private:
	Record* record_left;
	Record* record_right;
public:
	int type;
	RM_Record* record;
	string tablename;
public:
	Record(RM_Record* record, string tablename) { this->record = record; this->type = 0; this->tablename = tablename; }
	Record(Record* left, Record* right) { this->record_left = left; this->record_right = right; this->type = 1; }

	Record* get_record_left(void) { return this->record_left; };
	Record* get_record_right(void) { return this->record_right; };
};


#endif // !EXECUTE_EXTEND
