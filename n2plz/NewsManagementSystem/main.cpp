#include"News.h"
#include <iostream>
#include <string>
#include <vector>
#include<unordered_map>
#include <cstdlib>
using namespace std;
void displayMainMenu();
void login();
void registerUser();
void loginAsAdmin();
void userFunctions(const string& username);
void adminFunctions();
void clearInputBuffer();
string adminUsername = "admin";
string adminPassword = "admin";
unordered_map <string, User> usersMap;
unordered_map<int, News> newsMap;
unordered_map<string, vector<News*>> newsByCategory;
unordered_map<string, vector<News*>> newsByDate;
unordered_map<string, News*> newsByTitle;
User user;
News news;
Admin admin;
using namespace std;




int main() {



    Admin admin;
    user.LoadUser(usersMap);
    news.LoadNews(newsMap, newsByCategory, newsByDate, newsByTitle);
    news.Loadcategories();



    while (true) {
        displayMainMenu();
        news.Savecategories();
        user.SaveUser(usersMap);
        news.SaveNews(newsMap);
    }


    
}
void displayMainMenu() {
    system("cls");
    cout << "Welcome to the News System" << endl;
    cout << "-------------------------------" << endl;
        cout << "1. Log in " << endl;
    cout << "2. Register " << endl;
    cout << "3. Exit" << endl;
    cout << "Please enter your option: ";

    int option;
    cin >> option;

    switch (option) {
       
    case 1:
        login();
        break;
    case 2:
        registerUser();
        break;
    case 3:
        cout << "Exiting program. Goodbye!" << endl;
        exit(0);
    default:
        cout << "Invalid option. Please try again." << endl;
        clearInputBuffer();
        system("pause");
        break;
    }
}

void login() {
    system("cls");
    bool found = false;
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    if (username == adminUsername && password == adminPassword) {
        found = true;
        cout << "Successfully logged in as admin." << endl;
        adminFunctions();

    }
    else {

        unordered_map<string, User>::iterator it;
        for (it = usersMap.begin(); it != usersMap.end(); it
            ++) {
            if (it->first == username && it->second.getpassword() == password) {
                found = true;
                cout << "login successfull" << endl;
                userFunctions(username);
                return;
            }
        }
    }
    if (!found) {
        cout << "Invalid username or password. Please try again." << endl;
        clearInputBuffer();
        system("pause");
    }


}

void registerUser() {
    system("cls");
    string name;
    string pass;
    string email;
    string ans;
    bool ans1;
    bool valid;
    do {
        cout << "Enter your desired username: ";
        cin >> name;
        valid = true;
        unordered_map<string, User>::iterator it;
        for (it = usersMap.begin(); it != usersMap.end(); it++) {
            if (it->first == name) {
                cout << "username isnt available" << endl;
                valid = false;
            }

        }
    } while (valid == false);
    cout << "Enter your password: ";
    cin >> pass;
    cout << "Enter your Email:";
    cin >> email;
    cout << "Do you want to turn Email notifications on? (yes/no)" << endl;
    cin >> ans;
    if (ans == "yes") {
        ans1 = true;

    }
    else {
        ans1 = false;
    }

    User newUser(name, pass, email, ans1, 0);
    usersMap[name] = newUser;

    cout << "Registration successful!" << endl;
    cout << endl;
    cout << "Username: " << newUser.getusername() << endl;
    cout << "Password: " << newUser.getpassword() << endl;
    system("pause");
    userFunctions(newUser.getusername());
}

void loginAsAdmin() {
    system("cls");
    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword) {
        cout << "Successfully logged in as admin." << endl;
        adminFunctions();
    }
    else {
        cout << "Invalid admin credentials." << endl;
        system("pause");
    }
}

