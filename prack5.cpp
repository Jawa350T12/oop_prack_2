#include <iostream>
#include <fstream>
#include <typeinfo>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <random>
#include <cmath>

using namespace std;

class Exception: public std::exception
{
protected:
//сообщение об ошибке
    char* str;
public:
    Exception(const char* s){
        str = new char[strlen(s) + 1];
        //strcpy_s(str, strlen(s) + 1, s);
    }
    Exception(const Exception& e){
        str = new char[strlen(e.str) + 1];
        //strcpy_s(str, strlen(e.str) + 1, e.str);
    }
    virtual ~Exception(){
        delete[] str;
    }
    virtual void print() const {
        cout << "Exception: " << str << "; " << what() << "\n";
    }

    virtual const char* what() const throw() {
        return str;
    }
};
class InvalidOperation : public Exception {
public:
    InvalidOperation(const char* inpStr) : Exception(inpStr) {}

    void print() const {
        cout << "InvalidOperation: " << str << "; " << what() << "\n";
    }
};

class IndexOutOfBounds : public Exception {
private:
    int row_;
    int column_;

public:
    IndexOutOfBounds(const char* inpStr, int inpRow, int inpColumn)
        : Exception(inpStr), row_(inpRow), column_(inpColumn) {}

    void print() const {
        cout << "IndexOutOfBounds: " << str << ": row = " << row_ << ", column = " << column_ << "; " << what() << "\n";
    }
};

class WrongSize : public Exception {
protected:
    int height_;
    int width_;

public:
    WrongSize(const char* inpStr, int inpHeight, int inpWidth)
        : Exception(inpStr), height_(inpHeight), width_(inpWidth) {}

    int getHeight() const { return height_; }
    int getWidth() const { return width_; }

    void print() const {
        cout << "WrongSize: " << str << ": height = " << height_ << ", width = " << width_ << "; " << what() << "\n";
    }
};

class NonPositiveSize : public WrongSize {
public:
    NonPositiveSize(const char* inpStr, int inpHeight, int inpWidth)
        : WrongSize(inpStr, inpHeight, inpWidth) {}

    void print() const {
        cout << "NonPositiveSize: " << str << ": height = " << getHeight() << ", width = " << getWidth() << "; " << what() << "\n";
    }
};

class TooLargeSize : public WrongSize {
public:
    TooLargeSize(const char* inpStr, int inpHeight, int inpWidth)
        : WrongSize(inpStr, inpHeight, inpWidth) {}

    void print() const {
        cout << "TooLargeSize: " << str << ": height = " << getHeight() << ", width = " << getWidth() << "; " << what() << "\n";
    }
};        res.print();


class ElementNotFoundException : public Exception {
public:
    ElementNotFoundException(const char* inpStr) : Exception(inpStr) {}

    void print() const {
        cout << "ElementNotFoundException: " << str << "; " << what() << "\n";
    }
};


template <typename T>
class BaseMatrix
{
protected:
    T** ptr;
    int height;
    int width;
public:
    BaseMatrix(int Height = 2, int Width = 2) {
        if (Height <= 0 || Width <= 0) throw NonPositiveSize("Matrix size invalid (non-positive)", Height, Width);
        if (Height > 10000 || Width > 10000) throw TooLargeSize("Matrix size invalid (too large)", Height, Width);
        height = Height;
        width = Width;
        ptr = new T * [height];
        for (int i = 0; i < height; i++) {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++) {
                ptr[i][j] = T();
            }
        }
    }
    BaseMatrix(const BaseMatrix& M) {
        height = M.height;
        width = M.width;
        ptr = new T * [height];
        for (int i = 0; i < height; i++) {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++) {
                ptr[i][j] = M.ptr[i][j];
            }
        }
    }

    BaseMatrix(T** inp, int h, int w) {
        if (inp == NULL || inp[0] == NULL) throw NonPositiveSize("got NULL pointer", 0, 0);
        if (h <= 0 || w <= 0)  throw NonPositiveSize("Invalid object size", h, w);
        height = h;
        width = w;
        ptr = new T * [height];
        for (int i = 0; i < height; i++) {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++) {
                ptr[i][j] = inp[i][j];
            }
        }
    }

    virtual ~BaseMatrix() {
        if (ptr!= NULL) {
            for (int i = 0; i < height; i++) {
                delete[] ptr[i];
            }
            delete[] ptr;
            ptr = NULL;
        }
    }
    virtual void print(const char* sep = " ") {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << ptr[i][j] << sep;
            }
            cout << "\n";
        }
    }
    T& operator()(int row, int column) {
        if (row < 0 || column < 0 || row >= height || column >= width) {
            throw IndexOutOfBounds("Index out of bounds", row, column);
        }
        return ptr[row][column];
    }
    BaseMatrix& operator=(BaseMatrix& M) {
        if (ptr!= NULL) {
            for (int i = 0; i < height; i++) {
                delete[] ptr[i];
            }
            delete[] ptr;
            ptr = NULL;
        }
        height = M.height;
        width = M.width;
        ptr = new T * [height];
        for (int i = 0; i < height; i++) {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++) {
                ptr[i][j] = M.ptr[i][j];
            }
        }
        return *this;
    }
    BaseMatrix operator+(BaseMatrix& M) {
        if (height!= M.height || width!= M.width) throw InvalidOperation("Can't add up matricies of different sizes");
            BaseMatrix res = BaseMatrix(height, width);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) res.ptr[i][j] = ptr[i][j] + M.ptr[i][j];
        }

        return res;
    }
    T tr() {
        if (width!= height) throw InvalidOperation("Can't calculate trace of a non-square matrix");
        T sum = T();
        for (int i = 0; i < height; i++) {
            sum += ptr[i][i];
        }
        return sum;
    }
    template <typename T1>
    friend ostream& operator<<(ostream& s, const BaseMatrix<T1>& M);

    template <typename T1>
    friend istream& operator>>(istream& s, BaseMatrix<T1>& M);
};
    template <typename T>
