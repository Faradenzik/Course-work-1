#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <algorithm>

using namespace std;


const string DataFileUsers = "Accounts_Info.txt";
const string DataFilePlayers = "Players_Info.txt";
bool adminstat;
bool systemAdmin;
bool UsOrPl;


struct Account
{
	string login;
	string password;
	int role;
};

struct Person
{
	string surname;
	string name;
	string patronymic;

	struct Date
	{
		int day;
		int month;
		int year;
	} birth;

	int games;
	int goals;
	int assists;
	int banMins;
};


void admin_core(vector<Account>&, vector<Person>&);
void user_core(vector<Account>&, vector<Person>&);

void admin_menu();
void user_menu();

//void adminPodmenu(vector<Account>&, int);
//void userPodmenu(vector<Person>&, int);

void addAdminAcc(vector<Account>&);

void readFileUsers(vector<Account>&);
void readFilePlayers(vector<Person>&);

void writeFileUsers(vector<Account>&);
void writeFilePlayers(vector<Person>&);
void writeSomePlayers(vector<Person>&, int);

void writeUsersList(vector<Account>&);
void writePlayersList(vector<Person>&);

void sort(vector<Person>&, bool&);
void sortSurname(vector<Person>& players);
void sortNumOfPucks(vector<Person>& players);
void sortMatch(vector<Person>& players);

void search(vector<Person>&);
void searchSurname(vector<Person>&);
void searchGoals(vector<Person>&);
void searchMatches(vector<Person>&);

void showUsers(vector<Account>&);
void showPlayers(vector<Person>&);

void addUser(vector<Account>&);
void addPlayer(vector<Person>&);

void delUser(vector<Account>&);
void delFuncText();
void delPlayer(vector<Person>&);

void updUser(vector<Account>&);
void updFuncText();
void updatePlayer(vector<Person>&);

void hellomenu(vector<Account>&, vector<Person>&);
void chooseMenu(vector<Account>&, vector<Person>&);

void signup(vector<Account>&, vector<Person>&);
void signin(vector<Account>&, vector<Person>&);
bool checkLogPass(string);

void indTask(vector<Person>&); // НАПИСАТЬ!!!

int inNum(int min, int max);
void palochki(int);
string whoWrote(bool UsOrPl);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<Account> users;
	vector<Person> players;

	readFileUsers(users);
	readFilePlayers(players);

	hellomenu(users, players);
}

void palochki(int k)
{
	for (int i = 0; i < k; i++)
		cout << "-";
	cout << endl;
}
string whoWrote(bool UsOrPl)
{
	if (UsOrPl == true)
	{
		return "игрока";
	}
	else
	{
		return "пользователя";
	}
}
int inNum(int min, int max)
{
	double input;
	while (true)
	{
		cin >> input;
		if (cin.get() == '\n')
		{
			if(input>=min && input<=max)
				break;
			else
			{
				cout << "Выберите из списка.\n";
			}
		}
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Недопустимое значение.\n";
		}
	}
	return input;
}

