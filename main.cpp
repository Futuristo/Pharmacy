//using compiler config TDM GCC 4.9.2 Release (C++11)
#include <iostream>
#include <fstream>
//#include <stdlib.h>
#include <ctime>

using namespace std; //Otherwise use std::cout etc.

//file streams
fstream f;

//global function prototypes
void menu();
void menuV();
int countMed();

//global var
int choice;

//char ibuf[100];

//global utility functions
void pinput(int &v,int u, int l) //u: upper limit, l: lower limit, both inclusive
		{
			int c;
			while((!(cin>>v)) || v<l || v>u)
			{
				cout<<"Enter Correct Value: ";
				cin.clear(); //https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input
				cin.ignore(100,'\n');
			}
			cin.ignore(1,'\n'); //empties input buffer
		}
void pfinput(float &v,float u, float l) //u: upper limit, l: lower limit, both inclusive
		{
			int c;
			while((!(cin>>v)) || v<l || v>u)
			{
				cout<<"Enter Correct Value: ";
				cin.clear(); //https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input
				cin.ignore(100,'\n');
			}
			cin.ignore(1,'\n'); //empties input buffer
		}
		
//classes
class medicine
{
	int K;
	char name[20];
	
	int quantity;
	float u_price;
	float t_price;
	
	//mfg
	//int m_d;
	int m_m;
	int m_y;
	
	//exp
	//int e_d;
	int e_m;
	int e_y;
	
//	int exp_m;
//	int exp_y;
	
	public:
		void getDetails()
		{
			
			cout<<endl<<"Enter details about medicine: "<<endl;

			K = countMed(); //assigns K value | calling this function after input of other variables does something fishy
			
			cout<<"Enter Name: ";
			gets(name);
			
			cout<<"Enter Quantity(in units): ";
			pinput(quantity, 100, 1);
			cout<<"Enter Price of 1 unit(INR): "; 
			pfinput(u_price, 10000, 1);
			
//			cout<<endl<<"Enter Manufacturing Date: "<<endl;
//			cout<<"Month: ";
//			pinput(m_m, 12, 1);
//			cout<<"Year: ";
//			pinput(m_y, 2018, 2014);
//			
//			cout<<endl<<"Enter Expiry Date: "<<endl;
//			cout<<"Month: ";
//			pinput(e_m, 12, 1);
//			cout<<"Year: ";
//			pinput(e_y, 2030, m_y+1);
			
			//calculated data
//			t_price=quantity*u_price;
//			exp_m = (e_m + (12*(e_y-m_y)))-m_m; //difference in terms of months
//			exp_y = exp_m/12;
//			exp_m%=12;
			

			//INPUT BUFFER PROBLEM IF INPUT EXCEEDS ONE CHARACTER | RESOLVED WITH GETS() IN LINE 55
			//gets(ibuf); //to empty input buffer | XII Vol.1 Pg-311
		
		}
		void showDetails()
		{
			cout<<K<<"\t\t"<<name<<"\t\t"<<quantity<<"\t\t"<<u_price<<endl;
		}
		float rPrice() //accessor function
		{
			return u_price;
		}
		
		
		
} med;

int countMed() //counts list items
		{
			int k=0;
			f.open("Medicines.dat", ios::in | ios::binary);
			
			
			while(f.read((char*) &med, sizeof(medicine)))
			{
				k++;	
			}
			f.close();
			k++;
			
			return k;
		}

//global funcitons
void showMed()
{
	f.open("Medicines.dat", ios::in | ios::binary);
	f.seekg(0, ios::beg);
	
	cout<<"\nLIST OF MEDICINES IN STOCK"<<endl;
	cout<<"S.no\t\tNAME\t\tQUANTITY\tPRICE(INR)\n";

	while(f.read((char*) &med, sizeof(medicine)))
	{
		med.showDetails();	
	}
	f.close();
}

void remMed()
{
	
}

void sellMed()
{
	showMed(); //shows list of all medicines from Medicines.dat
	
	//select medicine using K, take input of quantity, show Cost, confirm
	int k, q, c;
	cout<<endl<<"Enter Medicine Serial Number: ";
	pinput(k, countMed()-1, 1); 
	cout<<"Enter Quantity of Item: ";
	pinput(q, 100, 1); //upper limit to be CHANGED to quantity of list item
	
	f.open("Medicines.dat", ios::in | ios::binary);
	f.seekg((k-1)*sizeof(med), ios::beg); //put read pointer of given s.no. list item
	f.read((char*) &med, sizeof(medicine));
	
	cout<<endl<<"Cost (INR): "<<q*med.rPrice();
	
	cout<<"\nConfirm? Yes(1) / No(0): ";
	pinput(c, 1, 0);
	if(!c)
	{
		f.close();
		sellMed();
		return;
	}
	
	f.close();
	
	//open Medicines.dat
	//searh for MID
	//modify quantity | if quantity = total quantity => remove med from list | DO WITH remMed()
	//if things go good, show confirm message

}
int getInt()
{
	
}
void addMed()
{
	med.getDetails();
	f.open("Medicines.dat", ios::app | ios::in | ios::binary);
	f.write((char* ) &med, sizeof(medicine));
	f.close();
	
	menuV();
}



void menuV()
{
	int c;
	cout<<"\nShow Menu? Yes(1) / No(0): ";
	pinput(c, 1, 0);
	if(c) menu();
}


void menu()
{
	
	cout<<endl<<"Menu"<<endl;
	
	//view choices
	cout<<"1. Sell\n"<<"2. Add\n"<<"3. Remove\n"<<"4. View\n";

	//select choice
	cout<<endl<<"Enter Your Choice: ";
	pinput(choice, 4, 1);
	
	
	//execute
	if(choice==1)
	{
		sellMed();
		menuV();
	}
	else if(choice==2) addMed();
//	else if(choice==3) remMed();
	else if (choice==4) //show medicine list
	{
		showMed();
		menuV();
	}
}


int main()
{
	cout<<"Welcome to Pharmacy Manager"<<endl;
	menu();
	
	cout<<"\nThank You For Using Pharmacy Manager\nPress Any Key to Exit...";
	
	//getchar(); //for pause before termination
	return 0;
}


