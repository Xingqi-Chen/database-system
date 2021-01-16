%{
#include "DDL_public.h"
#include "Node.h"
#include "DML_gram.tab.h"

extern int yylex();
extern int yyerror(const char * format,...);
extern void strcopy(char*& src,char*& dest);

void set_node(int type);
void dividetypes(vector<int>& v,int sum);
void divideToNum(vector<int>& v,int sum);

struct yy_buffer_state;
#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif
extern void yy_switch_to_buffer (YY_BUFFER_STATE new_buffer);
extern YY_BUFFER_STATE yy_scan_string ( const char *yy_str  );

DDLStmt g_DDLStmt;

%}
 
%union
{
	M_DML::Attribute *attribute;
	M_DML::OrderNode *orderNode;
	M_DML::Relation *relation;
	M_DML::Operator *soperator;
	M_DML::SelList	*selList;
	M_DML::FromList *fromList;
	M_DML::Condition *condision;
	M_DML::OrderList *orderList;
	M_DML::GroupList *groupList;
	M_DML::Query *query;
	M_DML::Number* rNumber;
	M_DML::ParaString* pString;
	
	M_DML::Name* name;
    vector<M_DML::Name*>* nameList;
    
	string* text;
	int type;
	
	M_DML::Insert* insert;
	vector<string>* values;
	
	M_DML::Delete* del;
	
	M_DML::Update* upd;
	string* attr_index[2];
	map<string, string>* attr_indexs;

	PhyPlanNode* phyNode;
	vector<PhyPlanNode*>* phyNodes; 

	NodeStorage* nodestorage;

	/* ddl */
	int					intval;
	double				floatval;
	char*				strval;
	int					subtok;
	CreateTableStmt*	createtablestmt;
}
 
%token LF RF
%token ST FM WH UPT DEL IST VAL INTO SET
%token WHSPLIT T_LT T_LE T_GT T_GE T_EQ T_NE T_NE IN
%token ORDER BY ORTYPE
%token DISTINCT AGGRET
%token EXIT
%token NUMBER PARA_STRING
%token SUBQUERY
%token NATURAL DML_JOIN
%token MULTI EXEC DISCARD
%token USE

%type<soperator> WHSPLIT T_LT T_LE T_GT T_GE T_EQ T_NE IN
%type<text> ORTYPE AGGRET

%type<rNumber> number
%type<query> stmt
%type<soperator> op
%type<selList> st_list st_nodes
%type<fromList> fm_list
%type<condision> wh_list whname whname_list
%type<orderList> order_list order
%type<nameList> name_list
%type<orderNode> order_node
%type<name> table_attr attr_name
%type<pString> para_string
%type<text> insert_value
%type<values> value_list
%type<attr_index> set_value
%type<attr_indexs>set_list
%type<phyNode> delete query update insert dml
%type<phyNodes> dmls
%type<nodestorage> whvalue

/* ddl */

%token <strval> NAME
%token <strval> DDL_STRING
%token <intval> INTNUM
%token <intval> BOOL
%token <floatval> APPROXNUM

	/*操作符*/
%left DDL_OR
%left XOR
%left ANDOP
%left <subtok> COMPARISON
%left <subtok> SHIFT

%token TABLE
%token CREATE
%token PRIMARY
%token KEY
%token NOT
%token NULLX
%token DDL_INT
%token REAL
%token TEXT
%token DATABASE

%token DROP
%token ALTER
%token INDEX
%token COLUMN
%token CONSTRAINT
%token ADD
%token MODIFY
%token TYPE
%token UNIQUE
%token ON

%type <intval> create_table_stmt
%type <intval> create_col_list create_definition column_list data_type column_atts
%type <intval> create_database create_index col_list_index
%type <intval> drop_stmt
%type <intval> alter_stmt

%%

command
	: utility
	| dml ';'
	{
		//此处调用执行函数即可,执行函数将返回错误状态码，需要获取并传入printError函数
		SqlGlobal::getInstance()->turnPnode2Exec($1);
		YYACCEPT;
	}
	| chooseDB ';'
	{
		YYACCEPT;
	}
	| dowork ';'
	{
		YYACCEPT;
	}
	| cancelwork ';'
	{
		YYACCEPT;
	} 
	| DDL_commands ';'
	{
		YYACCEPT;
	}
	;

