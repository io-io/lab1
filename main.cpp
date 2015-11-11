#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

const int nn = 100;
using namespace std;
struct SoLongReal{
    int integer[nn]={0};
    int real[nn]={0};
};

void show(SoLongReal& inp){
    //cout << "!!" <<inp.integer[0];
    //cout << "Here: " << endl;
    //cout << inp.integer[inp.integer[0]];
    cout << inp.integer[inp.integer[0]];
    for (int i = inp.integer[0]-1; i >0; --i) {
        if (inp.integer[i]/1000==0){
            cout << "0";
        };
        if (inp.integer[i]/100==0){
            cout << "0";
        };
        if (inp.integer[i]/10==0){
            cout << "0";
        };
        cout << inp.integer[i];
    }

    cout << ".";
    for (int i = 1; i <= inp.real[0]-1; ++i) {
        if (inp.real[i]/1000==0){
            cout << "0";
        };
        if (inp.real[i]/100==0){
            cout << "0";
        };
        if (inp.real[i]/10==0){
            cout << "0";
        };
        cout << inp.real[i];
    }
    cout << inp.real[inp.real[0]];
    //cout << "inp.real[inp.real[0]] "<< inp.real[inp.real[0]] << endl;
    //cout << "[inp.real[0]] "<< inp.real[0] << endl;
}
void removeZeroInt(string& inpstr){
    while (inpstr[0]=='0'){
        inpstr.erase(0,1);
    }
};
void removeZeroReal(string& inpstr){
    while (inpstr[inpstr.length()-1]=='0'){
        inpstr.erase(inpstr.length()-1);
    }
};
void int2arr(string& intstr, SoLongReal& inp){
    inp.integer[0]=ceil(intstr.length()/4.0);
    //cout <<"heh "<< inp.integer[0];
    if (inp.integer[0]==0)
        {inp.integer[0]=1;
        intstr="000"+intstr;}; //dirty
    for (int i = 1; i < inp.integer[0]; ++i) {
        inp.integer[i]=stoi(intstr.substr(intstr.length()-4,intstr.length()));
        //cout << "##"<< intstr.substr(intstr.length()-4,intstr.length());
        //cout << inp.integer[i] << endl;
        intstr.erase(intstr.length()-4,4);
    }
    inp.integer[inp.integer[0]]=stoi(intstr);

};
void real2arr(string& realstr, SoLongReal& inp){
    inp.real[0]=ceil(realstr.length()/4.0);
    if (inp.real[0]==0)
    {inp.real[0]=1;
    realstr="000"+realstr;}; //dirty
    //cout <<"wow "<< inp.real[0];
    for (int i = 1; (i < inp.real[0]); ++i) {
        inp.real[i]=stoi(realstr.substr(0,4));
        realstr.erase(0,4);
    }
    inp.real[inp.real[0]]=stoi(realstr);
}
bool isdotinstr(string inp){
    bool alreadydot = false;
    for (int i = 0; i < inp.length(); ++i) {
        if (inp[i]=='.'){
            return true;
        }
    }
    return false;
}
bool IsNumber (const string ins){
    for (int i = 0; i < ins.length(); ++i)
    {
        if (!(isdigit(ins[i])))
        {
            return false;
        }
    }
    return true;
};
bool readfromfile(ifstream& intxt, SoLongReal& inp) {
    string txtstr, intstr, realstr;
    intxt >> txtstr;
    cout << txtstr << endl;
    cout << txtstr << endl;
    intstr = txtstr.substr(0, txtstr.find('.'));
    ///
    if (isdotinstr(txtstr)){
        realstr = txtstr.substr(txtstr.find('.')+1, txtstr.length());
    }
    else {
        realstr="";
    }
    //cout << endl << "intstr " << intstr << endl;
    //cout << endl <<  "realstr" << realstr << endl;
    removeZeroInt(intstr);
    removeZeroReal(realstr);
    if (IsNumber(intstr)){
        int2arr(intstr, inp);
    }
    else {
        //cout << "wrong in int part" << endl;
        return false;
    }
    if (IsNumber(realstr)){
        real2arr(realstr, inp);
    }
    else {
        //cout << "wrong in real part" << endl;
        return false;
    }

    return true;
};
bool is_Equal(SoLongReal first, SoLongReal second){
    int maxintcells=max(first.integer[0],second.integer[0]);
    int maxrealcells=max(first.real[0],second.real[0]);
    if (!(first.integer[0]=second.integer[0])){
        return false;
    }
    if (!(first.real[0]=second.real[0])){
        return false;
    }
    for (int i = 1; i < maxintcells; ++i) {
        if (first.integer[i]!=second.integer[i]){
            return false;
        }
    }
    for (int i = 1; i < maxrealcells; ++i) {
        if (first.real[i]!=second.real[i]) {
            return false;
        }
    }
    return true;
};

