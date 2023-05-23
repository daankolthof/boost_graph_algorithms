#pragma once

#include <functional>

struct edge_tuple {
	using first_type = std::size_t;
	using second_type = std::size_t;

	first_type first;
	second_type second;
};

bool operator==(const edge_tuple& A, const edge_tuple& B) {
	return A.first == B.first && A.second == B.second;
}

namespace std {
	template <>
	class hash<edge_tuple>
	{
	public:
		std::uint64_t operator()(const edge_tuple& edge_tuple) const
		{
			return edge_tuple.first * edge_tuple.second;
		}
	};
}
