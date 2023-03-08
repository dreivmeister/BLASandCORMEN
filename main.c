#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void DSCAL(int N, double SA, double* SX, int INCX) {
    if (N < 0 || INCX < 0 || SA == 1.0) {
        return;
    }
    if (INCX == 1) {
        // increment equal to one
        int m = N % 5;
        if (m != 0) {
            // go upto m
            for(int i = 0; i < m; i++) {
                SX[i] = SA*SX[i];
            }
            if (N < 5) {
                return;
            }
        }
        // loop unrolling if N is multiple of 5
        int mp1 = m;
        for(int i = mp1; i < N; i += 5) {
            SX[i] = SA*SX[i];
            SX[i+1] = SA*SX[i+1];
            SX[i+2] = SA*SX[i+2];
            SX[i+3] = SA*SX[i+3];
            SX[i+4] = SA*SX[i+4];
        }
    }
    else {
        int NINCX = N*INCX;
        for(int i = 0; i < NINCX; i += INCX) {
            SX[i] = SA*SX[i];
        }
    }
}

double DDOT(int N, double* DX, int INCX, double* DY, int INCY) {
    double ddot = 0.0;
    double dtemp = 0.0;
    if (N < 0) {
        return -1;
    }
    if (INCX == 1 && INCY == 1) {
        int m = N % 5;
        if (m != 0) {
            for(int i = 0; i < m; i++) {
                dtemp = dtemp + DX[i]*DY[i];
            }
            if (N < 5) {
                ddot = dtemp;
                return ddot;
            }
        }
        int mp1 = m;
        for(int i = mp1; i < N; i += 5) {
            dtemp = dtemp + DX[i]*DY[i] + 
            DX[i+1]*DY[i+1] + DX[i+2]*DY[i+2] + DX[i+3]*DY[i+3] + DX[i+4]*DY[i+4];
        }
    }
    else {
        int ix = 0;
        int iy = 0;
        if (INCX < 0) {
            ix = (-N+1)*INCX;
        }
        if (INCY < 0) {
            iy = (-N+1)*INCY;
        }
        for(int i = 0; i < N; i++) {
            dtemp = dtemp + DX[i]*DY[i];
            ix = ix + INCX;
            iy = iy + INCY;
        }
    }
    ddot = dtemp;
    return ddot;
}

void DAXPY(int N, double DA, double* DX, int INCX, double* DY, int INCY) {
    if (N < 0) {
        return;
    }
    if (DA == 0.0) {
        return;
    }
    if (INCX == 1 && INCY == 1) {
        int m = N % 4;
        if (m != 0) {
            for(int i = 0; i < m; i++) {
                DY[i] = DY[i] + DA*DX[i];
            }
            if (N < 4) {
                return;
            }
        }
        int mp1 = m;
        for(int i = mp1; i < N; i += 4) {
            DY[i] = DY[i] + DA*DX[i];
            DY[i+1] = DY[i+1] + DA*DX[i+1];
            DY[i+2] = DY[i+2] + DA*DX[i+2];
            DY[i+3] = DY[i+3] + DA*DX[i+3];
        }
    }
    else {
        int ix = 0;
        int iy = 0;
        if (INCX < 0) {
            ix = (-N+1)*INCX;
        }
        if (INCY < 0) {
            iy = (-N+1)*INCY;
        }
        for(int i = 0; i < N; i++) {
            DY[iy] = DY[iy] + DA*DX[ix];
            ix = ix + INCX;
            iy = iy + INCY;
        }
    }
}


//copy X into Y
void DCOPY(int N, double* DX, int INCX, double* DY, int INCY) {
    if (N < 0) {
        return;
    }
    if (INCX == 1 && INCY == 1) {
        //increments both equal to one

        int m = N % 7;
        if (m != 0) {
            for(int i = 0; i < m; i++) {
                DY[i] = DX[i];
            }
            if (N < 7) {
                return;
            }
        }
        int mp1 = m;
        for(int i = mp1; i < N; i += 7) {
            DY[i] = DX[i];
            DY[i+1] = DX[i+1];
            DY[i+2] = DX[i+2];
            DY[i+3] = DX[i+3];
            DY[i+4] = DX[i+4];
            DY[i+5] = DX[i+5];
            DY[i+6] = DX[i+6];
        }
    }
    else {
        // increments not equal to one or unequal
        int ix = 0;
        int iy = 0;
        if (INCX < 0) {
            ix = (-N+1)*INCX;
        }
        if (INCY < 0) {
            iy = (-N+1)*INCY;
        }
        for(int i = 0; i < N; i++) {
            DY[iy] = DX[ix];
            ix = ix + INCX;
            iy = iy + INCY;
        }
    }
}

double DNRM2(int N, double* X, int INCX) {
    //this is wrong but who really cares?
    if (N < 0) {
        return -1;
    }
    double dnrm2 = 0.0;
    if (INCX == 1) {
        for(int i = 0; i < N; i++) {
            dnrm2 += X[i]*X[i];
        }
    }
    else {
        int nincx = N*INCX;
        for(int i = 0; i < nincx; i += INCX) {
            dnrm2 += X[i]*X[i];
        }
    }
    return sqrt(dnrm2);
}

