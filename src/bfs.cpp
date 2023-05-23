#include <array>
#include <iostream>
#include <queue>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/edge_coloring.hpp>
#include <boost/graph/edge_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graph_archetypes.hpp>
#include <boost/property_map/shared_array_property_map.hpp>
#include <boost/property_map/vector_property_map.hpp>

/**
 * Describes an edge within the graph.
 * Boost Graph will require the fields first and second to be present.
 */
struct edge_tuple {
	using first_type = std::size_t;
	using second_type = std::size_t;

	first_type first;
	second_type second;
};

class bfs_visitor_impl : public boost::default_bfs_visitor {
public:
	template < class Vertex, class Graph >
	boost::graph::bfs_visitor_event_not_overridden examine_vertex(Vertex u, Graph& g)
	{
		std::cout << "Visited node: " << u << std::endl;
		return boost::graph::bfs_visitor_event_not_overridden();
	}
};


void bfs_example() {
	const std::size_t vertex_count = 5;
	const std::size_t edge_count = 5;

	const std::array<edge_tuple, edge_count> edges = { { {0, 1}, {1, 2}, {2, 3}, {3, 4}, {0, 1} } };

	
	using undirected_unweighted_graph = boost::adjacency_list<boost::listS, boost::vecS, boost::directedS>;
	

	//using undirected_unweighted_graph = boost::edge_list< std::array<edge_tuple, edge_count>::const_iterator>;

	undirected_unweighted_graph g(edges.cbegin(), edges.cend(), vertex_count);
	//undirected_unweighted_graph g(edges.cbegin(), edges.cend());




	boost::queue<std::size_t> queue;
	boost::vector_property_map <std::size_t > color_boost_map;
	bfs_visitor_impl vis;

	boost::graph_traits<undirected_unweighted_graph>::vertex_descriptor start_vertex = 0;

	boost::breadth_first_search(g, start_vertex, queue, vis, color_boost_map);

	{
		auto [vi_begin, vi_end] = boost::vertices(g);
		auto [ei_begin, ei_end] = boost::out_edges(*vi_begin, g);

		while (ei_begin != ei_end) {
			std::cout << *ei_begin << std::endl;
			ei_begin++;
		}


	}

	{
		std::cout << "Removing vertex 0" << std::endl;

		//boost::remove_vertex(0, g);
		auto [vi_begin, vi_end] = boost::vertices(g);
		/*
		while (vi_begin != vi_end) {
			std::cout << *vi_begin << std::endl;
			vi_begin++;
		}
		*/

		boost::remove_vertex(*vi_begin, g);
	}
}
