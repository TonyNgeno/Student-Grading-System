using namespace std;
#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>

class Grading
{
	int admno;
	char name1[100],name2[100],name3[100],choice;
	int marks,math,eng,kis,bio,chem,phy,bs;
	float avg;
	char grade;
	void calculate();
public:
	void getdata();
	void showdata();
	void display();
	int adm();
};
void Grading::calculate()
{
avg=(math+eng+kis+bio+chem+phy+bs)/7;
            if (avg>=80)
            {
                grade='A';
            }
            else if (avg>=60)
            {
                grade='B';
            }
            else if (avg>=40)
            {
                grade='C';
            }
            else if (avg>=20)
            {
               grade='D';
            }
            else
            {
               grade='E';
            }
}
void Grading::getdata()
{
	cout<<"\nEnter the admission number of student ";
	cin>>admno;
	cout<<"\n\nEnter the name of the student ";
	cin>>name1;
	cout<<"\n\nEnter the name of the student ";
	cin>>name2;
	cout<<"\n\nEnter the name of the student ";
	cin>>name3;
	cout<<"\nEnter the marks out of 100 for: ";
    cout<<"\n Maths: ";
    cin>>math;
    cout<<"\n English: ";
    cin>>eng;
    cout<<"\n Kiswahili: ";
    cin>>kis;
    cout<<"\n Biology: ";
    cin>>bio;
    cout<<"\n Chemistry: ";
    cin>>chem;
    cout<<"\n Physics: ";
    cin>>phy;
    cout<<"\n business: ";
	cin>>bs;
	calculate();
}
void Grading::showdata()
{
	cout<<"\n Student admission number : "<<admno;
	cout<<"\n Student name: "<<name1<<" "<<name2<<" "<<name3;
	cout<<"\n Student marks for:\n";
	cout<<"\n Maths: "<<math;
    cout<<"\n English: "<<eng;
    cout<<"\n Kiswahili: "<<kis;
    cout<<"\n Biology: "<<bio;
    cout<<"\n Chemistry: "<<chem;
    cout<<"\n Physics: "<<phy;
    cout<<"\n business: "<<bs;
	cout<<"\n Student average marks: "<<avg;
	cout<<"\n Student grade is: "<<grade;
}
void Grading::display()
{
	cout<<admno<<"\t"<<name1<<" "<<name2<<" "<<name3<<"\t"<<math<<"\t"<<eng<<"\t"<<kis<<"\t"
		<<bio<<"\t"<<chem<<"\t"<<phy<<"\t"<<bs<<"\t"<<avg<<"\t\t"<<grade<<endl;
}
int  Grading::adm()
{
	return admno;
}
void studentdata()
{
	Grading a;
	ofstream outFile;
	outFile.open("Grading.dat",ios::binary|ios::app);
	a.getdata();
	outFile.write((char *) &a, sizeof(Grading));
	outFile.close();
    	cout<<"\n\nThe data was successfully created ";
	cin.ignore();
	getch();
}
void display_all()
{
	Grading a;
	ifstream inFile;
	inFile.open("Grading.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\a\nNo student data exists !!! Press any Key to continue\n";
		getch();
		return;
	}
	cout<<"\n\n\n\t\tResults for all students\n\n";
	while(inFile.read((char *) &a, sizeof(Grading)))
	{
		a.showdata();
		cout<<"\n\n*************************************\n";
	}
	inFile.close();
	getch();
}
void display_sp(int n)
{
	Grading a;
	ifstream inFile;
	inFile.open("Grading.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\a\nFile does not exist !!! Press any Key to continue\n";
		getch();
		return;
	}

	int flag=0;
	while(inFile.read((char *) &a, sizeof(Grading)))
	{
		if(a.adm()==n)
		{
			 a.showdata();
			 flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\n\a\nFile does not exist !!! Press any Key to continue\n";
	getch();
}
void modify(int n)
{
	int found=0;
	Grading a;
	fstream File;
	File.open("Grading.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"\n\n\a\nFile does not exist !!! Press any Key to continue\n";
		getch();
		return;
	}
	while(File.read((char *) &a, sizeof(Grading)) && found==0)
	{
		if(a.adm()==n)
		{
			a.showdata();
			cout<<"\n\nEnter new student details\n"<<endl;
			a.getdata();
		    	int pos=(-1)*sizeof(a);
		    	File.seekp(pos,ios::cur);
		    	File.write((char *) &a, sizeof(Grading));
		    	cout<<"\n\n\tThe data was successfully updated\n";
		    	found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n\n\n\a\nFile does not exist !!! Press any Key to continue\n";
	getch();
}
void delet(int n)
{
	Grading a;
	ifstream inFile;
	inFile.open("Grading.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\n\n\a\nFile does not exist !!! Press any Key to continue\n";
		getch();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &a, sizeof(Grading)))
	{
		if(a.adm()!=n)
		{
			outFile.write((char *) &a, sizeof(Grading));
		}
	}
	outFile.close();
	inFile.close();
	remove("Grading.dat");
	rename("Temp.dat","Grading.dat");
	cout<<"\n\n\tThe data was successfully deleted\n";
	getch();
}
void class_result()
{
	Grading a;
	ifstream inFile;
	inFile.open("Grading.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\n\n\a\nFile does not exist !!! Press any Key to continue\n";
		getch();
		return;
	}
	cout<<"\n\n\t\tResult for all students\n\n";
    cout<<"ADM. NO.\tName\t\tMATHS\tENG\tKIS\tBIO\tCHEM\tPHY\tB/S\tTOTAL\t\tGrade"<<endl;
	while(inFile.read((char *) &a, sizeof(Grading)))
	{
		a.display();
	}
	getch();
	inFile.close();
}
void result()
{
	char ch;
	int ad;
	cout<<"\n\n\n\tResults menu";
	cout<<"\n\n\n\t1. Result for the whole class";
	cout<<"\n\n\t2. Result for individual student";
	cout<<"\n\n\t3. Back to Main Menu";
    cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :class_result(); break;
	case '2' :cout<<"\n\n\tEnter student ADM. NO.:\n";
		  cin>>ad;
		  display_sp(ad);
		  break;
	case '3' :break;
	default :cout<<"\a";
	}
}
void menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\t1.Enter student data\n";
	cout<<"\n\n\t2.Display student data\n";
	cout<<"\n\n\t3.Search for student data\n";
	cout<<"\n\n\t4.Change or modify student data\n";
	cout<<"\n\n\t5.Delete student data\n";
	cout<<"\n\n\t6.Back to main menu\n";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	studentdata();
	break;
	case '2':	display_all();
	break;
	case '3':	cout<<"\n\n\tEnter student ADM. NO.\n";
                cin>>num;
                display_sp(num);
                break;
	case '4':	cout<<"\n\n\tEnter student ADM. NO.\n";
                cin>>num;
                modify(num);
                break;
	case '5':	cout<<"\n\n\tEnter student ADM. NO.\n";
                cin>>num;
                delet(num);
                break;
	case '6':	break;
                default:	cout<<"\a";
                menu();
	}
}
void intro()
{
	cout<<"\n\n\t\tDEDAN KIMATHI UNIVERSITY OF TECHNOLOGY";
	cout<<"\n\n\n\t\t\tCOMPUTER SCIENCE";
	cout<<"\n\n\n\t\t    STUDENT GRADING PROGRAM";
	
    getch();
}
int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(4);
	system("cls");
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMain menu\n";
		cout<<"\n\n\t1. Edit student data\n";
		cout<<"\n\n\t2. View results\n";
		cout<<"\n\n\t3. Exit";
        cin>>ch;
		system("cls");
		switch(ch)
		{
			case '1': menu();
				break;
			case '2': result();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    	}while(ch!='3');
	return 0;
}
