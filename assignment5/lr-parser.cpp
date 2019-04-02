/**
    LR parser with for given grammar
*/
#include <iostream>
#include <cstdio>
#include <map>
#include <stack>
#include <string>

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

int main() {
    stack<char> s;
    map<char, pair<char, int> > action[12];
    map<char, int> go[12];
    pair<char, string> rules[6];
    fillRules(rules);
    generateTable(action, go);
    s.push('0');
    string inp = "i*i+i$";
    int i = 0;
    while(true) {
        pair<char, int> step;
        char state = s.top();
        int index;
        // hack
        if (state == 'a') {
            index = 10;
        } else if (state == 'b') {
            index = 11;
        } else {
            index = state - '0';
        }

        step = action[index][inp[i]];
        if (step.first == 'e') {
            cout<<"Parsing failed!"<<endl;
            return 0;
        } else if (step.first == 's') {
            cout<<"shift"<<endl;
            s.push(inp[i]);
            s.push(to_string(step.second)[0]);
            if (inp[i] != '$') {
                i++;
            }
        } else if (step.first == 'r') {
            printf("reduce by %c -> ", rules[step.second - 1].first);
            cout<< rules[step.second - 1].second << endl;
            int removals = 2*rules[step.second - 1].second.length();
            while (removals--) {
                s.pop();
            }
            string gotoState = to_string(go[s.top() - '0'][rules[step.second - 1].first]);
            char gotostate;
            // hack
            if (gotoState == "10") {
                gotostate = 'a';
            } else if (gotoState == "11") {
                gotostate = 'b';
            } else {
                gotostate = gotoState[0];
            }

            s.push(rules[step.second - 1].first);
            s.push(gotostate);
        } else if (step.first == 'a') {
            cout<<"accept"<<endl;
            return 0;
        }
    }
    return 0;
}
