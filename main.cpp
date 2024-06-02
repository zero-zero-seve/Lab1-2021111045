#include <fstream>
#include <iostream>
#include <limits>

#include "graph.h"
#include "readFile.h"

using namespace std;

int main(int argc, char const *argv[]) {
    map<string, int> map1;
    map<int, string> map2;
    string str = readFileFromTxt("./text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    showMap2(map2);
    graph.initGraph();
    graph.storeGraph();
    cout << "1. Show Graph" << endl;
    cout << "2. Query Bridge Words" << endl;
    cout << "3. Generate New Text" << endl;
    cout << "4. Calculate Shortest Path" << endl;
    cout << "5. Random Walk" << endl;
    cout << "6. Exit" << endl;
    while (true) {
        int action;
        string word1, word2, result;
        ofstream output;
        cout << "Please enter action you want to perform" << endl;
        cin >> action;
        switch (action) {
            case 1:
                graph.showGraph();
                break;
            case 2:
                cout << "Please enter word1" << endl;
                cin >> word1;
                cout << "Please enter word2" << endl;
                cin >> word2;
                result = graph.queryBridgeWords(word1, word2);
                cout << result << endl;
                break;
            case 3:
                // cin.clear();
                // fflush(stdin);
                cout << "Please enter text" << endl;
                getchar();

                getline(cin, word1);
                result = graph.generateNewText(word1);
                cout << result << endl;
                break;
            case 4:
                char c;
                cout << "Please enter word1" << endl;
                cin >> word1;
                cout << "Do you want to enter word2 , y for yes or n for no" << endl;
                cin >> c;
                if (c == 'y') {
                    cout << "Please enter word2" << endl;
                    cin >> word2;
                    graph.calcShortestPath(word1, word2);
                } else if (c == 'n') {
                    graph.calcShortestPath(word1, "");
                }
                break;
            case 5:
                result = graph.randomWalk();
                output.open("randomwalk.txt");
                output << result;
                output.close();
                break;
            case 6:
                goto label;
            default:
                cout << "Invalid Action" << endl;
                cin.clear();   // 清除错误标志
                cin.ignore();  // 忽略错误输入，直到遇到换行符
                getline(cin, word1);
                break;
        }
    }
label:
    return 0;
}
