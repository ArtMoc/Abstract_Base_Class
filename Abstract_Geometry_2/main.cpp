#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<thread>
using std::cin;
using std::cout;
using std::endl;

namespace Geometry
{
	enum Color
	{
		console_gray = 0x88,  //0x88 - шестнадцатеричный код цвета
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_white = 0xFF,
		console_default = 0x07,

		red = 0x000000FF,
		green = 0x0000FF00,
		dark_green = 0x0000AA00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,  //1-00: альфа-канал, 2-00: blue, 3-FF: green, 4-FF: red
		white = 0x00FFFFFF


		/*console_gray,  //0x88 - шестнадцатеричный код цвета
		console_blue,
		console_green,
		console_red,
		console_white*/
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
		unsigned int width; //Ширина линии
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
		Shape
		(
			Color color, unsigned int width = 5, unsigned int start_x = 100,
			unsigned int start_y = 100
		) :color(color)
		{
			set_width(width);
			set_start_x(start_x);
			set_start_y(start_y);
			cout << "ShConstructor: " << this << endl;
		}
		virtual ~Shape()
		{
			cout << "ShDestructor: " << this << endl;
		}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		void start_draw()const
		{
			while (true)
			{
				draw();
			}
		}
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
		Square(double side, Color color, unsigned int width = 5, unsigned int start_x = 100,
			unsigned int start_y = 100) :Shape(color, width, start_x, start_y)
		{
			set_side(side);
			cout << "SqConstructor: " << this << endl;
		}
		~Square()
		{
			cout << "SqDestructor: " << this << endl;
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
			//SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|BACKGROUND_RED);
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

	class Rectangle :public Shape   //Прямоугольник
	{
		double left_side;           //Левая сторона
		double upper_side;          //Верхняя сторона
	public:
		double get_left_side()const
		{
			return left_side;
		}
		double get_upper_side()const
		{
			return upper_side;
		}
		void set_left_side(double left_side)
		{
			if (left_side <= 0)left_side = 1;
			this->left_side = left_side;
		}
		void set_upper_side(double upper_side)
		{
			if (upper_side <= 0)upper_side = 2;
			this->upper_side = upper_side;
		}
		Rectangle(double upper_side, double left_side, Color color, unsigned int width = 5, unsigned int start_x = 100,
			unsigned int start_y = 100) :Shape(color, width, start_x, start_y)
		{
			set_upper_side(upper_side);
			set_left_side(left_side);
			cout << "RecConstructor: " << this << endl;
		}
		~Rectangle()
		{
			cout << "RecDestructor: " << this << endl;
		}

		double get_area()const
		{
			return left_side * upper_side;
		}
		double get_perimeter()const
		{
			return (left_side * 2) + (upper_side * 2);
		}
		void draw()const
		{
			//1) Получаем окно консоли:
			HWND hwnd = GetConsoleWindow();
			//HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			//2) Создаём контекст устройства, полученного окна:
			HDC hdc = GetDC(hwnd);
			//3)Создаём карандаш:
			HPEN hPen = CreatePen(PS_SOLID, 5, color); //PS_SOLID - сплошная линия, 5 - толщина линии 5 пикселей
			//4)Прежде чем рисовать, нужно выбрать чем и на чём рисовать:
			SelectObject(hdc, hPen);
			//5)Чтобы фигура была закрашена орпеделённым цветом, нужно создать и применить кисть:
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, start_x, start_y, start_x + upper_side, start_y + left_side);
			DeleteObject(hBrush);
			//?)Удаляем карандаш:
			DeleteObject(hPen);
			//?) Все контексты устройств нужно удалять, чтобы освободить занимаемые ими ресурсы:
			ReleaseDC(hwnd, hdc);
			/*for (int i = 0; i < left_side; i++)
			{
				for (int j = 0; j < upper_side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}*/
		}
	};

	class Triangle :public Shape 
	{
		
	public:
		Triangle(Color color, unsigned int width, unsigned int start_x, unsigned int start_y) :Shape(color, width, start_x, start_y)
		{

		}
		~Triangle()
		{

		}
		virtual double get_height()const = 0;
	};

	class EquilateralTriangle :public Triangle  
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		double get_height()const
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		void set_side(double side)
		{
			if (side <= 0)side = 1;
			this->side = side;
		}
		EquilateralTriangle
		(
			double side, Color color = Color::white, unsigned int width = 5, unsigned int start_x = 100, unsigned int start_y = 100
		) : Triangle(color, width, start_x, start_y)
		{
			set_side(side);
		}
		double get_area()const
		{
			return side * side * sqrt(3) / 4;
		}
		double get_perimeter()const
		{
			return side * 3;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			const POINT points[] =
			{
				{start_x, start_y + this->get_height()},
				{start_x + side, start_y + this->get_height()},
				{start_x + side / 2, start_y}
			};
			::Polygon(hdc, points, sizeof(points) / sizeof(POINT));

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};

