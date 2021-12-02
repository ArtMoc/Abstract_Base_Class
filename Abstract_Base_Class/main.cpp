#include <iostream>
using namespace std;

class Vehicle
{
	int speed;
public:
	virtual void move() = 0; //pure virtual function
	//именно этот метод и делает класс абстрактным
};

class Ground_Vehicle :public Vehicle
{

};

class Water_Vehicle :public Vehicle
{
	//абстрактный класс
};

class Air_Vehicle :public Vehicle
{
	int height; //абстрактный класс
};

class Bike :public Ground_Vehicle
{
	//Конкретный класс, поскольку он определяет чисто виртуальный метод move
public:
	void move()
	{
		cout << "Мотоцикл едет на двух колесах" << endl;
	}
};

class Car :public Ground_Vehicle
{
public:
	void move()
	{
		cout << "Машина едет на четырех колесах" << endl;
	}
};

class Boat :public Water_Vehicle
{
public:
	void move()
	{
		cout << "Лодка плывет по воде" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
//	Vehicle v; //невозможно создать экземпляр абстрактного класса
//	Ground_Vehicle gv; этот класс также является абстрактным поскольку не определяет
	                   //метод move
	Bike HD;
	HD.move();
	Car bmw;
	bmw.move();
	Boat boat;
	boat.move();
}