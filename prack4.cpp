#include <iostream>
#include <cstring>

using namespace std;

class BaseString
{
protected:
    char* p; int len; int capacity;
public:
    BaseString(char* ptr){
        //cout<<"\nBase Constructor 1\n";
        len = strlen(ptr) + 1;
        capacity = 256;
        p = new char[capacity];
        if (p != NULL){
            for(int i=0;i<len;i++){
                p[i] = ptr[i];
            }
            p[len] = '\0';
        }
    }
    BaseString(int Capacity = 256){
        //cout<<"\nBase Constructor 0\n";
        capacity = Capacity;
        p = new char[capacity];
        if (p != NULL){
            len = 0;
        }
    }
    BaseString(const BaseString& cbs){
        //cout<<"\nBase Copy Constructor\n";
        len = cbs.len;
        p = new char[cbs.capacity];
        if (p != NULL){
            capacity = cbs.capacity;
            for(int i=0;i<cbs.len - 1;i++){
                p[i] = cbs.p[i];
            }
            p[len-1] = '\0';
        }
    }
    ~BaseString(){
        //cout<<"\nBase Destructor\n";
        if(p!=NULL)
            delete[] p;
        len = 0;
    }
    
    int Length() {return len;}
    int Capacity() { return capacity; }
    char* get() {return p;}
    
    char& operator[](int i) {return p[i];}
    BaseString& operator=(BaseString& s){
        //cout<<"\nBase Operator = \n";
        len = s.Length();
        p = new char[s.capacity];
        if (p != NULL){
            capacity = s.capacity;
            for(int i=0;i<s.Length();i++){
                p[i] = s[i];
            }
            //strcpy(p, s.get());
            p[len-1] = '\0';
        }
        return *this;
    }
    virtual void print(){
        int i=0;
        while(p[i]!='\0'){cout<<p[i];i++;}
    }
};

class ChaildString:public BaseString
{
protected:
    char* p; int len; int capacity;
public:
    ChaildString() : BaseString(){}
    ChaildString(char* p) : BaseString(p){}
    ChaildString(int capacity) : BaseString(capacity){}
    ChaildString(const ChaildString& cbs) : BaseString(cbs){}
    ~ChaildString(){}
    
    ChaildString& operator=(ChaildString& s){
        //cout<<"\nBase Operator = \n";
        len = s.Length();
        p = new char[s.capacity];
        if (p != NULL){
            capacity = s.capacity;
            for(int i=0;i<s.Length();i++){
                p[i] = s[i];
            }
            //strcpy(p, s.get());
            p[len-1] = '\0';
        }
        return *this;
    }

    void codsalat(){
        ChaildString res(*this);
        if (p != NULL){
            for (int i = 0; i < res.Length(); i++){
                res.p[i] = char(int(p[i])+1);
                //cout << char(int(p[i])+1) << ' ';
            }
        }
        //p[len]='\0';
        //res.print();
        //*this = reskon;
        p = res.p;
    }
    //char* decodsalat(){}
};

int main(){
    char c1[10] = {'q','w','e','r','t','y'};
    char c2[10] = {'t','e','s','t'};
    BaseString str1(c1);
    BaseString str2(str1);
    ChaildString str3(c2);
    ChaildString str4(c1);
    // cout << "str1 Capacity = " << str1.Capacity() << endl;
    // cout << "str1 Length = " << str1.Length() << endl;
    // cout << "str1 get = " << str1.get() << endl;
    // str1.print();
    // cout << endl;
    // str2.print();
    // //cout << endl << strlen(c);
    // cout << endl;
    // cout << "str3 Capacity = " << str3.Capacity() << endl;
    // cout << "str3 Length = " << str3.Length() << endl;
    // cout << "str3 get = " << str3.get() << endl;
    // str3.print();
    // cout << endl;
    // str4.print();
    // cout << endl << "codesalat str3 ";
    //str4.codsalat(str1);
    str3.codsalat();
    str3.print();
    cout << endl;
    //str4.print();
    return 0;
}
