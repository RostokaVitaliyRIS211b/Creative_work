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
	void set_pos(float x, float y, float paramx, float paramy)
	{
		uio.setPosition(x, y);
		text.setPosition(x + paramx - text.getString().getSize(), y+ paramy - text.getCharacterSize());
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
	bool contain(Vector2i o)
	{
		return uio.getGlobalBounds().contains(o.x,o.y);
	}
	void set_outlinethickness(int x)
	{
		uio.setOutlineThickness(x);
	}
	void set_Outline_Color(Color p)
	{
		uio.setOutlineColor(p);
	}
	string get_text()
	{
		return text.getString();
	}
	Vector2f getPosition()
	{
		return uio.getPosition();
	}
	void set_fill_color(Color p)
	{
		uio.setFillColor(p);
	}
};
