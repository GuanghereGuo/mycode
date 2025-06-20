#include <array>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>

#define N 11
#define c 299792.458

double X[N], A[N], B[N], C[N], T[N];

void scanf1(double A[N], int n) {
    for (int i = 0; i < n; i++) {
        scanf("%lf", &A[i]);
    }
}

void print1(double A[N], int n) {
    int i, tmp;
    double a;
    for (i = 0; i < n - 1; i++) {
        tmp = (int)(A[i] * 10000);
        a = (double)tmp / 10000.0;
        printf("%.4lf,", a);
    }
    tmp = (int)(A[n - 1] * 10000);
    a = (double)tmp / 10000.0;
    printf("%.4lf", a);
}

void print2(double A[N][N], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) printf("%.7lf ", A[i][j]);
        printf("\n");
    }
}

int GetCoFactor(double dest[N][N], double src[N][N], int row, int col, int n) {
    int i, j;
    int colCount = 0, rowCount = 0;
    for (i = 0; i < n; i++) {
        if (i != row) {
            colCount = 0;
            for (j = 0; j < n; j++)
                if (j != col) {
                    dest[rowCount][colCount] = src[i][j];
                    colCount++;
                }
            rowCount++;
        }
    }
    return 1;
}

double CalcDeterminant(double mat[N][N], int n) {
    int i, j;
    double det = 0;
    double minor[N][N];

    if (n == 1) return mat[0][0];
    for (i = 0; i < n; i++) {
        GetCoFactor(minor, mat, 0, i, n);
        det += (i % 2 == 1 ? -1.0 : 1.0) * mat[0][i] *
               CalcDeterminant(minor, n - 1);
    }
    return det;
}

void MatrixInversion(double J[N][N], int n) {
    int i, j;
    double det, temp[N][N], minor[N][N];
    double inv[N][N];

    det = 1.0 / CalcDeterminant(J, n);
    for (j = 0; j < n; j++)
        for (i = 0; i < n; i++) {
            GetCoFactor(minor, J, j, i, n);
            inv[i][j] = det * CalcDeterminant(minor, n - 1);
            if ((i + j) % 2 == 1) inv[i][j] = -inv[i][j];
        }
    for (j = 0; j < n; j++)
        for (i = 0; i < n; i++) J[i][j] = inv[i][j];
}

void CalcF(double F[N], double X[N], int n) {
    double f;
    int i;
    for (i = 0; i < n; i++) {
        switch (i + 1) {
            case 1:
                f = X[0] * X[0] + X[1] * X[1] - 2 * X[0] - X[2] + 1;
                break;
            case 2:
                f = X[0] * X[1] * X[1] - X[0] - 3 * X[1] + X[1] * X[2] + 2;
                break;
            case 3:
                f = X[0] * X[2] * X[2] - 3 * X[2] + X[1] * X[2] * X[2] +
                    X[0] * X[1];
                break;
        }
        F[i] = f;
    }
}

void CalcF_re(double F[N], double X[N], int n) {
    double f;
    int i;
    for (i = 0; i < n; i++) {
        switch (i + 1) {
            case 1:
                f = (X[0] - A[0]) * (X[0] - A[0]) +
                    (X[1] - B[0]) * (X[1] - B[0]) +
                    (X[2] - C[0]) * (X[2] - C[0]) -
                    (c * (T[0] - X[3])) * (c * (T[0] - X[3]));
                break;
            case 2:
                f = (X[0] - A[1]) * (X[0] - A[1]) +
                    (X[1] - B[1]) * (X[1] - B[1]) +
                    (X[2] - C[1]) * (X[2] - C[1]) -
                    (c * (T[1] - X[3])) * (c * (T[1] - X[3]));
                break;
            case 3:
                f = (X[0] - A[2]) * (X[0] - A[2]) +
                    (X[1] - B[2]) * (X[1] - B[2]) +
                    (X[2] - C[2]) * (X[2] - C[2]) -
                    (c * (T[2] - X[3])) * (c * (T[2] - X[3]));
                break;
            case 4:
                f = (X[0] - A[3]) * (X[0] - A[3]) +
                    (X[1] - B[3]) * (X[1] - B[3]) +
                    (X[2] - C[3]) * (X[2] - C[3]) -
                    (c * (T[3] - X[3])) * (c * (T[3] - X[3]));
        }
        F[i] = f;
    }
}