ostream& operator<<(ostream& s, const BaseMatrix<T>& M) {
    if (typeid(s) == typeid(ofstream)) {
        s << M.height << " " << M.width << " ";
        for (int i = 0; i < M.height; ++i) {
            for (int j = 0; j < M.width; ++j) {
                s << M.ptr[i][j] << " ";
            }
        }
        s << "\n";
        return s;
    }
    for (int i = 0; i < M.height; ++i) {
        for (int j = 0; j < M.width; ++j) {
            s << M.ptr[i][j] << " ";
        }
        s << "\n";
    }
    return s;
}
    template <typename T>
istream& operator>>(istream& s, BaseMatrix<T>& M) {
    if (typeid(s) == typeid(ifstream)) {
        int h, w;
        s >> h >> w;
        if (M.height!= h || M.width!= w) {
            for (int i = 0; i < M.height; i++) {
                delete[] M.ptr[i];
            }
            delete[] M.ptr;
            M.height = h;
            M.width = w;
            M.ptr = new T * [h];
            for (int i = 0; i < h; i++) {
                M.ptr[i] = new T[w];
            }
        }
    }
    for (int i = 0; i < M.height; i++) {
        for (int j = 0; j < M.width; j++) {
            s >> M.ptr[i][j];
        }
    }
    return s;
}
class Array {
private:
    int size_;
    pair<int, int>* data_;

public:
    Array(int size) : size_(size) {
        data_ = new pair<int, int>[size];
    }

    ~Array() {
        delete[] data_;
    }

    void set(int index, pair<int, int> value) {
        data_[index] = value;
    }

    pair<int, int> get(int index) {
        return data_[index];
    }

    int size() {
        return size_;
    }
};
template <typename T>
class Proizvol : public BaseMatrix<T>
{
public:
    Proizvol(int height = 2, int width = 2) : BaseMatrix<T>(height, width) {}
    Proizvol(const Proizvol<T>& other) : BaseMatrix<T>(other) {}
    Proizvol(const BaseMatrix<T>& other) : BaseMatrix<T>(other) {}
    Proizvol(T** ptr, int height, int width) : BaseMatrix<T>(ptr, height, width) {}
    ~Proizvol(){}

    void fill_arr(){
        for (int i = 0; i < BaseMatrix<T>::height; i++){
            for (int j = 0; j < BaseMatrix<T>::width; j++){
                BaseMatrix<T>::ptr[i][j] = rand()%(100-0+1)+0;
            }
        }
    }
    bool isNil(){
        int c = 0;
        while (c<100){
            
        }
    }
};

int main(){
    try {
        Proizvol<double> invalidMatrix(-1, 2); // throws NonPositiveSize
    } catch (const NonPositiveSize& e) {
        e.print();
    }

    try {
        Proizvol<double> tooLargeMatrix(10001, 10001); // throws TooLargeSize
    } catch (const TooLargeSize& e) {
        e.print();
    }

    try {
        Proizvol<double> matrix(2, 2);
        matrix(5, 5) = 10.0; // throws IndexOutOfBounds
    } catch (const IndexOutOfBounds& e) {
        e.print();
    }

    try {
        Proizvol<double> matrix1(2, 2);
        Proizvol<double> matrix2(3, 3);
        matrix1 + matrix2; // throws InvalidOperation
    } catch (const InvalidOperation& e) {
        e.print();
    }
    cout << '\n';
    Proizvol<int> matrix(3, 3);
    matrix(0, 0) = 1;
    matrix(0, 1) = 5;
    matrix(0, 2) = 3;
    matrix(1, 0) = 5;
    matrix(1, 1) = 2;
    matrix(1, 2) = 5;
    matrix(2, 0) = 4;
    matrix(2, 1) = 1;
    matrix(2, 2) = 5;

    matrix.print();

    cout << "\n\n\n\n";

    Proizvol<double> matrices[3];
    for (int i = 0; i < 3; i++) {
        matrices[i].fill_arr();
    }

    ofstream file("matrices.txt");
    for (int i = 0; i < 3; i++) {
        file << matrices[i];
    }
    file.close();

    Proizvol<double> readMatrices[3];
    ifstream readFile("matrices.txt");
    for (int i = 0; i < 3; i++) {
        readFile >> readMatrices[i];
    }
    readFile.close();

    for (int i = 0; i < 3; i++) {
        cout << "Original matrix " << i << ":\n";
        matrices[i].print();
        cout << "Read matrix " << i << ":\n";
        readMatrices[i].print();
        cout << "\n";
    }

    return 0;
}
