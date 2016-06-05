#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#ifndef DETERMINANT_H
#define DETERMINANT_H

int factor(int faca);
void vector_permutation (std::vector<int> &orig, std::vector<int> &perm, std::vector<std::vector<int> > &permutations);
void list_permutationsi (int key, std::vector<std::pair<int, std::vector<int> > > &sign_pairing);
std::vector<std::vector<double> > Determinant (std::vector<std::vector<double> >  holder);

#endif