void CalcJ(double J[N][N], double X[N], int n) {
    double f;
    int i, j;
    for (i = 0; i < n; i++) switch (i + 1) {
            case 1:
                for (j = 0; j < n; j++) {
                    switch (j + 1) {
                        case 1:
                            f = 2 * X[0] - 2;
                            break;
                        case 2:
                            f = 2 * X[1];
                            break;
                        case 3:
                            f = -1;
                            break;
                    }
                    J[i][j] = f;
                }
                break;
            case 2:
                for (j = 0; j < n; j++) {
                    switch (j + 1) {
                        case 1:
                            f = X[1] * X[1] - 1;
                            break;
                        case 2:
                            f = 2 * X[0] * X[1] - 3 + X[2];
                            break;
                        case 3:
                            f = X[1];
                            break;
                    }
                    J[i][j] = f;
                }
                break;
            case 3:
                for (j = 0; j < n; j++) {
                    switch (j + 1) {
                        case 1:
                            f = X[2] * X[2] + X[1];
                            break;
                        case 2:
                            f = X[2] * X[2] + X[0];
                            break;
                        case 3:
                            f = 2 * X[0] * X[2] - 3 + 2 * X[1] * X[2];
                            break;
                    }
                    J[i][j] = f;
                }
                break;
        }
}

void CalcJ_re(double J[N][N], double X[N], int n) {
    double f;
    int i, j;
    for (i = 0; i < n; i++) switch (i + 1) {
            case 1:
                for (j = 0; j < n; j++) {
                    switch (j + 1) {
                        case 1:
                            f = 2 * (X[0] - A[0]);
                            break;
                        case 2:
                            f = 2 * (X[1] - B[0]);
                            break;
                        case 3:
                            f = 2 * (X[2] - C[0]);
                            break;
                        case 4:
                            f = 2 * c * c * (T[0] - X[3]);
                            break;
                    }
                    J[i][j] = f;
                }
                break;
            case 2:
                for (j = 0; j < n; j++) {
                    switch (j + 1) {
                        case 1:
                            f = 2 * (X[0] - A[1]);
                            break;
                        case 2:
                            f = 2 * (X[1] - B[1]);
                            break;
                        case 3:
                            f = 2 * (X[2] - C[1]);
                            break;
                        case 4:
                            f = 2 * c * c * (T[1] - X[3]);
                            break;
                    }
                    J[i][j] = f;
                }
                break;
            case 3:
                for (j = 0; j < n; j++) {
                    switch (j + 1) {
                        case 1:
                            f = 2 * (X[0] - A[2]);
                            break;
                        case 2:
                            f = 2 * (X[1] - B[2]);
                            break;
                        case 3:
                            f = 2 * (X[2] - C[2]);
                            break;
                        case 4:
                            f = 2 * c * c * (T[2] - X[3]);
                            break;
                    }
                    J[i][j] = f;
                }
                break;
            case 4:
                for (j = 0; j < n; j++) {
                    switch (j + 1) {
                        case 1:
                            f = 2 * (X[0] - A[3]);
                            break;
                        case 2:
                            f = 2 * (X[1] - B[3]);
                            break;
                        case 3:
                            f = 2 * (X[2] - C[3]);
                            break;
                        case 4:
                            f = 2 * c * c * (T[3] - X[3]);
                            break;
                    }
                    J[i][j] = f;
                }
                break;
        }
}

void CalcJF(double R[N], double J[N][N], double F[N], int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        R[i] = 0.0;
        for (j = 0; j < n; j++) R[i] = R[i] + J[i][j] * F[j];
    }
}

void CalcX(double X[N], double X0[N], double R[N], int n) {
    int i;
    for (i = 0; i < n; i++) X[i] = X0[i] - R[i];
}

void AequB(double A[N], double B[N], int n) {
    int i;
    for (i = 0; i < n; i++) A[i] = B[i];
}

double Ferror(double F[N], int n) {
    double m = 0;
    int i;
    for (i = 0; i < n; i++) {
        double t = abs(F[i]);
        if (m < t) m = t;
    }
    return m;
}

void mvNewtons(double X0[N], int n, double e) {
    int k;
    double J[N][N], Y[N][N];
    double X[N], R[N], F[N];

    for (k = 1; k <= 20; k++) {
        CalcF_re(F, X0, n);

        CalcJ_re(J, X0, n);
        MatrixInversion(J, n);
        CalcJF(R, J, F, n);
        CalcX(X, X0, R, n);
        AequB(X0, X, n);
        if (Ferror(F, n) < e) break;
    }
}

int main() {
    int n = 4;
    scanf("%lf %lf %lf", &A[0], &B[0], &C[0]);
    scanf("%lf %lf %lf", &A[1], &B[1], &C[1]);
    scanf("%lf %lf %lf", &A[2], &B[2], &C[2]);
    scanf("%lf %lf %lf", &A[3], &B[3], &C[3]);
    scanf1(T, n);
    scanf1(X, n);
    mvNewtons(X, n, 1e-6);
    print1(X, 3);
    return 0;
}