#include "../googletest-main/googletest/include/gtest/gtest.h"
#include "../src/graph.h"
#include "../src/readFile.h"

TEST(QUERY, bridgeWords_1) {
    map<string, int> map1;
    map<int, string> map2;
    string str =
        readFileFromTxt("C://Users//Lenovo//Desktop//lab3//2021111045-lab1//code//src//text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    showMap2(map2);
    graph.initGraph();
    graph.storeGraph();
    string result = graph.queryBridgeWords("the", "wants");
    string str2 = "heart";
    EXPECT_EQ(result, str2);
}

TEST(QUERY, bridgeWords_2) {
    map<string, int> map1;
    map<int, string> map2;
    string str =
        readFileFromTxt("C://Users//Lenovo//Desktop//lab3//2021111045-lab1//code//src//text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    showMap2(map2);
    graph.initGraph();
    graph.storeGraph();
    string result = graph.queryBridgeWords("wind", "a");
    string str2 = "in";
    EXPECT_EQ(result, str2);
}

TEST(QUERY, bridgeWords_3) {
    map<string, int> map1;
    map<int, string> map2;
    string str =
        readFileFromTxt("C://Users//Lenovo//Desktop//lab3//2021111045-lab1//code//src//text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    showMap2(map2);
    graph.initGraph();
    graph.storeGraph();
    string result = graph.queryBridgeWords("no", "a");
    string str2 = " ";
    EXPECT_EQ(result, str2);
}

TEST(WHITE, bridgeWords_1) {
    map<string, int> map1;
    map<int, string> map2;
    string str =
        readFileFromTxt("C://Users//Lenovo//Desktop//lab3//2021111045-lab1//code//src//text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    showMap2(map2);
    graph.initGraph();
    graph.storeGraph();
    string result = graph.queryBridgeWords("experience", "idea");
    string str2 = "No 'experience' and 'idea' in the graph!";
    EXPECT_EQ(result, str2);
}

TEST(WHITE, bridgeWords_2) {
    map<string, int> map1;
    map<int, string> map2;
    string str =
        readFileFromTxt("C://Users//Lenovo//Desktop//lab3//2021111045-lab1//code//src//text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    showMap2(map2);
    graph.initGraph();
    graph.storeGraph();
    string result = graph.queryBridgeWords("experience", "wants");
    string str2 = "No 'experience' in the graph!";
    EXPECT_EQ(result, str2);
}

TEST(WHITE, bridgeWords_3) {
    map<string, int> map1;
    map<int, string> map2;
    string str =
        readFileFromTxt("C://Users//Lenovo//Desktop//lab3//2021111045-lab1//code//src//text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    showMap2(map2);
    graph.initGraph();
    graph.storeGraph();
    string result = graph.queryBridgeWords("always", "idea");
    string str2 = "No 'idea' in the graph!";
    EXPECT_EQ(result, str2);
}

TEST(WHITE, bridgeWords_4) {
    map<string, int> map1;
    map<int, string> map2;
    string str =
        readFileFromTxt("C://Users//Lenovo//Desktop//lab3//2021111045-lab1//code//src//text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    showMap2(map2);
    graph.initGraph();
    graph.storeGraph();
    string result = graph.queryBridgeWords("wants", "always");
    string str2 = "it";
    EXPECT_EQ(result, str2);
}

TEST(WHITE, bridgeWords_5) {
    map<string, int> map1;
    map<int, string> map2;
    string str =
        readFileFromTxt("C://Users//Lenovo//Desktop//lab3//2021111045-lab1//code//src//text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    showMap2(map2);
    graph.initGraph();
    graph.storeGraph();
    string result = graph.queryBridgeWords("like", "backward");
    string str2 = "traveling";
    EXPECT_EQ(result, str2);
    str2 = "hello";
    EXPECT_EQ(result, str2);
}

TEST(WHITE, bridgeWords_6) {
    map<string, int> map1;
    map<int, string> map2;
    string str =
        readFileFromTxt("C://Users//Lenovo//Desktop//lab3//2021111045-lab1//code//src//text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    showMap2(map2);
    graph.initGraph();
    graph.storeGraph();
    string result = graph.queryBridgeWords("like", "a");
    string str2 = " ";
    EXPECT_EQ(result, str2);
}

TEST(WHITE, bridgeWords_7) {
    map<string, int> map1;
    map<int, string> map2;
    string str =
        readFileFromTxt("C://Users//Lenovo//Desktop//lab3//2021111045-lab1//code//src//text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    showMap2(map2);
    graph.initGraph();
    graph.storeGraph();
    string result = graph.queryBridgeWords("up", "a");
    string str2 = " ";
    EXPECT_EQ(result, str2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}