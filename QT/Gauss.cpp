#include "Gauss.h"

void row_echelon(vector_matrix &holder) //Holder is the variable name of the matrix
{
  double row_eliminator = 0;
  for(u_int r = 0; r < holder.size(); r++) //Main Loop to iterate through the matrix top to bottom.
  {
    for(u_int c = 0; c < holder[r].size(); c++) //Inner Main Loop to first iterate through the entries by column
    {
      if(holder[r][c] != 0) //And paging for a non-zero entry.
      {
        for(u_int nonzero_rowiterator = r+1; nonzero_rowiterator < holder.size();  nonzero_rowiterator++) //Once nonzero has been found, all entries bellow have to be zero, outer iterator is through the rows again.
        {
          if(holder[nonzero_rowiterator][c] != 0) //
          {
            row_eliminator = holder[nonzero_rowiterator][c]/holder[r][c]; //Use this as the elimination varibale for the entire row.
            for(u_int nonzero_columniterator = c; nonzero_columniterator < holder[r].size(); nonzero_columniterator++)
            {
              holder[nonzero_rowiterator][nonzero_columniterator] = holder[nonzero_rowiterator][nonzero_columniterator] - row_eliminator * holder[r][nonzero_columniterator];//eliminate the entry with the found variable, do so for the entire row.
            }
          }
        }
        break;
      }
    }
  }
}

void reduced_row_echelon(vector_matrix& holder) //holder is the variable name of the matrix
{
  double column_eliminator = 0;
  for(u_int r = holder.size()-1; r > 0; r--) //Main Loop to iterate through the matrix bottom to top.
  {
    for(u_int c = 0; c < holder[r].size(); c++) //Inner Main Loop to first iterate through the entries by column left to right.
    {
      if(holder[r][c] != 0) //And paging for a non-zero entry.
      {
        for(int nonzero_rowiterator = r-1; nonzero_rowiterator >= 0;  nonzero_rowiterator--) //Once nonzero has been found, all entries above have to be zero, outer iterator goes through the rows again.
        {
          if(holder[nonzero_rowiterator][c] != 0) //
          {
              column_eliminator = holder[nonzero_rowiterator][c]/holder[r][c];
              for(u_int nonzero_columniterator = 0; nonzero_columniterator < holder[r].size(); nonzero_columniterator++)
              {
                holder[nonzero_rowiterator][nonzero_columniterator] = holder[nonzero_rowiterator][nonzero_columniterator] - column_eliminator * holder[r][nonzero_columniterator]; //eliminates entries above the pivots
              }
          }
        }
        break;
      }
    }
  }
}

void singular_entries(vector_matrix &holder)
{
  double column_eliminator = 0;
  for(u_int r = 0; r < holder.size(); r++)
  {
    for (u_int c = 0; c < holder[r].size(); c++)
    {
      if ((holder[r][c] > 0) || (holder[r][c] < 0))
      {
        column_eliminator = 1/holder[r][c];
        for (u_int column = 0; column < holder[r].size(); column++)
        {
          holder[r][column] *= column_eliminator;
        }
        break;
      }
    }
  }
}

vector_matrix Gauss_Jordan(vector_matrix holder)
{
  row_echelon(holder);
  reduced_row_echelon(holder); //seems to cause segfault
  singular_entries(holder);
  return holder;
}


