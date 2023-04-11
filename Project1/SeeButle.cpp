
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

char Player[10][10];
char maskPlayer[11][11];
char Comp[10][10];
char maskComp[11][11];
int mark;
int Ycomp = 0, Xcomp = 0;
int flagII = 0;
int markVorH = 0;
bool markLoR = false;
bool markUoL;
bool markShot = false;

void clearField(char mass[10][10]) {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			mass[i][j] = 46;
		}
	}
}

void fieldPlayer(char iPlayer[10][10]) {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (iPlayer[i][j] != 'O' && iPlayer[i][j] != '-' && iPlayer[i][j] != 'X' && iPlayer[i][j] != '*')
				iPlayer[i][j] = 46;
		}
	}
}

void fieldComp(char iComp[10][10]) {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (iComp[i][j] != 'O' && iComp[i][j] != '-' && iComp[i][j] != 'X' && iComp[i][j] != '*' && iComp[i][j] != '+')
				iComp[i][j] = 46;
		}
	}
}

void copyMassPlayer(char iPlayer[10][10], char imaskPlayer[11][11]) {
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			if (iPlayer[i - 1][j - 1] == '-')
				imaskPlayer[i][j] = 46;
			else
				imaskPlayer[i][j] = iPlayer[i - 1][j - 1];
		}
	}
}

void copyMassComp(char iComp[10][10], char imaskComp[11][11]) {
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			if ((iComp[i - 1][j - 1] == '-') || (iComp[i - 1][j - 1] == 'O'))
				imaskComp[i][j] = 46;
			else
				imaskComp[i][j] = iComp[i - 1][j - 1];
		}
	}
}

void maskFieldPlayer(char mass[11][11]) {
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (j == 0 && i != 0)
			{
				mass[i][j] = 65 + i - 1;
			}
			if (i == 0 && j != 0) {
				mass[i][j] = j + 47;
			}
			else {
				mass[0][0] = 32;
				copyMassPlayer(Player, mass);
			}

		}

	}
}

void maskFieldComp(char mass[11][11]) {
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (j == 0 && i != 0)
			{
				mass[i][j] = 65 + i - 1;
			}
			if (i == 0 && j != 0) {
				mass[i][j] = j + 47;
			}
			else {
				mass[0][0] = 32;
				copyMassComp(Comp, mass);
			}
		}
	}
}

void showField(char mass1[11][11], char mass2[11][11]) {
	cout << "Поле Игрока\t\t\tПоле Компьютера\n\n";
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (i == 0 && j == 0)
				cout << setw(2);
			if (i != 0 && j == 0)
				cout << mass1[i][j] << setw(3);
			else if (i == 0 && j != 0) {
				cout << " " << mass1[i][j];
			}
			else {
				cout << " " << mass1[i][j];
			}
		}
		cout << "\t\t";
		for (int j = 0; j < 11; j++) {
			if (i == 0 && j == 0)
				cout << setw(2);
			if (i != 0 && j == 0)
				cout << mass2[i][j] << setw(3);
			else if (i == 0 && j != 0) {
				cout << " " << mass2[i][j];
			}
			else {
				cout << " " << mass2[i][j];
			}
		}
		cout << endl;
	}
}

void FoolFieldPlayer(char iPlayer[10][10]) {
	fieldPlayer(iPlayer);
	maskFieldPlayer(maskPlayer);
}

void FoolFieldComp(char iComp[10][10]) {
	fieldComp(iComp);
	maskFieldComp(maskComp);
}

