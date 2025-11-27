#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;
/*
const string UserFileName = "User.txt";
  struct sClients
  {
  	string AccountNumber;
  	string PinCode;
  	string Name;
  	string Phone;
  	int AccountBalance;
  
  };
  
  sClients ReadNewClient()
  {
  	sClients Client;
  
  	cout << "\nEnter Users's information \n";
  
  	cout << "Username " << endl;
  	getline(cin >> ws, Client.AccountNumber);
  
  	cout << "Passwordd  " << endl;
  	getline(cin, Client.PinCode);
  
  	cout << "Permissions " << endl;
  	getline(cin, Client.Name);
  
  	cout << "Enter  phone " << endl;
  	getline(cin, Client.Phone);
  
  	cout << "Enter countBalance " << endl;
  	cin >> Client.AccountBalance;
  
  	return Client;
  }
  
  string ConvertRecordToLine(sClients Client, string Sprator = " #//# ")
  {
  	string sLine;
  	sLine += Client.AccountNumber + Sprator;
  
  	sLine += Client.PinCode + Sprator;
  
  	sLine += Client.Name + Sprator;
  
  	sLine += Client.Phone + Sprator;
  
  	sLine += to_string(Client.AccountBalance) + Sprator;
  
  	return sLine;
  }
  
  void AddDataLineToFile(string FileName, string DataLine)
  {
  	fstream MyFile;
  
    MyFile.open(FileName, ios::out | ios::app);
  
  	if (MyFile.is_open())
  	{
  
  		MyFile << DataLine << endl;
  		MyFile.close();
  	}
  
  }
  
  void AddNewClient()
  {
  
  	sClients Client;
  	Client = ReadNewClient();
  
  	AddDataLineToFile(UserFileName, ConvertRecordToLine(Client));
  
  }
  
  void AddAllClients()
  {
  	char AddMore = 'y';
  
  	do
  	{
  		system("cls");
  		cout << "Adding new client : \n\n";
  		AddNewClient();
  
  		cout << "\nClients added succssfuly , do you want add more clients ? ";
  		cin >> AddMore;
  	} while (AddMore == 'y' || AddMore == 'Y');
  }
  
  
  
  int main()
  {
  
  	AddAllClients();
  
  }

  
  */



struct sUser
{
	string UserName; string Password; int Permissions; bool MarkForDelete = false;
};


enum enTransactionsMenueOptions 
{ eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 }; 


enum enManageUsersMenueOptions 
{ eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6 }; 


enum enMainMenueOption
{ eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eManageUsers = 7, eExit = 8 };


enum enMainMenuePermissions { eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient= 4, pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64 }; 

const string ClientFileName = "Client.txt"; 
const string UserFileName = "User.txt";

sUser CurrentUser;
void ShowMainMenue(); 
void ShowTransactionsMenue(); 
void ShowManageUsersMenue(); 
bool CheckAccessPermission(enMainMenuePermissions Permission);
void Login(); 
 
struct sClient
{ string AccountNumber; string PinCode; string Name; string Phone; double AccountBalance; bool MarkForDelete = false; };

vector<string> SpiltString(string S1, string Delim )
{
    vector<string>vString;

    int pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);

        if (sWord != "")
        {
            vString.push_back(sWord);

        }

        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}




sClient ConvertClientLineToRecord(string Line, string Spraetor="#//#")
{
    vector<string>vClient;
    sClient Client;

    vClient = SpiltString(Line, Spraetor);
    Client.AccountNumber = vClient[0];
    Client.PinCode = vClient[1];
    Client.Name = vClient[2];
    Client.Phone = vClient[3];
    Client.AccountBalance = stod(vClient[4]);

    return Client;
}


sUser ConvertUserLineToRecord(string Line, string Spraetor ="#//#")
{
    vector<string>vUserData;
    sUser User;

    vUserData = SpiltString(Line, Spraetor);
  User.UserName = vUserData[0];
  User.Password = vUserData[1];
  User.Permissions = stoi(vUserData[2]);
   

    return User;
}




string ConvertRecordToLine(sClient Client, string Sprator="#//#")
{
    string sLine;
    sLine += Client.AccountNumber + Sprator;

    sLine += Client.PinCode + Sprator;

    sLine += Client.Name + Sprator;

    sLine += Client.Phone + Sprator;

    sLine += to_string(Client.AccountBalance) + Sprator;

    return sLine;
}



