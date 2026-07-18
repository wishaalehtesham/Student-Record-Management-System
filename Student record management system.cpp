#include<iostream>
#include<fstream>
#include<string>
using namespace std;
//--- Data Model ---
// Structure to store student info
struct Student
{
    int roll_no;
    string name;
    int age;
    float marks;
};
Student student[100];   // array holding all student records (max 100)
int count=0;           // number of records currently stored

// Function to add new student
void insertrecord()
{
      // Get and validate roll number (must be a positive integer)
    cout<<"Enter your roll number: ";
    while(!(cin>>student[count].roll_no) ||student[count].roll_no <=0)
    {
        cout<<"invalid Roll number!Enter a positive number: ";
        cin.clear();    // reset error flags on cin
        cin.ignore(1000,'\n');  // discard bad input from the buffer
    }
     // Check if the new roll number (about to be entered) already exists
    bool duplicate = false;
    for (int i=0;i<count;i++)
    {
        if(student[i].roll_no == student[count].roll_no)
        {
            duplicate=true;
            break;
        }
    }
    if(duplicate)
    {
        cout<<"Roll Number already exists!\n";
        return;
    }
    // Get name (getline needed for full names with spaces)
    cout<<"Enter your name: ";
    cin.ignore();   // discard leftover newline from previous cin>>
    getline(cin,student[count].name);

    // Get and validate age (must be between 15 and 35)
    cout<<"Enter your age: ";
    while(!(cin>>student[count].age)||student[count].age<15||student[count].age >35)
        {
            cout<<" Invalid age!Enter age between 15 and 35. ";
            cin.clear();
            cin.ignore(1000,'\n');
        }

        // Get and validate marks (must be between 0 and 100)
    cout<<"Enter your marks: ";
    while(!(cin>>student[count].marks) ||student[count].marks <0 || student[count].marks >100)
          {
              cout<<"Invalid marks!Enter marks between 0 to 100: ";
              cin.clear();
              cin.ignore(1000,'\n');
          }
    count++;
    cout<<" student added successfully. \n";
}
// Function to view student info
void displayrecords()
{
     // If no students exist yet, nothing to show
    if(count==0)
    {
        cout<<"\n No student record found. \n";
        return;
    }
     // Loop through and print every stored record
    for(int i=0;i<count;i++)
    {
        cout<<"\n Student "<<i+1<<endl;
        cout<<"Roll number: "<<student[i].roll_no<<endl;
        cout<<"Name: "<<student[i].name<<endl;
        cout<<"Age: "<<student[i].age<<endl;
        cout<<"Marks: "<<student[i].marks<<endl;
    }
}
//Function to search student info
void findrecord()
{
     int roll;
     bool found=false;
     cout<<"\n Enter the roll number to search: ";
     cin>>roll;
      // Linear search through all records for matching roll number
     for(int i=0;i<count;i++)
     {
         if(student[i].roll_no==roll)
         {
             cout<<"\n \t Student found \t\n ";
             cout<<" Roll number: "<<student[i].roll_no<<endl;
             cout<<" Name: "<<student[i].name<<endl;
             cout<<" Age: "<<student[i].age<<endl;
             cout<<" Marks: "<<student[i].marks<<endl;
             found=true;
             break; // stop once found
         }
     }
     // Only report "not found" after checking the whole array
         if(!found)
            cout<<"\n Student not found \n";
}
//Function to update student info
void editrecord()
{
     int roll;
     bool found=false;
     cout<<"\n Enter the roll number to update: ";
     cin>>roll;
      // Find the student by roll number, then overwrite their fields
     for(int i=0;i<count;i++)
     {
         if(student[i].roll_no==roll)
         {
             cout<<"\n \t Student found \t\n ";
             cout<<"Enter new roll number: ";
             cin>>student[i].roll_no;
             cout<<" Enter new name: ";
             cin.ignore();
             getline(cin,student[i].name);
             cout<<" Enter new age: ";
             cin>>student[i].age;
             cout<<" Enter new marks: ";
             cin>>student[i].marks;
             found=true;
             break;
         }
     }
         if(!found)
            cout<<"\n Student not found \n";
}
//Function to delete student info
void removerecord()
{
     int roll;
     bool found=false;
     cout<<"\n Enter the roll number to delete: ";
     cin>>roll;
     for(int i=0;i<count;i++)
     {
         if(student[i].roll_no==roll)
         {
              // Shift every student after position i one slot to the left,
            // effectively overwriting the deleted record
            for(int j=i;j<count-1;j++)
            {
                student[j]=student[j+1];
            }
            count--;  // one less valid record now
            cout<<"\n Student record deleted successfully. \n";
             found=true;
             break;
         }
     }
         if(!found)
            cout<<"\n Student not found \n";
}
// Function to save all current records to disk (overwrites file each time)
void saveData()
{
   ofstream file("records.data");

   if(!file)
   {
       cout<<"Error Opening File! "<<endl;
       return;
   }
   // Write one line per student: roll_no name age marks
   for(int i=0;i<count;i++)
   {
       file<<student[i].roll_no<<" "<<student[i].name<<" "<<student[i].age<<" "<<student[i].marks<<endl;
   }
   file.close();
   cout<<"\n Records saved successfully. \n";
}
// Function to load previously saved records at program startup
void loadData()
{
    ifstream file("records.data");

    if(!file)
        return;  // no file yet — fine, start with an empty list

    count=0;

    while(file>>student[count].roll_no>>student[count].name>>student[count].age>>student[count].marks)
    {
        count++;
    }
    file.close();
}
int main()
{
    loadData();  // restore previously saved records, if any
    int choice;
    do{
    cout<<"\t STUDENT RECORD MANAGEMENT SYSTEM \t\n";

    cout<<"1. Add Student \n";
    cout<<"2. View Student \n";
    cout<<"3. Search Student \n";
    cout<<"4. Update Student \n";
    cout<<"5. Delete Student \n";
    cout<<"6. Save Records \n";
    cout<<"7. Exit \n";

    cout<<"\n Enter your choice: ";
    // Validate menu choice is a number between 1 and 7
    while(!(cin>>choice)||choice <1 || choice>7)
    {
        cout<<"Invalid choice!Enter a number between 1 and 7: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    // Dispatch to the matching function
    switch(choice)
    {
    case 1:
         insertrecord();
        break;
    case 2:
         displayrecords();
         break;
    case 3:
        findrecord();
        break;
    case 4:
        editrecord();
        break;
    case 5:
        removerecord();
        break;
    case 6:
        saveData();
        break;
    case 7:
        cout<<"\n Thank You!Exiting program.";
        break;
    default:
            cout<<"Invalid choice!Please try again.";
            break;
    }
}
    while(choice!=7);  // keep looping until the user chooses Exit
    return 0;
}
