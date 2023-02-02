#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;
template <class T>
class Wrap_vector
{      
     // friend ostream& operator<<(ostream&, vector <T> &);
      private: vector <T> v;
      public: Wrap_vector(){}
      void add(T c){
           v.push_back(c);
           }
      int size(){return v.size();}
      T remove(){
          T value = v[v.size()-1];
          v.pop_back();
          return value;
          }
     /* void remove_if()
          {
           for(vector<int>::iterator i=v.begin(); i!=v.end(); ++i)
                   {
                       if(*i<4){
                                  v.erase(*i);
                                  }
                   }
          }*/
      void display(){
           copy(v.begin(), v.end(), ostream_iterator<T>(cout, " "));
           }
      int find_el(T value){//return the position of the element if not -1
           for(int i =0;i<v.size();i++)
                   {
                       if(v[i]==value)
                       return i;
                   }
                   return -1;
          }
      void sort_el(){
           sort(v.begin(),v.end());
           }

};
/*template <class T>
ostream& operator<<(ostream &out, vector <T> &v)
{
         for(vector<int>::iterator i=v.begin(); i!=v.end(); ++i)
                   {
                       out<<" "<<*i;
                   }
         return out;
}*/

class Student
{
      private:
              int id;
      public:
             Student(){id=1;}
             Student(int id){this->id=id;}
};

int main()
{
 Wrap_vector <int>container;
 container.add(56);
 container.add(12);
 container.add(15);
 container.display();
 cout<<endl;
 //container.remove_if();
 cout<<container.find_el(1)<<endl;
 cout<<container.size()<<endl;
 cout<<container.remove()<<endl;
// cout<<container[1];
 cout<<container.size()<<endl;
 container.display();
 cout<<endl;
 container.sort_el();
 container.display();
 cout<<endl;
 //cout<<container;
 cout<<container.remove()<<endl;
 cout<<container.remove()<<endl;
 //cout<<container[7];//out of vector
 //cout<<container.remove();//can't remove anything in empty vector
 
 
 //
 
Wrap_vector <string>container1;
 container1.add("hello");
 container1.add("buy");
 container1.add("great");
 cout<<container1.find_el("buy")<<endl;
 cout<<container1.size()<<endl;
 cout<<container1.remove()<<endl;
// cout<<container[1];
 cout<<container1.size()<<endl;
 container1.display();
 cout<<endl;
 container1.sort_el();//key sensitive
 container1.display();
 cout<<endl;
 //cout<<container;
 cout<<container1.remove()<<endl;
 cout<<container1.remove()<<endl;
 //cout<<container[7];
 //cout<<container.remove();
 
 /*
  Wrap_vector <Student>container2;
 container2.add(Student(123));
 container2.add(Student(222));
 container2.add(Student(333));
// cout<<container1.find_el(15)<<endl;
 //cout<<container.size()<<endl;
 //cout<<container.remove()<<endl;
// cout<<container[1];
 //cout<<container.size()<<endl;
 container2.display();
 cout<<endl;
 container2.sort_el();
 container2.display();
 cout<<endl;
 //cout<<container;
 //cout<<container2.remove()<<endl;
 //cout<<container2.remove()<<endl;
 //cout<<container[7];
 //cout<<container.remove();
 */
 system("PAUSE");
 return 0;
}
 
