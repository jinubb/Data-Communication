#include<iostream>
#define MAX_CHARACTER_NUM 1000
using namespace std;
string block[MAX_CHARACTER_NUM*2]; // 최대 전송할 수 있는 문자개수 : 1000

//char형을 int형으로 변환 
int change_asc(char c){
	int num = c;
	return num;
}

//이진수를 뒤집는 함수 
void reverse_binary(int k){ 
	char temp;
	for(int i=k;i<k+2;i++){
		temp = block[i].at(0);
		block[i].at(0) = block[i].at(3);
		block[i].at(3) = temp;
		
		temp = block[i].at(1);
		block[i].at(1) = block[i].at(2);
		block[i].at(2) = temp;
	}
	//swap
	block[k].swap(block[k+1]);
} 
//이진수로 변환
void change_binary(int n,int k){
	for(int i=k;i<k+2;i++){
		for(int j=0;j<4;j++){
			if(n>0){
				if(n%2==0){
					block[i]+="0";
				}
				else{
					block[i]+="1";
				}
				n/=2;
			}
			else{
				block[i]+="0";
			}
		}
	}
	reverse_binary(k); // 이진수를 뒤집는 함수 
}

//패리티 비트 추가
string add_parity(string str){
	int cnt=0;
	for(int i=0;i<4;i++){
		if(str.at(i) == '1'){
			cnt++;
		}
	}
	if(cnt % 2 == 0){
		return str+"(0)";
	}
	else{
		return str+"(1)";
	}
} 
int main(void){
	cout << "----14051012_Dojinwoo_Data communication : Parity check code Program----" << endl;
	cout << endl;
	int num;  // 패리티 비트를 추가할 문자의 개수 
	cout << "Enter the number of Characters (Maximum 1000 Characters) : ";
	cin >> num;
	cout << "Enter "<< num << " input characters : ";
	for(int i=0;i<num;i++){
		char char_input;
		cin >> char_input;
		change_binary(change_asc(char_input),i*2);
	}
	
	cout << "Change into binary number : "; 
	int cnt = 0;
	for(int i=0;i<num;i++){
		cout << block[cnt] << block[cnt+1] << " ";
		cnt+=2; 
	}
	cout << "\n\n";
	
	cout << "■■ Parity check code ■■"<<endl; 
	cout << "Change into 4bits blocks : ";
	cnt = 0;
	for(int i=0;i<num;i++){
		cout << block[cnt] << " " << block[cnt+1] << " ";
		cnt+=2; 
	}
	cout << endl;
	
	cout << "Add parity bit : ";
	cnt = 0;
	for(int i=0;i<num;i++){
		block[cnt] = add_parity(block[cnt]);
		block[cnt+1] = add_parity(block[cnt+1]);
		cout << block[cnt] << " "; 
		cout << block[cnt+1] << " "; 
		cnt+=2;
	}
	return 0;
}
