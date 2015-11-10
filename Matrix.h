#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstring>


template<typename elemType>
void print_vector(const std::vector<elemType>&vct )
{
	for( int i=0; i<vct.size(); i++ )
		std::cout<<std::fixed<<vct[i]<<' ';
	std::cout<<std::endl;
}

double getVectorValue(int, const std::vector<double>&);
double norm(const std::vector<double>&, int p=2);
double norm_signed(const std::vector<double>&, int p=2);
double inner_product
(const std::vector<double>&, const std::vector<double>&);
std::vector<double> operator+
(const std::vector<double>&,const std::vector<double>&);
std::vector<double> operator-
(const std::vector<double>&,const std::vector<double>&);
std::vector<double> operator-(const std::vector<double>&);
std::vector<double> operator*(double,const std::vector<double>&);
std::vector<double> operator*(const std::vector<double>&,double);
std::vector<double> operator/(const std::vector<double>&,const double);
std::vector<double> vector_tail(const std::vector<double>&,const int);
void vector_normalize(std::vector<double>&,int p=0);


////////////////////CLASS MATRIX/////////////////////////////////////////////
class matrix
{
public:
	//Initialize
	matrix(){}
	matrix(unsigned int,unsigned int);
	//Read file
	bool readFile(const char *filename);
	//Get entries
	double& at(int i,int j);
	const double get(int i,int j)const;
	//Get properties
	int n_l()const{return _matrix.size();}
	int n_c()const{return _matrix[0].size();}
	//Print
	int print(std::ostream& os=std::cout,int=10) const;
	//Operator overload
	matrix& operator=(const matrix&);//Assignment
	bool operator==(const matrix&);//Comparation
	bool operator!=(const matrix&);
	matrix operator+(const matrix&);//Plus
	matrix operator-(const matrix&);//Minus
	//Get value from the muliplication of two vectors
	void vector_mult(const std::vector<double>&,const std::vector<double>&);
	//Get row and column
	std::vector<double> get_row(int i) const;
	std::vector<double> get_column(int i) const;
	//Times vector
	//Right Multiply a vector
	std::vector<double> rmult_vector(const std::vector<double>&);
	//Left Multiply a vector
	std::vector<double> lmult_vector(const std::vector<double>&);
	//Elementary row transforms
	void elem_row_trans(int row1, int row2);
	void elem_row_trans(int from, double times, int to=0);
	//Elementary column transforms
	void elem_clm_trans(int clm1, int clm2);
	void elem_clm_trans(int from, double times, int to=0);
	//Norms
	double normF();
	//Submatrix
	matrix submatrix(int left, int top, int width=0, int height=0);
protected:
	std::vector<std::vector<double> > _matrix;
};
/////////////////////////////////////////////////////////////////////////////
/////////////////DERIVED CLASS SQUARE_MATRIX//////////////////////////////////////
class sq_matrix:public matrix
{
public:
	//Initialize
	sq_matrix(){}
	sq_matrix(unsigned int n):matrix(n,n){}
	//Size
	int size() const;
	//Operator overload
    sq_matrix operator+(const sq_matrix&);
    sq_matrix operator-(const sq_matrix&);
    sq_matrix operator-();
	sq_matrix operator*(const sq_matrix&);//Multiply another square matrix
    sq_matrix operator*(double);//Multiply a double
	//Power
	sq_matrix power(int n);
	//Matrix manipulate
	void idlize();//Make itself an identity matrix
	void get_values(const std::vector<double>&);//Get values from a vector
	void tridiagonal(double lower, double mid, double upper, int from=1, int to=0);
	//Tridiagonalize matrix
	//Return a matrix with elements being sqrt of the corresponding
	//elements in A
	sq_matrix sqrt_all();
	//Return a diagonal matrix with elements being sqrt of the corresponding
	//elements in A
	sq_matrix sqrt_diag();
	//Multiply vector
	std::vector<double> rmult_vector_tri(const std::vector<double>&);
	std::vector<double> lmult_vector_tri(const std::vector<double>&);
	//Factoring
	void LU(sq_matrix&,sq_matrix&);
	bool QRTrans(sq_matrix&, std::vector<double>&);
	bool QR(sq_matrix&,sq_matrix&,bool nonsingular=false);
	bool Heisenberg(sq_matrix&,sq_matrix&);
	//Inversing
	void inv(sq_matrix&);
	sq_matrix inv();
	//Set
	void set_column(int,const std::vector<double>&);
	//Transpose
	sq_matrix transpose();
	//Condition number(2-norm)
	double cond2();
	//Submatrix
	sq_matrix submatrix(int left, int top, int n_size=0);
	sq_matrix lowertriangle();
	sq_matrix uppertriangle();
	sq_matrix diagonal();
	//Eigenvalues
	std::vector<double> ev_power();//With power methods
	sq_matrix ev_QR(bool nonsingular=false);//QR method
	sq_matrix ev_QR(sq_matrix&,bool nonsingular=false);//QR method
	bool JacobiTrans(sq_matrix&, int i, int j);//Jacobi Transformer
	sq_matrix ev_Jacobi();//Jacobi method
	//Preparing for solving linear systems
	int jacobian_iteration(std::vector<double>&,std::vector<double>&,
										const std::vector<double>&);
	int jacobian_weighted_iteration(std::vector<double>&,std::vector<double>&,
										const std::vector<double>&,double w);
	int	jaco_iter_tri_matrix(std::vector<double>&,std::vector<double>&,
										const std::vector<double>&);
	int	jacobian_weighted_iteration_tri(std::vector<double>&,std::vector<double>&,
										const std::vector<double>&,double w);
	int gauss_seidel_iteration(std::vector<double>&,std::vector<double>&,
										const std::vector<double>&);
	int	gauss_seidel_iter_tri_matrix(std::vector<double>&,std::vector<double>&,
										const std::vector<double>&);
	void residual(std::vector<double>&,const std::vector<double>&,
										const std::vector<double>&);
	void residual_tri(std::vector<double>&,const std::vector<double>&,
										const std::vector<double>&);
	int P_inv(std::vector<double>&,const std::vector<double>&);
	int P_inv_tri(std::vector<double>&,const std::vector<double>&);
	int two_grid_iter(std::vector<double>& x,const std::vector<double>& b);
	int two_grid_tri_iter(std::vector<double>& x,const std::vector<double>& b);
	//Solving linear systems
	std::vector<double> right_tri_solve(const std::vector<double>&);
	std::vector<double> right_tri_solve_tri(const std::vector<double>&);
	std::vector<double> gaussian_solve(const std::vector<double>&);
	std::vector<double> gaussian_solve_tri(const std::vector<double>&);
	std::vector<double> jacobian_solve(const std::vector<double>&);
	std::vector<double> jacobian_solve_tri_matrix(const std::vector<double>&);
	std::vector<double> gauss_seidel_solve(const std::vector<double>&);
	std::vector<double> gauss_seidel_solve_tri_matrix(const std::vector<double>&);
	std::vector<double> steepest_descent(const std::vector<double>&);
	std::vector<double> steepest_descent_tri(const std::vector<double>&);
	std::vector<double> conjugate_gradient(const std::vector<double>&);
	std::vector<double> conjugate_gradient_tri(const std::vector<double>&);
	std::vector<double> SSOR_PCG(const std::vector<double>&);
	std::vector<double> SSOR_PCG_tri(const std::vector<double>&);
	std::vector<double> two_grid(const std::vector<double>&);
	std::vector<double> two_grid_tri(const std::vector<double>&);
	//Judging properties
	bool is_diagonal();
	bool is_tridiagonal();
	bool is_diagonal_like();//Only 1*1 or 2*2 matrices on the diagonal
	double sum_without_diagonal();
	//Generate matrix
	//Generate matrix(r,Ar,A^2r,...,A^(n-1)r)
	sq_matrix derive(const std::vector<double>&);
private:
protected:
};
/////////////////////////////////////////////////////////////////////////////

