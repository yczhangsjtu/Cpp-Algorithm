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


//Constructor//////////////////////////////////////
matrix::matrix(unsigned int m,unsigned int n)
{
	m=m>0?m:1;//If the input numbers are 0, change it to 1
	n=n>0?n:1;
	std::vector<double>line(n);
	for(int i=0;i<m;++i)
		_matrix.push_back(line);
}
//Read a matrix from a file
bool matrix::readFile(const char *filename)
{
	std::ifstream fin(filename);
	if(!fin)
	{
		std::cerr << "Failed to open the file!\n" << filename << std::endl;
		return false;
	}
	int m = n_l(), n = n_c();
	for(int i = 1; i<=m; i++)
		for(int j = 1; j<=n; j++)
		{
			fin >> at(i,j);
			if( (i<m || j<n) && fin.eof() )
			{
				std::cerr << "Not enough data!\n" << filename <<std::endl;
				fin.close();
				return false;
			}
		}
	fin.close();
	return true;
}
//Get the reference of a particular entry//////////
double& matrix::at(int i,int j)
{
	return _matrix[i-1][j-1];
}
///////////////////////////////////////////////////

//Get the value of a particular entry///////////////////////
const double matrix::get(int i, int j)const
{
	return (i>=1 && j>=1 && i<=n_l() && j<=n_c())? _matrix[i-1][j-1]:0;
}
///////////////////////////////////////////////////////////

//Print a matrix///////////////////////////////////////////
int matrix::print(std::ostream& os,int width) const
{
	for( int i=1; i<=n_l(); ++i )
	{
		for(int j=1; j<=n_c(); ++j)
			os<<std::setw(width)<<std::fixed<<get(i,j)<<' ';
		os<<std::endl;
	}
	os<<std::endl;
}
///////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//Overload operators//////////////////////////////////////////
//Assignment//////////////////////////////////////////////////
matrix& matrix::operator=(const matrix& mtx)
{
	_matrix=mtx._matrix;
	return *this;
}
//////////////////////////////////////////////////////////////

//Comparation///////////////////////////////////////////////
bool matrix::operator==(const matrix& mtx)
{
	return _matrix==mtx._matrix;
}
////////////////////////////////////////////////////////////
bool matrix::operator!=(const matrix& mtx)
{
	return _matrix!=mtx._matrix;
}
////////////////////////////////////////////////////////////

//Plus//////////////////////////////////////////////////////
matrix matrix::operator+(const matrix& mtx)
{
	matrix n_mtx(n_l(),n_c());
	for(int i=1;i<=n_l();i++)
		for(int j=1;j<=n_c();j++)
			n_mtx.at(i,j)=at(i,j)+mtx.get(i,j);
	return n_mtx;
}
////////////////////////////////////////////////////////////

//Minus/////////////////////////////////////////////////////
matrix matrix::operator-(const matrix& mtx)
{
	matrix n_mtx(n_l(),n_c());
	for(int i=1;i<=n_l();i++)
		for(int j=1;j<=n_c();j++)
			n_mtx.at(i,j)=at(i,j)-mtx.get(i,j);
	return n_mtx;
}
/////////////////////////////////////////////////////////////

//Right Multiply a vector////////////////////////////////////
std::vector<double> matrix::rmult_vector(const std::vector<double>& vct)
{
	std::vector<double>n_vtc;
	for( int i=1;i<=n_l();i++ )
	{
		n_vtc.push_back(0);
		for( int j=1;j<=vct.size();j++ )
			n_vtc.back()+=vct[j-1]*get(i,j);
	}
	return n_vtc;
}
/////////////////////////////////////////////////////////////

//Left Multiply a vector/////////////////////////////////////
std::vector<double> matrix::lmult_vector(const std::vector<double>&vct)
{
	std::vector<double>n_vtc;
	for( int i=1;i<=n_c();i++ )
	{
		n_vtc.push_back(0);
		for( int j=1;j<=vct.size();j++ )
			n_vtc.back()+=vct[j-1]*get(j,i);
	}
	return n_vtc;
}
////////////////////////////////////////////////////////////


//Get value from the muliplication of two vectors
void matrix::vector_mult(const std::vector<double>& lvct,const std::vector<double>& rvct)
{
	for( int i=1; i<=n_l(); i++ )
		for( int j=1; j<=n_c(); j++ )
			if( i<=lvct.size() && j<=rvct.size() )
				at(i,j)=lvct[i-1]*rvct[j-1];
			else
				at(i,j)=0;
}

