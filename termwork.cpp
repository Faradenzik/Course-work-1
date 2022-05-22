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
int curind;


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


void hellomenu(vector<Account>&, vector<Person>&);// Приветственное меню
void chooseMenu(vector<Account>&, vector<Person>&);// Перенаправление в меню администратора/пользователя
void signup(vector<Account>&, vector<Person>&);// Регистрация
void signin(vector<Account>&, vector<Person>&);// Авторизация

string enterPass();// Проверка ввода пароля
string checkLogPass();// Проверка ввода логина
string checkNSP(bool&);// Проверка ФИО на корректный ввод
void palochki(int);// Выводит строку из "-"
int inNum(int, int);// Проверка на ввод чисел из диапазона
bool checkForNum(string);// Проверка на число в строке

void addAdminAcc(vector<Account>&);// Добавление аккаунта Гл.администратора
void delAdminAcc(vector<Account>&);// Удаление аккаунта с именем "admin"

void admin_menu();// Содержание админ-меню
void user_menu();// Содержание польз.меню

void admin_core(vector<Account>&, vector<Person>&);// Админ-меню
void user_core(vector<Account>&, vector<Person>&);// Польз.меню

void readFileUsers(vector<Account>&);// Чтение пользователей из файла
void readFilePlayers(vector<Person>&);// Чтение игроков из файла

void writeFileUsers(vector<Account>&);// Запись пользователей в файл
void writeFilePlayers(vector<Person>&);// Запись игроков в файл

void writeUsersList(vector<Account>&);// Вывод списка пользователей
void writePlayersList(vector<Person>&);// Вывод списка игроков
void writeSomePlayers(vector<Person>&, int);// Вывод определенного игрока

void showUsers(vector<Account>&);// Шапка списка пользователей
void showPlayers(vector<Person>&);//  Список и сортировка игроков

void addUser(vector<Account>&);// Добавление пользователя
void addPlayer(vector<Person>&);// Добавление игрока

void delUser(vector<Account>&);// Удаление пользователя
void delPlayer(vector<Person>&);// Удаление игрока

void updUser(vector<Account>&);// Редактирование пользователя
void updatePlayer(vector<Person>&);// Редактирование игрока

void indTask(vector<Person>&);// Индивидуальное задание

void sort(vector<Person>&, bool&);// Меню сортировки
void sortSurname(vector<Person>&);// Сортировка по фамилии
void sortMatch(vector<Person>&);// Сортировка по количеству матчей
void sortGoals(vector<Person>&);// Сортировка по количеству голов


void search(vector<Person>&);// Меню поиска
void searchSurname(vector<Person>&);// Поиск по фамилии
void searchGoals(vector<Person>&);// Поиск по количеству голов
void searchMatches(vector<Person>&);// Поиск по количеству матчей


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


