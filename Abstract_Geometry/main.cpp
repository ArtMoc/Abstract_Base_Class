#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

namespace Geometry
{
	enum Color
	{
		console_gray = 0x88,  //0x88 - 16-тиричный код цвета
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_white = 0xFF,
		console_default = 0x07,

		red = 0x000000FF,
		green = 0x0000FF00,
		darkgreen = 0x0000AA00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF

	};
	//enum - перечисление. Перечисление - набор именованных констант типа int.

	const char* console_color[] =
	{
		"08",
		"19",
		"2A",
		"4C",
		"7F"
	};

	class Shape
	{
	protected:
		Color color;
		unsigned int width; //ширина линии
		//Начальные координаты для рисования фигуры
		unsigned int start_x;
		unsigned int start_y;
	public:
		unsigned int get_width()const
		{
			return width;
		}
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		void set_width(unsigned int width)
		{
			if (width > 20)width = 20;
			this->width = width;
		}
		void set_start_x(unsigned int start_x)
		{
			if (start_x > 1000)start_x = 1000;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y > 700)start_y = 700;
			this->start_y = start_y;
		}
		Shape(Color color, unsigned int width = 5,
			unsigned int star_x = 100,
			unsigned int strat_y = 100) : color(color)
		{
			set_width(width);
			set_start_x(start_x);
			set_start_y(start_y);
			cout << "Sh_Constructor:\t" << this << endl;
		}
		virtual ~Shape()
		{
			cout << "Sh_Destructor:\t" << this << endl;
		}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side <= 0)side = 1;
			this->side = side;
		}
		Square(double side, Color color, unsigned int width = 5,
			unsigned int star_x = 100,
			unsigned int strat_y = 100) :Shape(color, width, start_x, start_y)
		{
			set_side(side);
		}
		~Square()
		{

		}

		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			//std::string command = std::string("color ") + console_color[color];
			//cout << command << endl;
			//system(command.c_str());

			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
	};

	class Rectangle :public Shape
	{
		double side1;
		double side2;
	public:
		double get_side1()const
		{
			return side1;
		}
		double get_side2()const
		{
			return side2;
		}
		void set_side1(double side1)
		{
			if (side1 <= 0)side1 = 1;
			this->side1 = side1;
		}
		void set_side2(double side2)
		{
			if (side2 <= 0)side2 = 2;
			this->side2 = side2;
		}
		Rectangle(double side1, double side2, Color color, unsigned int width = 5,
			unsigned int star_x = 100,
			unsigned int strat_y = 100) :Shape(color, width, start_x, start_y)
		{
			set_side1(side1);
			set_side2(side2);
		}
		~Rectangle()
		{

		}
		double get_area()const
		{
			return side1 * side2;
		}
		double get_perimeter()const
		{
			return(side1 + side2) * 2;
		}
		void draw()const
		{
			//1) получаем окно консоли
			HWND hwnd = GetConsoleWindow();
			//HWND hwnd = FindWindow(NULL, L"Abstract_Base_Class - Microsoft Visual Studio");
			//2) создаем контекст устройства полученного окна
			HDC hdc = GetDC(hwnd);
			//3) создаем карандаш
			HPEN hpen = CreatePen(PS_SOLID, 5, color);//PS_SOLID -сплошная линия, 5 - толщина(писк)
			//4) прежде, чем рисовать, нужно выбрать чем и на чем рисовать
			SelectObject(hdc, hpen);

			//5) чтобы фигура была закрашена, нужно создать и применить кисть
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, start_x, start_y, start_x + side2, start_y + side1);

			DeleteObject(hBrush);
			//?) удаляем карандаш
			DeleteObject(hpen);
			//?) все контексты устройств нужно удалят, чтобы освободить занимаемые ими ресурсы
			ReleaseDC(hwnd, hdc);
		}
	};
	
	class Circle :public Shape
	{
		double radius;
		CONST double PI = 3.14;
	public:
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			if (radius <= 0)radius = 1;
			this->radius = radius;
		}
		Circle(double radius, Color color, unsigned int width = 5, 
			unsigned int start_x = 100, 
			unsigned int start_y = 100) :Shape(color, width, start_x, start_y)
		{
			set_radius(radius);
		}
		~Circle()
		{

		}

		double get_area()const
		{
			return PI * pow(radius, 2);
		}
		double get_perimeter()const
		{
			return 2 * PI * radius;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hpen = CreatePen(PS_SOLID, 5, color);
			SelectObject(hdc, hpen);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);
			DeleteObject(hBrush);
			DeleteObject(hpen);
			ReleaseDC(hwnd, hdc);
		}
	};

}

void main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 80, 50 };
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN, &buffer);
	system("pause");

	setlocale(LC_ALL, "");

	/*Geometry::Square square(5, Geometry::Color::console_red);
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/

	/*Geometry::Rectangle rect(100, 200, Geometry::Color::yellow, 5, 200, 100);
	rect.draw();*/

	Geometry::Circle ellip(150, Geometry::Color::green, 5, 200, 100);
	cout << "Area of circle: " << ellip.get_area() << endl;
	cout << "Perimeter of circle: " << ellip.get_perimeter() << endl;
	ellip.draw();
	Geometry::Circle ellip1(100, Geometry::Color::blue, 5, 200, 100);
	ellip1.draw();
	Geometry::Circle ellip2(70, Geometry::Color::yellow, 5, 200, 100);
	ellip2.draw();
	Geometry::Circle ellip3(50, Geometry::Color::red, 5, 200, 100);
	ellip3.draw();
}