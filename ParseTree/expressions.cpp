#include "expressions.h"

Operator::Operator(const std::string& op) : op(op) {}
std::string Operator::getOp() const {
    return op;
}

// Literal<int> implementation
Literal<int>::Literal(int value) : value(value) {}
    
int Literal<int>::operator+(const Literal<int>& literal) const {
    return value + literal.value;
}
int Literal<int>::operator-(const Literal<int>& literal) const {
    return value - literal.value;
}

int Literal<int>::evaluateInt() const {
    return value;
}
int Literal<int>::getValue() const {
    return value;
}

// Literal<bool> implementation
Literal<bool>::Literal(bool value) : value(value) {}

bool Literal<bool>::evaluateBool() const {
    return value;
}

// BinaryExpression implementation
BinaryExpression::BinaryExpression(Expression* e1, Operator* op, Expression* e2)
    : e1(e1), op(op), e2(e2) {}

BinaryExpression::~BinaryExpression() {
    delete e1;
    delete e2;
    delete op;
}

    bool BinaryExpression::evaluateBool() const {
        throw std::runtime_error("Invalid unary operation");
    }

    int BinaryExpression::evaluateInt() const {
        throw std::runtime_error("Invalid unary operation");
    }



EqExp::EqExp(Expression* e1, Operator* op, Expression* e2)
    : BinaryExpression(e1, op, e2) {}

bool EqExp::evaluateBool() const  {
    
    if (op->getOp() == "==" || op->getOp() == "!=") {
        try {
            bool leftBool = e1->evaluateBool();
            bool rightBool = e2->evaluateBool();
            if (op->getOp() == "==") {
                return leftBool == rightBool;
            } else {
                return leftBool != rightBool;
            }
        } catch (const std::runtime_error&) {
            try { 
                int leftInt = e1->evaluateInt();
                int rightInt = e2->evaluateInt();
                if (op->getOp() == "==") {
                    return leftInt == rightInt;
                } else {
                    return leftInt != rightInt;
                }
            } catch (const std::runtime_error&) {
                throw std::runtime_error("Invalid operation");
            }
        }
    }

    throw std::runtime_error("Invalid operation");
}

AndExp::AndExp(Expression* e1, Operator* op, Expression* e2)
    : BinaryExpression(e1, op, e2) {}

bool AndExp::evaluateBool() const {
    if (op->getOp() == "&&") {
        return e1->evaluateBool() && e2->evaluateBool();
    }
    throw std::runtime_error("Invalid operation");
}

OrExp::OrExp(Expression* e1, Operator* op, Expression* e2)
    : BinaryExpression(e1, op, e2) {}

bool OrExp::evaluateBool() const {
    if (op->getOp() == "||") {
        return e1->evaluateBool() || e2->evaluateBool();
    }
    throw std::runtime_error("Invalid operation");
}

RelExp::RelExp(Expression* e1, Operator* op, Expression* e2)
    : BinaryExpression(e1, op, e2) {}

bool RelExp::evaluateBool() const {
    if (op->getOp() == "<") {
        return e1->evaluateInt() < e2->evaluateInt();
    } else if (op->getOp() == ">") {
        return e1->evaluateInt() > e2->evaluateInt();
    } else if (op->getOp() == "<=") {
        return e1->evaluateInt() <= e2->evaluateInt();
    } else if (op->getOp() == ">=") {
        return e1->evaluateInt() >= e2->evaluateInt();
    }
    throw std::runtime_error("Invalid operation");
}

AddExp::AddExp(Expression* e1, Operator* op, Expression* e2)
    : BinaryExpression(e1, op, e2) {}



int AddExp::evaluateInt() const {
    try {
        int Value = e1->evaluateInt();
        int Value2 = e2->evaluateInt();
        if (op->getOp() == "+") {
            return Value + Value2;
        } else if (op->getOp() == "-") {
            return Value - Value2;
        }
    } catch (const std::runtime_error&) {
        throw std::runtime_error("Incompatible operands");
    }

    throw std::runtime_error("Invalid operation");
}

MulExp::MulExp(Expression* e1, Operator* op, Expression* e2)
    : BinaryExpression(e1, op, e2) {}

int MulExp::evaluateInt() const {
    if (op->getOp() == "*") {
        return e1->evaluateInt() * e2->evaluateInt();
    } else if (op->getOp() == "/") {
        int divisor = e2->evaluateInt();
        if (divisor == 0) {
            throw std::runtime_error("Division by zero");
        }
        return e1->evaluateInt() / divisor;
    }
    throw std::runtime_error("Invalid operation");
}

UnaryExpression::UnaryExpression(Expression* e, Operator* op)
    : e(e), op(op) {}

UnaryExpression::~UnaryExpression() {
    delete e;
    delete op;
}

int UnaryExpression::evaluateInt() const {
    int value = e->evaluateInt();
    if (op->getOp() == "-") {
        return -value;
    }
    throw std::runtime_error("Invalid unary operation");
}


ParenthesesExpression::ParenthesesExpression(Expression* e)
    : e(e) {}

ParenthesesExpression::~ParenthesesExpression() {
    delete e;
}

int ParenthesesExpression::evaluateInt() const {
    return e->evaluateInt();
}
bool ParenthesesExpression::evaluateBool() const {
    return e->evaluateBool();
}