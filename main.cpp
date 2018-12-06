//using compiler config TDM GCC 4.9.2 Release (C++11)
#include <iostream>
#include <fstream>
//#include <stdlib.h>
#include <string.h>
#include <ctime>

using namespace std; //Otherwise use std::cout etc.

//file streams
fstream f;
fstream t;

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
		
//CLASSES
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
		int rQuantity() //accesor function
		{
			return quantity;
		}
		int rK() //accessor functino
		{
			return K;
		}
		void changeK(int newK)
		{
			K = newK;
		}
		void decQuantity(int dQ)
		{
			quantity-= dQ;
		}
		char* rName()
		{
			return name;
		}
} med;


//GLOBAL FUNCTIONS
int nameID(char medN[20])
{	
	int medK,flag=1;
	f.open("Medicines.dat", ios::in | ios::binary);
	while(f.read((char*) &med, sizeof(medicine)))
	{
		if(!strcmp(medN, med.rName()))
		{
			flag=0;
			medK = med.rK();
			f.close();
			return medK;
		}
	}
	if(flag)
	{
		f.close();
		cout<<"\nMedicine Not Found";
		return 0;
	}
}
int countMed() //returns total list items + 1
{
	int k=0;
	f.open("Medicines.dat", ios::in | ios::binary);
			
	while(f.read((char*) &med, sizeof(medicine)))
	{
		k++;	
	}
	f.close();
	k++; //do not remove this, this is for addition of first medicine		
	return k;
}
float countWorth() //returns total worth of stock
{
	float w=0;
	f.open("Medicines.dat", ios::in | ios::binary);
	
	while(f.read((char*) &med, sizeof(medicine)))
	{
		w+=med.rQuantity*med.rPrice();
	}
	f.close();
	return w;
}
int countQuantity() //returns total stock quantity
{
	int q=0;
	f.open("Medicines.dat", ios::in | ios::binary);

	while(f.read((char*) &med, sizeof(medicine)))
	{
		q+=med.rQuantity();
	}
	f.close();
	return q;
}
void showMed() //shows all medicine in list
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
void delMed(int remK) //Removes Entry List using Med Serial No.(assumes paramter input is already verified)
{
	f.open("Medicines.dat", ios::in | ios::binary);
	f.seekg(0, ios::beg);
	t.open("temp.dat", ios::out | ios::binary);
	
	while(f.read((char*) &med, sizeof(medicine)))
	{
		if(med.rK()!=remK)	
		{
			t.write((char* ) &med, sizeof(medicine));
		}
	}
	f.close();
	t.close();
	
	remove("Medicines.dat");
	rename("temp.dat", "Medicines.dat");
}
void remMed()
{
	showMed();
	int remK=0, c;
	char medN[20];
	
	//Name-ID Options
	cout<<endl<<"Select Medicine using: "<<"\n1. Serial Number"<<"\n2. Name"<<"\nChoice: ";
	pinput(choice, 2, 1);
	if(choice==2)
	{
		while(!remK)
		{
			cout<<endl<<"Enter Medicine Name to remove: ";
			gets(medN);
			remK = nameID(medN);
		}
	}
	else
	{
		cout<<endl<<"Enter Medicine Serial Number to remove: ";
		pinput(remK, countMed()-1, 1); //countMed()-1 is used instead of countMed only - refer to the definition of countMed()
	}
	
	//confirm
	cout<<"\nConfirm? Yes(1) / No:-Change Choice(0): ";
	pinput(c, 1, 0);
	if(!c)
	{
		remMed();
		return;
	}
	
	delMed(remK);
	
	//to correct the Medicine serial number values MODIFY
	f.open("Medicines.dat", ios::in | ios::out | ios::binary);
	f.seekg(0, ios::beg);
	int pos;
	c=1;
	for(;;)
	{
		pos = f.tellg();
		if(f.read((char*) &med, sizeof(medicine)))
		{
			med.changeK(c);
			
			f.seekg(pos);
			f.write((char*) &med, sizeof(medicine));
			
			f.seekg(pos+sizeof(medicine));
			c++;
			continue;
		}
		else
		{
			break;
		}
	}
	f.close();
	
	showMed();
	cout<<"\nMedicine Removed from List";
	
	menuV();
}
void sellMed()
{
	showMed();
	int sellK=0, sellQ, c;
	char medN[20];

	//Name-ID Option
	cout<<endl<<"Select Medicine using: "<<"\n1. Serial Number"<<"\n2. Name"<<"\nChoice: ";
	pinput(choice, 2, 1);
	if(choice==2)
	{
		while(!sellK)
		{
			cout<<endl<<"Enter Medicine Name to sell: ";
			gets(medN);
			sellK = nameID(medN);
		}
	}
	else
	{
		cout<<endl<<"Enter Medicine Serial Number to sell: ";
		pinput(sellK, countMed()-1, 1); //countMed()-1 is used instead of countMed only - refer to the definition of countMed()
	}
	
	//Show list item and price
	f.open("Medicines.dat", ios::in | ios::binary);
	f.seekg((sellK-1)*sizeof(med), ios::beg); //put read pointer of given s.no. list item
	f.read((char*) &med, sizeof(medicine));
	
	cout<<"\nMedicine Found\n";
	cout<<"S.no\t\tNAME\t\tQUANTITY\tPRICE(INR)\n";
	med.showDetails();
	
	cout<<"Enter Quantity of Item: ";
	pinput(sellQ, med.rQuantity(), 1);
	cout<<endl<<"Cost (INR): "<<sellQ*med.rPrice();
	
	//confirm
	cout<<"\nConfirm? Yes(1) / No(0): ";
	pinput(c, 1, 0);
	if(!c)
	{
		f.close();
		sellMed();
		return;
	}
	
	//change-quantity-in-file
	if(sellQ == med.rQuantity())
	{
		c = sellK;
		f.close();
		delMed(c);
		
		f.open("Medicines.dat", ios::in | ios::out | ios::binary);
		f.seekg(0, ios::beg);
		int pos;
		c=1;
		for(;;)
		{
			pos = f.tellg();
			if(f.read((char*) &med, sizeof(medicine)))
			{
				med.changeK(c);
			
				f.seekg(pos);
				f.write((char*) &med, sizeof(medicine));
			
				f.seekg(pos+sizeof(medicine));
				c++;
				continue;
			}
			else
			{
				break;
			}
		}
		f.close();
	}
	else
	{
		f.open("Medicines.dat", ios::in | ios::out | ios::binary);
		f.seekg((sellK-1)*sizeof(med), ios::beg);
		f.read((char*) &med, sizeof(medicine));
		
		med.decQuantity(sellQ);
		f.close();
		//BUG
		f.open("Medicines.dat", ios::out | ios::binary);
		f.seekg((sellK-1)*sizeof(medicine), ios::beg);
		f.write((char*) &med, sizeof(medicine));
		f.close();
		
	}
	
	showMed();
	cout<<"\nTransaction Complete";

	menuV();
}
void addMed() //addition
{
	med.getDetails();
	f.open("Medicines.dat", ios::app | ios::in | ios::binary);
	f.write((char* ) &med, sizeof(medicine));
	f.close();
	
	menuV();
}
void searchMed() //search by name
{
	char medN[20];
	int flag=1;
	cout<<"Enter name of Medicine to Seach: ";
	gets(medN);
	
	f.open("Medicines.dat", ios::in | ios::binary);
	while(f.read((char*) &med, sizeof(medicine)))
	{
		if(!strcmp(medN, med.rName()))
		{
			flag=0;
			cout<<"\nMedicine Found\n";
			cout<<"S.no\t\tNAME\t\tQUANTITY\tPRICE(INR)\n";
			med.showDetails();
		}
	}
	if(flag)
	{
		cout<<"\nMedicine NOT Found\n";
	}
	f.close();
	
	menuV();
}
void ovMed() //full overview
{
	cout<<"\nOVERVIEW:\n";
	cout<<"TOTAL ITEMS\t\tTOTAL WORTH\t\tTOTAL STOCK\n";
	cout<<countMed()-1<<"\t\t\t"<<countWorth()<<"\t\t\t"<<countQuantity()<<endl;
}

//MENU FUNCTIONS
void menuV()
{
	int c;
	cout<<"\nShow Menu? Yes(1) / Exit(0): ";
	pinput(c, 1, 0);
	if(c) menu();
}
void menu()
{
	cout<<endl<<"Menu"<<endl;
	//view choices
	cout<<"1. Sell\n"<<"2. Add\n"<<"3. Remove\n"<<"4. Search\n"<<"5. Overview\n";
	//select choice
	cout<<endl<<"Enter Your Choice: ";
	pinput(choice, 5, 1);
	//execute
	if(choice==1) sellMed();
	else if(choice==2) addMed();
	else if(choice==3) remMed();
	else if(choice==4) searchMed();
	else if(choice==5) //show medicine list
	{
		ovMed();
		showMed();
		menuV(); //because showMed() can be called by other functions
				//and menu cannot be shown everytime it is called
	}
}

int main()
{
	cout<<"Welcome to Pharmacy Manager"<<endl;
	menu();
	cout<<"\nThank You For Using Pharmacy Manager\nPress Any Key to Exit...";
	getchar(); //for pause before termination
	return 0;
}


