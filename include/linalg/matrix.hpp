#pragma once
#include "exceptions.hpp"
#include <cstddef>
#include <iostream>
#include <vector>

namespace linalg {
class Matrix : public : Matrix();

explicit Matrix(std::size_t rows, std::size_t cols, double value = 0.0);

Matrix(const Matrix &) = default;
Matrix &operator=(const Matrix &) = default;
Matrix(Matrix &&) noexcept = default;
Matrix &operator=(Matrix &&) noexcept = default;

[[nodiscard]] std::size_t rows() const noexcept { return rows_; }

[[nodiscard]] std::size_t cols() const noexcept { return cols_; }

double at(std::size_t i, std::size_t j) const;
void set(std::size_t i, std::size_t j, double value);

[[nodiscard]] Matrix operator+(const Matrix &other) const;
[[nodiscard]] Matrix operator-(const Matrix &other) const;

[[nodiscard]] Matrix operator*(const Matrix &other) const;

[[nodiscard]] Matrix operator*(double scalar) const;

friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

private:
std::size_t rows_ = 0;
std::size_t cols_;
std::vector<double> data_;

void check_index(std::size_t i, std::size_t j) const;
void check_dimensions(const Matrix &other, const std::string &operation) const;

[[nodiscard]] Matrix operator*(double scalar, const Matrix &matrix);
} 