void hellomenu(vector<Account>& users, vector<Person>& players)
{
	bool exit = true;
	while (exit)
	{
		cout << "\tДобро пожаловать!" << endl;
		palochki(40);
		cout << "1) Создать аккаунт" << endl;
		cout << "2) Войти в существующий" << endl;
		cout << "0) Выход" << endl;

		int num;

		num = inNum(0, 2);

		switch (num)
		{
		case 1:
			signup(users, players);
			break;
		case 2:
			signin(users, players);
			break;
		case 0:
			exit = false;
			break;
		}
		system("cls");
	}
}
void signup(vector<Account>& users, vector<Person>& players)
{
	Account obmanka;
	bool flag = true;
	while (flag)
	{
		system("cls");
		cout << "<--Приветствие" << endl;
		cout << "\tРегистрация" << endl;
		palochki(40);
		cout << "Если захотите вернуться введите 0" << endl;

		cout << "Придумайте логин для входа:\n";
		while (true)
		{
			cout << "Логин должен состоять из букв и(или) цифр\n";
			cin >> obmanka.login;
			if (checkLogPass(obmanka.login) == true)
				break;
		}

		if (obmanka.login == "0")
		{
			system("cls");
			flag = false;
		}
		else
		{
			bool check = false;
			for (int i = 0; i < users.size(); i++)
			{
				if (obmanka.login == users[i].login)
					check = true;
			}
			if (check == true)
			{
				cout << "Данный логин занят. Попробуйте другой" << endl;
				cout << "Нажмите любую клавишу чтобы вернуться...";
				_getch();
			}
			else
			{
				flag = false;
				cout << "Придумайте пароль:\n";
				while (true)
				{
					cout << "Пароль должен состоять из букв и(или) цифр\n";
					cin >> obmanka.password;
					if (checkLogPass(obmanka.password) == true)
						break;
				}
				obmanka.role = 0;

				users.push_back(obmanka);

				writeFileUsers(users);

				system("cls");
				cout << "Добро пожаловать, " << obmanka.login << endl;
				user_core(users, players);
			}
		}
	}
}
void signin(vector<Account>& users, vector<Person>& players) // ДОДЕЛАТЬ
{
	bool er = true;
	while (er)
	{
		system("cls");
		cout << "<--Приветствие" << endl;
		cout << "\tАвторизация" << endl;
		palochki(40);
		cout << "Если захотите вернуться введите 0" << endl;
		cout << "Введите логин: ";
		string log;
		cin >> log;

		if (log == "0")
		{
			system("cls");
			er = false;
		}
		else
		{
			cout << "Введите пароль: ";
			char pass[16];
			int i;

			for (i = 0; i < 16; i++)
			{
				pass[i] = _getch();

				if (pass[i] == 13)
					break;

				if (pass[i] == 8)
				{
					if (i == 0)
					{
						i--;
						continue;
					}
					pass[i - 1] = '\0';
					cout << "\b \b";
					i -= 2;
				}
				else
				{
					cout << "*";
				}
			}
			pass[i] = '\0';

			for (int i = 0; i < users.size(); i++)
			{
				if (users[i].login == log && users[i].password == pass)
				{
					if (users[i].role == 1)
					{
						adminstat = true;
					}
					else
					{
						adminstat = false;
					}

					system("cls");
					cout << "Добро пожаловать, " << log << "\n\n";
					
					if (log == users[0].login)
						systemAdmin = true;
					else
						systemAdmin = false;
					
					er = false;
					chooseMenu(users, players);
					break;
				}
				else if (i == users.size() - 1)
				{
					cout << "\nПроверьте правильность данных" << endl;
					cout << "Нажмите любую клавишу чтобы вернуться...";
					_getch();
					break;
				}
			}
		}
	}
}
bool checkLogPass(string str)
{
	for (int i = 0; i <= str.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9' || str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z')
		{
		}
		else
		{
			cout << "Некорректный ввод!\n";
			return false;
			break;
		}
		if (i == str.length() - 1)
			return true;
	}
}

void chooseMenu(vector<Account>& users, vector<Person>& players)
{
	if (adminstat == true)
	{
		admin_core(users, players);
	}
	else
	{
		user_core(users, players);
	}
}

void addAdminAcc(vector<Account>& users)
{
	Account obmanka;
	
	obmanka.login = "admin";
	obmanka.password = "admin";
	obmanka.role = 1;

	users.push_back(obmanka);
}

void admin_menu()
{
	cout << "\tAdmin panel" << endl;
	palochki(40);
	cout << "1) Просмотр" << endl;
	cout << "2) Добавление" << endl;
	cout << "3) Удаление" << endl;
	cout << "4) Редактирование" << endl;
	cout << "5) User panel" << endl;
	cout << "0) Выход" << endl;

}
void user_menu()
{
	if (adminstat == true)
		cout << "\tUser panel" << endl;
	else
		cout << "\t\tМеню" << endl;

	palochki(36);

	cout << "1) Просмотр" << endl;
	cout << "2) Поиск по параметрам" << endl;
	cout << "3) Индивидуальное задание" << endl;
	
	if (adminstat == true)
	{
		cout << "4) Добавление" << endl;
		cout << "5) Удаление" << endl;
		cout << "6) Редактирование" << endl;
		cout << "7) Admin panel" << endl;
	}
	cout << "0) Выход" << endl;
}

