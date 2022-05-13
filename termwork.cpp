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

void palochki(int);
string whoWrote(bool UsOrPl);
int inNum(int min, int max);

void hellomenu(vector<Account>&, vector<Person>&);
void chooseMenu(vector<Account>&, vector<Person>&);
void signup(vector<Account>&, vector<Person>&);
void signin(vector<Account>&, vector<Person>&);
string enterPass();
string checkLogPass();

void addAdminAcc(vector<Account>&);
void delAdminAcc(vector<Account>&);

void admin_menu();
void user_menu();

void admin_core(vector<Account>&, vector<Person>&);
void user_core(vector<Account>&, vector<Person>&);

void readFileUsers(vector<Account>&);
void readFilePlayers(vector<Person>&);

void writeFileUsers(vector<Account>&);
void writeFilePlayers(vector<Person>&);

void writeUsersList(vector<Account>&);
void writePlayersList(vector<Person>&);
void writeSomePlayers(vector<Person>&, int);

void showUsers(vector<Account>&);
void showPlayers(vector<Person>&);

void addUser(vector<Account>&);
void addPlayer(vector<Person>&);

void delUser(vector<Account>&);
void delPlayer(vector<Person>&);

void updUser(vector<Account>&);
void updatePlayer(vector<Person>&);

void indTask(vector<Person>&);

void sort(vector<Person>&, bool&);
void sortSurname(vector<Person>& players);
void sortNumOfPucks(vector<Person>& players);
void sortMatch(vector<Person>& players);

void search(vector<Person>&);
void searchSurname(vector<Person>&);
void searchGoals(vector<Person>&);
void searchMatches(vector<Person>&);


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
	cout << "\n";
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
			if (min == 21 && max == 2)
				break;
			else
			{
				if (input >= min && input <= max)
					break;

				else
				{
					cout << "Недопустимое значение.\n";
				}
			}
		}
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Введите число.\n";
		}
	}
	return input;
}

