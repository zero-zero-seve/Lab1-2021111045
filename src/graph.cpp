#include "graph.h"

#include <limits.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

#include "readFile.h"
using std::cout;
using std::endl;
// 构造函数
Graph::Graph(string str, map<string, int> _map1, map<int, string> _map2) {
    len = 0;
    map1 = _map1;
    map2 = _map2;
    std::stringstream STR(str);
    string word;
    while (STR >> word) {
        this->str[len++] = map1[word];
    }
    this->size = map1.size();
    initGraph();
}

void Graph::showStr() {
    for (int i = 0; i < len; i++) {
        cout << this->str[i] << " ";
    }
    cout << endl;
}
void Graph::showGraph() {
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            cout << this->graph[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::storeGraph() {
    std::ofstream file(
        "./graph.txt");  // 替换为你的文件名

    if (!file.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
        return;  // 文件打开失败
    }

    // 写入节点个数
    file << size << std::endl;
    // 写入图
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file << graph[i][j] << " ";
        }
        file << endl;
    }
    // 写入map2
    for (int i = 0; i < size; i++) {
        file << i << " " << map2[i] << endl;
    }
    // 关闭文件
    file.close();

    return;
}

void Graph::initGraph() {
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            this->graph[i][j] = 0;
        }
    }
    for (int i = 0; i < this->len - 1; i++) {
        int index1 = this->str[i];
        int index2 = this->str[i + 1];
        this->graph[index1][index2] += 1;
    }
}

Graph::~Graph() {}

string Graph::queryBridgeWords(string word1, string word2) {
    int flag1 = 1;
    int flag2 = 1;
    if (map1.find(word1) == map1.end()) {
        flag1 = 0;
    }
    if (map1.find(word2) == map1.end()) {
        flag2 = 0;
    }
    string s = "";
    if (flag1 == 0 && flag2 == 0) {
        s = s + "No" + " '" + word1 + "' and '" + word2 + "' in the graph!";
    } else if (flag1 == 0) {
        s = s + "No" + " '" + word1 + "' in the graph!";
    } else if (flag2 == 0) {
        s = s + "No" + " '" + word2 + "' in the graph!";
    } else {
        // 存在word1与word2，查询图
        s = findMiddleWord(map1[word1], map1[word2], 1);
    }
    return s;
}
string Graph::findMiddleWord(int firstword, int secondword, int choice) {
    string str = "";
    int flag = 0;
    for (int middleword = 0; middleword < size; middleword++) {
        if (graph[firstword][middleword] != 0) {
            if (graph[middleword][secondword] != 0) {
                flag = 1;
                str = str + map2[middleword] + ",";
            }
        }
    }
    switch (choice) {
        case 0: {
            if (flag == 0) {
                str = str + "No bridge words from " + "\"" + map2[firstword] + " \"to \"" + map2[secondword] +
                      "\"!";
            } else {
                str[str.size() - 1] = '.';
                string s = "";
                str = s + "The bridge words from " + "\"" + map2[firstword] + " \"to \"" + map2[secondword] +
                      "\" are:" + str;
            }
            break;
        }
        // 返回中间词或者空
        case 1: {
            if (flag == 0) {
                str = " ";
            } else {
                int count = 0;
                for (int i = 0; i < str.size(); i++) {
                    if (str[i] == ',') {
                        str[i] = ' ';
                        count++;
                    }
                }
                // 选择一个桥接词
                str = chooseOne(str, count);
            }
            break;
        }
    }
    return str;
}
string Graph::chooseOne(string str, int len) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int random_number = (rand()) % len;
    // 选择合适的一个桥接词
    std::stringstream STR(str);
    string word;
    for (int i = 0; i <= random_number; i++) {
        STR >> word;
    }
    return word;
}

string Graph::generateNewText(string inputText) {
    // 已经获得用户输入文本，对文本做处理
    preHandleStr(inputText);
    std::stringstream STR(inputText);
    string word1;
    string word2;
    string str = "";
    int step = 0;
    // 读取第一个存在word1
    while (STR >> word1) {
        str = str + word1 + ' ';
        if (map1.find(word1) != map1.end()) {
            break;
        }
    }
    string temp_str;
    while (STR >> word2) {
        // str+=word2;
        if (map1.find(word2) == map1.end()) {
            str = str + word2 + ' ';
            step = 1;
            continue;
        }
        if (step != 0) {
            str = str + word2 + ' ';
            step = 0;
            word1 = word2;
            continue;
        }
        temp_str = findMiddleWord(map1[word1], map1[word2], 1);
        str = temp_str == " " ? str + word2 + ' ' : str + temp_str + ' ' + word2 + ' ';
        word1 = word2;
    }
    return str;
}

