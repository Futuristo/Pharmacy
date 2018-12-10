# Pharmacy
#### A basic program for a Pharmacy for handling drugs and their storage and transactions.

## About Program
### Classes
`medicine` class
- #### Data Members: (32 bytes)
  - `private int K` : Serial Number of Medicine
  - `private char name[20]` : Name of Medicine
  - `private int quantity` : Stock Quantity of Medicine
  - `private float u_price` : Price of One Unit
  
- #### Member Functions (8 functions)
  - `public void getDetails()`
  - `public void showDetails()`
  - `public float rPrice()`
  - `public int rQuantity()`
  - `public int rK()`
  - `public void changeK(int newK)`
  - `public void decQuantity(int dQ)`
  - `public char* rName()`
  
### Global Variables
- `fstream f`
- `fstream t`
- `int choice`
- `medicine med`

### Global Functions (15)
- `void menu()`
- `void menuV()`
- `int countMed()`
- `void pinput(int &v,int u, int l)`
- `void pfinput(float &v,float u, float l)`
- `int nameID(char medN[20])`
- `float countWorth()`
- `int countQuantity()`
- `void showMed()`
- `void delMed(int remK)`
- `void remMed()`
- `void sellMed()`
- `void addMed()`
- `void searchMed()`
- `void ovMed()`


## Info
- Compiler: GCC 4.9.2 Release (C++ 11)

