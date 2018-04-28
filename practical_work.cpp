#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Condition
{
    vector<int> a, b, c, e;
};

vector<Condition> conditions;//Conditions of the machine.

struct NSM   //Nondeterministic state machine
{
    int first_condition;
    int final_condition;

    NSM(char c);
    void Concatenation(NSM* second_part);
    void Disjunction(NSM* second_part);
    void Iteration();
};

NSM::NSM(char c) {
    first_condition = conditions.size();
    final_condition = first_condition + 1;
    conditions.resize(conditions.size() + 2);
    switch(c)
    {
        case 'a': conditions[final_condition].a.push_back(first_condition);break;
        case 'b': conditions[final_condition].b.push_back(first_condition);break;
        case 'c': conditions[final_condition].c.push_back(first_condition);break;
        case '1': conditions[final_condition].e.push_back(first_condition);
    }
}

void NSM::Concatenation(NSM* second_part)
{
    conditions[second_part->first_condition].e.push_back(final_condition);
    final_condition = second_part->final_condition;
}

void NSM::Disjunction(NSM* second_part)
{
    conditions[second_part->first_condition].e.push_back(first_condition);
    conditions[second_part->final_condition].e.push_back(final_condition);
    final_condition = second_part->final_condition;
}

void NSM::Iteration()
{
    conditions[first_condition].e.push_back(final_condition);
    final_condition = first_condition;
}

int Find_suff(string s, int cur_cond, int cur_res, vector<bool>& e_transitions)
{
    if (s == "" || e_transitions[cur_cond]) {
        return cur_res;
    }
    int next_res = cur_res;
    e_transitions[cur_cond] = 1;
    for (int i = 0; i < conditions[cur_cond].e.size(); ++i) {
        next_res = max(next_res, Find_suff(s, conditions[cur_cond].e[i], cur_res, e_transitions));
    }
    char c = s[s.size() - 1];
    s.resize(s.size() - 1);
    vector<bool> new_e_transitions(conditions.size(), 0);
    switch(c) {
        case 'a':
        for (int i = 0; i < conditions[cur_cond].a.size(); ++i) {
            next_res = max(next_res, Find_suff(s, conditions[cur_cond].a[i], cur_res + 1, new_e_transitions));
        }
        break;
        case 'b':
        for (int i = 0; i < conditions[cur_cond].b.size(); ++i) {
            next_res = max(next_res, Find_suff(s, conditions[cur_cond].b[i], cur_res + 1, new_e_transitions));
        }
        break;
        case 'c':
        for (int i = 0; i < conditions[cur_cond].c.size(); ++i) {
            next_res = max(next_res, Find_suff(s, conditions[cur_cond].c[i], cur_res + 1, new_e_transitions));
        }
    }
    return next_res;
}

int main()
{
    string regular_expression;
    cin >> regular_expression;
    stack<NSM> st;
    conditions.resize(0);
    for (int i = 0; i < regular_expression.size(); ++i) {
        if (regular_expression[i] == ' ') {
            continue;
        } else if (regular_expression[i] >= 'a' && regular_expression[i] <= 'c' || regular_expression[i] == '1') {
            st.push(NSM(regular_expression[i]));
        } else {
            if (st.empty()) {
                cout << "ERROR. Incorrect expression." << endl;
                return 0;
            }
            if (regular_expression[i] == '*') {
                st.top().Iteration();
            } else {
                NSM nsm1 = st.top();
                st.pop();
                if (st.empty()) {
                    cout << "ERROR. Incorrect expression." << endl;
                    return 0;
                }
                if (regular_expression[i] == '.') {
                    st.top().Concatenation(&nsm1);
                } else if (regular_expression[i] == '+') {
                    st.top().Disjunction(&nsm1);
                } else {
                    cout << "ERROR. Incorrect expression." << endl;
                    return 0;
                }
            }

        }
    }
    if (st.size() != 1) {
        cout << "ERROR. Incorrect expression." << endl;
        return 0;
    }

    string s;
    cin >> s;
    vector<bool> e_transitions(conditions.size(), 0); //While we use e-transitions we should remember where we have already been;
    cout << Find_suff(s, st.top().final_condition, 0, e_transitions);
    st.pop();
    return 0;
}