double DASUM(int N, double* DX, int INCX) {
    double dasum = 0.0;
    double dtemp = 0.0;
    if (N < 0 || INCX < 0) {
        return -1;
    }
    if (INCX == 1) {
        int m = N % 6;
        if (m != 0) {
            for(int i = 0; i < N; i++) {
                dtemp = dtemp + abs(DX[i]);
            }
            if (N < 6) {
                return dtemp;
            }
        }
        int mp1 = m;
        for(int i = mp1; i < N; i+=6) {
            dtemp = dtemp + abs(DX[i]) + abs(DX[i+1]) + abs(DX[i+2]) + 
                    abs(DX[i+3]) + abs(DX[i+4]) + abs(DX[i+5]);
        }
    }
    else {
        int nincx = N*INCX;
        for(int i = 0; i < nincx; i += INCX) {
            dtemp = dtemp + abs(DX[i]);
        }
    }
    return dtemp;
}

int IDAMAX(int N, double* DX, int INCX) {
    int idamax = -1;
    if (N < 1 || INCX < 0) {
        return idamax;
    }
    idamax = 0;
    if (N == 1) {
        return idamax;
    }
    if (INCX == 1) {
        double dmax = abs(DX[0]);
        for(int i = 1; i < N; i++) {
            if (abs(DX[i]) > dmax) {
                idamax = i;
                dmax = abs(DX[i]);
            }
        }
    }
    else {
        int ix = 0;
        double dmax = abs(DX[0]);
        ix = ix + INCX;
        for(int i = 1; i < N; i++) {
            if (abs(DX[ix]) > dmax) {
                idamax = i;
                dmax = abs(DX[ix]);
            }
            ix = ix + INCX;
        }
    }
    return idamax;
}


void DSWAP(int N, double* DX, int INCX, double* DY, int INCY) {
    if (N < 0) {
        return;
    }
    if (INCX == 1 && INCY == 1) {
        int m = N % 3;
        if (m != 0) {
            for(int i = 0; i < m; i++) {
                double dtemp = DX[i];
                DX[i] = DY[i];
                DY[i] = dtemp;
            }
            if (N < 3) {
                return;
            }
        }
        int mp1 = m;
        for(int i = mp1; i < N; i += 3) {
            double dtemp = DX[i];
            DX[i] = DY[i];
            DY[i] = dtemp;
            dtemp = DX[i+1];
            DX[i+1] = DY[i+1];
            DY[i+1] = dtemp;
            dtemp = DX[i+2];
            DX[i+2] = DY[i+2];
            DY[i+2] = dtemp;
        }
    }
    else {
        int ix = 0;
        int iy = 0;
        if (INCX < 0) {
            ix = (-N+1)*INCX;
        }
        if (INCY < 0) {
            iy = (-N+1)*INCY;
        }
        for(int i = 0; i < N; i++) {
            double dtemp = DX[ix];
            DX[ix] = DY[iy];
            DY[iy] = dtemp;
            ix = ix + INCX;
            iy = iy + INCY;
        }
    }
}

void DROTG(double* A, double* B, double* C, double* S) {
    //A -> r, B -> z
    double zero = 0.0;
    double one = 1.0;
    double safmax = 10e8;
    double safmin = 10e-8;

    double anorm = abs(*A);
    double bnorm = abs(*B);

    if (bnorm == zero) {
        *C = one;
        *S = zero;
        *B = zero;
    }
    else if (anorm == zero) {
        *C = zero;
        *S = one;
        *A = *B;
        *B = one;
    }
    else {
        double scl = fmin(safmax, fmax(fmax(safmin,anorm),bnorm));
        double sigma = 0.0;
        if (anorm > bnorm) {
            sigma = copysign(one,*A);
        }
        else {
            sigma = copysign(one,*B);
        }
        double r = sigma*(scl*sqrt(pow((*A/scl),2)+pow((*B/scl),2)));
        *C = *A/r;
        *S = *B/r;

        double z = 0.0;
        if (anorm > bnorm) {
            z = *S;
        }
        else if (*C != zero) {
            z = one/(*C);
        }
        else {
            z = one;
        }
        *A = r;
        *B = z;
    }
}

void DROT(int N, double* DX, int INCX, double* DY, int INCY, double* C, double* S) {
    if (N < 0) {
        return;
    }
    if (INCX == 1 && INCY == 1) {
        for(int i = 0; i < N; i++) {
            double dtemp = *C*DX[i]+*S*DY[i];
            DY[i] = *C*DY[i]-*S*DX[i];
            DX[i] = dtemp;
        }
    }
    else {
        int ix = 0;
        int iy = 0;
        if (INCX < 0) {
            ix = (-N+1)*INCX;
        }
        if (INCY < 0) {
            iy = (-N+1)*INCY;
        }
        for(int i = 0; i < N; i++) {
            double dtemp = *C*DX[ix] + *S*DY[iy];
            DY[iy] = *C*DY[iy] - *S*DX[ix];
            DX[ix] = dtemp;
            ix = ix + INCX;
            iy = iy + INCY;
        }
    }
}




int main(void) {
    int N = 4;
    double X[] = {1.0,2.0,4.0,4.0};
    double Y[] = {1.0,2.0,3.0,1.0};

    double a = 3.0;
    double* A = &a;
    double b = 3.0;
    double* B = &b;
    double* C = malloc(sizeof(double));
    double* S = malloc(sizeof(double));

    DROTG(A,B,C,S);
    printf("%f %f", *C, *S);
    printf("\n");
    DROT(N,X,1,Y,1,C,S);

    for(int i = 0; i < N; i++) {
        printf("%f ", X[i]);
    }
    printf("\n");
    for(int i = 0; i < N; i++) {
        printf("%f ", Y[i]);
    }
}