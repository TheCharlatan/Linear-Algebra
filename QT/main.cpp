#include <cstdio>
#include <utility>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>

#include "Determinant.h"
#include "Gauss.h"


typedef std::vector<std::vector<double> > vector_matrix;
typedef unsigned int u_int;

class precision_number {
private:
 // enum char {0,1,2,3,4,5,6,7,8,9} number;
public:
  //Todo: Convert the string to an enumerated char array, then declare the overloaded operators... this is a lot of work, so it would be best to first code the rest of Gauss and then get started on your own bignum type.
};

void print_single(vector_matrix matrix)
{
    std::cout << '\n';
    for(u_int r=0; r < matrix.size(); r++)
    {
      for(u_int c=0; c<matrix[r].size(); c++)
      {
        std::cout << std::setprecision(3) << std::fixed <<  matrix[r][c];
        std::cout << " ";
      }
      std::cout<<"\n";
    }
}

//Construct the main matrix and store it in memory
class matrix {
private:
  std::string numberstring;
  std::stringstream stringstream;
  u_int columns,rows;
  double entry;
public:
  vector_matrix main_matrix;
  void new_matrix()
  {
    std::cout<<"\nPlease state the dimensions of the matrix, first the columns\n" << '\n';
    std::cin >> numberstring;
    stringstream << numberstring;
    stringstream >> columns;
    clear_strings();
    std::cout<<"\nNow the Rows  \n";
    std::cin >> numberstring;
    stringstream << numberstring;
    stringstream >> rows;
    clear_strings();
    std::cout << "Please input the coefficients column by column, row by row, use the enter key to confirm every entry." << '\n' << '\n';
    for(u_int r = 0; r < rows; r++)
    {
      main_matrix.push_back(std::vector<double>() );
      for(u_int c = 0; c < columns; c++)
      {
        std::cout << "column: " << c+1 << " Row: " << r+1 << '\n';
        std::cin >> numberstring;
        stringstream << numberstring;
        stringstream >> entry;
        clear_strings();
        main_matrix[r].push_back(entry);
        print_single(main_matrix);
      }
    }
  }

  void clear_strings()
  {
    stringstream.clear();
    stringstream.str("");
    numberstring.clear();
  }

  void clear_matrix()
  {
    main_matrix.clear();
    numberstring.clear();
    stringstream.str("");
    stringstream.clear();
  }
};

vector_matrix Inverse(vector_matrix holder)
{
  for(u_int r = 0;  r < holder.size(); r++)
  {
    for(u_int c = 0; c < holder.size();  c++)
    {
      if(r == c)
      {
        holder[r].push_back(1);
      }
      else
      {
        holder[r].push_back(0);
      }
    }
  }
  print_single(holder);
  holder =  Gauss_Jordan(holder);
  for(u_int r=0; r < holder.size();  r++)
  {
    for(u_int c = 0; c < holder.size(); c++)
    {
      holder[r].erase(holder[r].begin());
    }
  }
  print_single(holder);
  return holder;
}

vector_matrix Transpose(vector_matrix holder)
{
  vector_matrix temp_matrix = holder;
  for(u_int r = 0; r < holder.size(); r++)
  {
    for(u_int c=0; c < holder.size(); c++)
    {
      holder[r][c] = temp_matrix[c][r];
    }
  }
  print_single(holder);
  return holder;
}

vector_matrix Multiplication(vector_matrix a_matrix, vector_matrix b_matrix)
{
  vector_matrix holder;
  double sum;
  if (a_matrix[0].size() != b_matrix.size())
    return holder;
  for(u_int r = 0; r < a_matrix.size(); r++)
  {
    holder.push_back(std::vector<double>());
    for(u_int c = 0; c < b_matrix[0].size(); c++)
    {
      for(u_int i = 0; i < b_matrix.size();  i++)
      {
        sum = a_matrix[r][i] * b_matrix[i][c];
      }
      holder[r].push_back(sum);
    }
  }
  print_single(holder);
  return holder;
}

vector_matrix Sum(vector_matrix a_matrix, vector_matrix b_matrix)
{
  vector_matrix holder = a_matrix;

  if((a_matrix.size() != b_matrix.size()) || (a_matrix[0].size() != b_matrix[0].size()))
  {
    return holder;
  }

  for(u_int c = 0; c < holder.size(); c++)
  {
    for(u_int i=0; i < holder.size(); i++)
    {
      holder[c][i] = a_matrix[c][i] + b_matrix[c][i];
    }
  }
  return holder;
}

vector_matrix Factor(double factor, vector_matrix holder)
{
  for(u_int c = 0; c < holder.size(); c++)
  {
    for(u_int i=0; i < holder.size(); i++)
    {
      holder[c][i] *= factor;
    }
  }
  return holder;
}

vector_matrix Addition(double add, vector_matrix holder)
{
  for(u_int c = 0; c < holder.size(); c++)
  {
    for(u_int i=0; i < holder.size(); i++)
    {
      holder[c][i] += add;
    }
  }
  return holder;
}