//Elementary row transforms
void matrix::elem_row_trans(int row1, int row2)
{
	if( row1>=1 && row2>=1 && row1<=n_l() && row2<=n_l() )
		_matrix[row1-1].swap(_matrix[row2-1]);
}
void matrix::elem_row_trans(int from, double times, int to)
{
	if( from>=1 && from<=n_l() )
		if( to>=1 && to<=n_l() )
			for( int i=1; i<=n_c(); i++ )
				at(to,i)+=at(from,i)*times;
		else
			for( int i=1; i<=n_c(); i++ )
				at(from,i)*=times;
}
//Elementary column transforms
void matrix::elem_clm_trans(int clm1, int clm2)
{
	double tmp;
	if( clm1>=1 && clm2>=1 && clm1<=n_c() && clm2<=n_c() )
		for( int i=1; i<=n_l(); i++ )
		{
			tmp=at(i,clm1);
			at(i,clm1)=at(i,clm2);
			at(i,clm2)=tmp;
		}
}
void matrix::elem_clm_trans(int from, double times, int to)
{
	if( from>=1 && from<=n_c() )
		if( to>=1 && to<=n_c() )
			if( times!=0 )
			{
				for( int i=1; i<=n_l(); i++ )
					at(i,to)+=at(i,from)*times;
			}
		else
			for( int i=1; i<=n_l(); i++ )
				at(i,from)*=times;
}
//Get row
std::vector<double> matrix::get_row(int i) const
{
	std::vector<double>n_vct;
	if( i>=1 && i<=n_l() )
		n_vct=_matrix[i-1];
	return n_vct;
}
//Get column
std::vector<double> matrix::get_column(int i) const
{
	std::vector<double>n_vct;
	if( i>=1 && i<=n_c() )
		for( int j=1; j<=n_l(); j++ )
			n_vct.push_back(get(j,i));
	return n_vct;
}
//Norms
double matrix::normF()
{
	double sum=0;
	for( int i=1; i<=n_l();i++ )
		for( int j=1; j<=n_l();j++ )
		{
			sum+=get(i,j)*get(i,j);
		}
	return sqrt(sum);
}
//Submatrix
matrix matrix::submatrix(int left, int top, int width, int height)
{
	if (width<=0 || width>n_c()-left+1) width=n_c()-left+1;
	if (height<=0 || height>n_l()-top+1 ) height=n_l()-top+1;
	matrix n_matrix(height,width);
	if( left>=1 && left<=n_c() && top>=1 && top<=n_l() )
		for( int i=0; i<height; i++ )
			for( int j=0; j<width; j++ )
				n_matrix.at(i+1,j+1)=get(top+i,left+j);
	return n_matrix;
}
//////////////////////////////////////////////////////
/////////Member functions of class sq_matrix//////////
//Multiply
//Size
int sq_matrix::size() const
{
	return _matrix.size();
}
//Operator oveload
sq_matrix sq_matrix::operator+(const sq_matrix& mtx)
{
    sq_matrix n_mtx(size());
    for(int i=1;i<=size();++i)
        for(int j=1;j<=size();++j)
            n_mtx.at(i,j)=get(i,j)+mtx.get(i,j);
    return n_mtx;
}
sq_matrix sq_matrix::operator-(const sq_matrix& mtx)
{
    sq_matrix n_mtx(size());
    for(int i=1;i<=size();++i)
        for(int j=1;j<=size();++j)
            n_mtx.at(i,j)=get(i,j)-mtx.get(i,j);
    return n_mtx;
}
sq_matrix sq_matrix::operator-()
{
    sq_matrix n_mtx(size());
    for(int i=1;i<=size();++i)
        for(int j=1;j<=size();++j)
            n_mtx.at(i,j)=-get(i,j);
    return n_mtx;
}
sq_matrix sq_matrix::operator*(const sq_matrix& mtx)
{
	sq_matrix n_mtx(size());
	for( int i=1;i<=size();i++ )
		for( int j=1;j<=size();j++ )
		{
			n_mtx.at(i,j)=0;
			for( int k=1;k<=size();k++ )
				n_mtx.at(i,j)+=get(i,k)*mtx.get(k,j);
		}
	return n_mtx;
}
sq_matrix sq_matrix::operator*(double r)
{
    sq_matrix n_mtx(size());
    for(int i=1; i<=size(); ++i)
        for(int j=1; j<=size(); ++j)
            n_mtx.at(i,j)=get(i,j)*r;
    return n_mtx;
}
//Power
sq_matrix sq_matrix::power(int n)
{
	sq_matrix A(size());
	A.idlize();
	for(int i=0; i<n; ++i)
		A=A*(*this);
	return A;
}
//Make itself an identity matrix
void sq_matrix::idlize()
{
	for( int i=1;i<=n_l();i++ )
		for( int j=1;j<=n_l();j++ )
			at(i,j)=i==j?1:0;
}
//Get values from a vector
void sq_matrix::get_values(const std::vector<double>&vct)
{
	for( int i=1;i<=n_l();i++ )
		for( int j=1;j<=n_l();j++ )
			at(i,j)=(i-1)*n_l()+(j-1)<vct.size()?vct[(i-1)*n_l()+(j-1)]:0;
}
//LU Decomposition
void sq_matrix::LU(sq_matrix& L,sq_matrix& U)
{
	sq_matrix n_L(n_l());
	sq_matrix n_U(n_l());
	n_L.idlize();
	n_U=*this;
	for( int i=1; i<n_l(); i++ )
	{
		if( n_U.at(i,i)==0 ) return;
		double times;
		for( int j=i+1; j<=n_l(); j++ )
		{
			times=-n_U.at(j,i)/n_U.at(i,i);
			n_U.elem_row_trans(i,times,j);
			n_L.elem_clm_trans(j,-times,i);
		}
	}
	L=n_L;
	U=n_U;
}
bool sq_matrix::QR(sq_matrix& Q,sq_matrix& R,bool nonsingular)
{
	sq_matrix n_R(size());
	sq_matrix Trans(size());
	sq_matrix keep(size());
	keep.idlize();
	std::vector<double> clm;
	n_R=*this;
	for( int i=1; i<size(); i++ )
	{
		clm=n_R.get_column(i);
		clm=vector_tail(clm,i-1);
		if(!QRTrans(Trans,clm)) return false;
		n_R=Trans*n_R;
		if(nonsingular) keep=keep*Trans;
	}
	R=n_R;
	if(nonsingular)
	{
		Q=keep;
	}
	else
	{
		n_R.inv(n_R);
		Q=(*this)*n_R;
	}
	return true;
}
bool sq_matrix::Heisenberg(sq_matrix& Q,sq_matrix& H)
{
	sq_matrix n_H(size());
	sq_matrix Trans(size());
	sq_matrix keep(size());
	keep.idlize();
	std::vector<double> clm;
	n_H=*this;
	for(int i=1; i<size()-1; i++)
	{
		clm=n_H.get_column(i);
		clm=vector_tail(clm,i);
		if(!QRTrans(Trans,clm)) return false;
		n_H=Trans*n_H*Trans;
		keep=Trans*keep;
	}
	H=n_H;
	Q=keep;
}
//Inverse
void sq_matrix::inv(sq_matrix& Inv)
{
	sq_matrix n_Inv(n_l());
	sq_matrix n_copy(n_l());
	n_Inv.idlize();
	n_copy=*this;
	for( int i=1; i<n_l(); i++ )
	{
		if( n_copy.at(i,i)==0 ) return;
		double times;
		for( int j=i+1; j<=n_l(); j++ )
		{
			times=-n_copy.at(j,i)/n_copy.at(i,i);
			n_copy.elem_row_trans(i,times,j);
			n_Inv.elem_row_trans(i,times,j);
		}
	}
	for( int i=n_l(); i>=1; i-- )
	{
		if( n_copy.at(i,i)==0 ) return;
		double times;
		for( int j=i-1; j>=1; j-- )
		{
			times=-n_copy.at(j,i)/n_copy.at(i,i);
			n_copy.elem_row_trans(i,times,j);
			n_Inv.elem_row_trans(i,times,j);
		}
		times=1/n_copy.at(i,i);
		n_copy.elem_row_trans(i,times);
		n_Inv.elem_row_trans(i,times);
	}
	Inv=n_Inv;
}
sq_matrix sq_matrix::inv()
{
	sq_matrix A(size());
	inv(A);
	return A;
}
//Set
//Set column
void sq_matrix::set_column(int c,const std::vector<double>& vct)
{
	if(c<=0 || c>size()) return;
	for(int i=1; i<=size(); ++i)
		at(i,c)=(i<=vct.size()? vct[i-1]: 0);
}
//Transpose
sq_matrix sq_matrix::transpose()
{
	sq_matrix A(size());
	for(int i=1; i<=size(); ++i)
		for(int j=1; j<=size(); ++j)
			A.at(i,j)=get(j,i);
	return A;
}
//QR Decomposition
bool sq_matrix::QRTrans(sq_matrix& mtx, std::vector<double>&vct)
{
	if(fabs(norm(vct))<1e-10) return false;
	if( vct.size()>0 )
	{
		sq_matrix n_mtx(size());
		sq_matrix ww(vct.size());
		std::vector<double>w(vct.size());
		std::vector<double>tgt(vct.size());
		double times;
		tgt[0]=norm(vct);
		if(inner_product(tgt,vct)<0) tgt=tgt/(-1);
		w=tgt-vct;
		w=w/norm_signed(w);
		ww.vector_mult(w,w);
		n_mtx.idlize();
		mtx.idlize();
		for( int i=1; i<=vct.size(); i++ )
		{
			for( int j=1; j<=vct.size(); j++ )
			{
				n_mtx.at(i+size()-vct.size(),j+size()-vct.size())-=2*ww.at(i,j);
			}
		}
		mtx=n_mtx;
	}
	return true;
}
//Jacobi's Transformer matrix
bool sq_matrix::JacobiTrans(sq_matrix& P, int i, int j)
{
	//i shouldn't be equal to j, and shouldn't be over
	//a[i][j] shouldn't be zero
	if( i==j || i<1 || j<1 || i>size() || j>size() || get(i,j)==0 ) 
		return false;
	//Create new matrix
	sq_matrix n_P(size());
	n_P.idlize();
	//If a[i][i]!=a[j][j]
	if( get(i,i)!=get(j,j) )
	{
		double b=fabs(get(i,i)-get(j,j));
		double c=2*get(i,j)*(get(i,i)>get(j,j)?1:-1);
		n_P.at(i,i)=sqrt(1.0/2*(1+b/sqrt(b*b+c*c)));
		n_P.at(j,i)=-c/2/n_P.get(i,i)/sqrt(b*b+c*c);
	}
	else//If a[i][i]==a[j][j]
		n_P.at(i,i)=n_P.at(j,i)=sqrt(2)/2;
	///////////////////////////////////
	n_P.at(i,j)=-n_P.get(j,i);
	n_P.at(j,j)=n_P.at(i,i);
	P=n_P;
	return true;
}
//Tridiagonalize matrix
void sq_matrix::tridiagonal(double lower, double mid, double upper,int from,int to)
{
    if(from<1) from=1;
    if(from>size()) from=size();
    if(to<from || to>size()) to=size();
	for( int i=from; i<=to;i++ )
		for( int j=from; j<=to;j++ )
		{
			at(i,j)= i==j?mid:(i-j==1?lower:(j-i==1?upper:0));
		}
}
sq_matrix sq_matrix::sqrt_all()
{
	sq_matrix A(size());
	for(int i=1; i<=size(); ++i)
		for(int j=1; j<=size(); ++j)
			A.at(i,j)=sqrt(fabs(get(i,j)));
	return A;
}
sq_matrix sq_matrix::sqrt_diag()
{
	sq_matrix A(size());
	for(int i=1; i<=size(); ++i)
		A.at(i,i)=sqrt(fabs(get(i,i)));
	return A;
}
//Submatrix
sq_matrix sq_matrix::submatrix(int left, int top, int n_size)
{
	if (n_size<=0 || n_size>n_c()-left+1) n_size=n_c()-left+1;
	if (n_size<=0 || n_size>n_l()-top+1 ) n_size=n_l()-top+1;
	sq_matrix n_matrix(n_size);
	if( left>=1 && left<=n_c() && top>=1 && top<=n_l() )
		for( int i=0; i<n_size; i++ )
			for( int j=0; j<n_size; j++ )
				n_matrix.at(i+1,j+1)=get(top+i,left+j);
	return n_matrix;
}
sq_matrix sq_matrix::lowertriangle()
{
	sq_matrix A(size());
	for(int i=1; i<=size(); ++i)
		for(int j=1; j<=i; ++j)
			A.at(i,j)=get(i,j);
	return A;
}
sq_matrix sq_matrix::uppertriangle()
{
	sq_matrix A(size());
	for(int i=1; i<=size(); ++i)
		for(int j=i; j<=size(); ++j)
			A.at(i,j)=get(i,j);
	return A;
}
sq_matrix sq_matrix::diagonal()
{
	sq_matrix A(size());
	for(int i=1; i<=size(); ++i)
		A.at(i,i)=get(i,i);
	return A;
}
//Condition number
double sq_matrix::cond2()
{
	sq_matrix A(size());
	A=*this;
	const double eps=1e-10;
	std::vector<double>x(size());//The vector to iterated
	std::vector<double>z;//The vector to store the new x
						//in each step temporarily
						
	double u,nu;//The eigenvalue(nu to store the new value temporarily)
	
	double max;//Max eigenvalue
	double max_inv;//Max eigenvalue of A^{-1}
	for( int j=0; j<2; j++ )//Do the following twice with A and A^{-1}
							//respectively
	{
		double diff=1;//Keep the difference between two 'u';
		x[0]=1;//Initiate x
		for( int i=0; i<200 && diff>eps; i++ )
		{
			z=A.rmult_vector(x);//z=A*x
			vector_normalize(z,2);//z=z/(signed)norm2(z)
			nu=inner_product(x,A.rmult_vector(x));//nu=(x,A*x)
			diff=fabs(u-nu);//diff=fabs(n,nu)
			//Iteration
			x=z;//x->z
			u=nu;//u->nu
		}
		if( j==1 ) break;//The following excecuted in the first loop
		max=u;
		inv(A);
	}
	max_inv=u;
	return fabs(max*max_inv);	
}
//Eigenvectors
//With power method
std::vector<double> sq_matrix::ev_power()
{
	sq_matrix A(size());//A copy of this matrix
	sq_matrix Trans(size());//Householder transformer
	
	A=*this;
	std::vector<double>x(size());//The vector to iterated
	std::vector<double>z;//The vector to store the new x
						//in each step temporarily
	double u,nu;//The eigenvalue(nu to store the new value temporarily)
	double eps=1e-10;
	
	std::vector<double> return_vector;//The vector to return
	
	do
	{
		//Set the difference back to 1(to be larger than epsilon)
		double diff=1;
		x[0]=1;//Initiate x
		for( int i=0; i<200 && diff>eps; i++ )
		{
			z=A.rmult_vector(x);//z=A*x
			vector_normalize(z,2);//z=z/(signed)norm2(z)
			nu=inner_product(x,A.rmult_vector(x));//nu=(x,A*x)
			diff=fabs(u-nu);//diff=fabs(n,nu)
			//Iteration
			x=z;//x->z
			u=nu;//u->nu
		}
		return_vector.push_back(u);//Push the eigenvalue to the return vector
		
		if( A.size()<=1 ) break;//End of loop
		
		A.QRTrans(Trans,x);//Householder transformer
		A=Trans*A*Trans;//A=HAH
		A=A.submatrix(2,2);//A=A_{n-1}
	}while( 1 );
	return return_vector;
}
//With QR method
sq_matrix sq_matrix::ev_QR(bool nonsingular)
{
	double diff=1,eps=1e-10;
	sq_matrix Q(size());//The Q matrix
	sq_matrix R(size());//The R matrix
	sq_matrix A(size());//A copy of this matrix
	sq_matrix nA(size());//To store new matrix temporarily
	A=*this;
	
	for( int i=0; i<500 && diff>eps && !is_diagonal_like(); i++ )
	{
		A.QR(Q,R,nonsingular);//QR decomposition
		nA=R*Q;//New matrix
		diff=fabs((A-nA).normF());//Count the difference
								  //to judge whether to stop
		A=nA;//Iteration
	}
	
	return A;
}
//With QR method(A=Q^{-1}DQ), Q will be passed by parameter sQ
sq_matrix sq_matrix::ev_QR(sq_matrix &sQ,bool nonsingular)
{
	double diff=1,eps=1e-10;
	sq_matrix Q(size());//The Q matrix
	sq_matrix R(size());//The R matrix
	sq_matrix A(size());//A copy of this matrix
	sq_matrix nA(size());//To store new matrix temporarily
	A=*this;
	sQ.idlize();//Set sQ be identity matrix
	for( int i=0; i<500 && diff>eps && !is_diagonal_like(); i++ )
	{
		A.QR(Q,R,nonsingular);//QR decomposition
		nA=R*Q;//New matrix
		diff=fabs((A-nA).normF());//Count the difference
								  //to judge whether to stop
		A=nA;//Iteration
		sQ=sQ*Q;//sQ=Q1Q2...Qn
	}
	
	return A;
}
//Jacobi Method for eigenvalues
sq_matrix sq_matrix::ev_Jacobi()
{
	double tol=1e-10;//Tolerance to stop
	sq_matrix A(size());//A copy of this matrix
	sq_matrix P(size());//The Jacobi Transformer
	A=*this;
	//Loop until the sum of all the abs value except
	//those on the diagonal are smaller than tolerance
	while( A.sum_without_diagonal()>tol )
	{//Set a[2][1], a[3][1] a[3][2],...,a[n][1]...a[n][n-1] in turn to zero
		for( int i=2; i<=size(); i++ )
			for( int j=1; j<i; j++ )
			{
				if( A.get(i,j)==0 ) continue;//If it's alread zero, skip
				A.JacobiTrans(P,i,j);//Construct the Jacobi Transformer
				A=P*A;//A=PA  (P')
				//Since P[i][j]=-P[j][i], and all the other off-diagonal
				//entries of P are zeros, we need only change two symbols
				P.at(i,j)*=-1;P.at(j,i)*=-1;//P=P'
				A=A*P;//A=PAP'
			}
	}
	return A;
}
//Solving linear systems
//Solving the linear system assuming that it's up triangular
std::vector<double> sq_matrix::right_tri_solve(const std::vector<double>& b)
{
	std::vector<double> x(size());
	for( int i=size(); i>0; i-- )
	{
		if(at(i,i)!=0) x[i-1]=b[i-1]/at(i,i);
		else return x;
		for( int j=size(); j>i; j-- )
		{
			x[i-1]-=at(i,j)*x[j-1]/at(i,i);
		}
	}
	return x;
}
//Solving the linear system assuming that it's up triangular and tridiagonal
std::vector<double> sq_matrix::right_tri_solve_tri(const std::vector<double>& b)
{
	std::vector<double> x(size());
	for( int i=size(); i>0; i-- )
	{
		if(at(i,i)!=0) x[i-1]=b[i-1]/at(i,i);
		else return x;
		if(i!=size())x[i-1]-=at(i,i+1)*x[i]/at(i,i);
	}
	return x;
}
//Solve linear system with Gaussian Elimination
std::vector<double> sq_matrix::gaussian_solve(const std::vector<double>& b)
{
	std::vector<double>x(size());
	x=b;
	//print();
	sq_matrix n_U(size());
	n_U=*this;
	
	for( int i=1; i<size(); i++ )
	{
		if( n_U.at(i,i)==0 )
		{
			bool success = false;
			for(int j=i+1; j<=size(); j++)
				if(n_U.at(i,j)!=0)
				{
					n_U.elem_row_trans(i,j);
					double tmp = x[i-1];
					x[i-1]=x[j-1];
					x[j-1]=tmp;
					success = true;
					break;
				}
			if(!success)
			{
				std::cerr<<"Unexpected zero at left up corner!"<<std::endl;
				return x;
			}
		}
		double times;
		for( int j=i+1; j<=size(); j++ )
		{
			times=-n_U.at(j,i)/n_U.at(i,i);
			if(times!=0) n_U.elem_row_trans(i,times,j);
			x[j-1]+=x[i-1]*times;
		}
	}
	
	//print_vector(b);
	//print_vector(rmult_vector(n_U.right_tri_solve(x)));
	//n_U.print();
	//std::cout << "Error " << norm(b - rmult_vector(n_U.right_tri_solve(x))) << std::endl;
	return n_U.right_tri_solve(x);
}

