// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Please do not redistribute without asking permission.

#ifndef TINYMATH_HPP
#define TINYMATH_HPP

#include <cmath>
#include <algorithm>

/**
 * @file TinyMath.hpp
 * @brief Header for Vector2D structure
 */

// Forward references of each of the structs
struct Vector3D;
struct Matrix3D;

// Vector3D performs vector operations with 3-dimensions
// The purpose of this class is primarily for 3D graphics
// applications.
struct Vector3D{
    // Note: x,y,z are a convention
    // x,y,z could be position, but also any 3-component value.
    float x,y,z;

    // Default constructor
    // 'why default?' https://stackoverflow.com/questions/20828907/the-new-keyword-default-in-c11
    Vector3D() = default;

    // The "Real" constructor we want to use.
    // This initializes the values x,y,z
    Vector3D(float a, float b, float c){
      // TODO:
      this->x = a;
      this->y = b;
      this->z = c;
    }

    // Index operator, allowing us to access the individual
    // x,y,z components of our vector.
    float& operator[](int i){
        // TODO: Discuss with your partner why this works.
        //       There is no code to change here. 
      return ((&x)[i]);
    }

    // Index operator, allowing us to access the individual
    // x,y,z components of our vector.
    const float& operator[](int i) const{
        // TODO: Discuss with your partner why this works.
        //       There is no code to change here.
        return ((&x)[i]);
    }

    // Multiplication Operator
    // Multiply vector by a uniform-scalar.
    Vector3D& operator *=(float s){
        // TODO:
        //transform(this.begin(), this.end(), *s);
        this->x *= s;
        this->y *= s;
        this->z *= s;
        return (*this);
    }

    // Division Operator
    Vector3D& operator /=(float s){
        // TODO:
        this->x /= s;
        this->y /= s;
        this->z /= s;
        return (*this);
    }

    // Addition operator
    Vector3D& operator +=(const Vector3D& v){
      this->x += v.x;
      this->y += v.y;
      this->z += v.z;

      return (*this);
    }

    // Subtraction operator
    Vector3D& operator -=(const Vector3D& v){
      this->x -= v.x;
      this->y -= v.y;
      this->z -= v.z;

      return (*this);
    }

    

};