int buildShips(char mass[10][10], int deck) {
	bool VertorHor = 0;
	int x, y;
	char yy;
	int cntShips2 = 0;
	do
	{
	tryagain:
		system("cls");
		FoolFieldPlayer(Player);
		FoolFieldComp(Comp);
		showField(maskPlayer, maskComp);
		if (deck > 1) {
			cout << "\nКак корабль будет распологаться?\n" << "0 - горизонтально\n1 - вертикально\n";
			cin >> VertorHor;
		}
		cout << "\nВведите координаты начала корабля (например C 4)\n";
		cin >> yy >> x;
		y = yy - 'A';
		if (!VertorHor) {
			for (int i = x; i < x + deck; i++) {
				if (mass[y][i] == '-' || mass[y][i] == 'O') {
					cout << "\nКорабль столкнётся с другим вашим кораблём!\nПовторите ввод\n\n";
					goto tryagain;
				}
			}
			if (y < 0 || y>10 || x < 0 || (x + deck)>10)
			{
				cout << "\nКорабль выходит за пределы игрового поля!\nПовторите ввод.\n";
				system("pause");
				goto tryagain;
			}
			else {
				for (int i = 0; i < deck; i++)
				{
					mass[y][x] = 'O';
					x++;
				}
				for (int i = y - 1; i <= y + 1; i++)
				{
					for (int j = x - 1 - deck; j < x + 1; j++)
					{
						if (mass[i][j] != 'O')
							if (i >= 0 && i < 10 && j >= 0 && j < 10)
								mass[i][j] = '-';
					}
				}
				/*cout << endl << endl;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						cout << " " << Player[i][j];
					}
					cout << endl;
				}*/

			}
		}
		else {
			for (int i = y; i < y + deck; i++) {
				if (mass[i][x] == '-' || mass[i][x] == 'O') {
					cout << "\nКорабль столкнётся с другим вашим кораблём!\n\n";
					goto tryagain;
				}
			}
			if (y < 0 || (y + deck)>10 || x < 0 || x>10)
			{
				cout << "\nКорабль выходит за пределы игрового поля\n\n";
				goto tryagain;
			}
			else {
				for (int i = 0; i < deck; i++)
				{
					mass[y][x] = 'O';
					y++;
				}
				for (int i = y - 1 - deck; i < y + 1; i++)
				{
					for (int j = x - 1; j <= x + 1; j++)
					{
						if (mass[i][j] != 'O')
							if (i >= 0 && i < 10 && j >= 0 && j < 10)
								mass[i][j] = '-';
					}
				}

				//	cout << endl << endl;
				//for (int i = 0; i < 10; i++)
				//{
				//	for (int j = 0; j < 10; j++)
				//	{
				//		cout << " " << Player[i][j];
				//	}
				//	cout << endl;
				//}
			}
		}
		system("cls");
		cntShips2++;
	} while ((5 - deck) > cntShips2);
	return cntShips2;
}

void PlaceShipsPlayer(char mass[10][10]) {
	system("cls");
	int deck_1 = 0, deck_2 = 0, deck_3 = 0, deck_4 = 0;
	int cntShips = 0;
	int Ships;
	cout << "Вам необходимо расставить следущие корабли:\n" << "1 - четыре однопалубных\n" << "2 - три двухпалубных\n" << "3 - два трёхпалубных\n" << "4 - один четырёхпалубный\n\n";
	do
	{
		FoolFieldPlayer(Player);
		FoolFieldComp(Comp);
		showField(maskPlayer, maskComp);
		if ((deck_1 == 0 || deck_2 == 0 || deck_3 == 0 || deck_4 == 0) && cntShips != 0) {
			cout << "\nВам еще необходимо расставить следующие корабли:\n";
			if (deck_1 == 0)
				cout << "1 - четыре однопалубных\n";
			if (deck_2 == 0)
				cout << "2 - три двухпалубных\n";
			if (deck_3 == 0)
				cout << "3 - два трёхпалубных\n";
			if (deck_4 == 0)
				cout << "4 - один четырёхпалубный\n";
		}
		cout << "\nКакие корабли будем расставлять? -> ";
		cin >> Ships;
		switch (Ships)
		{
		case 1:
			system("cls");
			if (deck_1 == 4) {
				cout << "Вы уже построили эти корабли!\n\n";
				break;
			}
			else {
				cout << "Однопалубный корабль\n\n";
				deck_1 = buildShips(mass, Ships);
				cntShips = cntShips + deck_1;
				/*cout << endl << endl;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						cout << " " << Player[i][j];
					}
					cout << endl;
				}*/
			}
			break;

		case 2:
			system("cls");
			if (deck_2 == 3) {
				cout << "Вы уже построили эти корабли!\n\n";
				break;
			}
			else {
				cout << "Двухпалубный корабль\n\n";
				deck_2 = buildShips(mass, Ships);
				cntShips += deck_2;
			}
			break;
		case 3:
			system("cls");
			if (deck_3 == 2) {
				cout << "Вы уже построили эти корабли!\n\n";
				break;
			}
			else {
				cout << "Трёхпалубный корабль\n\n";
				deck_3 = buildShips(mass, Ships);
				cntShips += deck_3;
			}
			break;
		case 4:
			system("cls");
			if (deck_4 == 1) {
				cout << "Вы уже построили эти корабли!\n\n";
				break;
			}
			else {
				cout << "Четырёхпалубный корабль\n\n";
				deck_4 = buildShips(mass, Ships);
				cntShips += deck_4;
			}
			break;
		default:
			cout << "Нет таких кораблей в этой игре!\n\n";
			break;
		}
	} while (cntShips < 10);

}

