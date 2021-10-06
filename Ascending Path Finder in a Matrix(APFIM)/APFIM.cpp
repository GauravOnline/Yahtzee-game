#include <fstream>
#include <iostream>
#include <vector>

void buildMatrix(std::ifstream &, std::vector<std::vector<int>> &, int, int);
void printMatrix(std::vector<std::vector<int>> &, int, int);
void printMatrix(std::vector<std::vector<char>> &, int, int);
bool path_finder( std::vector<std::vector<int>> &, int &, int &, int &, std::vector<std::vector<char>> & );
bool checkRight( std::vector<std::vector<int>> &, int , int  ,std::vector<std::vector<char>> &  );
bool checkLeft( std::vector<std::vector<int>> &, int , int  , std::vector<std::vector<char>> &  );
bool checkDown( std::vector<std::vector<int>> &, int , int , std::vector<std::vector<char>> & );
bool checkUp( std::vector<std::vector<int>> &, int , int , std::vector<std::vector<char>> & );
bool noWayOut( int , int , std::vector<std::vector<char>> & );


/*
Name - Gaurav Shienhmar
Date - 08/10/2020

This program is about finding a continuous non-descending path of length entered by the user in a matrix
abstracted from the file input by the user. We will use various methods to move through the matrix keeping
in mind that a position can only be crossed once.And at the end, we return the path if there exists one..

*/
int main(){
    
    std::ifstream in;
    std::string fileName;
    std::cout<<"Which file would you like to process ? "<<std::endl;
    std::cin>>fileName;
    in.open(fileName);
    
    int rows, columns;
    in>>rows;
    in>>columns;
    std::vector<std::vector<int>> v;
    buildMatrix(in,v,rows,columns);
    printMatrix(v,rows,columns);
    
    std::vector<std::vector<char>> c;
    std::vector<char> cOneD;
    
     for(int j = 0; j <columns; j++ )
    {
        cOneD.push_back('-');
    }
    for(int i = 0; i < rows; i++ )
    {
        c.push_back(cOneD);
    }
    
    int  len;
    std::cout<<"Enter length of the sequence : ";
    std::cin>>len;
    int a = 0;
    int b = 0;
    
    if(len <= 0)
    {
        std::cout<<"Invalid length"<<std::endl;
    }
    
    else if(path_finder(v,a,b,len,c))
    {
        printMatrix(c,rows,columns);
    }  
    
    else
    {
        std::cout<<"Sorry. No path found\n";
    }
        
        return 0;
    
}
//input -> File named as in(by reference) which helps us get the integers and form a matrix with them.
//input -> vector v of type int(by reference) to store the matrix
//input ->  int rows that represents the number of rows matrix should have
//input -> int columns that represents the number of columns matrix should have
//output -> none
// This methods helps us get elements from the file line by line by storing them in a vectors. Later we will make
// vector of these vectors to represent the matrix by a 2D vector name v
void buildMatrix(std::ifstream &in, std::vector<std::vector<int>> &v, int rows, int columns)
{
    
    std::vector<int> vOneD;
    int element;
    if(in.is_open())
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                in>>element;
                vOneD.push_back(element);
            }
            
            v.push_back(vOneD);
            vOneD.clear();
        }
    }
    
    in.close();
}

//input -> v(by reference) that is a vector of vectors<int> and contains the matrix
//input -> rows of type int representing the number of rows matrix have
//input -> columns of type int representing the number of columns matrix have
//output -> none
//This method helps us print all the elements of the matrix
void printMatrix(std::vector<std::vector<int>> &v, int rows, int columns)
{
    
     for(int i = 0; i < rows ; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            std::cout<<v[i][j]<<"  ";
        }
        
        std::cout<<"\n";
    }
}

//input -> c(by reference) that is a vector of vectors<char> and contains the path matrix
//input -> rows of type int representing the number of rows matrix have
//input -> columns of type int representing the number of columns matrix have
//output -> none
//This method helps us print all the elements of the path matrix
void printMatrix(std::vector<std::vector<char>> &c, int rows, int columns)
{
    
    for(int i = 0; i < rows ; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            std::cout<<c[i][j]<<"  ";
        }
        
        std::cout<<"\n";
    }
}

