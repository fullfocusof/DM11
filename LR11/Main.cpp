#include "WGInterraction.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_BACKSPACE 8

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleTitle(L"Графы");
	ConsoleCursorVisible(false, 100);

	WGInterraction WGI;

	int active_menu = 0;
	int keyInput;
	bool exitProg = false;

	while (!exitProg)
	{
		int x = 40, y = 12;
		GoToXY(x, y);

		vector<string> menu =
		{
			"Считать граф из файла",
			"Вывести граф на экран",
			"Кратчайший путь (Дейкстра)",
			"Кратчайший путь (Флойд)",
			"Кратчайший путь (Форд-Беллман)",
			"Выход"
		};

		for (int i = 0; i < menu.size(); i++)
		{
			if (i == active_menu)
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			GoToXY(x, y++);
			cout << menu[i] << endl;
		}

		keyInput = _getch();
		switch (keyInput)
		{
			case KEY_ESC:
				exit(0);

			case KEY_UP:
			{
				if (active_menu > 0)
				{
					active_menu--;
				}
			}
			break;

			case KEY_DOWN:
			{
				if (active_menu < menu.size() - 1)
				{
					active_menu++;
				}
			}
			break;

			case KEY_ENTER:
			{
				switch (active_menu)
				{
					case 0:
					{
						system("cls");

						WGI.Read_g();

						WGI.printQuit();
					}
					break;

					case 1:
					{
						system("cls");
						if (WGI.adjacencyM.empty())
						{
							cout << "Данные отсутствуют";
						}
						else
						{
							WGI.Print_g();
						}
						WGI.printQuit();
					}
					break;

					case 2:
					{
						system("cls");

						if (!WGI.adjacencyM.empty())
						{
							int start, end, sw;
							cout << "Введите начальную вершину - ";
							cin >> start;
							cout << "Введите конечную вершину - ";
							cin >> end;

							vector<int> shortPath = WGI.DijkstraShortPath(start, end, sw);

							system("cls");
							if (sw == INT_MAX)
							{
								cout << "Путь между вершинами " << start << " и " << end << " отсутствует";
							}
							else
							{
								cout << "Кратчайший путь из вершины " << start << " в вершину " << end << " равен " << sw << endl;
								for (auto el : shortPath)
								{
									cout << el << " ";
								}
							}
						}
						else
						{
							cout << "Данные о графе отсутствуют";
						}
			
						WGI.printQuit();
					}
					break;

					case 3:
					{
						system("cls");

						if (!WGI.adjacencyM.empty())
						{
							int start, end, sw;
							cout << "Введите начальную вершину - ";
							cin >> start;
							cout << "Введите конечную вершину - ";
							cin >> end;

							vector<vector<int>> matrix;
							vector<int> shortPath = WGI.FloydShortPath(start, end, sw, matrix);

							system("cls");
							if (sw == INT_MAX)
							{
								cout << "Путь между вершинами " << start << " и " << end << " отсутствует";
							}
							else
							{
								cout << "Кратчайший путь из вершины " << start << " в вершину " << end << " равен " << sw << endl;
								for (auto el : shortPath)
								{
									cout << el << " ";
								}
								cout << endl << endl;

								cout << "Матрица кратчайших путей" << endl;
								for (int i = 1; i <= WGI.verts; i++)
								{
									for (int j = 1; j <= WGI.verts; j++)
									{
										if (i == j)
										{
											cout << 0 << "\t";
										}
										else if (matrix[i][j] == INT_MAX)
										{
											cout << "INF" << "\t";
										}
										else
										{
											cout << matrix[i][j] << "\t";
										}
									}
									cout << endl;
								}
							}
						}
						else
						{
							cout << "Данные о графе отсутствуют";
						}

						WGI.printQuit();
					}
					break;

					case 4:
					{
						system("cls");

						if (!WGI.adjacencyM.empty())
						{
							int start, end, sw;
							cout << "Введите начальную вершину - ";
							cin >> start;
							cout << "Введите конечную вершину - ";
							cin >> end;

							try
							{
								vector<int> shortPath = WGI.BellmanFordShortPath(start, end, sw);

								system("cls");
								if (sw == INT_MAX)
								{
									cout << "Путь между вершинами " << start << " и " << end << " отсутствует";
								}
								else
								{
									cout << "Кратчайший путь из вершины " << start << " в вершину " << end << " равен " << sw << endl;
									for (auto el : shortPath)
									{
										cout << el << " ";
									}
									cout << endl << endl;
								}
							}
							catch (const exception&)
							{
								cout << "Граф содержит отрицательный цикл" << endl;
							}	
						}
						else
						{
							cout << "Данные о графе отсутствуют";
						}

						WGI.printQuit();
					}
					break;

					case 5:
					{
						system("cls");
						exitProg = true;
					}
					break;

				}
			}
			break;
		}
	}
}