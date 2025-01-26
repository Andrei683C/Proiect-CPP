#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;

class Patient
{
    private:
        unsigned int patientId,birth;
        string firstName,lastName,address,contact,condition;

    public:

   void setPatientId(unsigned int id)
   {patientId=id;}

   unsigned int getPatientId() const
   {return patientId;}

   void setBirth(unsigned int birthDate)
   {birth=birthDate;}

   unsigned int getBirth() const
   {return birth;}

   void setFirstName(string fname)
   {firstName=fname;}

   string getFirstName() const
   {return firstName;}

   void setLastName(string lname)
   {lastName=lname;}

   string getLastName() const
   {return lastName;}

   void setAddress(string address1)
   {address=address1;}

   string getAddress() const
   {return address;}

   void setContact(string cnct)
   {contact=cnct;}

   string getContact() const
   {return contact;}

   void setCondition(string conditie)
   {condition=conditie;}

   string  getCondition() const
   {return condition;}
};

unsigned int currentNumberOfPatients=0, idNumber=0;
Patient*patientList= new Patient [1];
fstream saveFile("save.txt");

void clearScreen() {
#ifdef _WIN32
    system("CLS"); // Windows
#else
    system("clear"); // Linux/macOS
#endif
}

void expandTable()
{
    currentNumberOfPatients++;
    Patient*newList= new Patient[currentNumberOfPatients+1];
    for(unsigned int i=0;i<currentNumberOfPatients;i++)
    {
         newList[i] = patientList[i];
    }

    delete[] patientList;
    patientList=newList;
}


void ToLower(string &word)
{
    for(int i=0;i<word.length();i++)
        word[i]=tolower(word[i]);
}



bool checkPreviousElements(string contact)
{
    for(int i=0;i<currentNumberOfPatients;i++)
        if(contact==patientList[i].getContact())
            return true;
    return false;
}

bool isNumeric(string isbn)
{
    for(int i=1;i<isbn.length();i++)
        if(!isdigit(isbn[i]))
            return false;
    return true;
}

void NewEntry()
{
    string value;
    int number;
    expandTable();
    idNumber++;
    patientList[currentNumberOfPatients-1].setPatientId(idNumber);;


    cout<<"Enter the first name of patient no."<<currentNumberOfPatients<<":";
    cin>>value;
    patientList[currentNumberOfPatients-1].setFirstName(value);

    cout<<"Enter the last name of patient no."<<currentNumberOfPatients<<":";
    cin>>value;
    patientList[currentNumberOfPatients-1].setLastName(value);


    while(true){
        cout<<"Enter the date of birth of patient no."<<currentNumberOfPatients<<":";
        cin>>number;

        if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a numeric value\n";
                }
        else
            if(number>2024 || number<1900)
                cout<<"Invalid year. Please try again.\n";
        else
        {
            patientList[currentNumberOfPatients-1].setBirth(number);
            break;
        }

    }

    cout<<"Enter the address of patient no."<<currentNumberOfPatients<<":";
    cin>>value;
    patientList[currentNumberOfPatients-1].setAddress(value);

    if(currentNumberOfPatients>0){
        while(true){
            cout<<"Enter the contact number of patient no."<<currentNumberOfPatients<<":";
            cin>>value;

            if(checkPreviousElements(value)){
                cout<<"This phone number already exists on the list. Please enter a new one. "<<endl;
            }
            else
                if((!isNumeric(value)) || value[0]!='+' || value.length()>20)
                   cout<<"This phone number is invalid. Please enter a new one.\n";
            else
            {
                patientList[currentNumberOfPatients-1].setContact(value);
                break;
            }
        }
    }
    else{
            while(true)
            {
                cout<<"Enter the phone number of patient no."<<currentNumberOfPatients+1<<":";
                cin>>value;
                if((!isNumeric(value)) || value[0]!='+' || value.length()>20)
                   cout<<"This phone number is invalid. Please enter a new one.\n";
                else
                    {
                        patientList[currentNumberOfPatients-1].setContact(value);
                        break;
                    }
            }

    }

    cout<<"Enter the medical condition of patient no."<<currentNumberOfPatients<<":";
    cin>>value;
    patientList[currentNumberOfPatients-1].setCondition(value);

}

