#include <mex.h>

void fftshift(double* x,int N);
void fftshiftC(double* xr, double *xi, int N);
void callFFTN(double *, size_t, const mwSize *, double **, double **);


/******************************************************************************/
void fftshift(double* x,int N)
{
  double temp;
  for(int k=0;k<N/4;k++){
      temp = x[2*k];
      x[2*k] = x[2*k+N/2];
      x[2*k+N/2] = temp;

      temp = x[2*k+1];
      x[2*k+1] = x[2*k+N/2+1];
      x[2*k+N/2+1] = temp;
  }
}

/******************************************************************************/
void fftshiftC(double* xr, double* xi, int N)
{
  double temp;
  for(int k=0;k<N/2;k++){
      temp = xr[k];
      xr[k] = xr[k+N/2];
      xr[k+N/2] = temp;

      temp = xi[k];
      xi[k] = xi[k+N/2];
      xi[k+N/2] = temp;
  }
}

/******************************************************************************/

void callFFTN(double          *data, 
	      size_t              M,
	      size_t              N,
	      double        **sol_r,
	      double        **sol_i
	      )
 {
   mxArray *F,*f;
   mxArray *LHS[1];
   /* int N1 = N[0]; */
   /* int N2 = N[1]; */

  //  f = mxCreateNumericArray(K,N,mxDOUBLE_CLASS,mxCOMPLEX);
  f = mxCreateDoubleMatrix(M,N,mxCOMPLEX);
  memcpy(mxGetPr(f),data,sizeof(double)*M*N);
  mexCallMATLABWithTrap(1,LHS,1,&f,"fftn");

  F = LHS[0];

  *sol_r = (double *)mxGetData(F);
  *sol_i = (double *)mxGetImagData(F);
 
  mxDestroyArray(f);
  //  mxDestroyArray(F);  
}
