//***************************************************************
//     ------------  HEADER FILE USED IN PROJECT  -------------
//****************************************************************

#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<fstream>//used for file handling 
#include<iomanip>//The header <iomanip> consists of functions that are
  //used to manipulate the output of the C++ program.We can make the output 
 // of any program neater and presentable based on where we want to show it or who is going to use it.

using namespace std;
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class Admin
{
    int rollno;
    char name[50];
    int phy,chem,bio,eng,urdu;
    float per;
    char Grade;
    int n;
  
public:
	
//*********************************************************
//          GET DATA & CALCULATE FUNCTIONS
//*********************************************************

    void getdata()
    {
    	system("color 7");
		cout<<endl<<"Enter Student Roll number:  ";
		cin>>rollno;
		cout<<endl<<"Enter the Name of the Student:  ";
		cin>>name;
		cout<<"Enter the marks of physics out of 100:   ";
		cin>>phy;
		cout<<endl<<"Enter the marks of chemistry out of 100:  ";
		cin>>chem;
		cout<<endl<<"Enter the marks of biology out of 100:  ";
		cin>>bio;
		cout<<endl<<"Enter the marks of english out of 100:   ";
		cin>>eng;
		cout<<endl<<"Enter the marks of urdu out of 100:   ";
		cin>>urdu;
			per=(phy+chem+bio+eng+urdu)/5.0;
		if(per>=60)
		{
			Grade='A';
		}
		else if(per>=50&&per<=60)
		{
			Grade='B';
		}
		else if(per>=33&&per<=50)
		{
			Grade='C';
		}
		else
		{
			Grade='F';
		}
		cout<<endl<<"Percentage of student:  "<<per;
		cout<<endl<<"Grade of student:  "<<Grade;
		cout<<endl<<"     Total Marks of Student are:  "<<phy+chem+bio+eng+urdu;
		system("cls");
			
    }
    
//*******************************************************
//           SHOW DATA FUNCTION
//*******************************************************

    void showdata()
    {
    	system("color 8");
        cout<<"\t\t\t\tSTUDENT ROLL NUMBER :"<<rollno<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT NAME :"<<name<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT PHYSCIS MARKS :"<<phy<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT CHEMISTRY MARK :"<<chem<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT BIOLOGY MARK :"<<bio<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT URDU MARKS MARK :"<<urdu<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT ENGLISH MARK :"<<eng<<endl<<endl;
        cout<<"\t\t\t\tTOTAL MARKS :"<<phy+chem+bio+eng+urdu<<endl<<endl;
        cout<<"\t\t\t\tPERCENTAGE :"<<per<<endl<<endl;
        cout<<"\t\t\t\tGRADE :"<<Grade;
    }

    void showTabular()
    {
    	system("color 5");
        cout<<rollno<<setw(12)<<name<<setw(10)<<phy<<setw(3)<<chem<<setw(3)<<bio<<setw(3)<<eng<<setw(3)<<urdu<<setw(6)<<per<<"   "<<Grade<<endl;
        /*Setw()   number of width setw function is a C++ manipulator which stands
	 	for set width. The manipulator sets the ios library field width or specifies
	 	the minimum number of character positions a variable will consume.*/
    }
    

    int  retrollno()
    {
        return rollno;
    }

};         //class ends here



//***************************************************************
//      GLOBAL DECELERATION OF CLASS SUBJECT, FILE OBJECT
//****************************************************************

fstream fp;
Admin ad;

//***************************************************************
//         FUNCTION TO WRITE FILE
//****************************************************************

void writedata()
{
    fp.open("name.dat",ios::out|ios::app|ios::binary);
    ad.getdata();
    fp.write((char*)&ad,sizeof(Admin));
    fp.close();
    cout<<"\n\nstudent record Has Been Created ";
    getch();
}


//***************************************************************
//      FUNCTION TO READ ALL RECORD FROM FILE
//****************************************************************


void displayAll()
{
    system("cls");
    system("color a");
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("name.dat",ios::in|ios::binary);
    while(fp.read((char*)&ad,sizeof(Admin)))
    {
        ad.showdata();
        cout<<"\n\n====================================\n";
        getch();
    }
    fp.close();
    getch();
}


//***************************************************************
//      FUNCTION TO READ SPECIFIC RECORD FROM FILE
//****************************************************************


