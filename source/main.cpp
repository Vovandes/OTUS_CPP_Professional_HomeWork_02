#include "ip_filter.hpp"

#include <fstream>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

// 113.162.145.156  111 0

int main(int, char const* []) {
	try {

		// std::ifstream in{ "ip_filter.tsv" };
		// std::cin.rdbuf(in.rdbuf());

		auto ip_pool{ input_ip() };

		auto vect_string_to_int{ vector_string_to_int(ip_pool) };

		reverse_lexicographically_sort(vect_string_to_int);

		print_ip(vect_string_to_int);

		print_ip(filter(vect_string_to_int, 1));

		print_ip(filter(vect_string_to_int, 46, 70));

		print_ip(filter_any(vect_string_to_int, 46));
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