void userFunctions(const string& username) {
    while (true) {
        system("cls");
        cout << "User Functions" << endl;
        cout << "-------------------------------" << endl;
        cout << "1. Display News" << endl;
        cout << "2. Search News" << endl;
        cout << "3. Rate News Article" << endl;
        cout << "4. Bookmarks" << endl;
        cout << "5. Add Preferred Categories" << endl;
        cout << "6. View Notifications" << endl;
        cout << "7. Add a Comment" << endl;
        cout << "8. Display Comments" << endl;
        cout << "9. Display Preferred Categories" << endl;
        cout << "10. Logout" << endl;
        cout << "Please enter your option: ";

        int option;
        cin >> option;
        int op;
        string title;
        float rate;
        switch (option) {
        case 1:

            cout << "1. Display News by category" << endl;
            cout << "2. Display latest News" << endl;
            cout << "3. Display News descending" << endl;
            cout << "4. Display all News" << endl;
            cout << "5. Display Trending News" << endl;
            cout << "Please enter your option";
            cin >> op;
            clearInputBuffer();
            system("cls");
            if (op == 1) {
                string catg;
                cout << "enter the category:";
                cin >> catg;
                usersMap[username].displayNewsByCategory(catg, newsByCategory);

            }
            else if (op == 2) {

                usersMap[username].DisplayLastestNews(newsMap);


            }
            else if (op == 3) {

                usersMap[username].descendingNews(newsMap);

            }
            else if (op == 4) {

                usersMap[username].displayNews(newsMap);
            }
            else if (op == 5) {

                usersMap[username].Trending_News(newsMap);
            }
            system("pause");
            break;

        case 2:
            usersMap[username].SearchNews(newsMap, newsByDate, newsByTitle);
            system("pause");
            break;
        case 3:
            cin.ignore();
            usersMap[username].rateNewsArticle(newsByTitle, newsMap);
            system("pause");
            break;
        case 4:
            cout << "1. Display Bookmarks" << endl;
            cout << "2. Add Bookmark" << endl;
            cin >> op;
            if (op == 1) {

                usersMap[username].displayBookmark(newsMap);
            }
            else if (op == 2) {

                usersMap[username].addBookmark(newsMap);
            }
            system("pause");
            break;
        case 5:
            usersMap[username].addPreferredCategories(news.getAllcategories());
            system("pause");
            break;
        case 6:
            usersMap[username].view_notifications();
            system("pause");
            break;
        case 7:
            usersMap[username].addComment(newsMap);
            system("pause");
            break;
        case 8:
            usersMap[username].displayComment(newsMap);
            system("pause");
            break;
        case 9:
            usersMap[username].viewPreferredCategories();
            system("pause");
            break;
        case 10:
            cout << "Logging out..." << endl;
            system("pause");
            return;

        default:
            cout << "Invalid option. Please try again." << endl;
            clearInputBuffer();
            system("pause");
            break;
        }
    }
}


void adminFunctions() {
    while (true) {
        system("cls");
        cout << "Admin Functions" << endl;
        cout << "-------------------------------" << endl;
        cout << "1. Post news" << endl;
        cout << "2. Delete News" << endl;
        cout << "3. Update News" << endl;
        cout << "4. Display Average Rate For a News Article" << endl;
        cout << "5. Add Category" << endl;
        cout << "6. Logout" << endl;
        cout << "Please enter your option: ";

        int option;
        cin >> option;

        switch (option) {
        case 1:
            admin.postNews(newsMap, newsByCategory, newsByDate, newsByTitle, usersMap);
            cout << "Posting News Article..." << endl;
            system("pause");
            break;
        case 2:
            admin.deleteNews(newsMap, newsByCategory, newsByDate, newsByTitle);
            cout << "Deleting News Article..." << endl;
            system("pause");
            break;
        case 3:
            admin.updateNews(newsMap, newsByTitle);
            cout << "Updating News Article..." << endl;
            system("pause");
            break;
        case 4:
            admin.displayavgrate(newsMap);
            system("pause");
            break;
        case 5:
            admin.addCategory(news.getAllcategories(), newsByCategory, newsByDate, newsByTitle, newsMap, usersMap);
            system("pause");
            cout << "Category Added!" << endl;
            break;
        case 6:
            cout << "Logging Out..." << endl;
            system("pause");
            return;
        default:
            cout << "Invalid option. Please try again." << endl;
            clearInputBuffer();
            system("pause");
            break;
        }
    }
}

void clearInputBuffer() {
    cin.clear(); // Clear any error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the input buffer
}