void admin_core(vector<Account>& users, vector<Person>& players)
{
	UsOrPl = false;
	bool flag = true;
	int item;

	while (flag)
	{
		admin_menu();
		item = inNum(0, 5);

		switch (item)
		{
		case 1:
			showUsers(users);
			break;
		case 2:
			addUser(users);
			break;
		case 3:
			delUser(users);
			break;
		case 4:
			updUser(users);
			break;
		case 5:
			system("cls");
			user_core(users, players);
			flag = false;
			break;
		case 0:
			flag = false;
			break;
		default:
			system("cls");
		}
	}
}
void user_core(vector<Account>& users, vector<Person>& players)
{
	UsOrPl = true;
	bool flag = true;
	int item;

	while (flag)
	{	
		user_menu();

		if (adminstat == true)
			item = inNum(0, 7);
		else
			item = inNum(0, 4);

		switch (item)
		{
		case 0:
			flag = false;
			break;
		case 1:
			showPlayers(players);
			break;
		case 2:
			search(players);
			break;
		case 3:
			indTask(players);
			break;
		case 4:
			addPlayer(players);
			break;
		case 5:
			delPlayer(players);
			break;
		case 6:
			updatePlayer(players);
			break;
		case 7:
			system("cls");
			admin_core(users, players);
			flag = false;
			break;
		default:
			system("cls");
		}
	}
}

void readFileUsers(vector<Account>& users)
{
	ifstream fin(DataFileUsers, ios::in);

	Account obmanka;

	if (!(fin.is_open()) || fin.peek() == EOF)
	{
		addAdminAcc(users);
		writeFileUsers(users);
	}
	else
	{
		bool i = true;
		while (!fin.eof())
		{
			fin >> obmanka.login >> obmanka.password >> obmanka.role;
			while (i)
			{
				if (obmanka.login != "admin" && obmanka.role != 1)
				{
					addAdminAcc(users);
				}
				i = false;
			}
			users.push_back(obmanka);
		}
	}

	fin.close();
}
void readFilePlayers(vector<Person>& players)
{
	ifstream fin(DataFilePlayers, ios::in);

	Person obmanka;

	if (!(fin.is_open()) || fin.peek() == EOF)
	{
	}
	else
	{
		bool i = true;
		while (!fin.eof())
		{
			fin >> obmanka.surname >> obmanka.name >> obmanka.patronymic >> obmanka.birth.day >> obmanka.birth.month
				>> obmanka.birth.year >> obmanka.games >> obmanka.goals >> obmanka.assists >> obmanka.banMins;
			players.push_back(obmanka);
		}
	}

	fin.close();
}

void writeFileUsers(vector<Account>& users)
{
	ofstream fout(DataFileUsers, ios::out);

	for (int i = 0; i < users.size(); i++)
	{
		fout << users[i].login << " " << users[i].password << " " << users[i].role;

		if (i < users.size() - 1)
			fout << endl;
	}

	fout.close();
}
void writeFilePlayers(vector<Person>& players)
{
	ofstream fout(DataFilePlayers, ios::out);

	for (int i = 0; i < players.size(); i++)
	{
		fout << players[i].surname << " " << players[i].name << " " << players[i].patronymic << " " << players[i].birth.day << " " << players[i].birth.month << " "
			<< players[i].birth.year << " " << players[i].games << " " << players[i].goals << " " << players[i].assists << " " << players[i].banMins;

		if (i < players.size() - 1)
		{
			fout << endl;
		}
	}

	fout.close();
}