utility
	: exit
	;
	
dowork
	: MULTI dmls EXEC
	{
		//dmls内即为各物理计划树根节点
		if(PhysicalPlan::canFinish(*$2))
		{
			//说明可以完成事务
			for (PhyPlanNode* root : *$2) 
			{
				//调用执行函数
				SqlGlobal::getInstance()->turnPnode2Exec(root);
			}
		}
		else
		{
			cout<<"违反事务"<<endl;
		}
	}
	;

cancelwork
	: MULTI dmls DISCARD
	{
		cout<<"已取消事务"<<endl;
	}
	;

dmls
	: dml
	{	
		$$ = new vector<PhyPlanNode*>;
		$$->push_back($1);
	}
	| dml dmls
	{
		$2->push_back($1);
		$$ = $2;
	}
	;

dml
	: query
	{
		//$$即为物理计划根节点
		$$ = $1;
	}
	| delete
	{
		$$ = $1;
	}
	| update
	{
		$$ = $1;
	}
	| insert
	{
		$$ = $1;
	}
	;

exit
	: EXIT ';'
	{
		YYACCEPT;
	}
	;

chooseDB
	: USE NAME
	{
		string dbName = string($2);//使用的数据库名
		SqlGlobal::getInstance()->useDB(dbName);
	}
	;

query
	: stmt
	{
		if(!SqlGlobal::getInstance()->preCheck()){
			//未通过预判断
			YYACCEPT;
		}
		M_DML::Query* query = $1;
		query->showInfo();

		
		SqlGrammer sqlgrammer;
		sqlgrammer.root = query->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		sqlgrammer.optimiza();
		cout << "-------------------------------"<<endl;

		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		$$ = physicalPlan.root;

		
		cout<<endl;
		//YYACCEPT;
	}
	;

delete
	: DEL FM NAME wh_list
	{
		if(!SqlGlobal::getInstance()->preCheck()){
			//未通过预判断
			YYACCEPT;
		}

		M_DML::Delete * del = new M_DML::Delete();
		del->tableName = std::string($3);
		del->condition = $4;
		del->showInfo();
		
		//$$ = new Delete();
		//$$->tableName = $3;
		//$$->condition = $4;
		//$$->showInfo();
		
		SqlGrammer sqlgrammer;
		//sqlgrammer.root = $$->transform2Grammer();
		sqlgrammer.root = del->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		cout << "-------------------------------"<<endl;
		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		$$ = physicalPlan.root;
		
		cout<<endl;
		//YYACCEPT;
	}
	;

update
	: UPT NAME SET set_list wh_list
	{	
		if(!SqlGlobal::getInstance()->preCheck()){
			//未通过预判断
			YYACCEPT;
		}

		M_DML::Update* upt = new M_DML::Update();
		upt->tableName = std::string($2);
		upt->attr_indexs = *$4;
		upt->condition = $5;
		upt->showInfo();
		
		//$$ = new Update();
		//$$->tableName = $2;
		//$$->attr_indexs = $4;
		//$$->condition = $5;
		//$$->showInfo();
		
		SqlGrammer sqlgrammer;
		//sqlgrammer.root = $$->transform2Grammer();
		sqlgrammer.root = upt->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		cout << "-------------------------------"<<endl;
		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		$$ = physicalPlan.root;
		
		cout<<endl;
		//YYACCEPT;
	}
	;

stmt
	: st_list fm_list
	{
		$$ = new M_DML::Query();
		$$->selList = $1;
		$$->fromList = $2;
	}
	| stmt wh_list
	{
		$1->condition = $2;
		$$ = $1;
	}
	| stmt order
	{
		$1->orderList = $2;
		$$ = $1;
	}
	;


st_list
	: ST st_nodes
	{
		$$ = $2;
	}
	;

st_nodes
	: name_list
	{
		$$ = new M_DML::SelList();
		for(int m=0;m<$1->size();m++){
			M_DML::Attribute* attr = new M_DML::Attribute();
			M_DML::Name* name = $1->at(m);
			attr->setName(name);
			$$->addAttribute(attr);
		}
	}
	| '*'
	{
		$$ = new M_DML::SelList();
		M_DML::Attribute* attr = new M_DML::Attribute();
		attr->attrName = "*";
		$$->addAttribute(attr);
	}
	| DISTINCT st_nodes
	{
        cout<<"distinct，暂不进行处理"<<endl;
	}
	;


