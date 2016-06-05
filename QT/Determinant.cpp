#include "Determinant.h"

int factorial(int faca)
{
  if (faca > 1)
   return (faca * factorial(faca-1));
  else
    return 1;
}

void vector_permutation(std::vector<int> &orig, std::vector<int> &perm, std::vector<std::vector<int> > &permutations) //The last argument is used for overall progress storage.
{
  std::vector<int> orig2, perm2;
  if (orig.empty())
  {
    permutations.push_back(perm);
    return;
  }
  for(unsigned int i=0; i<orig.size();i++)
  {
    orig2.clear();
    perm2.clear();
    orig2 = orig;
    orig2.erase(orig2.begin()+i);
    perm2 = perm;
    perm2.push_back(orig[i]);
    vector_permutation(orig2,perm2, permutations);
  }
}

void list_permuatations(int key, std::vector<std::pair<int, std::vector<int> > > &sign_pairing) //Take one argument for the permutation origin, thus if key=2, then the function returns the signned permutations of (1,2).
{
  std::vector < std::vector <int> > permutations; //A vector to store the overall progress
  std::vector <int> vorig, vperm; //two vectors that hold the swapped permutations
  for (int c=1; c<=key; c++)
  {
    vorig.push_back(c); //fill the original vector with whatever key is provided. If key=3, then vorig now holds (1,2,3).
  }
  vector_permutation(vorig,vperm, permutations); //then execute the permutation function
 /* for (int c=0; c< permutations.size(); c++) //print the result
  {
    for(int i=0; i < key; i++)
    {
      std::cout << permutations[c][i];
    }
    std::cout << '\n';
  }*/
  for(unsigned int c=0; c<permutations.size(); c++)
  {
    if(c%4==0 || (c+1)%4==0) //every second permutation has a different sign from its last in this order.
      sign_pairing.push_back(std::make_pair(1,permutations[c]));
    else
      sign_pairing.push_back(std::make_pair(-1,permutations[c]));
  }
  /*for (int c=0; c< sign_pairing.size(); c++) //Print all permutations with corresponding signs.
  {
    std::cout << sign_pairing[c].first << ' ';
    for (int i=0; i<key; i++)
    {
      std::cout << sign_pairing[c].second[i];
    }
    std::cout << '\n';
  }*/
}

std::vector<std::vector<double> > Determinant(std::vector<std::vector<double> > holder)
{
  std::vector<std::vector<double> > det;
  det.push_back(std::vector<double> ());
  det[0].push_back(0);
  double product=1;
  if(holder[0].size() != holder.size()) //Only square matrices may be processed.
    return det;
  std::vector<std::pair<int, std::vector<int> > > ordered_permutations;
  list_permuatations(holder.size(), ordered_permutations); //grab all permutations of the particular matrix.
  for(int c=0; c < factorial(holder.size()); c++)
  {
    for(unsigned int i=0; i < holder.size(); i++)
    {
      product *= holder[ordered_permutations[c].second[i]-1][i]; //line produces the segfault
    }
    product *= ordered_permutations[c].first;
    det[0][0] += product;
    product=1;
  }
  std::cout << "Determinant: " << det[0][0] << '\n';
  return det;
}