void DeleteEntry(unsigned int i)
{

        for(i;i<currentNumberOfPatients-1;i++)
        {
            patientList[i].setPatientId(patientList[i+1].getPatientId());
            patientList[i].setFirstName(patientList[i+1].getFirstName());
            patientList[i].setLastName(patientList[i+1].getLastName());
            patientList[i].setBirth(patientList[i+1].getBirth());
            patientList[i].setAddress(patientList[i+1].getAddress());
            patientList[i].setContact(patientList[i+1].getContact());
            patientList[i].setCondition(patientList[i+1].getCondition());
        }
            currentNumberOfPatients--;

}

void EditEntry(unsigned int i)
{
    string input,word;
    unsigned int number;
    while(true){
        cout<<"Enter what you wish to edit or exit:\n1)First Name\n2)Last Name\n3)Date of Birth\n4)Address\n5)Contact Number\n6)Medical Condition\n7)Exit\n"<<endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Enter your option: ";
        getline(cin, input);
        ToLower(input);

        if(input=="7")
            break;

        else
        if(input=="1")
        {
            cout<<"Enter the first name of patient no."<<i+1<<":";
            cin>>word;
            patientList[i].setFirstName(word);
        }

        else
        if(input=="2")
        {
            cout<<"Enter the last name of patient no."<<i+1<<":";
            cin>>word;
            patientList[i].setLastName(word);
        }

        else
        if(input=="3")
        {
            while(true)
            {
                cout<<"Enter the date of birth of patient no."<<i+1<<":";
                cin>>number;

                if (cin.fail() || (number>2024 || number<1900)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a numeric value\n";
                        continue;
                    }
                else
                {
                    patientList[i].setBirth(number);
                    break;
                }
            }
        }


        else
        if(input=="6")
        {
            cout<<"Enter the medical condition of patient no."<<i+1<<":";
            cin>>word;
            patientList[i].setCondition(word);
        }
        else
        if(input=="4")
        {
            cout<<"Enter the address of patient no."<<i+1<<":";
             cin>>word;
            patientList[i].setAddress(word);
        }

        else
        if(input=="5")
        {
            while(true){
            cout<<"Enter the contact number of patient no."<<i+1<<":";
            cin>>word;

            if(checkPreviousElements(word)){
                cout<<"This phone number exists on the list. Please enter a new one. "<<endl;
            }
            else
                if((!isNumeric(word)) || word[0]!='+' || word.length()>20)
                   cout<<"This phone number is invalid. Please enter a new one.\n";
            else
            {
                patientList[i].setContact(word);
                break;
            }
            }
        }
        else
            cout<<"Invalid input. Please try again.\n";

}
}



