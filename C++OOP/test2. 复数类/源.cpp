#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r, i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
    Complex(const char *s)
    {
        string c(s);
        int pos = c.find('+');
        int len1 = pos, len2 = c.length() - 1 - pos;
        r = atof(c.substr(0, len1).c_str());
        i = atof(c.substr(pos + 1, pos + 1 + len2).c_str());
    }
    Complex() {}
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}