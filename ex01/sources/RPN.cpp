#include "../includes/RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <iostream>

// Evaluates a Reverse Polish Notation expression
int RPN::evaluatePostfix(const std::string& expr) {
    std::stack<int> stack;
    std::istringstream iss(expr);
    std::string token;
    while (iss >> token) {
        if (token.length() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
            // Operator: need at least two operands
            if (stack.size() < 2)
                throw std::runtime_error("Error");
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            int result = 0;
            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0)
                        throw std::runtime_error("Error");
                    result = a / b;
                    break;
            }
            stack.push(result);
        } else if (token.length() == 1 && isdigit(token[0]) && token[0] >= '0' && token[0] <= '9') {
            // Operand: single digit
            stack.push(token[0] - '0');
        } else {
            throw std::runtime_error("Error");
        }
    }
    if (stack.size() != 1)
        throw std::runtime_error("Error");
    return stack.top();
}