// 最短路径计算
void Graph::calcShortestPath(string word1, string word2) {
    string str = "";
    vector<vector<int>> allpaths;
    vector<int> path;
    if (map1.find(word1) == map1.end() || (map1.find(word2) == map1.end() && !word2.empty())) {
        if (!word2.empty()) {
            str = str + "There is no word named " + word1 + " or " + word2;
            cout << str << endl;
        } else {
            str = str + "There is no word named " + word1;
            cout << str << endl;
        }
    } else if (word2.empty())  // 只输入了一个单词
    {
        for (int j = 0; j < size; j++) {
            if (j != map1[word1]) {
                cout << "The shortest path form " << word1 << " to " << map2[j] << " : ";
                path.clear();
                allpaths.clear();
                dijkstra(map1[word1], j, allpaths, path);
                vector<vector<int>>::iterator iter;
                if (allpaths.empty()) {
                    str = "Do not have a path from " + word1 + " to " + map2[j];
                    cout << str << endl;
                } else {
                    for (iter = allpaths.begin(); iter != allpaths.end(); ++iter) {
                        for (int i = 0; i < (*iter).size(); ++i) {
                            cout << map2[(*iter)[i]];
                            if (j != (*iter)[i]) {
                                cout << " -> ";
                            }
                        }
                        cout << endl;
                    }
                }
            }
        }
    } else {  // 输入了两个单词
        dijkstra(map1[word1], map1[word2], allpaths, path);
        cout << "The shortest path form " << word1 << " to " << word2 << " : ";
        vector<vector<int>>::iterator iter;
        if (allpaths.empty()) {
            str = "Do not have a path from " + word1 + " to " + word2;
            cout << str << endl;
        } else {
            for (iter = allpaths.begin(); iter != allpaths.end(); ++iter) {
                for (int i = 0; i < (*iter).size(); ++i) {
                    cout << map2[(*iter)[i]];
                    if (map1[word2] != (*iter)[i]) {
                        cout << " -> ";
                    }
                }
                cout << endl;
            }
        }
    }
}

int Graph::minDistance(int dist[], int sptSet[]) {
    // 初始化最小距离为无穷大
    int min = INT_MAX, min_index;

    for (int v = 0; v < size; v++)
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    return min_index;
}

void Graph::dijkstra(int src, int dest, vector<vector<int>>& allpaths, vector<int>& path) {
    int dist[size - 1];  // dist[i]将保存从源点到顶点i的最短路径长度
    int sptSet[size - 1];  // sptSet[i]为真，如果顶点i包含在最短路径树中或最短路径已被确定
    vector<vector<int>> preNodes(size);
    for (int i = 0; i <= size - 1; i++) {
        if (graph[src][i] == 0) {
            dist[i] = INT_MAX;
            // preNodes[i].push_back(-1);//www 下次不写递归了
        } else {
            dist[i] = graph[src][i];
            preNodes[i].push_back(src);
        }
        sptSet[i] = 0;
    }
    dist[src] = 0;
    sptSet[src] = true;

    for (int count = 0; count <= size - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;
        for (int v = 0; v < size; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                preNodes[v].clear();
                preNodes[v].push_back(u);
            } else if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] == dist[v]) {
                preNodes[v].push_back(u);
            }
        }
    }
    // 根据每个节点前驱节点得到从src到dest最短路径
    findPaths(src, dest, preNodes, path, allpaths);
}

void Graph::findPaths(int src, int dest, vector<vector<int>>& preNodes, vector<int>& path,
                      vector<vector<int>>& allpaths) {
    path.push_back(dest);
    if (dest == src) {
        vector<int> temp = path;
        reverse(temp.begin(), temp.end());
        allpaths.push_back(temp);
    } else {
        for (int i = 0; i < preNodes[dest].size(); i++) {
            findPaths(src, preNodes[dest][i], preNodes, path, allpaths);
        }
    }
    path.pop_back();
}

// 随机游走
string Graph::randomWalk() {
    vector<int> path;
    // 随机选择一个节点遍历，如果对应边已经走过，则把i,j设置为true
    srand(static_cast<unsigned int>(time(nullptr)));
    int random_number = (rand()) % size;
    cout << "random_number" << random_number << endl;
    scan(path, random_number);
    int _size = path.size();
    string str = "";
    for (int i = 0; i < _size; i++) {
        str = str + map2[path[i]] + " ";
    }
    return str;
}

// 随机游走
void Graph::scan(vector<int>& path, int src) {
    bool temp[size][size] = {{0}};
    string str = "";
    int count = 0;
    path.push_back(src);
    while (true) {
        str = "";
        count = 0;
        // 随机游走
        for (int i = 0; i < size; i++) {
            if (graph[src][i] != 0) {
                str = str + map2[i] + " ";
                count++;
            }
        }
        if (count != 0) {
            str = chooseOne(str, count);
            if (temp[src][map1[str]]) {
                src = map1[str];
                path.push_back(src);
                break;
            } else {
                temp[src][map1[str]] = true;
                src = map1[str];
                path.push_back(src);
            }
        } else {
            break;
        }
    }
}
