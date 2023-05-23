#include <iostream>
#include <vector>
#include <random>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>

std::size_t iterate_all_edges_adj_list(const boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>& g) {
	std::size_t result = 0;

	auto [vertex_iterator_begin, vertex_iterator_end] = boost::vertices(g);
	while (vertex_iterator_begin != vertex_iterator_end) {
		auto [edges_iterator_begin, edges_iterator_end] = boost::out_edges(*vertex_iterator_begin, g);
		while (edges_iterator_begin != edges_iterator_end) {
			//result += ((*edges_iterator_begin).m_source + (*edges_iterator_begin).m_target);
			result += 1;

			edges_iterator_begin++;
		}

		vertex_iterator_begin++;
	}

	return result;
}

std::size_t iterate_all_edges_adj_matrix(const boost::adjacency_matrix<boost::directedS>& g) {
	std::size_t result = 0;

	auto [vertex_iterator_begin, vertex_iterator_end] = boost::vertices(g);
	while (vertex_iterator_begin != vertex_iterator_end) {
		auto [edges_iterator_begin, edges_iterator_end] = boost::out_edges(*vertex_iterator_begin, g);
		while (edges_iterator_begin != edges_iterator_end) {
			//result += ((*edges_iterator_begin).m_source + (*edges_iterator_begin).m_target);
			result += 1;

			edges_iterator_begin++;
		}

		vertex_iterator_begin++;
	}

	return result;
}
