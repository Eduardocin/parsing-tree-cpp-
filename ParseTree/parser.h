#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <sstream>
#include "expressions.h"

class Parser {
private:
    std::istringstream stream;
    std::string current_token;

    std::string tokenizer();
    void next_token() { current_token = tokenizer(); }
    void valid_token();

    Expression* or_exp();
    Expression* and_exp();
    Expression* eq_exp();
    Expression* rel_exp();
    Expression* add_exp();
    Expression* mul_exp();
    Expression* unary_exp();
    Expression* primary_exp();

public:

    Parser(const std::string& expression);
    ~Parser() = default;
    static bool balancedParentheses(const std::string& expr);
    Expression* parse_exp();
    std::string curToken() const;
};

#endif
