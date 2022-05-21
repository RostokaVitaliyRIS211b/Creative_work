#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;
class Button
{
	Vector2f size = { 150,75 };
	CircleShape circle;
	Text text;
	Font font;
	int z = 0;
	char g = 'a';
	string j = "";
public:
	RectangleShape area;
	Button()//93 48 153
	{
		area.setSize(size);
		area.setPosition(0, 0);
		area.setFillColor(Color(93, 48, 153));
		area.setOutlineThickness(3);
		area.setOutlineColor(Color::Black);
		circle.setFillColor(Color(242, 137, 38));
		circle.setRadius(20);
		circle.setPosition(55, 17.5);
		circle.setOutlineColor(Color::Black);
		circle.setOutlineThickness(2);
	}
	Button(int n)
	{
		area.setSize(size);
		area.setPosition(153, 0);
		area.setFillColor(Color(93, 48, 153));
		area.setOutlineThickness(3);
		area.setOutlineColor(Color::Black);
		z = n;
	}
	Button(char n)
	{
		area.setSize(size);
		area.setPosition(306, 0);
		area.setFillColor(Color(93, 48, 153));
		area.setOutlineThickness(3);
		area.setOutlineColor(Color::Black);
		circle.setFillColor(Color(242, 137, 38));
		circle.setRadius(20);
		circle.setPosition(363, 17.5);
		circle.setOutlineColor(Color::Black);
		circle.setOutlineThickness(2);
		g = n;
	}
	Button(string n)
	{
		area.setSize(size);
		area.setPosition(459, 0);
		area.setFillColor(Color(93, 48, 153));
		area.setOutlineThickness(3);
		area.setOutlineColor(Color::Black);
		j = n;
		z = 2;
	}
	void set_fill_color(Color po)
	{
		area.setFillColor(po);
	}
	void draw(RenderWindow& MainWindow)
	{
		MainWindow.draw(area);
		if (z == 0)
			MainWindow.draw(circle);
		else
		{
			if (z == 1)
			{
				RectangleShape lo(Vector2f(100, 3));
				lo.setPosition(185, 60);
				lo.setFillColor(Color::Black);
				lo.rotate(-30);
				MainWindow.draw(lo);
			}

		}
		if (g == 'x')
		{
			RectangleShape lo(Vector2f(100, 3)), go(Vector2f(100, 3));
			lo.setPosition(335, 60);
			go.setPosition(335, 17.5);
			lo.setFillColor(Color::Red);
			go.setFillColor(Color::Red);
			go.rotate(22);
			lo.rotate(-26);
			MainWindow.draw(lo);
			MainWindow.draw(go);
		}
		if (j == "x")
		{
			RectangleShape to(Vector2f(100, 3));
			to.setPosition(489, 60);
			to.setFillColor(Color::Black);
			to.rotate(-30);
			MainWindow.draw(to);
			RectangleShape lo(Vector2f(50, 3)), go(Vector2f(50, 3));
			lo.setPosition(515, 50);
			go.setPosition(513, 20.5);
			lo.setFillColor(Color::Red);
			go.setFillColor(Color::Red);
			go.rotate(30);
			lo.rotate(-40);
			MainWindow.draw(lo);
			MainWindow.draw(go);
		}
	}
	Button(int x, int y)
	{
		area.setSize(size);
		area.setPosition(0, 0);
		area.setFillColor(Color(93, 48, 153));
		area.setOutlineThickness(3);
		area.setPosition(612, 0);
		area.setOutlineColor(Color::Black);
		font.loadFromFile("timesnewromanpsmt.ttf");
		text.setFillColor(Color::Black);
		text.setFont(font);
		text.setCharacterSize(15);
		text.setString("Way of Salesman");
		text.setPosition(650 - text.getString().getSize(), 37.5 - text.getCharacterSize());

	}
	void draw_com(RenderWindow& MainWindow)
	{
		MainWindow.draw(area);
		MainWindow.draw(text);
	}
};
