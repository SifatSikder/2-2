#include<bits/stdc++.h>
using namespace std;
#define N 20
vector<pair<char,char>> v;
void key()
{
    for (int i = 32; i < 127; i++)
    {
      if(i+N>126)
      {
           v.push_back({i,i+N-127+32}); 
      }
      else
      {
           v.push_back({i,i+N}); 
      }
    }  
}

string encryption(string plain_text)
{
    string s; 
    for (int i = 0; i < plain_text.size(); i++)
    {
       for (int j = 0; j < 95; j++)
       {
          if(v[j].first==plain_text[i])
          {
              s.push_back(v[j].second);
              break;
          }
       }
       
    }
    return s;
}

string decryption(string cipher_text)
{
    string s; 
    for (int i = 0; i < cipher_text.size(); i++)
    {
       for (int j = 0; j < 95; j++)
       {
          if(v[j].second==cipher_text[i])
          {
              s.push_back(v[j].first);
              break;
          }
       }
       
    }
    return s;
}

int main()
{
    key();
     cout << "\n\n---------------------------------\n---------------------------------\nThe Substitution Table is\n---------------------------------\n---------------------------------\n"<< endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].first << "--->" << v[i].second << endl;
    }

    string plain_text,cipher_text,decrypted_text;

    cout << "\n\nEnter the plain text below" << endl;
    getline(cin,plain_text); 

    cipher_text=encryption(plain_text);

    cout << "Encrypted Text is:- " << cipher_text << endl;

    decrypted_text=decryption(cipher_text);

    cout << "Decrypted Text is:- " << decrypted_text << endl;
}
