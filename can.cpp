//#include<conio.h>
#include<stdio.h>
//#include<process.h>
#include<iostream>
#include<fstream>
using namespace std;
//***************************************************************
// CLASS USED
//****************************************************************
class product
{
	int pno;
	char name[50];
	float price,qty,tax;
	public:
	void add_product()
	{
	cout<<"\nPlease Enter The Product No. of The Product : ";
	cin>>pno;
	cout<<"\n\nPlease Enter The Name of The Product : ";
	cin>>name;
	cout<<"\nPlease Enter The Price of The Product : ";
	cin>>price;
	}
	void show_product()
	{
	cout<<"\nThe Product No. of The Product : "<<pno;
	cout<<"\nThe Name of The Product : ";
	puts(name);
	cout<<"\nThe Price of The Product : "<<price;
	}
	int retpno()
	{
		return pno;
	}
	float retprice()
	{
	return price;
	}
	char* retname()
	{
	return name;
	}
}; // CLASS ENDS HERE
//***************************************************************
// GLOBAL DECLARATION FOR STREAM OBJECT
//****************************************************************
fstream fp;
product pr;
//***************************************************************
// FUNCTION TO WRITE IN THE FILE
//****************************************************************
void write_product()
{
    int n;
	fp.open("Canteen.dat",ios::out|ios::app);
	cout<<"How many Product";
	cin>>n;
	for(int i=1;i<=n;i++)
    {
	pr.add_product();
	fp.write((char*)&pr,sizeof(product));
	fp.close();
    }
	cout<<"\n\nThe Product Has Been Added ";

}
//***************************************************************
// FUNCTION TO READ ALL RECORDS FROM FILE
//****************************************************************
void display_all()
{

	cout<<"\n\n\n\t\tDISPLAY ALL RECORD\n\n";
	fp.open("Canteen.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		pr.show_product();
	cout<<"\n\n====================================\n";

	}
	fp.close();

}
//***************************************************************
// FUNCTION TO READ SPECIFIC RECORD FROM FILE
//****************************************************************
void display_sp(int n)
{
	int flag=0;
	fp.open("Canteen.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(product)))
	{
	if(pr.retpno()==n)
	{

	pr.show_product();
	flag=1;
	}
	}
	fp.close();
	if(flag==0)
	cout<<"\n\nSorry !!! Record not exist";

}
//***************************************************************
// FUNCTION TO MODIFY RECORD OF FILE
//****************************************************************
void modify_product()
{
int no,found=0;

cout<<"\n\n\tMODIFY PRODUCT";
cout<<"\n\n\tPlease Enter The Product Number : ";
cin>>no;
fp.open("Canteen.dat",ios::in|ios::out);
while(fp.read((char*)&pr,sizeof(product)) && found==0)
{
if(pr.retpno()==no)
{
pr.show_product();
cout<<"\nPlease Enter The New Details of Product"<<endl;
pr.add_product();
//int pos=-1*sizeof(pr);
fp.seekp(-1*sizeof(pr),ios::cur);
fp.write((char*)&pr,sizeof(product));
cout<<"\n\n\t Record Updated Successfuly";
found=1;

}
}
fp.close();
if(found==0)
cout<<"\n\n Sorry !!! Record Not Found ";

}
//***************************************************************
// FUNCTION TO DELETE A PRODUCT
//****************************************************************
void delete_product()
{
int no;

cout<<"\n\n\n\nDELETE PRODUCT";
cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete : ";
cin>>no;
fp.open("Canteen.dat",ios::in|ios::out);
fstream fp2;
fp2.open("Temp.dat",ios::out);
fp.seekg(0,ios::beg);
while(fp.read((char*)&pr,sizeof(product)))
{
if(pr.retpno()!=no)
{
fp2.write((char*)&pr,sizeof(product));
}
}
fp2.close();
fp.close();
remove("Canteen.dat");
rename("Temp.dat","Canteen.dat");
cout<<"\n\n\tRecord Deleted Successfully ...";

}
//***************************************************************
// FUNCTION TO DISPLAY THE PRICE LIST
//****************************************************************
void menu()
{

fp.open("Canteen.dat",ios::in);
if(!fp)
{
cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n First Add A Product";
cout<<"\n\n\n Program is closing ....";

//exit(0);
return;
}
cout<<"\n\n\t\tProduct MENU\n\n";
cout<<"====================================================\n";
cout<<"P.NO.\t\tNAME\t\tPRICE\n";
cout<<"====================================================\n";
while(fp.read((char*)&pr,sizeof(product)))
{
cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl
;
}
fp.close();
}
//***************************************************************
// FUNCTION TO PLACE ORDER AND MAKE BILL
//****************************************************************
void place_order()
{
int order_arr[50],quan[50],c=0;
float amt,total=0;
char ch='Y';
menu();
cout<<"\n============================";
cout<<"\n PLACE YOUR ORDER";
cout<<"\n============================\n";
do
{
cout<<"\n\nEnter The Product No. Of The Product : ";
cin>>order_arr[c];
cout<<"\nEnter The Quantity : ";
cin>>quan[c];
c++;
cout<<"\nDo You Want To Order More Products ? (y/n) : ";
cin>>ch;
}
while(ch=='y' ||ch=='Y');
cout<<"\n\n******************************** BILL************************\n";
for(int x=0;x<=c;x++)
{
fp.open("Canteen.dat",ios::in);
fp.read((char*)&pr,sizeof(product));
while(!fp.eof())
{
if(pr.retpno()==order_arr[x])
{
amt=pr.retprice()*quan[x];
cout<<"\nProduct Number : "<<order_arr[x]
<<"\nProduct Name : " <<pr.retname() <<"\nQuantity : "<<quan[x]
<<"\nPrice : " <<pr.retprice();
total=amt;
}
fp.read((char*)&pr,sizeof(product));
}
fp.close();
}
cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
cout<<"\n\n\n\nTHANK YOU FOR PLACING ORDER";

}
//***************************************************************
// ADMINISTRATOR MENU FUNCTION
//****************************************************************
void admin_menu()
{

char ch2;
cout<<"\n\n\n\tADMINISTRATOR MENU";
cout<<"\n\n\t1.ADD PRODUCT";
cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
cout<<"\n\n\t3.PRODUCT DETAILS ";
cout<<"\n\n\t4.MODIFY PRODUCT";
cout<<"\n\n\t5.DELETE PRODUCT";
cout<<"\n\n\t6.VIEW PRODUCT MENU";
cout<<"\n\n\t7.BACK TO MAIN MENU";
cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
cout<<"\n Enter Choice:";
cin>>ch2;
//ch2=getche();
switch(ch2)
{
case '1':

write_product();
break;
case '2':
display_all();

break;
case '3':
	 int num;

cout<<"\n\n\tEnter The Product No : ";
cin>>num;
display_sp(num);
break;
case '4':
modify_product();
break;
case '5':
	delete_product();
break;
case '6':
		menu();
		//
case '7':

	break;
default:
cout<<"\a";
admin_menu();
}
}
//***************************************************************
// THE MAIN FUNCTION
//****************************************************************
int main()
{
char ch;
do
{

cout<<"\n\n\n*******************************CANTEEN MANAGEMENT*******************************";
cout<<"\n\n\n\tMAIN MENU";
cout<<"\n\n\t01. CUSTOMER";
cout<<"\n\n\t02. ADMINISTRATOR MENU";
cout<<"\n\n\t03. EXIT";
cout<<"\n\n\tPlease Select Your Option (1-3) : ";
cin>>ch;
switch(ch)
{
case '1':
place_order();

break;
case '2': admin_menu();
break;
case '3': cout<<"\n\nThank You Visit Again...";
cout<<"\n\nMADE BY : RAHUL POMNAR";
cout<<"\n\nCOLLAGE : viit pune.";

return 0;
default :cout<<"\a";
}
}
while(ch!='3');
}
//***************************************************************
// END OF PROJECT
//***************************************************************