int buildShipsComp(char mass[10][10], int deck) {
	int VertorHor;
	int x, y;
	int cntShips2 = 0;
	do
	{
		VertorHor = rand() % 2;
	tryagain:
		y = rand() % 10;
		x = rand() % 10;
		if (VertorHor == 0) {
			for (int i = x; i < x + deck; i++) {
				if (mass[y][i] == '-' || mass[y][i] == 'O') {
					goto tryagain;
				}
			}
			if (y < 0 || y>10 || x < 0 || (x + deck)>10)
			{
				goto tryagain;
			}
			else {
				for (int i = 0; i < deck; i++)
				{
					mass[y][x] = 'O';
					x++;
				}
				for (int i = y - 1; i <= y + 1; i++)
				{
					for (int j = x - 1 - deck; j < x + 1; j++)
					{
						if (mass[i][j] != 'O')
							if (i >= 0 && i < 10 && j >= 0 && j < 10)
								mass[i][j] = '-';
					}
				}
				//cout << endl << endl;
				//for (int i = 0; i < 10; i++)
				//{
				//	for (int j = 0; j < 10; j++)
				//	{
				//		cout << " " << Player[i][j];
				//	}
				//	cout << endl;
				//}

			}
		}
		else {
			for (int i = y; i < y + deck; i++) {
				if (mass[i][x] == '-' || mass[i][x] == 'O') {
					goto tryagain;
				}
			}
			if (y < 0 || (y + deck)>10 || x < 0 || x>10)
			{
				goto tryagain;
			}
			else {
				for (int i = 0; i < deck; i++)
				{
					mass[y][x] = 'O';
					y++;
				}
				for (int i = y - 1 - deck; i < y + 1; i++)
				{
					for (int j = x - 1; j <= x + 1; j++)
					{
						if (mass[i][j] != 'O')
							if (i >= 0 && i < 10 && j >= 0 && j < 10)
								mass[i][j] = '-';
					}
				}

			}
		}
		cntShips2++;
	} while ((5 - deck) > cntShips2);
	return cntShips2;
}

void placeShipsComp(char mass[10][10]) {
	system("cls");
	int cntShips = 0;
	int Ships = 4;
	cout << "Необходимо расставить следущие корабли:\n" << "1 - четыре однопалубных\n" << "2 - три двухпалубных\n" << "3 - два трёхпалубных\n" << "4 - один четырёхпалубный\n\n";
	system("pause");
	cout << "\n\tКомпьютер расставляет корабли...";
	Sleep(1500);
	do
	{
		switch (Ships)
		{
		case 1:
			cntShips = cntShips + buildShipsComp(mass, Ships);
			break;
		case 2:
			cntShips = cntShips + buildShipsComp(mass, Ships);
			Ships--;
			break;
		case 3:
			cntShips = cntShips + buildShipsComp(mass, Ships);
			Ships--;
			break;
		case 4:
			cntShips = cntShips + buildShipsComp(mass, Ships);
			Ships--;
			break;
		default:
			cout << "Нет таких кораблей в этой игре!\n\n";
			break;
		}
	} while (cntShips < 10);
}

