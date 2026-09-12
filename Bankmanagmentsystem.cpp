#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

// ======================================================
// Transaction Class
// ======================================================

class Transaction
{
private:
    string type;
    double amount;

public:
    Transaction(string type, double amount)
    {
        this->type = type;
        this->amount = amount;
    }

    string getType() const
    {
        return type;
    }

    double getAmount() const
    {
        return amount;
    }
};


// ======================================================
// Client Class
// ======================================================

class Client
{
private:
    string name;
    int id;
    double balance;

    vector<Transaction> transactions;

public:

    // Constructor
    Client(int id, string name, double balance)
    {
        this->id = id;
        this->name = name;
        this->balance = balance;
    }


    // Getters
    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    double getBalance() const
    {
        return balance;
    }


    // Setters
    void setName(string newName)
    {
        name = newName;
    }

    void setId(int newId)
    {
        id = newId;
    }


    // Deposit
    bool deposit(double amount)
    {
        if (amount <= 0)
        {
            return false;
        }

        balance += amount;

        transactions.push_back(
            Transaction("Deposit", amount)
        );

        return true;
    }


    // Withdraw
    bool withdraw(double amount)
    {
        if (amount <= 0)
        {
            return false;
        }

        if (amount > balance)
        {
            return false;
        }

        balance -= amount;

        transactions.push_back(
            Transaction("Withdrawal", amount)
        );

        return true;
    }


    // Add Transfer Transaction
    void addTransaction(string type, double amount)
    {
        transactions.push_back(
            Transaction(type, amount)
        );
    }


    // Show Client
    void showClient() const
    {
        cout << "\n================================\n";
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Balance: $" << fixed << setprecision(2)
             << balance << endl;
        cout << "================================\n";
    }


    // Show Transaction History
    void showTransactionHistory() const
    {
        if (transactions.empty())
        {
            cout << "\nNo Transactions Available!\n";
            return;
        }

        cout << "\n========== Transaction History ==========\n";

        for (size_t i = 0; i < transactions.size(); i++)
        {
            cout << "\nTransaction " << i + 1 << endl;

            cout << "Type: "
                 << transactions[i].getType()
                 << endl;

            cout << "Amount: $"
                 << fixed
                 << setprecision(2)
                 << transactions[i].getAmount()
                 << endl;
        }

        cout << "=========================================\n";
    }
};


// ======================================================
// Bank Class
// ======================================================

class Bank
{
private:
    vector<Client> clients;


    // Find Client by ID
    int findClientIndex(int id) const
    {
        auto it = find_if(
            clients.begin(),
            clients.end(),
            [id](const Client& client)
            {
                return client.getId() == id;
            }
        );

        if (it != clients.end())
        {
            return static_cast<int>(
                distance(clients.begin(), it)
            );
        }

        return -1;
    }


public:

    // ==================================================
    // Add Client
    // ==================================================

    void addClient()
    {
        int id;
        string name;
        double balance;

        cout << "\nEnter Client ID: ";
        cin >> id;

        if (findClientIndex(id) != -1)
        {
            cout << "This ID already exists!\n";
            return;
        }

        cout << "Enter Client Name: ";
        cin >> name;

        cout << "Enter Initial Balance: ";
        cin >> balance;

        if (balance < 0)
        {
            cout << "Balance cannot be negative!\n";
            return;
        }

        Client newClient(id, name, balance);

        clients.push_back(newClient);

        cout << "\nClient Added Successfully!\n";
    }


    // ==================================================
    // Show All Clients
    // ==================================================

    void showClients() const
    {
        if (clients.empty())
        {
            cout << "\nNo Clients Available!\n";
            return;
        }

        cout << "\n========== All Clients ==========\n";

        for (const Client& client : clients)
        {
            client.showClient();
        }
    }


    // ==================================================
    // Search Client
    // ==================================================