void FindEntry()
{
    if(currentNumberOfPatients==0)
    {
        while(true){
            cout<<"There are no entries on the list, press enter to return to the main menu.";
            string exit;
            cin.ignore();
            getline(cin,exit);
            break;
        }
    }
    else
    while(true)
    {
         unsigned int i=0,j,number,ok=0;
         string key,option;
         clearScreen();
         cout<<"Enter the field you are looking for or exit:\n1)Patient ID\n2)First Name\n3)Last Name\n4)Date of Birth\n5)Address\n6)Contact Number\n7)Medical Condition\n8)Exit" <<endl; ;

         cout<<"Enter your option: ";
         getline(cin, key);
         ToLower(key);
         if(key=="8")
            break;
        else
         if(key=="6")
         {
             cout<<"Enter the contact number of the patient you are searching for: ";
             cin>>key;
             for(i=0;i<currentNumberOfPatients;i++)
            {
                if(patientList[i].getContact()==key)
                {
                 cout<<left<<setw(15)<<"Patient ID"<<setw(25)<<"First Name"<<setw(20)<<"Last Name"<<setw(15)<<"Date of Birth"<<setw(25)<<"Address"<<setw(20)<<"Contact Number"<<setw(15)<<"Medical Condition"<<endl;
                 cout << string(137, '-') << endl;
                 cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                 j=i;
                 ok++;
                 break;
                }
            }
         }
        else
         if(key=="1")
        {
            while(true)
            {
            cout<<"Enter the patient ID you are searching for: ";
            cin>>number;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter again\n";
                }
            else
                break;
            }
            for(i=0;i<currentNumberOfPatients;i++)
            {
                if(patientList[i].getPatientId()==number)
                {
                 cout<<left<<setw(15)<<"Patient ID"<<setw(25)<<"First Name"<<setw(20)<<"Last Name"<<setw(15)<<"Date of Birth"<<setw(25)<<"Address"<<setw(20)<<"Contact Number"<<setw(15)<<"Medical Condition"<<endl;
                 cout << string(137, '-') << endl;
                 cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                 ok++;
                 j=i;
                 break;
                }
            }
        }
        else
         if(key=="2")
        {
            cout<<"Enter the first name you are searching for: ";
            cin>>key;
            for(i=0;i<currentNumberOfPatients;i++)
            {
                if(patientList[i].getFirstName()==key)
                {
                    if(ok==0)
                    {
                        cout<<left<<setw(15)<<"Patient ID"<<setw(25)<<"First Name"<<setw(20)<<"Last Name"<<setw(15)<<"Date of Birth"<<setw(25)<<"Address"<<setw(20)<<"Contact Number"<<setw(15)<<"Medical Condition"<<endl;
                        cout << string(137, '-') << endl;
                        cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                        j=i;
                        ok++;
                    }
                    else
                    {
                        cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                        ok++;
                    }
                }
            }
        }
        else
         if(key=="3")
         {
            cout<<"Enter the last name you are searching for: ";
            cin>>key;
            for(i=0;i<currentNumberOfPatients;i++)
            {
                if(patientList[i].getLastName()==key)
                {
                   if(ok==0)
                    {
                        cout<<left<<setw(15)<<"Patient ID"<<setw(25)<<"First Name"<<setw(20)<<"Last Name"<<setw(15)<<"Date of Birth"<<setw(25)<<"Address"<<setw(20)<<"Contact Number"<<setw(15)<<"Medical Condition"<<endl;
                        cout << string(137, '-') << endl;
                        cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                        j=i;
                        ok++;
                    }
                    else
                    {
                        cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                        ok++;
                    }
                }
            }
         }
         else
          if(key=="4")
         {
            while(true)
            {
                cout<<"Enter the date of birth of the patient you are looking for: ";
                cin>>number;

                if (cin.fail() || (number>2024 || number<1900)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a numeric value\n";
                        continue;
                    }
                else
                    break;
            }
            for(i=0;i<currentNumberOfPatients;i++)
            {
                if(patientList[i].getBirth()==number)
                    if(ok==0)
                    {
                        cout<<left<<setw(15)<<"Patient ID"<<setw(25)<<"First Name"<<setw(20)<<"Last Name"<<setw(15)<<"Date of Birth"<<setw(25)<<"Address"<<setw(20)<<"Contact Number"<<setw(15)<<"Medical Condition"<<endl;
                        cout << string(137, '-') << endl;
                        cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                        ok++;
                        j=i;
                    }
                    else
                    {
                        cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                        ok++;
                    }

            }
         }
         else
          if(key=="5")
         {
            cout<<"Enter the address of the patient you are searching for: ";
            cin>>key;
            for(i=0;i<currentNumberOfPatients;i++)
            {
                if(patientList[i].getAddress()==key)
                {
                    if(ok==0)
                    {
                        cout<<left<<setw(15)<<"Patient ID"<<setw(25)<<"First Name"<<setw(20)<<"Last Name"<<setw(15)<<"Date of Birth"<<setw(25)<<"Address"<<setw(20)<<"Contact Number"<<setw(15)<<"Medical Condition"<<endl;
                        cout << string(137, '-') << endl;
                        cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                        j=i;
                        ok++;
                    }
                    else
                    {
                        cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                        ok++;
                    }
                }
            }
         }
         else
          if(key=="7")
         {
             cout<<"Enter the medical condition of the patient you are searching for: ";
            cin>>key;
            for(i=0;i<currentNumberOfPatients;i++)
            {
                if(patientList[i].getCondition()==key)
                {
                    if(ok==0)
                    {
                        cout<<left<<setw(15)<<"Patient ID"<<setw(25)<<"First Name"<<setw(20)<<"Last Name"<<setw(15)<<"Date of Birth"<<setw(25)<<"Address"<<setw(20)<<"Contact Number"<<setw(15)<<"Medical Condition"<<endl;
                        cout << string(137, '-') << endl;
                        cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                        j=i;
                        ok++;
                    }
                    else
                    {
                        cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
                        ok++;
                    }
                }
            }
         }

         if(ok==0)
            cout<<"The key wasn't found. Please input another key.\n";
         else
         {
             if(ok>1)
             {
                 while(true)
                {
                    cout<<"There are multiple patients with your selected criteria. Please type the patient ID of the patient you want to edit: ";
                    cin>>j;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter again\n";
                    }

                else
                    break;
                }
                     for(i=0;i<currentNumberOfPatients;i++)
                        if(patientList[i].getPatientId()==j)
                            break;
                    clearScreen();
                    cout<<left<<setw(15)<<"Patient ID"<<setw(25)<<"First Name"<<setw(20)<<"Last Name"<<setw(15)<<"Date of Birth"<<setw(25)<<"Address"<<setw(20)<<"Contact Number"<<setw(15)<<"Medical Condition"<<endl;
                    cout << string(137, '-') << endl;
                    cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";


             }
             while(true)
             {
                 if(ok>1)
                 {
                     cout<<"Please select one of the following options: \n";
                     cout<<"1)Edit\n";
                     cout<<"2)Delete\n";
                     cout<<"3)Exit\n";
                     cout<<"Enter your option: ";
                     cin>>option;
                     ToLower(option);

                    if(option=="1")
                     {
                        EditEntry(i);
                         break;
                     }
                     if(option=="2")
                     {
                        DeleteEntry(i);
                        break;
                     }
                     if(option=="3")
                        break;
                 }
                 else
                    if(ok==1)
                 {
                     cout<<"Please select one of the following options: \n";
                     cout<<"1)Edit\n";
                     cout<<"2)Delete\n";
                     cout<<"3)Exit\n";
                     cout<<"Enter your option: ";
                     cin>>option;
                     ToLower(option);

                    if(option=="1")
                     {
                        EditEntry(j);
                         break;
                     }
                     if(option=="2")
                     {
                        DeleteEntry(j);
                        break;
                     }
                     if(option=="3")
                        break;
                 }

             }

         }


    }
}