void writeUsersList(vector<Account>& users)
{
	cout << "\n";

	cout << "| № |   Логин  |   Пароль  | Статус |" << endl;

	palochki(37);

	for (int i = 0; i < users.size(); i++)
	{
		cout << "|" << setw(3) << i + 1 << "|" << setw(10) << users[i].login << "|" << setw(11) << users[i].password << "|" << setw(8) << users[i].role << "|" << endl;
		palochki(37);
	}
	cout << "\n";
}
void writePlayersList(vector<Person>& players)
{
	cout << "\n";

	cout << "| № |   Фамилия   |     Имя    |    Отчество   | Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |" << endl;

	palochki(100);

	for (int i = 0; i < players.size(); i++)
	{
		cout << "|" << setw(3) << i + 1 << "|" << setw(13) << players[i].surname << "|" << setw(12) << players[i].name << "|" << setw(15) << players[i].patronymic << "|"
			<< setw(5) << players[i].birth.day << "." << players[i].birth.month << "." << players[i].birth.year << "|" << setw(7) << players[i].games << "|" << setw(6)
			<< players[i].goals << "|" << setw(11) << players[i].assists << "|" << setw(11) << players[i].banMins << "|" << endl;
		palochki(100);
	}
	cout << "\n";
}
void writeSomePlayers(vector<Person>& players, int i)
{
	cout << "|" << setw(3) << i + 1 << "|" << setw(13) << players[i].surname << "|" << setw(12) << players[i].name << "|" << setw(15) << players[i].patronymic << "|"
		<< setw(5) << players[i].birth.day << "." << players[i].birth.month << "." << players[i].birth.year << "|" << setw(7) << players[i].games << "|" << setw(6)
		<< players[i].goals << "|" << setw(11) << players[i].assists << "|" << setw(11) << players[i].banMins << "|" << endl;
		
	palochki(100);
}

void showUsers(vector<Account>& users)
{
	system("cls");
	cout << "<--Admin panel" << endl;

	cout << "\tСписок пользователей" << endl;
	palochki(40);
	writeUsersList(users);

	cout << "Нажмите любую клавишу чтобы вернуться...";
	_getch();
	system("cls");
}
void showPlayers(vector<Person>& players)
{
	bool flag = true;
	while (flag)
	{
		system("cls");
		if (adminstat == true)
			cout << "<--User panel" << endl;
		else
			cout << "<--Меню" << endl;

		cout << "\t\t\t\t\tСписок игроков" << endl;
		palochki(100);
		writePlayersList(players);

		sort(players, flag);
	}
}


void addUser(vector<Account>& users)
{
	Account obmanka;

	system("cls");
	cout << "<--Admin panel" << endl;

	cout << "\tДобавление" << endl;
	palochki(40);

	writeUsersList(users);
	cout << "Для отмены введите 0\n";

	cout << "Введите логин: ";
	cin >> obmanka.login;

	if (obmanka.login != "0")
	{
		cout << "Введите пароль: ";
		cin >> obmanka.password;

		cout << "Введите роль: ";
		cin >> obmanka.role;

		users.push_back(obmanka);

		writeFileUsers(users);

		//adminPodmenu(users, item);
	}
	else
	{
		system("cls");
	}
}
void addPlayer(vector<Person>& players)
{
	Person obmanka;

	bool flag = true;
	while (flag)
	{
		system("cls");
		if (adminstat == true)
		{
			cout << "<--Admin panel" << endl;
		}
		else
		{
			cout << "<--Меню" << endl;
		}

		cout << "\t\t\t\t\tДобавление" << endl;
		palochki(40);

		writePlayersList(players);

		cout << "Для отмены введите 0\n";

		cout << "Введите фамилию: ";
		cin >> obmanka.surname;

		if (obmanka.surname != "0")
		{
			cout << "Введите имя: ";
			cin >> obmanka.name;

			cout << "Введите отчество: ";
			cin >> obmanka.patronymic;

			cout << "Введите дату рождения(цифрами)\n";
			cout << "День ";
			obmanka.birth.day = inNum(1, 31);
			cout << "Месяц ";
			obmanka.birth.month = inNum(1, 12);
			cout << "Год ";
			obmanka.birth.year = inNum(1922, 2004);

			cout << "Введите кол-во сыгранных матчей: ";
			obmanka.games = inNum(0, 999999);

			cout << "Введите число заброшенных шайб: ";
			obmanka.goals = inNum(0, 999999);

			cout << "Введите кол-во голевых передач: ";
			obmanka.assists = inNum(0, 999999);

			cout << "Введите кол-во штрафных минут: ";
			obmanka.banMins = inNum(0, 999999);

			players.push_back(obmanka);

			writeFilePlayers(players);
		}
		else
		{
			flag = false;
			system("cls");
		}
	}
}

