#include <array>
#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>

#include "../../include/edge_tuple.hpp"

class bfs_visitor_impl : public boost::default_bfs_visitor {
public:
	template < class Vertex, class Graph >
	void examine_vertex(Vertex u, Graph& g)
	{
		std::cout << "Visited node: " << u << std::endl;
	}
};

void bfs() {
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

    undirected_unweighted_graph g(edges.cbegin(), edges.cend(), vertex_count);
    bfs_visitor_impl vis;

    // A correct order would be: {0, 1, 2, 3, 4, 5, 6}
    boost::breadth_first_search(g, 0u, boost::visitor(vis));
}

int main() {
    bfs();
}