fm_list
	: FM name_list
	{
		$$ = new M_DML::FromList();
		for(int m=0;m<$2->size();m++){
			M_DML::Relation* rl = new M_DML::Relation();
			rl->relationName = $2->at(m)->attrName;
			rl->alias = $2->at(m)->alias;
			$$->addNode(rl);
		}
	}
	| FM LF stmt RF
	{
        cout<<"子查询，暂不进行处理"<<endl;
	}
	;


wh_list
	: WH whname_list
	{
		$$ = $2;
	}
	;


whname_list
	: whname
	{
        //可能有多个condition
		$$ = $1;
	}
	| whname WHSPLIT whname_list 
	{
		M_DML::Condition* condition = new M_DML::Condition();
		condition->lCnode = $3;

		condition->soperator = $2;
		condition->rCnode = $1;
		$$ = condition;
	}
	;

whname
	: table_attr op whvalue
	{
        //【】op【】:a=b
		M_DML::Condition* condition = new M_DML::Condition();
		$$ = condition;
		M_DML::Attribute* lattr = new M_DML::Attribute();
		lattr->setName($1);
		condition->Lattr = lattr;

		int ttype = $3->type;
		if(ttype == NUMBER){
            
			condition->rNumber = $3->rNumber;
            
		}else if(ttype == PARA_STRING){
			
			condition->pString = $3->pString;
			
		}else if(ttype == NAME){

			M_DML::Attribute* rattr = new M_DML::Attribute();
			rattr->setName($3->name);
			condition->Rattr = rattr;
            
		}else if(ttype == SUBQUERY){
            //子查询
            condition->query = $3->query;
		}
		condition->soperator = $2;
	}
	;


whvalue
	: table_attr
	{
        //where a=【】,可为表名,数字，子查询
		$$ = new NodeStorage();
		$$->name = $1;
		$$->type = NAME;
	}
	| number
	{
		$$ = new NodeStorage();
		$$->rNumber = $1;
		$$->type = NUMBER;
	}
	| LF stmt RF
	{
		$$ = new NodeStorage();
		$$->query = $2;
		$$->type = SUBQUERY;

	}
	| para_string
	{
		$$ = new NodeStorage();
		$$->pString = $1;
		$$->type = PARA_STRING;
	}
	;

order
	: ORDER BY order_list
	{
		$$ = $3;
	}
	;

order_list
	: order_node
	{
		//可能有多个排序节点
		$$ = new M_DML::OrderList();
		$$->addOrderNode($1);
	}
	| order_node ',' order_list	
	{
		$3->addOrderNode($1);
		$$ = $3;
	}
	;

order_node
	: attr_name
	{
		//排序节点,可带rule也可不带
		$$ = new M_DML::OrderNode();
		$$->attr.setName($1->attrName,$1->tableName);
	}
	| attr_name ORTYPE
	{
		$$ = new M_DML::OrderNode();
		$$->attr.setName($1->attrName,$1->tableName);
		$$->rule = *$2;
	}
	;

name_list
   : table_attr
   {
		//名字列表
		$$ = new vector<M_DML::Name*>;
   		$$->push_back($1);
   }
   | table_attr ',' name_list 
   {
		$3->push_back($1);
   		$$ = $3;
   } 
   | table_attr NATURAL DML_JOIN name_list
   {
		M_DML::Name *name = new M_DML::Name();
		name->attrName = "@natural@";//@natural@作为指示符
        $4->push_back(name);
        $4->push_back($1);
        $$ = $4;
   }
   ;

table_attr
	: attr_name
	{
		$$ = $1;
	}
	| AGGRET LF attr_name RF
	{
		M_DML::Name* name = $3;
		name->aggFunc = *$1;
		$$ = name;
	}
	| table_attr NAME
	{
		M_DML::Name* name = $1;
		name->alias = std::string($2);
		$$ = name;
	}
	;

attr_name
	: NAME
	{
		M_DML::Name* name = new M_DML::Name();
		name->attrName = std::string($1);
		$$ = name;
	}
	| NAME '.' NAME
	{
		M_DML::Name* name = new M_DML::Name();
		name->tableName = std::string($1);
		name->attrName = std::string($3);

		$$ = name;
	}
	;
	
