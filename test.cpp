#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

struct Production {
    char lhs;
    string rhs;
};

// Function to augment the grammar
vector<Production> augmentGrammar(const vector<Production>& grammar) {
    vector<Production> augmentedGrammar = grammar;
    char startSymbol = grammar[0].lhs;
    augmentedGrammar.insert(augmentedGrammar.begin(), {'S', string(1, startSymbol)});
    return augmentedGrammar;
}

// Function to compute the closure of an LR(0) item
set<pair<Production, int>> closure(const set<pair<Production, int>>& items, const vector<Production>& grammar) {
    set<pair<Production, int>> closureItems = items;
    bool added = true;
    while (added) {
        added = false;
        set<pair<Production, int>> newItems;
        for (const auto& item : closureItems) {
            char nextSymbol = item.second < item.first.rhs.size() ? item.first.rhs[item.second] : '\0';
            if (nextSymbol != '\0') {
                for (const auto& prod : grammar) {
                    if (prod.lhs == nextSymbol) {
                        pair<Production, int> newItem = {prod, 0};
                        if (closureItems.find(newItem) == closureItems.end()) {
                            newItems.insert(newItem);
                            added = true;
                        }
                    }
                }
            }
        }
        closureItems.insert(newItems.begin(), newItems.end());
    }
    return closureItems;
}

// Function to compute the goto function
set<pair<Production, int>> Goto(const set<pair<Production, int>>& items, char symbol, const vector<Production>& grammar) {
    set<pair<Production, int>> gotoItems;
    for (const auto& item : items) {
        if (item.second < item.first.rhs.size() && item.first.rhs[item.second] == symbol) {
            gotoItems.insert({item.first, item.second + 1});
        }
    }
    return closure(gotoItems, grammar);
}

// Function to create LR(0) parser tables
void createLR0ParserTables(const vector<Production>& grammar) {
    vector<Production> augmentedGrammar = augmentGrammar(grammar);
    map<set<pair<Production, int>>, int> stateMap;
    vector<set<pair<Production, int>>> states;
    vector<map<char, int>> transitionTable;
    int stateCount = 0;

    set<pair<Production, int>> startState = closure({{augmentedGrammar[0], 0}}, augmentedGrammar);
    stateMap[startState] = stateCount++;
    states.push_back(startState);
    transitionTable.push_back(map<char, int>());

    for (int i = 0; i < states.size(); ++i) {
        for (const auto& item : states[i]) {
            char nextSymbol = item.second < item.first.rhs.size() ? item.first.rhs[item.second] : '\0';
            if (nextSymbol != '\0') {
                set<pair<Production, int>> gotoState = Goto(states[i], nextSymbol, augmentedGrammar);
                if (stateMap.find(gotoState) == stateMap.end()) {
                    stateMap[gotoState] = stateCount++;
                    states.push_back(gotoState);
                    transitionTable.push_back(map<char, int>());
                }
                transitionTable[i][nextSymbol] = stateMap[gotoState];
            }
        }
    }

    // Print augmented grammar
    cout << "Augmented Grammar:" << endl;
    for (const auto& prod : augmentedGrammar) {
        cout << prod.lhs << " -> " << prod.rhs << endl;
    }

    // Print states
    cout << "\nStates:" << endl;
    for (int i = 0; i < states.size(); ++i) {
        cout << "State " << i << ":" << endl;
        for (const auto& item : states[i]) {
            cout << "  " << item.first.lhs << " -> " << item.first.rhs.substr(0, item.second) << "." << item.first.rhs.substr(item.second) << endl;
        }
    }

    // Print transition table
    cout << "\nTransition Table:" << endl;
    for (int i = 0; i < transitionTable.size(); ++i) {
        cout << "State " << i << ":" << endl;
        for (const auto& trans : transitionTable[i]) {
            cout << "  " << trans.first << " -> State " << trans.second << endl;
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of productions: ";
    cin >> n;

    vector<Production> grammar(n);
    cout << "Enter the productions (e.g., E->E+T):" << endl;
    for (int i = 0; i < n; ++i) {
        string prod;
        cin >> prod;
        grammar[i] = {prod[0], prod.substr(3)};
    }

    createLR0ParserTables(grammar);

    return 0;
}
