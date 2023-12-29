#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Forest {
    int weight;
    int root;
};

struct Tree {
    int left, right, parent;
    int symbol;
};
Forest forest[256];
Tree tree[520];
FILE *f, *g;
vector<pair<int, string>> code;

//функция кодов
string codeMAK(Tree t[], int i){
    string codik;
    while (t[i].parent != -1){
        if (t[t[i].parent].left == i){
            codik.push_back('0');
        } else codik.push_back('1');
        i = t[i].parent;
    }
    return codik;
}

// функция поиска минимума
void getmin(Forest f[], int size_f, int &pos1, int &pos2){
    if (f[0].weight < f[1].weight){
        pos1 = 0;
        pos2 = 1;
    } else {
        pos1 = 1;
        pos2 = 0;
    }
    for (int i = 2; i < size_f; i++){
        if (f[i].weight < f[pos1].weight){
            pos2 = pos1;
            pos1 = i;
        } else if (f[i].weight < f[pos2].weight){
            pos2 = i;
        }
    }
}
int main()
{
    int freq[256];
    for (int i = 0; i < 256; i++){
        freq[i] = 0;
    }
    char ch;
    int p1, p2;
    int size_forest = 0;
    int size_tree = 0;
    int szf = 0;

    f = fopen("inputt.txt", "rb");
    g = fopen("outputt.txt", "w");
    //freopen("outputt.txt", "w", stdout);
    while (fscanf(f, "%c", &ch) != -1) {
            szf++;
            freq[ch]++;
    }

  //заполнить forest через freq
    for (int i = 0; i < 256; i++){
        if (freq[i]!= 0){
            forest[size_forest].root = size_forest;
            forest[size_forest].weight = freq[i];
            size_forest++;
        }
    }
    int sizeztree = size_forest;
    string baseofch;

    while (fscanf(f, "%c", &ch) != -1) {
            if (baseofch.find(ch) == std::string::npos){
                baseofch = baseofch + ch;
                for (int i = 0; i < sizeztree; i++){
                    if (freq[ch] == forest[i].weight){
                        tree[i].symbol = ch;
                    }
                }
            }
    }
    // иниализация tree   
    for (int i = 0;i<size_forest; i++){
        tree[i].left = -1;
        tree[i].right = -1;
        tree[i].parent = -1;
        size_tree++;
     }
    while (size_forest > 1){
        getmin(forest, size_forest, p1, p2);
        tree[size_tree].left = forest[p1].root;
        tree[size_tree].right = forest[p2].root;
        tree[size_tree].parent = -1;

        tree[forest[p1].root].parent = size_tree;
        tree[forest[p2].root].parent = size_tree;

        forest[p1].weight = forest[p1].weight + forest[p2].weight;
        forest[p1].root = size_tree;
        forest[p2] = forest[size_forest-1];
        size_forest--;
        size_tree++;
    }
    string s;
    for (int i = 0; i < sizeztree; i++){
        s = codeMAK(tree, i);
        reverse(s.begin(), s.end());
        code.push_back({i,s});
    }

    unsigned char byte = 0;
    f = fopen("input.txt", "rb");
    int bitik = 0;
    while (fscanf(f, "%c", &ch) != -1) {
        for (int i = 0; i < szf; i++){
            if (ch == tree[i].symbol){
                for(int t = 0; t < code[i].second.length(); i++){
                    byte = byte <<1;
                    byte = byte + code[i].second[t];
                    bitik++;
                    if (bitik == 8){
                        fprintf(g, "%c", byte);
                        bitik = 0;
                    }
                }
            }
        }

     //for (int i = 0; i < code.size(); i++){
        //cout << code[i].first << ' ' << code[i].second << endl;
     //}
}
}