bool MoreOrEqual(SoLongReal first, SoLongReal second){
    if (first.integer[0]>second.integer[0]){
        return true;
    }
    else if (first.integer[0]==second.integer[0]){
        for (int i = first.integer[0] ; i > 0; --i) {
            if (first.integer[i]<second.integer[i]){
                return false;
            }
        }
        for (int j = 1; j < first.real[0]; ++j) {
            if (first.real[j]<second.real[j]){
                return false;
            }
        }
        return true;
    }
    else false;
};

SoLongReal sum(SoLongReal first, SoLongReal second){
  SoLongReal res;
    int next=0;
    res.real[0]=max(first.real[0],second.real[0]);
    res.integer[0]=max(first.integer[0], second.integer[0]);
    //cout << "max " << res.real[0] << res.integer[0];
    for (int i = res.real[0]; i>0; --i) {
    res.real[i]=first.real[i]+second.real[i]+next;
        if (res.real[i]>=10000){
            res.real[i]%=10000;
            next=1;

        }
        else next=0;
    };

    for (int i = 1; i<=res.integer[0]; ++i) {
        res.integer[i]=first.integer[i]+second.integer[i]+next;
        if (res.integer[i]>=10000){
            res.integer[i]%=10000;
            next=1;

        }
        else next=0;
    }
    if (next==1){
        res.integer[0]++;
        res.integer[res.integer[0]]=1;
   };
    return res;
};
SoLongReal sub(SoLongReal first, SoLongReal second){
    int next=0;
    SoLongReal res;
    res.real[0]=first.real[0];
    cout << "hey" << first.real[0];
    for (int i = first.real[0]; i > 0; --i) {
        cout << "i is: " << i << endl;
        res.real[i]=first.real[i]-second.real[i]-next;
        cout << "res.real[i]" << res.real[i] << endl;
        if (first.real[i]-second.real[i]-next<0){
            next=1;
        }
        else next=0;
    }
//    for (int j = 1; j <= first.integer[0]; ++j) {
//        res.integer[j] = first.integer[j] - second.integer[j] - next;
//        if (first.integer[j] - second.integer[j] - next < 0) {
//            next = 1;
//        }
//    }
    return res;
};
int main() {



    SoLongReal a;
    SoLongReal b;
    SoLongReal c;
    ifstream intxt("in.txt");
    ofstream outtxt("out.txt");
    if (readfromfile(intxt, a) && readfromfile(intxt, c)){
        b = sub(a,c);
        cout << endl;
        cout << "here is b" << endl;
        show(b);
        cout << endl;
    }
    else cout << "ошибка в записи чисел во входном файле";
    ////////
//    cout << "here is a ";
//    show(a);
//    cout << endl << "here is c ";
//    show(c);
//    cout << endl;
//    //cout << endl << is_Equal(a,a);
//    b = sum(a,c);
//    show(b);
    //cout << endl << MoreOrEqual(a,a);
    cout <<endl << "Hello, World!" << endl;

    system("READ");


    return 0;
}