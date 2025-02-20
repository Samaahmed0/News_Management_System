#include"News.h";
News::News() {
	ID = 0;
	title = " ";
	description = " ";
	date = " ";
	category = " ";
	rates = {};
	rate = 0;
}
News::News(int iD, string Title, string Description, string Date, string Category, vector<float> Rates) {
	ID = iD;
	title = Title;
	description = Description;
	date = Date;
	category = Category;
	rates = Rates;
	calculaterates();
	Addcategory(Category);
}
set<string> News::allCategories;

int News::getid() {
	return ID;
}
string& News::getTitle() {
	return title;
}
string& News::getdesc() {
	return description;
}
string& News::getdate() {
	return date;
}
string& News::getcat() {
	return category;
}
vector<float>& News::getrate() {
	return rates;
}
float& News::getavgrate() {
	calculaterates();
	return rate;
}
set<string>& News::getAllcategories() {
	return allCategories;
}
void News::setID(int id) {
	ID = id;
}
void News::settitle(string Title) {
	title = Title;
}
void News::setdesc(string desc) {
	description = desc;
}
void News::setdate(string Date) {
	date = Date;
}
void News::setcategory(string cat) {
	category = cat;
}
void News::Addrate(float Rating) {
	rates.push_back(Rating);
}
void News::Addcategory(string category) {
	allCategories.insert(category);
}
User::User() {
	username = " ";
	password = " ";
	notification = false;
}
User::User(string use, string pass, string em, bool notif, int notifcountt) {
	username = use;
	password = pass;
	email = em;
	notification = notif;
	notifcount = notifcountt;
}
string User::getEmail() {
	return email;
}
string User::getusername() {
	return username;
}
string User::getpassword() {
	return password;
}
void User::setusername(string use) {
	username = use;
}
void User::setpassword(string pass) {
	password = pass;
}
void User::addBookmark(int id) {
	bookmarksList.push_back(id);
}

void  User::view_notifications() {
	stack <string>temp;
	if (notification) {
		if (!notifications.empty()) {
			while (!notifications.empty()) {
				cout << notifications.top() << endl;
				temp.push(notifications.top());
				notifications.pop();
			}
			while (!temp.empty()) {
				notifications.push(temp.top());
				temp.pop();
			}
		}
		else {
			cout << "you have no notifications at the moment" << endl;
		}

	}
	else {
		cout << "you have the notifications off" << endl;
	}
}
void User::addBookmark(unordered_map<int, News>& NewsMap) {

	bool found = false;
	int id;
	cout << "Enter the News id you want to add " << endl;
	cin >> id;

	for (auto& b : bookmarksList) {
		if (id == b) {
			cout << "It's already bookmarked" << endl;
			return;
		}
	}
	auto it = NewsMap.find(id);
	if (it != NewsMap.end()) {
		bookmarksList.push_back(id);
		cout << "Bookmarked!" << endl;
	}
	else {
		cout << "ID not found" << endl;
	}

}
void User::addPreferredCategories(string category) {
	preferredCategories.insert(category);
}
void User::displayBookmark(unordered_map<int, News>& NewsMap)
{
	if (bookmarksList.empty()) {
		cout << "Your bookmark list is empty" << endl;
	}
	else {
		cout << "Your Bookmarks:" << endl;
		cout << endl;
		for (auto& b : bookmarksList) {

			cout << "Id: " << NewsMap[b].getid() << endl;
			cout << "Title: " << NewsMap[b].getTitle() << endl;
			cout << "Description: " << NewsMap[b].getdesc() << endl;
			cout << "Category: " << NewsMap[b].getcat() << endl;
			cout << "Date: " << NewsMap[b].getdate() << endl;
			cout << endl;
		}
	}

}



bool User::CompareNewsByDate(pair<int, News>& n1, pair<int, News>& n2) {
	try {

		int day1 = stoi(n1.second.getdate().substr(0, 2));
		int month1 = stoi(n1.second.getdate().substr(3, 2));
		int year1 = stoi(n1.second.getdate().substr(6, 4));

		int day2 = stoi(n2.second.getdate().substr(0, 2));
		int month2 = stoi(n2.second.getdate().substr(3, 2));
		int year2 = stoi(n2.second.getdate().substr(6, 4));

		if (year1 != year2) {
			return year1 > year2;
		}
		else if (month1 != month2) {
			return month1 > month2;
		}
		else {
			return day1 > day2;
		}
	}
	catch (const invalid_argument& e) {
		cerr << "Error: Invalid date string encountered\n";
		cerr << "Date string 1: " << n1.second.getdate() << "\n";
		cerr << "Date string 2: " << n2.second.getdate() << "\n";
		return false;
	}
}


