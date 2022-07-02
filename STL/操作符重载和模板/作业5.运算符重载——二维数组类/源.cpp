#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
    // 在此处补充你的代码
private:
    int row, col;
    int* data;
public:
    Array2(int r=0,int c=0):row(r),col(c) 
    {
        data = new int[row * col];
    }
    virtual ~Array2() {}
    Array2(Array2& a)
    {
        row = a.row;
        col = a.col;
        delete[] data;
        data = new int[row * col];
        memcpy(data, a.data, sizeof(int) * row * col);
    }
    Array2& operator=(Array2 a)
    {
        row = a.row;
        col = a.col;
        delete[] data;
        data = new int[row * col];
        memcpy(data, a.data, sizeof(int) * row * col);
        return *this;
    }
    int* operator[](int i) //返回值视为指针，又可以用于索引
    {
        return data + i * col;
    }
    int& operator()(int i,int j) //用指针偏移完成索引
    {
        return *(data+i*col+j);
    }
};

int main() {
    Array2 a(3, 4);
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 4; j++)
            a[i][j] = i * 4 + j;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 4; j++) {
            cout << a(i, j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 4; j++) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}