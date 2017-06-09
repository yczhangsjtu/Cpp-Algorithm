#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

#define G(x,y) exp(x)*cos(y)

using namespace std;

double **allocVector(int N)
{
	double **V = new double*[N];
	for(int i = 0; i < N; i++)
		V[i] = new double[N];
	return V;
}

void freeVector(double **V, int N)
{
	for(int i = 0; i < N; i++)
		delete []V[i];
	delete []V;
}

void setVector(double **V, double v, int N)
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			V[i][j] = v;
}

void printVector(const char *info, double **V, int N)
{
	cout << info << endl;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			cout << setw(20) << V[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void evaluateVector(double **U, double h, int N)
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			U[i][j] = G((i+1)*h,(j+1)*h);
		}
	
}

double computeMaxDiff(double **U, double **V, int N)
{
	double max = 0.0;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			double m = fabs(U[i][j]-V[i][j]);
			if(m > max) max = m;
		}
	return max;
}

void initRightVector(double **B, double h, int N)
{
	{
		int i = 0;
		{
			int j = 0;
			B[i][j] = G((i+1)*h,j*h)+G(i*h,(j+1)*h);
		}
		{
			for(int j = 1; j < N-1; j++)
				B[i][j] = G(i*h,(j+1)*h);
		}
		{
			int j = N-1;
			B[i][j] = G(i*h,(j+1)*h)+G((i+1)*h,(j+2)*h);
		}
	}
	{
		for(int i = 1; i < N-1; i++)
		{
			{
				int j = 0;
				B[i][j] = G((i+1)*h,j*h);
			}
			{
				for(int j = 1; j < N-1; j++)
					B[i][j] = 0.0;
			}
			{
				int j = N-1;
				B[i][j] = G((i+1)*h,(j+2)*h);
			}
		}
	}
	{
		int i = N-1;
		{
			int j = 0;
			B[i][j] = (G((i+1)*h,j*h)+G((i+2)*h,(j+1)*h));
		}
		{
			for(int j = 1; j < N-1; j++)
				B[i][j] = G((i+2)*h,(j+1)*h);
		}
		{
			int j = N-1;
			B[i][j] = (G((i+2)*h,(j+1)*h)+G((i+1)*h,(j+2)*h));
		}
	}
}

/**
 *  Here the matrix has a -4 on the diagonal and four 1's in each line
 */
void matrixTimesVector(double **V, double **U, int N)
{
	{
		int i = 0;
		{
			int j = 0;
			U[i][j] = -(V[i+1][j]+V[i][j+1]-4*V[i][j]);
		}
		{
			for(int j = 1; j < N-1; j++)
				U[i][j] = -(V[i+1][j]+V[i][j-1]+V[i][j+1]-4*V[i][j]);
		}
		{
			int j = N-1;
			U[i][j] = -(V[i+1][j]+V[i][j-1]-4*V[i][j]);
		}
	}
	{
		for(int i = 1; i < N-1; i++)
		{
			{
				int j = 0;
				U[i][j] = -(V[i-1][j]+V[i+1][j]+V[i][j+1]-4*V[i][j]);
			}
			{
				for(int j = 1; j < N-1; j++)
					U[i][j] = -(V[i-1][j]+V[i+1][j]+V[i][j-1]+V[i][j+1]-4*V[i][j]);
			}
			{
				int j = N-1;
				U[i][j] = -(V[i-1][j]+V[i+1][j]+V[i][j-1]-4*V[i][j]);
			}
		}
	}
	{
		int i = N-1;
		{
			int j = 0;
			U[i][j] = -(V[i-1][j]+V[i][j+1]-4*V[i][j]);
		}
		{
			for(int j = 1; j < N-1; j++)
				U[i][j] = -(V[i-1][j]+V[i][j-1]+V[i][j+1]-4*V[i][j]);
		}
		{
			int j = N-1;
			U[i][j] = -(V[i-1][j]+V[i][j-1]-4*V[i][j]);
		}
	}
}

void vectorMinus(double **V, double **U, double **R, int N)
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			R[i][j] = V[i][j]-U[i][j];
}

void vectorAdd(double **V, double v, double **U, double u, double **R, int N)
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			R[i][j] = v*V[i][j] + u*U[i][j];
}

void vectorMultiply(double **V, double **U, double t, int N)
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			U[i][j] = t*V[i][j];
}

void computeResidual(double **X, double **B, double **R, int N)
{
	double **AX = allocVector(N);
	matrixTimesVector(X,AX,N);
	vectorMinus(B,AX,R,N);
	freeVector(AX,N);
}

void copyVector(double **U, double **V, int N)
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			V[i][j] = U[i][j];
}

double maxNorm(double **V, int N)
{
	double max = 0.0;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			double m = fabs(V[i][j]);
			if(m > max) max = m;
		}
	return max;
}

