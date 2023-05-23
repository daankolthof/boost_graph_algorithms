#include <array>
#include <iostream>

#include <boost/graph/adjacency_list.hpp>

struct edge_tuple {
	using first_type = std::size_t;
	using second_type = std::size_t;

	first_type first;
	second_type second;
};

void list_as_vertexlist() {
	const std::size_t vertex_count = 3;
	const std::size_t edge_count = 2;

	const std::array<edge_tuple, edge_count> edges = { { {0, 1}, {1, 2} } };


	using undirected_unweighted_graph = boost::adjacency_list<boost::listS, boost::listS, boost::undirectedS>;
	undirected_unweighted_graph g(edges.cbegin(), edges.cend(), vertex_count);

	auto [vertex_iterator_begin, vertex_iterator_end] = boost::vertices(g);
	boost::remove_vertex(*vertex_iterator_begin, g);
}
