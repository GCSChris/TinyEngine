#ifndef TINYMATH
#define TINYMATH

#include <cmath>
#include <vector>
#include <map>

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

    std::pair<float, float> getPair() {
      return std::pair<float, float>(x, y);
    }

};

/** Given two pairs of floats, returns their dot product.*/
float Dot(/** The first pair */std::pair<float, float> aPair, /** The second pair */ std::pair<float, float> bPair){
  Vector2D a = Vector2D(aPair.first, aPair.second);
  Vector2D b = Vector2D(bPair.first, bPair.second);
  float dotProd = (a[0] * b[0]) + (a[1] * b[1]);
  return dotProd;
}

/** Returns a new pair that is the given pair multiplied by a scalar value*/
std::pair<float, float> vectorMult(/** The pair to multiply */ std::pair<float, float> vPair, /** The scalar value */float s){
  Vector2D v = Vector2D(vPair.first, vPair.second);
  Vector2D vec = Vector2D(v[0] * s, v[1] * s);
  return vec.getPair();
}

/** Returns a new pair that is the given pair divided by a scalar value*/
std::pair<float, float> vectorDiv(/** The pair to divide */std::pair<float, float> vPair, /** The scalar value */float s){
  Vector2D v = Vector2D(vPair.first, vPair.second);
  Vector2D vec = Vector2D(v[0] / s, v[1] / s);
  return vec.getPair();
}

/** Returns the inverse pair of the given pair */
std::pair<float, float> vectorInverse(/** The pair to get the inverse of */std::pair<float, float> vPair){
  return vectorMult(vPair, -1);
}

/** Returns the magnitude of the pair */
float Magnitude(/** The pair to get the magnitude */std::pair<float, float> vPair){
  Vector2D v = Vector2D(vPair.first, vPair.second);
  float squares = (v[0] * v[0]) + (v[1] * v[1]);
  float mag = sqrt(squares);
  return mag;
}

/** Returns the addition of the given pairs */
std::pair<float, float> vectorAdd(/** The first pair */std::pair<float, float> aPair, /** The second pair */ std::pair<float, float> bPair){
  Vector2D a = Vector2D(aPair.first, aPair.second);
  Vector2D b = Vector2D(bPair.first, bPair.second);
  Vector2D vec = Vector2D(a[0] + b[0], a[1] + b[1]);
  return vec.getPair();
}

/** Returns the subtraction of the given pairs */
std::pair<float, float> vectorSub(/** The first pair */std::pair<float, float> aPair, /** The second pair */std::pair<float, float> bPair){
  Vector2D a = Vector2D(aPair.first, aPair.second);
  Vector2D b = Vector2D(bPair.first, bPair.second);
  Vector2D vec = Vector2D(a[0] - b[0], a[1] - b[1]);
  return vec.getPair();
}

/** Returns the projection of the first pair onto the second pair */
std::pair<float, float> Project(/** The first pair */std::pair<float, float> aPair, /** The second pair*/std::pair<float, float> bPair){
  float magA = Magnitude(aPair);
  float scalar = Dot(aPair, bPair) / (magA * magA);
  return vectorMult(aPair, scalar);
}

