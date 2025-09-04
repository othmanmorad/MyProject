#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;





//  problem47(To open file)
//  const string ClientFileName = "Client.txt";
//  struct sClients
//  {
//  	string AccountNumber;
//  	string PinCode;
//  	string Name;
//  	string Phone;
//  	int AccountBalance;
//  
//  };
//  
//  sClients ReadNewClient()
//  {
//  	sClients Client;
//  
//  	cout << "\nEnter Client's information \n";
//  
//  	cout << "Account Number " << endl;
//  	getline(cin >> ws, Client.AccountNumber);
//  
//  	cout << "Enter  PinCode " << endl;
//  	getline(cin, Client.PinCode);
//  
//  	cout << "Enter  Name " << endl;
//  	getline(cin, Client.Name);
//  
//  	cout << "Enter  phone " << endl;
//  	getline(cin, Client.Phone);
//  
//  	cout << "Enter countBalance " << endl;
//  	cin >> Client.AccountBalance;
//  
//  	return Client;
//  }
//  
//  string ConvertRecordToLine(sClients Client, string Sprator = " #//# ")
//  {
//  	string sLine;
//  	sLine += Client.AccountNumber + Sprator;
//  
//  	sLine += Client.PinCode + Sprator;
//  
//  	sLine += Client.Name + Sprator;
//  
//  	sLine += Client.Phone + Sprator;
//  
//  	sLine += to_string(Client.AccountBalance) + Sprator;
//  
//  	return sLine;
//  }
//  
//  void AddDataLineToFile(string FileName, string DataLine)
//  {
//  	fstream MyFile;
//  
//    MyFile.open(FileName, ios::out | ios::app);
//  
//  	if (MyFile.is_open())
//  	{
//  
//  		MyFile << DataLine << endl;
//  		MyFile.close();
//  	}
//  
//  }
//  
//  void AddNewClient()
//  {
//  
//  	sClients Client;
//  	Client = ReadNewClient();
//  
//  	AddDataLineToFile(ClientFileName, ConvertRecordToLine(Client));
//  
//  }
//  
//  void AddAllClients()
//  {
//  	char AddMore = 'y';
//  
//  	do
//  	{
//  		system("cls");
//  		cout << "Adding new client : \n\n";
//  		AddNewClient();
//  
//  		cout << "\nClients added succssfuly , do you want add more clients ? ";
//  		cin >> AddMore;
//  	} while (AddMore == 'y' || AddMore == 'Y');
//  }
//  
//  
//  
//  int main()
//  {
//  
//  	AddAllClients();
//  
//  }






