//Irad Nuriel, 324220458
#ifndef _MATRIXCONTAINER_H_
#define _MATRIXCONTAINER_H_
#include "Matrix.h"
#include <iostream>
#include <ostream>


//class MatrixContainer decleration:
template<int row,int col,class T=int>
class MatrixContainer {
private:
	/*the container itself, methos used: dynamic array,
	when it full, the size of the container is doubled, 
	and if the number of elements is less from 1/3 of the size of the array, the size of the array will become 2/3 of its current size.*/ 
	Matrix<row, col, T>* container;
	//the current size of the array
	int size;
	//number of elements in the container
	int realSize;
	void init(const MatrixContainer<row, col, T>& other) {
		//Method for initialize the array
		this->realSize = other.realSize;
		this->size = other.size;
		this->container = new Matrix<row,col,T>[this->size];
		for (int i = 0; i < this->realSize; i++) {
			this->container[i] = other.container[i];
		}
	}
	void reInit() {
		Matrix<row, col, T>* newContainer = new Matrix<row, col, T>[this->size];
		for (int i = 0; i < this->realSize; i++) {
			newContainer[i] = this->container[i];
		}
		delete[] this->container;
		this->container = newContainer;
	}
public:
	//default constructor
	MatrixContainer():size(1),realSize(0) {
		container = new Matrix<row, col, T>[1];
	}
	//the big three:
	MatrixContainer(const MatrixContainer<row, col, T>& other) {
		//copy c'tor
		init(other);
	}
	~MatrixContainer() {
		//d'tor
		delete[] this->container;
	}
	const MatrixContainer<row, col, T>& operator=(const Matrix<row, col, T>& other) {
		//assignment operator
		if (this != (&other)) {
			delete[] this->container;
			init(other);
		}
		return *this;
	}
	void addMatrix(const Matrix<row, col, T>& mat) {
		//method for adding matrix to the container
		if ((this->size > (this->realSize+1)) && (this->realSize!=0)) {
			//if this isn't the last place in the array, just add.
			this->container[this->realSize] = mat;
			this->realSize++;
		}
		else {
			//if the container is full, we will double the size of the array
			this->size = this->size * 2;
			this->container[this->realSize] = mat;
			this->realSize++;
			this->reInit();
		}
	}
	void removeLastMatrix() {
		//method for removing the last matrix in the container
		if ((this->size < (3 * this->realSize)) && (this->realSize!=0)) {
			//if the array is more than 1/3 full, we will just regulary removing it by totaly ignore it's existence  
			this->realSize--;
		}
		else if(this->realSize != 0) {
			//if the array is less than 1/3 full, we will decrease the size of the array to 2/3 of its origenal size 
			this->realSize--;
			this->size = this->realSize * 2;
			this->reInit();
		}
	}
	Matrix<row,col,T> addMatricesAtIndexes(int index1, int index2) {
		//method for adding two different matrices in the container
		Matrix<row,col,T> m = this->container[index1] + this->container[index2];
		return m;
	}
	Matrix<row, col, T> mulMatAtIndexByScalar(int index, int scalar) {
		//method for multiply matrix from the container by scalar
		Matrix<row, col, T> m = this->container[index] * scalar;
		return m;
	}
	friend std::ostream& operator<<(std::ostream& out, MatrixContainer<row, col, T> container) {
		//printing operator
		out << "There are " <<container.realSize<< " matrices in the container. The matrices:" << std::endl;
		for (int i = 0; i < container.realSize; i++) {
			out << container.container[i] << std::endl;
		}
		return out;
	}


};



#endif//!_MATRIXCONTAINER_H_