//Solve linear system with Gaussian Elimination
std::vector<double> sq_matrix::gaussian_solve_tri(const std::vector<double>& b)
{
	std::vector<double>x(size());
	x=b;
	
	sq_matrix n_U(size());
	n_U=*this;
	
	for( int i=1; i<size(); i++ )
	{
		if( n_U.at(i,i)==0 ) return x;
		double times;
		times=-n_U.at(i+1,i)/n_U.at(i,i);
		n_U.at(i+1,i)=0;n_U.at(i+1,i+1)+=times*n_U.at(i,i+1);
		x[i]+=x[i-1]*times;
	}
	return n_U.right_tri_solve_tri(x);
}


//Solve linear systems
//Preparation
void sq_matrix::residual(std::vector<double>& r,const std::vector<double>& x,
										const std::vector<double>& b)
{
	r=b-rmult_vector(x);
}
void sq_matrix::residual_tri(std::vector<double>& r,const std::vector<double>& x,
										const std::vector<double>& b)
{
	r=b-rmult_vector_tri(x);
}
//Solve the linear system with Jacobi method
//Preparation
int sq_matrix::jacobian_iteration(	std::vector<double>&nvct,
									std::vector<double>&ovct,
									const std::vector<double>&b)
{
	if( nvct.size()<size() || b.size()<size() ) return -1;
	for( int i=1; i<=size(); ++i )
	{
		if( get(i,i)!=0 )
		{
			//x_i=b_i
			nvct[i-1]=b[i-1];
			for( int j=1; j<=size(); ++j )//x_i=Sum(-a_ij*x_j)+b_i
				if( j!=i )
					nvct[i-1]-=get(i,j)*ovct[j-1];
			nvct[i-1]/=get(i,i);
		}
		else
			return -1;
	}
	return 1;
}
int sq_matrix::jacobian_weighted_iteration(	std::vector<double>&nvct,
									std::vector<double>&ovct,
									const std::vector<double>&b,
									double w)
{
	if( nvct.size()<size() || b.size()<size() ) return -1;
	for( int i=1; i<=size(); ++i )
	{
		if( get(i,i)!=0 )
		{
			//x_i=b_i
			nvct[i-1]=w*b[i-1];
			for( int j=1; j<=size(); ++j )//x_i=Sum(-a_ij*x_j)+b_i
				if( j!=i )
					nvct[i-1]-=w*get(i,j)*ovct[j-1];
			nvct[i-1]/=get(i,i);
			nvct[i-1]+=(1-w)*ovct[i-1];
		}
		else
			return -1;
	}
	return 1;
}
int sq_matrix::jaco_iter_tri_matrix(	std::vector<double>&nvct,
									std::vector<double>&ovct,
									const std::vector<double>&b)
{
	if( nvct.size()<size() || b.size()<size() ) return -1;
	for( int i=1; i<=size(); ++i )
	{
		if( get(i,i)!=0 )
		{
			//x_i=b_i
			nvct[i-1]=b[i-1];
			//for( int j=1; j<=size(); ++j )//x_i=Sum(-a_ij*x_j)+b_i
			if( i>1 )
				nvct[i-1]-=get(i,i-1)*ovct[i-2];
			if( i<size() )
				nvct[i-1]-=get(i,i+1)*ovct[i];
			nvct[i-1]/=get(i,i);
		}
		else
			return -1;
	}
	return 1;
}
int sq_matrix::jacobian_weighted_iteration_tri(	std::vector<double>&nvct,
									std::vector<double>&ovct,
									const std::vector<double>&b,
									double w)
{
	if( nvct.size()<size() || b.size()<size() ) return -1;
	for( int i=1; i<=size(); ++i )
	{
		if( get(i,i)!=0 )
		{
			//x_i=b_i
			nvct[i-1]=w*b[i-1];
			//for( int j=1; j<=size(); ++j )//x_i=Sum(-a_ij*x_j)+b_i
			if( i>1 )
				nvct[i-1]-=w*get(i,i-1)*ovct[i-2];
			if( i<size() )
				nvct[i-1]-=w*get(i,i+1)*ovct[i];
			nvct[i-1]/=get(i,i);
			nvct[i-1]+=(1-w)*ovct[i-1];
		}
		else
		{
			std::cerr<< "Error! Zero in diagonal" << std::endl;
			return -1;
		}
	}
	return 1;
}
//Main function
std::vector<double> sq_matrix::jacobian_solve(const std::vector<double>& b)
{
	std::vector<double> ox(size());
	std::vector<double> nx(size());
	std::vector<double> r(size());
	double tol=1.0e-8;
	residual(r,ox,b);
	double init_norm_of_r=norm(r,0);
	if( init_norm_of_r==0 ) return ox;
	for( int i=0; i<1000000; ++i )
	{/*
		std::cerr<<"r=";
		print_vector(r);
		std::cerr<<"x=";
		print_vector(ox);*/
		residual(r,nx,b);
		if(jacobian_iteration(nx,ox,b)==-1){std::cerr<<"Error!";return nx;} 
		if( norm(r,0)/init_norm_of_r<tol )
		{
			std::cout<<" Number of steps by Jacobi method="<<i<<std::endl;
			return nx;
		}
		ox=nx;
	}
	return nx;
}
std::vector<double> sq_matrix::jacobian_solve_tri_matrix(const std::vector<double>& b)
{
	std::vector<double> ox(size());
	std::vector<double> nx(size());
	std::vector<double> r(size());
	double tol=1.0e-8;
	residual_tri(r,ox,b);
	double init_norm_of_r=norm(r,0);
	if( init_norm_of_r==0 ) return ox;
	for( int i=0; i<1000000; ++i )
	{
		//std::cerr<<"r=";
		//print_vector(r);
		//std::cerr<<"x=";
		//print_vector(ox);
		residual_tri(r,nx,b);
		if(jaco_iter_tri_matrix(nx,ox,b)==-1){std::cerr<<"Error!";return nx;} 
		if( norm(r,0)/init_norm_of_r<tol )
		{
			std::cout<<" Number of steps by Jacobi method="<<i<<std::endl;
			return nx;
		}
		ox=nx;
	}
	return nx;
}
//Solve the linear system with Gauss-Seidel method
//Preparation
int sq_matrix::gauss_seidel_iteration(	std::vector<double>&nvct,
									std::vector<double>&ovct,
									const std::vector<double>&b)
{
	if( nvct.size()<size() || b.size()<size() ) return -1;
	for( int i=1; i<=size(); ++i )
	{
		if( get(i,i)!=0 )
		{
			//x_i=b_i
			nvct[i-1]=b[i-1];
			for( int j=1; j<=size(); ++j )//x_i=Sum(-a_ij*x_j)+b_i
				if( j<i )
					nvct[i-1]-=get(i,j)*nvct[j-1];
				else if( j>i )
					nvct[i-1]-=get(i,j)*ovct[j-1];
			nvct[i-1]/=get(i,i);
		}
		else
			return -1;
	}
	return 1;
}
int sq_matrix::gauss_seidel_iter_tri_matrix(	std::vector<double>&nvct,
												std::vector<double>&ovct,
												const std::vector<double>&b)
{
	if( nvct.size()<size() || b.size()<size() ) return -1;
	for( int i=1; i<=size(); ++i )
	{
		if( get(i,i)!=0 )
		{
			//x_i=b_i
			nvct[i-1]=b[i-1];
			//for( int j=1; j<=size(); ++j )//x_i=Sum(-a_ij*x_j)+b_i
			if( i>1 )
				nvct[i-1]-=get(i,i-1)*nvct[i-2];
			if( i<size() )
				nvct[i-1]-=get(i,i+1)*ovct[i];
			nvct[i-1]/=get(i,i);
		}
		else
			return -1;
	}
	return 1;
}