bool chekField(char mass[10][10]) {
	int cnt = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (mass[i][j] == 'O')
				cnt++;
		}
	}
	if (cnt > 0)
		return true;
	else
		return false;
}


bool checkShip(char mass[10][10], int a, int b) {
	int cnt = 0;
	for (int i = b; i >= 0; i--)
	{
		if (mass[a][i] == 'O')
			cnt++;
		if (mass[a][i] == '-' || mass[a][i] == '*')
			break;
	};
	for (int i = b; i < 10; i++)
	{
		if (mass[a][i] == 'O')
			cnt++;
		if (mass[a][i] == '-' || mass[a][i] == '*')
			break;
	};
	for (int i = a; i >= 0; i--)
	{
		if (mass[i][b] == 'O')
			cnt++;
		if (mass[i][b] == '-' || mass[i][b] == '*')
			break;
	}
	for (int i = a; i < 10; i++)
	{
		if (mass[i][b] == 'O')
			cnt++;
		if (mass[i][b] == '-' || mass[i][b] == '*')
			break;
	}
	if (cnt == 0)
		return true;
	else
	{
		return false;
	}
}

void drawShip(char mass[10][10], int a, int b) {
	int Left = 0, Right = 9, Up = 0, Law = 9;
	int DeckH, DeckV;
	for (int i = b; i >= 0; i--)
	{
		if (mass[a][i] == '-' || mass[a][i] == '*' || mass[a][i] == '+') {
			Left = i;
			break;
		}
	};
	for (int i = b; i < 10; i++)
	{
		if (mass[a][i] == '-' || mass[a][i] == '*' || mass[a][i] == '+') {
			Right = i;
			break;
		}
	};
	for (int i = a; i >= 0; i--)
	{
		if (mass[i][b] == '-' || mass[i][b] == '*' || mass[a][i] == '+') {
			Up = i;
			break;
		}
	}
	for (int i = a; i < 10; i++)
	{
		if (mass[i][b] == '-' || mass[i][b] == '*' || mass[a][i] == '+') {
			Law = i;
			break;
		}
	}
	DeckH = Right - Left - 1;
	DeckV = Law - Up - 1;
	if (DeckH == DeckV || DeckH > DeckV) {// ГОРИЗОНТАЛЬНЫЙ
		for (int i = a - 1; i <= a + 1; i++)
		{
			for (int j = Left; j <= Right; j++)
			{
				if (mass[i][j] != 'X')
					if (i >= 0 && i < 10 && j >= 0 && j < 10)
						mass[i][j] = '+';
			}
		}
	}
	if (DeckV > DeckH) {// ВЕРТИКАЛЬНЫЙ
		for (int i = Up; i <= Law + 1; i++)
		{
			for (int j = b - 1; j <= b + 1; j++)
			{
				if (mass[i][j] != 'X')
					if (i >= 0 && i < 10 && j >= 0 && j < 10)
						mass[i][j] = '+';
			}
		}
	}


}

void shot(int& a, int& b) {
	char yy;
	int flag;
	do
	{
		flag = 0;
		cin >> yy >> b;
		a = yy - 'A';
		if (a < 0 || a>9 || b < 0 || b>9)
		{
			cout << "\t\nВы ввели координаты вне игрового поля!\n\nПовторите ввод!\n";
			flag++;
		}
	} while (flag == 1);
}