string ConvertUserRecordToLine(sUser User, string Sprator="#//#")
{
    string sLine;
    sLine += User.UserName + Sprator;

    sLine += User.Password+ Sprator;

    sLine += to_string(User.Permissions )+ Sprator;

   

    return sLine;
}










bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    vector<sClient>vClient;
    fstream MyFile;

    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertClientLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClient.push_back(Client);
        }

        MyFile.close();
    }

    return false;

}





bool UserExistsByUserName(string UserName, string FileName)
{
   
    fstream MyFile;

    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {
            User = ConvertUserLineToRecord(Line);
            if (User.UserName == UserName)
            {
                MyFile.close();
                return true;
            }
            
        }

        MyFile.close();
    }

    return false;

}









sClient ReadNewClient()
{
    sClient Client;

    cout << "\nEnter Client's information \n";

    cout << "Account Number " << endl;
    getline(cin >> ws, Client.AccountNumber);
    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientFileName))
    {
        cout << "\nClient with (" << Client.AccountNumber << ") already exists , Enter another Account Number ? ";
        getline(cin >> ws, Client.AccountNumber);
    }
    cout << "Enter  PinCode " << endl;
    getline(cin, Client.PinCode);

    cout << "Enter  Name " << endl;
    getline(cin, Client.Name);

    cout << "Enter  phone " << endl;
    getline(cin, Client.Phone);

    cout << "Enter countBalance " << endl;
    cin >> Client.AccountBalance;

    return Client;
}

int ReadPermissions()
{
    int Permissions = 0;
    char Answer = 'n';

    cout << "Do you want to give full access ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        return -1;
    }

    cout << "\nDo you want to give access to : \n ";  
    cout << "\nShow Client List? y/n? ";    
    cin >> Answer; if (Answer == 'y' || Answer == 'Y')
    { Permissions += enMainMenuePermissions::pListClients; }   
    cout << "\nAdd New Client? y/n? ";  
    cin >> Answer; if (Answer == 'y' || Answer == 'Y') 
    { Permissions += enMainMenuePermissions::pAddNewClient; }    
    cout << "\nDelete Client? y/n? ";     cin >> Answer; if (Answer == 'y' || Answer == 'Y') 
    { Permissions += enMainMenuePermissions::pDeleteClient; }  
    cout << "\nUpdate Client? y/n? ";     cin >> Answer; if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pUpdateClients;
    }
    cout << "\nFind Client? y/n? ";   
    cin >> Answer; if (Answer == 'y' || Answer == 'Y')
    { Permissions += enMainMenuePermissions::pFindClient; }  
    cout << "\nTransactions? y/n? ";     cin >> Answer; if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pTranactions;
    }

    cout << "\nManage Users? y/n? ";   
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    { 
        Permissions += enMainMenuePermissions::pManageUsers;
    }
    
    
        return Permissions;
}


sUser ReadNewUser()
{
    sUser User;

    cout << "\nEnter User's information \n";

    cout << "User Name " << endl;
    getline(cin >> ws, User.UserName);
    while (UserExistsByUserName(User.UserName, UserFileName))
    {
        cout << "\nUser with (" << User.UserName << ") already exists , Enter another User Name ? ";
        getline(cin >> ws, User.UserName);
    }
    cout << "Enter  Password " << endl;
    getline(cin, User.Password);

    User.Permissions = ReadPermissions();

    return User;
}




vector<sClient>LoadClientDataFromFile(string FileName)
{

    vector<sClient>vClient;
    fstream MyFile;

    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertClientLineToRecord(Line);
            vClient.push_back(Client);
        }

        MyFile.close();
    }

    return vClient;


}







vector<sUser>LoadUserDataFromFile(string FileName)
{

    vector<sUser>vUser;
    fstream MyFile;

    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {
            User = ConvertUserLineToRecord(Line);
            vUser.push_back(User);
        }

        MyFile.close();
    }

    return vUser;


}


void PrintClientRecord(sClient Client)
{
    cout << "|  " << setw(15) << left << Client.AccountNumber;
    cout << "|  " << setw(10) << left << Client.PinCode;
    cout << "|  " << setw(30) << left << Client.Name;
    cout << "|  " << setw(12) << left << Client.Phone;
    cout << "|  " << setw(12) << left << Client.AccountBalance;

}