//Main function
std::vector<double> sq_matrix::gauss_seidel_solve(const std::vector<double>& b)
{
	std::vector<double> ox(size());
	std::vector<double> nx(size());
	std::vector<double> r(size());
	double tol=1.0e-8;
	residual(r,ox,b);
	double init_norm_of_r=norm(r,0);
	if( init_norm_of_r==0 ) return ox;
	for( int i=0; i<1000000; ++i )
	{
		//std::cerr<<"r=";
		//print_vector(r);
		//std::cerr<<"x=";
		//print_vector(ox);
		residual(r,nx,b);
		if(gauss_seidel_iteration(nx,ox,b)==-1){std::cerr<<"Error!";return nx;} 
		if( norm(r,0)/init_norm_of_r<tol )
		{
			//std::cout<<" Number of steps by Gauss-Seidel method="<<i<<std::endl;
			return nx;
		}
		ox=nx;
	}
	return nx;
}
std::vector<double> sq_matrix::gauss_seidel_solve_tri_matrix(const std::vector<double>& b)
{
	std::vector<double> ox(size());
	std::vector<double> nx(size());
	std::vector<double> r(size());
	double tol=1.0e-8;
	residual_tri(r,ox,b);
	double init_norm_of_r=norm(r,0);
	if( init_norm_of_r==0 ) return ox;
	for( int i=0; i<1000000; ++i )
	{
		//std::cerr<<"r=";
		//print_vector(r);
		//std::cerr<<"x=";
		//print_vector(ox);
		residual_tri(r,nx,b);
		if(gauss_seidel_iter_tri_matrix(nx,ox,b)==-1){std::cerr<<"Error!";return nx;} 
		if( norm(r,0)/init_norm_of_r<tol )
		{
			//std::cout<<" Number of steps by Gauss-Seidel method="<<i<<std::endl;
			return nx;
		}
		ox=nx;
	}
	return nx;
}
std::vector<double> sq_matrix::steepest_descent(const std::vector<double>& b)
{
	std::vector<double>x(size());
	std::vector<double>r(size());
	double init_norm_of_r=norm(b,0);
	if(init_norm_of_r<1e-8)return x;
	for( int i=1; i<=1000000; ++i )
	{
		residual(r,x,b);
		if(norm(r,0)/init_norm_of_r<1e-8)
		{
			//std::cout<<" Number of steps by steepest descent method="<<i<<std::endl;
			return x;
		}
		double t=inner_product(r,r)/inner_product(r,rmult_vector(r));
		x=x+t*r;
	}
	return x;
}
std::vector<double> sq_matrix::steepest_descent_tri(const std::vector<double>& b)
{
	std::vector<double>x(size());
	std::vector<double>r(size());
	double init_norm_of_r=norm(b,0);
	if(init_norm_of_r<1e-8)return x;
	for( int i=1; i<=1000000; ++i )
	{
		residual_tri(r,x,b);
		if(norm(r,0)/init_norm_of_r<1e-8)
		{
			//std::cout<<" Number of steps by steepest descent method="<<i<<std::endl;
			return x;
		}
		double t=inner_product(r,r)/inner_product(r,rmult_vector_tri(r));
		x=x+t*r;
	}
	return x;
}
std::vector<double> sq_matrix::conjugate_gradient(const std::vector<double>& b)
{
	std::vector<double>x(size());
	std::vector<double>r(size());
	std::vector<double>nr(size());
	std::vector<double>v(size());
	std::vector<double>Av(size());
	//r=b;
	for(int i=0; i<x.size(); ++i) x[i]=0;
	r=b-rmult_vector(x);
	//std::cout<<" r=";
	//print_vector(r);
	v=r;
	double init_norm_of_r=norm(b,0);
	if(init_norm_of_r<1e-8)return x;
	for( int i=1; i<=1000000; ++i )
	{
		if(norm(r,0)/init_norm_of_r<1e-8)
		{
			//std::cout<<" Number of steps by conjugate gradient method="<<i<<std::endl;
			return x;
		}
		Av=rmult_vector(v);
		double r_r=norm(r);r_r*=r_r;
		double t=r_r/inner_product(v,Av);
		//std::cout<<" rr="<<r_r<<std::endl;
		//std::cout<<" vAv="<<inner_product(v,Av)<<std::endl;
		//std::cout<<" t="<<t<<std::endl;
		x=x+t*v;
		//std::cout<<" x=";
		//print_vector(x);
		nr=r-t*Av;
		//std::cout<<" r=";
		//print_vector(nr);
		double s=inner_product(nr,nr)/r_r;
		//std::cout<<" s="<<s<<std::endl;
		v=nr+s*v;
		r=nr;
	}
	return x;
}
std::vector<double> sq_matrix::conjugate_gradient_tri(const std::vector<double>& b)
{
	std::vector<double>x(size());
	std::vector<double>r(size());
	std::vector<double>nr(size());
	std::vector<double>v(size());
	std::vector<double>Av(size());
	v=b;
	double init_norm_of_r=norm(b,0);
	if(init_norm_of_r<1e-8)return x;
	for( int i=1; i<=1000000; ++i )
	{
		residual_tri(r,x,b);
		if(norm(r,0)/init_norm_of_r<1e-8)
		{
			//std::cout<<" Number of steps by conjugate gradient method="<<i<<std::endl;
			return x;
		}
		Av=rmult_vector_tri(v);
		double t=inner_product(r,r)/inner_product(v,Av);
		x=x+t*v;
		nr=r-t*Av;
		double s=inner_product(nr,nr)/inner_product(r,r);
		v=nr+s*v;
		r=nr;
		
	}
	return x;
}
int sq_matrix::P_inv(std::vector<double>&c,const std::vector<double>&r)
{
	//Solve the function LD^{-1}Uc=r
	std::vector<double>u(size());
	//First solve the part: LD^{-1}u=r
	for(int i=1;i<=size();++i)
	{
		u[i-1]=r[i-1];
		if(get(i,i)==0) return -1;//a[i][i]==0
		for(int j=1; j<i; ++j)
			u[i-1]-=u[j-1]*get(i,j)/get(j,j);
	}
	//Second solve the part Uc=u
	c=right_tri_solve(u);
	
}
int sq_matrix::P_inv_tri(std::vector<double>&c,const std::vector<double>&r)
{
	//Solve the function LD^{-1}Uc=r
	std::vector<double>u(size());
	//First solve the part: LD^{-1}u=r
	for(int i=1;i<=size();++i)
	{
		u[i-1]=r[i-1];
		if(get(i,i)==0) return -1;//a[i][i]==0
		if(i>1)u[i-1]-=u[i-2]*get(i,i-1)/get(i-1,i-1);
	}
	//Second solve the part Uc=u
	c=right_tri_solve_tri(u);
}
//Preconditioned SSOR-PCG method
std::vector<double> sq_matrix::SSOR_PCG(const std::vector<double>& b)
{
	std::vector<double>x(size());
	std::vector<double>r(size());
	std::vector<double>nr(size());
	std::vector<double>v(size());
	std::vector<double>Av(size());
	std::vector<double>nc(size());
	std::vector<double>c(size());
	//x_0=0
	for(int i=0;i<size();++i) x[i]=0;
	r=b;
	P_inv(c,r);
	v=c;
	double init_norm_of_r=norm(b,0);
	if(init_norm_of_r<1e-8)return x;
	for( int i=1; i<=1000000; ++i )
	{
		if(norm(r,0)/init_norm_of_r<1e-8)
		{
			//std::cout<<" Number of steps by conjugate SSOR-PCG method="<<i<<std::endl;
			return x;
		}
		Av=rmult_vector(v);
		double rc=inner_product(r,c);
		double t=rc/inner_product(v,Av);
		x=x+t*v;
		//std::cout<<" x=";
		//print_vector(x);
		nr=r-t*Av;
		P_inv(nc,nr);
		//std::cout<<" r=";
		//print_vector(nr);
		double s=inner_product(nr,nc)/inner_product(r,c);
		//std::cout<<" s="<<s<<std::endl;
		v=nc+s*v;
		r=nr;
		c=nc;
	}
	return x;
}
//Preconditioned Conjugate-Gradient method(dealing with tridiagonal matrix)
std::vector<double> sq_matrix::SSOR_PCG_tri(const std::vector<double>& b)
{
	std::vector<double>x(size());
	std::vector<double>r(size());
	std::vector<double>nr(size());
	std::vector<double>v(size());
	std::vector<double>Av(size());
	std::vector<double>nc(size());
	std::vector<double>c(size());
	//x_0=0
	for(int i=0;i<size();++i) x[i]=0;
	r=b;
	P_inv(c,r);
	v=c;
	double init_norm_of_r=norm(b,0);
	if(init_norm_of_r<1e-8)return x;
	for( int i=1; i<=1000000; ++i )
	{
		if(norm(r,0)/init_norm_of_r<1e-8)
		{
			//std::cout<<" Number of steps by conjugate SSOR-PCG method="<<i<<std::endl;
			return x;
		}
		Av=rmult_vector_tri(v);
		double rc=inner_product(r,c);
		double t=rc/inner_product(v,Av);
		//std::cout<<"t'="<<t<<std::endl;
		x=x+t*v;
		//std::cout<<"x=";
		//print_vector(x);
		nr=r-t*Av;
		P_inv_tri(nc,nr);
		//std::cout<<"r=";
		//print_vector(nr);
		double s=inner_product(nr,nc)/inner_product(r,c);
		//std::cout<<"s="<<s<<std::endl;
		v=nc+s*v;
		r=nr;
		c=nc;
		
	}
	return x;
}
//Solve linear system by multigrid method
int sq_matrix::two_grid_iter(
	std::vector<double>& x,const std::vector<double>& b)
{
	int n = size();
	if(n<5)
	{
		x = gaussian_solve(b);
		return 1;
	}
	int n2 = (n+1)/2;
	//Create coarse matrix
	sq_matrix Ac(n2);
	for(int i = 1; i <= n2; i++)
		for(int j = 1; j <= n2; j++)
		{
			double s = 0.0;
			Ac.at(i,j) = at(2*i-1,2*j-1);
			s += 1.0;
			if(i>1)
			{
				Ac.at(i,j) += 0.25*at(2*i-2,2*j-1);
				s += 0.25;
			}
			if(2*i<=n)
			{
				Ac.at(i,j) += 0.25*at(2*i,2*j-1);
				s += 0.25;
			}
			if(j>1)
			{
				Ac.at(i,j) += 0.25*at(2*i-1,2*j-2);
				s += 0.25;
			}
			if(2*j<=n)
			{
				Ac.at(i,j) += 0.25*at(2*i-1,2*j);
				s += 0.25;
			}
			Ac.at(i,j)/=s;
		}
	/////////////////////////////////
	std::vector<double> nx(n);
	std::vector<double> r(n);
	std::vector<double> rc(n2);
	std::vector<double> dc(n2);
	std::vector<double> ndc(n2);
	std::vector<double> d(n);
	double norm_r = 1;
	double eps = 1e-8;
	//Pre-smoothing
	for(int i = 0; i<3; i++)
	{
		if(jacobian_weighted_iteration(nx,x,b,0.5)==-1){std::cerr<<"Error!";return -1;}
		//print_vector(nx);
		x=nx;
	}
	//Calculate residual
	residual(r,x,b);
	norm_r = norm(r,0);
	//If it's already good enough, return
	if(norm_r<eps) return 1;
	//Calculate the coarse residual
	rc[0] = r[0];
	for(int i = 1; i<n2-1; i++)
		rc[i] = r[2*i-1]/4 + r[2*i]/2 + r[2*i+1]/4;
	if(2*n2==n) rc[n2-1] = r[n-3]/4 + r[n-2]/2 + r[n-1]/4;
	else rc[n2-1] = r[n-2];
	////////////////////////////////////////////
	//std::cerr<<"r="<<std::endl;print_vector(r);
	//std::cerr<<"rc="<<std::endl;print_vector(rc);
	Ac.two_grid_iter(dc,rc);
	
	/*
	for(int i = 0; i<5; i++)
	{
		Ac.jacobian_weighted_iteration(ndc,dc,rc,0.5);
		dc = ndc;
	}*/
	//Prolong correction
	for(int i = 0; i<n2-1; i++)
	{
		d[2*i] = dc[i];
		d[2*i+1] = (dc[i]+dc[i+1])/2;
	}
	d[2*n2-2] = d[n2-1];
	if(2*n2==n) d[n-1] = (3*d[n2-1]-d[n2-2])/2;
	//Add the correction to the solution
	for(int i = 0; i<n; i++)
		x[i] += d[i];
	////////////////////////////////////////////////
	//std::cerr<<"dc="<<std::endl;print_vector(dc);
	//std::cerr<<"d="<<std::endl;print_vector(d);
	//std::cerr<<std::endl;
	//Post-smoothing
	for(int i = 0; i<5; i++)
	{
		if(jacobian_weighted_iteration(nx,x,b,0.5)==-1){std::cerr<<"Error!";return -1;}
		//print_vector(nx);
		x=nx;
	}
	return 1;
}
//Solve linear system by multigrid method
std::vector<double> sq_matrix::two_grid(const std::vector<double>& b)
{
	std::vector<double> x(size());
	std::vector<double> r(size());
	double tol=1.0e-8;
	residual(r,x,b);
	double init_norm_of_r=norm(r,0);
	if( init_norm_of_r < tol ) return x;
	for( int i=0; i<10000; ++i )
	{
		//std::cerr<<"r=";
		//print_vector(r);
		//std::cerr<<"x=";
		//print_vector(x);
		residual(r,x,b);
		if(two_grid_iter(x,b)==-1){std::cerr<<"Error!";return x;} 
		if( norm(r,0)/init_norm_of_r<tol )
		{
			std::cout<<" Number of steps by two grid method="<<i<<std::endl;
			return x;
		}
	}
	return x;
}
int sq_matrix::two_grid_tri_iter(
	std::vector<double>& x,const std::vector<double>& b)
{
	int n = size();
	if(n<5)
	{
		x = gaussian_solve_tri(b);
		return 1;
	}
	int n2 = (n+1)/2;
	//Create coarse matrix
	sq_matrix Ac(n2);
	/*
	for(int i = 1; i < n2; i++)
	{
		Ac.at(i,i) = at(2*i-1,2*i-1);
		Ac.at(i+1,i) = at(2*i,2*i-1);
		Ac.at(i,i+1) = at(2*i-1,2*i);
	}
	Ac.at(n2,n2) = at(2*n2-1,2*n2-1);*/
	
	for(int i = 1; i <= n2; i++)
		for(int j = i-1; j <= i+1 && j<=n2; j++)
		{
			if(j<=0) j++;
			double s = 0.0;
			Ac.at(i,j) = at(2*i-1,2*j-1);
			s += 1.0;
			if(i>1)
			{
				Ac.at(i,j) += 0.25*at(2*i-2,2*j-1);
				s += 0.25;
			}
			if(2*i<=n)
			{
				Ac.at(i,j) += 0.25*at(2*i,2*j-1);
				s += 0.25;
			}
			if(j>1)
			{
				Ac.at(i,j) += 0.25*at(2*i-1,2*j-2);
				s += 0.25;
			}
			if(2*j<=n)
			{
				Ac.at(i,j) += 0.25*at(2*i-1,2*j);
				s += 0.25;
			}
			Ac.at(i,j)/=s;
		}
	/////////////////////////////////
	std::vector<double> nx(n);
	std::vector<double> r(n);
	std::vector<double> rc(n2);
	std::vector<double> dc(n2);
	std::vector<double> ndc(n2);
	std::vector<double> d(n);
	double norm_r = 1;
	double eps = 1e-8;
	//Pre-smoothing
	for(int i = 0; i<3; i++)
	{
		if(jacobian_weighted_iteration_tri(nx,x,b,0.5)==-1){std::cerr<<"Error!";return -1;}
		//print_vector(nx);
		x=nx;
	}
	//Calculate residual
	residual_tri(r,x,b);
	norm_r = norm(r,0);
	//If it's already good enough, return
	if(norm_r<eps) return 1;
	//Calculate the coarse residual
	rc[0] = r[0];
	for(int i = 1; i<n2-1; i++)
		rc[i] = r[2*i-1]/4 + r[2*i]/2 + r[2*i+1]/4;
	if(2*n2==n) rc[n2-1] = r[n-3]/4 + r[n-2]/2 + r[n-1]/4;
	else rc[n2-1] = r[n-2];
	////////////////////////////////////////////
	//std::cerr<<"r="<<std::endl;print_vector(r);
	//std::cerr<<"rc="<<std::endl;print_vector(rc);
	Ac.two_grid_tri_iter(dc,rc);
	
	
	//Prolong correction
	for(int i = 0; i<n2-1; i++)
	{
		d[2*i] = dc[i];
		d[2*i+1] = (dc[i]+dc[i+1])/2;
	}
	d[2*n2-2] = d[n2-1];
	if(2*n2==n) d[n-1] = (3*d[n2-1]-d[n2-2])/2;
	//Add the correction to the solution
	for(int i = 0; i<n; i++)
		x[i] += d[i];
	////////////////////////////////////////////////
	//std::cerr<<"dc="<<std::endl;print_vector(dc);
	//std::cerr<<"d="<<std::endl;print_vector(d);
	//std::cerr<<std::endl;
	//Post-smoothing
	for(int i = 0; i<5; i++)
	{
		if(jacobian_weighted_iteration_tri(nx,x,b,0.5)==-1){std::cerr<<"Error!";return -1;}
		//print_vector(nx);
		x=nx;
	}
	return 1;
}
//Solve linear system by multigrid method
std::vector<double> sq_matrix::two_grid_tri(const std::vector<double>& b)
{
	std::vector<double> x(size());
	std::vector<double> r(size());
	double tol=1.0e-8;
	residual_tri(r,x,b);
	double init_norm_of_r=norm(r,0);
	if( init_norm_of_r < tol ) return x;
	for( int i=0; i<10000; ++i )
	{
		//std::cerr<<"r=";
		//print_vector(r);
		//std::cerr<<"x=";
		//print_vector(x);
		residual_tri(r,x,b);
		if(two_grid_tri_iter(x,b)==-1){std::cerr<<"Error!";return x;} 
		if( norm(r,0)/init_norm_of_r<tol )
		{
			std::cout<<" Number of steps by two grid method="<<i<<std::endl;
			return x;
		}
	}
	return x;
}

