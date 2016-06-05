#include <vector>

#ifndef GAUSS_H
#define GAUSS_H

typedef std::vector<std::vector<double> > vector_matrix;
typedef unsigned int u_int;

void row_echelon(vector_matrix &holder);
void reduced_row_echelon(vector_matrix &holder);
void singular_entries(vector_matrix &holder);
vector_matrix Gauss_Jordan(vector_matrix holder);

#endif