void PrintUserRecord(sUser User)
{
    cout << "|  " << setw(15) << left << User.UserName;
    cout << "|  " << setw(10) << left << User.Password;
    cout << "|  " << setw(40) << left << User.Permissions;
  
}

void ShowAccessDeniedMessage()
{
    cout << "\n------------------------------------------------------\n  " ;
    cout << "| Access Denied , \nYou dont have Permission To Do This, \n please Conact Yor Admin . "  ;
    cout << "\n------------------------------------------------------\n  ";
}



void ShowAllClientsScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pListClients))
    {
        ShowAccessDeniedMessage();
        return;
    }
    vector<sClient>vClient = LoadClientDataFromFile(ClientFileName);
    cout << "                  Client (" << vClient.size() << ")              ";
    cout << "\n------------------------------------------------------------------------------------------------------\n";
    cout << "|  " << left << setw(15) << "AccountNumber ";
    cout << "|  " << left << setw(10) << "PinCode ";
    cout << "|  " << left << setw(30) << "Name ";
    cout << "|  " << left << setw(12) << "Phone ";
    cout << "|  " << left << setw(12) << "Account Balance ";
    cout << "\n------------------------------------------------------------------------------------------------------\n";

    for (sClient Client : vClient)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n------------------------------------------------------------------------------------------------------\n";

}




void ShowAllUsersScreen()
{
    vector<sUser>vUser = LoadUserDataFromFile(UserFileName);
    cout << "                  User List(" << vUser.size() << ")              ";
    cout << "\n------------------------------------------------------------------------------------------------------\n";
    cout << "|  " << left << setw(15) << "User Nmae ";
    cout << "|  " << left << setw(10) << "Password ";
    cout << "|  " << left << setw(40) << "Permissions ";
    cout << "\n------------------------------------------------------------------------------------------------------\n";

    if (vUser.size() == 0)
        cout << "\t\t\t\t No Users Avaliable in the system!";
    else

    for (sUser User : vUser)
    {
        PrintUserRecord(User);
        cout << endl;
    }
    cout << "\n------------------------------------------------------------------------------------------------------\n";

}

void PrintClientRecordBalanceLine(sClient Client)
{
    cout << "|  " << setw(15) << left << Client.AccountNumber;
    cout << "|  " << setw(30) << left << Client.Name;
    cout << "|  " << setw(12) << left << Client.AccountBalance;

}

void ShowTotalBalances()
{
    vector<sClient>vClient = LoadClientDataFromFile(ClientFileName);
    cout << "                  Client (" << vClient.size() << ")              ";
    cout << "\n------------------------------------------------------------------------------------------------------\n";
    cout << "|  " << left << setw(15) << "AccountNumber ";
    cout << "|  " << left << setw(30) << "Name ";
    cout << "|  " << left << setw(12) << "Account Balance ";
    cout << "\n------------------------------------------------------------------------------------------------------\n";

    double TotalBalnces = 0;
    if (vClient.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Avaliable in the system!";
    }

    else
    {
        for (sClient Client : vClient)
        {
            PrintClientRecordBalanceLine(Client);
            TotalBalnces += Client.AccountBalance;
            cout << endl;
        }
        cout << "\n------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\t     Total balances = " << TotalBalnces;
    }
}



void PrintClientCard(sClient Client) 
{ cout << "\nThe following are the client details:\n";  
cout << "-----------------------------------";   
cout << "\nAccout Number: " << Client.AccountNumber;  
cout << "\nPin Code     : " << Client.PinCode;   
cout << "\nName         : " << Client.Name;   
cout << "\nPhone        : " << Client.Phone;  
cout << "\nAccount Balance: " << Client.AccountBalance;  
cout << "\n-----------------------------------\n"; 

}

void PrintUserCard(sUser User)
{ cout << "\nThe following are the user details:\n"; 
cout << "-----------------------------------";   
cout << "\nUsername    : " << User.UserName;   
cout << "\nPassword    : " << User.Password;   
cout << "\nPermissions : " << User.Permissions;  
cout << "\n-----------------------------------\n"; 

}






