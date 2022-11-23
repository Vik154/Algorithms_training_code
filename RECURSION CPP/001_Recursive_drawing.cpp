#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;


class Paint {
public:
	int **map;							// Карта (двумерный массив координат)
	int w, h;							// Размеры окна, 100х100 и т.п.
	//string symbol = " #+ox";			// Отображение на экране куда идёт рекурсия
	string symbol = "<>^|x#";			// Отображение на экране куда идёт рекурсия

	Paint(int w, int h) {				// Конструктор
		this->w = w;					// Ширина окна
		this->h = h;					// Высота окна
		map = new int* [w];				// Массив динамический для хранения координат х:у
		for (int i = 0; i < w; ++i)		// Выделение памяти для вложенных ячеек
			map[i] = new int[h];		// стобцы w заполняются строками h [0,0,0,0,0]
		for (int i = 0; i < w; ++i)		// Заполнение ячеек массива нулями [0,0,0,0,0]
			for (int j = 0; j < h; ++j)
				map[i][j] = 0;
	}
	// Установка значения number в массив, контроль уже пройденного места
	void set_map(int x, int y, int number) {
		map[x][y] = number;				// В ячейку x:y присваивается 2 если уже посещали её {0,0,0,0} 
		print_at(x, y);					// Вывод на экран                                    {0,0,2,0}
	}
	// GetStdHandle возвращает объект - окно консоли, необходимо для работы с курсором и его координатами
	HANDLE std_out = GetStdHandle(STD_OUTPUT_HANDLE);

	void print_at(int x, int y) {						// Вывод на экран 
		short cx = static_cast<short>(x);				// Привидение типа int к типу short для краткой передачи в setcons
		short cy = static_cast<short>(y);				// Для функции setconsole, т.к. принимает short
		SetConsoleCursorPosition(std_out, { cx, cy });	// Установить позицию курсора в координату х и у		
		if (symbol[map[x][y]] == '#') {
			SetConsoleTextAttribute(std_out, FOREGROUND_BLUE);
			cout << symbol[map[x][y]];
		}// Отобразить на экране уже проиденный путь
		if (symbol[map[x][y]] == '<' || symbol[map[x][y]] == '>' ||
			symbol[map[x][y]] == '^' ||	symbol[map[x][y]] == '|') {
			SetConsoleTextAttribute(std_out, FOREGROUND_RED);
			cout << symbol[map[x][y]];
		}
		if (symbol[map[x][y]] == 'x') {
			SetConsoleTextAttribute(std_out, FOREGROUND_GREEN);
			cout << symbol[map[x][y]];
		}
	}
	bool empty(int x, int y) {					// Проверка на выход за диапозон окна, т.к. будет падать с ошибкой памяти
		if (x < 0 || x >= w) return false;		// Если значения координат х или у окажуться больше или меньше размера окна
		if (y < 0 || y >= h) return false;		// В таком случае вернуть false
		return map[x][y] == 0;					// Если посещали ячейку и там записано 2 или 4 тогда вернуть false
	}
	void random_console(int count) {			// Рандомное заполнение окна преградами
		int i;
		for (i = 0; i < count; i++)				// От 0 до переданного кол-ва преград
			set_map(rand() % w, rand() % h, 5); // Рандомно заполнять поля шарпами # - в строке symbol это 1ый элемент
		/*
		for (i = 0; i < w; ++i)					// Если получиться так, что при вызове метода fill, переданные координаты
			if (map[i][i] == 0)					// окажуться на позиции # скрипт закончит работу, можно просто поменять
				return i;						// значения координат при передаче в fill --> fill(2, 5) на fill(4, 6)
		if (i == w)
			random_console(count / 2);
		*/
	}
	void fill(int x, int y) {					// Рекурсивное заполнение окошка
		if (!empty(x, y))						// Проверка валидности координат x и y
			return;								// Если не вышли за заданный диапозон окна - выполнять логику
		Sleep(30);								// Задержка небольшая, чтобы залипать в работу рекурсии
		set_map(x, y, 0);	fill(x - 1, y);		// set - установка направления рекурсии, fill - рекурсивный обход
		set_map(x, y, 1);	fill(x + 1, y);
		set_map(x, y, 2);	fill(x, y - 1);
		set_map(x, y, 3);   fill(x, y + 1);
		set_map(x, y, 4);
	}
};


int main() {
	Paint recurcive_drow(50, 25);			// Ширина окна 50х25
	recurcive_drow.random_console(200);		// Рандомные препядствия на пути
	recurcive_drow.fill(3,5);				// Заполнение рекурсивное. Если не началось, значит курсор попал на границу 
	cout << "\n\n\n";						// Надо в fill(x,y) поменять значения fill(6, 12) --> fill(3, 5) и тому подобноее
}