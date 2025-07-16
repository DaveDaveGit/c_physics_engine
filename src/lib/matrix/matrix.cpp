#include "matrix.hpp"

const std::out_of_range OOB = std::out_of_range("Row or column index out of bounds.");
const std::invalid_argument SUBMAT_OOB = std::invalid_argument("Submatrix exceeds bounds of original matrix.");
const std::invalid_argument DIM_MISMATCH = std::invalid_argument("Matrix-dimensions don't match.");
const std::invalid_argument INNERDIM_MISMATCH = std::invalid_argument("Inner matrix-dimensions don't align.");

namespace cpp_physics {

Matrix::Matrix(std::size_t rows, std::size_t cols) : rows(rows), cols(cols) { this->data = std::vector<float>(rows * cols, 0.0f); }

Matrix Matrix::Identity(std::size_t size) {
  Matrix result(size, size);
  for (std::size_t i = 0; i < size; i++) result[i, i] = 1;
  return result;
}

std::ostream& operator<<(std::ostream& flux, const Matrix& mat) {
  std::size_t rows = mat.Shape().first;
  std::size_t cols = mat.Shape().second;
  std::vector<std::size_t> maxLength(cols, 0);
  std::stringstream ss;

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      ss << mat.Get(r, c);
      if (maxLength[c] < ss.str().size()) maxLength[c] = ss.str().size();
      ss.str(std::string());
    }
  }
  for (int r = 0; r < rows; r++) {
    if (r != 0) flux << "\n";
    for (int c = 0; c < cols; c++) {
      flux << mat.Get(r, c);
      ss << mat.Get(r, c);
      for (int k = 0; k < maxLength[c] - ss.str().size() + 1; k++) flux << " ";
      ss.str(std::string());
    }
  }
  return flux;
}

std::pair<std::size_t, std::size_t> Matrix::Shape() const { return {this->rows, this->cols}; }

float Matrix::Get(std::size_t row, std::size_t col) const {
  if (row >= rows || col >= cols) throw OOB;
  return data[row * cols + col];
}

void Matrix::applyFunction(std::function<float(float)> func) {
  for (float& f : data) f = func(f);
}

Matrix Matrix::Submatrix(std::size_t num_rows, std::size_t num_cols, std::size_t row_start, std::size_t col_start) const {
  if (row_start + num_rows > rows || col_start + num_cols > cols) throw SUBMAT_OOB;
  Matrix result(num_rows, num_cols);
  for (std::size_t r = 0; r < num_rows; r++) {
    for (std::size_t c = 0; c < num_cols; c++) {
      result[r, c] = Get(row_start + r, col_start + c);
    }
  }
  return result;
}

Matrix Matrix::operator+=(const Matrix& other) {
  if (rows != other.rows || cols != other.cols) throw DIM_MISMATCH;
  for (std::size_t i = 0; i < data.size(); i++) data[i] += other.data[i];
  return *this;
}
Matrix Matrix::operator+(const Matrix& other) const {
  if (rows != other.rows || cols != other.cols) throw DIM_MISMATCH;
  Matrix result(rows, cols);
  for (std::size_t i = 0; i < data.size(); i++) result.data[i] = data[i] + other.data[i];
  return result;
}

Matrix Matrix::operator-=(const Matrix& other) {
  if (rows != other.rows || cols != other.cols) throw DIM_MISMATCH;
  for (std::size_t i = 0; i < data.size(); i++) data[i] -= other.data[i];
  return *this;
}
Matrix Matrix::operator-(const Matrix& other) const {
  if (rows != other.rows || cols != other.cols) throw DIM_MISMATCH;
  Matrix result(rows, cols);
  for (std::size_t i = 0; i < data.size(); i++) result.data[i] = data[i] - other.data[i];
  return result;
}

Matrix Matrix::operator*=(const Matrix& other) {
  if (cols != other.rows) throw INNERDIM_MISMATCH;
  return *this * other;
}

Matrix Matrix::operator*(const Matrix& other) const {
  if (cols != other.rows) throw INNERDIM_MISMATCH;
  Matrix result(rows, other.cols);
  for (std::size_t r = 0; r < rows; r++) {
    for (std::size_t c = 0; c < other.cols; c++) {
      float sum = 0;
      for (std::size_t k = 0; k < cols; k++) {
        sum += Get(r, k) * other.Get(k, c);
      }
      result[r, c] = sum;
    }
  }
  return result;
}

Matrix Matrix::operator*=(float scalar) {
  applyFunction([scalar](float x) { return x * scalar; });
  return *this;
}

Matrix Matrix::operator*(float scalar) const {
  Matrix result(rows, cols);
  for (std::size_t i = 0; i < data.size(); i++) result.data[i] = data[i] * scalar;
  return result;
}

Matrix Matrix::operator/=(float scalar) {
  applyFunction([scalar](float x) { return x / scalar; });
  return *this;
}

Matrix Matrix::operator/(float scalar) const {
  Matrix result(rows, cols);
  for (std::size_t i = 0; i < data.size(); i++) result.data[i] = data[i] / scalar;
  return result;
}

Matrix Matrix::operator=(const Matrix& other) {
  Matrix result(other.rows, other.cols);
  result.data = other.data;
  return result;
}

Matrix Matrix::operator-() const {
  Matrix result(rows, cols);
  for (std::size_t i = 0; i < result.data.size(); i++) result.data[i] = -data[i];
  return result;
}

Matrix Matrix::operator!() const {
  Matrix result(cols, rows);
  for (std::size_t r = 0; r < rows; r++) {
    for (std::size_t c = 0; c < cols; c++) {
      result[c, r] = Get(r, c);
    }
  }
  return result;
}

float& Matrix::operator[](std::size_t row, std::size_t col) {
  if (row >= this->rows || col >= this->cols) throw OOB;
  return this->data[row * this->cols + col];
}

bool Matrix::operator==(const Matrix& other) {
  if (rows != other.rows || cols != other.cols) return false;
  return data == other.data;
}

bool Matrix::operator!=(const Matrix& other) {
  if (rows != other.rows || cols != other.cols) return true;
  return data != other.data;
}

} // namespace cpp_physics
