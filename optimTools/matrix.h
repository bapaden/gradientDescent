#ifndef MATRIX_H
#define MATRIX_H

#include <cstdio>
#include <vector>
#include <cmath>
#include <cassert>

class matrix
{

//Private members of linAlg
typedef std::vector<double> vec;
std::vector<vec> mat;
  
public:
  
  //Public member variables of linAlg
  int numCols;
  int numRows;

   
  
  //constructor/destructor
  matrix(int nRow, int nCol);
  ~matrix();
  
  //some utility functions
  double index(int rowIndex, int colIndex);
  void assign(int rowIndex, int colIndex, double value);
  void disp(void);
  void size(int& rowSize, int& colSize);
  void resize(int& newRowSize, int& newColSize);
  
};


/***** Constructor-Destructor *****/

//Constructor
matrix::matrix(int nRow, int nCol)
{
  //construct object with matrix size
  numRows=nRow;
  numCols=nCol;
  
  //resize the mat member to nRow and nCol
  mat.resize(nRow);//set the number of rows

  std::vector<double> genericCol;//put a generic column into each row to get size right
  genericCol.resize(nCol);
  
  for(int i=0;i<nRow;i++)
  {
   mat.at(i)=genericCol;
  };
  printf("Creating linAlg object...\n");
};

//Destructor
matrix::~matrix(void)
{
  printf("\nDeleting linAlg object...");
};


/***** matrix member functions *****/

//Get entry at index
double matrix::index(int rowIndex, int colIndex)
{
  //Pointer to indexed row
  std::vector<double>* rowPointer;
  rowPointer=&mat.at(rowIndex);
  //Pick out the column entry of that row
  double entry = rowPointer->at(colIndex);
};

//Assign entry of mat
void matrix::assign(int rowIndex, int colIndex, double value)
{
  //Pointer to indexed row
  std::vector<double>* rowPointer;
  rowPointer=&mat.at(rowIndex);
  //Pick out the column entry of that row
  rowPointer->at(colIndex)=value;
};

//Put the size into arguments
void matrix::size(int& rowSize, int& colSize)
{
  rowSize = numRows;
  colSize = numCols;
};

//Print the matrix to the terminal
void matrix::disp(void)
{
  printf("\n\n");
  for(int i=0;i<numRows;i++)
  {
    vec row=mat.at(i);
    for(int j=0;j<numCols;j++)
    {
      printf("%4.2f ",row.at(j));
    };
    printf("\n");
  };
  printf("\n");
};

//Change the size of matrix
void matrix::resize(int& newRowSize, int& newColSize)
{
   //construct object with matrix size
  numRows=newRowSize;
  numCols=newColSize;
  
  //resize to the new row dimensions
  mat.resize(newRowSize);//set the number of rows
  //resize to new column dimension
  std::vector<double> genericCol(newColSize);//put a generic column into each row to get size right
  
  for(int i=0;i<newRowSize;i++)
  {
   mat.at(i)=genericCol;
  };
}

/*****  Matrix functions not part of class matrix *****/

//Transpose
matrix transpose(matrix& A)
{
  //get the size of A
  int numRows,numCols;
  A.size(numRows,numCols);
     
  //make a matrix B with the dimensions of transpose(A)
  matrix B(numCols,numRows);
  for(int i=0;i<numRows;i++)
  {
    for(int j=0;j<numCols;j++)
    {
      B.assign(j,i,A.index(i,j));
    };
  };
  return B;
}

//Add A and B
matrix add(matrix& A, matrix& B)
{
  //Get the size of A (and B hopefully) to figure out return size
  int numRows,numCols;
  A.size(numRows,numCols);
  matrix C(numRows,numCols);
  
  //entrywise compute Cij=Aij+Bij
  for(int i=0;i<numRows;i++)
  {
    for(int j=0;j<numCols;j++)
    {
      C.assign(i,j,A.index(i,j)+B.index(i,j));
    };
  };
  
  return C;
}

//Subtract A and B
matrix subtract(matrix& A, matrix& B)
{
  //Get the size of A (and B hopefully) to figure out return size
  int numRows,numCols;
  A.size(numRows,numCols);
  matrix C(numRows,numCols);
  
  //entrywise compute Cij=Aij+Bij
  for(int i=0;i<numRows;i++)
  {
    for(int j=0;j<numCols;j++)
    {
      C.assign(i,j,A.index(i,j)-B.index(i,j));
    };
  };
  
  return C;
}