vector<pair<int, News>>  User::SortNews(unordered_map<int, News>& NewsMap) {
	vector<pair<int, News>> newsVec(NewsMap.begin(), NewsMap.end());
	sort(newsVec.begin(), newsVec.end(), CompareNewsByDate);
	return newsVec;
}

void User::DisplayLastestNews(unordered_map<int, News>& NewsMap) {

	vector<pair<int, News>> sortedNews = SortNews(NewsMap);

	int count = 0; //display the latest 5 news ( bmzagy 3ady)

	cout << "Latest News :" << endl;
	cout << endl;
	for (auto it = sortedNews.begin(); it != sortedNews.end(); ++it) {
		News& n = it->second;
		cout << "ID: " << n.getid() << endl;
		cout << "Title: " << n.getTitle() << endl;
		cout << "Description: " << n.getdesc() << endl;
		cout << "Date: " << n.getdate() << endl;
		cout << "Category: " << n.getcat() << endl;
		cout << "Rate: " << n.getavgrate() << endl;//return average rate lama martina tekhalasha //khalastaha :P
		count++;
		cout << endl;
		if (count == 5) {
			break;
		}
		else {
			continue;
		}
	}
}


void Admin::deleteNews(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, News*>& newsByTitle)
{
	int ID;
	cout << "Enter the ID of the News Article you would like to delete";
	cin >> ID;
	auto it = NewsMap.find(ID);
	if (it != NewsMap.end()) {
		// Remove from newsByDate
		vector<News*>& datevec = newsByDate[it->second.getdate()];
		datevec.erase(remove_if(datevec.begin(), datevec.end(), [ID](News* newsPtr) { return newsPtr->getid() == ID; }), datevec.end());

		// Remove from newsByCategory
		vector<News*>& catvec = newsByCategory[it->second.getcat()];
		catvec.erase(remove_if(catvec.begin(), catvec.end(), [ID](News* newsPtr) { return newsPtr->getid() == ID; }), catvec.end());

		// Remove from newsByTitle
		auto itt = newsByTitle.find(it->second.getTitle());
		if (itt != newsByTitle.end()) {
			newsByTitle.erase(itt);
		}

		// Remove from NewsMap
		NewsMap.erase(it);

		cout << "News deleted!";
	}
	else
		cout << "No News Found With this ID";
}
void Admin::updateNews(unordered_map<int, News>& NewsMap, unordered_map<string, News*>& newsByTitle) {
	int id, choice;
	bool found = false;
	cout << "Enter the ID of the article you want to update:";
	cin >> id;
	auto it = NewsMap.find(id);
	if (it != NewsMap.end()) {
		News& n = it->second;
		found = true;
		string newupd;
		cout << "Choose what you would like to update:\n1.Title\n2.Description\n";
		cin >> choice;
		cin.ignore();
		if (choice == 1) {
			cout << "Enter The Updated Title:";
			getline(cin, newupd);
			string oldTitle = n.getTitle();
			n.settitle(newupd);
			newsByTitle.erase(oldTitle);
			newsByTitle[newupd] = &n;
		}
		else if (choice == 2) {
			cout << "Enter The Updated Description:";
			getline(cin, newupd);

			n.setdesc(newupd);
		}
		else
			cout << "Unavailable Choice.";
	}
	if (found == false)
		cout << "ID not found";

}
void News::calculaterates() {
	rate = 0.0f;
	if (rates.empty())
		return;
	for (int i = 0; i < rates.size(); i++) {
		rate += rates[i];
	}
	rate = rate / rates.size();
}
void User::displayNewsByCategory(const string& category, unordered_map<string, vector<News*>>& newsByCategory) {
	bool found = false;
	if (newsByCategory.find(category) != newsByCategory.end()) {
		for (News* ptr : newsByCategory[category]) {
			found = true;
			int id = ptr->getid(); // Accessing ID via pointer
			cout << "Id: " << id << endl;
			cout << " Title: " << ptr->getTitle() << endl;
			cout << " Description: " << ptr->getdesc() << endl;
			cout << " Date: " << ptr->getdate() << endl;
			cout << " Rate: " << ptr->getavgrate() << endl;
			cout << "................................................." << endl;
		}
	}
	else {
		cout << "This Category does not exist" << endl;
	}
	if (!found)
		cout << "No news found under this category";
}