void ListEntries()
{
    if(currentNumberOfPatients==0)
    {
        while(true){
            cout<<"There are no entries on the list, press enter to return to the main menu.";
            string exit;
            cin.ignore();
            getline(cin,exit);
            return;
            break;
        }
    }
    else
    cout<<left<<setw(15)<<"Patient ID"<<setw(25)<<"First Name"<<setw(20)<<"Last Name"<<setw(15)<<"Date of Birth"<<setw(25)<<"Address"<<setw(20)<<"Contact Number"<<setw(15)<<"Medical Condition"<<endl;
    cout << string(137, '-') << endl;
    string exit;
    while(true)
    {
        for(unsigned int i=0;i<currentNumberOfPatients;i++)
        {
        cout<<left<<setw(15)<<patientList[i].getPatientId()<<setw(25)<<patientList[i].getFirstName()<<setw(20)<<patientList[i].getLastName()<<setw(15)<<patientList[i].getBirth()<<setw(25)<<patientList[i].getAddress()<<setw(20)<<patientList[i].getContact()<<setw(15)<<patientList[i].getCondition()<<"\n";
        }
        cout<<"\nPress enter to exit ";
        cin.ignore();
        getline(cin,exit);
        break;
    }


}

void DummyOperation()
{
    saveFile.open("save.txt", std::ios::out);
    saveFile.close();
}
void FileSave()
{
    saveFile.open("save.txt", std::ios::out);
    if(!saveFile)
        cout<<"Failed to open file for writing.";
    else
    if(currentNumberOfPatients==0)
        cout<<"You have nothing to save on the file,if it had something previously, now its empty.";
    else
    {
        saveFile<<currentNumberOfPatients<<endl;
        saveFile<<idNumber<<endl;
        for(int i=0;i<currentNumberOfPatients;i++)
        {
            saveFile<<patientList[i].getPatientId()<<" ";
            saveFile<<patientList[i].getFirstName()<<" ";
            saveFile<<patientList[i].getLastName()<<" ";
            saveFile<<patientList[i].getBirth()<<" ";
            saveFile<<patientList[i].getAddress()<<" ";
            saveFile<<patientList[i].getContact()<<" ";
            saveFile<<patientList[i].getCondition()<<" ";
            saveFile<<endl;
        }
        cout<<"Save was succesfull.";
    }
     saveFile.close();
}

