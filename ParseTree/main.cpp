#include <iostream>
#include <limits>
#include <stdexcept>
#include "parser.h"
#include "expressions.h"

using namespace std;

int main() {
    int num_inputs;
    cin >> num_inputs;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    while (num_inputs--) {
        string expression;
        getline(cin, expression);

        try {
            if (!Parser::balancedParentheses(expression)) {
                throw runtime_error("Unbalanced parentheses");
            }

            Parser parser(expression);
            Expression* exp = parser.parse_exp();
            
            try {
                int intResult = exp->evaluateInt();
                cout << intResult << endl;
            } 
            catch (const runtime_error&) {
                try {
                    bool boolResult = exp->evaluateBool();
                    cout << boolalpha << boolResult << endl;
                } 
                catch (const runtime_error&) {
                    cout << "error" << endl;
                }
            }
            delete exp;
        }
        catch (const exception&) {
            cout << "error" << endl;
        }
    }
    
    return 0;
}