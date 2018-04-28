#include <iostream>
#include <vector>

using namespace std;

void Minimization4 (vector< pair< vector<int>, vector<int> > >& conditions, int power, int flag, vector<bool>& is_final)
{
    vector< pair< pair<char, char>, vector<char> > > classes(conditions.size());
    for (int i = 0; i < classes.size(); ++i) {
        classes[i].second.resize(power);
    }
    for (int i = 0; i < classes.size(); ++i) {
        classes[i].first.first = (is_final[i]) ? 'B' : 'A';
    }
    bool b = 1;//If there are any new classes
    int counter = 0;
    char letter;
    while (b) {
        letter = 'A';
        for (int i = 0; i < classes.size(); ++i) {
            //Find next classes by each letter
            for (int j = 0; j < power; ++j) {
                classes[i].second[j] = classes[conditions[i].second[j]].first.first;
            }
            bool b1 = 1;     //If class is new
            for (int j = 0; j < i; ++j) {
                if (classes[i].first.first == classes[j].first.first){
                    b1 = 0;
                    for (int k = 0; k < power; ++k) {
                        if (classes[i].second[k] != classes[j].second[k]) {
                            b1 = 1;
                            break;
                        }
                    }
                    if (!b1) {
                        classes[i].first.second = classes[j].first.second;
                        break;
                    }
                }
            }
            if (b1) {
                classes[i].first.second = letter;
                letter++;
            }
        }
        //Check if there are any new classes
        counter++;
        b = 0;
        for (int i = 0; i < classes.size(); ++i) {
            if (classes[i].first.first != classes[i].first.second) {
                b = 1;
                classes[i].first.first = classes[i].first.second;
            }
        }
    }
    cout << "Number ## ";
    for (int i = 0; i < power; ++i) {
        cout << char('a' + i) << ' ';
    }
    cout << endl;
    int h = 0;
    for (int i = 0; i < letter - 'A'; ++i) {
        cout << i << ") ## ";
        while (classes[h].first.first != i + 'A') {
            h++;
        }
        for (int j = 0; j < power; ++j) {
            for (int k = 0; k < classes.size(); ++k) {
                if (classes[h].second[j] == classes[k].first.first) {
                    cout << k << ' ';
                    break;
                }
            }
        }
        if (is_final[h]) {
            cout << "## final";
        }
        cout << endl;
    }
}

void Minimization3 (vector< pair< vector<int>, vector<int> > >& conditions, int power, int flag, vector<bool>& is_final)
{
    vector< pair< pair<char, char>, vector<char> > > classes(conditions.size());
    for (int i = 0; i < classes.size(); ++i) {
        classes[i].second.resize(power);
    }
    cout << "   ";
    for (int i = 0; i < classes.size(); ++i) {
        cout << i << ' ';
    }
    cout << endl;
    cout << "0) ";
    for (int i = 0; i < classes.size(); ++i) {
        classes[i].first.first = (is_final[i]) ? 'B' : 'A';
        cout << classes[i].first.first << ' ';
    }
    cout << endl;
    bool b = 1;//If there are any new classes
    int counter = 0;
    char letter;
    while (b) {
        letter = 'A';
        for (int i = 0; i < classes.size(); ++i) {
            //Find next classes by each letter
            for (int j = 0; j < power; ++j) {
                classes[i].second[j] = classes[conditions[i].second[j]].first.first;
            }
            bool b1 = 1;     //If class is new
            for (int j = 0; j < i; ++j) {
                if (classes[i].first.first == classes[j].first.first){
                    b1 = 0;
                    for (int k = 0; k < power; ++k) {
                        if (classes[i].second[k] != classes[j].second[k]) {
                            b1 = 1;
                            break;
                        }
                    }
                    if (!b1) {
                        classes[i].first.second = classes[j].first.second;
                        break;
                    }
                }
            }
            if (b1) {
                classes[i].first.second = letter;
                letter++;
            }
        }
        for (int i = 0; i < power; ++i) {
            cout << char('A' + i) << ") ";
            for (int j = 0; j < classes.size(); ++j) {
                cout << classes[j].second[i] << ' ';
            }
            cout << endl;
        }
        //Check if there are any new classes
        counter++;
        b = 0;
        cout << counter << ") ";
        for (int i = 0; i < classes.size(); ++i) {
            if (classes[i].first.first != classes[i].first.second) {
                b = 1;
                classes[i].first.first = classes[i].first.second;
            }
            cout << classes[i].first.first << ' ';
        }
        cout << endl;
    }
    cout << "Number ## ";
    for (int i = 0; i < power; ++i) {
        cout << ' ' << char('a' + i) << ' ';
    }
    cout << endl;
    int h = 0;
    for (int i = 0; i < letter - 'A'; ++i) {
        printf("%5d) ## ", i);
        while (classes[h].first.first != i + 'A') {
            h++;
        }
        for (int j = 0; j < power; ++j) {
            for (int k = 0; k < classes.size(); ++k) {
                if (classes[h].second[j] == classes[k].first.first) {
                    printf("%2d ", k);
                    break;
                }
            }
        }
        if (is_final[h]) {
            cout << "## final";
        }
        cout << endl;
    }
}

