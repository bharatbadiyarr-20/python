#include <bits/stdc++.h>
using namespace std;

struct Value {
    int time;
    string lab;
};

vector<string> var = {"A", "B", "C"};

map<string, vector<Value>> domain = {
    {"A", {{1, "L1"}, {2, "L1"}}},
    {"B", {{2, "L1"}, {2, "L2"}, {3, "L2"}, {4, "L2"}}},
    {"C", {{1, "L2"}, {3, "L2"}, {4, "L2"}}}
};

map<string, Value> assignment;

bool isNeighbor(string a, string b) {
    if ((a == "A" && b == "B") || (a == "B" && b == "A"))
        return true;

    if ((a == "B" && b == "C") || (a == "C" && b == "B"))
        return true;

    if ((a == "A" && b == "C") || (a == "C" && b == "A"))
        return true;

    return false;
}

bool validPair(string a, Value x, string b, Value y) {
    if (a == "A" && b == "B")
        if (x.time == y.time)
            return false;

    if (a == "B" && b == "A")
        if (x.time == y.time)
            return false;

    if (a == "B" && b == "C")
        if (x.time == y.time)
            return false;

    if (a == "C" && b == "B")
        if (x.time == y.time)
            return false;

    if (x.time == y.time && x.lab == y.lab)
        return false;

    if ((a == "A" && b == "C") || (a == "C" && b == "A")) {
        if (abs(x.time - y.time) == 1)
            return false;
    }

    return true;
}

bool validWithAssignment(string s, Value x) {
    for (auto p : assignment) {
        if (!validPair(s, x, p.first, p.second))
            return false;
    }

    return true;
}

int degree(string s, map<string, vector<Value>>& domains) {
    int d = 0;

    for (string x : var) {
        if (x == s || assignment.count(x))
            continue;

        if (isNeighbor(s, x))
            d++;
    }

    return d;
}

string selectMRV(map<string, vector<Value>>& domains) {
    string best = "";
    int minSize = INT_MAX;
    int maxDegree = -1;

    for (string s : var) {
        if (assignment.count(s))
            continue;

        int size = domains[s].size();
        int d = degree(s, domains);

        if (size < minSize || (size == minSize && d > maxDegree)) {
            minSize = size;
            maxDegree = d;
            best = s;
        }
    }

    return best;
}

void printDomains(map<string, vector<Value>>& domains) {
    for (string s : var) {
        if (assignment.count(s))
            continue;

        cout << s << " = { ";

        for (auto x : domains[s])
            cout << "(" << x.time << "," << x.lab << ") ";

        cout << "}\n";
    }
}

bool forwardCheck(string s, Value x, map<string, vector<Value>>& newDomains) {
    for (string y : var) {
        if (assignment.count(y) || y == s)
            continue;

        vector<Value> temp;

        for (auto v : newDomains[y]) {
            if (validPair(s, x, y, v))
                temp.push_back(v);
        }

        newDomains[y] = temp;

        if (newDomains[y].empty()) {
            cout << "Domain of " << y << " becomes EMPTY\n";
            return false;
        }
    }

    return true;
}

bool solve(map<string, vector<Value>>& domains) {
    if (assignment.size() == 3)
        return true;

    string s = selectMRV(domains);

    cout << "\nMRV selects: " << s << "\n";

    for (auto x : domains[s]) {

        if (!validWithAssignment(s, x)) {
            cout << "Constraint violated: " << s
                 << " -> (" << x.time << "," << x.lab << ")\n";
            continue;
        }

        cout << "Assign " << s << " -> Time "
             << x.time << ", Lab " << x.lab << "\n";

        assignment[s] = x;

        map<string, vector<Value>> newDomains = domains;

        newDomains[s].clear();

        if (forwardCheck(s, x, newDomains)) {
            cout << "Domains after Forward Checking:\n";
            printDomains(newDomains);

            if (solve(newDomains))
                return true;
        }

        cout << "Backtrack from " << s
             << " -> (" << x.time << "," << x.lab << ")\n";

        assignment.erase(s);
    }

    return false;
}

int main() {
    cout << "AI Lab Scheduling\n\n";

    if (solve(domain)) {
        cout << "\nFinal Schedule:\n\n";

        cout << "Section\tTime Slot\tLab\n";

        for (string s : var) {
            cout << s << "\t"
                 << assignment[s].time << "\t\t"
                 << assignment[s].lab << "\n";
        }
    }
    else {
        cout << "\nNo solution exists.\n";
    }

    return 0;
}
