#include "parser.h"
#include <stdexcept>
#include <iostream>

Parser::Parser(const std::string& expression) : stream(expression), current_token("") {
    next_token();
}

std::string Parser::curToken() const {
    return current_token;
}

bool Parser::balancedParentheses(const std::string& expr) {
    int count = 0;
    for (char c : expr) {
        if (c == '(') {
            count++;
        } else if (c == ')') {
            count--;
            if (count < 0) {
                return false;
            }
        }
    }
    return count == 0;
}

//Separa os tokens
std::string Parser::tokenizer() {
    char c;

    while (stream.get(c) && std::isspace(c)) {}
        
        //para o loop se o arquivo acabar
        if (stream.eof()) {
            return "";
        }

        if (std::isdigit(c) || std::isalpha(c)) {
            
            std::string token(1, c);
            while (stream.peek() != EOF && std::isalnum(stream.peek())) {
                token += static_cast<char>(stream.get());
            }
            return token; 

        }

        //create token for parentheses and operators
        if (c == '(' || c == ')') {
            return std::string(1, c);
        }

        //to handle sequential operators
        std::string op(1, c);
        if (stream.peek() != EOF) {
            char next = static_cast<char>(stream.peek());
            if ((op == "=" && next == '=') ||
                (op == "|" && next == '|') ||
                (op == "&" && next == '&') ||
                (op == "!" && next == '=') ||
                (op == "<" && next == '=') ||
                (op == ">" && next == '=')) {
                stream.get();
                return op + next;
            }
        }
        return op;
}

void Parser::valid_token(){
    if(!current_token.empty() &&
        current_token != ")" &&
        current_token != "&&" &&
        current_token != "||" &&
        current_token != "==" &&
        current_token != "!=" &&
        current_token != "<" &&
        current_token != ">" &&
        current_token != "<=" &&
        current_token != ">=" &&
        current_token != "+" &&
        current_token != "-" &&
        current_token != "*" &&
        current_token != "/")
        {
        throw std::runtime_error("Invalid token");
        }
}



//Inicializa o parser
Expression* Parser::parse_exp() {
    return or_exp();
}

Expression* Parser::or_exp() {
    Expression* e1 = and_exp();
    if (current_token == "||") {
        Operator* op = new Operator(current_token);
        next_token();
        Expression* e2 = and_exp();
        e1 = new OrExp(e1, op, e2);
    }
    return e1;
}

Expression* Parser::and_exp() {
    Expression* e1 = eq_exp();
    while (current_token == "&&") {
        Operator* op = new Operator(current_token);
        next_token();
        Expression* e2 = eq_exp();
        e1 = new AndExp(e1, op, e2);
    }
    return e1;
}

Expression* Parser::eq_exp() {
    Expression* e1 = rel_exp();
    while (current_token == "==" || current_token == "!=") {
        Operator* op = new Operator(current_token);
        next_token();
        Expression* e2 = rel_exp();
        e1 = new EqExp(e1, op, e2);
    }
    return e1;
}

Expression* Parser::rel_exp() {
    Expression* e1 = add_exp();
    while (current_token == "<" || current_token == ">" ||
        current_token == "<=" || current_token == ">=") {
        Operator* op = new Operator(current_token);
        next_token();
        Expression* e2 = add_exp();
        e1 = new RelExp(e1, op, e2);
    }
    return e1;
}

Expression* Parser::add_exp() {
    Expression* e1 = mul_exp();
    while (current_token == "+" || current_token == "-") {
        Operator* op = new Operator(current_token);
        next_token();
        Expression* e2 = mul_exp();
        e1 = new AddExp(e1, op, e2);
    }
    return e1;
}

Expression* Parser::mul_exp() {
    
    Expression* e1 = unary_exp();
    while (current_token == "*" || current_token == "/") {
        Operator* op = new Operator(current_token);
        next_token();
        Expression* e2 = unary_exp();
        e1 = new MulExp(e1, op, e2);
    }
    return e1;
}

Expression* Parser::unary_exp() {
    if (current_token == "-") {
        Operator* op = new Operator(current_token);
        next_token();
        return new UnaryExpression(unary_exp(), op);
    }
    return primary_exp();
}


Expression* Parser::primary_exp() {
    if (current_token == "(") {
        next_token();
        Expression* e = parse_exp();
        if (current_token == ")") {
            next_token();
        }
        return new ParenthesesExpression(e); 
    }

    std::string token = current_token;
    next_token();
    if (token == "true") {
        return new Literal<bool>(true);
    } else if (token == "false") {
        return new Literal<bool>(false);
    } else {
        int value = std::stoi(token);
        return new Literal<int>(value);
    }
}