bool FindClientByAccountNumber(string AccountNumber, vector<sClient>vClient, sClient& Client)
{

    for (sClient C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool FindUserByUserName(string UserName, vector<sUser>vUser, sUser& User)
{

    for (sUser U : vUser)
    {
        if (U.UserName == UserName)
        {
            User = U;
            return true;
        }
    }
    return false;
}


bool FindUserByUserNameAndPassWord(string UserName , string Password, sUser& User)
{
    vector<sUser>vUser = LoadUserDataFromFile(UserFileName);

    for (sUser U : vUser)
    {
        if (U.UserName == UserName && U.Password==Password)
        {
            User = U;
            return true;
        }
    }
    return false;
}



sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "Enter  PinCode " << endl;
    getline(cin >> ws, Client.PinCode);

    cout << "Enter  Name " << endl;
    getline(cin, Client.Name);

    cout << "Enter  phone " << endl;
    getline(cin, Client.Phone);

    cout << "Enter countBalance " << endl;
    cin >> Client.AccountBalance;


    return Client;
}



sUser ChangeUserRecord(string Username)
{
    sUser User;
    User.UserName = Username;

    cout << "Enter  Password ? " << endl;
    getline(cin >> ws, User.Password);

    User.Permissions = ReadPermissions();

    return User;
}



bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClient)
{
    for (sClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}


bool MarkUserForDeleteByUserName(string UserName, vector<sUser>& vUser)
{
    for (sUser& U : vUser)
    {
        if (U.UserName == UserName)
        {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}






vector <sClient>SaveClientDataToFile(string FileName, vector<sClient>vClient)
{
    fstream MyFile;

    string DataLine;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (sClient C : vClient)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClient;
}


vector <sUser>SaveUserDataToFile(string FileName, vector<sUser>vUser)
{
    fstream MyFile;

    string DataLine;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (sUser U : vUser)
        {
            if (U.MarkForDelete  == false)
            {
                DataLine = ConvertUserRecordToLine(U);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUser;
}


void AddDataLineToFile(string FileName, string sDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile<<sDataLine<<endl;

        MyFile.close();

    }
}


void AddNewClient()
{

    sClient Client;
    Client = ReadNewClient();

    AddDataLineToFile(ClientFileName, ConvertRecordToLine(Client));

}



void AddNewUser()
{

    sUser User;
    User = ReadNewUser();

    AddDataLineToFile(UserFileName, ConvertUserRecordToLine(User));

}



void AddAllClients()
{
    char AddMore = 'y';

    do
    {
        system("cls");
        cout << "Adding new client : \n\n";
        AddNewClient();

        cout << "\nClients added succssfuly , do you want add more clients ? ";
        cin >> AddMore;
    } while (AddMore == 'y' || AddMore == 'Y');
}



void AddAllUsers()
{
    char AddMore = 'y';

    do
    {
        system("cls");
        cout << "Adding new User : \n\n";
        AddNewUser();

        cout << "\nUserss added succssfuly , do you want add more Users ? ";
        cin >> AddMore;
    } while (AddMore == 'y' || AddMore == 'Y');
}



bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClient)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientRecord(Client);

        cout << "\nAre you sure to delete the Client ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
            SaveClientDataToFile(ClientFileName, vClient);

            vClient = LoadClientDataFromFile(ClientFileName);

            cout << "\n\n Client deleted succssfuly ";
            return true;

        }

    }
    else
    {
        cout << "\nClient With account number (" << AccountNumber << ") Not found ";
        return false;
    }
}




bool DeleteUserByUserName(string UserName, vector<sUser>& vUser)
{

    if (UserName == "Admin")
    {
        cout << "\n\nYou cannot Delete this User";
        return false;
    }
    sUser User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUser, User))
    {
        PrintUserRecord(User);

        cout << "\nAre you sure to delete the User ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUserName(UserName, vUser);
            SaveUserDataToFile(UserFileName, vUser);

            vUser = LoadUserDataFromFile(UserFileName);

            cout << "\n\n User deleted succssfuly ";
            return true;

        }

    }
    else
    {
        cout << "\nUser With User Name  (" << UserName << ") Not found ";
        return false;
    }
}








bool UpDataClientByAccountNumber(string AccountNumber, vector<sClient>& vClient)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientRecord(Client);

        cout << "\nAre you sure you want updata Client ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClient)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientDataToFile(ClientFileName, vClient);
            vClient = LoadClientDataFromFile(ClientFileName);

            cout << "\n\n Client updata succssfuly ";
            return true;

        }

    }
    else
    {
        cout << "\nClient With account number (" << AccountNumber << ") Not found ";
        return false;
    }
}