void User::rateNewsArticle(unordered_map<string, News*>& newsByTitle, unordered_map<int, News>& NewsMap) {

	for (auto it = newsByTitle.begin(); it != newsByTitle.end(); ++it) {
		cout << "ID: " << it->second->getid() << endl << " Title: " << it->first << endl;
	}
	int id;
	cout << "Choose The News article you would like to rate: ";
	cin >> id;
	auto itt = NewsMap.find(id);
	if (itt != NewsMap.end()) {
		float rating;
		cout << "Enter Your Rating: ";
		cin >> rating;
		itt->second.Addrate(rating);
		itt->second.calculaterates();
		cout << "News article '" << id << "' rated successfully." << endl;
		return;
	}
	else
		cout << "News article '" << id << "' not found." << endl;
}
void User::searchKeyword(unordered_map<int, News>& NewsMap) {
	string keyword;
	vector<News> matchingNews;

	cout << "Enter keyword to search in description :" << endl;
	cin >> keyword;
	for (auto it = NewsMap.begin(); it != NewsMap.end(); ++it) {
		auto n = it->second;
		if (n.getdesc().find(keyword) != string::npos) {
			cout << "ID:" << n.getid() << endl;
			cout << " Title:" << n.getTitle() << endl;
			cout << " Description:" << n.getdesc() << endl;
			cout << " Category:" << n.getcat() << endl;
			cout << " Rating:" << n.getavgrate() << endl;
		}
	}
}
void User::searchTitle(unordered_map<int, News>& NewsMap, unordered_map<string, News*>& newsByTitle) {
	string keyword;
	cout << "Enter the Title :" << endl;
	cin.ignore(); // Clear the input buffer before reading the title
	getline(cin, keyword);
	auto it = newsByTitle.find(keyword);
	if (it != newsByTitle.end()) {
		News* foundNews = it->second;
		cout << "ID:" << foundNews->getid() << endl;
		cout << " Title:" << foundNews->getTitle() << endl;
		cout << " Description:" << foundNews->getdesc() << endl;
		cout << " Category:" << foundNews->getcat() << endl;
		cout << " Rating:" << foundNews->getavgrate() << endl;
	}
	else {
		cout << "This title does not exist in our system";
	}
}
bool User::get_notification_status() {
	return notification;
}

void User::searchDate(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByDate) {
	string date;
	cout << "Enter the Date :" << endl;
	getline(cin, date);
	bool found = false;
	if (newsByDate.find(date) != newsByDate.end()) {
		for (News* ptr : newsByDate[date]) {

			found = true;
			int id = ptr->getid(); // Accessing ID via pointer
			cout << "Id: " << id << endl;
			cout << " Title: " << ptr->getTitle() << endl;
			cout << " Description: " << ptr->getdesc() << endl;
			cout << " Date: " << ptr->getdate() << endl;
			cout << " Rate: " << ptr->getavgrate() << endl;
			cout << "................................................." << endl;
		}
	}
	else {
		cout << "This Date does not exist";
	}
	if (!found)
		cout << "No news found under this Date";
}
void User::SearchNews(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News*>& newsByTitle) {
	int choice;
	bool valid = false;
	while (!valid) {
		cout << "How would you like to search?";
		cout << "1. By Keyword" << endl;
		cout << "2. By Title" << endl;
		cout << "3. By Date" << endl;
		cout << "Enter your choice: " << endl;
		cin >> choice;
		cin.ignore();

		if (choice == 1) {
			valid = true;
			searchKeyword(NewsMap);

		}
		else if (choice == 2) {
			valid = true;
			searchTitle(NewsMap, newsByTitle);
		}
		else if (choice == 3) {
			valid = true;
			searchDate(NewsMap, newsByDate);
		}
		else {
			cout << "Invalid choice , Try again" << endl;

		}
	}
}
void Admin::displayavgrate(unordered_map<int, News>& NewsMap) {
	bool found = false;
	int ID;
	cout << "Enter the ID of the News Article:\n";
	cin >> ID;
	auto it = NewsMap.find(ID);
	if (it != NewsMap.end()) {
		found = true;
		if (NewsMap[ID].getrate().empty())
			cout << "This News article has no ratings yet" << "\n";
		else {
			cout << "the rating for the news article " << it->second.getTitle() << "\n" << " is " << it->second.getavgrate() << "\n";
		}
	}
	if (!found) {
		cout << "ID: " << ID << " not found in news database." << endl;
	}
}
void Admin::push_notifications(string notif, unordered_map <string, User>& usersMap)
{
	for (auto it = usersMap.begin(); it != usersMap.end(); ++it) {
		if (it->second.get_notification_status()) {
			it->second.notifications.push(notif);
			it->second.notifcount++;
		}
	}

}
void Admin::postNews(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News* >& newsByTitle, unordered_map <string, User>& users) {
	News news;
	news.setID(NewsMap.size() + 1);
	string title, description, category, date;
	bool validcat = false;
	cin.ignore();
	cout << "Enter The Title of The News Article:";
	getline(cin, title);
	news.settitle(title);
	cout << "Enter The Description of The News Article:";
	getline(cin, description);
	news.setdesc(description);
	cout << "Enter The Category of The News Article:";
	getline(cin, category);
	news.setcategory(category);
	while (!validcat) {
		if (News::getAllcategories().find(category) == News::getAllcategories().end()) {
			cout << "This category doesn't exists, Try again";
			getline(cin, category);
		}
		else
		{
			validcat = true;
			news.setcategory(category);
		}

	}
	cout << "Enter The Date of The News Article:";
	getline(cin, date);
	news.setdate(date);
	cout << "Your News Article has been Added!";
	addNews(NewsMap, newsByCategory, newsByDate, newsByTitle, news);
	string s = "news article" + title + "was posted ,check it out!!";
	push_notifications(s, users);


}

