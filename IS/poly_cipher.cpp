#include<bits/stdc++.h>
using namespace std;

char a[26][26];
string encryption(string plain_text , string key)
{
   int l=key.length();
   string s;
   for (int k = 0; k < plain_text.size(); k++)
   {
        for (int i = 0; i < 26; i++)
        {
            if(a[i][0]==key[k%l])
            {
                for (int j = 0; j < 26; j++)
                {
                   if(a[0][j]==plain_text[k])
                   {
                       s.push_back(a[i][j]);
                   } 
                }
            }
        } 
   }
   return s;
    
}

string decryption(string cipher_text , string key)
{
    int l=key.length();
   string s;
   for (int k = 0; k < cipher_text.size(); k++)
   {
        for (int i = 0; i < 26; i++)
        {
            if(a[i][0]==key[k%l])
            {
                for (int j = 1; j < 26; j++)
                {
                   if(a[i][j]==cipher_text[k])
                   {
                       s.push_back(a[0][j]);
                   } 
                }
            }
        } 
   }
   return s;
}

int main()
{
    
    for (int i = 0; i < 26; i++)
    {
        
        char c='A'+i;
        for (int j = 0; j < 26; j++)
        {
            if(c+j>90)
            {
                a[j][i]=c+j-26;
            }
            else
            {
                a[j][i]=c+j;
            }
        }  
    } 

    cout << "---------------------------------\n---------------------------------\nThe Substitution Table is\n---------------------------------\n---------------------------------\n"<< endl;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            cout << a[i][j] << " ";
        }  
        cout << endl;
    } 
    
    string plain_text,cipher_text,decrypted_text,key;
    
    cout << "\n\nEnter the plain text and the key below" << endl; 
    cin >> plain_text >> key;


    cipher_text=encryption(plain_text,key);

    cout << "Encrypted Text is:- " << cipher_text << endl;

    decrypted_text=decryption(cipher_text,key);

    cout << "Decrypted Text is:- " << decrypted_text << endl;



       
}