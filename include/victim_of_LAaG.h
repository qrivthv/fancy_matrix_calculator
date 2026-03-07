#ifndef FANCY_MATRIX_CALCULATOR_1_VICTIM_OF_LAAG_H
#define FANCY_MATRIX_CALCULATOR_1_VICTIM_OF_LAAG_H
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "victim_of_LAaG.h"
class v_of_LAaG;
class Identity;
inline std::ostream& operator<<(std::ostream& out, const v_of_LAaG & a);
double eps = 10e-6;
class v_of_LAaG {
protected:
    std::vector<std::vector<double>> aaaa;
    size_t n;
    size_t m;
public:
    v_of_LAaG() : aaaa{}, n(0), m(0) {}
    v_of_LAaG(size_t r) : aaaa{}, n(r), m(r) {
        aaaa = std::vector<std::vector<double>>(n, std::vector<double>(m, 0));
    }
    v_of_LAaG(size_t r, size_t col) : aaaa{}, n(r), m(col) {
        aaaa = std::vector<std::vector<double>>(n, std::vector<double>(m, 0));
    }
    v_of_LAaG(size_t r, size_t col, const std::vector<double> &data) : aaaa{}, n(r), m(col) {
        aaaa = std::vector<std::vector<double>>(n, std::vector<double>(m, 0));
        for (size_t i = 0; i < std::min(data.size(), n*m); i++) {
            aaaa[i/m][i%m] = data[i];
        }
    }
    v_of_LAaG(const std::vector<std::vector<double>> &data) : aaaa{}, n(data.size()), m(0) {
        if (n!=0) m = data[0].size();
        aaaa = data;
    }
    v_of_LAaG(const v_of_LAaG &data) : aaaa{data.aaaa}, n(data.n), m(data.m) {}

    v_of_LAaG& operator=(const std::vector<std::vector<double>> &data)  {
        reset();
        aaaa = data;
        n = data.size();
        if (n != 0) m = data[0].size();
        return *this;
    }
    v_of_LAaG& operator=(const v_of_LAaG &data)  {
        reset();
        aaaa = data.aaaa;
        n = data.n;
        m = data.m;
        return *this;
    }
    //TODO add dushnye move shtuky
    //TODO be happy (nope, not today)

