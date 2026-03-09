#ifndef FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H
#define FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H

#include <string>
#include <vector>
#include <variant>

enum Command {
	Determinant = 1, Inverse = 2, Transponent = 3, Rank = 4, Multiplication = 6,
	Sum = 7, Difference = 8, Identity = 9, Swap = 10
};

class Lookalikeness{
private:
	std::string written;
	std::pair<std::string, int> match;
	double level;
public:
	Lookalikeness(const std::string s, const std::vector<std::pair<std::string, int>>& v) : written(s), match(std::make_pair("temp", 0)), level(0) {
		for (std::pair<std::string, int> t : v) {
			unsigned long f = std::min(t.first.size(), written.size());
			unsigned long score = 0;
			for (unsigned long i = 0; i < f; i++) {
				if (t.first[i] == written[i]) {
					score++;
				}
			}
			score = score / written.size();
			if (level < score) {
				level = score;
				match = t;
			}
		}
	}
	std::variant<Command, int, bool> commandTranslation() {
		if (level > 0,7) {
			if (match.second != 5){
				return static_cast<Command>(match.second);
			}
			else {
				std::string s;
				for (char i : written) {
					if (i < 58 && i >47) {
						s = s + i;
					}
				}
				if (s != "") {
					int x = 0;
					x = std::stoi(s);
					return x;
				} else {
					return Multiplication;
				}
			}
		}
		return false;
	}
};

#endif //FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H