//project1


    const string ClientFileName = "Client.txt";
    void ShowMainMenue();
    struct sClients
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    int AccountBalance;
    bool MarkForDelete = false;

};
    vector<string> SpiltString(string S1, string delim = " #//# ")
{
    vector<string>vString;

    int pos = 0;
    string sWord;

    while ((pos = S1.find(delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);

        if (sWord != "")
        {
            vString.push_back(sWord);

        }

        S1.erase(0, pos + delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

    sClients ConvertLineToRecord(string Line, string Spraetor = " #//# ")
{
    vector<string>vClient;
    sClients Client;

    vClient = SpiltString(Line, Spraetor);
    Client.AccountNumber = vClient[0];
    Client.PinCode = vClient[1];
    Client.Name = vClient[2];
    Client.Phone = vClient[3];
    Client.AccountBalance = stod(vClient[4]);

    return Client;
}



    vector<sClients>LoadClientDataFromFile(string FileName)
{

    vector<sClients>vClient;
    fstream MyFile;

    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClients Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClient.push_back(Client);
        }

        MyFile.close();
    }

    return vClient;


}

    void PrintClientRecord(sClients Client)
{
    cout << "|  " << setw(15) << left << Client.AccountNumber;
    cout << "|  " << setw(10) << left << Client.PinCode;
    cout << "|  " << setw(30) << left << Client.Name;
    cout << "|  " << setw(12) << left << Client.Phone;
    cout << "|  " << setw(12) << left << Client.AccountBalance;

}

    void ShowAllClientsScreen()
{
    vector<sClients>vClient = LoadClientDataFromFile(ClientFileName);
    cout << "                  Client (" << vClient.size() << ")              ";
    cout << "\n------------------------------------------------------------------------------------------------------\n";
    cout << "|  " << left << setw(15) << "AccountNumber ";
    cout << "|  " << left << setw(10) << "PinCode ";
    cout << "|  " << left << setw(30) << "Name ";
    cout << "|  " << left << setw(12) << "Phone ";
    cout << "|  " << left << setw(12) << "Account Balance ";
    cout << "\n------------------------------------------------------------------------------------------------------\n";

    for (sClients Client : vClient)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n------------------------------------------------------------------------------------------------------\n";

}

    bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    vector<sClients>vClient;
    fstream MyFile;

    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClients Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
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
    sClients ReadNewClient()
{
    sClients Client;

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

    void ShowAddNewClientsScreen()
{
    cout << "-----------------------------------------\n";
    cout << "            Add New Client screen        \n";
    cout << "-----------------------------------------\n";
    AddAllClients();

}

    string ReadAccountNumber()
{
    string AccountNumber;
    cout << "\nEnter Account Number : " << endl;
    cin >> AccountNumber;
    return AccountNumber;
}

    bool FindClientByAccountNumber(string AccountNumber, sClients& Client)
{
    vector<sClients>vClient = LoadClientDataFromFile(ClientFileName);

    for (sClients C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

    bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClients>& vClient)
{
    for (sClients& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}


    vector <sClients>SaveClientDataToFile(string FileName, vector<sClients>vClient)
{
    fstream MyFile;

    string DataLine;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (sClients C : vClient)
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

   bool DeleteClientByAccountNumber(string AccountNumber, vector<sClients>& vClient)
{
    sClients Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, Client))
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

  void ShowDeleeClientScreen()
{
    cout << "\n-------------------------------------------------------\n";
    cout<<"\tDelate Client Screen ";
    cout << "\n-------------------------------------------------------\n";

    vector<sClients>vClient = LoadClientDataFromFile(ClientFileName);

    string AccountNumber = ReadAccountNumber();


    DeleteClientByAccountNumber(AccountNumber, vClient);

}
    sClients ChangeClientRecord(string AccountNumber)
{
    sClients Client;
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

    bool UpDataClientByAccountNumber(string AccountNumber, vector<sClients>& vClient)
{
    sClients Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientRecord(Client);

        cout << "\nAre you sure you want updata Client ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClients& C : vClient)
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
    void ShowUpDataClientScreen()
{
    cout << "\n-------------------------------------------------------\n";
    cout << "\tUpData Client info Screen ";
    cout << "\n-------------------------------------------------------\n";

    vector<sClients>vClient = LoadClientDataFromFile(ClientFileName);

    string AccountNumber = ReadAccountNumber();


    UpDataClientByAccountNumber(AccountNumber, vClient);

}

    void FindClientScreen()
{
    cout << "\n-------------------------------------------------------\n";
    cout << "\tFind Client info Screen ";
    cout << "\n-------------------------------------------------------\n";

    string AccountNumber = ReadAccountNumber();
    sClients Client;

    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientRecord(Client);
    }
    else
    {
        cout << "\nClient with Account number (" << AccountNumber << ") Not found";
    }
}

    void ShowEndScreen()
{
    cout << "----------------------------------------------\n";
    cout << "              Program Ends :-)                \n";
    cout << "----------------------------------------------\n";

}
    enum enMainMenueOptions
{
    eListClients = 1, eAddNewClient = 2,
    eDelateClient = 3, eUpDataClient = 4,
    eFindClient = 5, eExit = 6
};





    void GoPackToMainMenue()
{
    cout << "\nPress any kay to go back to main menue ...";
    system("pause>0");
    ShowMainMenue();
}
   short ReadMainMenueOption()
{
    short Choice;

     cout << "Chooce what do you want to do ? [1 to 6] ? \n";
     cin >> Choice;
     return Choice;
}

   void PerformMainMenueOption(short Choice)
{
    switch (Choice)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");

        ShowAllClientsScreen();
        GoPackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
    {
        system("cls");

        ShowAddNewClientsScreen();
        GoPackToMainMenue();
        break;
    }
    case enMainMenueOptions::eDelateClient:
    {
        system("cls");

        ShowDeleeClientScreen();
        GoPackToMainMenue();

        break;
    }
    case enMainMenueOptions::eUpDataClient:
    {
        system("cls");

        ShowUpDataClientScreen();
        GoPackToMainMenue();

        break;

    }
    case enMainMenueOptions::eFindClient:
    {
        system("cls");

        FindClientScreen();
        GoPackToMainMenue();
        break;

    }
    case enMainMenueOptions::eExit:
    {
        system("cls");
        ShowEndScreen();
        GoPackToMainMenue();

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

    cout << "            [6] Exit." << endl;

    cout << "====================================================================================\n";


    PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());

}

   int main()
   {
       ShowMainMenue();


   }






