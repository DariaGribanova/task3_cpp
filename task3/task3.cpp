#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Graph
{
public:
    Graph() {
    }

    Graph(int num_vertices)
    {
        edges.resize(num_vertices);
    }

    void add_vertex() {
        int num_vertices = edges.size();
        std::vector<std::pair<int, T>> empty_vector;
        edges.emplace_back(empty_vector);
    }

    void add_edge(int from, int to, T weight = T{})
    {
        if (to > edges.size()) {
            return;
        }
        edges[from].emplace_back( to, weight );
    }

    void remove_edge(int from, int to)
    {
        auto new_end = std::remove_if(edges[from].begin(), edges[from].end(),
            [to](const std::pair<int, T>& e) { return e.first == to; });
        edges[from].erase(new_end, edges[from].end());
    }

    void remove_vertex(int vertex)
    {
        edges[vertex].clear();
        for (auto& v : edges)
        {
            auto new_end = std::remove_if(v.begin(), v.end(),
                [vertex](const std::pair<int, T>& e) { return e.first == vertex; });
            v.erase(new_end, v.end());
        }
    }

    std::vector<std::pair<int, T>> get_neighbors(int vertex)
    {
        return edges[vertex];
    }

    std::vector<std::vector<std::pair<int, T>>> get_vertex()
    {
        return edges;
    }

    //`edges` хранит список смежности графа, где каждый элемент представляет собой вектор пар `std::pair<int, T>`. 
    //В каждой паре первый элемент - это номер вершины, смежной с данной, а второй элемент - вес ребра.
    //Таким образом, `edges` представляет собой вектор векторов, 
    //где каждый вектор - это список смежности для соответствующей вершины.
    //Все смежные вершины для данной вершины хранятся в векторе `std::vector<std::pair<int, T>>`. 

private:
    std::vector<std::vector<std::pair<int, T>>> edges;
};

int main()
{
    //Пример на строках
    Graph<string> g(0);
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    g.add_edge(0, 2, "0to2");
    g.add_edge(1, 2, "1to2");
    g.add_edge(1, 3, "1to3");
    g.add_edge(1, 4, "1to4");
    g.add_edge(2, 3, "2to3");
    g.add_edge(3, 4, "3to4");
    g.add_edge(3, 2, "3to2");
    g.add_edge(4, 1, "4to1");
    g.remove_edge(1, 3);

    auto vertex = g.get_vertex();
    int i = 0;
    for (const auto& n : vertex)
    {
        std::cout << "Neighbors of vertex "<<i<<":" << std::endl;
        auto neighbors = g.get_neighbors(i);
        for (const auto& n : neighbors)
        {
            std::cout << n.first << " (" << n.second << ")" << std::endl;
        }
        i++;
    }

    std::cout << std::endl;

    //Пример на числах
    Graph<int> k(0);
    k.add_vertex();
    k.add_vertex();
    k.add_vertex();
    k.add_vertex();
    k.add_edge(0, 2, 2);
    k.add_edge(1, 2, 12);
    k.add_edge(1, 3, 13);
    k.add_edge(2, 3, 23);
    k.add_edge(3, 2, 32);
    k.add_edge(3, 0, 30);
   

    auto vert = k.get_vertex();
    int j = 0;
    for (const auto& n : vert)
    {
        std::cout << "Neighbors of vertex " << j << ":" << std::endl;
        auto neighbors = k.get_neighbors(j);
        for (const auto& n : neighbors)
        {
            std::cout << n.first << " (" << n.second << ")" << std::endl;
        }
        j++;
    }

    return 0;
}