void Determination(vector< vector< vector<char> > >& conditions, int power, int flag, vector<int>& final_conditions)
{
    vector< pair< vector<int>, vector<int> > > new_conditions(1);  //Table of new conditions: old conditions and transitions
    new_conditions[0].first.resize(1, 0);                     //First condition is the same that was in old machine
    new_conditions[0].second.resize(power);         //Transitions by letters
    //Make the table of new machine
    for (int i = 0; i < new_conditions.size(); ++i) {
        vector< vector<int> > next_conditions(power);//Next conditions of the current condition
        for (int j = 0; j < power; ++j) {
            next_conditions[j].resize(0);
        }
        //Find next conditions by each letter
        for (int j = 0; j < new_conditions[i].first.size(); ++j) {
            for (int k = 0; k < conditions.size(); ++k) {
                for (int l = 0; l < conditions[new_conditions[i].first[j]][k].size(); ++l) {
                    bool b = 1;
                    //Check that this condition didn't add before
                    for (int h = 0; h < next_conditions[conditions[new_conditions[i].first[j]][k][l] - 'a'].size(); ++h) {
                        if (next_conditions[conditions[new_conditions[i].first[j]][k][l] - 'a'][h] == k) {
                            b = 0;
                            break;
                        }
                    }
                    if (b) {
                        next_conditions[conditions[new_conditions[i].first[j]][k][l] - 'a'].push_back(k);
                    }
                }
            }
        }
        //Sort
        for (int j = 0; j < power; ++j) {
            for (int k = 0; k < next_conditions[j].size(); ++k) {
                int h = k - 1;
                while (h >= 0 && next_conditions[j][h] > next_conditions[j][h + 1]) {
                    swap(next_conditions[j][h], next_conditions[j][h + 1]);
                    h--;
                }
            }
        }
        //Looking for all new conditions
        for (int j = 0; j < power; ++j) {
            bool b = 0;
            //Checking all previous conditions
            for (int k = 0; k < new_conditions.size(); ++k) {
                //Comparing of conditions
                if (next_conditions[j].size() == new_conditions[k].first.size()) {
                    b = 1;
                    for (int l = 0; l < next_conditions[j].size(); ++l) {
                        if (next_conditions[j][l] != new_conditions[k].first[l]) {
                            b = 0;
                            break;
                        }
                    }
                }
                if (b) {
                    new_conditions[i].second[j] = k;
                    break;
                }
            }
            //If condition is new
            if (!b) {
                //Add new condition to the machine
                new_conditions.resize(new_conditions.size() + 1);
                new_conditions[new_conditions.size() - 1].first = next_conditions[j];
                new_conditions[new_conditions.size() - 1].second.resize(power);
                new_conditions[i].second[j] = new_conditions.size() - 1;
            }
        }
    }

    //Print the results.
    vector<bool> is_final(new_conditions.size(), 0);
    if (flag <= 2 || flag > 4) {
        cout << endl << "Number ## ";
        if (flag == 1 || flag == 13 || flag == 14) {
            cout << "old numbers ## ";
        }
        for (int i = 0; i < power; ++i) {
            cout << char('a' + i) << " ";
        }
        cout << endl;
        for (int i = 0; i < new_conditions.size(); ++i) {
            printf("%5d) ## ", i);
            if (flag == 1 || flag == 13 || flag == 14) {
                //Print with old conditions
                for (int j = 0; j < new_conditions[i].first.size(); ++j) {
                    cout << new_conditions[i].first[j] << ' ';
                }
                cout << "## ";
            }
            bool b = 0;
            for (int j = 0; j < power; ++j) {
                cout << new_conditions[i].second[j] << " ";
            }
            for (int j = 0; j < new_conditions[i].first.size(); ++j) {
                //Chech if the condition is final
                for (int k = 0; k < final_conditions.size() && !b; ++k) {
                    if (new_conditions[i].first[j] == final_conditions[k]) {
                        is_final[i] = 1;
                        b = 1;
                        break;
                    }
                }
            }
            if (b) {
                cout << "## final";
            }
            cout << endl << endl;
        }
    } else {
        //Build is_final
        for (int i = 0; i < new_conditions.size(); ++i) {
            bool b = 0;
            for (int j = 0; j < new_conditions[i].first.size(); ++j) {
                for (int k = 0; k < final_conditions.size() && !b; ++k) {
                    if (new_conditions[i].first[j] == final_conditions[k]) {
                        is_final[i] = 1;
                        b = 1;
                        break;
                    }
                }
            }
        }
    }

    if (flag > 2) {
        if (flag % 10 == 3) {
            Minimization3(new_conditions, power, flag, is_final);
        } else {
            Minimization4(new_conditions, power, flag, is_final);
        }
    }
}

