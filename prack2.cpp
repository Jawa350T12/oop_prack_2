#include <iostream>
#include <cstring>

using namespace std;

class MyArrayParent
{
protected:
    //сколько памяти выделено?
    int capacity;
    //количество элементов - сколько памяти используем
    int count;
    //массив
    double* ptr;

    // Увеличение вместимости массива на заранее определенную константу
    void incrCap(double exp=2.0) {
        capacity = (int)(capacity*exp);
        double* p_newArr = new double[capacity];
        for (int i = 0; i < count; i++)
        {
            p_newArr[i] = ptr[i];
        }

        if (ptr)
        {
            delete[] ptr;
        }
        ptr = p_newArr;
    }

public:
    //конструкторы и деструктор
    MyArrayParent(int Dimension = 100){
        cout << "\nMyArray constructor";
        ptr = new double[Dimension];
        capacity = Dimension;
        count = 0;
    }
    //конструктор принимает существующий массив
    MyArrayParent(double* arr, int Dimension){
        cout << "\nMyArray constructor";
        capacity = Dimension*2;
        count = Dimension;
        ptr = new double[capacity];
        for (int i=0;i<count;i++){
            ptr[i]=arr[i];
        }
        //заполнить массив ptr, заполнить поля
    }
    // Конструктор (копий) MyArrayParent
    MyArrayParent(const MyArrayParent& cop) {
        cout << "Copy constructor\n";
        ptr = new double[cop.capacity];
        count = cop.count;
        capacity = cop.capacity;
        for (int i = 0; i < count; i++) {
            ptr[i] = cop.ptr[i];
        }
    }
    //деструктор
    ~MyArrayParent(){
        cout << "\nMyArray destructor";
        if (ptr != NULL){delete[] ptr; ptr = NULL;}
    }
    //обращение к полям
    int Capacity() { return capacity; }
    int Size() { return count; }
    double GetComponent(int index){
        if (index >= 0 && index < count)
            return ptr[index];
        //сгенерировать исключение, если индекс неправильный
        return -1;
    }
    void SetComponent(int index, double value){
        if (index >= 0 && index < count)
            ptr[index] = value;
        //сгенерировать исключение, если индекс неправильный
    }
    //добавление в конец нового значения
    void push(double value){
        if (count < capacity){
            ptr[count] = value;
            count++;
        }
        //что делаем, если массив заполнен?
        // else{
        //     cout << "ERROR! Array is full!";
        // }
    }
    //удаление элемента с конца
    void RemoveLastValue(){
        if (count >= 0)
            count--;
        // else
        //     cout << "ERROR! Array is space!";
        //что делаем, если пуст?
    }
    double& operator[](int index){
        return ptr[index];
        //перегрузка оператора []
    }
    double* indexOf(double* abcd) {
        string n;
        int c = 0;
        double* abcdres;
        for (auto i : abcd) {
            n = to_string(i);
            if (int(n[0]-'0')+ int(n[1] - '0') == int(n[2] - '0') + int(n[3] - '0')) {
                abcdres[c] = i;
                c++
            }
        }
        return abcdres;
    }
    MyArrayParent& operator=(const MyArrayParent& V){
        cout << "\noperator = ";
        if (capacity < V.capacity) {
            delete[] ptr;
            ptr = new double[V.capacity];
            capacity = V.capacity;
        }
        count = V.count;
        for (int i = 0; i < count; i++) {
            ptr[i] = V.ptr[i];
        }
        return *this;
        //оператор =
        //arr1 = arr2 = arr3; где arr_i - объекты нашего класса
}
    MyArrayParent(const MyArrayParent& V){
        cout << "\nCopy constructor";
        //создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
    }
    void print(){
        cout << "\nMyArr, size: " << count << ", values: {";
        int i = 0;
        for (i = 0; i < count; i++){
            cout << ptr[i];
            if (i != count - 1)
                cout << ", ";
        }
        cout << "}";
    }
};

