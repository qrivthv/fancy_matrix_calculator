#ifndef FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H
#define FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H

#include <string>
#include <vector>
class Text{
    private:
    std::string initial_text;
    std::vector<std::string> source;
	std::string actual_text;
	std::map<>
    public:
    Text(std::string s, std::vector) : initial_text(s){
	for (std::string t : source){if (initial_text == t){actual text = initial_text; break;}}
	std::vector<std::string> rub;
	for (size_t i = 2; i < initial_text.size() - 1; i++){
	std::string s = initial_text[i-2] + initial_text[i-1] + initial_text[i];
	rub.push_back(s);
	}

	};
    Operation Operate() {return op;}

}

#endif //FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H