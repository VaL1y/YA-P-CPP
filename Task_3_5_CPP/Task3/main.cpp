#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <typeinfo>

template <typename T>
class DirectedGraph {
private:
    std::unordered_map<T, std::vector<T>> adjacency_list;

public:
    // Добавить вершину
    void add_vertex(const T& vertex) {
        if (adjacency_list.find(vertex) == adjacency_list.end()) {
            adjacency_list[vertex] = std::vector<T>();
        }
    }

    // Добавить ребро
    void add_edge(const T& from, const T& to) {
        add_vertex(from);  // убедимся, что обе вершины существуют
        add_vertex(to);
        adjacency_list[from].push_back(to);
    }

    // Вывести смежные вершины
    void print_adjacent(const T& vertex) const {
        if (adjacency_list.find(vertex) != adjacency_list.end()) {
            std::cout << "Vertex, adjacent with " << vertex << ": ";
            for (const auto& adjacent : adjacency_list.at(vertex)) {
                std::cout << adjacent << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Vertex " << vertex << " not found" << std::endl;
        }
    }

    // Вывести граф
    void print_graph() const {
        for (const auto& pair : adjacency_list) {
            std::cout << pair.first << " -> ";
            for (const auto& adjacent : pair.second) {
                std::cout << adjacent << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    // Пример использования графа с типом int
    DirectedGraph<int> int_graph;
    int_graph.add_vertex(1);
    int_graph.add_vertex(2);
    int_graph.add_vertex(2);
    int_graph.add_edge(1, 2);
    int_graph.add_edge(2, 3);
    std::cout << "Graf (int):" << std::endl;
    int_graph.print_graph();
    int_graph.print_adjacent(1);
    int_graph.print_adjacent(2);
    int_graph.print_adjacent(3);

    std::cout << std::endl;

    // Пример использования графа с типом std::string
    DirectedGraph<std::string> string_graph;
    string_graph.add_vertex("A");
    string_graph.add_vertex("B");
    string_graph.add_edge("A", "B");
    string_graph.add_edge("B", "C");
    std::cout << "Graf (string):" << std::endl;
    string_graph.print_graph();
    string_graph.print_adjacent("A");
    string_graph.print_adjacent("B");
    string_graph.print_adjacent("C");

    return 0;
}
