#include <array>
#include <chrono>
#include <iostream>
#include <fstream>
#include <random>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>

#include "../include/edge_tuple.hpp"

using adj_list = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
using adj_matrix = boost::adjacency_matrix<boost::directedS>;

extern std::size_t iterate_all_edges_adj_list(const adj_list&);
extern std::size_t iterate_all_edges_adj_matrix(const adj_matrix&);

std::pair<std::size_t, std::size_t> do_measurement(const std::size_t vertex_count) {
	const std::size_t edge_count = 0;

	std::unordered_set<edge_tuple> edges_set;
	std::vector<edge_tuple> edges;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, vertex_count - 1);

	// Generate random edges between the vertices.
	// Ensure no parallel edges exist.
	while (edges_set.size() < edge_count) {
		const std::size_t source = distrib(gen);
		const std::size_t target = distrib(gen);

		const edge_tuple edge = { source, target };

		edges_set.insert(edge);
	}

	for (const edge_tuple& e : edges_set) {
		edges.push_back(e);
	}
	
	adj_list g_adj_list(edges.cbegin(), edges.cend(), vertex_count);
	adj_matrix g_adj_mat(edges.cbegin(), edges.cend(), vertex_count);
	
	const std::size_t DRY_RUNS = 10;

	// Adj list
	std::size_t total_micros_adj_list = 0;
	{
		const std::size_t AMOUNT_OF_MEASUREMENTS = 100'000;
		
		for (std::size_t i = 0; i < AMOUNT_OF_MEASUREMENTS + DRY_RUNS; i++) {
			const auto t_start = std::chrono::high_resolution_clock::now();
			iterate_all_edges_adj_list(g_adj_list);
			const auto t_end = std::chrono::high_resolution_clock::now();

			if (i < DRY_RUNS) {
				continue;
			}

			const std::size_t diff_in_micros = std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();

			total_micros_adj_list += diff_in_micros;
		}
	}

	// Adj matrix
	std::size_t total_micros_adj_matrix = 0;
	{
		const std::size_t AMOUNT_OF_MEASUREMENTS = 1'000;

		for (std::size_t i = 0; i < AMOUNT_OF_MEASUREMENTS + DRY_RUNS; i++) {
			const auto t_start = std::chrono::high_resolution_clock::now();
			iterate_all_edges_adj_matrix(g_adj_mat);
			const auto t_end = std::chrono::high_resolution_clock::now();

			if (i < DRY_RUNS) {
				continue;
			}

			const std::size_t diff_in_micros = std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();

			total_micros_adj_matrix += diff_in_micros;
		}
	}

	return std::make_pair(total_micros_adj_list, total_micros_adj_matrix);
}

int main() {
	std::cout << "Running measurements for Boost Graph" << std::endl;

	std::ofstream file;
	file.open("measurements.tsv", std::ios::out | std::ios::trunc);
	file << "V\tadj_list (micros)\tadj_matrix (micros)" << std::endl;

	for (std::size_t v = 500; v <= 10'000; v += 250) {
		for (std::size_t i = 0; i < 5; i++) {
			const auto [total_micros_adj_list, total_micros_adj_matrix] = do_measurement(v);
			file << v << "\t" << total_micros_adj_list << "\t" << total_micros_adj_matrix << std::endl;
			std::cout << v << "\t" << total_micros_adj_list << "\t" << total_micros_adj_matrix << std::endl;
		}
	}
}
