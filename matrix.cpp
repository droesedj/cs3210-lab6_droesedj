/**
 *	LAB WEEK 2: MATRIX CLASS
 *	CS3210
 *	@author Dennis Droese
 *	@date March 14, 2018
 *  @file matrix.cpp
 */


#include "matrix.h"
#include <string>
#include <cmath>

// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols) 
{  
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	} else {

		the_matrix = new double*[rows];

		for(unsigned int i = 0; i < rows; i++){
			the_matrix[i] = new double[cols];
		}

		clear();
	}
}

// Copy constructor
matrix::matrix(const matrix& from):rows(from.rows),cols(from.cols)
{
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	} else {

		the_matrix = new double*[rows];

		for(unsigned int i = 0; i < rows; i++){
			the_matrix[i] = new double[cols];
		}

		clear();
	}

	// Copy all of the data of the old matrix to the new one.
	for(unsigned int x = 0; x < rows; x++){
		for(unsigned int y = 0; y < cols; y++){
			the_matrix[x][y] = from.the_matrix[x][y];
		}
	}
}

// Destructor
matrix::~matrix()
{
	//Make sure there is actually something to delete...
	if(the_matrix != nullptr){
		for(unsigned int i = 0; i < rows; i++){
			delete[] the_matrix[i];
		}

		delete[] the_matrix;
	}
}

// Assignment operator
matrix& matrix::operator=(const matrix& rhs)
{

	// Delete the existing matrix since it's getting reassigned.
	if(the_matrix != nullptr){
		for(unsigned int i = 0; i < rows; i++){
			delete the_matrix[i];
		}

		delete the_matrix;
	}

	the_matrix = new double*[rows];

	for(unsigned int i = 0; i < rows; i++){
		the_matrix[i] = new double[cols];
	}

	clear();

	rows = rhs.rows;
	cols = rhs.cols;

	// Copy all of the data of the old matrix to the new one.
	for(unsigned int x = 0; x < rows; x++){
		for(unsigned int y = 0; y < cols; y++){
			the_matrix[x][y] = rhs.the_matrix[x][y];
		}
	}

	return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{
	// use p-constructor
	return matrix(size,size);
}


// Binary operations
matrix matrix::operator+(const matrix& rhs) const
{
	if(rhs.rows != rows || rhs.cols != cols){
		throw matrixException("Attempted to add two matrices with different sizes!");
	}

	matrix retVal(rhs);

	for(unsigned int x = 0; x < rows; x++){
		for(unsigned int y = 0; y < cols; y++){
			retVal[x][y] = retVal[x][y] + the_matrix[x][y];
		}
	}

	return retVal;
}


matrix matrix::operator*(const matrix& rhs) const
{
	if(cols != rhs.rows){
		throw matrixException("Attempted to multiply incompatible matrices.");
	}

	matrix retVal(rows,rhs.cols);

	for(unsigned int i = 0; i < rows; i++){
		for(unsigned int j = 0; j < rhs.cols; j++){
			int sum = 0;
			for(unsigned int k = 0; k < cols; k++){
				sum = sum + (the_matrix[i][k] * rhs[k][j]);
			}
			retVal[i][j] = sum;
		}
	}

	return retVal;
}

matrix matrix::operator*(const double scale) const
{
	matrix retVal(*this);

	// Multiply every entry in the matrix by the scale.
	for(unsigned int x = 0; x < rows; x++){
		for(unsigned int y = 0; y < cols; y++){
			retVal[x][y] = the_matrix[x][y] * scale;
		}
	}

	return retVal;
}


// Unary operations
matrix matrix::operator~() const
{
	matrix retVal(cols, rows);

	// Swap the axis of the matrix.
	for(unsigned int x = 0; x < cols; x++){
		for(unsigned int y = 0; y < rows; y++){
			retVal[x][y] = the_matrix[y][x];
		}
	}

	return retVal;
}
	

void matrix::clear()
{
	// make sure there are valid doubles to clear.
	if(rows == 0 || cols == 0 || the_matrix == nullptr){
		return;
	}

	double* ptr;

	for(unsigned int x = 0; x < rows; x++){
		ptr = the_matrix[x];
		for(unsigned int y = 0; y < cols; y++){
			ptr[y] = 0.0;
		}
	}

	return;
}

double* matrix::operator[](unsigned int row)
{


	for(unsigned int x = 0; x < row; x++){
		if(the_matrix[x] == nullptr) {
			throw matrixException("Specified index out of range.");
		}
	}

	return the_matrix[row];
}

double* matrix::operator[](unsigned int row) const
{
	for(unsigned int x = 0; x < row; x++){
		if(the_matrix[x] == nullptr) {
			throw matrixException("Specified index out of range.");
		}
	}

	return the_matrix[row];
}


std::ostream& matrix::out(std::ostream& os) const
{
	if(the_matrix == nullptr || rows == 0 || cols == 0){
		os << "Empty or invalid matrix.\n";
	} else {
	os << '[';

	for(unsigned int x = 0; x < rows; x++){
		os << "[\t";
		for(unsigned int y = 0; y < cols; y++){
			os << (double)(the_matrix[x][y]) << '\t';
		}
		os << ']';

		if(x < rows - 1){
			os << '\n';
		}
	}

	os << "]\n";
	}
	return os;	
}



// Global insertion and operator
std::ostream& operator<<(std::ostream& os, const matrix& rhs)
{
	return rhs.out(os);
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix& rhs)
{
	matrix retval(rhs);
	retval = retval * scale;
	return retval;
}


