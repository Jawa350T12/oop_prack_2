#include<iostream>

using namespace std;

template<class T>

class Element
{
protected:
    Element* next;
    Element* prev;
    T info;
public:
    Element(T data){
        next = prev = NULL;
        info = data;
    }
    Element(Element* Next, Element* Prev, T data){
        next = Next;
        prev = Prev;
        info = data;
    }
    Element(const Element& el)
    {
        next = el.next;
        prev = el.prev;
        info = el.info;
    }
    template<class T1>
    friend ostream& operator<<(ostream& s, Element<T1>& el);
};

template<class T1>

    ostream& operator<<(ostream& s, Element<T1>& el){
        s << el.info;
        return s;
    }

template<class T>

class LinkedList
{
protected:
    Element<T>* head;
    Element<T>* tail;
    int count;
public:
    LinkedList()
    {
        head = tail = NULL;
        count = 0;
    }
    virtual Element<T>* pop() = 0;
    virtual Element<T>* push(T value) = 0;
    virtual Element<T>& operator[](int index) = 0;
    virtual bool isEmpty() { return (LinkedList<T>::count == 0);}
    
    template<class T1>
    
    friend ostream& operator<<(ostream& s, LinkedList<T1>& el);
    virtual ~LinkedList(){
        cout << "\nBase class destructor";
        //дописать деструктор базового класса
        head = NULL; tail = NULL;
    }
};

template<class T1>

ostream& operator<<(ostream& s, LinkedList<T1>& el)
{

}

template<class T, int N = 20>

class Stack : public LinkedList<T>
{
public:
    Stack<T, N>() : LinkedList<T>(){
        if (N > 0)
            for (int i = 0; i < N; i++)
                push(0);
    }
    virtual Element<T>* push(T value){
        if (LinkedList<T>::head == NULL){//if(count==0)
            //пустой список
            LinkedList<T>::tail = new Element<T>(value);
            LinkedList<T>::head = LinkedList<T>::tail;
        }
        else{
            //элементы уже есть
            LinkedList<T>::tail->next = new Element<T>(value);
            //LinkedList<T>::tail->next->prev =
            LinkedList<T>::tail;
            LinkedList<T>::tail = LinkedList<T>::tail->next;
        }
        LinkedList<T>::count++;
        return LinkedList<T>::tail;
    }
    virtual Element<T>* pop(){
        //пустой список
        if (LinkedList<T>::tail == NULL)
            return NULL;
        Element<T>* res = LinkedList<T>::tail;
        //один элемент
        if (LinkedList<T>::head == LinkedList<T>::tail)
        LinkedList<T>::head = LinkedList<T>::tail = NULL;
        else{
            Element<T>* current;
            for (current = LinkedList<T>::head; current->next != LinkedList<T>::tail; current = current->next);
            LinkedList<T>::tail = current;
            LinkedList<T>::tail->next = NULL;
        }
        LinkedList<T>::count--;
        return res;
    }
    virtual ~Stack() { cout << "\nStack class destructor"; }
};

    ostream& operator<<(ostream& s, my_class& value){
        s << value.data;
        return s;
    }
int main(){
    if (true){
        Stack<double, 20> S;
        for (int i = 0; i < 10; i++)
            S.push(i);
        S.insert(3.5, S.head->next->next->next);
        cout << S;
        cout << "\n";
        //cout<<S.Find_R(5.5, S.head);
    }
return 0;}