void delFuncText()
{
	system("cls");
	if (UsOrPl == true)
		cout << "<--User panel" << endl;
	else
		cout << "<--Admin panel" << endl;

	cout << "\tУдаление" << endl;
	palochki(40);
	cout << "Какого " << whoWrote(UsOrPl) << " вы хотите удалить? Для выхода введите 0" << endl;
}
void delUser(vector<Account>& users)
{
	bool flag = true;
	while (flag)
	{
		delFuncText();
		writeUsersList(users);

		int index;
		index = inNum(0, users.size());

		switch (index)
		{
		case 0:
			system("cls");
			flag = false;
			break;
		default:
			index--;

			if (systemAdmin == false && users[index].role == 1)
			{
				cout << "Вы не можете удалить администратора." << endl;
				cout << "Нажмите любую клавишу чтобы вернуться...";
				_getch();
				break;
			}
			else
			{
				users.erase(users.begin() + index);

				writeFileUsers(users);
			}
		}
	}
}
void delPlayer(vector<Person>& players)
{
	bool flag = true;
	while (flag)
	{
		delFuncText();
		writePlayersList(players);

		int index;
		index = inNum(0, players.size());

		switch (index)
		{
		case 0:
			system("cls");
			flag = false;
			break;
		default:
			index--;
			players.erase(players.begin() + index);

			writeFilePlayers(players);

			break;
		}
	}
}

void updFuncText()
{
	system("cls");
	if (UsOrPl == true)
		cout << "<--User panel" << endl;
	else
		cout << "<--Admin panel" << endl;

	cout << "\tРедактирование\n";
	palochki(40);
	cout << "Какого " << whoWrote(UsOrPl) << " вы хотите редактировать? Для выхода введите 0\n";

}
void updUser(vector<Account>& users)
{
	bool flag = true;
	while (flag)
	{
		updFuncText();
		writeUsersList(users);

		int index;
		index = inNum(0, users.size());

		if (index == 0)
		{
			flag = false;
			system("cls");
		}
		else
		{
			index--;

			bool blag = true;
			while (blag)
			{
				system("cls");
				cout << "Что вы хотите редактировать? Для отмены введите 0\n";
				palochki(40);
				cout << "1) Логин: " << users[index].login << endl;
				cout << "2) Пароль: " << users[index].password << endl;
				cout << "3) Роль: " << users[index].role << endl;

				int choice;
				choice = inNum(0, 3);

				switch (choice)
				{
				case 0:
				{
					blag = false;
					break;
				}
				case 1:
				{
					system("cls");
					cout << "Новый логин: ";
					cout << users[index].login << " --> ";
					cin >> users[index].login;

					break;
				}
				case 2:
				{
					system("cls");
					cout << "Новый пароль: ";
					cout << users[index].password << " --> ";
					cin >> users[index].password;

					break;
				}
				case 3:
				{
					system("cls");
					cout << "Новая роль:\n";
					cout << users[index].role << " --> ";
					cin >> users[index].role;

					break;
				}
				default:
					system("cls");
				}
				writeFileUsers(users);
			}
		}
	}
}
void updatePlayer(vector<Person>& players)
{
	bool flag = true;
	while (flag)
	{
		updFuncText();
		writePlayersList(players);
		
		int index;
		index = inNum(0, players.size());

		if (index == 0)
		{
			flag = false;
			system("cls");
		}
		else
		{
			index--;

			bool blag = true;
			while (blag)
			{
				system("cls");

				cout << "1) Фамилия: " << players[index].surname << endl;
				cout << "2) Имя: " << players[index].name << endl;
				cout << "3) Отчество: " << players[index].patronymic << endl;
				cout << "4) Дата рождения: " << players[index].birth.day << "." << players[index].birth.month << "." << players[index].birth.year << endl;
				cout << "5) Количество матчей: " << players[index].games << endl;
				cout << "6) Число заброшенных шайб: " << players[index].goals << endl;
				cout << "7) Количество голевых передач: " << players[index].assists << endl;
				cout << "8) Штрафных минут: " << players[index].banMins << endl << endl;

				cout << "Что вы хотите изменить? Для отмены введите 0" << endl;
				int choice;
				choice = inNum(0, 8);
				switch (choice)
				{
				case 0:
					blag = false;

					break;
				case 1:
					cout << "Новая фамилия:" << endl;
					cout << players[index].surname << " --> ";
					cin >> players[index].surname;

					break;
				case 2:
					cout << "Новое имя:" << endl;
					cout << players[index].name << " --> ";
					cin >> players[index].name;

					break;
				case 3:
					cout << "Новое отчество:" << endl;
					cout << players[index].patronymic << " --> ";
					cin >> players[index].patronymic;

					break;
				case 4:
					cout << "Новая дата рождения:(вводите через пробел)" << endl;
					cout << players[index].birth.day << "." << players[index].birth.month << "." << players[index].birth.year << " --> ";
					cin >> players[index].birth.day >> players[index].birth.month >> players[index].birth.year;

					break;
				case 5:
					cout << "Новое количество матчей:" << endl;
					cout << players[index].games << " --> ";
					cin >> players[index].games;

					break;
				case 6:
					cout << "Новое число голов:" << endl;
					cout << players[index].goals << " --> ";
					cin >> players[index].goals;

					break;
				case 7:
					cout << "Новое число голевых передач:" << endl;
					cout << players[index].assists << " --> ";
					cin >> players[index].assists;

					break;
				case 8:
					cout << "Новое кол-во штрафных минут:" << endl;
					cout << players[index].banMins << " --> ";
					cin >> players[index].banMins;

					break;
				}
				writeFilePlayers(players);
			}
		}
	}
}