double innerProduct(double **U, double **V, int N)
{
	double sum = 0.0;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			sum += U[i][j]*V[i][j];
	return sum;
}

void solveByConjugateGradient(double **X, double **B, int N)
{
	double **R =allocVector(N);
	double **nR=allocVector(N);
	double **V =allocVector(N);
	double **AV=allocVector(N);
	double tol = 1e-10;
	setVector(X,0.0,N);
	
	computeResidual(X,B,R,N);
	copyVector(R,V,N);
	double initResidual=maxNorm(R,N);
	if(initResidual<tol) return;
	
	for( int i=0; i<10000; i++ )
	{
		if(maxNorm(R,N)/initResidual<tol)
		{
			cout << "Number of iteration is " << i << endl;
			return;
		}
		matrixTimesVector(V,AV,N);
		double rr=innerProduct(R,R,N);
		double t=rr/innerProduct(V,AV,N);
		vectorAdd(X,1.0,V,t,X,N);
		vectorAdd(R,1.0,AV,-t,nR,N);
		double s=innerProduct(nR,nR,N)/rr;
		vectorAdd(nR,1.0,V,s,V,N);
		copyVector(nR,R,N);
	}
	freeVector(R,N);
	freeVector(nR,N);
	freeVector(V,N);
	freeVector(AV,N);
}

void makeJacobiIteration(double **X, double **B, int N)
{
	double **AX = allocVector(N);
	double **AXB= allocVector(N);
	matrixTimesVector(X,AX,N);
	vectorMinus(AX,B,AXB,N);
	vectorMultiply(AXB,AXB,0.25,N);
	vectorMinus(X,AXB,X,N);
	freeVector(AX,N);
	freeVector(AXB,N);
}

void solveByJacobiMethod(double **X, double **B, int N)
{
	double **R = allocVector(N);
	double tol = 1e-8;
	setVector(X,0.0,N);
	for(int i = 0; i < 10000; i++)
	{
		computeResidual(X,B,R,N);
		if(maxNorm(R,N)<tol)
		{
			cout << "Number of iteration is " << i << endl;
			return;
		}
		makeJacobiIteration(X,B,N);
	}
	freeVector(R,N);
}

void restrictResidual(double **ref, double **crs, int N)
{
	for(int i = 0; i < N/2; i++)
		for(int j = 0; j < N/2; j++)
			crs[i][j] = ref[2*i][2*j];
}

void prolongCorrection(double **crs, double **ref, int N)
{
	for(int i = 0; i < N/2; i++)
		for(int j = 0; j < N/2; j++)
		{
			if(i % 2==0)
			{
				if(j % 2==0)
					ref[i][j] = crs[i/2][j/2];
				else
					ref[i][j] = 0.5*(crs[i/2][j/2]+crs[i/2][j/2+1]);
			}
			else
			{
				if(j % 2==0)
					ref[i][j] = 0.5*(crs[i/2][j/2]+crs[i/2+1][j/2]);
				else
					ref[i][j] = 0.25*(crs[i/2][j/2]+crs[i/2+1][j/2]+
									  crs[i/2+1][j/2]+crs[i/2+1][j/2+1]);
			}
		}
}

void makeTwoGridIteration(double **X, double **B, int N)
{
	double **R = allocVector(N);
	double **D = allocVector(N);
	double **CR = allocVector(N/2);
	double **CD = allocVector(N/2);
	int nu = 2;
	setVector(CD,0.0,N/2);
	for(int i = 0; i < nu; i++)
		makeJacobiIteration(X,B,N);
		
	computeResidual(X,B,R,N);
	restrictResidual(R,CR,N);
	makeJacobiIteration(CD,CR,N/2);
	prolongCorrection(CD,D,N);
	vectorAdd(X,1.0,D,1.0,X,N);
		
	for(int i = 0; i < nu; i++)
		makeJacobiIteration(X,B,N);
		
	freeVector(R,N);
	freeVector(D,N);
	freeVector(CR,N);
	freeVector(CD,N);
}



int main()
{
	for(int N = 10; N <= 1280; N*=2)
	{
		double h = 1.0/(N+1);
		double **X, **B, **U;
		X = allocVector(N);
		B = allocVector(N);
		U = allocVector(N);
		
		cout << "N=" << N << endl;
		cout << "N^2=" << N*N << endl;
		initRightVector(B,h,N);
		
		//solveByConjugateGradient(X,B,N);
		solveByJacobiMethod(X,B,N);
		
		matrixTimesVector(X,B,N);
		evaluateVector(U,h,N);
		matrixTimesVector(U,B,N);
		double err = computeMaxDiff(X,U,N);
		cout << "Maximum Error = " << err << endl;
		cout << "N^2 err = " << N*N*err << endl;
		cout << endl;
		
		freeVector(X,N);
		freeVector(B,N);
		freeVector(U,N);
	}
	return 0;
}
