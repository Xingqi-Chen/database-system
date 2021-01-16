#ifndef EXECUTE_GLOBAL_H
#define EXECUTE_GLOBAL_H

#include <string>
#include "../parser.h"
#include "../global.h"
using namespace std;


// 用于处理解析的结果，对应 attrNmae compOp value
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