void hellomenu(vector<Account>& users, vector<Person>& players)
{
	bool exit = true;
	while (exit)
	{
		cout << "\t-----  Добро пожаловать  -----\n\n";
		cout << "\t1 - Создать аккаунт\n";
		cout << "\t2 - Войти в существующий\n";
		cout << "\t0 - Выход\n\n";

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
void chooseMenu(vector<Account>& users, vector<Person>& players)
{
	if (adminstat == true)
		admin_core(users, players);
	else
		user_core(users, players);
}
void signup(vector<Account>& users, vector<Person>& players)
{
	Account obmanka;
	bool flag = true;
	while (flag)
	{
		system("cls");
		cout << "<--Приветствие\n\n";
		cout << "\t-----  Регистрация  -----\n\n";
		cout << "Для возврата введите 0\n";

		cout << "Придумайте логин для входа:\n";
		
		obmanka.login = checkLogPass();

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
				cout << "Данный логин занят. Попробуйте другой\n\n";
				cout << "Нажмите любую клавишу чтобы вернуться...";
				_getch();
			}
			else
			{
				flag = false;
				cout << "\nПридумайте пароль:\n";
				
				obmanka.password = checkLogPass();

				if (obmanka.password == "0")
				{
					system("cls");
					flag = false;
				}
				else
				{
					obmanka.role = 0;

					users.push_back(obmanka);

					writeFileUsers(users);

					system("cls");
					adminstat = false;
					cout << "Добро пожаловать, " << obmanka.login << "\n";
					user_core(users, players);
				}
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
		cout << "<--Приветствие\n\n";
		cout << "\t-----  Авторизация  -----\n\n";
		cout << "Для возврата введите 0\n";
		cout << "Введите логин:\n";
		string log;

		cout << "   - ";
		cin >> log;

		if (log == "0")
		{
			system("cls");
			er = false;
		}
		else
		{
			cout << "Введите пароль:\n";
			cout<<"   - ";
			string pass = enterPass();

			for (int i = 0; i < users.size(); i++)
			{
				if (users[i].login == log && users[i].password == pass)
				{
					if (users[i].role == 1)
						adminstat = true;
					else
						adminstat = false;

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
					cout << "\nПроверьте правильность данных\n";
					cout << "Нажмите любую клавишу чтобы вернуться...";
					_getch();
					break;
				}
			}
		}
	}
}
string checkLogPass()
{
	string str;
	bool flag = true;

	while (flag)
	{
		cout << "   - ";
		cin >> str;

		for (int i = 0; i < str.length(); i++)
		{
			if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
			{
			}
			else
			{
				cout << "Должны использоваться латинские буквы и(или) цифры!\n";
				break;
			}
			if (i == str.length() - 1)
			{
				if (str.length() >= 6 && str.length() <= 16)
				{
					return str;
					flag = false;
				}
				else if (str.length() == 1 && str[0] == '0')
				{
					return str;
					flag = false;
				}
				else
				{
					cout << "Длина должна составлять от 6 до 16 символов!\n";
					break;
				}
			}
		}
	}
}
string enterPass()
{
	char pass[256];
	int i = 0;

	while(true)
	{
		pass[i] = _getch();

		if (pass[i] == 13)
			break;

		if (pass[i] == 8)
		{
			if (i == 0)
			{
				continue;
			}
			else
			{
				pass[i - 1] = '\0';
				cout << "\b \b";
				i--;
			}
		}
		else
		{
			cout << "*";
			i++;
		}

		
	}
	pass[i] = '\0';

	return pass;
}

void addAdminAcc(vector<Account>& users)
{
	Account obmanka;
	
	obmanka.login = "admin";
	obmanka.password = "admin";
	obmanka.role = 1;

	users.push_back(obmanka);
}
void delAdminAcc(vector<Account>& users)
{
	for (int i = 1; i < users.size(); i++)
	{
		if (users[i].login == "admin")
		{
			users.erase(users.begin() + i);
		}
	}

	writeFileUsers(users);
}

void admin_menu()
{
	cout << "\t-----  Admin panel  -----\n\n";
	cout << "\t1 - Просмотр\n";
	cout << "\t2 - Добавление\n";
	cout << "\t3 - Удаление\n";
	cout << "\t4 - Редактирование\n";
	cout << "\t5 - User panel\n";
	cout << "\t0 - Выход\n\n";

}
void user_menu()
{
	if (adminstat == true)
		cout << "\t-----  User panel  -----\n\n";
	else
		cout << "\t-----  Меню  -----\n\n";

	cout << "\t1 - Просмотр\n";
	cout << "\t2 - Поиск по параметрам\n";
	cout << "\t3 - Индивидуальное задание\n";
	
	if (adminstat == true)
	{
		cout << "\t4 - Добавление\n";
		cout << "\t5 - Удаление\n";
		cout << "\t6 - Редактирование\n";
		cout << "\t7 - Admin panel\n";
	}
	cout << "\t0 - Выход\n\n";
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
			item = inNum(0, 3);

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

		delAdminAcc(users);
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
			fout << "\n";
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
			fout << "\n";
		}
	}

	fout.close();
}

void writeUsersList(vector<Account>& users)
{
	cout << "\n";

	cout << "| № |   Логин  |   Пароль  | Статус |\n";

	palochki(37);

	for (int i = 0; i < users.size(); i++)
	{
		cout << "|" << setw(3) << i + 1 << "|" << setw(10) << users[i].login << "|" << setw(11) << users[i].password << "|" << setw(8) << users[i].role << "|" << "\n";
		palochki(37);
	}
	cout << "\n";
}
void writePlayersList(vector<Person>& players)
{
	cout << "\n";

	cout << "| № |   Фамилия   |     Имя    |    Отчество   |  Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |" << "\n";

	palochki(101);

	for (int i = 0; i < players.size(); i++)
	{
		cout << "|" << setw(3) << i + 1 << "|" << setw(13) << players[i].surname << "|" << setw(12) << players[i].name << "|" << setw(15) << players[i].patronymic << "|"
			<< setw(5) << players[i].birth.day << "."; 
		if (players[i].birth.month < 10)
			cout << "0"; 
		cout << players[i].birth.month << "." << players[i].birth.year << "|" << setw(7) << players[i].games << "|" << setw(6)
			<< players[i].goals << "|" << setw(11) << players[i].assists << "|" << setw(11) << players[i].banMins << "|" << "\n";
		palochki(101);
	}
	cout << "\n";
}
void writeSomePlayers(vector<Person>& players, int i)
{
	cout << "|" << setw(3) << i + 1 << "|" << setw(13) << players[i].surname << "|" << setw(12) << players[i].name << "|" << setw(15) << players[i].patronymic << "|"
		<< setw(5) << players[i].birth.day << ".";
	if (players[i].birth.month < 10)
		cout << "0";
	cout << players[i].birth.month << "." << players[i].birth.year << "|" << setw(7) << players[i].games << "|" << setw(6)
		<< players[i].goals << "|" << setw(11) << players[i].assists << "|" << setw(11) << players[i].banMins << "|" << "\n";
		
	palochki(101);
}