bool UpDataUserByUserName(string UserName, vector<sUser>& vUser)
{
    sUser User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUser, User))
    {
        PrintUserRecord(User);

        cout << "\nAre you sure you want updata User ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sUser& U : vUser)
            {
                if (U.UserName == UserName)
                {
                    U = ChangeUserRecord(UserName);
                    break;
                }
            }
            SaveUserDataToFile(UserFileName, vUser);
            vUser = LoadUserDataFromFile(UserFileName);

            cout << "\n\n User updata succssfuly ";
            return true;

        }

    }
    else
    {
        cout << "\nUser With User name (" << UserName << ") Not found ";
        return false;
    }
}





bool DepositToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClient)
{
    char Answer;
    cout << "\nAre you sure you want perform this transactions ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient& C : vClient)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientDataToFile(ClientFileName, vClient);
                cout << "\nDone Succssfuly ,New balance is : " << C.AccountBalance;
                return true;
            }
        }
        return false;
    }



}



string ReadAccountNumber()
{
    string AccountNumber;
    cout << "\nEnter Client Account number ? \n";
    cin >> AccountNumber;
    return AccountNumber;
}


string ReadUserName()
{
    string UserName;
    cout << "\nEnter User Name ? \n";
    cin >> UserName;
    return UserName;
}








void ShowListUsersScreen()
{
    ShowAllUsersScreen();
}



void ShowAddNewUsersScreen()
{
    cout << "-----------------------------------------\n";
    cout << "            Add New User screen        \n";
    cout << "-----------------------------------------\n";
    AddAllUsers();

}




void ShowDeleteUserScreen()
{
    cout << "\n-------------------------------------------------------\n";
    cout << "\tDelate User Screen ";
    cout << "\n-------------------------------------------------------\n";

    vector<sUser>vUser = LoadUserDataFromFile(UserFileName);

    string UserName= ReadUserName();


    DeleteUserByUserName(UserName, vUser);

}




void ShowUpDataUserScreen()
{
    cout << "\n-------------------------------------------------------\n";
    cout << "\tUpData User info Screen ";
    cout << "\n-------------------------------------------------------\n";

    vector<sUser>vUser = LoadUserDataFromFile(UserFileName);

    string UserName =ReadUserName();

    
    UpDataUserByUserName(UserName, vUser);

}












void ShowDeleteClientScreen()
{

    if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
    {
        ShowAccessDeniedMessage();
        return;
    }
    cout << "\n-------------------------------------------------------\n";
    cout << "\tDelate Client Screen ";
    cout << "\n-------------------------------------------------------\n";

    vector<sClient>vClient = LoadClientDataFromFile(ClientFileName);

    string AccountNumber = ReadAccountNumber();


    DeleteClientByAccountNumber(AccountNumber, vClient);

}






void ShowUpDataClientScreen()
{


    if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients))
    {
        ShowAccessDeniedMessage();
        return;
    }

    cout << "\n-------------------------------------------------------\n";
    cout << "\tUpData Client info Screen ";
    cout << "\n-------------------------------------------------------\n";

    vector<sClient>vClient = LoadClientDataFromFile(ClientFileName);

    string AccountNumber = ReadAccountNumber();


    UpDataClientByAccountNumber(AccountNumber, vClient);

}



void ShowAddNewClientsScreen()
{

    if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
    {
        ShowAccessDeniedMessage();
        return;
    }
    cout << "-----------------------------------------\n";
    cout << "            Add New Client screen        \n";
    cout << "-----------------------------------------\n";
    AddAllClients();

}







void ShowFindClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
    {
        ShowAccessDeniedMessage();
        return;
    }
    cout << "\n-------------------------------------------------------\n";
    cout << "\tFind Client info Screen ";
    cout << "\n-------------------------------------------------------\n";

    vector<sClient>vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadAccountNumber();
    sClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientRecord(Client);
    }
    else
    {
        cout << "\nClient with Account number (" << AccountNumber << ") Not found";
    }
}


