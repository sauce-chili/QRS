#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QList>
#include "entities/ExprNodeImpl/ArithmeticNode.h"
#include "entities/ExprNodeImpl/LogicalNode.h"

using namespace std;


int main() {
    LogicalNodeAND andOpr(nullptr, nullptr);
    ArithmeticNode plusOpr(EXPR_NODE_TYPE::PLUS, BuilderUtil().getPriorityLvl(EXPR_NODE_TYPE::PLUS),
                   BuilderUtil().getPriorityLvl(EXPR_NODE_TYPE::PLUS), nullptr, nullptr);

    bool isEqual = plusOpr == andOpr;
    return 0;
}

//int main(int argc, char *argv[]) {
//    int n1 = 1;
//    int n2 = 2;
//    int n4 = 4;
//    B b1(&n1, &n2);
//    B b2(&n1, &n4);
////    A &a = b2;
//    C c(&n4);
//    A &a = b1;
//    B& b0 = dynamic_cast<B &>(a);
//    try {
//        cout << (bool) (b1 == dynamic_cast<B &>(a)) << endl;
//    }
//    catch (std::bad_cast b) {
//        cout << b.what() << endl;
//    }

//    int x = (5 * (2 << 4));
//    int y = ((5 * 2) << (5 * 4));
//    cout << (bool) (x == y);
//    cout << ((10 % (2 * 3)) == ((10 % 2) * (10%3))) << endl;
//    return 0;
//}
