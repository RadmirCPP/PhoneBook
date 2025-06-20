#include <iostream>
#include <vector>
#include <fstream>
#include <string>
struct Contact {
    std::string name;
    std::string phone;
};
void addContact(std::vector<Contact>& contact)
{
    Contact val;
    Contact checker;
    std::cout << "Type the name:";
    std::cin >> val.name;
    std::cout << "Type the phone number:";
    std::cin >> val.phone;
    contact.push_back(val);
    checker = contact[contact.size()-1];
    std::cout << checker.name << " name and " << checker.phone << " phone has been added\n";
}
void showEveryContact(const std::vector<Contact>& contact)
{
    std::cout << contact.size() <<'\n';
    for (int i = 0; i < contact.size(); i++)
    {
        
        std::cout << contact[i].name << ' ' << contact[i].phone << '\n';
    }
}
void showExactContact(const std::vector<Contact>& contact)
{
    bool found = false;
    std::string name;
    std::cout << "What is the name?";
    std::cin >> name;
    for (int i = 0; i < contact.size(); i++)
    {
        if (contact[i].name == name)
        {
            std::cout << contact[i].name << ' ' << contact[i].phone <<'\n';
            found = true;
        }
    }
    if (!found) {
        std::cout << "No contact with such name\n";
    }
}
void deleteExactContact(std::vector<Contact>& contact)
{
    if (contact.size()==0) {
        std::cout << "there is nothing to delete";
        return;
    }
    Contact val;
    std::cout << "What is the name?";
    std::cin >> val.name;
    std::cout << "What is the phone?";
    std::cin >> val.phone;
    bool isThere = false;
    for (int i = 0; i < contact.size();)
    {
        if (contact[i].name == val.name && contact[i].phone == val.phone)
        {
            std::cout << contact[i].name << " name and " << contact[i].phone << " phone is deleted\n";
            contact.erase(contact.begin() + i);
            isThere = true;
            break;
        }
        else
        {
            i++;
        }
    }
    if(!isThere)
    std::cout << "there is no such name and/or phone\n";
    
}
void savePhoneBook(const std::vector<Contact>& contact, std::string fileName) {
    
    std::ofstream file(fileName);
    if(file.is_open()){
        for (const auto& c : contact)
        {
            file << c.name << '|' << c.phone<<'\n';
        }
    file.close();
    }
    else {
        std::cerr << "Error";
    }
    
}
void loadPhoneBook(std::vector<Contact>& contact, std::ifstream&fileName) {
    std::string line;
    
    Contact c;
    if (fileName.is_open()) {
        while (std::getline(fileName, line))
        {
            bool alrExist=false;
            size_t middleDiv = line.find('|');
            if (middleDiv == std::string::npos) continue;
           
            c.name = line.substr(0, middleDiv);
            c.phone = line.substr(middleDiv + 1);
            alrExist = false;
            for (const auto& existing : contact) {
                if (existing.name == c.name && existing.phone == c.phone) {
                    alrExist = true;
                    break;
                }
            }
            if (!alrExist) {
                contact.push_back(c);
            }
        }
        
    }
    

}
int main()
{
    
    std::vector<Contact> contacts;
    int choice;
    
    while (true)
    {
        std::cout << "Write:\n1 for adding contact\n2 for showing every contact in a PhoneBook\n3 for searching by name\n4 for deleting contact\n5 for saving\n6 for uploading contacts from file \n99 for exit\n";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            continue;
        }
        if (choice == 1)
        {
            addContact(contacts);
        }
        else if (choice == 2)
        {
            showEveryContact(contacts);
        }
        else if (choice == 3)
        {
               
            showExactContact(contacts);
        }
        else if (choice == 4)
        {
            deleteExactContact(contacts);
        }
        else if (choice == 5)
        {
            std::string file;
            std::cout << "write name of a file\n";
            std::cin >> file;
            savePhoneBook(contacts, file+".txt");
        }
        else if (choice == 6)
        {
            std::string file;
            std::cout << "write name of a file\n";
            std::cin >> file;
            std::ifstream fileName(file + ".txt");
            if (!fileName.is_open()) {
                std::cerr << "failed to open file " << file << ".txt\n";
            }
            else {
                loadPhoneBook(contacts, fileName);
                fileName.close();
            }
        }
        else if (choice == 99) {
            if (contacts.size() != 0) {
                contacts.clear();
            }
            break;
        }
        else {
            std::cout << "please write viable number\n";
           
        }

    }
}
