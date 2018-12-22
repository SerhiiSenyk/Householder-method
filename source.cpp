#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define RAND_MAX 5
double HouseholderMethod(double **ppMatrix,int size_Of_Matrix);
void displaySquareMatrix(double **ppMatrix,int size_Of_Matrix);
double** allocationMatrix(int size_Of_Matrix);
void deleteMatrix(double **ppMatrix,int size_Of_Matrix);
void enterMatrixElements(double **ppMatrix,int size_Of_Matrix);
void randomEnterMatrixElenemts(double **ppMatrix,int size_Of_Matrix);
int entersize_Of_Matrix();
int main()
{
	printf("Program for calculating a determinant of the matrix using the Householder method\n");
	while(true)
	{
		int N = entersize_Of_Matrix();
		double **A = allocationMatrix(N);
		double determinant;
		randomEnterMatrixElenemts(A,N);
		//enterMatrixElements(A,N);
		printf("Matrix :\n");
		displaySquareMatrix(A,N);
		determinant = HouseholderMethod(A,N);
		printf("Matrix after Householder method :\n");
		displaySquareMatrix(A,N);
		printf("Determinant = %lf\n\n",determinant);
		deleteMatrix(A,N);
	  system ("pause");
	  system("cls");
	}
  return 0;
}
int entersize_Of_Matrix()
{
	int size_Of_Matrix;
	while(true)
    {
     printf("Enter size of matrix : ");
       while(scanf("%d",&size_Of_Matrix) != 1)
       {
          printf("Vvedeno ne chyslo.Vvedit' zanovo : ");
          flushall();
       }
      if(size_Of_Matrix < 1 || size_Of_Matrix > 1000)
      printf("1 <= size_Of_Matrix <= 1000 !!!\n");
	  else break;
     }
	return size_Of_Matrix;
}
void enterMatrixElenemts(double** matrix,int N)
{
	FILE*fileOut = fopen("Matrix.bin","rb");
	  if (fileOut == NULL)
	  {
		printf("Error opening file\n");
		return;
	  }
	for (int i = 0;i < N;++i)
	{
		for (int j = 0;j < N;++j)
		fscanf(fileOut,"%lf",&matrix[i][j]);
	}
    fclose(fileOut);
	return;
}
int sign(double x)
{
   if(x > 0)
	   return 1;
   if(x < 0)
	   return -1;
   if(x == 0)
       return 0; 
}
double HouseholderMethod(double **A,int N)
{
  double **Ak = allocationMatrix(N);
  double **Q = allocationMatrix(N);
  double **UUt = allocationMatrix(N);
  double *U = (double*)calloc(N,sizeof(double));
  double sigma;
  double beta;
  double Sum;
  for(int k = 0;k < N - 1;++k)
  { 
     Sum = 0;
     for(int p = k;p < N;++p)
	 {
        Sum += pow(A[p][k],2);
	 }
     sigma = -sign(A[k][k])*sqrt(Sum);//обчислення  sigma
     beta = pow(pow(sigma,2) - sigma*A[k][k],-1);
	 int n = 1;
	 for(int i = 0;i < N;++i)
	 {
		 if(i < k)
		 {
             U[i] = 0;
		 }
		 if(i == k)
		 {
			 U[i] = A[k][k] - sigma;
		 }
		 if(i > k)
		 {
             U[i] = A[k + n][k];
			 ++n;
		 }
	 }
	 for(int i = 0;i < N;++i)
	 {
		 for(int j = 0;j < N;++j)
		 {
			 UUt[i][j] = U[i]*U[j];
		 }
	 }
	 for(int i = 0;i < N;++i)
	 {
         for(int j = 0;j < N;++j)
		 {
            if (i == j)
				Q[i][j] = 1 - beta*UUt[i][j];
			else
				Q[i][j] = 0 - beta*UUt[i][j];
		 }
	 }
     for(int i = 0;i < N; ++i)
     {
          for(int j = 0;j < N; ++j)
          {
             Sum = 0 ;
             for (int k = 0;k < N; ++k)
             {
                 Sum += Q[i][k]*A[k][j];
             }
            Ak[i][j] = Sum;
          }
     }
	 Sum = 0;
	 for(int i = 0;i < N; ++i)
     {
          for(int j = 0;j < N; ++j)
          {
              A[i][j] = Ak[i][j];
		  }
	 }
  }
  double determinant = 1;
  for(int k = 0;k < N;++k)
  {
	  determinant *= A[k][k];
  }
  deleteMatrix(Ak,N);
  deleteMatrix(UUt,N);
  deleteMatrix(Q,N);
  free(U);
  return determinant;
}
void displaySquareMatrix(double** matrix,int N)
{
  for (int i = 0;i < N;++i)
  {
     printf("\n");
       for (int j = 0;j < N;++j)
         printf ("%.2f\t",matrix[i][j]);
  }
  printf("\n\n");
  return;
}
double** allocationMatrix(int N)
{
  double **matrix = (double**)calloc(N,sizeof(double));
	for(int i = 0;i < N;++i)
	{
		matrix[i] = (double*)calloc(N,sizeof(double));
	}
	return matrix;
}
void deleteMatrix(double **ppMatrix,int N)
{
	for(int i = 0;i < N;++i)
	{
		free(ppMatrix[i]);ppMatrix[i] = NULL;
	}
	free(ppMatrix);ppMatrix = NULL;
  return;
}
void randomEnterMatrixElements(double** matrix,int N)
{
    srand(time(NULL));
	for(int i = 0;i < N;++i)
	{
		for (int j = 0;j < N;++j)
		{
		    matrix[i][j] = rand()%RAND_MAX;
		    if(int(matrix[i][j])%RAND_MAX == 0)	
				matrix[i][j] = 0;
		}
	}
   return;
}