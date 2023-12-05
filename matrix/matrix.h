#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <iostream>

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

template <class U, size_t A, size_t B>
class Matrix {
 public:
  U arr[A][B];

  size_t RowsNumber() const;
  size_t ColumnsNumber() const;

  U& operator()(size_t, size_t);
  const U& operator()(size_t, size_t) const;

  U& At(size_t, size_t);
  const U& At(size_t, size_t) const;

  Matrix<U, A, B>& operator+=(Matrix<U, A, B>);
  Matrix<U, A, B>& operator-=(Matrix<U, A, B>);
  Matrix<U, A, B>& operator*=(Matrix<U, B, B>);
  Matrix<U, A, B>& operator*=(double);
  Matrix<U, A, B>& operator/=(double);
};

template <class U, size_t A, size_t B>
size_t Matrix<U, A, B>::RowsNumber() const {
  return A;
}

template <class U, size_t A, size_t B>
size_t Matrix<U, A, B>::ColumnsNumber() const {
  return B;
}

template <class U, size_t A, size_t B>
U& Matrix<U, A, B>::operator()(size_t i, size_t j) {
  return arr[i][j];
}

template <class U, size_t A, size_t B>
const U& Matrix<U, A, B>::operator()(size_t i, size_t j) const {
  return arr[i][j];
}

template <class U, size_t A, size_t B>
U& Matrix<U, A, B>::At(size_t i, size_t j) {
  if (i < A && j < B) {
    return arr[i][j];
  }
  throw MatrixOutOfRange();
}

template <class U, size_t A, size_t B>
const U& Matrix<U, A, B>::At(size_t i, size_t j) const {
  if (i < A && j < B) {
    return arr[i][j];
  }
  throw MatrixOutOfRange();
}

template <class U, size_t A, size_t B>
Matrix<U, B, A> GetTransposed(Matrix<U, A, B> mat) {
  Matrix<U, B, A> transposed;
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      transposed(j, i) = mat(i, j);
    }
  }
  return transposed;
}

template <class U, size_t A, size_t B>
Matrix<U, A, B> operator+(Matrix<U, A, B> mat1, Matrix<U, A, B> mat2) {
  Matrix<U, A, B> new_mat;
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      new_mat(i, j) = mat1(i, j) + mat2(i, j);
    }
  }
  return new_mat;
}

template <class U, size_t A, size_t B>
Matrix<U, A, B> operator-(Matrix<U, A, B> mat1, Matrix<U, A, B> mat2) {
  Matrix<U, A, B> new_mat;
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      new_mat(i, j) = mat1(i, j) - mat2(i, j);
    }
  }
  return new_mat;
}

template <class U, size_t A, size_t B, size_t C>
Matrix<U, A, B> operator*(Matrix<U, A, C> mat1, Matrix<U, C, B> mat2) {
  Matrix<U, A, B> new_mat;
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      new_mat(i, j) = 0;
    }
  }
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      for (size_t k = 0; k < C; ++k) {
        new_mat(i, j) += mat1(i, k) * mat2(k, j);
      }
    }
  }
  return new_mat;
}

template <class U, size_t A, size_t B>
Matrix<U, A, B>& Matrix<U, A, B>::operator+=(Matrix<U, A, B> mat) {
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      arr[i][j] += mat(i, j);
    }
  }
  return *this;
}

template <class U, size_t A, size_t B>
Matrix<U, A, B>& Matrix<U, A, B>::operator-=(Matrix<U, A, B> mat) {
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      arr[i][j] -= mat(i, j);
    }
  }
  return *this;
}

template <class U, size_t A, size_t B>
Matrix<U, A, B>& Matrix<U, A, B>::operator*=(Matrix<U, B, B> mat) {
  Matrix<U, A, B> new_mat;
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      new_mat(i, j) = 0;
    }
  }
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      for (size_t k = 0; k < B; ++k) {
        new_mat(i, j) += arr[i][k] * mat(k, j);
      }
    }
  }
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      arr[i][j] = new_mat(i, j);
    }
  }
  return *this;
}

template <class U, size_t A, size_t B>
Matrix<U, A, B>& Matrix<U, A, B>::operator*=(double num) {
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      arr[i][j] *= num;
    }
  }
  return *this;
}

template <class U, size_t A, size_t B>
Matrix<U, A, B>& Matrix<U, A, B>::operator/=(double num) {
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      arr[i][j] /= num;
    }
  }
  return *this;
}

template <class U, size_t A, size_t B>
Matrix<U, A, B> operator*(double num, Matrix<U, A, B> mat) {
  Matrix<U, A, B> new_mat = mat;
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      new_mat(i, j) *= num;
    }
  }
  return new_mat;
}

template <class U, size_t A, size_t B>
Matrix<U, A, B> operator*(Matrix<U, A, B> mat, double num) {
  Matrix<U, A, B> new_mat;
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      new_mat(i, j) = mat(i, j);
    }
  }
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      new_mat(i, j) *= num;
    }
  }
  return new_mat;
}

template <class U, size_t A, size_t B>
Matrix<U, A, B> operator/(Matrix<U, A, B> mat, double num) {
  Matrix<U, A, B> new_mat = mat;
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      new_mat(i, j) /= num;
    }
  }
  return new_mat;
}

template <class U, size_t A, size_t B>
bool operator==(Matrix<U, A, B> mat1, Matrix<U, A, B> mat2) {
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      if (mat1(i, j) != mat2(i, j)) {
        return false;
      }
    }
  }
  return true;
}

template <class U, size_t A, size_t B>
bool operator!=(Matrix<U, A, B> mat1, Matrix<U, A, B> mat2) {
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      if (mat1(i, j) != mat2(i, j)) {
        return true;
      }
    }
  }
  return false;
}

template <class U, size_t A, size_t B>
std::istream& operator>>(std::istream& io, Matrix<U, A, B>& mat) {
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B; ++j) {
      io >> mat.arr[i][j];
    }
  }
  return io;
}

template <class U, size_t A, size_t B>
std::ostream& operator<<(std::ostream& os, const Matrix<U, A, B>& mat) {
  for (size_t i = 0; i < A; ++i) {
    for (size_t j = 0; j < B - 1; ++j) {
      os << mat(i, j) << ' ';
    }
    os << mat(i, B - 1) << '\n';
  }
  return os;
}
#endif
