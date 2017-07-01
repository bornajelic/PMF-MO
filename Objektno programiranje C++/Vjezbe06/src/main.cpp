#include <iostream>
#include "Matrix.h"

using std::cout;
using std::endl;

int main()
{
    Matrix<2,3>  A{{1,2,3},{2,3,1}}, B({{-1,1,4},{0,0,3}});
    Matrix<3,1> x(3.0), y({{0},{1},{0}});
    Matrix<2,1> z, res{{48},{45}};
    z.zero();

    Matrix<2,3> M;
    M.eye();

    z = (2*A-M+B*3)*(x-3*y); // koliko privremenih objekta je ovdje konstruirano?

    z -= res;
    if(z) cout << "o.k.\n";
    else  cout << "pogresno!\n";
  return 0;
}
