#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define hh_div_2m 1
#define delta_x 1

typedef struct {
  int rows;
  int cols;
  double complex *data;
} ComplexMatrix;

typedef struct {
  int size;
  double complex *data;
} ComplexVector;

ComplexMatrix *create_matrix(int rows, int cols) {
  ComplexMatrix *new_matrix = (ComplexMatrix *)malloc(sizeof(ComplexMatrix));
  if (new_matrix == NULL) {
    printf("Failed to allocate structure memory\n");
    exit(1);
  }
  new_matrix->rows = rows;
  new_matrix->cols = cols;
  new_matrix->data = (double complex *)calloc(rows * cols, sizeof(double complex));
  if (new_matrix->data == NULL) {
    printf("Failed to allocate data memory\n");
    free(new_matrix);
    exit(1);
  }

  return new_matrix;
}

ComplexVector *create_vector(int size) {
  ComplexVector *new_vector = (ComplexVector *)malloc(sizeof(ComplexVector));
  if (new_vector == NULL) {
    printf("Failed to allocate structure memory\n");
    exit(1);
  }
  new_vector->size = size;
  new_vector->data = (double complex *)calloc(size, sizeof(double complex));
  if (new_vector->data == NULL) {
    printf("Failed to allocate data memory\n");
    free(new_vector);
    exit(1);
  }
  return new_vector;
}

void free_Matrix(ComplexMatrix *m) {
  if (m->data != NULL) {
    free(m->data);
  }
  free(m);
}

void free_vector(ComplexVector *v) {
  if (v->data != NULL) {
    free(v->data);
  }
  free(v);
}

void set_matrix_element(ComplexMatrix *m, int row, int col, double complex data) {
  if (row < 0 || row > m->rows || col < 0 || col > m->cols) {
    printf("Value Error set_matrix\n");
    exit(1);
  }
  int k = row * m->cols + col;
  m->data[k] = data;
}

void set_vector_element(ComplexVector *v, int index, double complex data) {
  if(index < 0 || index > v->size) {
    printf("Value Error set_vector\n");
    exit(1);
  }
  v->data[index] = data;
}

ComplexMatrix *create_H(int size, ComplexVector *V, double con, double Delta_x) {
  
  ComplexMatrix *new_H = create_matrix(size, size);
  //対角成分をセット
  //対角成分へのアクセスはi行i列目で考えれば良い．
  for (int i = 0; i < size; i++) {
    double v_val = V->data[i];
    double diag_val = con * (2.0 + v_val * Delta_x * Delta_x);
    double off_diag = -con;

    set_matrix_element(new_H, i, i, diag_val);

    if (i > 0) {
      set_matrix_element(new_H, i, i-1, off_diag);
    }
    if (i < size - 1) {
      set_matrix_element(new_H, i, i+1, off_diag);
    }
  }
  return new_H;
}

double complex get_matrix_element(const ComplexMatrix *m, int row, int col) {
  if(row < 0 || row > m->rows || col < 0 || col > m->cols) {
    printf("Value Error get_matrix\n");
    exit(1);
  }
  int k = row * m->cols + col;
  double complex seq = m->data[k];
  return seq;
}

double complex inner_product(ComplexVector *q, ComplexVector *a) {
  if (q->size != a->size) {
    printf("Different size of Vector\n");
    exit(1);
  }
  double complex ans = 0;
  for (int i = 0; i < q->size; i++) {
    ans += a->data[i] * a->data[i];
  }
  return ans;
}

double complex norm(ComplexVector *u) {
  double complex ans = 0;
  for (int i = 0; i < u->size; i++) {
    ans += u->data[i] * u->data[i];
  }
  return sqrt(ans);
}

ComplexMatrix *mat_mult(ComplexMatrix *A, ComplexMatrix *B) {
  if (A->cols != B->rows) {
    printf("Different size of Matrix\n");
    exit(1);
  }
  ComplexMatrix *ans = create_matrix(A->rows, B->cols);
  for (int i = 0; i < ans->rows; i++) {
    for (int j = 0; j < ans->cols; j++) {
      for (int k = 0; k < A->cols; k++) {
        int a = i * A->cols + k;
        int b = k * B->cols + j;
        int c = i * ans->cols + j;

        ans->data[c] += A->data[a] * B->data[b];
      }
    }
  }
  return ans;
}

int main(void) {
  int N = 5;
  ComplexVector *V = create_vector(N-1);
  ComplexMatrix *H = create_H(N-1, V, hh_div_2m, delta_x);
  // 表示
/*
  for(int i = 0; i < N-1; i++) {
    for(int j = 0; j < N-1; j++) {
      double complex ans = get_matrix_element(H, i, j);
      if(j == N-1) {
        if(cimag(ans) <= 0) {
          printf("%.2f+%.2f\n", creal(ans), cimag(ans));
        }
        else {
          printf("%.2f%.2f\n", creal(ans), cimag(ans));
        }
      }
      else {
        if(cimag(ans) <= 0) {
          printf("%.2f+%.2f  ", creal(ans), cimag(ans));
        }
        else {
          printf("%.2f%.2f  ", creal(ans), cimag(ans));
        }
      }
    }
  }
*/
  // 表示．今は実部のみ表示．
  for(int i = 0; i < N-1; i++) {
    for(int j = 0; j < N-1; j++){
      double complex ans = get_matrix_element(H, i, j);
      if(j == N-2) {
        printf("%.2f\n", creal(ans));
      }
      else {
        printf("%.2f  ", creal(ans));
      }
    }
  }
  free_vector(V);
  free_Matrix(H);
  return 0;
}  
