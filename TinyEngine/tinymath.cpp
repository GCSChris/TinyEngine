#ifndef TINYMATH
#define TINYMATH

#include <cmath>

// Forward references of each of the structs
struct Vector2D;
struct Matrix2D;
class TinyMath;

// Vector2D performs vector operations with 3-dimensions
// The purpose of this class is primarily for 2D graphics
// applications.
struct Vector2D{
    // Note: x,y,z are a convention
    // x,y,z could be position, but also any 3-component value.
    float x,y;

    // Default constructor
    Vector2D() = default;

    // The "Real" constructor we want to use.
    // This initializes the values x,y
    Vector2D(float a, float b){
      x = a;
	    y = b;
    }

    // Index operator, allowing us to access the individual
    // x,y,z components of our vector.
    float& operator[](int i){
      return ((&x)[i]);
    }

    // Index operator, allowing us to access the individual
    // x,y,z components of our vector.
    const float& operator[](int i) const{
        return ((&x)[i]);
    }

    float getX() {
      return x;
    }

    float getY() {
      return y;
    }

    // Multiplication Operator
    Vector2D& operator *=(float s){
        x *= s;
		    y *= s;
        return (*this);
    }

    // Division Operator
    Vector2D& operator /=(float s){
        x /= s;
		    y /= s;
        return (*this);
    }

    // Addition operator
    Vector2D& operator +=(const Vector2D& v){
        x += v.x;
		    y += v.y;
		    return (*this);
    }

    // Subtraction operator
    Vector2D& operator -=(const Vector2D& v){
        x -= v.x;
		    y -= v.y;
        return (*this);
    }

};

Dot(const Vector2D& a, const Vector2D& b){
  float dotProd = (a[0] * b[0]) + (a[1] * b[1]);
  return dotProd;
}

Vector2D vectorMult(const Vector2D& v, float s){
  Vector2D vec = Vector2D(v[0] * s, v[1] * s);
  return vec;
}

Vector2D vectorDiv(const Vector2D& v, float s){
  Vector2D vec = Vector2D(v[0] / s, v[1] / s);
  return vec;
}

Vector2D vectorInverse(const Vector2D& v){
  return vectorMult(v, -1);
}

float Magnitude(const Vector2D& v){
  float squares = (v[0] * v[0]) + (v[1] * v[1]);
  float mag = sqrt(squares);
  return mag;
}


Vector2D vectorAdd(const Vector2D& a, const Vector2D& b){
  Vector2D vec = Vector2D(a[0] + b[0], a[1] + b[1]);
  return vec;
}

Vector2D vectorSub(const Vector2D& a, const Vector2D& b){
  Vector2D vec = Vector2D(a[0] - b[0], a[1] - b[1]);
  return vec;
}

// Vector Projection - Projects b onto a
Vector2D Project(const Vector2D& a, const Vector2D& b){
	float magA = Magnitude(a);
  float scalar = Dot(a, b) / (magA * magA);
  Vector2D vec = vectorMult(a, scalar);
  return vec;
}

Vector2D Normalize(const Vector2D& v){
  float magnitude = Magnitude(v);
  Vector2D vec = Vector2D(v.x / magnitude, v.y / magnitude);
  return vec;
}

// Matrix 2D represents 2x2 matrices in Math
struct Matrix2D{
private:
    float n[2][2];  // Store each value of the matrix

public:
    // Matrix constructor with 4 scalar values.
	  // First value in each pair is row number, then column number
    Matrix2D( float n00, float n01,
              float n10, float n11){
        n[0][0] = n00; n[0][1] = n01;
        n[1][0] = n10; n[1][1] = n11;
    }

    float get(int i, int j) {
      return n[i][j];
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    float& operator ()(int i, int j){
      return (n[j][i]);
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    const float& operator ()(int i, int j) const{
      return (n[j][i]);
    }

    // Return a row from a matrix as a vector.
    Vector2D& operator [](int j){
      return (*reinterpret_cast<Vector2D *>(n[j]));
    }

    // Return a row from a matrix as a vector.
    const Vector2D& operator [](int j) const{
      return (*reinterpret_cast<const Vector2D *>(n[j]));
    }

};

// Matrix Multiplication
Matrix2D multMatrixMatrix(const Matrix2D& A, const Matrix2D& B){
  float p00 = Dot(Vector2D(A[0][0], A[0][1]), Vector2D(B[0][0], B[1][0]));
  float p01 = Dot(Vector2D(A[0][0], A[0][1]), Vector2D(B[0][1], B[1][1]));
  float p10 = Dot(Vector2D(A[1][0], A[1][1]), Vector2D(B[0][0], B[1][0]));
  float p11 = Dot(Vector2D(A[1][0], A[1][1]), Vector2D(B[0][1], B[1][1]));
  Matrix2D mat2D = Matrix2D(p00, p01,
							              p10, p11);
  return mat2D;
}

// Matrix multiply by a vector
Vector2D multMatrixVector(const Matrix2D& M, const Vector2D& v){
  float x = Dot(Vector2D(M[0][0], M[0][1]), v);
  float y = Dot(Vector2D(M[1][0], M[1][1]), v);
  Vector2D vec = Vector2D(x, y);
  return vec;
}

Vector2D vectorRotation(const Vector2D& vect, const Vector2D point, int deg) {
  // TODO rotate the given vector around the given point by degrees
  return vect;
}


// Include the pybindings
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(tinymath, m){
    m.doc() = "The TinyMath modules gives support for vector and matrix math"; // Optional docstring

    m.def("vAdd", &vectorAdd, "Adds two vectors together, returning the result");
    m.def("vSub", &vectorSub, "Subtracts two vectors, returning the result");
    m.def("vMul", &vectorMult, "Multiplies a vector by a scalar, returning the result");
    m.def("vDiv", &vectorDiv, "Divides a vector by a scalar, returning the result");
    m.def("vInverse", &vectorInverse, "Returns the inverse of a vector");
    m.def("vMag", &Magnitude, "Returns the magnitude of the vector");
    m.def("vNormalize", &Normalize, "Returns a new vector that is the given vector scaled to magnitude 1");
    m.def("vDot", &Dot, "Returns the dot product of the given vectors");
    m.def("vProject", &Project, "Returns the vector projection");
    m.def("mMultMM", &multMatrixMatrix, "Returns a Matrix2D that is the result of multiplying the given Matrix2Ds");
    m.def("mMultMV", &multMatrixVector, "Returns a Vector2D that is the result of multiplying the given Matrix2D and Vector2D");

    py::class_<Vector2D>(m, "Vector2D")
      .def(py::init<float,float>(), py::arg("x"), py::arg("y"))
      .def("x", &Vector2D::getX)
      .def("y", &Vector2D::getY);

    py::class_<Matrix2D>(m, "Matrix2D")
      .def(py::init<float, float, float, float>(), py::arg("n00"), py::arg("n01"), py::arg("n10"), py::arg("n11"))
      .def("get", &Matrix2D::get);
}

#endif
