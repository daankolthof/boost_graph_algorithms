#include <array>
#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/astar_search.hpp>

#include "../../include/edge_tuple.hpp"

class astar_visitor_impl : public boost::default_astar_visitor {
public:
	template < class Vertex, class Graph >
	void examine_vertex(Vertex u, Graph& g)
	{
		std::cout << "Visited node: " << u << std::endl;
	}
};

template < class Graph, class CostType >
class astar_heuristic_impl : public boost::astar_heuristic<Graph, CostType> {
public:
    typedef typename boost::graph_traits< Graph >::vertex_descriptor Vertex;

    CostType operator()(Vertex u) const {
        // For simplicity, our goal state will always be 6, the closer the current vertex descriptor is to 6, the better.
        return abs(6 - u);
    }
};

void a_star() {
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
    const std::array<std::size_t, edge_count> edge_weights = { 1, 1, 1, 1, 1, 1 };

	using undirected_unweighted_graph = boost::adjacency_list<
        boost::listS,
        boost::vecS,
        boost::directedS,
        boost::no_property,
        boost::property<
            boost::edge_weight_t,
            std::size_t>>;

    undirected_unweighted_graph g(edges.cbegin(), edges.cend(), edge_weights.cbegin(), vertex_count);

    astar_visitor_impl vis;
    astar_heuristic_impl<undirected_unweighted_graph, std::size_t> heur;

    // Expected order: {0, 2, 6, 5, 1, 4, 3}
    boost::astar_search(
        g,
        0u,
        heur,
        boost::visitor(vis)
    );
}

int main() {
    a_star();
}
