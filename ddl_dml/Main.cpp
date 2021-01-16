#include <iostream>
using namespace std;
#include "Node.h"
#include "SqlGlobal.h"
#include "Translator.h"
#include "DDL_public.h"
#include "DML_gram.tab.h"

int parser_ddl_sql(string sql);
extern DDLStmt g_DDLStmt;

//int parser_dml_sql(string sql);
string getInputSql();
int main() {

	string sql;
	extern SqlGlobal* sg;
	while (!sg->exit) 
	{
		cout << "sql> ";
		sql = getInputSql();
		int result = parser_ddl_sql(sql);
		//g_DDLStmt.transform();
	}
	return 0;
	
}