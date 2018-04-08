#ifndef TINYMATH
#define TINYMATH

#include <cmath>

// Forward references of each of the structs
struct Vector3D;
struct Matrix3D;
class TinyMath;

// Vector3D performs vector operations with 3-dimensions
// The purpose of this class is primarily for 3D graphics
// applications.
struct Vector3D{
    // Note: x,y,z are a convention
    // x,y,z could be position, but also any 3-component value.
    float x,y,z;

    // Default constructor
    Vector3D() = default;

    // The "Real" constructor we want to use.
    // This initializes the values x,y,z
    Vector3D(float a, float b, float c){
      x = a;
	    y = b;
	    z = c;
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

    float getZ() {
      return z;
    }

    // Multiplication Operator
    Vector3D& operator *=(float s){
        x *= s;
		y *= s;
		z *= s;
        return (*this);
    }

    // Division Operator
    Vector3D& operator /=(float s){
        x /= s;
		y /= s;
		z /= s;
        return (*this);
    }

    // Addition operator
    Vector3D& operator +=(const Vector3D& v){
        x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
    }

    // Subtraction operator
    Vector3D& operator -=(const Vector3D& v){
        x -= v.x;
		y -= v.y;
		z -= v.z;
      return (*this);
    }

};

Dot(const Vector3D& a, const Vector3D& b){
  float dotProd = (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
  return dotProd;
}

Vector3D vectorMult(const Vector3D& v, float s){
  Vector3D vec = Vector3D(v[0] * s, v[1] * s, v[2] * s);
  return vec;
}

Vector3D vectorDiv(const Vector3D& v, float s){
  Vector3D vec = Vector3D(v[0] / s, v[1] / s, v[2] / s);
  return vec;
}

Vector3D vectorInverse(const Vector3D& v){
  return vectorMult(v, -1);
}

float Magnitude(const Vector3D& v){
  float squares = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
  float mag = sqrt(squares);
  return mag;
}


Vector3D vectorAdd(const Vector3D& a, const Vector3D& b){
  Vector3D vec = Vector3D(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
  return vec;
}

Vector3D vectorSub(const Vector3D& a, const Vector3D& b){
  Vector3D vec = Vector3D(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
  return vec;
}

// Vector Projection - Projects b onto a
Vector3D Project(const Vector3D& a, const Vector3D& b){
	float magA = Magnitude(a);
  float scalar = Dot(a, b) / (magA * magA);
  Vector3D vec = vectorMult(a, scalar);
  return vec;
}

Vector3D Normalize(const Vector3D& v){
  float magnitude = Magnitude(v);
  Vector3D vec = Vector3D(v.x / magnitude, v.y / magnitude, v.z / magnitude);
  return vec;
}

Vector3D CrossProduct(const Vector3D& a, const Vector3D& b){
  float x = a[1] * b[2] - a[2] * b[1];
  float y = a[2] * b[0] - a[0] * b[2];
  float z = a[0] * b[1] - a[1] * b[0];
  Vector3D vec = Vector3D(x, y, z);
  return vec;
}

// Matrix 3D represents 3x3 matrices in Math
struct Matrix3D{
private:
    float n[3][3];  // Store each value of the matrix

public:
    Matrix3D() = default;

    // Matrix constructor with 9 scalar values.
	// First value in each pair is row number, then column number
    Matrix3D( float n00, float n01, float n02,
              float n10, float n11, float n12,
              float n20, float n21, float n22){

        n[0][0] = n00; n[0][1] = n01; n[0][2] = n02;
        n[1][0] = n10; n[1][1] = n11; n[1][2] = n12;
        n[2][0] = n20; n[2][1] = n21; n[2][2] = n22;
    }

    // Matrix constructor from three vectors.
    Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c){
      n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
      n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
      n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
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
    Vector3D& operator [](int j){
      return (*reinterpret_cast<Vector3D *>(n[j]));
    }

    // Return a row from a matrix as a vector.
    const Vector3D& operator [](int j) const{
      return (*reinterpret_cast<const Vector3D *>(n[j]));
    }

};

// Matrix Multiplication
Matrix3D multMatrixMatrix(const Matrix3D& A, const Matrix3D& B){
  float p00 = Dot(Vector3D(A[0][0], A[0][1], A[0][2]), Vector3D(B[0][0], B[1][0], B[2][0]));
  float p01 = Dot(Vector3D(A[0][0], A[0][1], A[0][2]), Vector3D(B[0][1], B[1][1], B[2][1]));
  float p02 = Dot(Vector3D(A[0][0], A[0][1], A[0][2]), Vector3D(B[0][2], B[1][2], B[2][2]));
  float p10 = Dot(Vector3D(A[1][0], A[1][1], A[1][2]), Vector3D(B[0][0], B[1][0], B[2][0]));
  float p11 = Dot(Vector3D(A[1][0], A[1][1], A[1][2]), Vector3D(B[0][1], B[1][1], B[2][1]));
  float p12 = Dot(Vector3D(A[1][0], A[1][1], A[1][2]), Vector3D(B[0][2], B[1][2], B[2][2]));
  float p20 = Dot(Vector3D(A[2][0], A[2][1], A[2][2]), Vector3D(B[0][0], B[1][0], B[2][0]));
  float p21 = Dot(Vector3D(A[2][0], A[2][1], A[2][2]), Vector3D(B[0][1], B[1][1], B[2][1]));
  float p22 = Dot(Vector3D(A[2][0], A[2][1], A[2][2]), Vector3D(B[0][2], B[1][2], B[2][2]));
  Matrix3D mat3D = Matrix3D(p00, p01, p02,
							p10, p11, p12,
							p20, p21, p22);
  return mat3D;
}

// Matrix multiply by a vector
Vector3D multMatrixVector(const Matrix3D& M, const Vector3D& v){
  float x = Dot(Vector3D(M[0][0], M[0][1], M[0][2]), v);
  float y = Dot(Vector3D(M[1][0], M[1][1], M[1][2]), v);
  float z = Dot(Vector3D(M[2][0], M[2][1], M[2][2]), v);
  Vector3D vec = Vector3D(x, y, z);
  return vec;
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
    m.def("vCrossProduct", &CrossProduct, "Returns the cross product");
    m.def("mMultMM", &multMatrixMatrix, "Returns a Matrix3D that is the result of multiplying the given Matrix3Ds");
    m.def("mMultMV", &multMatrixVector, "Returns a Vector3D that is the result of multiplying the given Matrix3D and Vector3D");

    py::class_<Vector3D>(m, "Vector3D")
      .def(py::init<float,float,float>(), py::arg("x"), py::arg("y"), py::arg("z"))
      .def("x", &Vector3D::getX)
      .def("y", &Vector3D::getY)
      .def("z", &Vector3D::getZ) ;

    py::class_<Matrix3D>(m, "Matrix3D")
      .def(py::init<Vector3D, Vector3D, Vector3D>(), py::arg("a"), py::arg("b"), py::arg("c"))
      .def("get", &Matrix3D::get);
}

#endif