    void searchClient() const
    {
        int id;

        cout << "\nEnter Client ID: ";
        cin >> id;

        int index = findClientIndex(id);

        if (index == -1)
        {
            cout << "Client not found!\n";
            return;
        }

        clients[index].showClient();
    }


    // ==================================================
    // Deposit
    // ==================================================

    void deposit()
    {
        int id;
        double amount;

        cout << "\nEnter Client ID: ";
        cin >> id;

        int index = findClientIndex(id);

        if (index == -1)
        {
            cout << "Client not found!\n";
            return;
        }

        cout << "Enter amount to deposit: ";
        cin >> amount;

        if (clients[index].deposit(amount))
        {
            cout << "\nAmount deposited successfully!\n";

            cout << "New Balance: $"
                 << fixed
                 << setprecision(2)
                 << clients[index].getBalance()
                 << endl;
        }
        else
        {
            cout << "Invalid amount!\n";
        }
    }


    // ==================================================
    // Withdraw
    // ==================================================

    void withdraw()
    {
        int id;
        double amount;

        cout << "\nEnter Client ID: ";
        cin >> id;

        int index = findClientIndex(id);

        if (index == -1)
        {
            cout << "Client not found!\n";
            return;
        }

        cout << "Enter amount to withdraw: ";
        cin >> amount;

        if (amount <= 0)
        {
            cout << "Invalid amount!\n";
            return;
        }

        if (amount > clients[index].getBalance())
        {
            cout << "Insufficient balance!\n";
            return;
        }

        clients[index].withdraw(amount);

        cout << "\nAmount withdrawn successfully!\n";

        cout << "New Balance: $"
             << fixed
             << setprecision(2)
             << clients[index].getBalance()
             << endl;
    }


    // ==================================================
    // Check Balance
    // ==================================================

    void checkBalance() const
    {
        int id;

        cout << "\nEnter Client ID: ";
        cin >> id;

        int index = findClientIndex(id);

        if (index == -1)
        {
            cout << "Client not found!\n";
            return;
        }

        cout << "\nCurrent Balance: $"
             << fixed
             << setprecision(2)
             << clients[index].getBalance()
             << endl;
    }


    // ==================================================
    // Update Client
    // ==================================================

    void updateClient()
    {
        int id;

        cout << "\nEnter Client ID: ";
        cin >> id;

        int index = findClientIndex(id);

        if (index == -1)
        {
            cout << "Client not found!\n";
            return;
        }

        string newName;

        cout << "Enter new Client Name: ";
        cin >> newName;

        clients[index].setName(newName);

        cout << "\nClient Updated Successfully!\n";
    }


    // ==================================================
    // Delete Client
    // ==================================================

    void deleteClient()
    {
        int id;

        cout << "\nEnter Client ID: ";
        cin >> id;

        auto it = find_if(
            clients.begin(),
            clients.end(),
            [id](const Client& client)
            {
                return client.getId() == id;
            }
        );

        if (it == clients.end())
        {
            cout << "Client not found!\n";
            return;
        }

        clients.erase(it);

        cout << "\nClient Deleted Successfully!\n";
    }


    // ==================================================
    // Transfer Money
    // ==================================================