void hellomenu(vector<Account>& users, vector<Person>& players)
{
	bool flag = true;
	while (flag)
	{
		cout << "\t\t-----  Добро пожаловать  -----\n\n";
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
			flag = false;
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
void signin(vector<Account>& users, vector<Person>& players)
{
	bool flag = true;
	int count = 0;
	while (flag)
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
			flag = false;
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

					if (log == users[0].login)
						systemAdmin = true;
					else
						systemAdmin = false;

					system("cls");
					cout << "Добро пожаловать, " << log << "\n\n";
					
					curind = i;
					
					flag = false;
					chooseMenu(users, players);
					break;
				}
				else if (i == users.size() - 1)
				{
					count++;
					if (count == 3)
					{
						cout << "\nСлишком много неверных попыток!\n";
						_getch();
						flag = false;
						system("cls");
						break;
					}
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
string checkNSP(bool& flag)
{
	string str;
	cin >> str;

	for (int i = 0; i < str.length(); i++)
	{
		if(str[i] >= 'A' && str[i] <= 'Z' || str[i] >='a' && str[i] <= 'z' || str[i] >= 'А' && str[i] <= 'Я' 
			|| str[i] >= 'а' && str[i] <= 'я')
		{
		}
		else
		{
			cout << "Должны быть только буквы!\n";
			break;
		}

		if (i == str.length() - 1)
		{
			flag = false;
		}
	}


	return str;
}
void palochki(int k)
{
	for (int i = 0; i < k; i++)
		cout << "-";
	cout << "\n";
}
int inNum(int min, int max)
{
	double input;
	while (true)
	{
		cout << ">> ";
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
					cout << "Выберите из списка.\n\n";
				}
			}
		}
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Введите число.\n\n";
		}
	}
	return input;
}
bool checkForNum(string str)
{
	for (int i = 0; i <= str.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9' || str[i] == '-')
		{
			if (i == str.length() - 1)
				return true;
		}
		else
			return false;
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
	bool flag = true;
	int item;

	while (flag)
	{
		admin_menu();
		item = inNum(-99999, 99999);

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

	if (systemAdmin == false)
	{
		cout << "\t| № |   Логин  |   Пароль  | Статус |\n";

		cout << "\t";
		palochki(37);

		for (int i = 0; i < users.size(); i++)
		{
			cout << "\t|" << setw(3) << i + 1 << "|" << setw(10) << users[i].login << "|" << setw(11) << "********" << "|" << setw(8) << users[i].role << "|\n";
			cout << "\t";
			palochki(37);
		}
	}
	else
	{
		cout << "\t| № |      Логин     |      Пароль    | Статус |\n";

		cout << "\t";
		palochki(48);

		for (int i = 0; i < users.size(); i++)
		{
			cout << "\t|" << setw(3) << i + 1 << "|" << setw(16) << users[i].login << "|" << setw(16) << users[i].password << "|" << setw(8) << users[i].role << "|\n";
			cout << "\t";
			palochki(48);
		}
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

	cout << "\t\t-----  Список пользователей  -----\n\n";
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

		cout << "\t\t\t\t\t-----  Список игроков  -----\n\n";
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

		cout << "\t\t-----  Добавление  -----\n\n";

		writeUsersList(users);
		cout << "Чтобы вернуться введите 0\n\n";

		cout << "Введите логин: ";
		cin >> obmanka.login;

		if (obmanka.login != "0")
		{
			cout << "Введите пароль: ";
			cin >> obmanka.password;

			if (systemAdmin == true)
			{
				cout << "Введите роль: ";
				obmanka.role = inNum(-100, 100);
			}
			else
			{
				obmanka.role = 0;
			}
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

		cout << "\t\t\t\t\t-----  Добавление  -----\n\n";

		writePlayersList(players);

		cout << "Чтобы вернуться введите \"exit\"\n\n";

		bool blag = true;
		while (blag)
		{
			cout << "Введите фамилию: ";
			obmanka.surname = checkNSP(blag);
		}

		if (obmanka.surname != "exit")
		{
			blag = true;
			while (blag)
			{
				cout << "Введите имя: ";
				obmanka.name = checkNSP(blag);
			}
			blag = true;
			while (blag)
			{
				cout << "Введите отчество: ";
				obmanka.patronymic = checkNSP(blag);
			}
			cout << "Введите дату рождения(цифрами)\n";
			cout << "День ";
			obmanka.birth.day = inNum(1, 31);
			cout << "Месяц ";
			obmanka.birth.month = inNum(1, 12);
			cout << "Год ";
			obmanka.birth.year = inNum(1922, 2004);

			cout << "Введите кол-во сыгранных матчей ";
			obmanka.games = inNum(0, 1000);

			cout << "Введите число заброшенных шайб ";
			obmanka.goals = inNum(0, 1000);

			cout << "Введите кол-во голевых передач ";
			obmanka.assists = inNum(0, 1000);

			cout << "Введите кол-во штрафных минут ";
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

		cout << "\t\t-----  Удаление  -----\n\n";

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
					if (systemAdmin == false && users[index].role == 1 && index != curind)
					{
						cout << "Вы не можете удалить другого администратора.\n\n";
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

		cout << "\t\t\t\t\t-----  Удаление  -----\n";

		writePlayersList(players);
		cout << "Какого игрока вы хотите удалить? Чтобы вернуться введите 0\n\n";

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
		cout << "\t\t-----  Редактирование  -----\n\n";

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

			if (systemAdmin == false && users[index].role == 1 && index != curind)
			{
				cout << "Вы не можете редактировать другого администратора.\n\n";
				cout << "Нажмите любую клавишу чтобы вернуться...";
				_getch();
				blag = false;
			}

			while (blag)
			{
				system("cls");
				cout << "<--Редактирование\n\n";
				cout << "\t-----  Данные пользователя  -----\n\n";

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
					cout << "Новый логин >> ";
					cin >> users[index].login;

					break;
				}
				case 2:
				{
					cout << "Новый пароль: >> ";
					cin >> users[index].password;

					break;
				}
				case 3:
				{
					cout << "Новая роль ";
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

		cout << "\t\t\t\t\t-----  Редактирование  -----\n\n";

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
				
				cout << "\t\t----- Данные игрока  -----\n\n";

				cout << "\t1 - Фамилия: " << players[index].surname << "\n";
				cout << "\t2 - Имя: " << players[index].name << "\n";
				cout << "\t3 - Отчество: " << players[index].patronymic << "\n";
				cout << "\t4 - Дата рождения: " << players[index].birth.day << "." << players[index].birth.month << "." << players[index].birth.year << "\n";
				cout << "\t5 - Количество матчей: " << players[index].games << "\n";
				cout << "\t6 - Число заброшенных шайб: " << players[index].goals << "\n";
				cout << "\t7 - Количество голевых передач: " << players[index].assists << "\n";
				cout << "\t8 - Штрафных минут: " << players[index].banMins << "\n";
				cout << "\t0 - Назад\n\n";

				cout << "Что вы хотите изменить?\n";
				int choice;
				choice = inNum(0, 8);
				bool glag;
				switch (choice)
				{
				case 0:
					blag = false;

					break;
				case 1:
					glag = true;
					while (glag)
					{
						cout << "\nНовая фамилия: ";
						players[index].surname = checkNSP(glag);
					}

					break;
				case 2:
					glag = true;
					while (glag)
					{
						cout << "\nНовое имя: ";
						players[index].name = checkNSP(glag);
					}
					break;
				case 3:
					glag = true;
					while (glag)
					{
						cout << "\nНовое отчество: ";
						players[index].patronymic = checkNSP(glag);
					}

					break;
				case 4:
					cout << "\nНовая дата рождения:\n";

					cout << "День(1-31) ";
					players[index].birth.day = inNum(1, 31);

					cout << "Месяц(1-12) ";
					players[index].birth.month = inNum(1, 12);

					cout << "Год(1922-2004) ";
					players[index].birth.year = inNum(1922, 2022);

					break;
				case 5:
					cout << "\nНовое количество матчей:\n";
					while (true)
					{
						players[index].games = inNum(-999999, 999999);
						if (players[index].games >= 0)
							break;
						else
							cout << "Количество не может быть отрицательным!";
					}

					break;
				case 6:
					cout << "\nНовое количество голов:\n";
					while (true)
					{
						players[index].goals = inNum(-999999, 999999);
						if (players[index].goals >= 0)
							break;
						else
							cout << "Количество не может быть отрицательным!";
					}

					break;
				case 7:
					cout << "\nНовое количество голевых передач:\n";
					while (true)
					{
						players[index].assists = inNum(-999999, 999999);
						if (players[index].assists >= 0)
							break;
						else
							cout << "Количество не может быть отрицательным!";
					}

					break;
				case 8:
					cout << "\nНовое количество штрафных минут:\n";
					while (true)
					{
						players[index].banMins = inNum(-999999, 999999);
						if (players[index].banMins >= 0)
							break;
						else
							cout << "Количество не может быть отрицательным!";
					}

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

	cout << "\t\t\t\t-----  Индивидуальное задание  -----\n\n";

	cout << "| № |   Фамилия   |     Имя    |    Отчество   |  Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |" << "\n";
	palochki(101);
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
		sortGoals(players);
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

	writeFilePlayers(players);
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

	writeFilePlayers(players);
}
void sortGoals(vector<Person>& players)
{
	for (int i = 0; i < players.size() - 1; i++)
	{
		for (int j = i + 1; j < players.size(); j++)
		{
			if (players[j].goals > players[i].goals)
				swap(players[j], players[i]);
		}
	}

	writeFilePlayers(players);
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

		cout << "\t\t-----  Поиск по параметрам -----\n\n";

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
	
	while (flag)
	{
		system("cls");
		cout << "<--Поиск по параметрам\n\n";
		cout << "\t-----  Поиск по фамилии  -----\n\n";

		cout << "Чтобы вернуться введите \"exit\"\n\n";

		string surname;
		bool blag = true;
		while (blag)
		{
			cout << "Введите фамилию игрока: ";
			surname = checkNSP(blag);
		}

		if (surname == "exit")
			flag = false;
		else
		{
			int k = surname.length();


			system("cls");
			cout << "<--Поиск по параметрам\n\n";

			cout << "\t\t\t\t\t-----  Список игроков  -----\n\n";

			int n = 0;
			bool match = false;

			cout << "| № |   Фамилия   |     Имя    |    Отчество   |  Дата рожд. | Матчи | Голы | Гол. пер. | Штр. мин. |\n";
			palochki(101);

			for (int i = 0; i < players.size(); i++)
			{
				for (int j = 0; j < k; j++)
				{
					if (players[i].surname[j] == surname[j] || players[i].surname[j] == surname[j] + 32 || players[i].surname[j] == surname[j] - 32)
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
		}
	}
}
void searchGoals(vector<Person>& players)
{
	bool flag = true;
	while (flag)
	{
		system("cls");

		cout << "<--Поиск по параметрам\n\n";
		cout << "\t-----  Поиск по количеству забитых голов  -----\n\n";

		cout << "Чтобы вернуться введите \"exit\"\n";

		int goals;
		cout << "Введите количество голов:\n";

		string vvod;
		cout << ">> ";
		cin >> vvod;

		if (vvod == "exit")
		{
			flag = false;
		}
		else if (checkForNum(vvod) == true)
		{
			int goals = stoi(vvod);

			system("cls");
			cout << "<--Поиск по параметрам\n\n";

			cout << "\t\t\t\t\t-----  Список игроков  -----\n\n";

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
}
void searchMatches(vector<Person>& players)
{
	bool flag = true;
	while (flag)
	{
		system("cls");

		cout << "<--Поиск по параметрам\n\n";
		cout << "\t-----  Поиск по количеству матчей  -----\n\n";

		cout << "Для отмены введите \"exit\"\n";
		cout << "Введите количество матчей:\n";

		string vvod;
		cout << ">> ";
		cin >> vvod;

		if (vvod == "exit")
		{
			flag = false;
		}
		else if (checkForNum(vvod) == true)
		{
			int games = stoi(vvod);

			system("cls");
			cout << "<--Поиск по параметрам\n\n";

			cout << "\t\t\t\t\t-----  Список игроков  -----\n\n";

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

		}
	}
}
