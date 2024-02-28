// AUTOR: Javier Acosta Portocarrero
// FECHA: 17/02/2024
// EMAIL: alu0101660769@ull.edu.es
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 2
// COMENTARIOS: se indican entre [] las pautas de estilo aplicadas de
//              "C++ Programming Style Guidelines"
//              https://geosoft.no/development/cppstyle.html

#pragma once

#include <iostream>
#include <cassert>

#include "vector_t.hpp"

using namespace std;

template<class T>
class matrix_t
{
public:
  matrix_t(const int = 0, const int = 0);
  ~matrix_t();
  
  void resize(const int, const int);
  
  // getters
  int get_m(void) const;
  int get_n(void) const;
  
  // getters-setters
  T& at(const int, const int);
  T& operator()(const int, const int);
  
  // getters constantes
  const T& at(const int, const int) const;
  const T& operator()(const int, const int) const;
  
  // operaciones y operadores
  void multiply(const matrix_t<T>&, const matrix_t<T>&);

  void write(ostream& = cout) const;
  void read(istream& = cin);

  void DiagonalPrincipal() const;
  void DiagonalSecundaria() const;
  void Escalera() const;
  void EscaleraBaja() const;
  void TriangularInferior() const;
  void TriangularSuperior() const;

private:
  int m_, n_; // m_ filas y n_ columnas
  vector_t<T> v_;
  
  int pos(const int, const int) const;
};



template<class T>
matrix_t<T>::matrix_t(const int m, const int n)
{ 
  m_ = m;
  n_ = n;
  v_.resize(m_ * n_);
}



template<class T>
matrix_t<T>::~matrix_t()
{}



template<class T>
void
matrix_t<T>::resize(const int m, const int n)
{
  assert(m > 0 && n > 0);
  m_ = m;
  n_ = n;
  v_.resize(m_ * n_);
}



template<class T>
inline int
matrix_t<T>::get_m() const
{
  return m_;
}



template<class T>
inline int
matrix_t<T>::get_n() const
{
  return n_;
}



template<class T>
T&
matrix_t<T>::at(const int i, const int j)
{
  assert(i > 0 && i <= get_m());
  assert(j > 0 && j <= get_n());
  return v_[pos(i, j)];
}



template<class T>
T&
matrix_t<T>::operator()(const int i, const int j)
{
  return at(i, j);
}



template<class T>
const T&
matrix_t<T>::at(const int i, const int j) const
{
  assert(i > 0 && i <= get_m());
  assert(j > 0 && j <= get_n());
  return v_[pos(i, j)];
}



template<class T>
const T&
matrix_t<T>::operator()(const int i, const int j) const
{
  return at(i, j);
}



template<class T>
void
matrix_t<T>::write(ostream& os) const
{ 
  os << get_m() << "x" << get_n() << endl;
  for (int i = 1; i <= get_m(); ++i) {
    for (int j = 1; j <= get_n(); ++j)
      os << at(i, j) << "\t";
    os << endl;
  }
  os << endl;
}



template<class T>
void
matrix_t<T>::read(istream& is)
{
  is >> m_ >> n_;
  resize(m_, n_);
  for (int i = 1; i <= get_m(); ++i)
    for (int j = 1; j <= get_n(); ++j)
      is >> at(i, j);
}


template<class T>
inline
int
matrix_t<T>::pos(const int i, const int j) const
{
  assert(i > 0 && i <= get_m());
  assert(j > 0 && j <= get_n());
  return (i - 1) * get_n() + (j - 1);
}



// FASE III: producto matricial
template<class T>
void
matrix_t<T>::multiply(const matrix_t<T>& A, const matrix_t<T>& B)
{
  assert(A.get_n() == B.get_m());
  int m{A.get_m()};
  int p{B.get_n()};
  int n{B.get_m()};
  resize( A.get_m(), B.get_n());
  for (int i{1}; i <= m; i++) {  // En este for se recorren las distintas filas de la matriz izq 
    T temp = 0;
    for (int j = 1; j <= p; j++) {  // En este for se recorren las columnas de la segunda matriz
      temp = 0;
      for (int k = 1; k <= n; k++) {  
      // En este for se recorren las posiciones de las columnas 
      // de la segunda matriz y ademas las posiciones de las filas de la primera, pues estas comparten la misma posicion k.
      
        temp = temp + A.at(i, k) * B.at(k, j);
      }
      at(i, j) = temp;
    }
}
  // rellenar código
}

template<class T>
void matrix_t<T>::Escalera() const {
  int rango{get_m()};
  for (int posicion{1}; posicion <= rango; ++posicion) {
    if (posicion == rango) {
      std::cout << at(posicion, posicion);
      break;
    }
    std::cout << at(posicion, posicion) << " " << at(posicion, posicion + 1) << " ";
  }
}

template<class T>
void matrix_t<T>::EscaleraBaja() const {
  int rango{get_m()};
  std::cout << at(1, 1) << " ";
  for (int posicion{2}; posicion <= rango; ++posicion) {
    std::cout << at(posicion, posicion - 1) << " " << at(posicion, posicion) << " ";
  }
}

template<class T>
void matrix_t<T>::DiagonalSecundaria() const{
  int rango{get_m()};
  for (int posicion{1}; posicion <= rango; ++posicion) {
    std::cout << at(posicion, rango - posicion + 1) << " ";
  }
}

template<class T>
void matrix_t<T>::TriangularInferior() const {
  int rango{get_m()};
  for (int fila{1}; fila <= rango; ++fila) {
    for (int columna{1}; columna <= fila; ++columna) {
      std::cout << at(fila, columna) << " ";
    }
    std::cout << std::endl;
  }
}

template<class T>
void matrix_t<T>::TriangularSuperior() const {
  int rango{get_m()};
  for (int fila{1}; fila <= rango; ++fila) {
    for (int espacios{0}; espacios <= fila -1; ++espacios) {
      std::cout << "  ";
    }
    for (int columna{fila}; columna <= rango; ++columna) {
      std::cout << at(fila, columna) << " ";
    }
    std::cout << std::endl;
  }
}