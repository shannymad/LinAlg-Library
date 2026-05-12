#include "include/linalg/matrix.hpp"
#include "include/linalg/algorithms.hpp"
#include <iostream>
#include <cmath>
#include <cassert>
#include <limits>



template <typename T>
bool approximately_equal(const linalg::Matrix<T>& first, const linalg::Matrix<T>& second, T eps = T{1e-6}) {
if (first.rows() != second.rows() || first.cols() != second.cols()) {
    return false;
}
for (std::size_t i = 0; i < first.rows(); ++i) {
    for (std::size_t j = 0; j < first.cols(); ++j) {
        if (std::abs(first.at(i, j) - second.at(i, j)) > eps) {
            return false;
        }
    }
    return true;
}

}


int main() {
    using namespace linalg;
    int tests_passed = 0;
    int tests_total = 0;

    std::cout << "Starting LinAlg++ Tests...\n\n";

    tests_total++;
    try {
        Matrix<double> m(2, 2, 5.0);
        assert(m.rows() == 2);
        assert(m.cols() == 2);
        assert(m.at(0, 0) == 5.0);
        assert(m.at(1, 1) == 5.0);
        
        m.set(0, 1, 10.0);
        assert(m.at(0, 1) == 10.0);
        
        std::cout << "[PASS] Test 1: Construction and Access\n";
        tests_passed++;
    } catch (...) {
        std::cout << "[FAIL] Test 1: Construction and Access\n";
    }
-
    tests_total++;
    try {
        Matrix<int> m(2, 2);
        m.at(2, 0);
        std::cout << "[FAIL] Test 2: Exception handling (should have thrown)\n";
    } catch (const IndexOutOfBounds&) {
        std::cout << "[PASS] Test 2: Exception handling (IndexOutOfBounds)\n";
        tests_passed++;
    } catch (...) {
        std::cout << "[FAIL] Test 2: Wrong exception type\n";
    }

    tests_total++;
    try {
        Matrix<double> A(2, 2);
        A.set(0, 0, 1); A.set(0, 1, 2);
        A.set(1, 0, 3); A.set(1, 1, 4);

        Matrix<double> B(2, 2, 1);

        Matrix<double> C = A + B;
        assert(C.at(0, 0) == 2.0); // 1+1
        assert(C.at(1, 1) == 5.0); // 4+1

        Matrix<double> D = A - B;
        assert(D.at(0, 1) == 1.0); // 2-1

        Matrix<double> E = A * 2.0;
        assert(E.at(1, 0) == 6.0); // 3*2

        Matrix<double> F = A * A;
        // A*A = [1*1+2*3, 1*2+2*4] = [7, 10]
        //       [3*1+4*3, 3*2+4*4]   [15, 22]
        assert(F.at(0, 0) == 7.0);
        assert(F.at(1, 1) == 22.0);

        std::cout << "[PASS] Test 3: Arithmetic Operations\n";
        tests_passed++;
    } catch (...) {
        std::cout << "[FAIL] Test 3: Arithmetic Operations\n";
    }

    tests_total++;
    try {
        Matrix<double> M(2, 3);
        M.set(0, 0, 1); M.set(0, 1, 2); M.set(0, 2, 3);
        M.set(1, 0, 4); M.set(1, 1, 5); M.set(1, 2, 6);

        Matrix<double> MT = M.transpose();
        
        assert(MT.rows() == 3);
        assert(MT.cols() == 2);
        assert(MT.at(0, 0) == 1); // [0][0] -> [0][0]
        assert(MT.at(1, 0) == 2); // [0][1] -> [1][0]
        assert(MT.at(2, 1) == 6); // [1][2] -> [2][1]

        assert(MT.transpose() == M);

        std::cout << "[PASS] Test 4: Transpose\n";
        tests_passed++;
    } catch (...) {
        std::cout << "[FAIL] Test 4: Transpose\n";
    }

    tests_total++;
    try {
        Matrix<double> X(2, 2);
        X.set(0, 0, 1.0000001);
        X.set(0, 1, 2.0);
        X.set(1, 0, 3.0);
        X.set(1, 1, 4.0);

        Matrix<double> Y(2, 2);
        Y.set(0, 0, 1.0);
        Y.set(0, 1, 2.0);
        Y.set(1, 0, 3.0);
        Y.set(1, 1, 4.0);

        assert(X == Y); 

        Matrix<double> Z(2, 2, 10.0);
        assert(!(X == Z));

        std::cout << "[PASS] Test 5: Equality Comparison (with epsilon)\n";
        tests_passed++;
    } catch (...) {
        std::cout << "[FAIL] Test 5: Equality Comparison\n";
    }

    tests_total++;
    try {
        // | 1 2 3 |
        // | 0 1 4 |
        // | 5 6 0 |
        Matrix<double> D(3, 3);
        D.set(0, 0, 1); D.set(0, 1, 2); D.set(0, 2, 3);
        D.set(1, 0, 0); D.set(1, 1, 1); D.set(1, 2, 4);
        D.set(2, 0, 5); D.set(2, 1, 6); D.set(2, 2, 0);

        double det = compute_determinant_gauss(D);
        
        if (std::abs(det - 1.0) < 1e-5) {
            std::cout << "[PASS] Test 6: Determinant Calculation (Det = " << det << ")\n";
            tests_passed++;
        } else {
            std::cout << "[FAIL] Test 6: Determinant Calculation (Expected 1.0, Got " << det << ")\n";
        }

        Matrix<double> Singular(2, 2);
        Singular.set(0, 0, 1); Singular.set(0, 1, 2);
        Singular.set(1, 0, 2); Singular.set(1, 1, 4);
        
        double det_sing = compute_determinant_gauss(Singular);
        if (std::abs(det_sing) < 1e-9) {
            std::cout << "[PASS] Test 6b: Singular Matrix Determinant (Det = " << det_sing << ")\n";
            tests_passed++;
            tests_total++;
        } else {
            std::cout << "[FAIL] Test 6b: Singular Matrix Determinant\n";
            tests_total++;
        }

    } catch (const std::exception& e) {
        std::cout << "[FAIL] Test 6: Determinant threw exception: " << e.what() << "\n";
    }

    std::cout << "\n==========================\n";
    std::cout << "Tests passed: " << tests_passed << " / " << tests_total << "\n";
    
    if (tests_passed == tests_total) {
        std::cout << "SUCCESS: All tests passed!\n";
        return 0;
    } else {
        std::cout << "FAILURE: Some tests failed.\n";
        return 1;
    }
}
