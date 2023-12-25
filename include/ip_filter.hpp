#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <charconv> //C++17
#include <algorithm>

int version();

// Input IP:
std::vector<std::vector<std::string>> input_ip();

// String Tokenization:
std::vector<std::string> split(const std::string& str, char d);

// Print Functions:
template<typename Q>
auto print_ip(const std::vector<Q>& Container) {
	for (auto ip = Container.cbegin(); ip != Container.cend(); ++ip) {
		for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
			if (ip_part != ip->cbegin()) {
				std::cout << ".";
			}
			std::cout << *ip_part;
		}
		std::cout << std::endl;
	}
}

// Convert String To Int:
std::vector<int> to_int(const std::vector<std::string>& ip);
std::vector<std::vector<int>> vector_string_to_int(std::vector<std::vector<std::string>>& Container);

// Reverse lexicographically sort
template<typename Q>
auto reverse_lexicographically_sort(std::vector<Q>& Container) {
	std::sort(Container.begin(), Container.end(), std::greater<Q>());
}

// Filter by bytes:
template<typename Q, typename...Args>
auto filter(const std::vector<Q>& Container, Args const& ... args) {
	std::vector<Q> tmp_container;
	Q tmp_vector{ {args...} };

	if (tmp_vector.size() > 4) { throw std::logic_error("There are too many arguments!!!"); }
	if (std::find_if(tmp_vector.cbegin(), tmp_vector.cend(), [](const int val) { return val < 0 || val > 255; }) != tmp_vector.cend()) { throw std::logic_error("Incorrect values by filter!!!"); }

	std::copy_if(Container.cbegin(), Container.cend(), std::back_inserter(tmp_container),
		[&tmp_vector](const auto& elem) {
			bool is_true_flag = true;
			for (size_t i = 0; i < tmp_vector.size(); ++i) {
				if (elem[i] != tmp_vector[i]) {
					is_true_flag = false;
					break;
				}
			}
			return is_true_flag;
		});

	return tmp_container;
}

template<typename Q>
auto filter_any(const std::vector<Q>& Container, uint8_t byte) {
	std::vector<Q> tmp_container;

	std::copy_if(Container.cbegin(), Container.cend(), std::back_inserter(tmp_container),
		[byte](const auto& elem) { return std::find(elem.cbegin(), elem.cend(), byte) != elem.cend(); });

	return tmp_container;
}