class MyArrayChild : public MyArrayParent
{
public:
    //используем конструктор родителя. Нужно ли что-то ещё?
    MyArrayChild(double* arr, int dim) : MyArrayParent(arr, dim) { cout << "MyArrayChild constructor\n"; }
    MyArrayChild(int dim = 100) : MyArrayParent(dim) { cout << "MyArrayChild constructor\n"; }
    MyArrayChild(const MyArrayChild& V) : MyArrayParent(V) { cout << "MyArrayChild constructor\n"; }
    ~MyArrayChild() { cout << "\nMyArrayChild destructor\n";}

    // Удаление элемента по индексу
    void removeAt(int index = -1) {
        if (count == 0) {
            throw out_of_range("Attempted to remove from empty array");
        }
        if (index < 0 || index >= count) {
            throw out_of_range("invalid index");
        }
        if (index == -1){ RemoveLastValue(); return;}
        for (int i = index; i < count - 1; i++) {ptr[i] = ptr[i + 1];} count--;
    }

    void insertAt(double value, int index = -1) {
        if (index == -1 || index == count) {push(value);  return;}
        if (index < 0 || index > count) {
            throw out_of_range("invalid index");
        }
        if (count >= capacity) {incrCap();}
        for (int i = count; i > index; i--) {ptr[i] = ptr[i - 1];}
        count++;
        ptr[index] = value;
    }


    // Вощвращает подмассив в полуинтеравле [start, end)
    void subsequence(int left, int right, MyArrayChild* res) {
        if (left < 0 || right > count - 1) {throw out_of_range("invalid left");}
        if (right < 1 || right > count) {throw out_of_range("invalid right index");}
        if (left >= right) {throw out_of_range("invalid boundaries");}
        for (int i = left; i < right; i++) {res->push(ptr[i]);}
    }

    friend MyArrayChild operator+(double elem, MyArrayChild arr);
    MyArrayChild operator+(double elem) {
        MyArrayChild res = MyArrayChild(*this);
        res.push(elem);
        return res;
    }
    //Добавить функцию из 5 пункта 8 варианта
};
    MyArrayChild operator+(double elem, MyArrayChild arr) {
        MyArrayChild res = MyArrayChild(arr);
        res.push(elem);
        return res;
    }
class MySortedArray : public MyArrayChild 
{
protected:
    int binSearch(double elem) {
        if (ptr[0] == elem) {return 0;}
        if (ptr[count - 1] == elem) {return count;}
        int left = 0; int right = count - 1; int m = 0;
        while (left <= right) {
            m = (left + right) / 2;
            if (ptr[m] < elem) {left = m + 1;}
            else if (ptr[m] > elem) {right = m - 1;}
            else {return m;}
        }
        return -1;
    }

    int _binSearch2(double elem) {
        if (ptr[0] > elem) {return 0;}
        if (ptr[count - 1] < elem) {return count;}
        int left = 0; int right = count - 1; int m = 0;
        while (left <= right) {
            m = (left + right) / 2;
            if (ptr[m] < elem) {left = m + 1;}
            else if (ptr[m] > elem) {right = m - 1;}
            else {return m;}
        }
        return m;
    }
public:
    // Конструкторы / Деструкторы

    MySortedArray(double* arr, int dim) : MyArrayChild(arr, dim) { cout << "MyArraySorted constructor\n"; }
    MySortedArray(int dim = 100) : MyArrayChild(dim) { cout << "MyArraySorted constructor\n"; }
    MySortedArray(const MyArrayChild& V) : MyArrayChild(V) { cout << "MyArraySorted constructor\n"; }
    ~MySortedArray() { cout << "MyArrayChild destructor\n"; }

    // void reqMethod() {return MyArrayChild::reqMethod();}

    int indexOf(double elem, bool b_searchFromStart) {return binSearch(elem);}

    // учитывая порядок
    void push(double elem) {
        int index = _binSearch2(elem);
        MyArrayChild::insertAt(elem, index);
    }
};

int main()
{
    if (true){
        MyArrayParent arr;
        int i = 0;
        for (i = 0; i < 10; i++){
            arr.push(i + 1);
        }
        MyArrayParent p1;
        p1 = arr;
        p1.print();
        cout << "\n";
    }
    char c; cin >> c;
    return 0;
}