void indTask(vector<Person>& players)
{
	int uniqRes = 0;
	int count = 0;
	int k = 0;

	uniqRes = players.size();

	vector<int>resultArr; // Вектор с результативностью каждого игрока

	for (int i = 0; i < players.size(); i++)
	{
		k = players[i].assists + players[i].goals;
		resultArr.push_back(k);
	}

	for (int i = 0; i < uniqRes; i++) // Находим кол-во уникальных результативностей и выставляем их в начало
	{
		for (int j = 0; j < uniqRes; j++)
		{
			if (i != j)
			{
				if (resultArr[i] == resultArr[j])
				{
					swap(resultArr[uniqRes - 1], resultArr[j]);
					uniqRes--;
				}
			}
		}
	}
	

	for (int i = 1; i < uniqRes; i++) // Сортировка результативностей по убыванию
	{
		for (int j = 0; j < uniqRes - i; j++)
		{
			if (resultArr[j] < resultArr[j + 1])
			{
				swap(resultArr[j], resultArr[j + 1]);
			}
		}
	}

	system("cls");

	if (adminstat == true)
		cout << "<--User panel" << endl;
	else
		cout << "<--Меню" << endl;

	cout << "\t\t\t\t\tИндивидуальное задание\n\n";

	cout << "| № |   Фамилия   |     Имя    |    Отчество   | Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |" << endl;
	palochki(100);
	for (int i = 0; i < uniqRes; i++)
	{
		for (int j = 0; j < players.size(); j++)
		{
			if (resultArr[i] == players[j].assists + players[j].goals)
			{
				writeSomePlayers(players, j);
				count++;
			}
			if (count == 6)
			{
				break;
			}
		}
	}

	cout << "Нажмите любую клавишу чтобы вернуться...";
	_getch();
	system("cls");
}

void sort(vector<Person>& players, bool& flag)
{
	cout << "1) По фамилии" << endl;
	cout << "2) По количеству забитых шайб" << endl;
	cout << "3) По количеству матчей" << endl;
	cout << "0) Назад" << endl << endl;

	int choice;
	choice = inNum(0, 3);

	switch (choice)
	{
	case 0:
		flag = false;
		system("cls");
		break;
	case 1:
		sortSurname(players);
		break;
	case 2:
		sortNumOfPucks(players);
		break;
	case 3:
		sortMatch(players);
		break;
	}
}
void sortMatch(vector<Person>& players)
{
	for (int i = 0; i < players.size() - 1; i++)
	{
		for (int j = i + 1; j < players.size(); j++)
		{
			if (players[j].games > players[i].games)
				swap(players[j], players[i]);
		}
	}
}
void sortNumOfPucks(vector<Person>& players)
{
	for (int i = 0; i < players.size() - 1; i++)
	{
		for (int j = i + 1; j < players.size(); j++)
		{
			if (players[j].goals > players[i].goals)
				swap(players[j], players[i]);
		}
	}
}
void sortSurname(vector<Person>& players)
{
	for (int i = 1; i < players.size(); i++)
	{
		for (int j = 0; j < players.size() - i; j++)
		{
			if (players[j].surname > players[j+1].surname)
			{
				swap(players[j], players[j + 1]);
			}
		}
	}
}