void showUsers(vector<Account>& users)
{
	system("cls");
	cout << "<--Admin panel\n\n";

	cout << "\t-----  Список пользователей  -----\n\n";
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
			cout << "<--User panel\n\n";
		else
			cout << "<--Меню\n\n";

		cout << "\t\t\t\t-----  Список игроков  -----\n\n";
		writePlayersList(players);

		sort(players, flag);
	}
}

void addUser(vector<Account>& users)
{
	Account obmanka;

	bool flag = true;
	while (flag)
	{
		system("cls");
		cout << "<--Admin panel\n\n";

		cout << "\t-----  Добавление  -----\n\n";

		writeUsersList(users);
		cout << "Чтобы вернуться введите 0\n\n";

		cout << "Введите логин: ";
		obmanka.login = checkLogPass();

		if (obmanka.login != "0")
		{
			cout << "Введите пароль: ";
			obmanka.password = checkLogPass();

			cout << "Введите роль: ";
			cin >> obmanka.role;

			users.push_back(obmanka);

			writeFileUsers(users);
		}
		else
		{
			flag = false;
			system("cls");
		}
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
			cout << "<--Admin panel\n\n";
		}
		else
		{
			cout << "<--Меню\n\n";
		}

		cout << "\t\t\t\t-----  Добавление  -----\n";
		palochki(100);

		writePlayersList(players);

		cout << "Чтобы вернуться введите 0\n\n";

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
			obmanka.games = inNum(0, 1000);

			cout << "Введите число заброшенных шайб: ";
			obmanka.goals = inNum(0, 1000);

			cout << "Введите кол-во голевых передач: ";
			obmanka.assists = inNum(0, 1000);

			cout << "Введите кол-во штрафных минут: ";
			obmanka.banMins = inNum(0, 1000);

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

void delUser(vector<Account>& users)
{
	bool flag = true;
	while (flag)
	{
		system("cls");
		cout << "<-- Admin panel\n\n";

		cout << "\t-----  Удаление  -----\n\n";

		writeUsersList(users);
		cout << "Какого пользователя вы хотите удалить? Чтобы вернуться введите 0\n\n";

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

			string YN;
			while (true)
			{
				cout << "Вы уверены что хотите удалить " << users[index].login << "?(Y/N):";
				cin >> YN;

				if (YN == "Y" || YN == "y")
				{
					if (systemAdmin == false && users[index].role == 1 || index == 0)
					{
						cout << "Вы не можете удалить администратора.\n";
						cout << "Нажмите любую клавишу чтобы вернуться...";
						_getch();
						break;
					}
					else
					{
						users.erase(users.begin() + index);

						writeFileUsers(users);
						break;
					}
				}
				else if (YN == "N" || YN == "n")
				{
					break;
				}
				else
				{
					cout << "Проверьте корректность ввода!\n";
				}
			}
		}
	}
}
void delPlayer(vector<Person>& players)
{
	bool flag = true;
	while (flag)
	{
		system("cls");
		if (adminstat == true)
			cout << "<-- User panel\n\n";
		else
			cout << "<-- Меню\n\n";

		cout << "\t\t\t\t-----  Удаление  -----\n";
		palochki(100);

		writePlayersList(players);
		cout << "Какого игрока вы хотите удалить? Для выхода введите 0\n\n";

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

			string YN;
			while (true)
			{
				cout << "Вы уверены что хотите удалить " << players[index].surname << " " << players[index].name << "?(Y/N):";
				cin >> YN;

				if (YN == "Y" || YN == "y")
				{
					players.erase(players.begin() + index);

					writeFilePlayers(players);
					break;
				}
				else if (YN == "N" || YN == "n")
				{
					break;
				}
				else
				{
					cout << "Проверьте корректность ввода!\n";
				}
			}

			players.erase(players.begin() + index);

			writeFilePlayers(players);

			break;
		}
	}
}

