//
// Created by Administrator on 2020/11/12.
//

#ifndef MYDATABASE_DDL_H
#define MYDATABASE_DDL_H

#include "../storage/rm.h"
#include "../parser.h"

/* 数据字典中所有字符串的长度都为MAXNAME + 1 */

// RelcatRecord - 存储在relcat中的记录
// relName - 表名
// tupleLength - 元组的长度
// attrCount - 属性的数量
// indexCount - 索引属性的数量
struct RelcatRecord {
    char relName[MAXNAME + 1];
    int tupleLength;
    int attrCount;
    int indexCount;
};

// AttrcatRecord - 存储在attrcat中的记录
// relName - 表名
// attrName - 属性名
// offset - 属性的偏移量
// attrType - 属性的类型
// attrLength - 属性的长度
// indexNo - indexNumber 或 -1表示没有索引
struct AttrcatRecord {
    char relName[MAXNAME + 1];
    char attrName[MAXNAME + 1];
    int offset;
    AttrType attrType;
    int attrLength;
    int indexNo;
};

#define SM_RELCAT_ATTR_COUNT    4       // 表示表目录的记录的属性数量
#define SM_ATTRCAT_ATTR_COUNT   6       // 表示属性目录的记录的属性数量

class DDL_Manager {
public:
    DDL_Manager(RM_Manager &_rmManager);
    ~DDL_Manager();
    RC openDb(const char *dbName);                  // 打开一个数据库
    RC closeDb();                                   // 关闭数据库
    RC createTable(const char *relName,             // 表名
                   int        attrCount,            // 属性的数量
                   AttrInfo   *attributes);         // 属性的数据(属性名, 属性长度, 属性类型)
    RC getRelInfo(const char *relName, RelcatRecord& relinfo);   // 返回属性信息和表信息
    RC getAttrInfo(const char *relName, int attrCount, AttrcatRecord *attrinfo);

private:
    int bDbOpen;
    RM_Manager *rmManager;
    RM_FileHandle relFileHandle;
    RM_FileHandle attrFileHandle;
};


#define DDL_DATABASE_OPEN                    (START_DDL_WARN + 2)
#define DDL_REL_NOT_EXISTS                   (START_DDL_WARN + 1)     // 进行操作的表不存在


#define DDL_INVALID_DBNAME                   (START_DDL_ERR - 0)

#endif //MYDATABASE_DDL_H