#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

class Transaction
{
      private: 
               int code;
               float amount;
      public: 
              Transaction(){code=1;amount=1;}
              Transaction(int code, float amount){this->code=code;this->amount=amount;}
              void setValues(int code,float amount){this->code=code;this->amount=amount;}
              int getCode(){return this->code;}
              float getAmount(){return this->amount;}
             
};

int main()
{
    list <Transaction> list1;//a
    
    Transaction t[4];//b
    for(int i=0;i<4;i++)
    {
                    t[i].setValues(i,i*2.1);
                    list1.push_back(t[i]);
        }
        list1.sort();
    copy (list1.begin(), list1.end(), ostream_iterator<Transaction>(cout," "));
    //copy(list1.begin(), list1.end(), ostream_iterator<Transaction>(cout, " "));
    //list1.display;               

    system("PAUSE");
    return 0;
}