void updUser(vector<Account>& users)
{
	bool flag = true;
	while (flag)
	{
		system("cls");
		cout << "<-- Admin panel\n\n";
		cout << "\t-----  Редактирование  -----\n\n";

		writeUsersList(users);
		cout << "Какого пользователя вы хотите редактировать? Чтобы вернуться введите 0\n\n";

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
				cout << "<--Редактирование\n\n";
				cout << "\t-----  Данные " << users[index].login << "  -----\n\n";

				cout << "\t1 - Логин: " << users[index].login << "\n";
				cout << "\t2 - Пароль: " << users[index].password << "\n";
				cout << "\t3 - Роль: " << users[index].role << "\n";
				cout << "\t0 - Назад\n\n";

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
					cout << "Старый логин: " << users[index].login << "\n";
					cout << "Новый логин:\n";
					cin >> users[index].login;

					break;
				}
				case 2:
				{
					cout << "Старый пароль: " << users[index].password << "\n";
					cout << "Новый пароль:\n";
					cin >> users[index].password;

					break;
				}
				case 3:
				{
					cout << "Старая роль: " << users[index].role << "\n";
					cout << "Новая роль:\n";
					users[index].role = inNum(0,1);

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
		system("cls");
		if (adminstat == true)
			cout << "<-- User panel\n\n";
		else
			cout << "<-- Меню\n\n";

		cout << "\t\t\t\t-----  Редактирование  -----\n\n";

		writePlayersList(players);

		cout << "Какого игрока вы хотите редактировать? Чтобы вернуться введите 0\n\n";
		
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
				cout << "<-- Редактирование\n\n";
				
				cout << "/t----- Данные игрока  -----\n\n";

				cout << "\t1 - Фамилия: " << players[index].surname << "\n";
				cout << "\t2 - Имя: " << players[index].name << "\n";
				cout << "\t3 - Отчество: " << players[index].patronymic << "\n";
				cout << "\t4 - Дата рождения: " << players[index].birth.day << "." << players[index].birth.month << "." << players[index].birth.year << "\n";
				cout << "\t5 - Количество матчей: " << players[index].games << "\n";
				cout << "\t6 - Число заброшенных шайб: " << players[index].goals << "\n";
				cout << "\t7 - Количество голевых передач: " << players[index].assists << "\n";
				cout << "\t8 - Штрафных минут: " << players[index].banMins << "\n\n";

				cout << "Что вы хотите изменить? Для отмены введите 0\n\n";
				int choice;
				choice = inNum(0, 8);
				switch (choice)
				{
				case 0:
					blag = false;

					break;
				case 1:
					cout << "Новая фамилия:\n";
					cout << players[index].surname << " --> ";
					cin >> players[index].surname;

					break;
				case 2:
					cout << "Новое имя:\n";
					cout << players[index].name << " --> ";
					cin >> players[index].name;

					break;
				case 3:
					cout << "Новое отчество:\n";
					cout << players[index].patronymic << " --> ";
					cin >> players[index].patronymic;

					break;
				case 4:
					cout << "Новая дата рождения:(вводите через пробел)\n";
					cout << players[index].birth.day << "." << players[index].birth.month << "." << players[index].birth.year << " --> ";
					cin >> players[index].birth.day >> players[index].birth.month >> players[index].birth.year;

					break;
				case 5:
					cout << "Новое количество матчей:\n";
					cout << players[index].games << " --> ";
					players[index].games = inNum(0, 1000);

					break;
				case 6:
					cout << "Новое число голов:\n";
					cout << players[index].goals << " --> ";
					players[index].goals = inNum(0, 1000);

					break;
				case 7:
					cout << "Новое число голевых передач:\n";
					cout << players[index].assists << " --> ";
					players[index].assists = inNum(0, 1000);

					break;
				case 8:
					cout << "Новое кол-во штрафных минут:\n";
					cout << players[index].banMins << " --> ";
					players[index].banMins = inNum(0, 1000);

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
		cout << "<--User panel\n\n";
	else
		cout << "<--Меню\n\n";

	cout << "\t\t\t\t\tИндивидуальное задание\n";
	palochki(100);

	cout << "\n| № |   Фамилия   |     Имя    |    Отчество   | Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |" << "\n";
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

	cout << "\nНажмите любую клавишу чтобы вернуться...";
	_getch();
	system("cls");
}

void sort(vector<Person>& players, bool& flag)
{
	cout << "1 - По фамилии\n";
	cout << "2 - По количеству матчей\n";
	cout << "3 - По количеству забитых шайб\n";
	cout << "0 - Назад\n\n";

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
		sortMatch(players);
		break;
	case 3:
		sortNumOfPucks(players);
		break;
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

void search(vector<Person>& players)
{
	bool flag = true;
	while (flag)
	{
		system("cls");

		if (adminstat == true)
			cout << "<--User panel\n\n";
		else
			cout << "<--Меню\n\n";

		cout << "\t-----  Поиск по параметрам -----\n\n";

		cout << "\t1 - Поиск по фамилии\n";
		cout << "\t2 - Поиск по голам\n";
		cout << "\t3 - Поиск по количеству матчей\n";
		cout << "\t0 - Назад\n\n";

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
	cout << "\t-----  Поиск по фамилии  -----\n\n";

	cout << "Чтобы вернуться введите 0\n\n";

	string surname;
	cout << "Введите фамилию игрока: ";
	cin >> surname;

	if (surname == "0")
		flag = false;

	int k = surname.length();

	while (flag)
	{
		system("cls");
		cout << "<--Поиск по параметрам\n";

		cout << "\t\t\t\t-----  Список игроков  -----\n\n";

		int n = 0;
		bool match = false;

		cout << "| № |   Фамилия   |     Имя    |    Отчество   |  Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |\n";
		palochki(101);

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
			cout << "\nИгроков с фамилией \"" << surname << "\" не найдено\n";
		}

		cout << "Нажмите любую клавишу чтобы вернуться...";
		_getch();
			
		flag = false;
	}
}
void searchGoals(vector<Person>& players)
{
	bool flag = true;
	system("cls");

	cout << "<--Поиск по параметрам\n\n";
	cout << "\t-----  Поиск по количеству забитых голов  -----\n\n";

	cout << "Чтобы вернуться введите 0\n";

	int goals;
	cout << "Введите количество голов: ";
	goals = inNum(-1000, 1000);

	if (goals == 0)
		flag = false;

	while (flag)
	{
		system("cls");
		cout << "<--Поиск по параметрам\n\n";

		cout << "\t\t\t\t-----  Список игроков  -----\n\n";

		int n = 0;

		cout << "| № |   Фамилия   |     Имя    |    Отчество   |  Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |\n";
		palochki(101);

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
	cout << "\t-----  Поиск по количеству матчей  -----\n\n";

	cout<<"Для отмены введите 0\n";

	int games;
	cout << "Введите количество матчей: ";
	cin >> games;

	if (games == 0)
		flag = false;

	while (flag)
	{
		system("cls");
		cout << "<--Поиск по параметрам\n\n";

		cout << "\t\t\t\t-----  Список игроков  -----\n\n";

		int n = 0;

		cout << "| № |   Фамилия   |     Имя    |    Отчество   |  Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |\n";
		
		palochki(101);

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
