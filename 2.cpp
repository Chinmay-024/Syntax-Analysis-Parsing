#include <bits/stdc++.h>
#include <iostream>

using namespace std;

void removeWhiteSpace(string &token)
{
    size_t startPos = token.find_first_not_of(" \t");
    if (startPos != string::npos)
    {
        token.erase(0, startPos);
    }
    size_t endPos = token.find_last_not_of(" \t");
    if (endPos != string::npos)
    {
        token.erase(endPos + 1);
    }
}

vector<string> getRules(string rule)
{
    vector<string> rules;
    stringstream ss(rule);
    string token;
    while (getline(ss, token, '|'))
    {
        removeWhiteSpace(token);
        rules.push_back(token);
    }

    return rules;
}

string getCommonPrefixes(const vector<string> &rules)
{
    string commonPrefixes = "";

    if (rules.empty())
    {
        return commonPrefixes;
    }
    string prefix = "";
    int maxl = 0;
    for (int i = 0; i < rules.size(); i++)
    {
        for (int j = i + 1; j < rules.size(); j++)
        {
            int l = 0;
            while (l < rules[i].size() && l < rules[j].size())
            {
                if (rules[i][l] == rules[j][l])
                    l++;
                else
                    break;
            }
            if (l > maxl)
                prefix = rules[i].substr(0, l);
        }
    }
    return prefix;
}

void applyLeftFactoring(vector<pair<string, vector<string>>> &nonTerminals)
{
    bool foundCommonPrefix = true;
    while (foundCommonPrefix)
    {
        foundCommonPrefix = false;
        int z = 1;
        for (int i = 0; i < nonTerminals.size();)
        {
            vector<string> &rules = nonTerminals[i].second;
            string commonPrefix = getCommonPrefixes(rules);

            if (commonPrefix != "")
            {
                foundCommonPrefix = true;
                string a = commonPrefix; // Longest common prefix
                string newName;
                if (z != 1)
                    newName = nonTerminals[i].first + to_string(z);
                else
                    newName = nonTerminals[i].first + "'";

                vector<string> newRules;
                vector<string> nonCommonSuffixes;

                for (const string &rule : rules)
                {
                    if (rule.find(a) == 0)
                    {
                        newRules.push_back((rule.substr(a.size()) == "") ? "∈" : (rule.substr(a.size())));
                    }
                    else
                    {
                        nonCommonSuffixes.push_back(rule == "" ? "∈" : rule);
                    }
                }

                nonTerminals[i].second = {a + newName};
                for (auto k : nonCommonSuffixes)
                    nonTerminals[i].second.push_back(k);
                nonTerminals.push_back({newName, newRules});
                z++;
            }
            else
            {
                i++;
                z = 1;
            }
        }
    }
}

int main()
{
    vector<pair<string, vector<string>>> nonTerminals;

    ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line))
    {
        size_t arrowPos = line.find("->");
        if (arrowPos != string::npos)
        {
            string nonTerminal = line.substr(0, arrowPos);
            string rule = line.substr(arrowPos + 2);
            removeWhiteSpace(nonTerminal);
            removeWhiteSpace(rule);
            // cout << nonTerminal << endl;
            // cout << rule << endl;
            nonTerminals.push_back({nonTerminal, getRules(rule)});
        }
        else
        {
            cout << "Invalid input format: " << line << endl;
        }
    }

    applyLeftFactoring(nonTerminals);

    for (const auto &nt : nonTerminals)
    {
        cout << nt.first << " -> ";
        for (int i = 0; i < nt.second.size(); i++)
        {
            if (i == nt.second.size() - 1)
            {
                cout << nt.second[i];
            }
            else
            {
                cout << nt.second[i] << " | ";
            }
        }
        cout << endl;
    }

    return 0;
}
