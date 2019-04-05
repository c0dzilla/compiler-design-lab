/**
    LR parser with for given grammar
*/
#include <iostream>
#include <cstdio>
#include <map>
#include <stack>
#include <string>

#define INT_MAX 1000000000

using namespace std;

void fillRules(pair<char, string> rules[6]) {
    rules[0] = make_pair('E', "E+T");
    rules[1] = make_pair('E', "T");
    rules[2] = make_pair('T', "T*F");
    rules[3] = make_pair('T', "F");
    rules[4] = make_pair('F', "(E)");
    rules[5] = make_pair('F', "i");
}

void generateTable(map<char, pair<char, int> > action[12], map<char, int> go[12]) {
    action[0]['i'] = make_pair('s', 5);
    action[0]['+'] = make_pair('e', 0);
    action[0]['*'] = make_pair('e', 0);
    action[0]['('] = make_pair('s', 4);
    action[0][')'] = make_pair('e', 0);
    action[0]['$'] = make_pair('e', 0);
    
    action[1]['i'] = make_pair('e', 0);
    action[1]['+'] = make_pair('s', 6);
    action[1]['*'] = make_pair('e', 0);
    action[1]['('] = make_pair('e', 0);
    action[1][')'] = make_pair('e', 0);
    action[1]['$'] = make_pair('a', 0);

    action[2]['i'] = make_pair('e', 0);
    action[2]['+'] = make_pair('r', 2);
    action[2]['*'] = make_pair('s', 7);
    action[2]['('] = make_pair('e', 0);
    action[2][')'] = make_pair('r', 2);
    action[2]['$'] = make_pair('r', 2);

    action[3]['i'] = make_pair('e', 0);
    action[3]['+'] = make_pair('r', 4);
    action[3]['*'] = make_pair('r', 4);
    action[3]['('] = make_pair('e', 0);
    action[3][')'] = make_pair('r', 4);
    action[3]['$'] = make_pair('r', 4);

    action[4]['i'] = make_pair('s', 5);
    action[4]['+'] = make_pair('e', 0);
    action[4]['*'] = make_pair('e', 0);
    action[4]['('] = make_pair('s', 4);
    action[4][')'] = make_pair('e', 0);
    action[4]['$'] = make_pair('e', 0);

    action[5]['i'] = make_pair('e', 0);
    action[5]['+'] = make_pair('r', 6);
    action[5]['*'] = make_pair('r', 6);
    action[5]['('] = make_pair('e', 0);
    action[5][')'] = make_pair('r', 6);
    action[5]['$'] = make_pair('r', 6);

    action[6]['i'] = make_pair('s', 5);
    action[6]['+'] = make_pair('e', 0);
    action[6]['*'] = make_pair('e', 0);
    action[6]['('] = make_pair('s', 4);
    action[6][')'] = make_pair('e', 0);
    action[6]['$'] = make_pair('e', 0);

    action[7]['i'] = make_pair('s', 5);
    action[7]['+'] = make_pair('e', 0);
    action[7]['*'] = make_pair('e', 0);
    action[7]['('] = make_pair('s', 4);
    action[7][')'] = make_pair('e', 0);
    action[7]['$'] = make_pair('e', 0);

    action[8]['i'] = make_pair('e', 0);
    action[8]['+'] = make_pair('s', 6);
    action[8]['*'] = make_pair('e', 0);
    action[8]['('] = make_pair('e', 0);
    action[8][')'] = make_pair('s', 11);
    action[8]['$'] = make_pair('e', 0);

    action[9]['i'] = make_pair('e', 0);
    action[9]['+'] = make_pair('r', 1);
    action[9]['*'] = make_pair('s', 7);
    action[9]['('] = make_pair('e', 0);
    action[9][')'] = make_pair('r', 1);
    action[9]['$'] = make_pair('r', 1);

    action[10]['i'] = make_pair('e', 0);
    action[10]['+'] = make_pair('r', 3);
    action[10]['*'] = make_pair('r', 3);
    action[10]['('] = make_pair('e', 0);
    action[10][')'] = make_pair('r', 3);
    action[10]['$'] = make_pair('r', 3);

    action[11]['i'] = make_pair('e', 0);
    action[11]['+'] = make_pair('r', 5);
    action[11]['*'] = make_pair('r', 5);
    action[11]['('] = make_pair('e', 0);
    action[11][')'] = make_pair('r', 5);
    action[11]['$'] = make_pair('r', 5);

    go[0]['E'] = 1;
    go[0]['T'] = 2;
    go[0]['F'] = 3;

    go[1]['E'] = -1;
    go[1]['T'] = -1;
    go[1]['F'] = -1;

    go[2]['E'] = -1;
    go[2]['T'] = -1;
    go[2]['F'] = -1;

    go[3]['E'] = -1;
    go[3]['T'] = -1;
    go[3]['F'] = -1;

    go[4]['E'] = 8;
    go[4]['T'] = 2;
    go[4]['F'] = 3;

    go[5]['E'] = -1;
    go[5]['T'] = -1;
    go[5]['F'] = -1;

    go[6]['E'] = -1;
    go[6]['T'] = 9;
    go[6]['F'] = 3;

    go[7]['E'] = -1;
    go[7]['T'] = -1;
    go[7]['F'] = 10;

    go[8]['E'] = -1;
    go[8]['T'] = -1;
    go[8]['F'] = -1;

    go[9]['E'] = -1;
    go[9]['T'] = -1;
    go[9]['F'] = -1;

    go[10]['E'] = -1;
    go[10]['T'] = -1;
    go[10]['F'] = -1;

    go[11]['E'] = -1;
    go[11]['T'] = -1;
    go[11]['F'] = -1;
}

