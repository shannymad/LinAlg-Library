#pragma once
#include "include/linalg/matrix.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>
#include "include/linalg/exceptions.hpp"

namespace linalg {

template <typename T>
Matrix<T>::Matrix() = default;

template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols, const T& value)
    : rows_(rows), cols_(cols), data_(rows * cols, value) {}

template <typename T>
void Matrix<T>::check_index(std::size_t i, std::size_t j) const {
    if (i >= rows_ || j >= cols_) {
        std::string msg = "Trying to access (" + std::to_string(i) + ", " + std::to_string(j) +
                          ") in " + std::to_string(rows_) + "x" + std::to_string(cols_) + " matrix";
        throw IndexOutOfBounds(msg);
    }
}

template <typename T>
void Matrix<T>::check_dimensions(const Matrix<T>& other, const std::string& operation) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        std::string msg = "Cannot perform " + operation + ": dimensions mismatch (" +
                          std::to_string(rows_) + "x" + std::to_string(cols_) + " vs " +
                          std::to_string(other.rows_) + "x" + std::to_string(other.cols_) + ")";
        throw DimensionError(msg);
    }
}

template <typename T>
const T& Matrix<T>::at(std::size_t i, std::size_t j) const {
    check_index(i, j);
    return data_[i * cols_ + j];
}

template <typename T>
T& Matrix<T>::at(std::size_t i, std::size_t j) {
    check_index(i, j);
    return data_[i * cols_ + j];
}

template <typename T>
void Matrix<T>::set(std::size_t i, std::size_t j, const T& value) {
    check_index(i, j);
    data_[i * cols_ + j] = value;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    check_dimensions(other, "addition");
    Matrix<T> result(rows_, cols_);
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            result.set(i, j, this->at(i, j) + other.at(i, j));
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    check_dimensions(other, "subtraction");
    Matrix<T> result(rows_, cols_);
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            result.set(i, j, this->at(i, j) - other.at(i, j));
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar) const {
    Matrix<T> result(rows_, cols_);
    for (std::size_t k = 0; k < data_.size(); ++k) {
        result.data_[k] = data_[k] * scalar;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (cols_ != other.rows_) {
        throw DimensionError("Inner dimensions must match");
    }
    Matrix<T> result(rows_, other.cols_);
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < other.cols_; ++j) {
            T sum = T{};
            for (std::size_t k = 0; k < cols_; ++k) {
                sum += this->at(i, k) * other.at(k, j);
            }
            result.set(i, j, sum);
        }
    }
    return result;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }

    if constexpr (std::is_floating_point_v<T>) {
        const T eps = std::numeric_limits<T>::epsilon() * 100;
        for (std::size_t i = 0; i < data_.size(); ++i) {
            if (std::abs(data_[i] - other.data_[i]) > eps) {
                return false;
            }
        }
    } else {
        for (std::size_t i = 0; i < data_.size(); ++i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result(cols_, rows_);

    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            result.set(j, i, this->at(i, j));
        }
    }
    return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
    os << "[";
    for (std::size_t i = 0; i < m.rows_; ++i) {
        if (i > 0)
            os << "\n ";
        os << "[";
        for (std::size_t j = 0; j < m.cols_; ++j) {
            os << m.at(i, j);
            if (j + 1 < m.cols_)
                os << ", ";
        }
        os << "]";
    }
    os << "]";
    return os;
}

template <typename T>
Matrix<T> operator*(const T& scalar, const Matrix<T>& matrix) {
    return matrix * scalar;
}

}  // namespace linalg