void FileLoad()
{
    saveFile.open("save.txt", std::ios::in);
    if(!saveFile)
        cout<<"Failed to open file for reading.";
    else
    {
        saveFile>>currentNumberOfPatients;
        saveFile>>idNumber;
        delete[] patientList;
        patientList = new Patient[currentNumberOfPatients];
        int i=0;
        unsigned int data;
        string datas;
        while(i<currentNumberOfPatients && saveFile>>data)
        {
            patientList[i].setPatientId(data);
            saveFile>>datas;
            patientList[i].setFirstName(datas);
            saveFile>>datas;
            patientList[i].setLastName(datas);
            saveFile>>data;
            patientList[i].setBirth(data);
            saveFile>>datas;
            patientList[i].setAddress(datas);
            saveFile>>datas;
            patientList[i].setContact(datas);
            saveFile>>datas;
            patientList[i].setCondition(datas);
            i++;
        }
        cout<<"Loading was succesfull.";
    }
     saveFile.close();
}

void SwitchEntries(int i,int j)
{
    Patient temp = patientList[i];
    patientList[i]=patientList[j];
    patientList[j]=temp;
}
void SortEntries()
{
   int i,j;
   string key,option;
   if(currentNumberOfPatients==0)
    {
        while(true){
            cout<<"There are no entries on the list, press enter to return to the main menu.";
            string exit;
            cin.ignore();
            getline(cin,exit);
            return;
            break;
        }
    }
    else
   while(true)
   {
       clearScreen();
       cout<<"Enter the field by which you wish to sort the entries or exit:\n1)Patient ID\n2)First Name\n3)Last Name\n4)Date of Birth\n5)Address\n6)Contact Number\n7)Medical Condition\n8)Exit\n";
       cout<<"Enter your option: ";
       cin.ignore(numeric_limits<streamsize>::max(), '\n');
       cin>>key;
       ToLower(key);
       if(key=="2")
       {
          cout<<"In what order do you wish to sort?:\n1)Ascending\n2)Descending\n";
          cout<<"Enter your option: ";
          cin>>option;
          if(option=="2")
          {
            for(i=0;i<currentNumberOfPatients-1;i++)
            for(j=i+1;j<currentNumberOfPatients;j++)
                {
                    if(patientList[i].getFirstName()>patientList[j].getFirstName())
                        SwitchEntries(i,j);
                }
          }
          else
            if(option=="2")
              {
                  for(i=0;i<currentNumberOfPatients-1;i++)
                    for(j=i+1;j<currentNumberOfPatients;j++)
                    {
                        if(patientList[i].getFirstName()<patientList[j].getFirstName())
                            SwitchEntries(i,j);
                    }
              }
       }

      if(key=="3")
       {
          cout<<"Do you wish to sort in ascending or descending order?:\n1)Ascending\n2)Descending\n";
          cout<<"Enter your option: ";
          cin>>option;
          if(option=="1")
          {
              for(i=0;i<currentNumberOfPatients-1;i++)
            for(j=i+1;j<currentNumberOfPatients;j++)
                {
                    if(patientList[i].getLastName()>patientList[j].getLastName())
                        SwitchEntries(i,j);
                }
          }
          else
            if(option=="2")
              {
                  for(i=0;i<currentNumberOfPatients-1;i++)
                    for(j=i+1;j<currentNumberOfPatients;j++)
                    {
                        if(patientList[i].getLastName()<patientList[j].getLastName())
                            SwitchEntries(i,j);
                    }
              }
       }
       if(key=="1")
       {
          cout<<"Do you wish to sort in ascending or descending order?:\n1)Ascending\n2)Descending\n";
          cout<<"Enter your option: ";
          cin>>option;
          if(option=="1")
          {
              for(i=0;i<currentNumberOfPatients-1;i++)
            for(j=i+1;j<currentNumberOfPatients;j++)
                {
                    if(patientList[i].getPatientId()>patientList[j].getPatientId())
                        SwitchEntries(i,j);
                }
          }
          else
            if(option=="2")
              {
                  for(i=0;i<currentNumberOfPatients-1;i++)
                    for(j=i+1;j<currentNumberOfPatients;j++)
                    {
                        if(patientList[i].getPatientId()<patientList[j].getPatientId())
                            SwitchEntries(i,j);
                    }
              }
       }
       if(key=="4")
       {
          cout<<"Do you wish to sort in ascending or descending order?:\n1)Ascending\n2)Descending\n";
          cout<<"Enter your option: ";
          cin>>option;
          if(option=="1")
          {
              for(i=0;i<currentNumberOfPatients-1;i++)
            for(j=i+1;j<currentNumberOfPatients;j++)
                {
                    if(patientList[i].getBirth()>patientList[j].getBirth())
                        SwitchEntries(i,j);
                }
          }
          else
            if(option=="2")
              {
                  for(i=0;i<currentNumberOfPatients-1;i++)
                    for(j=i+1;j<currentNumberOfPatients;j++)
                    {
                        if(patientList[i].getBirth()<patientList[j].getBirth())
                            SwitchEntries(i,j);
                    }
              }
       }
       if(key=="5")
       {
          cout<<"Do you wish to sort in ascending or descending order?:\n1)Ascending\n2)Descending\n";
          cout<<"Enter your option: ";
          cin>>option;
          if(option=="1")
          {
              for(i=0;i<currentNumberOfPatients-1;i++)
            for(j=i+1;j<currentNumberOfPatients;j++)
                {
                    if(patientList[i].getAddress()>patientList[j].getAddress())
                        SwitchEntries(i,j);
                }
          }
          else
            if(option=="2")
              {
                  for(i=0;i<currentNumberOfPatients-1;i++)
                    for(j=i+1;j<currentNumberOfPatients;j++)
                    {
                        if(patientList[i].getAddress()<patientList[j].getAddress())
                            SwitchEntries(i,j);
                    }
              }
       }
       if(key=="6")
       {
          cout<<"Do you wish to sort in ascending or descending order?:\n1)Ascending\n2)Descending\n";
          cout<<"Enter your option: ";
          cin>>option;
          if(option=="1")
          {
              for(i=0;i<currentNumberOfPatients-1;i++)
            for(j=i+1;j<currentNumberOfPatients;j++)
                {
                    if(patientList[i].getContact()>patientList[j].getContact())
                        SwitchEntries(i,j);
                }
          }
          else
            if(option=="2")
              {
                  for(i=0;i<currentNumberOfPatients-1;i++)
                    for(j=i+1;j<currentNumberOfPatients;j++)
                    {
                        if(patientList[i].getContact()<patientList[j].getContact())
                            SwitchEntries(i,j);
                    }
              }
       }
       if(key=="7")
       {
          cout<<"Do you wish to sort in ascending or descending order?:\n1)Ascending\n2)Descending\n";
          cout<<"Enter your option: ";
          cin>>option;
          if(option=="1")
          {
              for(i=0;i<currentNumberOfPatients-1;i++)
            for(j=i+1;j<currentNumberOfPatients;j++)
                {
                    if(patientList[i].getCondition()>patientList[j].getCondition())
                        SwitchEntries(i,j);
                }
          }
          else
            if(option=="2")
              {
                  for(i=0;i<currentNumberOfPatients-1;i++)
                    for(j=i+1;j<currentNumberOfPatients;j++)
                    {
                        if(patientList[i].getCondition()<patientList[j].getCondition())
                            SwitchEntries(i,j);
                    }
              }
       }
       if(key=="8")
        break;
   }
}

int main()
{
    DummyOperation();
    string option;
    bool terminate=false;
    while(terminate==false)
    {
         cout<<"Please select one of the following options: \n";
         cout<<"1)New\n";
         cout<<"2)Find\n";
         cout<<"3)List\n";
         cout<<"4)Sort\n";
         cout<<"5)Save\n";
         cout<<"6)Load\n";
         cout<<"7)Exit\n";
         cout<<"Enter your option: ";
         cin>>option;
         ToLower(option);
         if(option=="1")
            NewEntry();
        else
         if(option=="2")
            FindEntry();
        else
         if(option=="3")
            ListEntries();
        else
         if(option=="4")
            SortEntries();
        else
         if(option=="5")
            FileSave();
        else
         if(option=="6")
            FileLoad();
        else
         if(option=="7")
            terminate=true;
        else
        while(true){
            cout<<"Invalid option, press enter to try again.";
            string exit;
            cin.ignore();
            getline(cin,exit);
            break;
        }

        clearScreen();
    }

    return 0;
}