void ShowFindUserScreen()
{
    
    cout << "\n-------------------------------------------------------\n";
    cout << "\tFind User info Screen ";
    cout << "\n-------------------------------------------------------\n";

    vector<sUser>vUser = LoadUserDataFromFile(UserFileName);
    string UserName = ReadUserName();
    sUser User;

    if (FindUserByUserName(UserName, vUser, User))
    {
        PrintUserRecord(User);
    }
    else
    {
        cout << "\nUser with User name (" << UserName << ") Not found";
    }
}




void ShowEndScreen()
{
    cout << "----------------------------------------------\n";
    cout << "              Program Ends :-)                \n";
    cout << "----------------------------------------------\n";

}




void ShowDepositScreen()
{

    cout << "------------------------------------------\n";
    cout << "               Deposit Screen          \n";
    cout << "------------------------------------------\n";
    sClient Client;
    vector<sClient>vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient With (" << AccountNumber << ") Not found";
        AccountNumber = ReadAccountNumber();
    }

    PrintClientRecord(Client);

    double Amount;
    cout << "\nPlease Enter Deposit Amount ";
    cin >> Amount;

    DepositToClientByAccountNumber(AccountNumber, Amount, vClients);
}





void ShowWithDrawScreen()
{

    cout << "------------------------------------------\n";
    cout << "               Withdraw Screen          \n";
    cout << "------------------------------------------\n";
    sClient Client;
    vector<sClient>vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient With (" << AccountNumber << ") Not found";
        AccountNumber = ReadAccountNumber();
    }

    PrintClientRecord(Client);

    double Amount;
    cout << "\nPlease Enter withdraw Amount ";
    cin >> Amount;

    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance , you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "\nPease enter another amount ?";
        cin >> Amount;
    }
    DepositToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}



bool CheckAccessPermission(enMainMenuePermissions Permission)
{
    if (CurrentUser.Permissions == Permission)
        return true;
    if ((Permission & CurrentUser.Permissions) == Permission)
        return true;
    else
        return false;

}




void GoPackToMainMenue()
{
    cout << "\nPress any kay to go back to main menue ...";
    system("pause>0");
    ShowMainMenue();
}


void GoPackToTransactionsMenue()
{
    cout << "\nPress any kay to go back to transactions menue ...";
    system("pause>0");
    ShowTransactionsMenue();
}


void GoPackToManageUsersMenue()
{
    cout << "\nPress any kay to go back to transactions menue ...";
    system("pause>0");
   ShowManageUsersMenue();
}

short ReadTransactionsMenueOption()
{
    short Choice;

    cout << "Chooce what do you want to do ? [1 to 4] ? \n";
    cin >> Choice;
    return Choice;
}



void PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOPtions)
{
    switch (TransactionsMenueOPtions)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");

        ShowDepositScreen();
        GoPackToTransactionsMenue();
        break;
    }
    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");

        ShowWithDrawScreen();
        GoPackToTransactionsMenue();
        break;
    }
    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");

        ShowTotalBalances();
        GoPackToTransactionsMenue();

        break;
    }
    case enTransactionsMenueOptions::eShowMainMenue:
    {
        system("cls");


        ShowMainMenue();

        break;

    }

    }
}




void ShowTransactionsMenue()
{


    if (!CheckAccessPermission(enMainMenuePermissions::pTranactions))
    {
        ShowAccessDeniedMessage();
        GoPackToMainMenue();
        return;
    }

    system("cls");
    cout << "====================================================================================\n";


    cout << "                                    Transactions Menue Screen                             \n";
    cout << "====================================================================================\n";


    cout << "            [1] Deposit." << endl;

    cout << "            [2] Withdraw." << endl;

    cout << "            [3] Total Balances." << endl;

    cout << "            [4] Main Menue." << endl;


    cout << "====================================================================================\n";

    PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());


}

short ReadMainMenueOption()
{
    short Choice=0;

    cout << "Chooce what do you want to do ? [1 to 8] ? \n";
    cin >> Choice;
    return Choice;
}