void artInt(char mass[10][10], int& y, int& x) {
	int y1, x1;
	y1 = Ycomp;
	x1 = Xcomp;
	if (markVorH == 0) {
		int n = rand() % 4;
		if (n == 0) { //влево
			y = y1;
			x = x1 - 1;
		}
		if (n == 1) { //вправо
			y = y1;
			x = x1 + 1;
		}
		if (n == 2) { //вверх
			y = y1 - 1;
			x = x1;
		}
		if (n == 3) { //вниз
			y = y1 + 1;
			x = x1;
		}
	}
	if (markVorH == 1) {
		//int n = rand() % 2;
/*		if (n == 0) { */

//вверх
		if (!markShot) {
			x = x1;
			for (int i = y1; i > 0; i--)
			{
				if (mass[i][x] != 'X') {
					y = i;
					break;
				}
			}
		}
		//вниз
		else {
			x = x1;
			for (int i = y1; i <= 10; i++)
			{
				if (mass[i][x] != 'X') {
					y = i;
					break;
				}
			}
		}
		/*	y = y1 - 1;*/

			/*	}*/
				//if (n == 1) { 
				//	y = y1 + 1;
				//	x = x1;
				//}
	}
	if (markVorH == 2) {
		if (!markShot) {
			/*	int n = rand() % 2;*/
				/*if (n == 0) {*/
		//влево
			y = y1;
			for (int i = x1; i > 0; i--)
			{
				if (mass[y][i] != 'X') {
					x = i;
					break;
				}
			}
			/*}*/

			//if (n == 1) { //вправо
			//	y = y1;
			//	x = x1 + 1;
			//	markLoR = true;
			//}
		}
		//вправо
		else {
			y = y1;
			for (int i = x1; i <= 10; i++)
			{
				if (mass[y][i] != 'X') {
					x = i;
					break;
				}
			}
		}
	}
}

int VorH(char mass[10][10], int& a, int& b) {
	if ((a - Ycomp) == 0 && (b - Xcomp) == 0)
		return 0;
	if ((a - Ycomp) != 0 && (b - Xcomp) == 0)
		return 1; // вертикаль
	if ((a - Ycomp) == 0 && (b - Xcomp) != 0)
		return 2;//горизонталь
}

int stepPlayer(char mass[10][10], int y, int x) {
	if (mass[y][x] == 'O') {
		mass[y][x] = 'X';
		system("cls");
		FoolFieldPlayer(Player);
		FoolFieldComp(Comp);
		showField(maskPlayer, maskComp);
		cout << "\n\tВы попали!!\n";
		if (checkShip(mass, y, x))
		{
			cout << "\n\tИ Вы потопили корабль противника!\n\n";
			drawShip(mass, y, x);
			system("pause");
		}
		if (chekField(mass) != true)
			return 3;
		cout << "\nСтреляйте ещё раз\n";
		Sleep(1500);
		return 1;
	}
	if (mass[y][x] == 'X' || mass[y][x] == '*') {
		cout << "\nВы уже стреляли сюда!\n";
		system("pause");
		return 2;
	}
	else {
		mass[y][x] = '*';
		cout << "\n\tПромах!\n";
		Sleep(1500);
		return 3;
	}
}

int stepComp(char mass[10][10]) {
	int y, x;
	if (flagII == 0) {
		y = rand() % 10;
		x = rand() % 10;
		Ycomp = y;
		Xcomp = x;
	}
	else {
		artInt(mass, y, x);
	}

	if (mass[y][x] == 'O') {
		mass[y][x] = 'X';
		system("cls");
		FoolFieldPlayer(Player);
		FoolFieldComp(Comp);
		showField(maskPlayer, maskComp);
		cout << "\n\tКомпьютер попал по вашему кораблю! \n";
		Sleep(1500);
		if (checkShip(mass, y, x))
		{
			Ycomp = 0; Xcomp = 0;
			cout << "\n\tИ потопил ваш корабль!\n\n";
			drawShip(mass, y, x);
			flagII = 0;
			system("pause");
		}
		else {
			flagII = 1;
			markShot = false;
			markVorH = VorH(mass, y, x);
			Ycomp = y;
			Xcomp = x;

		}
		if (chekField(mass) != true)
			return 3;
		//system("cls");
		//FoolFieldPlayer(Player);
		//FoolFieldComp(Comp);
		//showField(maskPlayer, maskComp);
		/*cout << "\nОгонь ведёт компьютер\n";*/
		Sleep(1300);
		return 1;
	}
	if (mass[y][x] == '*' || mass[y][x] == '+') {
		markShot = true;
		return 2;
	}
	if (mass[y][x] == 'X')
		return 2;
	else {
		mass[y][x] = '*';
		cout << "\n\tКомпьютер промахнулся!\n";
		Sleep(1500);
		return 3;
	}
}

