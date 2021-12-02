#include <iostream>
using namespace std;

class Vehicle
{
	int speed;
public:
	virtual void move() = 0; //pure virtual function
	//������ ���� ����� � ������ ����� �����������
};

class Ground_Vehicle :public Vehicle
{

};

class Water_Vehicle :public Vehicle
{
	//����������� �����
};

class Air_Vehicle :public Vehicle
{
	int height; //����������� �����
};

class Bike :public Ground_Vehicle
{
	//���������� �����, ��������� �� ���������� ����� ����������� ����� move
public:
	void move()
	{
		cout << "�������� ���� �� ���� �������" << endl;
	}
};

class Car :public Ground_Vehicle
{
public:
	void move()
	{
		cout << "������ ���� �� ������� �������" << endl;
	}
};

class Boat :public Water_Vehicle
{
public:
	void move()
	{
		cout << "����� ������ �� ����" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
//	Vehicle v; //���������� ������� ��������� ������������ ������
//	Ground_Vehicle gv; ���� ����� ����� �������� ����������� ��������� �� ����������
	                   //����� move
	Bike HD;
	HD.move();
	Car bmw;
	bmw.move();
	Boat boat;
	boat.move();
}