void search(vector<Person>& players)
{
	bool flag = true;
	while (flag)
	{
		system("cls");

		if (adminstat == true)
			cout << "<--User panel" << endl;
		else
			cout << "<--Меню" << endl;

		cout << "\tПоиск по параметрам" << endl;
		palochki(40);

		cout << "1) Поиск по фамилии" << endl;
		cout << "2) Поиск по голам" << endl;
		cout << "3) Поиск по количеству матчей" << endl;
		cout << "0) Назад" << endl << endl;

		int choice;
		choice = inNum(0, 3);

		switch (choice)
		{
		case 0:
			flag = false;
			system("cls");
			break;
		case 1:
			searchSurname(players);
			system("cls");
			break;
		case 2:
			searchGoals(players);
			system("cls");
			break;
		case 3:
			searchMatches(players);
			system("cls");
			break;
		}
	}
}
void searchSurname(vector<Person>& players)
{
	bool flag = true;
	system("cls");

	cout << "<--Поиск по параметрам\n\n";
	cout << "\tПоиск по фамилии\n";
	
	palochki(36);

	cout << "Для отмены введите 0.\n";

	string surname;
	cout << "Введите фамилию игрока: ";
	cin >> surname;

	if (surname == "0")
		flag = false;

	int k = surname.length();

	while (flag)
	{
		system("cls");
		cout << "<--Поиск по параметрам" << endl;

		cout << "\t\t\t\t\tСписок игроков\n\n";

		int n = 0;
		bool match = false;

		cout << "| № |   Фамилия   |     Имя    |    Отчество   | Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |" << endl;
		palochki(100);

		for (int i = 0; i < players.size(); i++)
		{
			for (int j = 0; j < k; j++)
			{
				if (players[i].surname[j] == surname[j])
				{
					match = true;
				}
				else
				{
					match = false;
					break;
				}
			}

			if (match == true)
			{
				writeSomePlayers(players, i);
				n++;
				match = false;
			}
		}
		
		if (n == 0)
		{
			cout << "\nИгроков с такой фамилией не найдено\n";
		}

		cout << "Нажмите любую клавишу чтобы вернутсья...";
		
		_getch();
			
		flag = false;
	}
}
void searchGoals(vector<Person>& players)
{
	bool flag = true;
	system("cls");

	cout << "<--Поиск по параметрам\n\n";
	cout << "\tПоиск по количеству забитых голов.\n";

	palochki(50);

	cout << "Для отмены введите 0\n";

	int goals;
	cout << "Введите количество голов: ";
	cin >> goals;

	if (goals == 0)
		flag = false;

	while (flag)
	{
		system("cls");
		cout << "<--Поиск по параметрам\n\n";

		cout << "\t\t\t\t\tСписок игроков\n\n";

		int n = 0;

		cout << "| № |   Фамилия   |     Имя    |    Отчество   | Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |" << endl;
		palochki(100);

		for (int i = 0; i < players.size(); i++)
		{
			if (players[i].goals == goals)
			{
				writeSomePlayers(players, i);
				n++;
			}
		}

		if (n == 0)
		{
			cout << "\nИгроков с таким количеством голов не найдено\n";
		}

		cout << "Нажмите любую клавишу чтобы вернутсья...";
		
		_getch();

		flag = false;
	}
}
void searchMatches(vector<Person>& players)
{
	bool flag = true;
	system("cls");

	cout << "<--Поиск по параметрам\n\n";
	cout << "\tПоиск по количеству матчей.\n";

	palochki(43);

	cout<<"Для отмены введите 0\n";

	int games;
	cout << "Введите количество матчей: ";
	cin >> games;

	if (games == 0)
		flag = false;

	while (flag)
	{
		system("cls");
		cout << "<--Поиск по параметрам" << endl;

		cout << "\t\t\t\t\tСписок игроков\n\n";

		int n = 0;

		cout << "| № |   Фамилия   |     Имя    |    Отчество   | Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |" << endl;
		palochki(100);

		for (int i = 0; i < players.size(); i++)
		{
			if (players[i].games == games)
			{
				writeSomePlayers(players, i);
				n++;
			}
		}

		if (n == 0)
		{
			cout << "\nИгроков с таким количеством матчей не найдено\n";
		}

		cout << "Нажмите любую клавишу чтобы вернутсья...";

		_getch();

		flag = false;
	}
}

