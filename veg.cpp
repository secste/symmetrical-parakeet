#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

using namespace std;
static const int FROM = 3;
static const int TO = 4;

// count greatest common divisor of 2 numbers
static int gcd(int u, int v)
{
    if (v) return gcd(v, u % v);
    else return u < 0 ? -u : u;
}

// count GCD of list of numbers
int multi_gcd(vector<int> & num)
{
    if      (num.size() == 0) return 0;
    else if (num.size() == 1) return num[0];
    else if (num.size() == 2) return gcd(num[0], num[1]);

    num[1] = gcd(num[0], num[1]);
    num.erase(num.begin());
    return multi_gcd(num);
}

// find all n-grams (FROM-grams ... TO-grams) in linear time (!)
static void find_ngrams(string & str, map<string, vector<int> > & tgs, int from, int to)
{
    int length = str.length();
    for (int i = 0; i < length; ++i)
    {
        // from each position in str count all n-grams (if possible)
        for (int j = from; j <= to; ++j)
        {
            if (i+j > length) continue;
            string sub = str.substr(i, j);
            tgs[sub].push_back(i);
        }
    }
    // ignore those n-grams which are irrelevant due to insufficient
    // number of occurrences
    map<string, vector<int> >::iterator rem = tgs.begin();
    while (rem != tgs.end())
    {
        if (rem->second.size() < 3) tgs.erase(rem++);
        else ++rem;
    }
    for(map<string, vector<int> >::iterator it = tgs.begin(); it != tgs.end(); ++it)
    {
        int size = it->second.size();

        // count differences between occurences
        for (int i = size - 1; i > 0; --i)
            it->second[i] -= it->second[i-1];
        it->second.erase(it->second.begin());

        // count GCD for the n-grams
        int mgcd = multi_gcd(it->second);

        // save {"n-gram": [gcd, freq]}
        it->second.clear();
        it->second.push_back(mgcd);
        it->second.push_back(size);
    }
    // display "n-grams" with their frequency
    cout<<"n-grams with their freqiency"<<endl;
    for(map<string, vector<int> >::iterator it = tgs.begin(); it != tgs.end(); ++it)
    {
          std::cout<< it->first <<" ";
          for(int i=0;i<it->second.size();i++)
          {
                  cout<<it->second[i]<<" ";
          } 
          cout<<endl;
    }

}

// try to get the key len
static int get_key_len (map<string, vector<int> > & tgs)
{
    int key_len = 0;

    // take (4-3) best (most frequented ngrams)
    for (int step = 0; step < (TO-FROM); ++step)
    {
        // find ngram with the maximal frequency
        int max_size = 0;
        for (map<string, vector<int> >::iterator it = tgs.begin(); it != tgs.end(); ++it)
            if (it->second.at(1) > max_size) max_size = it->second.at(1);

        // find & erase all ngrams with the counted maximal frequency
        vector<int> max_gcd;
        map<string, vector<int> >::iterator rem = tgs.begin();
        while (rem != tgs.end())
        {
            if (rem->second.at(1) == max_size)
            {
                max_gcd.push_back(rem->second.at(0));
                tgs.erase(rem++);
            }
            else ++rem;
        }

        // count GCD for all ngrams with the same number of occurences
        int tmp_gcd = multi_gcd(max_gcd);
        // if key_len is invalid, then use counted GCD
        // or if can get better result with the latest gcd than we have
        // counted in previous loops
        if (key_len == 0 || gcd(key_len, tmp_gcd) < tmp_gcd) key_len = tmp_gcd;
    }

    return key_len;
}
int kasiski_test (string & str)
{
    map<string, vector<int> > ngrams;
    find_ngrams(str, ngrams, FROM, TO);
    return get_key_len(ngrams);
}

float kp = 0.0654966995;
//letter freq
map<int,int> letters_freq(string & str)
{
  map<int,int> freqs;
  for (int i = ' '; i <= '~'; ++i) freqs[i] = 0;

  for (string::iterator iter = str.begin(); iter != str.end(); ++iter)
    freqs[*iter] += 1;

  return freqs;
}

int alphabet_len = 'z' - 'a' + 1;

// letters frequencies in standard english text
static float letfreq[] = {
  0.08167, 0.01492, 0.02782, 0.04253, 0.12702, // A B C D E
  0.02228, 0.02015, 0.06094, 0.06966, 0.00153, // F G H I J
  0.00772, 0.04025, 0.02406, 0.06749, 0.07507, // K L M N O
  0.01929, 0.00095, 0.05987, 0.06327, 0.09056, // P Q R S T
  0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074}; // U V W X Y Z

//find the key itself
string get_key(string & str, int key_len)
{
  string key = "";
  
  for (int i = 0; i < key_len; ++i)
  {
    string ci = "";
    for (size_t j = i; j < str.length(); j += key_len) ci += str[j];

    map<int,int> f = letters_freq(ci);

    vector<double> guess;
    for (int g = 0; g < alphabet_len; ++g)
    {
      double sum = 0;
      for (int x = 0; x < alphabet_len; ++x) sum += letfreq[x] * f['a' + (x+g) % alphabet_len];
      sum /= double(ci.length());
      guess.push_back(fabs(sum - kp));
    }
    key += 'a' + int(min_element(guess.begin(), guess.end()) - guess.begin());
  }

  return key;
}

////////decipher
static string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

string decipher(string & ciphertext, string & key)
{

  string plaintext = "";

  int index = 0;int j=0;
  for (int i = 0; i < int(ciphertext.length()); i++)
  {   
     if((ciphertext[i]>='a' && ciphertext[i]<='z')||(ciphertext[i]>='A' && ciphertext[i]<='Z'))
     {
    index  = alphabet.find(ciphertext[i]);
    index -= alphabet.find(key[j % key.length()]);
    index += alphabet.length();
    index %= alphabet.length();
    plaintext += alphabet[index];
    j++;
}
else
{plaintext +=ciphertext[i];}
  }

  return plaintext;
}
string delSpaces(string &str) 
{
   str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
   str.erase(std::remove(str.begin(), str.end(), ','), str.end());
   str.erase(std::remove(str.begin(), str.end(), '.'), str.end());
   std::transform(str.begin(), str.end(), str.begin(), ::tolower);
   return str;
}


int main()
{
    //cihper to sting
    ifstream file("new_cext.txt");
    stringstream buffer;
    buffer << file.rdbuf();
    string ciphertext = buffer.str();
    cout << ciphertext<<endl;
    
    //clean from spaces , . and all tolower
    string chipher =ciphertext;
    chipher=delSpaces(chipher);
    //cout << chipher<<endl;
    
    //kasiski method
    int kasiski = kasiski_test(chipher);
    cout<<"Lenght of key is: "<<kasiski<<endl;
   //find real key
    string key = get_key(chipher,kasiski);
    cout<<"Key is: "<<key<<endl;
    //decipher text
    string res = decipher(ciphertext,key);
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    cout<<res<<endl;
    
    system("PAUSE");
    return 0;
}
