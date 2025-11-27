#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

/*
const string ClientFileName = "Client.txt";
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

    cout << "\nEnter Client's information \n";

    cout << "Account Number " << endl;
    getline(cin >> ws, Client.AccountNumber);

    cout << "Pin Code  " << endl;
    getline(cin, Client.PinCode);

    cout << "Name " << endl;
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

    AddDataLineToFile(ClientFileName, ConvertRecordToLine(Client));

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
  





enum enATMMainMenueOptions
{
    eQuickWithdraw = 1, eNormalWithdraw = 2,eDeposit = 3 ,eShowTotalBalance = 4 , eLogout = 5, 
};

enum enQuickWithdrawOptions { e20 = 1, e50 = 2,e100=3,e200=4,e400=5,e600=6,e800=7,e1000=8,eExit=9 };

const string ClientFileName = "Client.txt";

void ShowATMMainMenue();
void ShowWithDrawScreen();
void ShowQucikWithDrawScreen();
void Login();

struct sClient
{
    string AccountNumber; string PinCode; string Name; string Phone; double AccountBalance; bool MarkForDelete = false;
};

sClient CurrentClient;

vector<string> SpiltString(string S1, string Delim)
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

sClient ConvertClientLineToRecord(string Line, string Spraetor = "#//#")
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

string ConvertRecordToLine(sClient Client, string Sprator = "#//#")
{
    string sLine;
    sLine += Client.AccountNumber + Sprator;

    sLine += Client.PinCode + Sprator;

    sLine += Client.Name + Sprator;

    sLine += Client.Phone + Sprator;

    sLine += to_string(Client.AccountBalance) + Sprator;

    return sLine;
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

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client)
{
    vector<sClient>vClient = LoadClientDataFromFile(ClientFileName);

    for (sClient C : vClient)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
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

bool DepositToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClient)
{
    char Answer;
    cout << "\nAre you sure you want perform this transactions y/n ? ";
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

short ReadQuickWithDrawOption()
{
    short Choice;

   do
    {
        cout << "Chooce what do you want to do ? [1 to 9] ? \n";
        cin >> Choice;
   } while (Choice <= 0 || Choice > 9);
    return Choice;
}

short getQuickWithDrawAmount(short QuickWithDrawChoice)
{
    switch (QuickWithDrawChoice)
    {
    case 1:
    {
        return 20;
    }
    case 2:
    {
        return 50;
    }
    case 3:
    {
        return 100;
    }
    case 4:
    {
        return 200;
    }
    case 5:
    {
        return 400;
    }
    case 6:
    {
        return 600;
    }
    case 7:
    {
        return 800;
    }
    case 8:
    {
        return 1000;
    }

    default: return 0;
    }
}








       

void ShowCheckBalancesScreen()

{
    sClient Client;

    vector<sClient>vClient = LoadClientDataFromFile(ClientFileName);

    cout << "=======================================================\n";
    cout << "                  Check Balance Screen                   \n";
    cout << "=======================================================\n";

    cout << "Your balance is = " <<CurrentClient.AccountBalance;

}


void PerformDepositOption()
{
    sClient Client;
    vector<sClient>vClients = LoadClientDataFromFile(ClientFileName);




    double Amount;
    do 
    {

        cout << "\nPlease Enter a Positive Deposit Amount ";
        cin >> Amount;


    } while (Amount <= 0);
   

    DepositToClientByAccountNumber(CurrentClient.AccountNumber, Amount, vClients);
    CurrentClient.AccountBalance += Amount;
}
void ShowDepositScreen()
{

    cout << "==========================================\n";
    cout << "               Deposit Screen          \n";
    cout << "==========================================\n";
    PerformDepositOption();
}


int ReadWithDrawAmount()
{
    int Amount;


    cout << "\nEnter an Amount withdraw Mutiple 5's ? ";
    cin >> Amount;

   
  while (Amount % 5 != 0);
  {
      cout << "\nEnter an Amount withdraw Mutiple 5's ? ";
      cin >> Amount;

  }
  return Amount;
}

void PerformNormalWithdrawOption()
{
    sClient Client;
    vector<sClient>vClients = LoadClientDataFromFile(ClientFileName);



    int WithDrawBalance=ReadWithDrawAmount();
    
    

        
        if (WithDrawBalance > CurrentClient.AccountBalance)
        {
            cout << "\nThe Amount Exceeds the balance , you can withdraw up to : " << CurrentClient.AccountBalance << endl;
            ShowWithDrawScreen();
        }
   

    DepositToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawBalance * -1, vClients);
    CurrentClient.AccountBalance -= WithDrawBalance;

}


void ShowWithDrawScreen()
{

    cout << "===========================================\n";
    cout << "               Withdraw Screen          \n";
    cout << "===========================================\n";
    sClient Client;
    vector<sClient>vClients = LoadClientDataFromFile(ClientFileName);
   

    
    PerformNormalWithdrawOption();
}

void PerformQuickWithdrawOption(short QuickWithDrawOption)
{
    if (QuickWithDrawOption == 9)
        return;

    short WithDrawBalance = getQuickWithDrawAmount(QuickWithDrawOption);
    if (WithDrawBalance > CurrentClient.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance , you can withdraw up to : " << CurrentClient.AccountBalance << endl;
        cout << "Preess any kay to continue...";
        system("pause");
        ShowQucikWithDrawScreen();
        return;
    }

    sClient Client;
    vector<sClient>vClients = LoadClientDataFromFile(ClientFileName);



    DepositToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawBalance * -1, vClients);
    CurrentClient.AccountBalance -= WithDrawBalance;
}

void ShowQucikWithDrawScreen()
{

    cout << "===========================================\n";
    cout << "            Quick Withdraw Screen          \n";
    cout << "===========================================\n";
  
    cout << "[1] 20\t\t\t";
    cout << "[2] 50\n";
    cout << "[3] 100\t\t\t";
    cout << "[4] 200\n";
    cout << "[5] 400\t\t\t";
    cout << "[6] 600\n";
    cout << "[7] 800\t\t\t";
    cout << "[8] 1000\n";
    cout << "[9] Exit\t\t\t";
    cout << "\n===========================================\n";
    cout << "Your balance is = " << CurrentClient.AccountBalance;

   


    PerformQuickWithdrawOption(ReadQuickWithDrawOption());
}














void GoPackToATMMenueScreen()
{
    cout << "\nPress any kay to go back to ATM menue screen ...";
    system("pause>0");
    ShowATMMainMenue();
}

short ReadATMMainMenueOption()
{
    short Choice;

    cout << "Chooce what do you want to do ? [1 to 5] ? \n";
    cin >> Choice;
    return Choice;
}

void PerformATMMainMenueOption(enATMMainMenueOptions TransactionsMenueOPtions)
{
    switch (TransactionsMenueOPtions)
    {
    case enATMMainMenueOptions::eQuickWithdraw:
    {
        system("cls");

        ShowQucikWithDrawScreen();
        GoPackToATMMenueScreen();
        break;
    }
    case enATMMainMenueOptions::eNormalWithdraw:
    {
        system("cls");

        ShowWithDrawScreen();
        GoPackToATMMenueScreen();
        break;
    }

    case enATMMainMenueOptions::eDeposit:
    {
        system("cls");

        ShowDepositScreen();
        GoPackToATMMenueScreen();
        break;
    }
    case enATMMainMenueOptions::eShowTotalBalance:
    {
        system("cls");

        ShowCheckBalancesScreen();
        GoPackToATMMenueScreen();

        break;
    }
    case enATMMainMenueOptions::eLogout:
    {
        system("cls");


        Login();

        break;

    }

    }
}

void ShowATMMainMenue()
{


   

    system("cls");
    cout << "====================================================================================\n";


    cout << "                                    ATM Main Menue Screen                             \n";
    cout << "====================================================================================\n";


    cout << "            [1] Quick Withdraw." << endl;

    cout << "            [2] Normal Withdraw." << endl;

    cout << "            [3] Deposit ." << endl;

    cout << "            [4] Check Balance ." << endl;

    cout << "            [5] Logout." << endl;

    cout << "====================================================================================\n";

    PerformATMMainMenueOption((enATMMainMenueOptions)ReadATMMainMenueOption());


}

bool LoadClientInfo(string AccountNumber, string PinCode)
{
    if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
        return true;
    else
        return false;
}

void Login()
{
    bool LoginFaild = false;
    string AccountNumber, PinCode;
    do
    {
        system("cls");
        cout << "\n-----------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n-----------------------------\n";
        if (LoginFaild)
        {
            cout << "Invlaid Account Number/PinCode !\n";
        }
        cout << "Enter Account Number ";
        cin >> AccountNumber;

        cout << "Enter PinCode ";
        cin >> PinCode;

        LoginFaild = !LoadClientInfo(AccountNumber, PinCode);
    } while (LoginFaild);
    ShowATMMainMenue();
}

int main()
{
    Login();
    system("pause");
    return 0;
}