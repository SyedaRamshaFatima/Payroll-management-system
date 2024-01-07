#include<iostream>
#include<fstream>
using namespace std;
const int max_EMP=100;
class Employee{
private:
    string name;
    int id;
    int salary;
public:
	Employee(){}
    Employee(string name,int id,int salary)
	{
		this->name=name;
		this->id=id;
		this->salary=salary;
	} 
    string getname()
	{
        return name;
    }
    int getID()
	{
        return id;
    }
    int getsalary()
	{
        return salary;
    }
    void setsalary(int newsalary)
	{
        salary=newsalary;
    }
};

class payroll{
private:
    Employee employees[max_EMP];
    int numEmp;
public:
    payroll()
	{
        numEmp=0;
    }
    void addingEmployee(const Employee &employee)
	{
        if(numEmp<max_EMP)
		{
            employees[numEmp]=employee;
            numEmp++;
            saveData(); 
        }
		else
		{
            cout<<"EMPLOYEE LIMIT EXCEEDED "<<endl;
        }
    }
    void display()
	{
        cout<<"_________________________            EMPLOYESS INFO              ________________________"<<endl;
        for(int i=0;i<numEmp;i++)
		{
            cout<<"NAME: "<<employees[i].getname()<<"|| ID: "<<employees[i].getID()<<"|| SALARY: $"<<employees[i].getsalary()<<endl;
        }
    }

    void update_salary(int employeeID,int newsalary)
	{
        for(int i=0;i<numEmp;i++)
		{
            if(employees[i].getID() == employeeID)
			{
                employees[i].setsalary(newsalary);
                cout<<"SALARY UPDATED FOR EMPLOYEE ID "<<employeeID<<endl;
                saveData();
                return;
            }
        }
        cout<<"EMPLOYEE WITH ID "<<employeeID<<" NOT FOUND"<<endl;
    }

    void adding_NewEmp()
	{
        string name;
        int id;
        int salary;
        cin.ignore();
        cout<<"EMPLOYEE NAME: "<<endl;
        getline(cin,name);
        cout<<"EMPLOYEE ID: ";
        cin>>id;
        cout<<"EMPLOYEE SALARY: ";
        cin>>salary;
        Employee newEmployee(name,id,salary);
        addingEmployee(newEmployee);
        cout<<"               EMPLOYEE ADDED SUCCESSFULLY             "<<endl;
    }

    void saveData()
	{
        ofstream file("employee_data.txt");
        if(file.is_open())
		{
            for(int i=0;i<numEmp;i++)
			{
                file<<employees[i].getname()<< " "<<employees[i].getID()<<" "<<employees[i].getsalary()<<endl;
            }
            file.close();
        }
    }
};

bool login()
{
    string username,password;
    cout<<endl<<endl<<"------------------------               Login Screen                 ------------------------------"<<endl;
    cout<<endl<<"USERNAME : ";
    cin>>username;
    cout<<"PASSWORD : ";
    cin>>password;

    if(username == "admin" && password == "adminonly")
	{
        cout<<endl<<endl<<"_________________________________          LOGIN SUCCESSFUL          ________________________________"<<endl;
        return true;
    }
	else
	{
        cout<<"                INVALID USERNAME OR PASSWORD!              "<<endl;
        return false;
    }
}

void additionalEmployeeData(payroll &p)
{
    ifstream file("employee_data.txt");
    if(file.is_open())
	{
        string name;
        int id;
        int salary;
        while(file>>name>>id>>salary)
		{
            Employee emp(name,id,salary);
            p.addingEmployee(emp);
        }
        file.close();
    }
}

int main()
{
    cout<<"--------------------------------    WELCOME TO PAYROLL MANAGEMENT SYSTEM    ---------------------------------------"<<endl;
    cout<<endl<<endl<<"                                    PRESS ANY KEY...                                                         "<<endl;
    cin.get(); 
	    
    if(login())
	{
       payroll p;
       additionalEmployeeData(p);
       int opt;
       do
	   {
          cout<<endl<<"Menu: "<<endl;
          cout<<"1. DISPLAY EMPLOYEES"<<endl;
          cout<<"2. UPDATE EMPLOYEE SALARY"<<endl;
          cout<<"3. ADD A NEW EMPLOYEE"<<endl;
          cout<<"4. EXIT"<<endl;
          cout<<"SELECTED OPTION: ";
          cin>>opt;
          switch(opt)
		  {
            case 1:
              p.display();
              break;
            case 2:
              int empID;
	          int newSalary;
              cout<<"EMPLOYEE ID: ";
              cin>>empID;
              cout<<"NEW SALARY: ";
              cin>>newSalary;
              p.update_salary(empID,newSalary);
              break;
            case 3:
              p.adding_NewEmp();
		      break;
            case 4:
              cout<<"EXITED FROM PAYROLL MANAGEMENT SYSTEM "<<endl;
              break;
            default:
              cout<<"< ERROR >"<<endl;
            }
        } while(opt!=4);         
    }
    else
	{
       return 0; 	
	}
   
}

