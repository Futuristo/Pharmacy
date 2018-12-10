#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

fstream f;
fstream t;

//global function prototypes
void menu();
void menuV();
int countMed();

//global var
int choice;

//functions for conditional input
void pinput(int &v,int u, int l)
{
 while((!(cin>>v)) || v<l || v>u)
	{
		cout<<"Enter Correct Value: ";
		cin.clear();
		cin.ignore(100,'\n');
	}
	cin.ignore(1,'\n');
}
void pfinput(float &v,float u, float l)
{
 while((!(cin>>v)) || v<l || v>u)
	{
	cout<<"Enter Correct Value: ";
	cin.clear();
	cin.ignore(100,'\n');
	}
	cin.ignore(1,'\n');
}

//CLASSES
class medicine
{
	int K;
	char name[20];
	int quantity;
	float u_price;
	
	public:

		void getDetails()
		{
			cout<<endl<<"Enter details about medicine: "<<endl;

			K = countMed();
			cout<<"Enter Name: ";
			gets(name);
			cout<<"Enter Quantity(in units): ";
			pinput(quantity, 100, 1);
			cout<<"Enter Price of 1 unit(INR): ";
			pfinput(u_price, 10000, 1);
		}
		void showDetails()
		{
			cout<<K<<"\t\t"<<name<<"\t\t"<<quantity<<"\t\t"<<u_price<<endl;
		}
		float rPrice()
		{
			return u_price;
		}
		int rQuantity()
		{
			return quantity;
		}
		int rK()
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
int countMed()
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
float countWorth()
{
	float w=0;
	f.open("Medicines.dat", ios::in | ios::binary);
	while(f.read((char*) &med, sizeof(medicine)))
	{
		w+=med.rQuantity()*med.rPrice();
	}
	f.close();
	return w;
}
int countQuantity()
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
void showMed()
{
	f.open("Medicines.dat", ios::in | ios::binary);

	cout<<"\nLIST OF MEDICINES IN STOCK"<<endl;
	cout<<"S.no\t\tNAME\t\tQUANTITY\tPRICE(INR)\n";

	while(f.read((char*) &med, sizeof(medicine)))
	{
		med.showDetails();
	}
	f.close();
}
void delMed(int remK)
{
	f.open("Medicines.dat", ios::in | ios::binary);
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
		pinput(remK, countMed()-1, 1);
	}
	
	cout<<"\nConfirm? Yes(1) / No:-Change Choice(0): ";
	pinput(c, 1, 0);
	if(!c)
	{
		remMed();
		return;
	}

	delMed(remK);

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
		pinput(sellK, countMed()-1, 1);
	}

	f.open("Medicines.dat", ios::in | ios::binary);
	f.seekg((sellK-1)*sizeof(med), ios::beg);
	f.read((char*) &med, sizeof(medicine));

	cout<<"\nMedicine Found\n";
	cout<<"S.no\t\tNAME\t\tQUANTITY\tPRICE(INR)\n";
	med.showDetails();

	cout<<"Enter Quantity of Item: ";
	pinput(sellQ, med.rQuantity(), 1);
	cout<<endl<<"Cost (INR): "<<sellQ*med.rPrice();

	cout<<"\nConfirm? Yes(1) / No(0): ";
	pinput(c, 1, 0);
	if(!c)
	{
		f.close();
		sellMed();
		return;
	}

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
		
		f.open("Medicines.dat", ios::in |ios::out | ios::binary);
		f.seekg((sellK-1)*sizeof(medicine), ios::beg);
		f.write((char*) &med, sizeof(medicine));
		f.close();

	}

	showMed();
	cout<<"\nTransaction Complete";

	menuV();
}
void addMed()
{
	med.getDetails();
	f.open("Medicines.dat", ios::app | ios::in | ios::binary);
	f.write((char* ) &med, sizeof(medicine));
	f.close();

	menuV();
}
void searchMed()
{
	char medN[20];
	int flag=1;
	cout<<"Enter name of Medicine to Search: ";
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
void ovMed()
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
	cout<<"1. Sell\n"<<"2. Add\n"<<"3. Remove\n"<<"4. Search\n"<<"5. Overview\n";
	cout<<endl<<"Enter Your Choice: ";
	pinput(choice, 5, 1);
	if(choice==1) sellMed();
	else if(choice==2) addMed();
	else if(choice==3) remMed();
	else if(choice==4) searchMed();
	else if(choice==5)
	{
		ovMed();
		showMed();
		menuV();
	}
}

int main()
{
	cout<<"Welcome to Pharmacy Manager"<<endl;
	cout<<"BY Shashank Sengar, 12th-C"<<endl;
	menu();
	cout<<"\nThank You For Using Pharmacy Manager\nPress Any Key to Exit...";
	getchar();
	return 0;
}

