#ifndef _MATRIXCONTAINER_H_
#define _MATRIXCONTAINER_H_
#include "Matrix.h"
#include <iostream>
#include <ostream>


//class MatrixContainer decleration:
template<int row,int col,class T=int>
class MatrixContainer {
private:
	Matrix<row, col, T>* lst;
	int size;
	int realSize;
	void init(const MatrixContainer<row, col, T>& other) {
		this->realSize = other.realSize;
		this->size = other.size;
		this->lst = new Matrix<row,col,T>[this->size];
		for (int i = 0; i < this->realSize; i++) {
			this->lst[i] = other.lst[i];
		}
	}
public:
	MatrixContainer():size(1),realSize(0) {
		lst = new Matrix<row, col, T>[1];
	}
	MatrixContainer(const MatrixContainer<row, col, T>& other) {
		init(other);
	}
	~MatrixContainer() {
		delete[] this->lst;
	}
	const MatrixContainer<row, col, T>& operator=(const Matrix<row, col, T>& other) {
		if (this != (&other)) {
			delete[] this->lst;
			init(other);
		}
		return *this;
	}
	void addMatrix(const Matrix<row, col, T>& mat) {
		if ((this->size > (this->realSize+1)) && (this->realSize!=0)) {
			this->lst[this->realSize] = mat;
			this->realSize++;
		}
		else {
			this->size = this->size * 2;
			Matrix<row, col, T>* newLst = new Matrix<row, col, T>[this->size];
			for (int i = 0; i < this->realSize; i++) {
				newLst[i] = this->lst[i];
			}
			newLst[this->realSize] = mat;
			this->realSize++;
			delete[] this->lst;
			this->lst = newLst;
		}
	}
	void removeLastMatrix() {
		if ((this->size < (3 * this->realSize)) && (this->realSize!=0)) {
			this->realSize--;
		}
		else if(this->realSize != 0) {
			this->realSize--;
			this->size = this->realSize * 2;
			Matrix<row, col, T>* newLst = new Matrix<row, col, T>[this->size];
			for (int i = 0; i < this->realSize; i++) {
				newLst[i] = this->lst[i];
			}
			delete[] this->lst;
			this->lst = newLst;
		}
	}
	Matrix<row,col,T> addMatricesAtIndexes(int index1, int index2) {
		Matrix<row,col,T> m = this->lst[index1] + this->lst[index2];
		return m;
	}
	Matrix<row, col, T> mulMatAtIndexByScalar(int index, int scalar) {
		Matrix<row, col, T> m = this->lst[index] * scalar;
		return m;
	}
	friend std::ostream& operator<<(std::ostream& out, MatrixContainer<row, col, T> container) {
		out << "There are " <<container.realSize<< " matrices in the container. The matrices:" << std::endl;
		for (int i = 0; i < container.realSize; i++) {
			out << container.lst[i] << std::endl;
		}
		return out;
	}


};



#endif//!_MATRIXCONTAINER_H_