void Admin::addNews(unordered_map<int, News>& newsById, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News*>& newsByTitle, News& news) {
	newsById[news.getid()] = news;
	newsByCategory[news.getcat()].push_back(&news);
	newsByDate[news.getdate()].push_back(&news);
	newsByTitle[news.getTitle()] = &news;
}

void Admin::addCategory(set<string>& allCategories, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News*>& newsByTitle, unordered_map<int, News>& NewsMap, unordered_map <string, User>& users) {
	string newcat;
	string assignchoice;
	cout << "Enter The new Category:";
	cin.ignore();
	getline(cin, newcat);
	if (allCategories.find(newcat) != allCategories.end()) {
		cout << "This category already exists";
	}
	else {
		News::Addcategory(newcat);
		cout << "Category " << newcat << " added" << endl;
		do {
			cout << "Do you want to add news to this category? y ";
			getline(cin, assignchoice);

			if (assignchoice == "y" || assignchoice == "Y") {
				assignNewsTocat(NewsMap, newsByCategory, newsByDate, newsByTitle, newcat);
				break;
			}
		} while (assignchoice == "y" || assignchoice == "Y");
	}
	string s = "new category: " + newcat + " has been added!!";
	cout << endl;
	push_notifications(s, users);

}
void Admin::assignNewsTocat(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News*>& newsByTitle, const string& category) {
	string title, description, date;
	News news;
	int ID = NewsMap.size() + 1;
	news.setID(ID);
	cout << "Enter The Title of The News Article:" << endl;
	getline(cin, title);
	news.settitle(title);
	news.setcategory(category);
	cout << "Enter The Description of The News Article:";
	getline(cin, description);
	news.setdesc(description);
	cout << "Enter The Date of The News Article:";
	getline(cin, date);
	news.setdate(date);
	cout << "Your News Article has been Added!";
	NewsMap[ID] = news;
	newsByCategory[category].push_back(&NewsMap[ID]);
	newsByDate[date].push_back(&NewsMap[ID]);
	newsByTitle[title] = &NewsMap[ID];

}

void User::Trending_News(unordered_map<int, News>& newsArticles) {
	cout << "The Top 3 most trending Articles :" << endl;

	multimap<float, string, greater<float>> trendingArticles;

	for (auto itt = newsArticles.begin(); itt != newsArticles.end(); itt++) {
		if (itt->second.getavgrate() > 2) {
			trendingArticles.insert(make_pair(itt->second.getavgrate(), itt->second.getTitle()));
		}
	}
	int count = 0;
	for (auto it = trendingArticles.begin(); it != trendingArticles.end(); it++) {
		if (count >= 3) {
			break;
		}
		cout << "Title: " << it->second << " | Rate: " << it->first << endl;
		count++;
	}
}

