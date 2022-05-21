#include<SFML/Graphics.hpp>
#include"graf.h"//242 137 38
using namespace std;
using namespace sf;
class DataCircle
{
	CircleShape circle;
	Font font;
	Text text;
public:
	DataCircle()
	{
		font.loadFromFile("timesnewromanpsmt.ttf");
		text.setFillColor(Color::Black);
		text.setFont(font);
		text.setCharacterSize(15);
		circle.setOutlineColor(Color::Black);
		circle.setFillColor(Color(242, 137, 38));
		circle.setOutlineThickness(4);
	}
	DataCircle(const DataCircle &city)
	{
		font.loadFromFile("timesnewromanpsmt.ttf");
		text.setFillColor(Color::Black);
		text.setFont(font);
		text.setCharacterSize(15);
		circle.setOutlineColor(Color::Black);
		circle.setFillColor(Color(242, 137, 38));
		circle.setOutlineThickness(4);
		set_rad(city.circle.getRadius());
		set_name(city.text.getString());
		set_pos(city.circle.getPosition().x, city.circle.getPosition().y);
	}
	void set_pos(int x, int y)
	{
		circle.setPosition(x, y);
		text.setPosition(x, y);
	}
	void set_color(Color b)
	{
		circle.setFillColor(b);
	}
	void move(int x, int y)
	{
		circle.move(x, y);
		text.move(x, y);
	}
	void set_name(string name)
	{
		text.setString(name);
	}
	void set_rad(int r)
	{
		circle.setRadius(r);
	}
	void draw(RenderWindow& MainWindow)
	{
		MainWindow.draw(circle);
		int length_text = text.getString().getSize();
		text.move(circle.getRadius() - length_text * 3, circle.getRadius() - text.getCharacterSize());
		MainWindow.draw(text);
		text.move(-circle.getRadius() + length_text * 3, -circle.getRadius() + text.getCharacterSize());
	};
	int get_pos_x()
	{
		return circle.getPosition().x;
	}
	int get_pos_y()
	{
		return circle.getPosition().y;
	}
	int get_rad()
	{
		return circle.getRadius();
	}
	bool contain(int x, int y)
	{
		return circle.getGlobalBounds().contains(x, y);
	}
	void set_fill_color(Color p)
	{
		circle.setFillColor(p);
	}
	string get_name()
	{
		return text.getString();
	}


}; 