	class IsoscalesTriangle :public Triangle 
	{
		double side;            
		double bottom;           
	public:
		double get_side()const
		{
			return side;
		}
		double get_bottom()const
		{
			return bottom;
		}
		double get_height()const
		{
			return sqrt(pow(side, 2) - pow(bottom / 4, 2));
		}
		void set_side(double side)
		{
			this->side = side;
		}
		void set_bottom(double bottom)
		{
			this->bottom = bottom;
		}
		IsoscalesTriangle
		(
			double side, double bottom, Color color, unsigned int width, unsigned int start_x, unsigned int start_y
		) : Triangle(color, width, start_x, start_y)
		{
			set_side(side);
			set_bottom(bottom);
		}
		double get_area()const
		{
			return bottom / 2 * sqrt(pow(side, 2) - pow(bottom / 4, 2));
		}
		double get_perimeter()const
		{
			return 2 * side + bottom;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			const POINT points[] =
			{
				{start_x, start_y + this->get_height()},
				{start_x + this->get_bottom(), start_y + this->get_height()},
				{start_x + this->get_bottom() / 2, start_y}
			};
			::Polygon(hdc, points, sizeof(points) / sizeof(POINT));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
	};


	class Circle :public Shape             //Круг
	{
		double radius;                     //Радиус
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
		Circle(double radius, Color color, unsigned int width = 5, unsigned int start_x = 100,
			unsigned int start_y = 100) :Shape(color, width, start_x, start_y)
		{
			set_radius(radius);
			cout << "CircConstructor: " << this << endl;
		}
		~Circle()
		{
			cout << "CircDestructor: " << this << endl;
		}

		double get_area()const
		{
			return (22 / 7) * pow(radius, 2);
		}
		double get_perimeter()const
		{
			return 2 * radius * (22 / 7);
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			SelectObject(hdc, hPen);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hBrush);
			for (int i = 0; i < 25; cout << endl, i++); Sleep(200);

			::Ellipse(hdc, start_x, start_y, start_x + radius * 50, start_y + radius * 50);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};
}


//#define SQUARE
//#define RECTANGLE
#define TRIANGLE
//#define CIRCLE

void main()
{
	setlocale(LC_ALL, "");
	char key = 0;
#ifdef SQUARE
	//Shape shape
	Geometry::Square square(5, Geometry::Color::blue);
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();
	std::thread square_thread(&Geometry::Square::start_draw, square);
#endif // SQUARE
#ifdef RECTANGLE
	Geometry::Rectangle rect1(200, 100, Geometry::Color::yellow, 5, 400, 100);
	cout << "Площадь прямоугольника: " << rect1.get_area() << endl;
	cout << "Периметр прямоугольника: " << rect1.get_perimeter() << endl;
	/*while (key != ' ')
	{
		rect1.draw();
		if (_kbhit())key = _getch();
	}*/
	std::thread rect1_thread(&Geometry::Rectangle::start_draw, rect1);
#endif // RECTANGLE
#ifdef TRIANGLE
	Geometry::EquilateralTriangle et(300, Geometry::Color::green, 5, 220, 200);
	cout << "Площадь треугольника: " << et.get_area() << endl;
	cout << "Высота: " << et.get_height() << endl;
	cout << "Периметр треугольниа: " << et.get_perimeter() << endl;
	std::thread et_thread(&Geometry::EquilateralTriangle::start_draw, et);

	Geometry::IsoscalesTriangle it(200, 200, Geometry::Color::dark_green, 5, 50, 200);
	cout << "Площадь треугольника: " << it.get_area() << endl;
	cout << "Высота: " << it.get_height() << endl;
	cout << "Периметр треугольника: " << it.get_perimeter() << endl;
	std::thread it_thread(&Geometry::IsoscalesTriangle::start_draw, it);    

	
#endif // TRIANGLE
#ifdef CIRCLE
	Geometry::Circle circle(5, Geometry::Color::red);
	cout << "Площадь круга: " << circle.get_area() << endl;
	cout << "Периметр круга: " << circle.get_perimeter() << endl;
	circle.draw();
	std::thread circle_thread(&Geometry::Circle::start_draw, circle);

#endif // CIRCLE
	//cin.get();
	//square_thread.join();
	//rect1_thread.join();
	et_thread.join();
	it_thread.join();                    
	//circle_thread.join();
}