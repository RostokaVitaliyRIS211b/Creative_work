#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;
class Textbox
{
	Vector2f size = { 100,100 };
	RectangleShape uio;
	Font font;
	Text text;
public:
	Textbox()
	{
		uio.setSize(size);
		uio.setOutlineColor(Color::Black);
		uio.setOutlineThickness(2);
		font.loadFromFile("timesnewromanpsmt.ttf");
		text.setFillColor(Color::Black);
		text.setFont(font);
		text.setCharacterSize(15);
	}
	void set_pos(int x, int y)
	{
		uio.setPosition(x, y);
		text.setPosition(x + 50 - text.getString().getSize(), y + 50 - text.getCharacterSize());
	}
	void set_string(string s)
	{
		text.setString(s);
	}
	void set_size(Vector2f s)
	{
		uio.setSize(s);
	}
	void draw(RenderWindow& Table)
	{
		Table.draw(uio);
		Table.draw(text);
	}
	bool contain(int x, int y)
	{
		return uio.getGlobalBounds().contains(x, y);
	}
	string get_text()
	{
		return text.getString();
	}
	Vector2f getPosition()
	{
		return uio.getPosition();
	}
};