struct menu_options
{
  std::string command;
  std::string name, name2;
  std::string options =
    " matrix = spawns a new matrix \n save [name] = saves previously generated matrix under given name\n print [name] = prints matrix with given name\n multiply [name] [name] = multiplies two matrices with given name\n determinant [name] = Gives the determinant of said matrix\n transpose [name] = Gives the transpose of the matrix\n invert [name] = Gives the inverse of the matrix\n solve [name] = Executes Gauss-Jordan on the matrix\n add [number] add a real number to all matrix entries \n factor [number] = multiply the matrix by a real number \n quit = Quits the programm\n";
  bool control = true;
  std::string save_query = "\nYou have successfully entered above matrix. Enter save and a name to commit it to memory, or enter matrix again to discard it.\n";
  std::stringstream sstream;
  double real;
};

void menu(std::map <std::string, vector_matrix> &matrix_holder, matrix &constructed_matrix, menu_options &option)
{
  option.command.clear();
  option.name.clear();
  option.name2.clear();
  std::cout << "<<";
  std::cin.reset();
  std::getline(std::cin, option.command);
  std::cout << " Is it actually going here?";
  if(option.command == "quit")
  {
     option.control = false;
     return;
  }

  else if(option.command == "help")
  {
    std::cout << option.options;
  }

  else if(option.command == "matrix")
  {
    constructed_matrix.clear_matrix();
    constructed_matrix.new_matrix();
    constructed_matrix.clear_strings();
    print_single(constructed_matrix.main_matrix);
    std::cout << option.save_query;
  }

  else if(option.command.substr(0,4) == "save")
  {
    if (constructed_matrix.main_matrix.empty())
    {
      return;
      std::cout << "First generate a new matrix!";
    }
    for(int c = 5; option.command[c] != '\0'; c++)
    {
      option.name += option.command.at(c);
    }
    matrix_holder.insert(std::make_pair(option.name, constructed_matrix.main_matrix));
    std::cout << "\n Matrix saved to: " << option.name << '\n';
    //print_single(matrix_holder.at(option.name));
  }

  else if(option.command.substr(0,5) == "print")
  {
    for(int c = 6; option.command[c] != '\0'; c++)
    {
      option.name += option.command.at(c);
    }
    print_single(matrix_holder.at(option.name));
  }

  else if(option.command.substr(0,5) == "solve")
  {
    for(int c = 6; option.command[c] != '\0'; c++)
    {
      option.name += option.command.at(c);
    }
    constructed_matrix.main_matrix = Gauss_Jordan(matrix_holder.at(option.name));
    print_single(constructed_matrix.main_matrix);
  }

  else if(option.command.substr(0,9) == "transpose")
  {
    for(int c = 10; option.command[c] != '\0'; c++)
    {
      option.name += option.command.at(c);
    }
    constructed_matrix.main_matrix = Transpose(matrix_holder.at(option.name));
    print_single(constructed_matrix.main_matrix);
  }

  else if(option.command.substr(0,7) == "inverse")
  {
    for(int c=8; option.command[c] != '\0'; c++)
    {
      option.name += option.command.at(c);
    }
    constructed_matrix.main_matrix = Inverse(matrix_holder.at(option.name));
    print_single(constructed_matrix.main_matrix);
  }

  else if(option.command.substr(0,11) == "determinant")
  {
    for(int c=12; option.command[c] != '\0'; c++)
    {
      option.name += option.command.at(c);
    }
    constructed_matrix.main_matrix = Determinant(matrix_holder.at(option.name));
    print_single(constructed_matrix.main_matrix);
  }

  else if(option.command.substr(0,8) == "multiply")
  {
    int c=9;
    while(option.command[c] != ' ')
    {
      option.name += option.command.at(c);
      c++;
    }
    c++;
    while(option.command[c] != '\0')
    {
      option.name2 += option.command.at(c);
      c++;
    }
    std::cout << option.name << '\n' <<  option.name2 << '\n';
    constructed_matrix.main_matrix = Multiplication(matrix_holder.at(option.name), matrix_holder.at(option.name2));
    print_single(constructed_matrix.main_matrix);
  }

  else if(option.command.substr(0,3) == "add")
  {
    int c=4;
    while(option.command[c] != ' ')
    {
      option.name += option.command.at(c);
      c++;
    }
    c++;
    while(option.command[c] != '\0')
    {
      option.name2 += option.command.at(c);
      c++;
    }
    std::cout << option.name << '\n' <<  option.name2 << '\n';
    option.sstream << option.name2;
    option.sstream >> option.real;
    constructed_matrix.main_matrix = Addition(option.real,matrix_holder.at(option.name));
    print_single(constructed_matrix.main_matrix);
  }

  else if(option.command.substr(0,3) == "factor")
  {
    int c=4;
    while(option.command[c] != ' ')
    {
      option.name += option.command.at(c);
      c++;
    }
    c++;
    while(option.command[c] != '\0')
    {
      option.name2 += option.command.at(c);
      c++;
    }
    std::cout << option.name << '\n' <<  option.name2 << '\n';
    option.sstream << option.name2;
    option.sstream >> option.real;
    constructed_matrix.main_matrix = Factor(option.real,matrix_holder.at(option.name));
    print_single(constructed_matrix.main_matrix);
  }

}

int main() {
  std::map <std::string, vector_matrix> matrix_holder; //create vector to hold the calculated matrices.
  matrix constructed_matrix;
  menu_options option;
  std::cout << "Welcome to the Matrix Calculator\n" << "Type help for a list of commands.\n";
  while(option.control)
  {
    menu(matrix_holder, constructed_matrix, option);
  }
  return 0;
}
