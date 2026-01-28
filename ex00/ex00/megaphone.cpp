#include <cctype>
#include <string>
#include <iostream>

std::string to_upper(std::string s) {
	for (size_t i = 0; i < s.length(); ++i) {
		s[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(s[i])));
	}
	return s;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 0;
	}

	for (int i = 1; i < argc - 1; ++i) {
		std::string original_string = argv[i];
		std::string upper_string = to_upper(original_string);
		std::cout << upper_string << " ";
	}
	std::string original_string = argv[argc - 1];
	std::string upper_string = to_upper(original_string);
	std::cout << upper_string << std::endl;
	return 0;
}