//input -> v(by reference) that is a vector of vectors<int> and contains the matrix
//input -> i of type int(by reference) that represent the row index of the matrix
//input -> j of type int(by reference) that represent the column index of the matrix 
//input -> sequence of type inr(by reference) that would conatain a value which tells us how many more sequences are to be formed from now
//input -> c(by reference) that is a vector of vectors<char> and contains the path matrix
//output -> boolean which return true if a continuous path is formed or returns false if we can't make one
//It is a reccursive method which checks if a path exist from the current element, and if there exists, then it reduces 
//the sequence by one and assigns arrow at the current index of the path matrix in the direction of the next element from
//where it will call itself again to check for a path and so on.. If we could finally make sequence 0, means we found our
//desired path. Otherwise, no such continous non- descending path exists and we return false
bool path_finder( std::vector<std::vector<int>> &v, int &i, int &j, int &sequence, std::vector<std::vector<char>> &c )
{
    int rows = (int)v.size();
    int columns = (int)v[0].size();
    

    if( j >= columns || i >= rows)
    {
        return false;
    }
    
    if(checkRight(v,i,j,c))
    {
        sequence--;
        
        if(sequence == 0)
        {
            c[i][j] = '*';
        }
        else{
        c[i][j] = '>';
        }
        j++;
        
        if( path_finder(v,i,j,sequence,c))
        {
            return true;
        }
        
        else
        {
            j--;
            sequence++;
        }
    }
    
    if(checkDown(v,i,j,c))
    {
        sequence--;
        if(sequence == 0)
        {
            c[i][j] = '*';
        }
        
        else{
        c[i][j] = 'v';
        }
        i++;
        
        if( path_finder(v,i,j,sequence,c))
        {
            return true;
        }
        
        else
        {
            i --;
            sequence++;
        }
    }
    
    if(checkLeft(v,i,j,c))
    {
        sequence--;
        
        if(sequence == 0)
        {
            c[i][j] = '*';
        }
        else{
        c[i][j] = '<';
        }
        j--;
        
        if( path_finder(v,i,j,sequence,c))
        {
            return true;
        }
        
        else
        {
            j++;
            sequence++;
        }
    }
    
    if(checkUp(v,i,j,c))
    {
        sequence--;
        
        if(sequence == 0)
        {
            c[i][j] = '*';
        }
        else{
        c[i][j] = '^';
        }
        i--;
        
        if( path_finder(v,i,j,sequence,c))
        {
            return true;
        }
        
        else
        {
            i++;
            sequence++;
        
        }
    }
    
    c[i][j] = '-';
    
    if( sequence == 1)
    {
        c[i][j] = '*';
        return true;
    }
    
    if( sequence == 0)
    {
        return true;
    }
    
    if(noWayOut(i,j,c))
    {
        return false;
    }
    
    if( j == columns - 1 )
    {
        i++;
        j = 0;
    }
    else
    {
        j++;
        
    }

    
    return path_finder(v,i,j,sequence,c);
    
    
}

//input -> i of type int that represent the row index of the matrix
//input -> j of type int that represent the column index of the matrix 
//input -> c(by reference) that is a vector of vectors<char> and contains the path matrix
//output -> boolean true if there is no way out. 
//This method is basically called for the element which doesn't have any non-descending element around it. This method checkes if any
// neighbouring element is pointing to it or not so as to check that is it a part of an already exisiting chain or is it the starting element.
bool noWayOut( int i, int j, std::vector<std::vector<char>> &c )
{
    int rows = (int)c.size();
    int columns = (int)c[0].size();
    
    if( (j + 1) < columns && c[i][j + 1] == '<')
    {
        return true;
    }
    
    if( (i + 1) < rows && c[i + 1][j] == '^')
    {
        return true;
    }
    
    if( (j - 1) >=  0 && c[i][j - 1] == '>')
    {
        return true;
    }
    
    if( (i - 1) >= 0 && c[i - 1][j] == 'v')
    {
        return true;
    }
    
    return false;
}

//input -> v(by reference) that is a vector of vectors<int> and contains the matrix
//input -> i of type int(by reference) that represent the row index of the matrix
//input -> j of type int(by reference) that represent the column index of the matrix 
//input -> c(by reference) that is a vector of vectors<char> and contains the path matrix
//output -> bool true if desired element is available in the right of the current element
//This method return true if an element is found which has not been passed by earlier, and
// which is greater in value than the current element, in the right direction

bool checkRight( std::vector<std::vector<int>> &v, int i, int j, std::vector<std::vector<char>> &c  )
{
    int columns = (int)v[0].size();
    
    if( ((j + 1) < columns) && v[i][j] <= v[i][j + 1] && c[i][j + 1] == '-' )
    {
        return true;;
    }
    
    return false;
    
}

//input -> v(by reference) that is a vector of vectors<int> and contains the matrix
//input -> i of type int(by reference) that represent the row index of the matrix
//input -> j of type int(by reference) that represent the column index of the matrix 
//input -> c(by reference) that is a vector of vectors<char> and contains the path matrix
//output -> bool true if desired element is available down of the current element
//This method return true if an element is found which has not been passed by earlier, and
// which is greater in value than the current element, in the downward direction
bool checkDown( std::vector<std::vector<int>> &v, int i, int j, std::vector<std::vector<char>> &c )
{
    int rows = (int)v.size();
    
    if( ((i + 1) < rows) && v[i][j] <= v[i + 1][j] && c[i + 1][j] == '-')
    {
        return true;
    }
    
    return false;
    
}

//input -> v(by reference) that is a vector of vectors<int> and contains the matrix
//input -> i of type int(by reference) that represent the row index of the matrix
//input -> j of type int(by reference) that represent the column index of the matrix 
//input -> c(by reference) that is a vector of vectors<char> and contains the path matrix
//output -> bool true if desired element is available in the left of the current element
//This method return true if an element is found which has not been passed by earlier, and
// which is greater in value than the current element, in the left direction
bool checkLeft( std::vector<std::vector<int>> &v, int i, int j, std::vector<std::vector<char>> &c )
{
    if( ((j - 1) >= 0) && v[i][j] <= v[i][j - 1] && c[i][j - 1] == '-')
    {
        return true;;
    }
    
    return false;
    
}

//input -> v(by reference) that is a vector of vectors<int> and contains the matrix
//input -> i of type int(by reference) that represent the row index of the matrix
//input -> j of type int(by reference) that represent the column index of the matrix 
//input -> c(by reference) that is a vector of vectors<char> and contains the path matrix
//output -> bool true if desired element is available upward of the current element
//This method return true if an element is found which has not been passed by earlier, and
// which is greater in value than the current element, in the upward direction
bool checkUp( std::vector<std::vector<int>> &v, int i, int j, std::vector<std::vector<char>> &c) 
{
    if( ((i - 1) >= 0) && v[i][j] <= v[i - 1][j] && c[i - 1][j] == '-')
    {
        return true;
    }
    
    return false;
    
}