insert
	: IST INTO NAME VAL LF value_list RF
	{	
		if(!SqlGlobal::getInstance()->preCheck()){
			//未通过预判断
			YYACCEPT;
		}

		M_DML::Insert * insert = new M_DML::Insert();
		insert->attributes = *$6;
		insert->tableName = std::string($3);
		insert->showInfo();
		
		SqlGrammer sqlgrammer;
		sqlgrammer.root = insert->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		cout << "-------------------------------"<<endl;
		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		$$ = physicalPlan.root;

		cout<<endl;
	}
	;

value_list
	: insert_value
	{
		$$ = new vector<string>;
		$$->push_back(*$1);
	}
	| insert_value ',' value_list
	{
		$3->push_back(*$1);
		$$ = $3;
	}
	;

set_list
	: set_value
	{
		$$ = new map<string,string>;
		string **tmp = $1;
		$$->insert(pair<string, string>(*tmp[0], *tmp[1]));
	}
	| set_value ',' set_list
	{
		string **tmp = $1;
		$3->insert(pair<string,string>(*tmp[0],*tmp[1]));
		$$ = $3;
	}
	;

set_value
	: NAME T_EQ insert_value
	{		
		string** tmp = $$;
		string* pre = new string($1);
		tmp[0] = pre;
		tmp[1] = $3;
	}
	;  
	
insert_value
	: para_string
	{
		$$ = &$1->parameter;
	}
	| number
	{
		$$ = &$1->number;
	}
	;

para_string
	: '\'' NAME '\''
	{
		M_DML::ParaString* pstring = new M_DML::ParaString();
		pstring->parameter = "\'" + std::string($2) +"\'";
        $$ = pstring;
	}
	;

number
	: INTNUM
	{
		$$ = new M_DML::Number();
		$$->number = to_string($1);
	}
	| APPROXNUM
	{
		$$ = new M_DML::Number();
		$$->number = to_string($1);
	}
	;


	/* DDL */

DDL_commands:/*empty*/
			|DDL_commands DDL_command
			;

DDL_command:create_table_stmt
			|create_database
			|create_index
			|drop_stmt
			|alter_stmt
			;


	/*创建表*/
create_table_stmt
	: CREATE TABLE NAME LF create_col_list RF
	{
		//if(g_DD:Stmt.createtable->tablename == nullptr)
		set_node(DDL_SQL_TYPE::DDL_TYPE_CREATE_TABLE);
		g_DDLStmt.createtable->tablename = $3;
	}
	;

create_col_list
	: create_definition
	{
		$$ = 1; 
	}
	| create_col_list ',' create_definition
	{
		$$ = $1 + 1; 
	}
	;

create_definition
	: NAME data_type column_atts
	{ 
		ColDef newCol;
		strcopy($1,newCol.name);
		newCol.datatype = $2;
		dividetypes(newCol.constypes,$3);
		g_DDLStmt.createtable->cols.push_back(newCol);
	}
	| PRIMARY KEY LF column_list RF
	{ 
		vector<int> temp;
		divideToNum(temp,$4);
		for(int i = 0;i < temp.size();i++)
		{
			//g_DDLStmt.createtable->cols[temp[i]].constypes.push_back(DDL_CONS_TYPE::DDL_CONS_PRIKEY);
			int flag = DDL_CONS_TYPE::DDL_CONS_PRIKEY;
			g_DDLStmt.createtable->cols[temp[i]].constypes.push_back(flag);
		}
	}
	;

column_list
	: NAME 
	{ 
		for(int i = 0;i < g_DDLStmt.createtable->cols.size();i++)
		{
			if(strcmp(g_DDLStmt.createtable->cols[i].name,$1) == 0)
			{
				$$ = pow(2,i);break;
			}
		}
	}
  | column_list ',' NAME  
	{ 
		for(int i = 0;i < g_DDLStmt.createtable->cols.size();i++)
		{
			if(strcmp(g_DDLStmt.createtable->cols[i].name,$3) == 0)
			{
				int temp = pow(2,i);
				$$ = $1 + temp;break;
			}
		}
	}
    ;

