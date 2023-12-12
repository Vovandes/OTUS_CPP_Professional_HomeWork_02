#include "version.hpp"
#include "ip_filter.hpp"

int version() {
	return PROJECT_VERSION_PATCH;
}

std::vector<std::vector<std::string>> input_ip() {
	std::vector<std::vector<std::string>> tmp_ip;

	for (std::string line; std::getline(std::cin, line);) {
		std::vector<std::string> v = split(line, '\t');
		tmp_ip.push_back(split(v.at(0), '.'));
	}

	return tmp_ip;
}

std::vector<std::string> split(const std::string& str, char d) {
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	
	while (stop != std::string::npos) {
		r.push_back(str.substr(start, stop - start));
		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

std::vector<int> to_int(const std::vector<std::string>& Container) {
	std::vector<int> out;
	int tmp_value{};

	for (auto& str : Container) {
		if (auto tmp = std::from_chars(str.data(), str.data() + str.size(), tmp_value);
			tmp.ec != std::errc::invalid_argument && tmp.ec != std::errc::result_out_of_range) {
			out.push_back(tmp_value);
		}
		else {
			throw std::logic_error("can not convert IP component");
		}
	}

	return out;
}

std::vector<std::vector<int>> vector_string_to_int(std::vector<std::vector<std::string>>& Container) {
	std::vector<std::vector<int>> tmp_container;

	for (const auto& elem : Container) {
		tmp_container.push_back(to_int(elem));
	}

	return tmp_container;
}
