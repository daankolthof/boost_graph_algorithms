#include <array>
#include <iostream>

#include <boost/graph/adjacency_list.hpp>

struct edge_tuple {
	using first_type = std::size_t;
	using second_type = std::size_t;

	first_type first;
	second_type second;
};

void remove_vertex() {
}