    void transferMoney()
    {
        int senderId;
        int receiverId;
        double amount;

        cout << "\nEnter Sender ID: ";
        cin >> senderId;

        int senderIndex = findClientIndex(senderId);

        if (senderIndex == -1)
        {
            cout << "Sender not found!\n";
            return;
        }


        cout << "Enter Receiver ID: ";
        cin >> receiverId;

        int receiverIndex = findClientIndex(receiverId);

        if (receiverIndex == -1)
        {
            cout << "Receiver not found!\n";
            return;
        }


        if (senderIndex == receiverIndex)
        {
            cout << "You cannot transfer money to the same client!\n";
            return;
        }


        cout << "Enter amount to transfer: ";
        cin >> amount;


        if (amount <= 0)
        {
            cout << "Invalid amount!\n";
            return;
        }


        if (amount > clients[senderIndex].getBalance())
        {
            cout << "Insufficient balance!\n";
            return;
        }


        // Withdraw from sender
        clients[senderIndex].withdraw(amount);

        // Deposit to receiver
        clients[receiverIndex].deposit(amount);


        // Add transaction history
        clients[senderIndex]
            .addTransaction("Transfer Out", amount);

        clients[receiverIndex]
            .addTransaction("Transfer In", amount);


        cout << "\nTransfer completed successfully!\n";

        cout << "Sender New Balance: $"
             << fixed
             << setprecision(2)
             << clients[senderIndex].getBalance()
             << endl;

        cout << "Receiver New Balance: $"
             << fixed
             << setprecision(2)
             << clients[receiverIndex].getBalance()
             << endl;
    }


    // ==================================================
    // Transaction History
    // ==================================================

    void transactionHistory() const
    {
        int id;

        cout << "\nEnter Client ID: ";
        cin >> id;

        int index = findClientIndex(id);

        if (index == -1)
        {
            cout << "Client not found!\n";
            return;
        }

        clients[index].showTransactionHistory();
    }


    // ==================================================
    // Sort Clients by Balance
    // ==================================================

    void sortByBalance()
    {
        sort(
            clients.begin(),
            clients.end(),
            [](const Client& a, const Client& b)
            {
                return a.getBalance() > b.getBalance();
            }
        );

        cout << "\nClients sorted by balance successfully!\n";
    }


    // ==================================================
    // Save Data
    // ==================================================

    void saveToFile() const
    {
        ofstream file("clients.txt");

        if (!file)
        {
            cout << "Error opening file!\n";
            return;
        }

        for (const Client& client : clients)
        {
            file << client.getId() << " "
                 << client.getName() << " "
                 << client.getBalance() << endl;
        }

        file.close();
    }


    // ==================================================
    // Load Data
    // ==================================================

    void loadFromFile()
    {
        ifstream file("clients.txt");

        if (!file)
        {
            return;
        }

        clients.clear();

        int id;
        string name;
        double balance;

        while (file >> id >> name >> balance)
        {
            clients.emplace_back(
                id,
                name,
                balance
            );
        }

        file.close();
    }
};


// ======================================================
// Main
// ======================================================

int main()
{
    Bank bank;

    // Load saved clients
    bank.loadFromFile();

    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "        BANK MANAGEMENT SYSTEM\n";
        cout << "========================================\n";

        cout << "1.  Add Client\n";
        cout << "2.  Show Clients\n";
        cout << "3.  Search Client\n";
        cout << "4.  Deposit\n";
        cout << "5.  Withdraw\n";
        cout << "6.  Check Balance\n";
        cout << "7.  Update Client\n";
        cout << "8.  Delete Client\n";
        cout << "9.  Transfer Money\n";
        cout << "10. Transaction History\n";
        cout << "11. Sort by Balance\n";
        cout << "12. Save Data\n";
        cout << "13. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;


        switch (choice)
        {
        case 1:
            bank.addClient();
            break;

        case 2:
            bank.showClients();
            break;

        case 3:
            bank.searchClient();
            break;

        case 4:
            bank.deposit();
            break;

        case 5:
            bank.withdraw();
            break;

        case 6:
            bank.checkBalance();
            break;

        case 7:
            bank.updateClient();
            break;

        case 8:
            bank.deleteClient();
            break;

        case 9:
            bank.transferMoney();
            break;

        case 10:
            bank.transactionHistory();
            break;

        case 11:
            bank.sortByBalance();
            break;

        case 12:
            bank.saveToFile();
            cout << "\nData Saved Successfully!\n";
            break;

        case 13:
            bank.saveToFile();
            cout << "\nData saved automatically.\n";
            cout << "Goodbye!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 13);

    return 0;
}