column_atts
	: /* 空属性 */ { $$ = 0; }
	| column_atts NOT NULLX		{ $$ = $1 + DDL_CONS_TYPE::DDL_CONS_NOTNULL; }
	| column_atts PRIMARY KEY	{ $$ = $1 + DDL_CONS_TYPE::DDL_CONS_PRIKEY;}
	| column_atts UNIQUE		{ $$ = $1 + DDL_CONS_TYPE::DDL_CONS_UNIQUE;}
	;

	/*等会再加*/
data_type
	: DDL_INT	{ $$ = DDL_DATA_TYPE::DDL_INT; }
	| REAL	{ $$ = DDL_DATA_TYPE::DDL_REAL; }
	| TEXT	{ $$ = DDL_DATA_TYPE::DDL_TEXT; }
	;

	/*创建数据库*/
create_database
		: CREATE DATABASE NAME
		{
			set_node(DDL_SQL_TYPE::DDL_TYPE_CREATE_DATABASE);
			strcopy($3,g_DDLStmt.createdatabase->databasename);
		}
		;

	/*创建索引*/
create_index
			: CREATE INDEX NAME ON NAME
			{
				set_node(DDL_SQL_TYPE::DDL_TYPE_CREATE_INDEX);
				strcopy($3,g_DDLStmt.createindex->indexname);
				strcopy($5,g_DDLStmt.createindex->tablename);
			}
			| CREATE INDEX NAME ON NAME LF col_list_index RF
			{
				set_node(DDL_SQL_TYPE::DDL_TYPE_CREATE_INDEX);
				strcopy($3,g_DDLStmt.createindex->indexname);
				strcopy($5,g_DDLStmt.createindex->tablename);
			}
			;

col_list_index
			: NAME 
			{
				g_DDLStmt.createindex->colnames.push_back($1);
			}
			| col_list_index ',' NAME  
			{ 
				g_DDLStmt.createindex->colnames.push_back($3);
			}
			;
		
	/*Drop*/
drop_stmt
		: DROP TABLE NAME
		{
			set_node(DDL_SQL_TYPE::DDL_TYPE_DROP);
			g_DDLStmt.dropstmt->dropType = DROPTYPE::TABLE;
			strcopy($3,g_DDLStmt.dropstmt->dropname);
		}
		| DROP DATABASE NAME
		{
			set_node(DDL_SQL_TYPE::DDL_TYPE_DROP);
			g_DDLStmt.dropstmt->dropType = DROPTYPE::DATABASE;
			strcopy($3,g_DDLStmt.dropstmt->dropname);
		}
		;

	/*ALTER*/
alter_stmt
		: ALTER TABLE NAME alter_behind
		{
			set_node(DDL_SQL_TYPE::DDL_TYPE_ALTER);
			strcopy($3,g_DDLStmt.alterstmt->tablename);
		}
		;
alter_behind
		: DROP CONSTRAINT NAME
		{
			g_DDLStmt.alterstmt->altertype = ALTERTYPE::DROP_CONSTRAINT;
			strcopy($3,g_DDLStmt.alterstmt->constraintname);
		}
		| ADD NAME data_type
		{
			g_DDLStmt.alterstmt->altertype = ALTERTYPE::ADD_COL;
			ColDef newCol;
			strcopy($2,newCol.name);
			newCol.datatype = $3;
			g_DDLStmt.alterstmt->cols.push_back(newCol);
		}
		| DROP COLUMN NAME
		{
			g_DDLStmt.alterstmt->altertype = ALTERTYPE::DROP_COL;
			ColDef newCol;
			strcopy($3,newCol.name);
			g_DDLStmt.alterstmt->cols.push_back(newCol);
		}
		| ALTER COLUMN NAME TYPE data_type
		{
			g_DDLStmt.alterstmt->altertype = ALTERTYPE::ALTER_COL;
			ColDef newCol;
			strcopy($3,newCol.name);
			newCol.datatype = $5;
			g_DDLStmt.alterstmt->cols.push_back(newCol);
		}
		| MODIFY NAME data_type column_atts
		{
			g_DDLStmt.alterstmt->altertype = ALTERTYPE::MODIFY_COL;
			g_DDLStmt.alterstmt->modifytype = $4;
			ColDef newCol;
			strcopy($2,newCol.name);
			newCol.datatype = $3;
			g_DDLStmt.alterstmt->cols.push_back(newCol);
		}
		| ADD CONSTRAINT NAME UNIQUE LF col_list_alter RF
		{
			g_DDLStmt.alterstmt->altertype = ALTERTYPE::ADD_CONSTRAINT;
			strcopy($3,g_DDLStmt.alterstmt->constraintname);
			g_DDLStmt.alterstmt->constrainttype = DDL_CONS_TYPE::DDL_CONS_UNIQUE;
		}
		| ADD CONSTRAINT NAME PRIMARY KEY LF col_list_alter RF
		{
			g_DDLStmt.alterstmt->altertype = ALTERTYPE::ADD_CONSTRAINT;
			strcopy($3,g_DDLStmt.alterstmt->constraintname);
			g_DDLStmt.alterstmt->constrainttype = DDL_CONS_TYPE::DDL_CONS_PRIKEY;
		}
		;

