#ifndef FANCY_MATRIX_CALCULATOR_1_VICTIM_OF_LAAG_H
#define FANCY_MATRIX_CALCULATOR_1_VICTIM_OF_LAAG_H
#include <stdexcept>
#include <vector>
template <typename T>
class v_of_LAaG {
private:
    std::vector<std::pmr::vector<T>> aaaa;
    size_t n;
    size_t m;
public:
    v_of_LAaG() : aaaa{}, n(0), m(0) {}
    v_of_LAaG(size_t r, size_t col) : aaaa{}, n(r), m(col) {
        aaaa = std::vector<std::vector<T>>(n, std::vector<T>(m, 0));
    }
    v_of_LAaG(size_t n, size_t m, const std::vector<T> &data) : aaaa{}, n(n), m(m) {
        aaaa = std::vector<std::vector<T>>(n, std::vector<T>(m, 0));
        for (size_t i = 0; i < min(data.size(), n*m); i++) {
            aaaa[i/n][n%i] = data[i];
        }
    }
    v_of_LAaG(const std::vector<std::vector<T>> &data) : aaaa{}, n(data.size(data)), m(0) {
        if (n!=0) m = data[0].size();
        aaaa = data;
    }
    //TODO add dushnye operatory =
    //TODO add dushnye move shtuky
     // TODO be happy

    v_of_LAaG operator+ (const v_of_LAaG & wit) {
        if (n != wit.n || m != wit.m) throw std::runtime_error("Что вы делаете, сударь?.. У вашихъ матрицъ разные размеры!");
        std::vector<std::vector<T>> nn = aaaa;
        for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < m; j++) nn[i][j] += wit.aaaa[i][j];
        }
        return nn;
    }
    v_of_LAaG operator- (const v_of_LAaG & wit) {
        if (n != wit.n || m != wit.m) throw std::runtime_error("Что вы делаете, сударь?.. У вашихъ матрицъ разные размеры!");
        std::vector<std::vector<T>> nn = aaaa;
        for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < m; j++) nn[i][j] -= wit.aaaa[i][j];
        }
        return nn;
    }
    v_of_LAaG operator* (const v_of_LAaG & wit) {
        if (m != wit.n) throw std::runtime_error("Что вы делаете, сударь?.. У вашихъ матрицъ неверные размеры!");
        std::vector<std::vector<T>> nn = std::vector<std::vector<int>>(n, std::vector<int>(wit.m, 0));
        for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < m; j++) {

            }
        }
        return n;
    }




    void reset() {
        n = 0; m = 0;
        aaaa = {};
    }
    ~v_of_LAaG() {
      reset();
    }

}
#endif //FANCY_MATRIX_CALCULATOR_1_VICTIM_OF_LAAG_H