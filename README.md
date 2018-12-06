# Pharmacy
#### A basic program for a Pharmacy for handling drugs and their storage and expiration.

## About Program
### Classes
`medicine` class
- #### Data Members: (52 bytes)
  - `private int K` : Serial Number of Medicine
  - `private char name[20]` : Name of Medicine
  - `private int quantity` : Stock Quantity of Medicine
  - `private float u_price` : Price of One Unit
  - `private float t_price` : Total Price of the Item (i.e `t_price = quantity*u_price`)
  - `private int m_m` : Month of Manufacture
  - `private int m_y` : Year of Manufacture
  - `private int e_m`: Month of Expiry
  - `private int e_y` : Year of Expiry

- #### Member Functions
  - `public void getDetails()` :
  - `public void showDetails()` :
  - `public float rPrice()` :
  - `public int rQuantity()` :
  - `public int rK()` :
  - `public void changeK(int newK)` :
  - `public void decQuantity(int dQ)` :
  
### Global Variables
- `fstream f` :
- `fstream t` :
- `int choice` :
- `medicine med` :

### Global Functions
- `void menu()` :
- `void menuV()` :
- `int countMed()` :
- `void pinput(int &v,int u, int l)` :
- `void pfinput(float &v,float u, float l)` :
- `void showMed()` :
- `void delMed(int remK)` :
- `void remMed()` :
- `void sellMed()` :
- `void addMed()` :


## Info
- Compiler: GCC 4.9.2 Release (C++ 11)

