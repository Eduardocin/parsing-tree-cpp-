#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <string>
#include <stdexcept>

class Expression {
public:
    virtual ~Expression() {}
    virtual int evaluateInt() const {
        throw std::runtime_error("invalid operation");
    }
    virtual bool evaluateBool() const {
        throw std::runtime_error("invalid operation");
    }
};

class Operator {
private:
    std::string op;
public:
    Operator(const std::string& op);
    std::string getOp() const;
};

template<typename T>
class Literal : public Expression {
public:
    Literal(T value) : value(value) {}
    int evaluateInt() const override {
        throw std::runtime_error("invalid operation");
    }
    bool evaluateBool() const override {
        throw std::runtime_error("invalid operation");
    }
    
private:
    T value;
};

template<>
class Literal<int> : public Expression {
protected:
    int value;
public:
    Literal(int value);
    int operator+(const Literal<int>& literal) const;
    int operator-(const Literal<int>& literal) const;
    int evaluateInt() const override;
    int getValue() const;
};

template<>
class Literal<bool> : public Expression {
private:
    bool value;
public:
    Literal(bool value);
    bool evaluateBool() const override;
};

class BinaryExpression : public Expression {
protected:
    Expression* e1;
    Operator* op;
    Expression* e2;
public:
    BinaryExpression(Expression* e1, Operator* op, Expression* e2);
    virtual ~BinaryExpression();
    bool evaluateBool() const override;
    int evaluateInt() const override;
};

class EqExp : public BinaryExpression {
public:
    EqExp(Expression* e1, Operator* op, Expression* e2);
    bool evaluateBool() const override;
};

class AndExp : public BinaryExpression {
public:
    AndExp(Expression* e1, Operator* op, Expression* e2);
    bool evaluateBool() const override;
};

class OrExp : public BinaryExpression {
public:
    OrExp(Expression* e1, Operator* op, Expression* e2);
    bool evaluateBool() const override;
};

class RelExp : public BinaryExpression {
public:
    RelExp(Expression* e1, Operator* op, Expression* e2);
    bool evaluateBool() const override;
};

class AddExp : public BinaryExpression {
public:
    AddExp(Expression* e1, Operator* op, Expression* e2);
    int evaluateInt() const override;
};

class MulExp : public BinaryExpression {
public:
    MulExp(Expression* e1, Operator* op, Expression* e2);
    int evaluateInt() const override;
};

class UnaryExpression : public Expression {
protected:
    Expression* e;
    Operator* op;
public:
    UnaryExpression(Expression* e, Operator* op);
    ~UnaryExpression() override;
    int evaluateInt() const override;
};

class ParenthesesExpression : public Expression {
protected:
    Expression* e;
public:
    ParenthesesExpression(Expression* e);
    ~ParenthesesExpression() override;
    
    int evaluateInt() const override;
    bool evaluateBool() const override;
};

#endif