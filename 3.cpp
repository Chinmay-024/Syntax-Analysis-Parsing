#include <bits/stdc++.h>

#define EPSILON "\u2208"

using namespace std;

vector<string> non_terminals;
unordered_set<string> nt_exists;
vector<string> terminals;
unordered_map<string, vector<vector<string>>> rules;

string word;
int pos = 0;
int count1 = 0;

class Node
{
public:
    int ind;
    string label;
    vector<Node *> links;

    Node(int i, string l)
    {
        ind = i;
        label = l;
    }
};

void print(string str)
{
    cout << str << endl;
}

template <typename... Strings>
void print(string str, Strings... strings)
{
    cout << str << " ";
    print(strings...);
}

template <class... Rest>
void error(int code, Rest... rest)
{
    print(rest...);
    exit(code);
}

vector<string> split(string str, string p)
{
    vector<string> pieces;
    int l = 0, i = 0;
    while (i < str.size())
    {
        if (i + p.size() <= str.size() && str.substr(i, p.size()) == p)
        {
            pieces.push_back(str.substr(l, i - l));
            l = i + p.size();
            i = l;

            if (i == str.size())
            {
                pieces.push_back({});
                ++l;
            }
        }
        else
            ++i;
    }

    if (l <= i)
        pieces.push_back(str.substr(l, i - l));

    return pieces;
}

void noteRule(string rule)
{
    vector<string> r = split(rule, "->");

    if (r.size() != 2)
        error(-1, "Invalid production rule:", rule);

    if (nt_exists.find(r[0]) == nt_exists.end())
    {
        non_terminals.push_back(r[0]);
        nt_exists.insert(r[0]);
    }

    vector<string> rs = split(r[1], "|");
    int pos = 0;
    for (int i = 0; i < rs.size(); i++)
    {
        rules[r[0]].push_back({});

        int pos = 0;
        while (pos < rs[i].size())
        {
            int l = pos++;
            if (l + 1 < rs[i].size() && rs[i][l] == 'i' && rs[i][l + 1] == 'd')
            {
                rules[r[0]].back().push_back("id");
                pos += 1;
            }
            else if (l + 2 < rs[i].size() && (int)(rs[i][l]) == -30 && (int)(rs[i][l + 1]) == -120 && (int)(rs[i][l + 2]) == -120)
            {
                rules[r[0]].back().push_back(EPSILON);
                pos += 2;
            }
            else
            {
                while (pos < rs[i].size() && rs[i][pos] == '\'')
                    ++pos;
                rules[r[0]].back().push_back(rs[i].substr(l, pos - l));
            }
        }
    }
}

void printRules()
{
    for (auto el : non_terminals)
    {
        string nt = el;
        vector<vector<string>> c = rules[nt];

        cout << nt << "->";
        for (int i = 0; i < c.size(); i++)
        {
            for (int j = 0; j < c[i].size(); j++)
            {
                cout << " " << c[i][j];
            }
            if (i != c.size() - 1)
                cout << " |";
        }
        cout << endl;
    }
}

Node *parse(string str)
{
    Node *newnode = new Node(++count1, str);
    for (int i = 0; i < rules[str].size(); i++)
    {
        int j = 0;
        vector<Node *> vec;
        for (j = 0; j < rules[str][i].size(); j++)
        {
            string c = rules[str][i][j];
            if (rules.find(c) != rules.end())
            {
                Node *p = parse(c);
                if (p == NULL)
                {
                    return NULL;
                }
                else
                    vec.push_back(p);
            }
            else if (c == "id")
            {
                int l = pos;
                if (isalpha(word[l]))
                    ++l;
                else
                {
                    break;
                }
                pos = l;

                Node *idnode = new Node(++count1, "id");
                vec.push_back(idnode);
            }
            else if (c[0] == word[pos] || c == EPSILON)
            {
                if (c != EPSILON)
                {
                    ++pos;
                }
                Node *cnode = new Node(++count1, c);
                vec.push_back(cnode);
            }
            else
            {
                break;
            }
        }

        if (j == rules[str][i].size())
        {
            newnode->links = vec;
            return newnode;
        }
    }
    return NULL;
}

void drawTree(Node *root)
{
    if (root == NULL)
        return;

    ofstream dot_file("graph.dot");

    dot_file << "digraph G {\n";
    dot_file << "node [shape=\"circle\"]\n";

    queue<Node *> bfs;
    dot_file << "\t" << root->ind << " [label=\"" << root->label << "\"]\n";
    bfs.push(root);

    while (!bfs.empty())
    {
        Node *curr = bfs.front();
        bfs.pop();

        for (int i = 0; i < curr->links.size(); i++)
        {
            dot_file << "\t" << curr->links[i]->ind << " [label=\"" << curr->links[i]->label << "\"]\n";
            dot_file << "\t" << curr->ind << " -> " << curr->links[i]->ind << "\n";
            bfs.push(curr->links[i]);
        }
    }
    dot_file << "}\n";
    dot_file.close();
}

int main()
{
    ifstream inp("input.txt");
    string start, line;
    string t;
    getline(inp, start);
    while (getline(inp, line))
    {
        noteRule(line);
    }

    int choice = 1;
    while (true)
    {
        fflush(stdout);
        fflush(stdin);
        sleep(1);
        cout << "\nEnter your choice : 1 to test and 0 to end \nCHOICE: ";
        cin >> choice;

        if (!choice)
            break;

        cout << "Enter your word : ";
        cin >> word;
        pos = count1 = 0;

        Node *root = parse(start);
        if (root == NULL || pos != word.size())
            cout << "Does not match the grammar\n"
                 << endl;
        else
        {
            cout << "Word matches the grammar!\n";
            drawTree(root);
            system("dot -Tpng graph.dot -o graph.png");
            cout << "Derivation tree generated\n";
            system("xdg-open graph.png");
        }
    }

    inp.close();

    return 0;
}
// ∈ -> epsilon
// S
// S->idB
// B->idBAB|∈
// A->+|*