class triMatrix
{
public:
	/*Constructor*/
	triMatrix():_zero(0),_size(0){}
	triMatrix(int n):_size(n),_mid(n),
					_up(n-1),_down(n-1),_zero(0){}
	triMatrix(double*, int);/*Assign the entries in the main diagonal*/
	triMatrix(double*, double*, int);/*Assign the entries in the main diagonal
	and the upper bydiagonal*/
	triMatrix(double*, double*, double*, int);/*Assign the entries in the main
	diagonal, the upper bydiagonal, and the lower bydiagonal*/
	
	/*Assign the entries in the main diagonal*/
	triMatrix(const std::vector<double>& mid)
	:_size(mid.size()),_zero(0){_mid=mid;}
	/*Assign the entries in the main diagonal and the upper bydiagonal*/
	triMatrix
	(const std::vector<double>& mid, const std::vector<double>& upper)
	:_size(mid.size()),_zero(0){_mid=mid;_up=upper;}
	/*Assign the entries in the main
	diagonal, the upper bydiagonal, and the lower bydiagonal*/
	triMatrix
	(std::vector<double> mid, std::vector<double> upper, 
	std::vector<double> lower):_size(mid.size()),_zero(0)
	{_mid=mid;_up=upper;_down=lower;}
	
	/*Overload equality*/
	triMatrix operator=(const triMatrix& rh)
	{_size=rh._size; _mid=rh._mid; _up=rh._up; _down=rh._down; return *this;}
	
	int size() const {return _size;}
	std::vector<double> mid() const {return _mid;}
	std::vector<double> upper() const {return _up;}
	std::vector<double> lower() const {return _down;}
	
	double get(int i,int j) const;
	double& at(int i,int j);
	
	void print(int width=10) const;
	
	/*Solve linear system with Gaussian Elimination*/
	std::vector<double> solve(const std::vector<double>&) const;
	/*Multiply a vector*/
	std::vector<double> rmultVector(const std::vector<double>&) const;
	
private:
	int _size;
	std::vector<double> _mid;
	std::vector<double> _up;
	std::vector<double> _down;
	/*This variable is set to be returned by "at" function if
	the given location is out of the three diagonals*/
	double _zero;
};
////////////////////////////////////////////////////////////////////////////
/////////////Member functions of class matrix///////////////////////////////


#endif