bool sq_matrix::is_diagonal()
{
	for( int i=1; i<=size(); i++ )
		for( int j=1; j<=size(); j++ )
			if( i!=j && get(i,j)!=0 ) return false;
	return true;
}
bool sq_matrix::is_tridiagonal()
{
	for( int i=1; i<=size(); i++ )
		for( int j=1; j<=size(); j++ )
			if( abs(i-j)>1 && get(i,j)!=0 ) return false;
	return true;
}
bool sq_matrix::is_diagonal_like()
{
	if( !is_tridiagonal() ) return false;
	for( int i=1; i<size()-1; i++ )
	{
		if( get(i+1,i)!=0 && get(i+2,i+1)!=0 ) return false;
		if( get(i,i+1)!=0 && get(i+1,i+2)!=0 ) return false;
	}
	return true;
}
double sq_matrix::sum_without_diagonal()
{
	double sum=0;
	for( int i=1; i<=size(); i++ )
		for( int j=1; j<=size(); j++ )
			sum+= i!=j?fabs(at(i,j)):0;
	return sum;
}

//Right Multiply a vector
std::vector<double> sq_matrix::rmult_vector_tri(const std::vector<double>& vct)
{
	std::vector<double>n_vtc;
	for( int i=1;i<=size();i++ )
	{
		n_vtc.push_back(0);
		if(i>1) n_vtc.back()+=vct[i-2]*get(i,i-1);
		if(i<size()) n_vtc.back()+=vct[i]*get(i,i+1);
		n_vtc.back()+=vct[i-1]*get(i,i);
	}
	return n_vtc;
}
//Left Multiply a vector
std::vector<double> sq_matrix::lmult_vector_tri(const std::vector<double>&vct)
{
	std::vector<double>n_vtc;
	for( int i=1;i<=size();i++ )
	{
		n_vtc.push_back(0);
		if(i>1) n_vtc.back()+=vct[i-2]*get(i-1,i);
		if(i<size()) n_vtc.back()+=vct[i]*get(i+1,i);
		n_vtc.back()+=vct[i-1]*get(i,i);
	}
	return n_vtc;
}
//Generate matrix
//(r,Ar,...,A^{n-1}r)
sq_matrix sq_matrix::derive(const std::vector<double>&r)
{
	sq_matrix A(size());
	sq_matrix P(size());
	P.idlize();
	for(int i=1; i<=size(); ++i)
	{
		A.set_column(i,P.rmult_vector(r));
		P=P*(*this);
	}
	return A;
}
//////////////////////////////////////////////////////
////////////////Other functions////////////////////////////////////////////////
//Generate matrices with particular properties
//Random matrices
sq_matrix rand_sq_matrix(int n)
{
	srand((unsigned int)time(0));
	sq_matrix A(n);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			A.at(i,j)=(double)rand()/pow(2,15)-(double)rand()/pow(2,15);
	return A;
}
//Generate an SPD matrix randomly
sq_matrix randSPDmatrix(int n)
{
	sq_matrix A(1);
	A=rand_sq_matrix(n);
	return A.transpose()*A;
}
//rational matrix
sq_matrix rational_matrix(const std::vector<double>& co)
{
	sq_matrix A(co.size());
	for(int i=1; i<A.size(); ++i)
		A.at(i+1,i)=1;
	A.set_column(A.size(),co);
	return A;
}
sq_matrix rand_rational_matrix(int n)
{
	srand((unsigned int)time(0));
	sq_matrix A(n);
	for(int i=1; i<A.size(); ++i)
		A.at(i+1,i)=1;
	for(int i=1; i<=A.size(); ++i)
		A.at(i,A.size())=(double)rand()/pow(2,15)-(double)rand()/pow(2,15);
	return A;
}
//Random upper triangular matrix
sq_matrix rand_upper_triangular(int n)
{
	srand((unsigned int)time(0));
	sq_matrix A(n);
	for(int i=1; i<=A.size(); ++i)
		for(int j=i; j<=A.size(); ++j)
			A.at(i,j)=(double)rand()/pow(2,15)-(double)rand()/pow(2,15);
	return A;
}
//Identity matrix
sq_matrix identity_matrix(int n)
{
    sq_matrix I(n);
    I.idlize();
    return I;
}
void plotVector(const std::vector<double>& vct)
{
	std::cout<<"a:={";
	for( int i=0; i<vct.size(); i++ )
	{
		std::cout<<'{'<<i<<','<<std::fixed<<vct[i]<<'}';
		if(i!=vct.size()-1)std::cout<<',';
	}
	std::cout<<"}"<<std::endl
		<<"ListPlot[a,Joined->True,PlotRange->All,AxesOrigin->{0,0}]"<<std::endl;
	/*std::cout<<'{';
	for(int i=0; i<vct.size(); i++)
	{
		std::cout<<std::fixed<<vct[i];
		if(i!=vct.size()-1) std::cout<<',';
	}
	std::cout<<'}'<<std::endl;*/
}
void printMatrix(const matrix& mtx)
{
	/*std::cout<<"a:={";
	for(int i=1;i<=mtx.n_l()/2;i++)
	{
		plotVector(mtx.get_row(i));
		if(i!=mtx.n_l()/2) std::cout<<',';
	}
	std::cout<<'}'<<std::endl<<"ListPlot3D[a,PlotRange->All]"<<std::endl;*/
	plotVector(mtx.get_row(1));
	plotVector(mtx.get_row(2));
	//mtx.print();
}
void printSquareMatrix(const sq_matrix& mtx)
{
	mtx.print();
}
double sumOfDiff(const matrix& mtx,int i,int j)
{
	if(i<=1 || i>=mtx.n_l() || j<=1 || j>=mtx.n_c())
		return 0;
	return mtx.get(i,j-1)+mtx.get(i,j+1)+mtx.get(i-1,j)+mtx.get(i+1,j)-4*mtx.get(i,j);
		
}