struct stack_symbol {
    char symbol;
    int val = 0;
};

void generateInput(stack_symbol sym[6]) {
    stack_symbol a;
    a.symbol = 'i';
    a.val = 2;
    sym[0] = a;
    a.symbol = '*';
    sym[1] = a;
    a.symbol = 'i';
    a.val = 3;
    sym[2] = a;
    a.symbol = '+';
    sym[3] = a;
    a.symbol = 'i';
    a.val = 4;
    sym[4] = a;
    a.symbol = '$';
    sym[5] = a;
}

int generateAttr(stack<stack_symbol>& s, int rule) {
    stack_symbol a, b;
    switch(rule) {
        case 0:
            a = s.top();
            s.pop();
            s.pop();
            b = s.top();
            s.pop();
            cout<<"Performing ";
            cout<<a.val;
            cout<<"+";
            cout<<b.val<<endl;
            return a.val + b.val;
        case 1:
            a = s.top();
            s.pop();
            return a.val;
        case 2:
            a = s.top();
            s.pop();
            s.pop();
            b = s.top();
            s.pop();
            cout<<"Performing ";
            cout<<a.val;
            cout<<"*";
            cout<<b.val<<endl;
            return a.val * b.val;
        case 3:
            a = s.top();
            s.pop();
            return a.val;
        case 4:
            s.pop();
            a = s.top();
            s.pop();
            s.pop();
            return a.val;
        case 5:
            a = s.top();
            s.pop();
            return a.val;
        default:
            // shouldn't reach here
            return -1;
    }
}

void printPushedVal(char sym, int val) {
    cout<<"Value of ";
    cout<<sym;
    cout<<" pushed on stack = ";
    cout<<val<<endl;
}

int main() {
    stack<stack_symbol> s;
    map<char, pair<char, int> > action[12];
    map<char, int> go[12];
    pair<char, string> rules[6];
    fillRules(rules);
    generateTable(action, go);
    stack_symbol a;
    a.symbol = '0';
    a.val = -1;
    s.push(a);
    stack_symbol inp[6];
    generateInput(inp);
    int i = 0;
    while(true) {
        pair<char, int> step;
        char state = s.top().symbol;
        int index;
        // hack
        if (state == 'a') {
            index = 10;
        } else if (state == 'b') {
            index = 11;
        } else {
            index = state - '0';
        }

        step = action[index][inp[i].symbol];
        if (step.first == 'e') {
            cout<<"Parsing failed!"<<endl;
            return 0;
        } else if (step.first == 's') {
            cout<<"shift"<<endl;
            s.push(inp[i]);
            if (inp[i].symbol == 'i') {
                printPushedVal(inp[i].symbol, inp[i].val);
            }
            a.symbol = to_string(step.second)[0];
            a.val = -1;
            s.push(a);
            if (inp[i].symbol != '$') {
                i++;
            }
        } else if (step.first == 'r') {
            printf("reduce by %c -> ", rules[step.second - 1].first);
            cout<< rules[step.second - 1].second << endl;
            int removals = rules[step.second - 1].second.length();
            while (removals--) {
                s.pop();
            }
            int toPush = generateAttr(s, step.second - 1);
            a.symbol = rules[step.second - 1].first;
            string gotoState = to_string(go[s.top().symbol - '0'][rules[step.second - 1].first]);
            char gotostate;
            // hack
            if (gotoState == "10") {
                gotostate = 'a';
            } else if (gotoState == "11") {
                gotostate = 'b';
            } else {
                gotostate = gotoState[0];
            }
            a.symbol = rules[step.second - 1].first;
            a.val = toPush;
            s.push(a);
            printPushedVal(a.symbol, a.val);
            a.symbol = gotostate;
            a.val = -1;
            s.push(a);
        } else if (step.first == 'a') {
            cout<<"accept"<<endl;
            return 0;
        }
    }
    return 0;
}
