#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include<ctime>
#define MAX_CHARACTER_NUM 1000
using namespace std;
string block[MAX_CHARACTER_NUM*2]; // �ִ� ������ �� �ִ� ���ڰ��� : 1000

//char���� int������ ��ȯ 
int change_asc(char c){
	int num = c;
	return num;
}

//�������� ������ �Լ� 
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
//�������� ��ȯ
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
	reverse_binary(k); // �������� ������ �Լ� 
}

//�и�Ƽ ��Ʈ �߰�
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

// num��° ���� CRC encoding �ؼ� ��ȯ�ϴ� �Լ�
string add_crc(int num){   
	int i,j,keylen,msglen;
	char input[100] = {0,}, key[30] = {0, }, temp[30] = {0, }, quot[100]={0, }, rem[30]={0, }, key1[30]={0, };
	
	//string �� �迭 ���ڿ��� ���� 
	for(i=0;i<block[num].length();i++){
		input[i] = block[num].at(i);
	}
	
	//divisor = 1001�� ���� 
	key[0] = '1';
	key[1] = '0';
	key[2] = '0';
	key[3] = '1';
	
	//CRC encoding 
	keylen=strlen(key);
	msglen=strlen(input);
	strcpy(key1,key);
	for (i=0;i<keylen-1;i++) {
		input[msglen+i]='0';
	}
	for (i=0;i<keylen;i++){
		temp[i]=input[i];
	}
	for (i=0;i<msglen;i++) {
		quot[i]=temp[0];
		if(quot[i]=='0'){
			for (j=0;j<keylen;j++)
				key[j]='0'; 
		}
		else{
			for (j=0;j<keylen;j++)
				key[j]=key1[j];
		}
		for (j=keylen-1;j>0;j--) {
			if(temp[j]==key[j])
				rem[j-1]='0'; 
			else
				rem[j-1]='1';
		}
		rem[keylen-1]=input[i+keylen];
		strcpy(temp,rem);
	}
	strcpy(rem,temp);

	string final;
	int temp2=0;
	for(i=0;i<msglen;i++){
		final+=input[i];
	}
	for(i=0;i<keylen-1;i++){
		final+=rem[i];
	}
	block[num] = final;
	return final;
}

// num��° ���� CRC decoding �ؼ� syndrome�� ��ȯ�ϴ� �Լ�
string calc_syndrome(int num){   
	int i,j,keylen,msglen;
	char input[100] = {0,}, key[30] = {0, }, temp[30] = {0, }, quot[100]={0, }, rem[30]={0, }, key1[30]={0, };
	
	//string �� �迭 ���ڿ��� ���� 
	for(i=0;i<block[num].length();i++){
		input[i] = block[num].at(i);
	}
	
	//divisor = 1001�� ���� 
	key[0] = '1';
	key[1] = '0';
	key[2] = '0';
	key[3] = '1';
	
	//CRC encoding 
	keylen=strlen(key);
	msglen=strlen(input);
	strcpy(key1,key);
	for (i=0;i<keylen-1;i++) {
		input[msglen+i]='0';
	}
	for (i=0;i<keylen;i++){
		temp[i]=input[i];
	}
	for (i=0;i<msglen;i++) {
		quot[i]=temp[0];
		if(quot[i]=='0'){
			for (j=0;j<keylen;j++)
				key[j]='0'; 
		}
		else{
			for (j=0;j<keylen;j++)
				key[j]=key1[j];
		}
		for (j=keylen-1;j>0;j--) {
			if(temp[j]==key[j])
				rem[j-1]='0'; 
			else
				rem[j-1]='1';
		}
		rem[keylen-1]=input[i+keylen];
		strcpy(temp,rem);
	}
	strcpy(rem,temp);

	string syndrome;
	for(i=0;i<keylen-1;i++){
		syndrome+=rem[i];
	}
	return syndrome;
}
int main(void){
	cout << "----14051012_Dojinwoo_Data communication : CRC encoder & decoder Program----" << endl;
	cout << endl;
	int num;  // �и�Ƽ ��Ʈ�� �߰��� ������ ���� 
	cout << "Enter the number of Characters (Maximum 1000 Characters) : ";
	cin >> num;
	cout << "Enter "<< num << " input characters : ";
	for(int i=0;i<num;i++){
		char char_input;
		cin >> char_input;
		change_binary(change_asc(char_input),i*2);
	}
	cout << endl;
	
	cout << "��� CRC encoder  ���"<<endl; 	
	cout << "Change into binary number : "; 
	int cnt = 0;
	for(int i=0;i<num;i++){
		cout << block[cnt] << block[cnt+1] << " ";
		cnt+=2; 
	}
	cout << endl;
	

	cout << "Change into 4bits blocks : ";
	cnt = 0;
	for(int i=0;i<num;i++){
		cout << block[cnt] << " " << block[cnt+1] << " ";
		cnt+=2; 
	}
	cout << endl;
	
	cout << "CRC Codeword : ";
	for(int i=0;i<num*2;i++){
		cout << add_crc(i) << " ";
	}
	cout << "\n" << endl;
	
	cout << "Is link reliable? (Y/N) : ";
	char answer;
	cin >> answer;
	if(answer == 'Y' || answer == 'y'){
		cout << "Reliable transmission ..." << endl;
		Sleep(500); // 0.5�� ���� 
		cout << "Reliable transmission ...." << endl;
		Sleep(500); // 0.5�� ���� 
		cout << "\n";
	} 
	//Unreliable Link
	else if (answer == 'N' || answer == 'n'){
		// 0~6 �����߻� 
		srand((unsigned int)time(0));
		// ���� codeword 1bit �ٲ㼭 ���� 
		for(int i=0;i<num*2;i++){
			int random = rand() % 7; 
			if(block[i].at(random) == '0'){
				block[i].at(random) = '1';
			}
			else{
				block[i].at(random) = '0';
			}
		}
		cout << "Unreliable transmission ..." << endl;
		Sleep(500); // 0.5�� ���� 
		cout << "Unreliable transmission ...." << endl;
		Sleep(500); // 0.5�� ���� 
		cout << "\n";
	}
	else{
		cout << "System error!!";
		exit(1);
	}
	
	cout << "��� CRC decoder  ���"<<endl; 	
	cout << "<< Calculation Syndrome >>" << endl;
	for(int i=0;i<num*2;i++){
		if(calc_syndrome(i).at(0) == '0' && calc_syndrome(i).at(1) == '0' && calc_syndrome(i).at(2) == '0'){
			cout << "Syndorme : " << calc_syndrome(i) << " Accept!" << endl;
		}
		else{
			cout << "Syndorme : " << calc_syndrome(i) << " Discard!" << endl;
		}
	}
	return 0;
}