void PerformManageUserMenueOption(enManageUsersMenueOptions ManageUsersMenueOptions)
{
    switch (ManageUsersMenueOptions)
    {
    case enManageUsersMenueOptions::eListUsers:
    {
        system("cls");

        ShowAllUsersScreen();
        GoPackToManageUsersMenue();
        break;
    }
    case enManageUsersMenueOptions::eAddNewUser:
    {
        system("cls");

        ShowAddNewUsersScreen();
        GoPackToManageUsersMenue();
        break;
    }
    case enManageUsersMenueOptions::eDeleteUser:
    {
        system("cls");

        ShowDeleteUserScreen();
        GoPackToManageUsersMenue();

        break;
    }
    case enManageUsersMenueOptions::eUpdateUser:
    {
        system("cls");

        ShowUpDataUserScreen();
        GoPackToManageUsersMenue();
        break;

    }
    case enManageUsersMenueOptions::eFindUser:
    {
        system("cls");

        ShowFindUserScreen();
        GoPackToManageUsersMenue();
        break;

    }
    case enManageUsersMenueOptions::eMainMenue:
    {
        system("cls");

        ShowMainMenue();
       
    }
    
    }
}


short ReadManagUserMenueOption()
{
    short Choice = 0;

    cout << "Chooce what do you want to do ? [1 to 6] ? \n";
    cin >> Choice;
    return Choice;
}


void ShowManageUsersMenue()
{
    system("cls");
    cout << "====================================================================================\n";


    cout << "                                    Manage Users Menue Screen                             \n";
    cout << "====================================================================================\n";


    cout << "            [1] Show List Users." << endl;

    cout << "            [2] Add New User." << endl;

    cout << "            [3] Delete User." << endl;

    cout << "            [4] Updata User Info." << endl;

    cout << "            [5] Find User." << endl;

    cout << "            [6] Main Menue." << endl;

   

    cout << "====================================================================================\n";


    PerformManageUserMenueOption((enManageUsersMenueOptions)ReadManagUserMenueOption());

}








void PerformMainMenueOption(enMainMenueOption MainMenueOPtions)
{
    switch (MainMenueOPtions)
    {
    case enMainMenueOption::eListClients:
    {
        system("cls");

        ShowAllClientsScreen();
        GoPackToMainMenue();
        break;
    }
    case enMainMenueOption::eAddNewClient:
    {
        system("cls");

        ShowAddNewClientsScreen();
        GoPackToMainMenue();
        break;
    }
    case enMainMenueOption::eDeleteClient:
    {
        system("cls");

        ShowDeleteClientScreen();
        GoPackToMainMenue();

        break;
    }
    case enMainMenueOption::eUpdateClient:
    {
        system("cls");

        ShowUpDataClientScreen();
        GoPackToMainMenue();

        break;

    }
    case enMainMenueOption::eFindClient:
    {
        system("cls");

        ShowFindClientScreen();
        GoPackToMainMenue();
        break;

    }
    case enMainMenueOption::eShowTransactionsMenue:
    {
        system("cls");

        ShowTransactionsMenue();
        GoPackToMainMenue();

        break;
    }
    case enMainMenueOption::eManageUsers:
    {
        system("cls");
        ShowManageUsersMenue();
        GoPackToMainMenue();

        break;
    }

    case enMainMenueOption::eExit:
    {
        system("cls");
        Login();

        break;
    }
    }
}


void ShowMainMenue()
{
    system("cls");
    cout << "====================================================================================\n";


    cout << "                                    Main Menue Screen                             \n";
    cout << "====================================================================================\n";


    cout << "            [1] Show Client List." << endl;

    cout << "            [2] Add New Client." << endl;

    cout << "            [3] Delete Client." << endl;

    cout << "            [4] Updata Client Info." << endl;

    cout << "            [5] Find Client." << endl;

    cout << "            [6] Transactions Menue." << endl;

    cout << "            [7] Manage Users." << endl;

    cout << "            [8] Logout." << endl;

    cout << "====================================================================================\n";


    PerformMainMenueOption((enMainMenueOption)ReadMainMenueOption());

}

bool LoadUserInfo(string UserName, string Password)
{
    if (FindUserByUserNameAndPassWord(UserName, Password, CurrentUser))
        return true;
    else
        return false;
}


void Login()
{
    bool LoginFaild = false;
    string Username, Password;
    do
    {
        system("cls");
        cout << "\n-----------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n-----------------------------\n";
        if (LoginFaild)
        {
            cout << "Invlaid Username/Password !\n";
        }
        cout << "Enter Username ";
        cin >> Username;

        cout << "Enter Password ";
        cin >> Password;

        LoginFaild = !LoadUserInfo(Username, Password);
    } while (LoginFaild);
        ShowMainMenue();
}


int main()
{
    Login();
    system("pause");
    return 0;
}