void User::descendingNews(unordered_map<int, News>& newsArticles) {
	multimap<float, string, greater<float>> descArticles;

	for (int i = 0; i < newsArticles.size(); i++) {

		descArticles.insert(make_pair(newsArticles[i].getavgrate(), newsArticles[i].getTitle()));

	}
	for (auto it = descArticles.begin(); it != descArticles.end(); it++) {

		cout << "Title:\n " << it->second << "\nRate: " << it->first << endl;
	}
}
void User::displayNews(unordered_map<int, News>& NewsMap) {


	for (auto it = NewsMap.begin(); it != NewsMap.end(); ++it) {
		auto n = it->second;
		if (n.getavgrate() < 2.0f)
			continue;
		cout << "Article " << n.getid() << endl;
		cout << "  Title: " << n.getTitle() << endl;
		cout << "  Category: " << n.getcat() << endl;
		cout << "  Description: " << n.getdesc() << endl;
		cout << "  Date: " << n.getdate() << endl;
		cout << "  Rate: " << n.getavgrate() << endl;
	}
}
void User::LoadUser(unordered_map<string, User>& UserMap) {
	ifstream file("Users.txt");

	if (!file.is_open()) {

		cerr << "Unable to open users file" << endl;
	}
	else {
		while (true) {
			User user;
			string category;
			if (!(file >> user.username))
				break;

			file.ignore();
			getline(file, user.password);
			getline(file, user.email);
			int notif;
			file >> notif;
			if (notif == 0)
				user.notification = false;
			else
				user.notification = true;
			file.ignore();

			if (user.notification) {
				file >> user.notifcount;
				file.ignore(); // Ignore newline character
				for (int i = 0; i < user.notifcount; i++) {
					string notif;
					getline(file, notif);
					user.notifications.push(notif);
				}
			}

			string CategLine;
			getline(file, CategLine);
			stringstream categStream(CategLine);
			string categ;
			while (getline(categStream, categ, ',')) {
				user.addPreferredCategories(categ);
			}

			string bookmarkLine;
			getline(file, bookmarkLine);
			stringstream bookmarkStream(bookmarkLine);
			string bookmark;
			while (getline(bookmarkStream, bookmark, ',')) {
				user.addBookmark(stoi(bookmark));
			}

			UserMap[user.username] = user;
		}
		file.close();
	}

}
void User::SaveUser(unordered_map<string, User>& UserMap) {
	ofstream file("Users.txt");
	if (file.is_open()) {
		for (auto it = UserMap.begin(); it != UserMap.end(); ++it)
		{
			auto u = it->second;
			file << u.username << endl;
			file << u.password << endl;
			file << u.email << endl;
			file << u.notification << endl;
			if (u.notification) {
				file << u.notifcount << endl;

				stack <string> temp;
				while (!u.notifications.empty()) {
					temp.push(u.notifications.top());
					u.notifications.pop();
				}
				while (!temp.empty())
				{
					file << temp.top() << endl;
					temp.pop();
				}
			}
			for (auto prefCat = u.preferredCategories.begin(); prefCat != u.preferredCategories.end(); prefCat++) {
				file << *prefCat;
				if (next(prefCat) != u.preferredCategories.end())
					file << ",";
			}
			file << endl;
			for (auto bookmark = u.bookmarksList.begin(); bookmark != u.bookmarksList.end(); bookmark++) {
				file << *bookmark;
				if (next(bookmark) != u.bookmarksList.end())
					file << ",";
			}
			if (next(it) != UserMap.end())
				file << endl;

		}
		file.close();
	}
	else {
		cerr << "unable to open users file" << endl;
	}
}
void News::Loadcategories() {
	ifstream file("Categories.txt");
	if (!file.is_open()) {
		cerr << "Error: Unable to open file " << "News.txt" << " for reading" << endl;
		return;
	}
	string cat;
	while (!file.eof()) {
		getline(file, cat);
		allCategories.insert(cat);
	}
	file.close();
}
void News::Savecategories() {
	ofstream file("Categories.txt");
	if (!file.is_open()) {
		cerr << "Error: Unable to open file " << "News.txt" << " for reading" << endl;
		return;
	}
	for (string category : allCategories) {
		file << category << endl;
	}

	file.close();
}
void News::SaveNews(unordered_map<int, News>& NewsMap) {
	ofstream file("News.txt");
	if (!file.is_open()) {
		cerr << "Error: Unable to open file " << "News.txt" << " for writing" << endl;
		return;
	}
	for (auto& pair : NewsMap) {
		News& news = pair.second;
		file << news.ID << endl;
		file << news.title << endl;
		file << news.category << endl;
		file << news.description << endl;
		file << news.date << endl;
		file << news.commentsSz << endl;
		for (auto& comment : news.lisOfComments) {
			file << comment.username << endl;
			file << comment.comment << endl;
		}

		// Write ratings
		for (size_t i = 0; i < news.rates.size(); ++i) {
			file << news.rates[i];
			if (i != news.rates.size() - 1) {
				file << ",";
			}
		}
		file << endl;
	}
	file.close();
}

