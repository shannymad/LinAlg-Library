#pragma once
#include "matrix.hpp"
#include "exceptions.hpp"
#include <cmath>
#include <limits>

namespace linalg {

template <typename T>
T compute_determinant_gauss(Matrix<T> m) {
    if (m.rows() != m.cols()) {
        throw DimensionError("Determinant requires square matrix");
    }

    std::size_t n = m.rows();
    if (n == 0) {
        return T{1};
    }

    T determinant = T{1};
    const T eps = std::numeric_limits<T>::epsilon() * 1000;

    for (std::size_t col = 0; col < n; ++col) {
        std::size_t pivot_row = col;
        for (std::size_t row = col + 1; row < n; ++row) {
            if (std::abs(m.at(row, col)) > std::abs(m.at(pivot_row, col))) {
                pivot_row = row;
            }
        }

        if (std::abs(m.at(pivot_row, col)) < eps) {
            return T{0};
        }

        if (pivot_row != col) {
            for (std::size_t k = 0; k < n; ++k) {
                std::swap(m.data_[col * n + k], m.data_[pivot_row * n + k]);
            }
            determinant = -determinant;
        }

        determinant *= m.at(col, col);

        for (std::size_t row = col + 1; row < n; ++row) {
            T factor = m.at(row, col) / m.at(col, col);
            for (std::size_t k = col; k < n; ++k) {
                m.data_[row * n + k] -= factor * m.data_[col * n + k];
            }
        }
    }

    return determinant;
}

template <typename T>
Matrix<T> solve_linear_system(const Matrix<T>& A, const Matrix<T>& b) {
    if (A.rows() != A.cols()) {
        throw DimensionError("A must be square");
    }
    
    if (A.rows() != b.rows() || b.cols() != 1) {
        throw DimensionError("b must be a column vector with the same number of rows as A");
    }

    std::size_t n = A.rows();
    const T eps = std::numeric_limits<T>::epsilon() * 1000;
    
    Matrix<T> aug(n, n + 1);
    
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            aug.set(i, j, A.at(i, j));
        }
        aug.set(i, n, b.at(i, 0));
    }
    
    for (std::size_t col = 0; col < n; ++col) {
        std::size_t pivot_row = col;
        for (std::size_t row = col + 1; row < n; ++row) {
            if (std::abs(aug.at(row, col)) > std::abs(aug.at(pivot_row, col))) {
                pivot_row = row;
            }
        }
        
        if (std::abs(aug.at(pivot_row, col)) < eps) {
            throw SingularMatrixError();
        }
        
        if (pivot_row != col) {
            for (std::size_t k = 0; k <= n; ++k) {
                std::swap(aug.data_[col * (n + 1) + k], aug.data_[pivot_row * (n + 1) + k]);
            }
        }
        
        for (std::size_t row = col + 1; row < n; ++row) {
            T factor = aug.at(row, col) / aug.at(col, col);
            for (std::size_t k = col; k <= n; ++k) {
                aug.set(row, k, aug.at(row, k) - factor * aug.at(col, k));
            }
        }
    }
    
    Matrix<T> x(n, 1);
    for (std::size_t i = n; i-- > 0;) {
        T sum = aug.at(i, n);
        for (std::size_t j = i + 1; j < n; ++j) {
            sum -= aug.at(i, j) * x.at(j, 0);
        }
        x.set(i, 0, sum / aug.at(i, i));
    }
    
    return x;
}

}