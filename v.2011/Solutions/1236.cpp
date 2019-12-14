// первый байт ключа равен m2[0]^32, затем i-й байт ключа равен
// m2[i]^m1[i-1]^key[i-1]

#include <iostream>
#include <string>

using namespace std;

const unsigned char DECODE_BYTE=32;
const unsigned char LOW_HEX_MASK=15;

void hex_decode(string *message)
{
  for(unsigned int i=0;i<message->size();i++)
  {
    if(((*message)[i]>='0')&&((*message)[i]<='9'))
      (*message)[i>>1]=((*message)[i]-'0')<<4;
    else
      (*message)[i>>1]=((*message)[i]-'A'+10)<<4;
    i++;
    if(((*message)[i]>='0')&&((*message)[i]<='9'))
      (*message)[i>>1]+=(*message)[i]-'0';
    else
      (*message)[i>>1]+=(*message)[i]-'A'+10;
  }
  message->resize(message->size()>>1);
}

string hex_encode(string *message)
{
  string temp;
  for(unsigned int i=0;i<message->size();i++)
  {
    if(((unsigned char)(*message)[i]>>4)>9)
      temp+='A'+((unsigned char)(*message)[i]>>4)-10;
    else
      temp+='0'+((unsigned char)(*message)[i]>>4);
    if(((*message)[i]&LOW_HEX_MASK)>9)
      temp+='A'+((*message)[i]&LOW_HEX_MASK)-10;
    else
      temp+='0'+((*message)[i]&LOW_HEX_MASK);
  }
  return temp;
}

int main()
{
  string m1,m2;
  getline(cin,m1);
  hex_decode(&m1);
  getline(cin,m2);
  hex_decode(&m2);
  m2[0]^=DECODE_BYTE;
  for(unsigned int i=1;i<m2.size();i++)
    m2[i]^=m1[i-1]^m2[i-1];
  cout<<hex_encode(&m2);
}