void User::addComment(unordered_map<int, News>& NewsMap) {
	int id;
	Comments c;
	bool found = false;
	c.username = username;

	cout << "Enter the id of the News you want to add comment to: " << endl;
	cin >> id;
	cin.ignore();
	if (NewsMap.find(id) != NewsMap.end()) {
		found = true;
		cout << "Write your comment : ";

		getline(cin, c.comment);
		NewsMap[id].lisOfComments.push_back(c);
		cout << "Comment added!" << endl;
		NewsMap[id].commentsSz++;
	}
	if (!found) {
		cout << "ID not found" << endl;

	}

}

void User::displayComment(unordered_map<int, News>& NewsMap) {
	int id;
	bool found = false;
	cout << "Enter the id of the News you want to display it's comments: " << endl;
	cin >> id;
	cin.ignore();
	if (NewsMap.find(id) != NewsMap.end()) {
		found = true;
		if (NewsMap[id].lisOfComments.empty()) {
			cout << "There are no comments yet " << endl;
		}
		else {
			cout << "Comments: " << endl;
			cout << endl;
			for (auto& c : NewsMap[id].lisOfComments) {
				cout << c.username << ":";
				cout << c.comment << endl;
			}
		}
	}
	if (!found) {
		cout << "ID not found" << endl;

	}

}

void News::LoadNews(unordered_map<int, News>& NewsMap, unordered_map<string, vector<News*>>& newsByCategory, unordered_map<string, vector<News*>>& newsByDate, unordered_map<string, News*>& newsByTitle) {
	ifstream file("News.txt");
	if (!file.is_open()) {
		cerr << "Error: Unable to open file " << "News.txt" << " for reading" << endl;
		return;
	}
	while (true) {
		News news;
		if (!(file >> news.ID)) {
			break;
		}

		file.ignore();
		getline(file, news.title);
		getline(file, news.category);
		News::allCategories.insert(news.category);
		getline(file, news.description);
		getline(file, news.date);
		file >> news.commentsSz;
		file.ignore();
		for (int i = 0; i < news.commentsSz; ++i) {
			Comments comment;
			getline(file, comment.username);
			getline(file, comment.comment);
			news.lisOfComments.push_back(comment);
		}
		string ratingLine;
		getline(file, ratingLine);
		stringstream ratingStream(ratingLine);
		float rating;
		while (getline(ratingStream, ratingLine, ',')) {
			stringstream ratingValue(ratingLine);
			ratingValue >> rating;
			news.Addrate(rating);
		}
		NewsMap[news.ID] = news;
		newsByCategory[news.category].push_back(&NewsMap[news.ID]);
		newsByDate[news.date].push_back(&NewsMap[news.ID]);
		newsByTitle[news.title] = &NewsMap[news.ID];
	}

	file.close();
}
void User::addPreferredCategories(const set<string>& categories)
{
	string choose;
	cout << "here are all the categories" << endl;
	set<string>::iterator it;
	for (it = categories.begin(); it != categories.end(); it++) {
		cout << *it << endl;
	}
	do {
		cout << "choose a category you prefer or type done if you are finished" << endl;

		cin >> choose;
		if (categories.count(choose) && !preferredCategories.count(choose)) {
			preferredCategories.insert(choose);
			cout << "added" << endl;
		}
		else if (choose != "done" && choose != "Done") {
			cout << "category is already chosen or you entered a non existing category" << endl;
		}
	} while (choose != "done" && choose != "Done");
}
void User::viewPreferredCategories() {
	cout << "Your preferred categories:" << endl;
	for (auto category : preferredCategories) {
		cout << category << endl;
	}
}