int main()
{
    int flag;
    while (1) {
        cout << "Input a flag:" << endl;
        cout << "0 - to finish the work" << endl;
        cout << "1 - to determine the machine and print table with old conditions" << endl;
        cout << "2 - to determine the machine and print only the machine" << endl;
        cout << "3 - to minimize the machine and print all work" << endl;
        cout << "4 - to minimize the machine and print only the result" << endl;
        cout << "You can use combinations 13, 14, 23, 24" << endl;
        cin >> flag;
        if (flag == 0) {
            break;
        }
        if (flag < 0 || (flag > 4 && flag != 13 && flag != 14 && flag != 23 && flag != 24)) {
            cout << "ERROR. No such flag" << endl;
            continue;
        }
        int power;
        cout << "Input the power of the alphabet" << endl;
        cin >> power;
        int n;
        cout << "Input number of conditions" << endl;
        cin >> n;
        vector< vector< vector<char> > > conditions(n);
        for (int i = 0; i < n; ++i) {
            conditions[i].resize(n);
            for (int j = 0; j < n; ++j) {
                conditions[i][j].resize(0);
            }
        }
        int m;
        cout << "Input how many final conditionals there are" << endl;
        cin >> m;
        if (m >= n) {
            cout << "ERROR. It's more that the number of conditions" << endl;
            continue;
        }
        cout << "Input numbers of the final conditions" << endl;
        vector<int> final_conditions(0);
        for (int i = 0; i < m; ++i) {
            int k;
            cin >> k;
            if (k >= n) {
                cout << "ERROR. It's more that the number of conditions" << endl;
                continue;
            }
            final_conditions.push_back(k);
        }
        cout << "Input transitions in the format '<whence> <where> <letter>'" << endl;
        cout << "Then input -1" << endl;
        bool b = 1;
        int whence, where;
        char letter;
        cin >> whence;
        while (whence != -1) {
            cin >> where >> letter;
            if (whence >= n || where >= n || letter < 'a' || letter >= 'a' + power) {
                b = 0;
            }
            conditions[whence][where].push_back(letter);
            cin >> whence;
        }
        if (!b) {
            cout << "ERROR. Incorrect data" << endl;
            continue;
        }
        Determination(conditions, power, flag, final_conditions);
    }
    return 0;
}