// Compute the dot product of a Vector3D
inline float Dot(const Vector3D& a, const Vector3D& b){
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

// Multiplication of a vector by a scalar values
inline Vector3D operator *(const Vector3D& v, float s){
  // TODO:
  Vector3D vec;
  vec.x = v.x * s;
  vec.y = v.y * s;
  vec.z = v.z * s;

  
  return vec;
}

// Division of a vector by a scalar value.
inline Vector3D operator /(const Vector3D& v, float s){
  // TODO:
  Vector3D vec;

  vec.x = v.x / s;
  vec.y = v.y / s;
  vec.z = v.z / s;

  return vec;
}

// Negation of a vector
// Use Case: Sometimes it is handy to apply a force in an opposite direction
inline Vector3D operator -(const Vector3D& v){
  // TODO:
  Vector3D vec;
  vec.x = v.x * -1;
  vec.y = v.y * -1;
  vec.z = v.z * -1;

  return vec;
}

// Return the magnitude of a vector
inline float Magnitude(const Vector3D& v){
  // TODO:
  return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

// Add two vectors together
inline Vector3D operator +(const Vector3D& a, const Vector3D& b){
  // TODO:
  Vector3D vec;
  vec.x = a.x + b.x;
  vec.y = a.y + b.y;
  vec.z = a.z + b.z;
  return vec;
}

// Subtract two vectors
inline Vector3D operator -(const Vector3D& a, const Vector3D& b){
  // TODO:
  Vector3D vec;
  vec.x = a.x - b.x;
  vec.y = a.y - b.y;
  vec.z = a.z - b.z;
  return vec;
}

// Vector Projection
inline Vector3D Project(const Vector3D& a, const Vector3D& b){
  // TODO:
  float s = Dot(a, b)/ (pow(Magnitude(b), 2));
  Vector3D res = b * s;
  return res;
}

// Vector Projection only scalar - Ishani Kapoor extension
inline float ProjectScalar(const Vector3D& a, const Vector3D& b){
  // TODO:
  float s = Dot(a, b)/ (pow(Magnitude(b), 2));
  return s;
}

// Set a vectors magnitude to 1
// Note: This is NOT generating a normal vector
inline Vector3D Normalize(const Vector3D& v){
  // TODO:
  Vector3D vec;
  vec.x = v.x / Magnitude(v);
  vec.y = v.y / Magnitude(v);
  vec.z = v.z / Magnitude(v);

  return vec;
}

// a x b (read: 'a crossed b')
// Produces a new vector perpendicular to a and b.
// (So long as a and b are not parallel which returns zero vector)
inline Vector3D CrossProduct(const Vector3D& a, const Vector3D& b){
  // TODO:
  // Reference
  // https://www.tutorialspoint.com/cplusplus-program-to-compute-cross-product-of-two-vectors
  
  Vector3D vec;
  vec.x = a.y * b.z - a.z * b.y;
  vec.y = -(a.x * b.z - a.z * b.x);
  vec.z = a.x * b.y - a.y * b.x;
  return vec;
}


struct Vector2D{
  float x,y;

  Vector2D() = default;

  Vector2D(float a, float b) {
    this->x = a;
    this->y = b;
  }

  float& operator[](int i){
    // TODO: Discuss with your partner why this works.
    //       There is no code to change here. 
    return ((&x)[i]);
  }
      // Index operator, allowing us to access the individual
    // x,y,z components of our vector.
  const float& operator[](int i) const{
    // TODO: Discuss with your partner why this works.
    //       There is no code to change here.
    return ((&x)[i]);
  }

  // Multiplication Operator
    // Multiply vector by a uniform-scalar.
  Vector2D& operator *=(float s){
    // TODO:
    //transform(this.begin(), this.end(), *s);
    this->x *= s;
    this->y *= s;
    return (*this);
  }

    // Division Operator
  Vector2D& operator /=(float s){
    // TODO:
    this->x /= s;
    this->y /= s;
    return (*this);
  }

    // Addition operator
  Vector2D& operator +=(const Vector2D& v){
    this->x += v.x;
    this->y += v.y;
    return (*this);
  }

    // Subtraction operator
  Vector2D& operator -=(const Vector2D& v){
    this->x -= v.x;
    this->y -= v.y;
    return (*this);
  }
};


// Compute the dot product of a Vector2D
inline float Dot(const Vector2D& a, const Vector2D& b){
  return (a.x * b.x) + (a.y * b.y);
}

// Multiplication of a vector by a scalar values
inline Vector2D operator *(const Vector2D& v, float s){
  // TODO:
  Vector2D vec;
  vec.x = v.x * s;
  vec.y = v.y * s;

  
  return vec;
}

// Division of a vector by a scalar value.
inline Vector2D operator /(const Vector2D& v, float s){
  // TODO:
  Vector2D vec;

  vec.x = v.x / s;
  vec.y = v.y / s;

  return vec;
}

// Negation of a vector
// Use Case: Sometimes it is handy to apply a force in an opposite direction
inline Vector2D operator -(const Vector2D& v){
  // TODO:
  Vector2D vec;
  vec.x = v.x * -1;
  vec.y = v.y * -1;
  return vec;
}

// Return the magnitude of a vector
inline float Magnitude(const Vector2D& v){
  // TODO:
  return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

// Add two vectors together
inline Vector2D operator +(const Vector2D& a, const Vector2D& b){
  // TODO:
  Vector2D vec;
  vec.x = a.x + b.x;
  vec.y = a.y + b.y;
  return vec;
}

// Subtract two vectors
inline Vector2D operator -(const Vector2D& a, const Vector2D& b){
  // TODO:
  Vector2D vec;
  vec.x = a.x - b.x;
  vec.y = a.y - b.y;
  return vec;
}

// Vector Projection
inline Vector2D Project(const Vector2D& a, const Vector2D& b){
  float s = Dot(a, b) / (pow(Magnitude(b), 2));
  Vector2D res = b * s;
  return res;
}

// Vector Projection only scalar - Ishani Kapoor extension
inline float ProjectScalar(const Vector2D& a, const Vector2D& b){
  // TODO:
  float s = Dot(a, b) / (pow(Magnitude(b), 2));
  return s;
}

// Set a vectors magnitude to 1
// Note: This is NOT generating a normal vector
inline Vector2D Normalize(const Vector2D& v){
  // TODO:
  Vector2D vec;
  vec.x = v.x / Magnitude(v);
  vec.y = v.y / Magnitude(v);

  return vec;
}


/*
// Matrix 3D represents 3x3 matrices in Math
struct Matrix3D{
private:
    float n[3][3];  // Store each value of the matrix

public:
    Matrix3D() = default;

    // TODO: Row or column major order you decide!
    // Matrix constructor with 9 scalar values.
    Matrix3D( float n00, float n01, float n02,
              float n10, float n11, float n12,
              float n20, float n21, float n22){

        n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
        n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
        n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
    }

    // Matrix constructor from three vectors.
    Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c){
      n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
      n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
      n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
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
Matrix3D operator *(const Matrix3D& A, const Matrix3D& B){
  // TODO:
  Matrix3D mat3D;
  mat3D[0][0] = (A[0][0] * B[0][0]) + A[0][1] * B[1][0] + A[0][2] * B[2][0];
  mat3D[0][1] = (A[0][0] * B[0][1]) + A[0][1] * B[1][1] + A[0][2] * B[2][1];
  mat3D[0][2] = (A[0][0] * B[0][2]) + A[0][1] * B[1][2] + A[0][2] * B[2][2];
  mat3D[1][0] = (A[1][0] * B[0][0]) + A[1][1] * B[1][0] + A[1][2] * B[2][0];
  mat3D[1][1] = (A[1][0] * B[0][1]) + A[1][1] * B[1][1] + A[1][2] * B[2][1];
  mat3D[1][2] = (A[1][0] * B[0][2]) + A[1][1] * B[1][2] + A[1][2] * B[2][2];
  mat3D[2][0] = (A[2][0] * B[0][0]) + A[2][1] * B[1][0] + A[2][2] * B[2][0];
  mat3D[2][1] = (A[2][0] * B[0][1]) + A[2][1] * B[1][1] + A[2][2] * B[2][1];
  mat3D[2][2] = (A[2][0] * B[0][2]) + A[2][1] * B[1][2] + A[2][2] * B[2][2];

  return mat3D;
}

//Matrix Addition - Ishani Kapoor extension
Matrix3D operator +(const Matrix3D& A, const Matrix3D& B) {
  Matrix3D mat3D;
  mat3D[0][0] = (A[0][0] + B[0][0]);
  mat3D[0][1] = (A[0][1] + B[0][1]);
  mat3D[0][2] = (A[0][2] + B[0][2]);
  mat3D[1][0] = (A[1][0] + B[1][0]);
  mat3D[1][1] = (A[1][1] + B[1][1]);
  mat3D[1][2] = (A[1][2] + B[1][2]);
  mat3D[2][0] = (A[2][0] + B[2][0]);
  mat3D[2][1] = (A[2][1] + B[2][1]);
  mat3D[2][2] = (A[2][2] + B[2][2]);
  return mat3D;
}

//Matrix Subtraction - Ishani Kapoor extension
Matrix3D operator -(const Matrix3D& A, const Matrix3D& B) {
  Matrix3D mat3D;
  mat3D[0][0] = (A[0][0] - B[0][0]);
  mat3D[0][1] = (A[0][1] - B[0][1]);
  mat3D[0][2] = (A[0][2] - B[0][2]);
  mat3D[1][0] = (A[1][0] - B[1][0]);
  mat3D[1][1] = (A[1][1] - B[1][1]);
  mat3D[1][2] = (A[1][2] - B[1][2]);
  mat3D[2][0] = (A[2][0] - B[2][0]);
  mat3D[2][1] = (A[2][1] - B[2][1]);
  mat3D[2][2] = (A[2][2] - B[2][2]);
  return mat3D;
}

// Matrix multiply by a vector

Vector3D operator *(const Matrix3D& M, const Vector3D& v){
  // TODO:
  Vector3D vec;
  vec.x = M[0][0] * v.x + M[0][1] * v.y + M[0][2] * v.z;
  vec.y = M[1][0] * v.x + M[1][1] * v.y + M[1][2] * v.z;
  vec.z = M[2][0] * v.x + M[2][1] * v.y + M[2][2] * v.z;
  return vec;
}
*/


#endif