col_list_alter
		: NAME
		{
			ColDef newCol;
			strcopy($1,newCol.name);
			g_DDLStmt.alterstmt->cols.push_back(newCol);
		}
		| col_list_alter ',' NAME
		{
			ColDef newCol;
			strcopy($3,newCol.name);
			g_DDLStmt.alterstmt->cols.push_back(newCol);
		}
		;

op
	: T_LT
	{
		$$ = $1;
	}
	| T_LE
	{
		$$ = $1;
	}
	| T_GT
	{
		$$ = $1;
	}
	| T_GE
	{
		$$ = $1;
	}
	| T_EQ
	{
		$$ = $1;
	}
	| T_NE
	{
		$$ = $1;
	}
	| IN
	{
		$$ = $1;
	}
	;
 
%%

/*DML*/

int parser_dml_sql(string sql){

	yy_switch_to_buffer(yy_scan_string(sql.c_str()));
	if(yyparse())
		return -1;
	else{
		return 1;
	}
}

string getInputSql(){
	//获取输入的sql语句
	string sql;
	getline(cin, sql);
    while (sql.empty()) {
        getline(cin, sql);
    }
	while (sql.back() != ';') {
		string tmp;
		getline(cin, tmp);
		sql += " " + tmp;
	}
	return sql;
}

/* DDL */
//解析成功返回1，解析不成功返回-1
int parser_ddl_sql(string sql){

    //由于会重复调用此函数，因此先释放已申请的空间
    delete g_DDLStmt.createdatabase;
    delete g_DDLStmt.createindex;
    delete g_DDLStmt.createtable;
    delete g_DDLStmt.dropstmt;
    delete g_DDLStmt.alterstmt;

	//在解析之前，先申请空间
	g_DDLStmt.createtable = new CreateTableStmt;
	g_DDLStmt.createdatabase = new CreateDatabaseStmt;
	g_DDLStmt.createindex = new CreateIndex;
	g_DDLStmt.dropstmt = new DropStmt;
	g_DDLStmt.alterstmt = new AlterStmt;

	yy_switch_to_buffer(yy_scan_string(sql.c_str()));
	if(yyparse())
		return -1;
	else{
		return 1;
	}
}

//为g_DDLStmt申请结点空间,好像我已经把申请空间放外边了，直接全申请了，这个已经鸡肋了
void set_node(int type){
	g_DDLStmt.stmttype = type;
	//switch(type){
	//	case DDL_TYPE_CREATE_TABLE:
	//		//g_DDLStmt.createtable = new CreateTableStmt;  直接在外面申请所有的空间
	//		break;
	//	case DDL_TYPE_CREATE_DATABASE:
	//		break；
	//	default:
	//		cout<<"申请结点空间时出错"<<endl;break;
	//}
}

//将一个数据类型和拆分成一个个类型
void dividetypes(vector<int>& v,int sum){
	//首先将num转换成二进制
    vector<int> binaryint;
    while(1){
        binaryint.push_back((sum%2));
        if(sum/2 == 0) break;
        else sum = sum/2;
    }
	//得到了二进制的倒序
	for(int i = 0;i < binaryint.size();i++){
		if(binaryint[i] == 0) continue;
		v.push_back(pow(2,i));
	}
}

void divideToNum(vector<int>& v,int sum){
	//首先将num转换成二进制
    vector<int> binaryint;
    while(1){
        binaryint.push_back((sum%2));
        if(sum/2 == 0) break;
        else sum = sum/2;
    }
	//得到了二进制的倒序
	for(int i = 0;i < binaryint.size();i++){
		if(binaryint[i] == 0) continue;
		v.push_back(i);
	}
}