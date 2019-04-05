#include <bits/stdc++.h>
#include <iostream>
using namespace std;

stack<string> st;
map<string, vector<string> > grammar;
char a[100];
int c = 0;
char act[10];

bool substitute(string key) {
	int i = grammar[key].size()-1;
	stack<string> temp;
	while (i >= 0 && (st.top() == grammar[key][i])) {
		temp.push(st.top());
		st.pop();
		i--;
	}
	if (i < 0) {
		st.push(key);
		return true;
	} else {
		while(!temp.empty()) {
			st.push(temp.top());
			temp.pop();
		}
		return false;
	}
}


void generateGrammar() {
	vector<string> rule;
	rule.push_back("while");
	rule.push_back("cond");
	rule.push_back("bgn");
	rule.push_back("stat");
	rule.push_back("end");
	grammar["wloop"] = rule;
	rule.clear();
	
	rule.push_back("(");
	rule.push_back("id");
	rule.push_back("op");
	rule.push_back("number");
	rule.push_back(")");
	grammar["cond"] = rule;
	rule.clear();

	rule.push_back("expr");
	rule.push_back(";");
	grammar["stat"] = rule;
	rule.clear();

	
	rule.push_back("id");
	rule.push_back("mop");
	rule.push_back("number");
	grammar["expr"] = rule;
	rule.clear();
}

int main() {

	cout<<"GRAMMER IS:\n";
	cout<<"<wloop>::=<while><cond><bgn><stat><end>"<<endl;
	cout<<"<cond>::=<(><id><op><number><)>"<<endl;
	cout<<"<stat>::=<expr><;>"<<endl;
	cout<<"expr>::=<id><mop><number>"<<endl;

	strcpy(a, "while ( id op number ) bgn id mop number ; end");
	c = strlen(a);

	generateGrammar();

	vector<string> v;
	string s;
	for (int i=0;i<c;i++) {
		if (a[i] == ' ') {
			v.push_back(s);
			s = "";
		} else {
			s+=a[i];
		}
	}

	v.push_back(s);

	for (int i=0;i<v.size();i++) {
		st.push(v[i]);
		while(substitute("cond"));
		while(substitute("expr"));
		while(substitute("stat"));
		while(substitute("wloop"));
	}


	if (st.top() == "wloop") {
		cout<<"CFG accepts the given input!"<<endl;
	} else {
		cout<<"Error encountered for the given grammer"<<endl;
	}

	return 0;
}