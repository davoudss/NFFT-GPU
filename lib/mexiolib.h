#include<fftw3.h>

int printC(fftw_complex* x, int start, int N);
int printF(float*x, int start, int N);
int printFile(float *x, int N,int n);
int printCD(double* x, int start, int N);
int printFD(double*x, int start, int N);
int printFileD(double *x, int N,int n);
void DisplayMatrix(char*,double*, double*, int,int);


/***********************************************************************/
int printC(fftw_complex* x, int start, int N)
/* //N is the number of complex numbers, start is the starting complex number. */
/* { */
/*   printf("\n\n"); */
/*   for (int s=start;s<start+N;s++) */
/*     printf("(%.4e,%.4e)\n",x[2*s],x[2*s+1]); */
/*   return 0; */
/* } */
{
  printf("\n\n");
  for (int s=start;s<start+N;s++){
   printf("(%.4e,%.4e)\n",x[s][0],x[s][1]); 
  }
  return 0; 

}


/***********************************************************************/
int printCD(double* x, int start, int N)
//N is the number of complex numbers, start is the starting complex number.
{
  printf("\n\n");
  for (int s=start;s<start+N;s++)
    printf("(%.4e,%.4e)\n",x[2*s],x[2*s+1]);
  return 0;
}



/***********************************************************************/
int printF(float *x, int start, int N)
//N is the number of elements, start is the starting double number.
{
  printf("\n\n");
  for (int s=start;s<start+N;s++)
    printf("%e\n",x[s]);
  return 0;
}

/***********************************************************************/
int printFD(double *x, int start, int N)
//N is the number of elements, start is the starting double number.
{
  printf("\n\n");
  for (int s=start;s<start+N;s++)
    printf("%e\n",x[s]);
  return 0;
}

/***********************************************************************/
int printFile(float *x, int N,int n)
//N is the number of complex numbers
{
  FILE *fp;
  if(n==1)
    fp = fopen("matrix.m","w");
  else
    fp = fopen("matrix.m","a+");

  fprintf(fp,"F%d= [\n",n);

  for (int s=0;s<2*N;s++)
    fprintf(fp,"%+f%+fi\n",x[2*s],x[2*s+1]);

  fprintf(fp,"];\n");
  if(n==2)
    fprintf(fp,"plot(real(Fexact),imag(Fexact),'.',real(Fapprox),imag(Fapprox),'ro')\n legend('Exact','Appproximation')\n disp(['Relative error:', num2str(abs(norm(Fexact - Fapprox))/norm(Fexact))])");

  fclose(fp);

}

/***********************************************************************/
int printFileD(double *x, int N,int n)
//N is the number of complex numbers
{
  FILE *fp;
  if(n==1)
    fp = fopen("matrix.m","w");
  else
    fp = fopen("matrix.m","a+");

  fprintf(fp,"F%d= [\n",n);

  for (int s=0;s<2*N;s++)
    fprintf(fp,"%+f%+fi\n",x[2*s],x[2*s+1]);

  fprintf(fp,"];\n");
  if(n==2)
    fprintf(fp,"plot(real(Fexact),imag(Fexact),'.',real(Fapprox),imag(Fapprox),'ro')\n legend('Exact','Appproximation')\n disp(['Relative error:', num2str(abs(norm(Fexact - Fapprox))/norm(Fexact))])");

  fclose(fp);

}


void DisplayMatrix(char           *Name, 
		   double       *Data_r,
		   double       *Data_i, 
		   int                M, 
		   int                N
		   )
{
  int m, n;
  mexPrintf("%s = \n", Name);
  for(m = 0; m < M; m++, mexPrintf("\n"))
    for(n = 0; n < N; n++)
      mexPrintf("%+8.4f%+8.4fi ", Data_r[m + M*n],Data_i[m+M*n]);
}
