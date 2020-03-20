/*
** EPITECH PROJECT, 2019
** Work
** File description:
** main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>


class entry {
    public:
        entry()  { }
        ~entry()  { }
    
        int x;
        int y;
        int p;
};

int n;
double x;
double y;
std::string fileName;
std::vector<std::string> file;
std::vector<entry> entries;

bool checkSyntaxInt(char *av)
{
    for (int i = 0; av[i]; i++)
        if (av[i] < '0' || av[i] > '9')
            return (false);
    return (true);
}

bool checkSyntaxDouble(char *av)
{
    for (int i = 0; av[i]; i++)
        if (av[i] != '.' && av[i] < '0' && av[i] > '9')
            return (false);
    return (true);
}

int factorial(int n)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

class bezier
{
    public:
        bezier(int size, std::string file, double x, double y): _x(x), _y(y), _file(file), _size(size)
        {
            try
            {
                if (size <= 0)
                    exit(84);
                _x = _x / (size - 1);
                _y = _y / (size - 1);
                if (_x < 0 || _x > size - 2 || _y < 0 || _y > _size - 2)
                    std::exit(84);
            }
            catch(const std::exception& e)
            {
                std::exit(84);
            }
            
        }
        ~bezier()
        {

        }
        double getx() { return _x; }
        double gety() { return _y; }
        int getsize() { return _size - 1; }
        std::vector<std::vector<int>>   getGrid() { return (_grid); }
        int buildGrid(std::vector<entry> p) {
            for (int i = 0; i < _size; i++) {
                std::vector<int>    line;
                for (int j = 0; j < _size; j++) {
                    line.push_back(0);
                }
                _grid.push_back(line);
            }
            for (entry single : p)
            {
                if (single.x < 0 or single.x > _size - 1 or single.y < 0 or single.y > _size - 1)
                    std::exit(84);
                _grid[single.y][single.x] = single.p;
            }
        }
    private:
        double         _x;
        double         _y;
        std::string _file;
        int         _size;
        std::vector<std::vector<int>>   _grid;
};

double bernstein_polynomial(int n, int k, double p)
{
	int b = int(factorial(n) / (factorial(k) * factorial(n - k)));
	double pk;
    if (k != 0)
        pk = std::pow(p, k);
    else
        pk = 1;
	double pnk;
    if ((n - k) != 0)
        pnk = std::pow((1 - p), (n - k));
    else
        pnk = 1;
	return (b * pk * pnk);
}

double bezier_surface(double x, double y, std::vector<std::vector<int>> grid, int degree)
{
    double pollution = 0;

    for (int i = 0; i < degree + 1; i++) {
        for (int j = 0; j < degree + 1; j++) {
            double v = bernstein_polynomial(degree, i, y);
            v *= bernstein_polynomial(degree, j, x);
            v *= grid[i][j];
            pollution += v;
        }
    }
    return (pollution);
}

int main(int ac, char **av)
{
    try {
        // Help
        if (ac >= 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
            std::cout << "USAGE" << std::endl;
            std::cout << "\t" << av[0] << " n file x y" << std::endl;
            std::cout << "DESCRIPTION" << std::endl;
            std::cout << "\tn\tnumber of points on the grid axis" << std::endl;
            std::cout << "\tfile\tcsv file containing the data points x;y;p" << std::endl;
            std::cout << "\tx\tabscissa of the point whose pollution level we want to know" << std::endl;
            std::cout << "\ty\tordinate of the point whose pollution level we want to know" << std::endl;
            return (0);
        }
        // ErrorHandling
        if (ac != 5 || !checkSyntaxInt(av[1]) || !checkSyntaxDouble(av[3]) || !checkSyntaxDouble(av[4])) {
            std::cerr << "Bad usage." << std::endl;
            return (84);
        }
        // Parsing
        n = std::atoi(av[1]);
        x = std::atof(av[3]);
        y = std::atof(av[4]);
        fileName = std::string(av[2]);
        std::ifstream myfile(fileName);
        if (myfile.fail()) {
            std::cerr << "Bad input file." << std::endl;
            return (84);
        }
        std::string	line;
        while (getline(myfile, line))
            file.push_back(line);
        for (int i = 0; i < file.size(); i++) {
            if (file[i].find(';') == std::string::npos) {
                std::cerr << "Bad input file." << std::endl;
                return (84);
            }
            std::vector<std::string> parts = split(file[i], ';');
            if (parts.size() != 3) {
                std::cerr << "Bad input file." << std::endl;
                return (84);
            }
            entry entry;
            for (int i = 0; i < parts.size(); i++) {
                if (checkSyntaxInt((char*)parts[i].c_str()) == false) {
                    std::cerr << "Bad syntax file." << std::endl;
                    return (84);
                }
                switch (i) {
                    case 0:
                    entry.x = std::atoi(parts[i].c_str());
                    break;
                    case 1:
                    entry.y = std::atoi(parts[i].c_str());
                    break;
                    case 2:
                    entry.p = std::atoi(parts[i].c_str());
                    break;
                }
            }
            entries.push_back(entry);
        }
        // Engine
        if (x < 0 || entries.size() == 0) {
                std::cerr << "Bad input." << std::endl;
                return (84);
        }
        // Display
        bezier m(n, "", x, y);
        m.buildGrid(entries);
        double coef = bezier_surface(m.getx(), m.gety(), m.getGrid(), m.getsize());
        printf("%.2f\n", coef);
    } catch (...) { return (84); }
    return (0);
}