#include<iostream>						//Aim- to send data of object in file
#include<fstream>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
using namespace std;
class Book
{int bookno;
char title[20];
float price;
public:
	Book()
	{bookno=0;
	strcpy(title,"no title");
	price=0;}
	
	void getdetails()								//to get details of book
	{cout<<"enter the bookno of your book"<<endl;
	cin>>bookno;
	cin.ignore();									//it empty buffers
	cout<<"enter the title of your book"<<endl;
	cin.getline(title,19);
		cout<<"enter the price of your book"<<endl;
	cin>>price;}
	
	void showdetails()									//to show details of book
	{cout<<bookno<<"  "<<title<<"   "<<price<<endl;
	}

	int senddetails();
	void showbooks();
	void searchbooks(char *);
	void updateBook(char *);
	void deleteBook(char *);
	
};
void Book::deleteBook(char *t)							//to delete record in file
{
	ofstream fout;
	ifstream fin;
	fin.open("book.dat",ios::in|ios::binary);
	if(!fin)
	cout<<"\n FILE NOT FOUND   ";
	else
	fout.open("tempfile.dat",ios::out|ios::binary);
while(!fin.eof())
	{if(strcmp(t,title))
{	fout.write((char *)this,sizeof(*this));}
	fin.read((char *)this,sizeof(*this));
}
	fin.close();
	fout.close();
	remove("amar.dat");
	rename("tempfile.dat","amar.dat");
	fin.close();
	fout.close();
}
	void Book::updateBook(char *t)					//to update record in file
	{fstream file;
		file.open("book.dat",ios::in|ios::out|ios::ate|ios::binary);
		file.seekp(0);
		file.read((char*)this,sizeof(*this));
while(!file.eof())
	{if(!strcmp(t,title))
	{
		cout<<"\nENTER THE  NEW DETAILS OF BOOK   ";
		getdetails();
		file.seekp((file.tellp()- 1));
		file.write((char*)this,sizeof(*this));
		file.read((char*)this,sizeof(*this)); }
		}
	}

	int Book::senddetails()						//send details of book to file
		{if(price==0&&bookno==0)
		{cout<<"books data are no initialised";
		return 0;
		}
	else{
	
		ofstream fout;
		fout.open("book.dat",ios::app|ios::binary);
		fout.write((char *)this,sizeof(*this));					//stores data of object in file
		fout.close();
		return 1;}
	}

	void Book::showbooks()								//to read all records from file
		{ifstream fin;
		fin.open("book.dat",ios::in|ios::binary);
	if(!fin)
		cout<<"FILE NOT FOUND  ";
	else{
		fin.read((char*)this,sizeof(*this));
		while(!fin.eof())
		{showdetails();
		fin.read((char*)this,sizeof(*this)); }
	}
	
	}
	
	void Book::searchbooks(char *t)						//to search record in file
		{int counter=0;
		ifstream fin;
		fin.open("book.dat",ios::in|ios::binary);
	if(!fin)
		cout<<"\nFILE NOT FOUND ";
	else{
		fin.read((char*)this,sizeof(*this));
		if(!strcmp(t,title))
		{showdetails();
		counter++;
		}
		fin.read((char*)this,sizeof(*this));
		if(counter==0)
		cout<<"\nRECORD DOES NOT EXIST ";	}
		fin.close();
	}
	int menu()
	{int choice;
	cout<<"\n1.		CREATE NEW BOOK DETAILS ";
	cout<<"\n2.		VIEW DETAILS ";
	cout<<"\n3.  	SEARCH BOOK ";
	cout<<"\n4.  	UPDATE BOOK RECORD ";
	cout<<"\n5.		DELETE BOOK RECORD ";
	cout<<"\n6.		EXIT ";
	cout<<"\nENTER YOUR CHOICE ";
	cin>>choice;
	return(choice);
	}
int main()
{Book b1;
char title[20];
cout<<"	================================================================ ";
cout<<"					   	WELCOME										 ";
cout<<"==================================================================";
while(1){
switch(menu())
{	case 1:	
			b1.getdetails();
			b1.senddetails();
			cout<<"\nYOUR RECORD IS INSERTED   ";
			break;
	case 2:
			b1.showbooks();
			break;
	case 3:
			cout<<"\nENTER THE BOOK TITLE YOU WANT TO SEARCH  ";
			cin.ignore();
			cin.getline(title,19);
			b1.searchbooks(title);
			break;
	case 4:
			cout<<"\nENTER THE TITLE OF BOOK WHICH YOU WANT TO UPDATE  ";
			cin.ignore();
			cin.getline(title,19);
			b1.updateBook(title);
			break;
			case 5:
				cout<<"\nENTER THE TITLE OF BOOK WHICH YOU WANT TO DELETE ";
				cin.ignore();
				cin.getline(title,19);
				b1.deleteBook(title);
				cout<<"AFTER DELETION  NEW RECORDS ARE ";
				b1.showbooks();
				break;
				
	case 6:
		cout<<"\nTHANKS FOR YOUR COMING ";
		cout<<"\nENTER ANY TO EXIT  ";
		getch();
		exit(0);
	default:
		cout<<"\nINVALID CHOICE    ";
}

}

return 0;

}
