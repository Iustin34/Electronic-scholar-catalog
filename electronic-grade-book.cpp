#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class student
{
	int rollno;
	char name[50];
	int f_marks, c_marks, m_marks, r_marks, i_marks;
	double med;
	char grade;
	void calculate();
public:
	void getdata();
	void showdata() const;
	void show_tabular() const;
	int retrollno() const;
};


void student::calculate()
{
	med=(f_marks+c_marks+m_marks+r_marks+i_marks)/5.0;
	if(med>=40)
		grade='A';
	else if(med>=30)
		grade='B';
	else if(med>=25)
		grade='C';
	else
		grade='F';
}

void student::getdata()
{
	cout<<"\nIntroduceti numarul de identificare a studentului ";
	cin>>rollno;
	cout<<"\n\nIntroduceti numele studentului ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nIntroduceti nota din fizica pe o scara de la 1 la 10 : ";
	cin>>f_marks;
	cout<<"\nIntroduceti nota din chimie pe o scara de la 1 la 10: ";
	cin>>c_marks;
	cout<<"\nIntroduceti nota din matematica pe o scara de la 1 la 10: ";
	cin>>m_marks;
	cout<<"\nIntroduceti nota din romana pe o scara de la 1 la 10: ";
	cin>>r_marks;
	cout<<"\nIntroduceti nota din informatica pe o scara de la 1 la 10: ";
	cin>>i_marks;
	calculate();
}

void student::showdata() const
{
	cout<<"\nNumarul de identificare al studentului : "<<rollno;
	cout<<"\nNumele studentului : "<<name;
	cout<<"\nNota fizica : "<<f_marks;
	cout<<"\nNota chimie : "<<c_marks;
	cout<<"\nNota matematica : "<<m_marks;
	cout<<"\nNota romana : "<<r_marks;
	cout<<"\nNota informatica :"<<i_marks;
	cout<<"\nMedia notelor  :"<<med;
	cout<<"\nCalificativ :"<<grade;
}

void student::show_tabular() const
{
	cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<f_marks<<setw(4)<<c_marks<<setw(4)<<m_marks<<setw(4)
		<<r_marks<<setw(4)<<i_marks<<setw(8)<<med<<setw(6)<<grade<<endl;
}

int  student::retrollno() const
{
	return rollno;
}


void write_student();
void display_all();
void display_sp(int);
void modify_student(int);
void delete_student(int);
void class_result();
void result();
void intro();
void entry_menu();


int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2);
	intro();
	do
	{

		cout<<"\n\n\n\tMeniu ";
		cout<<"\n\n\t01. Continuarea Meniului ";
		cout<<"\n\n\t02. Introduce/Editeaza Meniu";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tVa rog introduceti o comanda (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}


void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    	cout<<"\n\nInregistrare noua creata ";
	cin.ignore();
	cin.get();
}

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Fisierul nu a putut fi deschis !! Apasa-ti orice buton...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tAfisa-ti toate inregistrarile !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Fisierul nu a putut fi deschis !! Apasa-ti orice buton...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nnu exista inregistrare";
	cin.ignore();
	cin.get();
}

void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Fisierul nu a putut fi deschis !! Apasa-ti orice buton...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nVa rog introduceti noile detalii ale elevului"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Inregistrare schimbata cu succes";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n nu exista inregistrari ";
	cin.ignore();
	cin.get();
}


void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Fisierul nu a putut fi deschis !! Apasa-ti orice buton...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tInregistrare stearsa cu succes ..";
	cin.ignore();
	cin.get();
}


void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Fisierul nu a putut fi deschis !! Apasa-ti orice buton...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tToate rezultatele studentilor \n\n";
	cout<<"==========================================================\n";
	cout<<"R.No       Nume        F   C   M   R   I   medie   Calif"<<endl;
	cout<<"==========================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

void result()
{
	char ch;
	int rno;

	cout<<"\n\n\n\tContinuarea Meniului";
	cout<<"\n\n\n\t1. Rezultatele Clasei";
	cout<<"\n\n\t2. Numarul studentului";
	cout<<"\n\n\t3. Intoarcere la meniul principal";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;

	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tIntrodu numarul studentului : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}



void intro()
{
	cout<<"\n\n\n\t\t  PROIECT";
	cout<<"\n\n\t\tCATALOG PENTRU";
	cout<<"\n\n\t\t  STUDENTI";
	cout<<"\n\n\n\tELEV : TOPLICIANU FLORIAN IUSTIN";
	cout<<"\n\tSCOALA : COLEGIUL NATIONAL CONSTANTIN CARABELLA";
	cin.get();
}


void entry_menu()
{
	char ch;
	int num;

	cout<<"\n\n\n\tMENIU";
	cout<<"\n\n\t1.ADAUGA DATELE STUDENTULUI";
	cout<<"\n\n\t2.ARATA TOTI STUDENTII CU TOATE DATELE";
	cout<<"\n\n\t3.CAUTA STUDENT ";
	cout<<"\n\n\t4.EDITEAZA DATELE STUDENTULUI";
	cout<<"\n\n\t5.STERGE DATELE STUDENTULUI";
	cout<<"\n\n\t6.INTOARCETE CATRE MENIUL PRINCIPAL";
	cout<<"\n\n\tINTRODUCETI OPTIUNEA CORESPUNZATOARE (1-6) ";
	cin>>ch;

	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tIntroduceti numarul de identificare  "; cin>>num;
			display_sp(num); break;
	case '4':	cout<<"\n\n\tIntroduceti numarul de identificare  "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tIntroduceti numarul de identificare  "; cin>>num;
			delete_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}


