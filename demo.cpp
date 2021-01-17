//
// Created by Administrator on 2021/1/16.
//

#include <iostream>
#include <ctime>
#include "sql/ddl.h"
#include "sql/dml.h"
//#include "error_message/all_error.h"

using namespace std;

const int dataCount = 100;

RC OpenDb(DDL_Manager &ddlManager, char *dbName);
RC CloseDb(DDL_Manager &ddlManager, char *dbName);
void generateStr(char str[], int size);
RC InsertData(DDL_Manager &ddlManager, DML_Manager &dmlManager, const char *relName);
RC PrintData(DDL_Manager &ddlManager, char *relName);

RC Demo();


int main() {
    int rc;
    srand(time(nullptr));
    if((rc = Demo())) {
        //PrintError(rc);
    }
    return 0;
}

// 打开数据库
RC OpenDb(DDL_Manager &ddlManager, char *dbName) {
    cout << "Open Database: " << dbName << "..\n";
    return ddlManager.openDb(dbName);
}

// 关闭数据库
RC CloseDb(DDL_Manager &ddlManager, char *dbName) {
    cout << "Close Database: " << dbName << "..\n";
    return ddlManager.closeDb();
}

// 随机生成size大小的字符串
void generateStr(char str[], int size) {
    for(int i = 0; i < size - 1; ++i) {
        str[i] = rand() % 26 + 97;
    }
    str[size - 1] = '\0';
}

// 向表中随机插入若干条记录
RC InsertData(DDL_Manager &ddlManager, DML_Manager &dmlManager, const char *relName) {
    RC rc;
    cout << "Insert " << dataCount << " items into " << relName << "\n";
    // 获取表的元信息
    RelcatRecord relcatRecord;
    if((rc = ddlManager.getRelInfo(relName, relcatRecord))) {
        return rc;
    }
    // 获取表属性的元信息
    AttrcatRecord *attrcatRecordList = new AttrcatRecord[relcatRecord.attrCount];
    if((rc = ddlManager.getAttrInfo(relName, attrcatRecordList))) {
        return rc;
    }
    // 插入若干随即生成的数据
    for(int i = 0; i < dataCount; ++i) {
        Value *values = new Value[relcatRecord.attrCount];
        for(int j = 0; j < relcatRecord.attrCount; ++j) {
            if((attrcatRecordList[j].attrType == INT)) {
                int val = rand() % 10000;
                values[j].value = new char[attrcatRecordList[j].attrLength];
                values[j].type = INT;
                memcpy(values[j].value, (char*)&val, attrcatRecordList[j].attrLength);
            }
            else if(attrcatRecordList[j].attrType == FLOAT) {
                float val = rand() % 10000 + ((float)(rand() % 100) / 100) ;
                values[j].value = new char[attrcatRecordList[j].attrLength];
                values[j].type = FLOAT;
                memcpy(values[j].value, (char*)&val, attrcatRecordList[j].attrLength);
            }
            else if(attrcatRecordList[j].attrType == STRING) {
                values[j].value = new char[attrcatRecordList[j].attrLength];
                values[j].type = attrcatRecordList[j].attrType;
                generateStr((char*)values[j].value, attrcatRecordList[j].attrLength);
            }
            else {
                int length = rand() % 20 + 2;
                values[j].value = new char[attrcatRecordList[j].attrLength];
                values[j].type = attrcatRecordList[j].attrType;
                generateStr((char*)values[j].value, length);
            }
        }
        if((rc = dmlManager.insert(relName, relcatRecord.attrCount, values))) {
            return rc;
        }
        for(int j = 0; j < relcatRecord.attrCount; ++j) {
            delete [] (char*)values[j].value;
        }
        delete [] values;
    }
    return 0;   // ok
}

RC Demo() {
    cout << "demo starts....\n";
    int rc;
    PF_Manager pfManager;
    RM_Manager rmManager(pfManager);
    IX_Manager ixManager(pfManager);
    DDL_Manager ddlManager(rmManager, ixManager);
    DML_Manager dmlManager(rmManager, ddlManager, ixManager);
    char dbName[MAXNAME + 1] = "bank";
    // 打开数据库
    if((rc = OpenDb(ddlManager, dbName))) {
        return rc;
    }
    // 插入数据
    if((rc = InsertData(ddlManager, dmlManager, "branch"))) {
        return rc;
    }
    if((rc = InsertData(ddlManager, dmlManager, "account"))) {
        return rc;
    }
    if((rc = InsertData(ddlManager, dmlManager, "borrower"))) {
        return rc;
    }
    if((rc = InsertData(ddlManager, dmlManager, "customer"))) {
        return rc;
    }
    if((rc = InsertData(ddlManager, dmlManager, "depositor"))) {
        return rc;
    }
    if((rc = InsertData(ddlManager, dmlManager, "loan"))) {
        return rc;
    }
    char tmpRelName[30] = "account";
    if((rc = PrintData(ddlManager, tmpRelName))) {
        return rc;
    }
    if((rc = CloseDb(ddlManager, dbName))) {
        return rc;
    }
    return rc;
}

RC PrintData(DDL_Manager &ddlManager, char *relName) {
    cout << "Print " << relName << "'s data.....\n";
    return ddlManager.printAllData(relName);
}
