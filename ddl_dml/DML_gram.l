%{
#include "DDL_public.h"
#include "Node.h"
#include "SqlGlobal.h"
#include "DML_gram.tab.h"

SqlGlobal* sg = SqlGlobal::getInstance();
void strcopy(char*& src,char*& dest);
%}

st              (select|SELECT|Select)
upt             (update|UPDATE|Update)
del             (delete|DELETE|Delete)
ist             (insert|INSERT|Insert)
val             (values|VALUES)
into            (into|INTO)
set             (set|SET)
natural         (natural|NATURAL)
join            (join|JOIN)
multi			(multi)
exec            (exec)
discard         (discard)


fm              (from|FROM|From)
order			(order|ORDER|Order)
by              (by|BY|By)
ortype          (desc|asc|DESC|ASC)            
wh              (where|WHERE|Where)
whsplit         (and|AND|or|OR|Or|And)
dis				(distinct)
aggret			(sum|max|min|avg|mean|SUM|MAX|MIN|AVG|MEAN)
exit			(exit|EXIT)
use             (use|USE)

whitespace      [ \n\t]

%%
    /* ddl */
	/*¹Ø¼ü×Ö*/
create|CREATE   {
                    return CREATE; 
                }
table|TABLE     {   
                    return TABLE;
                }
primary|PRIMARY {
                    return PRIMARY;
                }
key|KEY	        {
                    return KEY;
                }
not|NOT         {
                    return NOT;
                }
null|NULL       {
                    return NULLX;
                }
int|INT	        {
                    return DDL_INT;
                }
real|REAL       {   
                    return REAL;
                }
text|TEXT       {
                    return TEXT;
                }
database|DATABASE {
                    return DATABASE;
                  }

drop|DROP      {
                    return DROP;
                }

alter|ALTER     {
                    return ALTER;
                 }

index|INDEX     {
                    return INDEX;
                }

column|COLUMN   {
                    return COLUMN;
                }

constraint|CONSTRAINT {
                            return CONSTRAINT;
                       }

add|ADD         {
                    return ADD;
                }

modify|MODIFY   {
                    return MODIFY;
                 }

type|TYPE       {
                    return TYPE;
                }

unique|UNIQUE   {
                    return UNIQUE;
                }

on|ON           {
                    return ON;
                }

	/*Êý×Ö*/
-?[0-9]+	{
                yylval.intval = atoi(yytext);  
                return INTNUM; 
            } 

-?[0-9]+"."[0-9]* |
-?"."[0-9]+	|
-?[0-9]+E[-+]?[0-9]+	|
-?[0-9]+"."[0-9]*E[-+]?[0-9]+ |
-?"."[0-9]*E[-+]?[0-9]+	{

                 yylval.floatval = atof(yytext) ;
                 return APPROXNUM; 
            }

    /*Bool*/
TRUE	    {
                yylval.intval = 1; 
                return BOOL; 
            }

UNKNOWN	    { 
                yylval.intval = -1; 
                return BOOL; 
            }

FALSE	    { 
                yylval.intval = 0; 
                return BOOL; 
            }


"&&"		{ 
                return ANDOP; 
            }

"||"        { 
                return DDL_OR; 
            }


"("			{
				return LF;
			}
			
")"			{
				return RF;
			}

{st}        {
                return ST;
            }

{fm}        {
                return FM;
            }

{wh}        {
                return WH;
            }
{ist}		{
				return IST;
			}
{upt}		{
				return UPT;
			}
{del}		{
				return DEL;
			}
{set}		{
				return SET;
			}
{val}		{
				return VAL;
			}
{into}		{
				return INTO;
			}

{use}       {
                return USE;
            }
            
{whsplit}   {
                yylval.soperator = new M_DML::Operator();
                yylval.soperator->opName = yytext;
                return WHSPLIT;
            }


"<"         {
                yylval.soperator = new M_DML::Operator();
                yylval.soperator->opName = yytext;
                return T_LT;
            }

"<="        {
                yylval.soperator = new M_DML::Operator();
                yylval.soperator->opName = yytext;
                return T_LE;
            }

">"         {
                yylval.soperator = new M_DML::Operator();
                yylval.soperator->opName = yytext;
                return T_GT;
            }

">="        {
                yylval.soperator = new M_DML::Operator();
                yylval.soperator->opName = yytext;
                return T_GE;
            }

"="         {
                yylval.soperator = new M_DML::Operator();
                yylval.soperator->opName = yytext;
                return T_EQ;
            }

"!="        {
                yylval.soperator = new M_DML::Operator();
                yylval.soperator->opName = yytext;
                return T_NE;
            }

"<>"        {
                yylval.soperator = new M_DML::Operator();
                yylval.soperator->opName = yytext;
                return T_NE;
            }

"in"		{
                yylval.soperator = new M_DML::Operator();
                yylval.soperator->opName = yytext;
                return IN;
			}


{whitespace}    ;


{order}    {
                return ORDER;
           }
           
{by}       {
                return BY;
           }
           
{ortype}   {
                yylval.text = new string(yytext);
                return ORTYPE;
           }
           
{dis}      {

				return DISTINCT;
		   }
		   
{aggret}	{
                yylval.text = new string(yytext);
                return AGGRET;
			}
			
{exit}		{
                sg->exit = true;
				return EXIT;
			}	
			
{natural}  {
				return NATURAL;
		   }
		   
{join}	   {
				return DML_JOIN;
		   }	
			
{multi}		{
				return MULTI;
			}
{exec}		{
				return EXEC;
			}
{discard}	{
				return DISCARD;
			}

	/*NAME*/
[A-Za-z][A-Za-z0-9_]*  {
            strcopy(yytext,yylval.strval);
            return NAME; 
        }

        	/*²Ù×÷·û*/
[*/+\-=<>':;,.|&()]  {return yytext[0];}
           
.			;
 
%%
int yyerror(const char * format,...){
	printf("You have an error in your SQL syntax;\n");
	return 1;
}
 
int yywrap(void)
{  
  return 1;  
} 

void strcopy(char*& src,char*& dest){
    dest = (char*)malloc(sizeof(char*)*(strlen(src)+1));
    //dest = new char[strlen(src)+1];
    strcpy(dest,src);
}