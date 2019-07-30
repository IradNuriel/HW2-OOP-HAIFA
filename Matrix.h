#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <iostream>
#include <string>
#include <ostream>


//class Matrix


template<int row,int col,class T=int>
class Matrix {
private:
	//data is the actual matrix data
	T** data;
	//init are functions for avoiding code duplications
	void init(T l) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				this->data[i][j] = l;
			}
		}
	}
	void init(const Matrix<row, col, T>& other) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				this->data[i][j] = other.data[i][j];
			}
		}
	}
	void initArray() {
		this->data = new T*[row];
		for (int i = 0; i < row; i++) {
			this->data[i] = new T[col];
		}
	}
	//just min function
	int min(int a, int b) const{
		return (a < b) ? a : b;
	}
public:
	//constructors- default, normal and copy
	Matrix() {
		this->initArray();
		this->init(0);
	}
	Matrix(T l) {
		this->initArray();
		this->init(l);
	}
	Matrix(const Matrix<row,col,T>& other) {
		this->initArray();
		init(other);
	}
	//distructor
	~Matrix() {
		for (int i = 0; i < row; i++) {
			delete[] this->data[i];
		}
		delete[] this->data;
	}
	//assignment operator
	const Matrix<row, col, T>& operator=(const Matrix<row,col,T>& other) {
		if (this != &other) {
			for (int i = 0; i < row; i++) {
				delete[] (this->data[i]);
			}
			delete[] this->data;
			this->initArray();
			init(other);
		}
		return *this;
	}
	//parenthesis operation
	T& operator()(const int& a, const int& b) {
		if (a < row && b < col) {
			return this->data[a][b];
		}
		else {
			std::cout << "illegal values!!" << std::endl;
			return this->data[0][0];
		}
	}
	//printing operation
	friend std::ostream& operator<<(std::ostream& out, const Matrix<row, col, T>& mat){
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				out << mat.data[i][j] << " ";
			}
			out << std::endl;
		}
		return out;
	}
	//plus operation
	friend Matrix<row, col, T> operator+ (const Matrix<row,col,T>& lhs, const Matrix<row, col, T>& rhs){
		Matrix<row, col, T> res;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				res.data[i][j] = lhs.data[i][j] + rhs.data[i][j];
			}
		}
		return res;
	}
	//minus operation
	friend Matrix<row, col, T> operator- (const Matrix<row, col, T>& lhs, const Matrix<row, col, T>& rhs){
		Matrix<row, col, T> res;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				res.data[i][j] = lhs.data[i][j] - rhs.data[i][j];
			}
		}
		return res;
	}
	//multiplication operation
	friend Matrix<row, col, T> operator* (const Matrix<row, col, T>& lhs, const Matrix<row, col, T>& rhs){
		Matrix<row, col, T> res;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				res.data[i][j] = lhs.data[i][j] * rhs.data[i][j];
			}
		}
		return res;
	}
	//unary minus operation
	Matrix<row, col, T>& operator-() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				this->data[i][j] = -this->data[i][j];
			}
		}
		return *this;
	}
	//prefix increment operation
	Matrix<row, col, T>& operator++() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				this->data[i][j]++;
			}
		}
		return *this;
	}
	//prefix decrement operation
	Matrix<row, col, T>& operator--() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				this->data[i][j]--;
			}
		}
		return *this;
	}
	//postfix increment operation
	Matrix<row, col, T> operator++(int) {
		Matrix<row, col, T> other(*this);
		++(*this);
		return other;
	}
	//postfix decrement operation
	Matrix<row, col, T> operator--(int) {
		Matrix<row, col, T> other(*this);
		--(*this);
		return other;
	}
	//function for getting the main diag of the matrix
	T* getDiag(int& number) const{
		number = this->min(row, col);
		T* diag = new T[number];
		for (int i = 0; i < number; i++) {
			diag[i] = this->data[i][i];
		}
		return diag;
	}
	//function for getting the trace of the matrix
	T trace() const{
		int number;
		T trace;
		T* diag = getDiag(number);
		trace = diag[0];
		for (int i = 1; i < number; i++) {
			trace += diag[i];
		}
		delete[] diag;
		return trace;
	}
};
#endif //!_MATRIX_H_
