#include<SFML/Graphics.hpp>
#include<cmath>
using namespace std;
using namespace sf;
class a1
{
	Vector2f point_one;
	Vector2f point_two;
	Color cop=Color::Black;
	Font font;
	Text text;
	bool oriented = false;
	int pos1=-1, pos2=-1,posor=0;
	float pi = 3.14159265358;
	int string_to_int(string s)
	{
		int x = 0;
		for (int i = 0; i < s.size(); ++i)
			x = x * 10 + (int(s[i]) - 48);
		return x;
	}
	double dlina(const float &x, const float &y, const float &x1, const float &y1)
	{
		return sqrt(pow(x - x1, 2) + pow(y - y1, 2));
	}
	float dlina(Vector2f vec)
	{
		return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	}
	double angle(const float &x, const float &y, const float &x1, const float &y1)
	{
		Vector2f b = { 6,0 };
		Vector2f a = {x-x1,y-y1};
		return((a.x * b.x) / (dlina(a) * dlina(b)));
	}
	float angle(Vector2f vec)
	{
		Vector2f b = { 6,0 };
		return((vec.x * b.x) / (dlina(vec) * dlina(b)));
	}
public:
	a1()
	{
		font.loadFromFile("timesnewromanpsmt.ttf");
		text.setFillColor(cop);
		text.setCharacterSize(15);
		text.setFont(font);
		text.setOutlineColor(Color::White);
		text.setOutlineThickness(5);
		point_one = { 0,0 };
		point_two = { 1,1 };
		
	}
	a1(const a1 &y)
	{
		point_one = y.point_one;
		point_two = y.point_two;
		pos1 = y.pos1;
		pos2 = y.pos2; 
		font = y.font;
		text = y.text;
		text.setFillColor(y.text.getFillColor());
		text.setCharacterSize(15);
		text.setOutlineColor(Color::White);
		text.setOutlineThickness(5);
		text.setFont(font);
	}
	void draw1(RenderWindow& MainWindow)
	{
		vector<Vertex> line = { Vertex(point_one,cop), Vertex(point_two,cop) };
		text.setPosition((point_one.x + point_two.x - text.getCharacterSize()) / 2, (point_one.y + point_two.y - text.getCharacterSize()) / 2);
		MainWindow.draw(&line[0], line.size(), Lines);
		MainWindow.draw(text);
		
	}
	void draw2(RenderWindow& MainWindow)
	{
		RectangleShape lo(Vector2f(dlina(point_one.x,point_one.y,point_two.x,point_two.y), 3));
		lo.setPosition(point_one);
		lo.setFillColor(cop);
		lo.rotate(acos(dlina(point_one.x, point_one.y, point_two.x, point_one.y) /dlina(point_one.x, point_one.y, point_two.x, point_two.y)));
		MainWindow.draw(lo);
	}
	void set_coords(const float x, const float y, float x1, float y1)
	{
		point_one = { x,y };
		point_two = { x1,y1 };
	}
	void set_coords_one(const float x, const float y)
	{
		point_one = { x,y };
	}
	void set_coords_two(const float x, const float y)
	{
		point_two = { x,y };
	}
	void set_color(Color b)
	{
		cop = b;
	}
	int get_coord_first_x()
	{
		return point_one.x;
	}
	int get_coord_first_y()
	{
		return point_one.y;
	}
	int get_coord_second_x()
	{
		return point_two.x;
	}
	int get_coord_second_y()
	{
		return point_two.y;
	}
	void set_pos1(int pos)
	{
		pos1 = pos;
	}
	void set_pos2(int pos)
	{
		pos2 = pos;
	}
	int get_pos1()
	{
		return pos1;
	}
	int get_pos2()
	{
		return pos2;
	}
	void set_name(string s)
	{
		text.setString(s);
	}
	string get_name()
	{
		return text.getString();
	}
	bool contain(double x, double y)
	{
		Vector2f a = { point_one.x - point_two.x,point_one.y - point_two.y };
		double tochnost = 0.1/ (1 + abs(angle(a)));
		if (abs(angle(a)) < 0.05 or abs(angle(a)) > 0.995)
			tochnost = 0.4;
		if(abs(angle(a)) < 0.00005 or abs(angle(a)) > 0.99995)
			tochnost = 1;
		/*out <<point_two.x<<" "<< point_two.y << "     "<< dlina(point_one.x, point_one.y, point_two.x, point_two.y) << " " << dlina(point_two.x, point_two.y, x, y) << endl;*/
		return (abs(((x - point_one.x) / (point_two.x - point_one.x)) - ((y - point_one.y) / (point_two.y - point_one.y))) < tochnost) and (dlina(point_one.x, point_one.y, point_two.x, point_two.y)>= dlina(point_one.x, point_one.y, x, y)) and(dlina(point_one.x, point_one.y, point_two.x, point_two.y)>= dlina(x, y, point_two.x, point_two.y));
	}
	bool contain(Vector2f pos)
	{
		return abs(((pos.x - point_one.x) / (point_two.x - point_one.x)) - ((pos.y - point_one.y) / (point_two.y - point_one.y)))<0.00005;
	}
	void set_posor(bool f)
	{
		if (f)
			posor = pos1;
		else
			posor = pos2;
	}
	void set_oriented(bool f)
	{
		oriented = f;
	}
	bool get_oriented()
	{
		return oriented;
	}
	int get_weight()
	{
		return(string_to_int(text.getString()));
	}
};