//////////////////Member Functions of Tridiagonal Matrix////////////////////
triMatrix::triMatrix(double* data, int n)
:_zero(0),_size(n),_mid(n),_up(n-1),_down(n-1)
{
	for(int i=0;i<n;++i)
		_mid[i]=data[i];
}
triMatrix::triMatrix(double* mid, double* upper, int n)
:_zero(0),_size(n),_mid(n),_up(n-1),_down(n-1)
{
	for(int i=0;i<n-1;++i)
	{
		_mid[i]=mid[i];
		_up[i]=upper[i];
	}
	_mid[n-1]=mid[n-1];
}
triMatrix::triMatrix(double* mid, double* upper, double* lower, int n)
:_zero(0),_size(n),_mid(n),_up(n-1),_down(n-1)
{
	for(int i=0;i<n-1;++i)
	{
		_mid[i]=mid[i];
		_up[i]=upper[i];
		_down[i]=lower[i];
	}
	_mid[n-1]=mid[n-1];
}
double triMatrix::get(int i,int j) const
{
	if(i==j) return getVectorValue(i-1,_mid);
	if(i-j==1) return getVectorValue(j-1,_down);
	if(j-i==1) return getVectorValue(i-1,_up);
	return 0;
}
double& triMatrix::at(int i,int j)
{
	if(i==j && i>=1 && i<=_mid.size()) return _mid[i-1];
	if(i-j==1 && j>=1 && j<=_down.size()) return _down[j-1];
	if(j-i==1 && i>=1 && i<=_up.size()) return _up[i-1];
	return _zero;
}
void triMatrix::print(int width) const
{
	for(int i=1; i<=_size; ++i)
	{
		for(int j=1; j<=_size; ++j)
			std::cout<<std::setw(width)<<std::fixed<<get(i,j)<<' ';
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
}


double getVectorValue(int i, const std::vector<double>& vec)
{
	if(i>=0 && i<vec.size()) return vec[i];
	return 0;
}

std::vector<double> triMatrix::solve(const std::vector<double>& b) const
{
	std::vector<double> x(b.size()),nb;
	nb=b;
	triMatrix tmp;
	double times;
	
	tmp=*this;
	for(int i=1; i<b.size(); ++i)
	{
		if(tmp.get(i,i)==0)
		{
			std::cerr<<"Zero on diagonal!"<<std::endl;
			return x;/*The entry on the diagonal can't be 0*/
		}
		times=-tmp.get(i+1,i)/tmp.get(i,i);
		tmp.at(i+1,i)=0;
		tmp.at(i+1,i+1)+=tmp.at(i,i+1)*times;
		nb[i]+=nb[i-1]*times;
	}
	x.back()=nb.back()/tmp.mid().back();
	for(int i=b.size()-2; i>=0; i--)
	{
		x[i]=nb[i]-tmp.get(i+1,i+2)*x[i+1];
		if(tmp.get(i+1,i+1)==0)
		{
			std::cerr<<"Zero on diagonal!"<<std::endl;
			return x;
		}
		x[i]/=tmp.get(i+1,i+1);
	}
	return x;
}
std::vector<double> triMatrix::rmultVector(const std::vector<double>& x) const
{
	std::vector<double> Ax(x.size());
	for(int i=1;i<=x.size();++i)
		Ax[i-1]=get(i,i-1)*getVectorValue(i-2,x)+
				get(i,i)*getVectorValue(i-1,x)+
				get(i,i+1)*getVectorValue(i,x);
	return Ax;
}



////////////////////Norm/////////////////////////////////////////////////////
double norm(const std::vector<double>&vct, int p)
{
	double sum=0;
	if( p>0 )
	{
		for( int i=0;i<vct.size();i++ )
			sum+=pow(vct[i],p);
		return pow(sum,1.0/p);
	}
	else
	{
		for( int i=0; i<vct.size();i++ )
			if(sum<fabs(vct[i])) sum=fabs(vct[i]);
		return sum;
	}
}
double norm_signed(const std::vector<double>&vct, int p)
{
	double sum=0;
	if( p )
	{
		int max_index=0;
		for( int i=0;i<vct.size();i++ )
		{
			sum+=pow(vct[i],p);
			if( fabs(vct[max_index])<fabs(vct[i]) ) max_index=i;
		}
		return pow(sum,1.0/p)*(max_index>=0?1:-1);
	}
	else
	{
		for( int i=0; i<vct.size();i++ )
			if(fabs(sum<fabs(vct[i]))) sum=vct[i];
		return sum;
	}
}
////Inner product////////////////////////////////////////////////////////////////////
double inner_product(const std::vector<double>&vct1, const std::vector<double>&vct2)
{
	double sum=0;
	for( int i=0; i<vct1.size() && i<vct2.size(); i++ )
		sum+=vct1[i]*vct2[i];
	return sum;
}
//Operator overload
std::vector<double> operator+(const std::vector<double>&vct1,const std::vector<double>&vct2)
{
	std::vector<double>n_vct;
	for( int i=0; i<vct1.size() && i<vct2.size(); i++ )
		n_vct.push_back(vct1[i]+vct2[i]);
	return n_vct;
}
std::vector<double> operator-(const std::vector<double>&vct1,const std::vector<double>&vct2)
{
	std::vector<double>n_vct;
	for( int i=0; i<vct1.size() && i<vct2.size(); i++ )
		n_vct.push_back(vct1[i]-vct2[i]);
	return n_vct;
}
std::vector<double> operator-(const std::vector<double>& vct)
{
	std::vector<double>n_vct;
	for(int i=0; i<vct.size(); i++)
		n_vct.push_back(-vct[i]);
	return n_vct;
}
std::vector<double> operator*(double times,const std::vector<double>&vct)
{
	std::vector<double>n_vct;
	for( int i=0; i<vct.size(); ++i )
		n_vct.push_back(times*vct[i]);
	return n_vct;
}
std::vector<double> operator*(const std::vector<double>&vct,double times)
{
	return times*vct;
}
std::vector<double> operator/(const std::vector<double>&vct,const double dbl)
{
	std::vector<double>n_vct;
	if( dbl!=0 )
	{
		for( int i=0; i<vct.size(); i++ )
			n_vct.push_back(vct[i]/dbl);
	}
	return n_vct;
}
////Get a subsection of vector
std::vector<double> vector_tail(const std::vector<double>&vct,const int index)
{
	std::vector<double>n_vct;
	if( index>=0 && index<vct.size() )
		for( int i=index; i<vct.size(); i++ )
			n_vct.push_back(vct[i]);
	return n_vct;
}
////Normalize
void vector_normalize(std::vector<double>&vct,int p)
{
	double max=0;
	double times;
	times=norm_signed(vct,p);
	if( times!=0 )
	{
		vct=vct/times;
	}
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
