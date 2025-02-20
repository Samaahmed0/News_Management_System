#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <sstream>
#include <istream>
#include <fstream>
using namespace std;
class Comments {

public:
	string username;
	string comment;
};
class News {
private:
	int ID;
	string title;
	string description;
	string date;
	vector <float> rates;
	float rate = 0;
	string category;
	static set<string> allCategories;

public:
	list<Comments> lisOfComments;
	int commentsSz;
	News();
	News(int iD, string Title, string Description, string Date, string Category, vector < float > Rates);
	int getid();
	string& getTitle();
	string& getdesc();
	string& getdate();
	string& getcat();
	vector<float>& getrate();
	float& getavgrate();
	static set<string>& getAllcategories();
	void setID(int id);
	void settitle(string Title);
	void setdesc(string desc);
	void setdate(string Date);
	void setcategory(string cat);
	void Addrate(float Rating);
	void LoadNews(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News*>& newsByTitle);
	static void Loadcategories();
	static void Savecategories();
	void SaveNews(unordered_map<int, News>& NewsMap);
	void calculaterates();
	static void Addcategory(string category);

};
class User {
private:
	string username;
	string password;
	string email;
	bool notification;

public:
	stack<string> notifications;
	int notifcount;
	set<string> preferredCategories;
	list<int> bookmarksList;
	User();
	User(string use, string pass, string email, bool notif, int notifcountt);
	string getusername();
	string getpassword();
	string getEmail();
	void view_notifications();
	bool get_notification_status();
	void setusername(string use);
	void setpassword(string pass);
	void LoadUser(unordered_map<string, User>& UserMap);
	void SaveUser(unordered_map<string, User>& UserMap);
	void displayNewsByCategory(const string& category, unordered_map<string, vector<News*>>& newsByCategory);
	void rateNewsArticle(unordered_map<string, News*>& newsByTitle, unordered_map<int, News>& NewsMap);
	//search
	void SearchNews(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News*>& newsByTitle);
	void searchKeyword(unordered_map<int, News>& NewsMap);
	void searchTitle(unordered_map<int, News>& NewsMap, unordered_map<string, News*>& newsByTitle);
	void searchDate(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByDate);
	void addBookmark(unordered_map<int, News>& NewsMap);
	void addBookmark(int id);
	void displayBookmark(unordered_map<int, News>& NewsMap);
	//display latest news
	void DisplayLastestNews(unordered_map<int, News>& NewsMap);
	static bool CompareNewsByDate(pair<int, News>& n1, pair<int, News>& n2);
	vector<pair<int, News>>  SortNews(unordered_map<int, News>& NewsMap);
	void Trending_News(unordered_map<int, News>& newsArticles);
	void displayNews(unordered_map<int, News>& newsArticles);
	void descendingNews(unordered_map<int, News>& newsArticles);
	void addPreferredCategories(const set<string>& categories);
	void addPreferredCategories(string category);
	void displayComment(unordered_map<int, News>& NewsMap);
	void addComment(unordered_map<int, News>& NewsMap);
	void viewPreferredCategories();
};
class Admin {
public:
	static void postNews(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News*>& newsByTitle, unordered_map <string, User>& users
	);
	void deleteNews(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, News*>& newsByTitle);
	static void updateNews(unordered_map<int, News>& NewsMap, unordered_map<string, News*>& newsByTitle);
	static void addCategory(set<string>& allCategories, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News*>& newsByTitle, unordered_map<int, News>& NewsMap, unordered_map <string, User>& users);
	static void addNews(unordered_map<int, News>& newsById, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News*>& newsByTitle, News& news);
	static void displayavgrate(unordered_map<int, News>& NewsMap);
	static void assignNewsTocat(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News*>& newsByTitle, const string& category);
	static void push_notifications(string notif, unordered_map <string, User>& usersMap
	);



};