//Get the ith column of A
matrix column(matrix& A, const int& colIndex)
{
  matrix col(A.numRows,1);
  col.disp();
  
  for(int i=0;i<A.numRows;i++)
  {
    col.assign(i,0,A.index(i,colIndex));
    col.disp();  
  };
  return col;
  
}

//Get the jth row of A
matrix row(matrix& A, const int& rowIndex)
{
  matrix col(1,A.numCols);
  col.disp();
  
  for(int i=0;i<A.numCols;i++)
  {
    col.assign(0,i,A.index(rowIndex,i));
    col.disp();  
  };
  
  return col;
}

//Get the inner product of two matrices as a vector
double frobProd(matrix& A,matrix& B)
{
	//if(A.numCols != B.numCols || A.numRows != B.numRows)
	//{
	//	printf("\nMatrix dimension mismatch in frobProd\n");
	//};
	
	double innerProduct=0;
	for(int i=0;i<A.numRows;i++)
	{
		for(int j=0;j<A.numCols;j++)
		{
			innerProduct=innerProduct+A.index(i,j)*B.index(i,j);
		};
	};
	
	
	return innerProduct;
}

//Multiply A and B

matrix multiply(matrix& A, matrix& B)
{
  //Get the size of A (and B hopefully) to figure out return size
  int aRows,aCols,bRows,bCols;
  
  A.size(aRows,aCols);
  B.size(bRows,bCols);
  
  //Define a matrix which is the the size of the product of A and B
  matrix C(A.numRows,B.numCols);
  
  //entrywise compute Cij=sum_k(Aik+Bkj)
  double entry;
  for(int i=0;i<aRows;i++)
  {
    for(int j=0;j<aCols;j++)
    {
		//sum across colum and row 
		for(int k=0;k<A.numCols;k++)
		{
			entry=entry+A.index(i,k)*B.index(k,j);
		};
      C.assign(i,j,entry);
		entry=0;
    };
  };
  
  return C;
}

/*** Vector Operations ***/

std::vector<double> operator+(const std::vector<double>& x, const std::vector<double>& y)
{
    assert(x.size()==y.size());
    std::vector<double> z(x.size());
    for(int i=0;i<x.size();i++)
    {
        z.at(i)=x.at(i)+y.at(i);
    }
    
    return z;
}

std::vector<double> operator-(const std::vector<double>& x, const std::vector<double>& y)
{
    assert(x.size()==y.size());
    std::vector<double> z(x.size());
    for(int i=0;i<x.size();i++)
    {
        z.at(i)=x.at(i)-y.at(i);
    }
    
    return z;
}

std::vector<double> operator*(const double& c, const std::vector<double>& x)
{
    std::vector<double> z(x.size());
    for(int i=0;i<x.size();i++)
    {
        z.at(i)=c*x.at(i);
    }
    
    return z;
}

void disp(std::vector<double>& x)
{
    printf("vector:\n");
    for(int i=0;i<x.size();i++)
    {
        printf("%f\n",x.at(i));
    }
}

//vector sum
std::vector<double> add(const std::vector<double>& x,const std::vector<double>& y)
{
    std::vector<double> z(x.size());
    if(x.size()!=y.size())
    {
        printf("Adding vectors of mismatched size\n");
        assert(x.size()==y.size());
    }   
    else
    { 
        for(int i=0;i<x.size();i++)
        {
            z.at(i)=x.at(i)+y.at(i);
        }
    }
    return z;
}

//inner product
double dot(const std::vector<double>& x,const std::vector<double>& y)
{
    double z;
    if(x.size()!=y.size())
    {
        printf("Inner product of vectors of mismatched size\n");
        assert(x.size()==y.size());
    }   
    else
    { 
        for(int i=0;i<x.size();i++)
        {
            z += x.at(i)*y.at(i);
        }
    }
    return z;
}

//multiply a vector by a scalar
std::vector<double> scalarMult(const double c,const std::vector<double>& x)
{ 
    std::vector<double> y=x;
    for(int i=0;i<x.size();i++)
    {
        y.at(i)*=c;
    }
    
    return y;
}


/*** Vector-Matrix operations ***/

matrix vec2mat(const std::vector<double> x)
{
    matrix y(x.size(),1);
    for(int i=0;i<x.size();i++)
    {
        y.assign(i,1,x.at(i));
    }
    
    return y;
}

#endif