    v_of_LAaG operator+ (const v_of_LAaG & wit) const {
        if (n != wit.n || m != wit.m) throw std::runtime_error("Что вы делаете, сударь?.. У вашихъ матрицъ разные размеры!");
        std::vector<std::vector<double>> nn = aaaa;
        for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < m; j++) nn[i][j] += wit.aaaa[i][j];
        }
        return nn;
    }
    v_of_LAaG operator- (const v_of_LAaG & wit) const {
        if (n != wit.n || m != wit.m) throw std::runtime_error("Что вы делаете, сударь?.. У вашихъ матрицъ разные размеры!");
        std::vector<std::vector<double>> nn = aaaa;
        for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < m; j++) nn[i][j] -= wit.aaaa[i][j];
        }
        return nn;
    }
    v_of_LAaG operator* (const v_of_LAaG & wit) const {
        if (m != wit.n) throw std::runtime_error("Что вы делаете, сударь?.. У вашихъ матрицъ неверные размеры!");
        std::vector<std::vector<double>> nn = std::vector<std::vector<double>>(n, std::vector<double>(wit.m, 0));
        for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < wit.m; j++) {
                for (size_t ii = 0; ii < m; ii++) {
                    nn[i][j] += aaaa[i][ii]*wit.aaaa[ii][j];
                }
            }
        }
        return nn;
    }
    v_of_LAaG operator* (double x) const {
        std::vector<std::vector<double>> nn = aaaa;
        for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < m; j++) {
                nn[i][j] *=x;
            }
        }
        return nn;
    }
     bool operator==(const v_of_LAaG & wit) const {
        return (n == wit.n && m == wit.m && aaaa == wit.aaaa);
    }

    void t(const size_t& r1, const size_t &r2) {
        if (r1 >= n || r2 >= n) throw std::runtime_error("Сударь, будьте внимательнее!");
        std::vector<double> a = aaaa[r1];
        aaaa[r1] = aaaa[r2];
        aaaa[r2] = a;
    }
    void l(const size_t& r1, const size_t& r2, const double &lambda) {
        for (size_t j = 0; j < m; j++) {
            aaaa[r1][j] += aaaa[r2][j]*lambda;
            if (std::abs(aaaa[r1][j]) < eps) aaaa[r1][j] = 0;
        }
    }
    void d(const size_t &r, const double &lambda) {
        for (size_t j = 0; j < m; j++) {
            if (aaaa[r][j] != 0 && std::abs(lambda - 1/aaaa[r][j]) < eps) { aaaa[r][j] = 1; }
            else aaaa[r][j] *= lambda;
        }
    }

    bool is_rref() const {
        bool zero_fl = false;
        size_t last_leading = 0;
        std::vector<double> zero = std::vector<double>(m, 0.0);
        for (size_t i = 0; i < n; i++) {
            if (aaaa[i] == zero) zero_fl = true;
            else {
                if (zero_fl) return false;
                for (size_t j = 0; j < m; j++) {
                    if (aaaa[i][j] != 0 && j <= last_leading) return false;
                    if (aaaa[i][j] != 0 && aaaa[i][j] != 1) return false;
                    if (aaaa[i][j] != 0 && aaaa[i][j] == 1) { last_leading = j; break; }
                }
                for (size_t j = 0; j < n; j++)
                    if (j != i && aaaa[j][last_leading] != 0) return false;
            }
        }
        return true;
    }

    v_of_LAaG transpose() const {
        v_of_LAaG a(m, n);
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++) a[j][i] = aaaa[i][j];
        return a;
    }
    v_of_LAaG rref() const {
        size_t cur = 0;
        size_t leading = 0;
        if (is_rref()) return *this;
        v_of_LAaG press_rre_F = *this;
        for (size_t i = 0; i < n; i++) {
            if (leading >= press_rre_F.m) break;
            cur = i;
            while (press_rre_F.aaaa[cur][leading] == 0) {
                cur += 1;
                if (cur == press_rre_F.n) {
                    leading++;
                    cur = i;
                }
                if (leading == press_rre_F.m) break;
            }
            press_rre_F.t(cur, i);

            if (press_rre_F.aaaa[i][leading] != 0) press_rre_F.d(i, (1.0/press_rre_F.aaaa[i][leading]));

            for (size_t j = 0; j < n; j++) {
                if (j != i && press_rre_F.aaaa[j][leading] != 0) press_rre_F.l(j, i, -1*press_rre_F.aaaa[j][leading]);
            }
            leading++;
        }
        return press_rre_F;
    }
    v_of_LAaG minor(size_t i, size_t j) const {
        if (i >= n || j >= m) throw std::out_of_range("Сударь, остановитесь!");
        v_of_LAaG mmm (n - 1, m - 1);
        double a = 0, b = 0;
        for (size_t ii = 0; ii < n; ii++) {
            if (ii == i) {a = 1; continue;}
            b = 0;
            for (size_t jj = 0; jj < m; jj++) {
                if (jj == j) {b = 1; continue;}
                mmm[ii - a][jj - b] = aaaa[ii][jj];
            }
        }
        return mmm;
    }
    double det() const {
        if (n != m) throw std::runtime_error("Сударь, детерминанта для этой матрицы не можетъ быть!");
        if (n == 2) return aaaa[0][0]*aaaa[1][1] - aaaa[0][1] * aaaa[1][0];
        double determinism = 0;
        for (size_t i = 0; i < n; i++) {
            determinism += aaaa[i][0]*minor(i, 0).det()*(i%2 == 0 ? 1 : -1);
        }
        return determinism;
    }
    v_of_LAaG inverse() const {
        if (m != n) throw std::runtime_error("Сударь, детерминанта для этой матрицы не можетъ быть!");
        if (det() == 0) throw std::runtime_error("Сударь, детерминанта для этой матрицы не можетъ быть!");
        v_of_LAaG aaa(n, 2*m);
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) aaa[i][j] = aaaa[i][j];
            aaa[i][i + m] = 1;
        }
        aaa = aaa.rref();
        v_of_LAaG inv(n, m);
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                inv[i][j] = aaa[i][j + m];
            }
        }
        return inv;
    }
    size_t rank() const {
        size_t rk = 0;
        std::vector<double> zero(m, 0.0);
        v_of_LAaG yay = rref();
        for (size_t i = 0; i < n; i++) {
            if (yay[i] == zero) return rk;
            rk++;
        }
        return rk;
    } //TODO rank table math

    size_t get_rows() const { return n; }
    size_t get_cols() const { return m; }
    std::vector<std::vector<double>> get_raw_matrix() const {return aaaa;}
    std::vector<std::vector<double>>& get_raw_matrix() {return aaaa;}
    std::vector<double>& operator[](size_t ind) {
        if (ind >= n) throw std::out_of_range("Сударь, остановитесь");
        return aaaa[ind];
    }
    std::vector<double> operator[](size_t ind) const {
        if (ind >= n) throw std::out_of_range("Сударь, остановитесь");
        return aaaa[ind];
    }
    friend void swap(v_of_LAaG & a, v_of_LAaG & b);
    void reset() {
        n = 0; m = 0;
        aaaa.resize(0);
    }
    ~v_of_LAaG() {
      reset();
    }
};

inline std::ostream& operator<<(std::ostream& out, const v_of_LAaG & a) {
    for (size_t i = 0; i < a.get_rows(); i++) {
        for (size_t j = 0; j < a.get_cols(); j++) out << std::setprecision(3) << a[i][j] << "\t";
        out << "\n";
    }
    return out;
}
void swap(v_of_LAaG & a, v_of_LAaG & b) {
    v_of_LAaG temp = a;
    a = b;
    b = temp;
    temp.reset();
}
class Identity : public v_of_LAaG {
public:
    Identity() : v_of_LAaG() {}
    Identity(size_t r) : v_of_LAaG(r) {
        for (size_t i = 0; i < n; i++) {
            aaaa[i][i] = 1;
        }
    }
    ~Identity() {
        reset();
    }
};
#endif //FANCY_MATRIX_CALCULATOR_1_VICTIM_OF_LAAG_H