/*
void adminPodmenu(vector<Account>& users, int item)
{
	bool flag;
	switch (item)
	{
	case 1:
		flag = true;

		while (flag)
		{
			cout << "Нажмите любую клавишу чтобы вернуться...";
			_getch();

			system("cls");
			flag = false;
		}

		break;
	case 2:
		flag = true;

		while (flag)
		{
			cout << "\n";
			cout << "1) Добавить еще одного пользователя" << endl;
			cout << "0) Назад" << endl;

			int num;
			num = inNum(0, 1);
			switch (num)
			{
			case 1:
				addUser(users, item);
				flag = false;

				break;
			case 0:
				system("cls");
				flag = false;

				break;
			default:
				system("cls");
			}
		}

		break;
	case 3:
		flag = true;

		while (flag)
		{
			cout << "\n";
			cout << "1) Удалить еще одного пользователя" << endl;
			cout << "0) Назад" << endl;

			int num;
			num = inNum(0, 1);
			switch (num)
			{
			case 1:
				delUser(users, item);
				flag = false;

				break;
			case 0:
				system("cls");
				flag = false;

				break;
			default:
				system("cls");
			}
		}

		break;
	case 4:
		flag = true;

		while (flag)
		{
			cout << "\n";
			cout << "1) Редактировать еще одного пользователя" << endl;
			cout << "0) Назад" << endl;

			int num;
			num = inNum(1, 2);
			switch (num)
			{
			case 1:
				updUser(users, item);
				flag = false;

				break;
			case 0:
				system("cls");
				flag = false;

				break;
			default:
				system("cls");
			}
		}

		break;
	}
}
void userPodmenu(vector<Person>& players, int item)
{
	bool flag;
	switch (item)
	{
	case 1:
		flag = true;

		while (flag)
		{
			cout << "Нажмите любую клавишу чтобы вернуться...";
			_getch();

			system("cls");
			flag = false;
		}

		break;
	case 2:
		flag = true;


	case 3:
		flag = true;

		while (flag)
		{
			cout << "\n";
			cout << "1) Добавить еще одного игрока" << endl;
			cout << "0) Назад" << endl;

			int num;
			num = inNum(0, 1);
			switch (num)
			{
			case 1:
				addPlayer(players, item);
				flag = false;

				break;
			case 0:
				system("cls");
				flag = false;

				break;
			default:
				system("cls");
			}
		}

		break;
	case 4:
		flag = true;

		while (flag)
		{
			cout << "\n";
			cout << "1) Удалить еще одного игрока" << endl;
			cout << "0) Назад" << endl;

			int num;
			num = inNum(0, 1);
			switch (num)
			{
			case 1:
				delPlayer(players, item);
				flag = false;

				break;
			case 0:
				system("cls");
				flag = false;

				break;
			default:
				system("cls");
			}
		}

		break;
	case 5:
		flag = true;

		while (flag)
		{
			cout << "\n";
			cout << "1) Редактировать еще одного игрока" << endl;
			cout << "0) Назад" << endl;

			int num;
			num = inNum(0, 1);
			switch (num)
			{
			case 1:
				updatePlayer(players, item);
				flag = false;

				break;
			case 0:
				system("cls");
				flag = false;

				break;
			default:
				system("cls");
			}
		}

		break;
	}
}
*/