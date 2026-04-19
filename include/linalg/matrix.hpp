#pragma once
#include "exceptions.hpp"
#include <cstddef>
#include <iostream>
#include <vector>
#include <type_traits> 

namespace linalg {
    template<typename T>
class Matrix {
public : 
Matrix();

explicit Matrix(std::size_t rows, std::size_t cols, const T& value = 0.0);

Matrix(const Matrix &) = default;
Matrix &operator=(const Matrix &) = default;
Matrix(Matrix &&) noexcept = default;
Matrix &operator=(Matrix &&) noexcept = default;

[[nodiscard]] std::size_t rows() const noexcept { return rows_; }

[[nodiscard]] std::size_t cols() const noexcept { return cols_; }

T&  at(std::size_t i, std::size_t j);
const T& at(std::size_t i, std::size_t j) const;
void set(std::size_t i, std::size_t j, const T& value);

[[nodiscard]] Matrix<T> operator+(const Matrix<T> &other) const;
[[nodiscard]] Matrix<T> operator-(const Matrix<T> &other) const;

[[nodiscard]] Matrix<T> operator*(const Matrix<T> &other) const;

[[nodiscard]] Matrix<T> operator*(const T& scalar) const;


[[nodiscard]] bool operator==(const Matrix<T>& other) const;

[[nodiscard]] Matrix<T> transpose() const;

friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix);

private:
std::size_t rows_ = 0;
std::size_t cols_;
std::vector<T> data_;

void check_index(std::size_t i, std::size_t j) const;
void check_dimensions(const Matrix<T> &other, const std::string &operation) const;

};


template<typename T> 
[[nodiscard]] Matrix<T> operator*(const T& scalar, const Matrix<T>& matrix);
}