void gamePlayer(char mass[10][10]) {
	int y, x;
	int hit;
	do
	{
		system("cls");
		FoolFieldPlayer(Player);
		FoolFieldComp(Comp);
		showField(maskPlayer, maskComp);
		cout << "\nВы стреляете (например В 6)\n";
		shot(y, x);
		hit = stepPlayer(mass, y, x);
		system("cls");
		FoolFieldPlayer(Player);
		FoolFieldComp(Comp);
		showField(maskPlayer, maskComp);
	} while (hit == 1 || hit == 2);

}

void gameComp(char mass[10][10]) {
	int hit;
	do
	{
		cout << "\nОгонь ведёт компьютер\n";
		Sleep(1000);
		hit = stepComp(mass);
		//system("cls");
		//FoolFieldPlayer(Player);
		//FoolFieldComp(Comp);
		//showField(maskPlayer, maskComp);
		//cout << endl << endl;
		//for (int i = 0; i < 10; i++)
		//{
		//	for (int j = 0; j < 10; j++)
		//	{
		//		cout << " " << Comp[i][j];
		//	}
		//	cout << endl;
		//}
	} while (hit == 1 || hit == 2);
}


void Game(char mass[10][10], char mass2[10][10]) {
	do
	{
		gamePlayer(mass2);
		if (chekField(mass2) != true)
		{
			cout << "\n\tВы выиграли!\n\n";
			system("pause");
			break;
		}
		gameComp(mass);
		if (chekField(mass) != true)
		{
			cout << "\t\nВыиграл компьтер!\n";
			break;
		}

	} while (chekField(mass) != false);
}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	int Ycomp = 0, Xcomp = 0;
	int mainMenu;
	int placeMenu;
	do
	{
		system("cls");
		cout << "Игра Морской бой\n" << "1. Расстановка кораблей\n" << "2. Игра\n" << "0. Выход\n";
		cin >> mainMenu;
		switch (mainMenu)
		{
		case 1:
			clearField(Player);
			clearField(Comp);
			system("cls");
			cout << "Кто будет расставлять корабли?\n1. Игрок\n2. Компьютер\n";
			cin >> placeMenu;
			switch (placeMenu)
			{
			case 1:
				PlaceShipsPlayer(Player);
				cout << "\nТеперь корабли расставляет компьютер\n\n";
				placeShipsComp(Comp);
				system("cls");
				break;
			case 2:
				placeShipsComp(Player);
				placeShipsComp(Comp);
				system("cls");
				break;
			default:
				cout << "Выберите верный пункт меню\n\n";
				break;
			}
			cout << "Расстановка кораблей завершена!\n\n";
			FoolFieldPlayer(Player);
			FoolFieldComp(Comp);
			showField(maskPlayer, maskComp);
			cout << endl << endl;
			system("pause");
			mark++;
			break;
		case 2:
			if (mark == 0) {
				system("cls");
				cout << "\n\tСначала необходимо расставить корабли!\n\n";
				system("pause");
				break;
			}
			system("cls");
			FoolFieldPlayer(Player);
			FoolFieldComp(Comp);
			showField(maskPlayer, maskComp);
			Game(Player, Comp);

			break;
		default:
			cout << "\t\nНеправильный пункт меню!\n\n";
			break;
		}
	} while (mainMenu != 0);
}