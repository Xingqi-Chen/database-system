#ifndef EXECUTE_GLOBAL_H
#define EXECUTE_GLOBAL_H

#include <string>
#include "../parser.h"
#include "../global.h"
using namespace std;


// ���ڴ�������Ľ������Ӧ attrNmae compOp value
typedef struct Resolution_ {
	string attrName;
    CompOp compOp;
	Value value;
	void show()
    {
        cout << "attrName:" << attrName << endl;
        cout << "Value:" << value;
        cout << "compOp:" << compOp << endl;
        cout << "--------------";
    }
}Resolution;


enum Operator { AND = 1, OR };

#endif // !EXECUTE_GLOBAL_H
