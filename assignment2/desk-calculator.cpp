#include <iostream>
#include <stack>
using namespace std;

stack<char> operators, operands;

bool push(char d) {
    if (operators.empty()) {
        return true;
    }
    char c = operators.top();
    if (c == '+') {
        if (d == '-') {
            return false;
        }
    }
    if (c == '*') {
        if (d == '+' || d == '-') {
            return false;
        }
    }
    if (c == '/') {
        if (d == '+' || d == '-' || d == '*') {
            return false;
        }
    }
    return true;
}

void operation(int n1, int n2, char c) {
    if (c == '+') {
        operands.push(n1+n2 + 48);
    } else if (c == '*') {
        operands.push(n1*n2 + 48);
    } else if (c == '-') {
        operands.push(n1-n2 + 48);
    } else if (c == '/') {
        operands.push(n1/n2 + 48);
    }
}

int calculate(string s) {
    for (int i=s.length()-1;i>=0;i--) {
        if (s[i] == '+' || s[i] == '*' || s[i] == '-' || s[i] == '/') {
            if (push(s[i])) {
                operators.push(s[i]);
                continue;
            } else {
                while (!push(s[i])) {
                    int n1 = operands.top() - '0';
                    operands.pop();
                    char c = operators.top();
                    operators.pop();
                    int n2 = operands.top() - '0';
                    operands.pop();
                    operation(n1, n2, c);
                }
                operators.push(s[i]);
            }
        } else {
            operands.push(s[i]);
        }
    }
    while (!operators.empty()) {
        char c = operators.top();
        operators.pop();
        int n1 = operands.top() - '0';
        operands.pop();
        int n2 = operands.top() - '0';
        operands.pop();
        operation(n1, n2, c);
    }
    return operands.top() - '0';
}

// simple calculator
int main() {
	string s;
	cin>>s;
	cout<<calculate(s)<<endl;
	return 0;
}
