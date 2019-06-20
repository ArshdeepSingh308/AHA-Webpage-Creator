#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
using namespace std;
//Function Prototypes
void main_temp1();
void main_temp2();
void main_temp3();
void main_homescreen_calling();
void main_see_webcreate();
void main_web_create();
void main_see_temp();
void main_login();
// Class definition for SIGN UP FUNCTIONS
class sign_up
{
	private:
		char name[40];
		char email[40];
		char password[40];
		char month[40];
		int year;
		int date;
		char gender[40];
		long long int phoneno;
		char location[40];
	public:
		void getdata();
		void putdata();
		char* retemail()
		{
			return email;
		}
};
// Function to return password given by user
char *getpass()
{
     char c;
     char pass[30];
     int i=0;
     while(1)
     {
             c=getch();
             if(c!=13&&c!='\b')
             {
                               pass[i++]=c;
                               cout<<"*";
             }
             else if (c==13)
             {
                  pass[i]='\0';
                  return pass;
             }
             else if (c=='\b'&&i>0)
             {
                  i--;
                  cout<<"\b \b";
             }
     }
} 
// Function to enter the details for SIGN UP
void sign_up::getdata()
{
	cout<<"Fill in your particulars and get started : "<<"\n"<<"\n";
	cout<<"Name :- ";
	cin>>name;
	cout<<"Email :- ";
	cin>>email;
	cout<<"Password :- ";
	strcpy(password,getpass());
	cout<<"\nDate of Birth (yyyy/mm/dd) :- "<<"\n";
	cout<<"Year- ";
	cin>>year;
	cout<<"Month- ";
	cin>>month;
	cout<<"Date- ";
	cin>>date;
	cout<<"Gender :- ";
	cin>>gender;
	cout<<"Phone No. :- ";
	cin>>phoneno;
	cout<<"Location :- ";
	cin>>location;
}
// Function to display the details of user
void sign_up::putdata()
{
	cout<<"Your Account Details are as follows :"<<"\n"<<"\n";
	cout<<"\n"<<"NAME : "<<name<<"\n";
	cout<<"EMail : "<<email<<"\n";
	cout<<"DATE OF BIRTH : "<<year<<"/"<<month<<"/"<<date<<"\n";
	cout<<"GENDER : "<<gender<<"\n";
	cout<<"PHONE NO. : "<<phoneno<<"\n";
	cout<<"LOCATION : "<<location<<"\n";
}
// Function to write the details in the binary file
void write( )
{   
    ofstream fin("database.dat", ios::binary|ios::app);
    sign_up s;
    s.getdata( );
	fin.write((char*)&s,sizeof(s));
    fin.close( );
}
// Function to display the details from the binary file
void display()
{
	fstream f("database.dat",ios::in|ios::binary);
	sign_up s;
	char email[40]; int flag=0;
	cout<<"\n"<<"Enter Your Email : ";
	cin.ignore();
	cin.getline(email,40);
	while(f.read((char*)&s,sizeof(s)))
	{
		if(strcmpi(s.retemail(),email)==0)
		{
			flag=1;
			s.putdata();
			break;
		}
	}
	f.close();
	if(flag==0)
	cout<<"Record Not Found !"<<"\n";
}
// Function to delete a record from the binary file
void del()
{
	char email[40];
	cout<<"\n"<<"Enter the email for which you want to delete the account: ";
	cin.ignore();
	cin.getline(email,40);
	fstream f1("database.dat",ios::in|ios::binary);
	fstream f2("temporary.dat",ios::out|ios::app|ios::binary);
	sign_up s;
	while(f1.read((char*)&s,sizeof(s)))
	{
		if(strcmpi(s.retemail(),email)!=0)
		f2.write((char*)&s,sizeof(s));
	}
	f1.close();
	f2.close();
	remove("database.dat");
	rename("temporary.dat","database.dat");
}
// Switch Case for calling SIGN UP functions
void switchforsign_up()
{
	int ch;
	do
	{
		cout<<"\n"<<"MENU:"<<"\n";
		cout<<"0. Return To the Login Window"<<"\n";
		cout<<"1. Create a new Account"<<"\n";
		cout<<"2. View your Account Details"<<"\n";
		cout<<"3. Delete your existing Account"<<"\n";
		cout<<"\n"<<"Enter your Choice Number= ";
		cin>>ch;
		switch(ch)
		{
			case 1:	write();
					break;
			case 2: display();
					getch();
					system("cls");
					break;
			case 3: cout<<"Deletion of Account : ";
					del();
					break;
			case 0 :break;
		}
	}while(ch!=0);
}
// Class definition for LOGIN FUNCTIONS
class login_details
{
	public:
		char name[40];
		char email[40];
		char password[40];
		char month[40];
		int year;
		int date;
		char gender[40];
		long long int phoneno;
		char location[40];
};
//Function for comapring the EMail ID and Password (LOGIN window)
void login()
{
     int flg=0;
     char username[40],password[40],temp[40];
     login_details s;
     cout<<"Enter Login ID : ";
     cin>>username;
     ifstream fin("database.dat",ios::binary);
     while(fin.read((char*)&s,sizeof(s)))
     {
         if(strcmpi(username,s.email)==0)
         {
              strcpy(temp,s.password);
              flg=1;
         }                                                       
     }
     if(flg==0)
     {
        cout<<"Email does not exist."<<endl<<"\n";     
        cout<<"Create a new account and try again later."<<"\n";
        cout<<"THANK YOU."<<"\n"<<"\n";
        getch();
        system("cls");
        cout<<"TO CREATE YOUR ACCOUNT FOLLOW THESE STEPS : ";
        switchforsign_up();
     }
    else
    {
     	cout<<"Enter Password : ";
     	strcpy(password,getpass());
    	if(strcmp(password,temp)==0)
     	{
        	cout<<"\n"<<"LOGIN SUCCESSFUL !"<<endl<<"\n";
         	cout<<"You  Will be Transpotred to the HOMEPAGE of Our site."<<"\n";
         	getch();
         	system("cls");
         	main_homescreen_calling();
     	 }
     	if(strcmp(password,temp)!=0)
     	{
     		cout<<"LOGIN FAILED !"<<endl<<endl; 
        	cout<<"The ID or the Password is incorrect."<<"\n";
			cout<<"Please try again later."<<"\n"<<"THANK YOU"<<"\n";
     	}
   	}
}
//Function for Re-Login (if login attemp fails)
void askagain()
{
	char resp;
   	cout<<"\n"<<"Do you want to Login Now. [Yes(y) or No(n)] : ";
   	cin>>resp;
   	getch();
   	system("cls");
	if(resp=='y')
    login();
    else
    cout<<"\n"<<"\n"<<"\t"<<"\t"<<"**THANK YOU FOR USING OUR PRODUCT.**";	
}
//Switch Case for Calling the LOGIN and SIGN UP Functions
void switchcalling_firstscreen()
{
    cout<<"*******************************************************************************"<<"\n"<<"\n";
    cout<<"\t\t\t ~AHA WEBPAGE CREATOR~ \n";
    cout<<"*******************************************************************************"<<"\n"<<"\n";
	cout<<"Enter the Choice as indicated below :- ";
	int ch;
	do
	{
		cout<<"\n"<<"MENU:"<<"\n"<<"\n";
		cout<<"0. Exit."<<"\n";
		cout<<"1. LOGIN"<<"\n";
		cout<<"2. SIGN UP"<<"\n"<<"\n";
		cout<<"\n"<<"Enter your Choice Number= ";
		cin>>ch;
		cout<<"\n\t\t\t\t **THANK YOU** \n\n";
	    cout<<"*******************************************************************************"<<"\n"<<"\n";
		getch();
		system("cls");
		switch(ch)
		{
			case 1:	login();
					getch();
					system("cls");
					askagain();
					break;
			case 2: switchforsign_up();
					getch();
					system("cls");
					break;
			case 0 :exit(0);
		}
	}while(ch!=0);

}
//Function for calling the LOGIN and SIGN UP Window 
void main_login()
{
    switchcalling_firstscreen();
} 
//Function for providing information to the user
void begin()
{
	cout<<"*******************************************************************************"<<"\n"<<"\n";
    cout<<"\t"<<"\t"<<"\t"<<" ~AHA WEBPAGE CREATOR~ "<<"\n";
    cout<<"*******************************************************************************"<<"\n"<<"\n";
	cout<<"Enter the Choice as indicated below :- ";
	cout<<"WE PROVIDE A WIDE RANGE OF CREATION OF WEBPAGES AS PER THE DEMAND OF THE USER."<<"\n"<<"\n";
	cout<<"\t"<<"   "<<"**HAVE A NICE TIME USING WEBPAGE CREATOR**"<<"\n";
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"**THANK YOU**"<<"\n"<<"\n";
}
//Switch Case for VIEWING TEMPLATES, CREATING WEBPAGES and VIEW THE CREATED PAGES(by user)
void switchcalling()
{
	cout<<"Enter the Choice as indicated below :- ";
	int ch;
	do
	{
		cout<<"\n"<<"MENU:"<<"\n"<<"\n";
		cout<<"0. Exit"<<"\n";
		cout<<"1. VIEW THE TEMPLATES"<<"\n";
		cout<<"2. CREATE WEBPAGES"<<"\n";
		cout<<"3. VIEW THE PAGE CREATED"<<"\n";
		cout<<"\n"<<"Enter your Choice Number= ";
		cin>>ch;
		getch();
		system("cls");
		switch(ch)
		{
			case 1:	main_see_temp();
					break;
			case 2: main_web_create();
					break;
			case 3: main_see_webcreate();
					break;
			case 0 : exit(0);
		}
	}while(ch!=0);
}
//Functions for HOMESCREEN window
void main_homescreen_calling()
{
    begin();
    switchcalling();
    getch();
}
//Function for providing information to the user
void begin_see_temp()
{
cout<<"*******************************************************************************"<<"\n"<<"\n";
    cout<<"\t"<<"\t"<<"\t"<<" ~AHA WEBPAGE CREATOR~ "<<"\n";
    cout<<"*******************************************************************************"<<"\n"<<"\n";
	cout<<"Enter the Choice as indicated below :- ";
	cout<<"Here you will be able to see the alredy created TEMPLATE."<<"\n"<<"\n";
	cout<<"\t"<<"   "<<"**HAVE A NICE TIME USISNG WEBPAGE CREATOR**"<<"\n";
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"**THANK YOU**."<<"\n"<<"\n";
}
//Switch case for viewing the HTML templates
void switchcalling_see_temp()
{
	cout<<"Enter the Choice as indicated below :- ";
	int ch;
	do
	{
		cout<<"\n"<<"MENU:"<<"\n"<<"\n";
		cout<<"0. Return To the Homescreen"<<"\n";
		cout<<"1. Plain Text Webpage. ~ TEMPLATE 1"<<"\n";
		cout<<"2. Webpage with an image and Text. ~ TEMPLATE 2"<<"\n";
		cout<<"3. Webpage with an image, a Table and Text. ~ TEMPLATE 3"<<"\n"<<"\n";
		cout<<"\n"<<"Enter your Choice Number= ";
		cin>>ch;
		getch();
		system("cls");
		switch(ch)
		{
			case 1:	system("Template1.html");
					break;
			case 2: system("Template2.html");
					break;
			case 3: system("Template3.html");
					break;
			case 0 :main_homescreen_calling();
					break;
		}
	}while(ch!=0);
}
//Functions for the TEMPLATE window
void main_see_temp()
{
	begin_see_temp();
	switchcalling_see_temp();
	getch();
}
//Function for providing information to the user
void begin_web_create()
{
	cout<<"*******************************************************************************"<<"\n"<<"\n";
    cout<<"\t"<<"\t"<<"\t"<<" ~AHA WEBPAGE CREATOR~ "<<"\n";
    cout<<"*******************************************************************************"<<"\n"<<"\n";
	cout<<"Enter the Choice as indicated below :- ";
	cout<<"Here you will be able to create your Webpages."<<"\n";
	cout<<"INSTRUCTIONS :- "<<"\n";
	cout<<"\t"<<"1."<<" "<<"Enter the content properly (You will not be allowed to make any changes thereafter)."<<"\n";
	cout<<"\t"<<"2."<<" "<<"Complete the process and do not close the file while execution."<<"\n";
	cout<<"\t"<<"3."<<" "<<"After the procedure is complete. Your webpage will be created."<<"\n"<<"\n";
	cout<<"\t"<<"   "<<"**HAVE A NICE TIME CREATING YOUR WEPAAGE**"<<"\n";
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"**THANK YOU**."<<"\n"<<"\n";
}
//Switch Case for calling the Functions to CREATE THE WEB PAGES
void switchcalling_web_create()
{
	cout<<"Enter the Choice as indicated below :- ";
	int ch;
	do
	{
		cout<<"\n"<<"MENU:"<<"\n"<<"\n";
		cout<<"0. Return To the Homescreen"<<"\n";
		cout<<"1. Create a Plain Text Webpage. (Similar to Template1)"<<"\n";
		cout<<"2. Create a Webpage with an image and Text. (Similar to Template 2)"<<"\n";
		cout<<"3. Create a Webpage with an image, a table and Text. (Similar to Template 3)"<<"\n"<<"\n";
		cout<<"\n"<<"Enter your Choice Number= ";
		cin>>ch;
		getch();
		system("cls");
		switch(ch)
		{
			case 1:	main_temp1();
					break;
			case 2: main_temp2();
					break;
			case 3: main_temp3();
					break;
			case 0: main_homescreen_calling();
					break;
		}
	}while(ch!=0);
}
//Functions for the WEB PAGE CREATION window
void main_web_create()
{
	begin_web_create();
	switchcalling_web_create();
	getch();
}
//Function for providing information to the user
void instructions_temp1()
{
     cout<<"*******************************************************************************"<<"\n"<<"\n";
    cout<<"\t"<<"\t"<<"\t"<<" ~AHA WEBPAGE CREATOR~ "<<"\n";
    cout<<"*******************************************************************************"<<"\n"<<"\n";
	cout<<"Enter the Choice as indicated below :- ";
     cout<<"To create a webpage follow the instructions :-"<<"\n"<<"\n";
     cout<<"*"<<"Enter the appropriate information."<<"\n";
     cout<<"*"<<"If you want to enter the background, provide the background code with extension."<<"\n"<<"\n";
     cout<<"\t"<<"The following are the backgrounds available for your webpage:-"<<"\n";
     cout<<"\t"<<"-	Background.jpg"<<"\n";
     cout<<"\t"<<"-	Background1.jpg"<<"\n";
     cout<<"\t"<<"-	Background2.jpg"<<"\n";
     cout<<"\t"<<"-	Background3.jpg"<<"\n";
     cout<<"\t"<<"-	Background4.jpg"<<"\n";
	 cout<<"\t"<<"-	Background5.jpg"<<"\n";
	 cout<<"\t"<<"-	Background6.jpg"<<"\n";
     cout<<"\t"<<"-	Background7.jpg"<<"\n";
     cout<<"\t"<<"-	Background8.jpg"<<"\n";
     cout<<"\t"<<"-"<<"\t"<< "nobackground (If no background is required)"<<"\n";
     cout<<"*"<<"To end your paragraph, press ($)."<<"\n"<<"\n";
     cout<<"*******************************************************************************"<<"\n"<<"\n";
	 cout<<"Start entring the required data for your Webpage."<<"\n"<<"\n";
}
//Function to create a WEBPAGE similar to TMEPLATE 1
void create_template1()
{
	ofstream fout("CT1.html");
	char title[50], heading[50], title1[50], para[500],background[50];
	fout<<"<html><head><title>";
	cout<<"Enter the title of the Webpage :- ";
	cin.ignore();
	cin.getline(title,40);
	fout<<title<<"</title></head>";
	fout<<"<body background= \"";
	cout<<"Enter the Backgroung name  :- ";
    cin>>background;
	fout<<background<<"\">";
    fout<<"<h1><center><u>";
	cout<<"Enter the Heading :- ";
	cin.ignore();
	cin.getline(heading,50);
	fout<<heading<<"</u></center></h1>";
	fout<<"<p><b>";
	cout<<"Enter the Title for the Paragraph :- ";
	cin.getline(title1,50);
	fout<<" "<<title1<<"</b></p>";
	fout<<"<p>";
	char resp;
	do{
		cout<<"Enter the paragraph :- ";
		cin.getline(para,500,'$');
		for(int i=0;para[i]!='\0';i++)
		{
			if(para[i]=='\n')
				fout<<"<br>";
			else
				fout<<para[i];
		}
	    cout<<"\n"<<"Do you want to enter more Content? [yes(y) or No(n)]:- ";
		cin>>resp;
	}while(resp=='y');
	fout<<"</p></body></html>";
	cout<<"\n"<<"YOUR WEBPAGE HAS BEEN CREATED.";
	cout<<"\n"<<"\n"<<"\t"<<"\t"<<"**THANK YOU FOR VISITING WEB PAGE CREATER.**";
	fout.close();
	getch();
	system("cls");
}
//Function for calling WEBPAGE CREATOR similar to TEMPLATE 1 window
void main_temp1()
{
    instructions_temp1();
	create_template1();
	getch();
}
//Function for providing information to the user
void instructions_temp2()
{
     cout<<"\t"<<"\t"<<"\t"<<"**WELCOME TO THE WEB CREATOR PAGE**"<<"\n"<<"\n";
     cout<<"To create a webpage follow the instructions :-"<<"\n"<<"\n";
     cout<<"*"<<"Enter the appropriate information."<<"\n";
     cout<<"*"<<"If you want to have a background, provide the background with extension."<<"\n"<<"\n";
     cout<<"\t"<<"The following are the backgrounds available for your webpage:-"<<"\n";
     cout<<"\t"<<"-	Background.jpg"<<"\n";
     cout<<"\t"<<"-	Background1.jpg"<<"\n";
     cout<<"\t"<<"-	Background2.jpg"<<"\n";
     cout<<"\t"<<"-	Background3.jpg"<<"\n";
     cout<<"\t"<<"-	Background4.jpg"<<"\n";
	 cout<<"\t"<<"-	Background5.jpg"<<"\n";
	 cout<<"\t"<<"-	Background6.jpg"<<"\n";
     cout<<"\t"<<"-	Background7.jpg"<<"\n";
     cout<<"\t"<<"-	Background8.jpg"<<"\n";
     cout<<"\t"<<"-"<<"\t"<< "nobackground (If no background is required)"<<"\n"<<"\n";
     cout<<"*"<<"If you want to have a image, provide the image with extension."<<"\n"<<"\n";
     cout<<"\t"<<"The following are the images available for your webpage:-"<<"\n";
     cout<<"\t"<<"-	image.jpg"<<"\n";
     cout<<"\t"<<"-	image1.jpg"<<"\n";
     cout<<"\t"<<"-	image2.jpg"<<"\n";
     cout<<"\t"<<"-	image3.jpg"<<"\n";
     cout<<"\t"<<"-	image4.jpg"<<"\n";
	 cout<<"\t"<<"-	image5.jpg"<<"\n";
	 cout<<"\t"<<"-"<<"\t"<< "noimage (If no image is required)"<<"\n"<<"\n";
     cout<<"*"<<"To end your paragraph, press ($)."<<"\n"<<"\n";
     cout<<"*******************************************************************************"<<"\n"<<"\n";
	 cout<<"Start entring the required data for your Webpage."<<"\n"<<"\n";
}
//Function to create a WEBPAGE similar to TMEPLATE 2
void create_template2()
{
	ofstream fout("CT2.html");
	char title[50], heading[50], title1[50], para[500],background[50],image[50];
	fout<<"<html><head><title>";
	cout<<"Enter the title of the Webpage :- ";
	cin.ignore();	
    cin.getline(title,40);
	fout<<title<<"</title></head>";
	fout<<"<body background= \"";
	cout<<"Enter the Backgroung name  :- ";
    cin>>background;
	fout<<background<<"\"><h1><center><u>";
	cout<<"Enter the Heading :- ";
	cin.ignore();
	cin.getline(heading,50);
	fout<<heading<<"</u></center></h1>";
	fout<<"<center><img src= \"";
	cout<<"Enter the Image name :- ";
	cin>>image;
	fout<<image<<"\"></center>";
	fout<<"<p><b>";
	cout<<"Enter the Title for the Paragraph :- ";
	cin.ignore();
	cin.getline(title1,50);
	fout<<" "<<title1<<"</b></p>";
	fout<<"<p>";
	char resp;
	do{
		cout<<"Enter the paragraph :- ";
		cin.getline(para,500,'$');
		for(int i=0;para[i]!='\0';i++)
		{
			if(para[i]=='\n')
				fout<<"<br>";
			else
				fout<<para[i];
		}
	    cout<<"\n"<<"Do you want to enter more Content? [yes(y) or No(n)]:- ";
		cin>>resp;
	}while(resp=='y');
	fout<<"</p></body></html>";
	cout<<"\n"<<"YOUR WEBPAGE HAS BEEN CREATED.";
	cout<<"\n"<<"\n"<<"\t"<<"\t"<<"**THANK YOU FOR VISITING WEB PAGE CREATER.**";
	fout.close();
	getch();
	system("cls");
}
//Function for calling WEBPAGE CREATOR similar to TEMPLATE 2 window
void main_temp2()
{
    instructions_temp2();
	create_template2();
	getch();
}
//Function for providing information to the user
void instructions_temp3()
{
     cout<<"*******************************************************************************"<<"\n"<<"\n";
     cout<<"\t"<<"\t"<<"\t"<<" ~AHA WEBPAGE CREATOR~ "<<"\n";
     cout<<"*******************************************************************************"<<"\n"<<"\n";
	 cout<<"Enter the Choice as indicated below :- ";
     cout<<"To create a webpage follow the instructions :-"<<"\n"<<"\n";
     cout<<"*"<<"Enter the appropriate information."<<"\n";
     cout<<"*"<<"If you want to have a background, provide the background code with extension."<<"\n"<<"\n";
     cout<<"\t"<<"The following are the backgrounds available for your webpage:-"<<"\n";
     cout<<"\t"<<"-	Background.jpg"<<"\n";
     cout<<"\t"<<"-	Background1.jpg"<<"\n";
     cout<<"\t"<<"-	Background2.jpg"<<"\n";
     cout<<"\t"<<"-	Background3.jpg"<<"\n";
     cout<<"\t"<<"-	Background4.jpg"<<"\n";
	 cout<<"\t"<<"-	Background5.jpg"<<"\n";
	 cout<<"\t"<<"-	Background6.jpg"<<"\n";
     cout<<"\t"<<"-	Background7.jpg"<<"\n";
     cout<<"\t"<<"-	Background8.jpg"<<"\n";
     cout<<"\t"<<"-"<<"\t"<< "nobackground (If no background is required)"<<"\n"<<"\n";
     cout<<"*"<<"If you want to have a image, provide the image with extension."<<"\n"<<"\n";
     cout<<"\t"<<"The following are the images available for your webpage:-"<<"\n";
     cout<<"\t"<<"-	image.jpg"<<"\n";
     cout<<"\t"<<"-	image1.jpg"<<"\n";
     cout<<"\t"<<"-	image2.jpg"<<"\n";
     cout<<"\t"<<"-	image3.jpg"<<"\n";
     cout<<"\t"<<"-	image4.jpg"<<"\n";
	 cout<<"\t"<<"-	image5.jpg"<<"\n";
	 cout<<"\t"<<"-"<<"\t"<< "noimage (If no image is required)"<<"\n"<<"\n";
	 cout<<"*"<<"If you want to have a border around your table, provide the border code within double quotes."<<"\n"<<"\n";
     cout<<"\t"<<"The following are the border codes available for your webpage:-"<<"\n";
     cout<<"\t"<<"-	1 (for applying border around your table)"<<"\n";
     cout<<"\t"<<"-	2 (for no border around your table)"<<"\n";
     cout<<"*"<<"To end your paragraph, press ($)."<<"\n"<<"\n";
     cout<<"*******************************************************************************"<<"\n"<<"\n";
	 cout<<"Start entring the required data for your Webpage."<<"\n"<<"\n";
}
//Function to create a WEBPAGE similar to TMEPLATE 3
void create_template3()
{
	ofstream fout("CT3.html");
	int number;
	char title[50], heading[50], title1[50], para[500],background[50],image[50], tableheader[40],content[70];
	fout<<"<html><head><title>";
	cout<<"Enter the title of the Webpage :- ";
	cin.ignore();
    cin.getline(title,40);
	fout<<title<<"</title></head>";
	fout<<"<body background= \"";
	cout<<"Enter the Backgroung name  :- ";
	cin>>background;
	fout<<background<<"\"><h1><center><u>";
	cout<<"Enter the Heading :- ";
	cin.ignore();
	cin.getline(heading,50);
	fout<<heading<<"</u></center></h1>";
	fout<<"<center><img src= \"";
	cout<<"Enter the Image name :- ";
	cin>>image;
	fout<<image<<"\"></center>";
	fout<<"<p><b>";
	cout<<"Enter the Title for the Paragraph :- ";
	cin.ignore();
	cin.getline(title1,50);
	fout<<" "<<title1<<"</b></p>";
	fout<<"<p>";
	char resp;
	do{
		cout<<"Enter the paragraph :- ";
		cin.getline(para,500,'$');
		for(int i=0;para[i]!='\0';i++)
		{
			if(para[i]=='\n')
				fout<<"<br>";
			else
				fout<<para[i];
		}
	    cout<<"\n"<<"Do you want to enter more Content? [yes(y) or No(n)]:- ";
		cin>>resp;
	}while(resp=='y');
	fout<<"</p>";
	cout<<"\n"<<"Enter a Heading for the Table :- ";
	cin.ignore();
	cin.getline(tableheader,40);
	fout<<"<h2><u>"<<tableheader<<"</u></h2>";
	cout<<"Enter the border code for ur table :- ";
	cin>>number;
	fout<<"<table border=\""<<number<<"\">";
	char response;
	cin.ignore();
	do
	{
		fout<<"<tr>";
		char reply;
		do{
			fout<<"<td><center>";
			cout<<"Enter the Content :- ";
			cin.ignore();
			cin.getline(content,70);
			fout<<content<<"</center></td>";
	    	cout<<"\n"<<"Do you want to have more Columns? [yes(y) or No(n)]:- ";
			cin>>reply;
		}while(reply=='y');
	cout<<"\n"<<"Do you want to have more Rows? [yes(y) or No(n)]:- ";
	cin>>response;
	fout<<"</tr>";
	}while(response=='y');
	fout<<"</table>";
	fout<<"</body></html>";
	cout<<"\n"<<"YOUR WEBPAGE HAS BEEN CREATED.";
	cout<<"\n"<<"\n"<<"\t"<<"\t"<<"**THANK YOU FOR VISITING WEB PAGE CREATER.**";
	fout.close();
	getch();
	system("cls");
}
//Function for calling WEBPAGE CREATOR similar to TEMPLATE 3 window
void main_temp3()
{
    instructions_temp3();
	create_template3();
	getch();
}
//Function for providing information to the user
void begin_see_webcreate()
{
    cout<<"*******************************************************************************"<<"\n"<<"\n";
    cout<<"\t"<<"\t"<<"\t"<<" ~AHA WEBPAGE CREATOR~ "<<"\n";
    cout<<"*******************************************************************************"<<"\n"<<"\n";
	cout<<"Enter the Choice as indicated below :- ";
	cout<<"Here you will be able to see the pages you have created."<<"\n"<<"\n";
	cout<<"\t"<<"   "<<"**HAVE A NICE TIME USISNG WEBPAGE CREATOR**"<<"\n";
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"**THANK YOU**."<<"\n"<<"\n";
}
//Switch Case for VIEWING THE WEBPAGES(created by the user)
void switchcalling_see_webcreate()
{
	cout<<"Enter the Choice as indicated below :- ";
	int ch;
	do
	{
		cout<<"\n"<<"MENU:"<<"\n"<<"\n";
		cout<<"0. Return To the Homescreen"<<"\n";
		cout<<"1. Plain Text Webpage. ~ PAGE CREATED 1"<<"\n";
		cout<<"2. Webpage with an image and Text. ~ PAGE CREATED 2"<<"\n";
		cout<<"3. Webpage with an image, a Table and Text. ~ PAGE CREATED 3"<<"\n"<<"\n";
		cout<<"\n"<<"Enter your Choice Number= ";
		cin>>ch;
		getch();
		system("cls");
		switch(ch)
		{
			case 1:	system("CT1.html");
					break;
			case 2: system("CT2.html");
					break;
			case 3: system("CT3.html");
					break;
			case 0 :main_homescreen_calling();
					break;
		}
	}while(ch!=0);
}
//Functions for VIEW WEBPAGES CREATED(by user) window
void main_see_webcreate()
{
	begin_see_webcreate();
	switchcalling_see_webcreate();
	getch();
}
int main()
{
    main_login();
	getch();
	return 0;
}
