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
    removeWhiteSpace(token);
    while (getline(ss, token, '|'))
    {
        rules.push_back(token);
    }

    return rules;
}

void solveNonImmediateLR(vector<pair<string, vector<string>>> &nonTerminals, int A, int B)
{
    string nameA = nonTerminals[A].first;
    string nameB = nonTerminals[B].first;

    vector<string> &rulesA = nonTerminals[A].second;
    vector<string> &rulesB = nonTerminals[B].second;
    vector<string> newRulesA;

    for (const string &rule : rulesA)
    {
        if (rule.substr(0, nameB.size()) == nameB)
        {
            for (const string &rule1 : rulesB)
            {
                string newRule = rule.substr(nameB.size());
                removeWhiteSpace(newRule);
                newRulesA.push_back(rule1 + " " + newRule);
            }
        }
        else
        {
            newRulesA.push_back(rule);
        }
    }

    nonTerminals[A].second = newRulesA;
}

void solveImmediateLR(vector<pair<string, vector<string>>> &nonTerminals, int A)
{
    string name = nonTerminals[A].first;
    string newName = name + "'";

    vector<string> &rules = nonTerminals[A].second;
    vector<string> alphas, betas, newRulesA, newRulesA1;

    for (const string &rule : rules)
    {
        if (rule.substr(0, name.size()) == name)
        {
            string newRule = rule.substr(name.size());
            removeWhiteSpace(newRule);
            alphas.push_back(rule.substr(name.size()));
        }
        else
        {
            betas.push_back(rule);
        }
    }

    if (alphas.empty())
    {
        return;
    }

    if (betas.empty())
    {
        newRulesA.push_back(newName);
    }

    for (const string &beta : betas)
    {
        newRulesA.push_back(beta + " " + newName);
    }

    for (const string &alpha : alphas)
    {
        newRulesA1.push_back(alpha + " " + newName);
    }

    nonTerminals[A].second = newRulesA;
    newRulesA1.push_back("ε"); // Adding ε (epsilon)
    nonTerminals.push_back({newName, newRulesA1});
}

void applyAlgorithm(vector<pair<string, vector<string>>> &nonTerminals)
{
    int size = nonTerminals.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            solveNonImmediateLR(nonTerminals, i, j);
        }
        solveImmediateLR(nonTerminals, i);
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

            nonTerminals.push_back({nonTerminal, getRules(rule)});
        }
        else
        {
            cout << "Invalid input format: " << line << endl;
        }
    }

    applyAlgorithm(nonTerminals);

    for (const auto &nt : nonTerminals)
    {
        cout << nt.first << " -> ";
        for (int i = 0; i < nt.second.size(); i++)
        {
            if (i == nt.second.size() - 1)
                cout << nt.second[i];
            else
                cout << nt.second[i] << " | ";
        }
        cout << endl;
    }

    return 0;
}
