#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 8    // number of data points for mean/std
#define NX 4   // samples for linear regression
#define MX 2   // features for linear regression
#define ITER 1000

void normal_equation() {
    double X[NX][MX] = {{1,2},{2,3},{3,4},{4,5}};
    double y[NX] = {3,5,7,9};
    double XtX[MX][MX] = {0};
    double Xty[MX] = {0};
    double theta[MX] = {0};

    #pragma omp parallel for collapse(2)
    for(int i=0;i<MX;i++)
        for(int j=0;j<MX;j++){
            double sum=0;
            for(int k=0;k<NX;k++)
                sum += X[k][i]*X[k][j];
            XtX[i][j] = sum;
        }

    #pragma omp parallel for
    for(int i=0;i<MX;i++){
        double sum=0;
        for(int k=0;k<NX;k++)
            sum += X[k][i]*y[k];
        Xty[i] = sum;
    }

    double det = XtX[0][0]*XtX[1][1] - XtX[0][1]*XtX[1][0];
    theta[0] = (Xty[0]*XtX[1][1] - Xty[1]*XtX[0][1])/det;
    theta[1] = (XtX[0][0]*Xty[1] - XtX[1][0]*Xty[0])/det;

    printf("Normal Equation Theta: %f %f\n", theta[0], theta[1]);
}

void mean_std() {
    double data[N] = {1,2,3,4,5,6,7,8};
    double sum=0, mean, sq_sum=0, stddev;

    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<N;i++)
        sum += data[i];
    mean = sum/N;

    #pragma omp parallel for reduction(+:sq_sum)
    for(int i=0;i<N;i++)
        sq_sum += (data[i]-mean)*(data[i]-mean);
    stddev = sqrt(sq_sum/N);

    printf("Mean = %f, StdDev = %f\n", mean, stddev);
}

void gradient_descent() {
    double X[NX][MX] = {{1,1},{1,2},{1,3},{1,4}}; // bias + feature
    double y[NX] = {6,5,7,10};
    double theta[MX] = {0,0};
    double alpha = 0.01;

    for(int iter=0; iter<ITER; iter++){
        double gradient[MX] = {0,0};

        #pragma omp parallel for
        for(int j=0;j<MX;j++){
            double sum=0;
            for(int i=0;i<NX;i++){
                double pred=0;
                for(int k=0;k<MX;k++)
                    pred += X[i][k]*theta[k];
                sum += (pred - y[i])*X[i][j];
            }
            gradient[j] = sum/NX;
        }

        #pragma omp parallel for
        for(int j=0;j<MX;j++)
            theta[j] -= alpha*gradient[j];
    }

    printf("Gradient Descent Theta: %f %f\n", theta[0], theta[1]);
}

int main() {
    int choice;
    printf("Choose operation:\n1. Normal Equation\n2. Mean & StdDev\n3. Gradient Descent\nEnter choice: ");
    scanf("%d",&choice);

    if(choice==1) normal_equation();
    else if(choice==2) mean_std();
    else if(choice==3) gradient_descent();
    else printf("Invalid choice\n");

    return 0;
}
