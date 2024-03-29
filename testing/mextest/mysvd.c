#include <string.h>
#include "mex.h"

void DisplayMatrix(char *Name, double *Data, int M, int N) { /* Display matrix data */
    int m, n;

    mexPrintf("%s = \n", Name);
    
    for(m = 0; m < M; m++, mexPrintf("\n"))
        for(n = 0; n < N; n++)
            mexPrintf("%8.4f ", Data[m + M*n]);
}
void CallSVD(double *Data, int M, int N) { /* Perform QR factorization by calling the MATLAB function */
    mxArray *S, *V, *U , *A;
    mxArray *ppLhs[3];
    
    DisplayMatrix("Input", Data, M, N);
    
    A = mxCreateDoubleMatrix(M, N, mxREAL); /* Put input in an mxArray */
    
    memcpy(mxGetPr(A), Data, sizeof(double)*M*N);
    mexCallMATLAB(3, ppLhs, 1, &A, "svd"); /* Call MATLAB's qr function */
    
    U = ppLhs[0];
    S = ppLhs[1];
    V = ppLhs[2];
    
    DisplayMatrix("U", mxGetPr(U), M, N);
    DisplayMatrix("S", mxGetPr(S), M, N);
    DisplayMatrix("V", mxGetPr(V), M, N);
    
    mxDestroyArray(U); /* No longer need these */
    mxDestroyArray(S);
    mxDestroyArray(V);
    mxDestroyArray(A);
}

void CallEig(double *Data, int M, int N) { /* Perform QR factorization by calling the MATLAB function */
    mxArray *Var, *Vec, *A;
    mxArray *ppLhs[2];
    
    DisplayMatrix("Input", Data, M, N);
    
    A = mxCreateDoubleMatrix(M, N, mxREAL); /* Put input in an mxArray */
    
    memcpy(mxGetPr(A), Data, sizeof(double)*M*N);
    mexCallMATLABWithTrap(2, ppLhs, 1, &A, "eig"); /* Call MATLAB's qr function */
    
    Var = ppLhs[0];
    Vec = ppLhs[1];
    
    DisplayMatrix("Var", mxGetPr(Var), M, N);
    DisplayMatrix("Vec", mxGetPr(Vec), M, N);
    
    mxDestroyArray(Var); /* No longer need these */
    mxDestroyArray(Vec);
    mxDestroyArray(A);
}

void CallReshape(double *Data, int M, int N) { /* Perform QR factorization by calling the MATLAB function */
    double *pr1,*pr2;
    mxArray *Mat, *A;
    mxArray *ppLhs[1];
    mxArray *ppRhs[3]={A,pr1,pr2};  
    

    ppRhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
    ppRhs[2] = mxCreateDoubleMatrix(1, 1, mxREAL);
    pr1 = mxGetPr(ppRhs[1]);
    pr2 = mxGetPr(ppRhs[2]);
    
    *pr1 = M*N;
    *pr1 = 1;
    
    A = mxCreateDoubleMatrix(M, N, mxREAL); /* Put input in an mxArray */
    ppRhs[0] = mxGetPr(A);
    
    memcpy(mxGetPr(A), Data, sizeof(double)*M*N);
    
    mexCallMATLAB(1, ppLhs, 3, ppRhs, "reshape"); /* Call MATLAB's qr function */
    return;
    Mat = ppLhs[0];
   
    DisplayMatrix("Mat", mxGetPr(Mat), M*N,1);
    
    mxDestroyArray(Mat); /* No longer need these */
    mxDestroyArray(A);
}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
#define M_IN prhs[0]
    
    if(nrhs != 1 || mxGetNumberOfDimensions(M_IN) != 2 || !mxIsDouble(M_IN))
        mexErrMsgTxt("Invalid input.");

//CallEig(mxGetPr(M_IN), mxGetM(M_IN), mxGetN(M_IN));
//CallSVD(mxGetPr(M_IN), mxGetM(M_IN), mxGetN(M_IN));
CallReshape(mxGetPr(M_IN), mxGetM(M_IN), mxGetN(M_IN));
}