/** Returns the normalized form of the given pair (scaled to magnitude 1)*/
std::pair<float, float> Normalize(/** The pair to normalize */std::pair<float, float> vPair){
  Vector2D v = Vector2D(vPair.first, vPair.second);
  float magnitude = Magnitude(vPair);
  Vector2D vec = Vector2D(v.x / magnitude, v.y / magnitude);
  return vec.getPair();
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

/** Returns the Matrix2D from multiplying the given matrices */
Matrix2D multMatrixMatrix(/** The first matrix */const Matrix2D& A, /** The second matrix */const Matrix2D& B){
  float p00 = Dot(Vector2D(A[0][0], A[0][1]).getPair(), Vector2D(B[0][0], B[1][0]).getPair());
  float p01 = Dot(Vector2D(A[0][0], A[0][1]).getPair(), Vector2D(B[0][1], B[1][1]).getPair());
  float p10 = Dot(Vector2D(A[1][0], A[1][1]).getPair(), Vector2D(B[0][0], B[1][0]).getPair());
  float p11 = Dot(Vector2D(A[1][0], A[1][1]).getPair(), Vector2D(B[0][1], B[1][1]).getPair());
  Matrix2D mat2D = Matrix2D(p00, p01,
							              p10, p11);
  return mat2D;
}

/** Returns the 2D pair from multiplying the given matrix by the given pair */
std::pair<float, float> multMatrixVector(/** The matrix */const Matrix2D& M, /** The vector pair*/std::pair<float, float> vPair){
  float x = Dot(Vector2D(M[0][0], M[0][1]).getPair(), vPair);
  float y = Dot(Vector2D(M[1][0], M[1][1]).getPair(), vPair);
  Vector2D vec = Vector2D(x, y);
  return vec.getPoints();
}

/** Returns the given point rotated counter clockwise around the rotation point by the given angle in degrees*/
std::pair<float, float> rotatePoint(/** The point to rotate */std::pair<float, float> point,
    /** The point of rotation */const std::pair<float, float> rotPoint,
    /** The angle of rotation in degrees */int degRot) {
  std::pair<float, float> shiftedPoint = vectorSub(point, rotPoint);
  float radians = degRot * 3.14159265 / 180;
  Matrix2D matrix = Matrix2D(cos(radians), -sin(radians), sin(radians), cos(radians));
  std::pair<float, float> rotatedPoint = multMatrixVector(matrix, shiftedPoint);
  return vectorAdd(rotatedPoint, rotPoint);
}

/** Returns a list of the given points rotated counter clockwise around the rotation point by the given angle in degrees*/
std::vector<std::pair<float, float>> rotatePointsAround(/** The points to rotate */std::vector<std::pair<float, float>> points,
    /** The point of rotation */const std::pair<float, float> rotPoint,
    /** The angle of rotation in degrees */int degRot) {
  std::vector<std::pair<float, float>> newPoints;
  for (auto it = points.begin(); it < points.end(); it++) {
    newPoints.push_back(rotatePoint(*it, rotPoint, degRot));
  }

  return newPoints;
}

/** Returns a list of the given points rotated counter clockwise around their center point by the given angle in degrees*/
std::vector<std::pair<float, float>> rotatePoints(/** The points to rotate */std::vector<std::pair<float, float>> points,
    /** The angle of rotation in degrees*/int degRot) {
  float avgX = 0;
  float avgY = 0;
  int count = 0;

  for (auto it = points.begin(); it < points.end(); it++) {
    avgX += it->first;
    avgY += it->second;
    count++;
  }

  return rotatePointsAround(points, std::pair<float,float>(avgX / count, avgY / count), degRot);
}

/** Returns the translation of the given point by the given translation */
std::pair<float, float> translatePoint(/** The point to translate */std::pair<float, float> point, /** The transaltion */std::pair<float, float> translation) {
  return vectorAdd(point, translation);
}

/** Returns a list of the the translations of the given points by the given translation */
std::vector<std::pair<float, float>> translatePoints(std::vector<std::pair<float, float>> points, std::pair<float, float> translation) {
  std::vector<std::pair<float, float>> newPoints;
  for (auto it = points.begin(); it < points.end(); it++) {
    newPoints.push_back(translatePoint(*it, translation));
  }

  return newPoints;
}


// Include the pybindings
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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
    m.def("TranslatePoint", &translatePoint);
    m.def("TranslatePoints", &translatePoints);
    m.def("RotatePoint", &rotatePoint);
    m.def("RotatePoints", &rotatePoints);
    m.def("RotatePointsAround", &rotatePointsAround);

    py::class_<Vector2D>(m, "Vector2D")
      .def(py::init<float,float>(), py::arg("x"), py::arg("y"))
      .def("x", &Vector2D::getX)
      .def("y", &Vector2D::getY);

    py::class_<Matrix2D>(m, "Matrix2D")
      .def(py::init<float, float, float, float>(), py::arg("n00"), py::arg("n01"), py::arg("n10"), py::arg("n11"))
      .def("get", &Matrix2D::get);
}

#endif