void displaySP(int n)
{
	system("color b");
    int flag=0;
    fp.open("name.dat",ios::in|ios::binary);
    while(fp.read((char*)&ad,sizeof(Admin)))
    {
        if(ad.retrollno()==n)
        {
            system("cls");
            ad.showdata();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
        cout<<"\n\nrecord not exist";
    getch();
}


//***************************************************************
//      FUNCTION TO MODIFY THE RECORD
//****************************************************************


void modifydata()
{
    system("color e");
	int no,found=0;
    system("cls");
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The roll number of student";
    cin>>no;
    fp.open("name.dat",ios::in|ios::out|ios::binary);
    while(fp.read((char*)&ad,sizeof(Admin)) && found==0)
    {
        if(ad.retrollno()==no)
        {
            ad.showdata();
            cout<<"\nPlease Enter The New Details of student"<<endl;
            ad.getdata();
            int pos=(-1)*static_cast<int>(sizeof(ad)); //pos=Number of bytes//static_cast<int> is an implicit function which ignores all data types and convert it into int 
           // int pos=(-1)*sizeof(ad);
            fp.seekp(pos,ios::cur);//MOVE "PUT" POINTER TO A SPECIFIC LOCATION. Seekp is Member of ofstream.Use When you perform writing.
            fp.write((char*)&ad,sizeof(Admin));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
}



//***************************************************************
//         FUNCTION TO DISPLAY ALL GRADE REPORT
//****************************************************************

void classResult()
{
	system("cls");
	system("color 2");
    fp.open("name.dat",ios::in|ios::binary);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
        cout<<"\n\n\n Program is closing ....";
        getch();
        exit(0);
    }

    cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
    cout<<"====================================================\n";
    cout<<"Roll No. Name          P  C  M  E  U  %age Grade\n";
    cout<<"====================================================\n";

    while(fp.read((char*)&ad,sizeof(Admin)))
    {
        ad.showTabular();
    }
    fp.close();
    getch();
}




//***************************************************************
//         FUNCTION TO DISPLAY RESULT MENU
//****************************************************************

void result()
{
	system("color 9");
    int ans,rno;
    char ch;
    system("cls");
    cout<<"\n\n\nRESULT MENU";
    cout<<"\n\n\n1. Class Result\n\n2. Student Report Card\n\n3.Back to Main Menu";
    cout<<"\n\n\nEnter Choice (1/2)? ";
    cin>>ans;
    if(ans==1)
    {
        classResult();
    }
    else if(ans==2)
    {
        do
        {
            system("cls");
            system("color b");
            char ans;
            cout<<"\n\nEnter Roll Number Of Student : ";
            cin>>rno;
            displaySP(rno);
            cout<<"\n\nDo you want to See More Result (y/n)?";
            cin>>ans;
        }
        while(ans=='y'||ans=='Y');
    }
    else if(ans==3)
    {
    	exit(0);
	}
}




//***************************************************************
//      ENTRY / EDIT MENU FUNCTION
//****************************************************************

bool mainPage()
{
    system("color d");
	system("cls");
    int x;
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
    cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
    cin>>x;
    if(x==1)
    {
    	system("cls");
    	writedata();
    	system("cls");
    	mainPage();
    	return true;
	}
	else if(x==2)
	{
		displayAll();
		system("cls");
		mainPage();
		return true;
	}
	else if(x==3)
	{
		int num;
		system ("cls");
		cout<<"      Please enter the roll Number that you want to search:  ";
		cin>>num;
		displaySP(num);
		system("cls");
		mainPage();
		return true;
	}
	else if(x==4)
	{
		modifydata();
		system("cls");
		mainPage();
		return true;
	}
	else if(x==5)
	{
		system("cls");
		result();
		return true;
	}
}


//***************************************************************
//      INTRODUCTION FUNCTION
//***************************************************************

		void intro()
		{ 
		    system("color a");
			cout<<endl<<endl<<endl<<endl<<endl;
			cout<<endl<<"                    WELCOME TO RESULT MANAGEMENT PROJECT       "<<endl<<endl<<endl;
			cout<<"                             PRESS ENTER TO CONTINUE      "<<endl<<endl<<endl;
			cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
			cout<<"         Made by :"<<endl; 
			cout<<"                 MEHAK ASLAM   "<<endl;
			cin.get();
			
		}


//****************************************************************
//           ADMIN LOGIN FUNCTION(READ & COMPARE FROM FILE DATA)
//****************************************************************
	





bool admin()
{
	char c=' ';
	int i=0;//count login attempt
	int a=0;
    int option;
    system("color 6");
    string name, accountname, password, passwordlogin="mhk010",username;
    cout<<"ARE YOU ADMIN OR USER?"<<endl;
    cout<<"[Press 1] if you are admin"<<endl<<"[Press 2] if you are student"<<endl;
    cout<<"Your Option: ";
    cin>>option;
    if (option == 1)
    {
    
	        system("cls");
            cout<<"----------LOGIN-----------"<<endl;
            cout<<"Now, log in your account"<<endl;
	        do
			{  
				system("color 3");
        	    cout<<endl<<"Please enter your name to be login: ";
            	cin>>accountname;
            	cout<<endl<<"Please enter password: ";
           	  //  cin >> password_login;
    			while(i<=6)
				{
					passwordlogin[i]=getch();
					c=passwordlogin[i];
					if(c==13)
						break;
					else 
							cout<<"*";
	  					  i++;
					}
				ifstream find_account("Mehak.txt");
            	getline(find_account,name);
           // getline(find_account, password);
            	if (accountname==name && passwordlogin=="mhk010")
            	{
                	cout<<endl<<"You have logged in successfully!"<<endl<<endl;
                	cin.ignore();
                	int c;
					do
    				{
    					system("color 5");
    					cin.ignore();
        				system("cls");
        				cout<<"\n\n\n\tMAIN MENU";
        				cout<<"\n\n\t01. RESULT MENU";
        				cout<<"\n\n\t02. ENTRY/EDIT MENU";
        				cout<<"\n\n\t03. EXIT";
        				cout<<"\n\n\tPlease Select Your Option (1-3) ";
        				cin>>c;
    					if(c==1)
    					{
        					system("cls");
        					result();
						}	
						else if(c==2)
						{
							mainPage();
						}
						else 
						{
							exit(0);
						}
    				}
    				while(c!='3');
            	}
                
            	else
            	{
					cin.ignore();
                	cout<<endl<<"Invaild username or password"<<endl;
					a++;
            		cin.ignore();
				}
        	}
        	while(a<=2);
        	{
				if (a>2)
				{						
					cout<<"\nSO MANY WRONG ATTEMPTS!!!";
					getch();
				}
				system("cls");
            }
		}
	
	
    else if(option==2)
    {
    	int s;
    	cout<<"Enter your Roll Number:    ";
    	cin>>s;
    	displaySP(s);
	}
        else 
        {
            cout<<endl<<"Please enter correct option"<<endl;       
        }
    return 0;
}

//***************************************************************
//      THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
	intro();
	system("cls");
	admin();
	return 0;
}

//***************************************************************
//              ------END OF the PROJECT-----
//***************************************************************
