#include <iostream>
#include <string>
#include <cmath>
#include <string.h>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;
long long  LC=0;
ifstream in("assembler.txt");
ofstream out("machine.txt");
string line;
struct symbol{
int address;
string label;
string operand;
};
bool is_number(string s);

struct inst{
char i; int opcode;string operand;int address;string total;
};
vector<symbol> symboltable;
// instructions map
pair <string,int> instructiontable[]={
make_pair("AND",0x0),
make_pair("ADD",0x1),
make_pair("LDA",0x2),
make_pair("STA",0x3),
make_pair("BUN",0x4),
make_pair("BSA",0x5),
make_pair("ISZ",0x6),
make_pair("AND",0x8),
make_pair("ADD",0x9),
make_pair("LDA",0xA),
make_pair("STA",0xB),
make_pair("BUN",0xC),
make_pair("BSA",0xD),
make_pair("ISZ",0xE),
make_pair("CLA",0x7800),
make_pair("CLE",0x7400),
make_pair("CMA",0x7200),
make_pair("CME",0x7100),
make_pair("CIR",0x7080),
make_pair("CIL",0x7040),
make_pair("INC",0x7020),
make_pair("SPA",0x7010),
make_pair("SNA",0x7008),
make_pair("CZA",0x7004),
make_pair("SZE",0x7002),
make_pair("HLT",0x7001),
make_pair("INP",0xF800),
make_pair("OUT",0xF400),
make_pair("SKI",0xF200),
make_pair("SKO",0xF100),
make_pair("ION",0xF080),
make_pair("IOF",0xF040),
};
// gets the words within a map
void getwords(string *words);
string NumberToString(long long pNumber);
long long lltoi(string word);
long long hex(string word);
string itos(int n);
bool checkLabelAddress(string *words);
int stoi(string);
int bintodec(int);
long long bin(string x);
void firstpass();
void secondpass();
long long Convert( int val)
{
    long long sign;
    if(val >0)
        sign = 0 ;
    else{
        sign = 1000000000000000;
        val = -val;
        }
   int cnt = 0;long long temp=0; ;
   while(val!=0){
    temp+= (val%2)*pow(10,cnt++);
    val/=2;
        }
return temp+sign ;
}
int main(){
   firstpass();
   secondpass();
   for(int i=0;i<symboltable.size();i++)
            out <<symboltable[i].address<< " " << symboltable[i].operand << endl ;

    return 0;
}
void firstpass(){
    while(getline(in,line)){
    string words[4]= {"","","",""};
    getwords(words);
    if(checkLabelAddress(words));
    else {
    if(words[0]=="ORG")
        LC =  hex((NumberToString(stoi(words[1]) ) ) );
    else if (words[0]=="END")
            return ;
    }

    LC++;

}
}
int stoi(string word){
    int num=0,cnt=0;
    for(int i=word.length()-1;i>=0;i--)
        num+= (word[i] - '0')*pow(10,cnt++);
    return  num ;

}
long long lltoi(string word){
    long long num=0,cnt=0;
    for(int i=word.length()-1;i>=0;i--)
        num+= (word[i] - '0')*pow(10,cnt++);
    return  num ;

}
string itos(int n){
    string temp="" ;
    while(n>0){
        temp+= n%10 + '0' ;
        n/=10;
    }
    for(int i=12;temp.length() <12;i--)
        temp+='0';

    reverse(temp.begin(),temp.end());
    return temp;

}
int bintodec(int x){
    int temp =0,cnt=0;
    while(x >0){
    temp+= (x%10)*pow(2,cnt++);
    x/=10;

    }
    return temp ;
}
void getwords(string *words){
int cnt = 0 ;
for(int i=0;i<4;i++)
    words[i] ="";

for(int i=0;i<line.length() && cnt < 4;i++)
    if( line[i] != ' ' )
    words[cnt]+= line[i];
    else
        cnt++;

}
bool checkLabelAddress(string *words){
if(words[0][words[0].length()-1] == ',' ){
    symbol temp ;
     temp.address = Convert(LC) ;
     temp.label = words[0].substr(0,words[0].length()-1);
    if(words[1] =="HEX"){
            temp.operand =  NumberToString(Convert(hex(words[2]) ) );
        }else if (words[1]=="DEC"){
            temp.operand = NumberToString(bin(words[2]) );
        }
    while(temp.operand.length() <16)
        temp.operand.insert(0,"0");

    symboltable.push_back(temp);
    return 1 ;
    }else {
    return 0 ;
    }
}
long long hex(string word){
int num = 0 ;
 for(int i=word.length()-1;i>=0;i--){
        if( ( (word[i] -'0') >= 0 && (word[i] -'0') <= 9) || ( (word[i]-'A') >= 0 && (word[i]-'A') < 6 ) );
        else{
        cout << "wrong format in line "<<LC <<" expected hex insted of "<<word[i] <<endl ;
        return -1;}
 }
bool sign = false ;
if(word[0] == '-'){
    sign = true ;
    word = word.substr(1,word.length());
    }
string temp =  "0x"+word ;
sscanf(&temp[0],"%x",&num);
  if(sign)
    num = - num ;

    return num ;
}
long long bin(string x){
    int temp=0,cnt=0;
    for(int i=x.length()-1;i>=0;i--){
        if( (x[i] -'0') >= 0 && (x[i] -'0') <= 9  )
        temp+= (int)(x[i] - '0')*pow(10,cnt++);
            else{
            cout << "wrong format in line "<<LC <<" expected decimal"<<endl ;
            return -1;}
    }
return Convert(temp) ;
}
string NumberToString(long long pNumber)
{
 ostringstream oOStrStream;
 oOStrStream << pNumber;
 return oOStrStream.str();
}
bool is_number(string s){
bool numeric = true ;
for(int i=0;i<s.length();i++)
    if ( !( (s[i] - '0' >= 0 &&  s[i] - '0' <=9 ) || s[i] == 'A' || s[i] == 'B' || s[i] == 'C' || s[i] == 'D' || s[i] == 'E' || s[i] == 'F' ) )
        numeric = false ;
return numeric;
}
void secondpass(){
    LC=0;
    int org = 0 ;
    in.clear();
    in.seekg(0,ios::beg);
    while(getline(in,line)){
        string words[4]= {"","","",""};
    getwords(words);
    line = "";
       bool l2etoh = false ;
     if(words[0]=="ORG"){
        l2etoh = true ;
        LC =  hex((NumberToString(stoi(words[1]) ) ) );
        org = LC ;
        continue;
        }
    else if (words[0]=="END"){
            l2etoh = true ;
            return ;}

    for(int i=0;i<32;i++){
        if(instructiontable[i].first == words[0] && !l2etoh){
         inst instruction;
         instruction.address = LC ;
         // MRI instruction
         if(i<14){
            instruction.opcode = Convert(instructiontable[i].second);
            for(int j=0;j<symboltable.size();j++){
                if(words[1]==symboltable[j].label){
                    l2etoh = true ;
                    instruction.operand =itos(symboltable[j].address);
                    break ;
                }
            }
             if(is_number(words[2]) && !l2etoh){
                    l2etoh = true;
                    instruction.operand =Convert(hex(words[2]));
                }else {
                    if(!l2etoh)
                cout << "wrong format in line "<<LC-org <<" expected hex value or a label instead of "<<words[2] <<endl ;
                }
                if(words[2].length() == 1 && words[2][0] =='I'){
                instruction.i = '1';
                }
                else if(words[2]==""){
                instruction.i='0';
                }else{
                    if(!l2etoh)
                        cout << "wrong format in line "<<LC-org <<" expected I insted of "<<words[2] <<endl ;
                }
                string stropcode = NumberToString(instruction.opcode);
                while(stropcode.length() <3)
                    stropcode = '0'+ stropcode;
                instruction.total = instruction.i  + stropcode+instruction.operand;


            }
         // non MRI instruction
         else{
            l2etoh= true ;
             string pre ="";
            if(Convert(instructiontable[i].second) <= pow(10,15))
            pre="0";
            instruction.total = pre+NumberToString(Convert(instructiontable[i].second)) ;

         }

         out <<Convert(instruction.address)<<" " << instruction.total << endl;

       break ; }
    }
    LC++;
    }

}


