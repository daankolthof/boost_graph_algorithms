#include <array>
#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>

#include "../../include/edge_tuple.hpp"

void topological_sort() {
    const std::size_t vertex_count = 7;
	const std::size_t edge_count = 6;

    /*
        Graph structure
                0
               / \
              /   \
             1     2
            / \   / \
           3  4  5   6
    */
	const std::array<edge_tuple, edge_count> edges = { { {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6} } };

	using undirected_unweighted_graph = boost::adjacency_list<boost::listS, boost::vecS, boost::directedS>;
    using vertex_descriptor = boost::graph_traits<undirected_unweighted_graph>::vertex_descriptor;

    undirected_unweighted_graph g(edges.cbegin(), edges.cend(), vertex_count);
    std::array<vertex_descriptor, vertex_count> result_order;

    // A correct order would be: {3, 4, 1, 5, 6, 2, 0}
    boost::topological_sort(g, result_order.begin());

    for (const vertex_descriptor& v : result_order) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

int main() {
    topological_sort();
}
