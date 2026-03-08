#ifndef FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H
#define FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H

#include <optional>
#include <string>
#include <vector>
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
			score = score / f;
			if (level < score) {
				level = score;
				match = t;
			}
		}
	}
	std::optional<int> commandNumber() {
		if (level > 0,7) {
			return match.second;
		}
		return std::nullopt;
	}
};

#endif //FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H