#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include<Windows.h>
#include"graf.h"
#include"CircleforGraph.h"
#include"line for graaph.h"
#include"Textbox.h"
#include"Button.h"
using namespace std;
using namespace sf;
vector<DataCircle> otobr;// massive of vertexses
vector<a1> otobtl;//massive of lines between vertexes
vector<string> way;//way of salesman
int bykva = 65, pos = 0 /*position of vertex in otobr*/, posl = 0 /*position of line in otobtl*/, n = 2;
graf PermRegion;
int pos_vec(string name, vector<DataCircle> cities);
void delete_circle();
void delete_line();
string texting_window(Vector2u size, bool flag);
int string_to_int(string s);
void contain_pos(int x, int y, bool circle_or_line);
bool contain(int x, int y, bool circle_or_line);
bool ifx(int x);
void drawtable();
int main()
{
	Button button1;
	Button button2(1);
	Button button3('x');
	Button button4("x");
	Button button5(1, 2);
	int circle_focus=0, line_focus=0,circle_making=0,line_making=0,commi=0,circle_deleting = 0, line_deleting = 0,table_draw=0;
	enum Events
	{
		Circle_not_focus = 0,
		Line_not_focus = -1,
		Circle_in_focus = 1,
		Line_in_focus = 2,
		Circle_creating = 3,
		Circle_deleting = 4,
		Circle_not_creating = -2,
		Circle_not_deleting = -3,
		Line_deleting = 5,
		Line_creating = 6,
		Line_not_deleting = -4,
		Line_not_creating = -5,
		Commivoyager_active = 7,
		Commivoyager_not_active = -7,
		Table_draw=8,
		Table_not_draw=-8
	};
	enum Objects
	{
		circle = 1,
		line = 0
	};
	int com = 0, minway;
	Vector2f a = { 100,25 };
	RenderWindow MainWindow(VideoMode(1024, 768), "Graph", Style::Close | Style::Titlebar);
	while (MainWindow.isOpen())
	{
		system("cls");
		table_draw = Table_not_draw;
		Vector2i mouse_pos = Mouse::getPosition(MainWindow);
		if (mouse_pos.x < 0)
			mouse_pos.x = 0;
		if (mouse_pos.y < 0)
			mouse_pos.y = 0;
		if (mouse_pos.x > 1024)
			mouse_pos.x = 1024;
		if (mouse_pos.y > 768)
			mouse_pos.y = 768;
		Event event;
		MainWindow.clear(Color::White);
		circle_focus = Circle_not_focus;
		line_focus = Line_not_focus;
		if (!ifx(circle_focus))
			if (contain(mouse_pos.x, mouse_pos.y, circle))
			{
				circle_focus = Circle_in_focus;
				contain_pos(mouse_pos.x, mouse_pos.y, circle);
			}
		if (!ifx(line_focus) and !ifx(line_making))
			if (contain(mouse_pos.x, mouse_pos.y, line))
			{
				line_focus = Line_in_focus;
				contain_pos(mouse_pos.x, mouse_pos.y, line);
			}
		/*cout << "rt4" << endl;*/
		if (!ifx(circle_focus) and !ifx(circle_making) and !ifx(circle_deleting) and ifx(line_focus) and !ifx(commi))
		{
			otobtl[posl].set_color(Color::Red);
		}
		else
		{
			if (otobtl.size() > 0 and posl < otobtl.size())
				otobtl[posl].set_color(Color::Black);
		}
		if (ifx(circle_focus) and !ifx(line_making) and !ifx(line_focus) and !ifx(line_deleting) and !ifx(commi))
		{
			otobr[pos].set_color(Color(196, 107, 23));
		}
		else
		{
			if (otobr.size() > 0 and pos< otobr.size())
				otobr[pos].set_color(Color(242, 137, 38));
		}
		while (MainWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				MainWindow.close();
				break;
			case Event::MouseButtonPressed:
			{
				if (event.key.code == Mouse::Right and !ifx(commi))
				{
					if (ifx(circle_focus) and !ifx(line_making) and !ifx(line_focus) and !ifx(line_deleting) and !ifx(commi) and !ifx(circle_deleting))
					{
						string s = texting_window(MainWindow.getSize(), false);
						if (s.size() > 0 and s.size()<6)
						{
							PermRegion.pereimenovat_city(otobr[pos].get_name(), s);
							otobr[pos].set_name(s);
						}
					}
					if (!ifx(circle_focus) and !ifx(circle_making) and !ifx(circle_deleting) and ifx(line_focus) and !ifx(commi) and !ifx(line_deleting))
					{
						string s = texting_window(MainWindow.getSize(), true);
						int x = string_to_int(s);
						if (x > 0)
						{
							PermRegion.add_connection(otobr[otobtl[posl].get_pos1()].get_name(), otobr[otobtl[posl].get_pos2()].get_name(), x);
							otobtl[posl].set_name(to_string(x));
						}
					}
				}
				if (event.key.code == Mouse::Left and !ifx(commi))
				{
					if (ifx(circle_making))
						circle_making=Circle_not_creating;
					else if (ifx(circle_focus) and !ifx(line_making) and !ifx(circle_deleting) and !ifx(line_deleting))
						circle_making=Circle_creating;
					if (ifx(line_making) and ifx(circle_focus))
					{
						if (n==2)
						{
							otobtl[posl].set_coords_one(otobr[pos].get_pos_x() + otobr[pos].get_rad(), otobr[pos].get_pos_y() + otobr[pos].get_rad());
							otobtl[posl].set_pos1(pos);
						}
						else
						{
							otobtl[posl].set_coords_two(otobr[pos].get_pos_x() + otobr[pos].get_rad(), otobr[pos].get_pos_y() + otobr[pos].get_rad());
							otobtl[posl].set_pos2(pos);
						}
						/*flag6 = !flag6;*/
						--n;
						if (n == 0)
						{
							line_making = Line_not_creating;
							n = 2;
							int x;
							string s = texting_window(MainWindow.getSize(), true);
							x = string_to_int(s);
							if (x > 0)
							{
								PermRegion.add_connection(otobr[otobtl[posl].get_pos1()].get_name(), otobr[otobtl[posl].get_pos2()].get_name(), x);
								otobtl[posl].set_name(to_string(x));
							}
							else
							{
								delete_line();
								system("cls");
							/*	cout << "9gr9at9y999" << endl;*/
							}
						}
						/*cout << pos << " " << otobtl[posl].get_pos1() << " " << otobtl[posl].get_pos2() <<" "<<posl<< endl;*/
					}
					if (button1.area.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y) and !ifx(circle_making) and !ifx(circle_deleting) and !ifx(line_deleting) and !ifx(line_making))
					{
						string name = "";
						name += char(bykva);
						DataCircle cir;
						cir.set_rad(60);
						cir.set_name(name);
						cir.set_pos(432, 2);
						PermRegion.add_city(name);
						otobr.push_back(cir);
						pos = otobr.size() - 1;
						circle_making=Circle_creating;
						++bykva;
						
					}
					if (button2.area.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y) and !ifx(line_making) and otobr.size() > 1 and !ifx(circle_deleting) and !ifx(line_deleting) and !ifx(circle_making))
					{
						a1 t;
						otobtl.push_back(t);
						posl = otobtl.size() - 1;
						line_making=Line_creating;
						n = 2;
					}
					if (button3.area.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y) and !ifx(line_deleting) and !ifx(circle_making) and !ifx(line_making))
					{
						if(ifx(circle_deleting))
							circle_deleting = Circle_not_deleting;
						else
							circle_deleting = Circle_deleting;
						if (ifx(circle_deleting))
							button3.set_fill_color(Color::Blue);
						else
							button3.set_fill_color(Color(93, 48, 153));
					}
					if (button4.area.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y) and !ifx(circle_making) and !ifx(line_making) and !ifx(circle_deleting))
					{
						if (ifx(line_deleting))
							line_deleting = Circle_not_deleting;
						else
							line_deleting = Circle_deleting;
						if (ifx(line_deleting))
							button4.set_fill_color(Color::Blue);
						else
							button4.set_fill_color(Color(93, 48, 153));
					}
					if (ifx(circle_focus) and ifx(circle_deleting))
					{
						delete_circle();
					}
					if (ifx(line_deleting) and ifx(line_focus))
					{
						delete_line();
					}
					if (button5.area.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
					{
						way = PermRegion.get_optway();
						commi = Commivoyager_active;//141 2 234
						minway = PermRegion.minway();
					}
					/*cout << flag7 <<" "<<flag4<<" "<<flag2<<endl;*/
				}
				break;
			}
			case Event::KeyPressed:
			{
				
				if (event.key.code == Keyboard::Escape and ifx(circle_making))
				{
					delete_circle();
					circle_making=Circle_not_creating;
					/*cout << "rt2" << endl;*/
					break;
				}
				if (event.key.code == Keyboard::Escape and ifx(line_making))
				{
					line_making=Line_not_creating;
					vector<a1> buff;
					for (int i = 0; i < otobtl.size(); ++i)
						if (i != posl)
							buff.push_back(otobtl[i]);
					otobtl.clear();
					otobtl = buff;
					break;
				}
				if (event.key.code == Keyboard::Tab)
					table_draw=Table_draw;
				if (event.key.code == Keyboard::Escape)
					MainWindow.close();
				break;
			}

			}
		}
		
		if (ifx(circle_making))
		{
			for (int i = 0; i < otobtl.size(); ++i)
			{
				if (otobtl[i].get_pos1() == pos)
					otobtl[i].set_coords_one(mouse_pos.x, mouse_pos.y);
				if (otobtl[i].get_pos2() == pos)
					otobtl[i].set_coords_two(mouse_pos.x, mouse_pos.y);
				/*cout << pos << " " << otobtl[i].get_pos1() << " " << otobtl[i].get_pos2() << " " << i << endl;*/
			}
			/*cout << endl << endl;*/
			
			otobr[pos].set_pos(mouse_pos.x - otobr[otobr.size() - 1].get_rad(), mouse_pos.y - otobr[otobr.size() - 1].get_rad());
		}/*
	*/	/*cout << "rt3" << endl;*/
		if (ifx(line_making))
		{
			if (n == 2)
				otobtl[posl].set_coords_one(mouse_pos.x, mouse_pos.y);
			else
				otobtl[posl].set_coords_two(mouse_pos.x, mouse_pos.y);
		}
		if (ifx(commi))
		{
			if (com < way.size())
				otobr[pos_vec(way[com], otobr)].set_fill_color(Color(141, 1, 234));
			if (com > 0)
				otobr[pos_vec(way[com - 1], otobr)].set_fill_color(Color(242, 137, 38));
			if (com < way.size())
				++com;
			else
			{
				commi=Commivoyager_not_active;
				com = 0;
			}
			Text text;
			Font font;
			font.loadFromFile("timesnewromanpsmt.ttf");
			text.setFillColor(Color::Black);
			text.setFont(font);
			text.setCharacterSize(15);
			text.setString("Way of Salesman equals " + to_string(minway));
			text.setPosition(850 - text.getString().getSize(), 37.5 - text.getCharacterSize());
			MainWindow.draw(text);
		}
		for (int i = 0; i < otobtl.size(); ++i)
			otobtl[i].draw1(MainWindow);
		for (int i = 0; i < otobr.size(); ++i)
			otobr[i].draw(MainWindow);
		button1.draw(MainWindow);
		button2.draw(MainWindow);
		button3.draw(MainWindow);
		button4.draw(MainWindow);
		button5.draw_com(MainWindow);
		if (ifx(table_draw))
			drawtable();
		MainWindow.display();
		if (ifx(commi))
			Sleep(1000);
	}
	return 0;
}
bool ifx(int x)
{
	return x > 0;
}
bool contain(int x, int y, bool circle_or_line)
{
	bool flag = false;
	if (circle_or_line)
	{
		for (int i = 0; i < otobr.size() and !flag; ++i)
		{
			if (otobr[i].contain(x, y))
				flag = true;
		}
	}
	else
	{
		for (int i = 0; i < otobtl.size() and !flag; ++i)
		{
			if (otobtl[i].contain(x, y))
				flag = true;
		}
	}
	return flag;
}
void contain_pos(int x, int y, bool circle_or_line)
{
	if (circle_or_line)
	{
		for (int i = 0; i < otobr.size(); ++i)
		{
			if (otobr[i].contain(x, y))
				pos = i;
		}
	}
	else
	{
		for (int i = 0; i < otobtl.size(); ++i)
		{
			if (otobtl[i].contain(x, y))
				posl = i;
		}
	}
}
int string_to_int(string s)
{
	int x = 0;
	for (int i = 0; i < s.size(); ++i)
		x = x * 10 + (int(s[i]) - 48);
	return x;
}
string texting_window(Vector2u size, bool flag)
{
	Text text, text_user;
	Font font;
	font.loadFromFile("timesnewromanpsmt.ttf");
	text.setFillColor(Color::Black);
	text.setFont(font);
	text.setCharacterSize(22);
	text_user.setFillColor(Color::Black);
	text_user.setFont(font);
	text_user.setCharacterSize(18);
	RectangleShape message;
	message.setPosition(0, 0);
	message.setFillColor(Color::White);
	Vector2f size1 = { 150,75 };
	message.setSize(size1);
	string s = "";
	RenderWindow NewWindow(VideoMode(size.x, size.y), "");
	if (flag)
		text.setString("Write number larger than zero");
	else
		text.setString("Write name of vertex");
	text.setPosition(75 - text.getString().getSize(), 27.5 - text.getCharacterSize());
	while (NewWindow.isOpen())
	{
		NewWindow.clear(Color::White);
		Event event;
		while (NewWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyPressed:
			{
				if (event.key.code == Keyboard::Enter and s.size() > 0)
					NewWindow.close();
				if (flag and (event.key.code > 25 and event.key.code < 36))
					s += char(event.key.code + 22);
				if (!flag and event.key.code > -1 and event.key.code < 26)
					s += char(event.key.code + 65);
				if (event.key.code == Keyboard::BackSpace)
					if (s.length() > 1)
						s.erase(s.length() - 1, s.length() - 1);
					else
						s = "";
				break;
			}
			}
		}
		text_user.setString(s);
		text_user.setPosition(150 - text_user.getString().getSize(), 75 - text_user.getCharacterSize());
		NewWindow.draw(message);
		NewWindow.draw(text);
		NewWindow.draw(text_user);
		NewWindow.display();
	}
	return s;
}
void delete_line()
{
	vector<a1> buff;
	PermRegion.delete_connection(otobr[otobtl[posl].get_pos1()].get_name(), otobr[otobtl[posl].get_pos2()].get_name());
	for (int i = 0; i < otobtl.size(); ++i)
		if (i != posl)
			buff.push_back(otobtl[i]);
	otobtl.clear();
	otobtl = buff;
}
void delete_circle()
{
	vector<a1> buff1;
	/*cout << "Tyt" << endl;*/
	for (int i = 0; i < otobtl.size(); ++i)
		if (otobtl[i].get_pos1() != pos and otobtl[i].get_pos2() != pos)
		{
			if (otobtl[i].get_pos1() > pos)
				otobtl[i].set_pos1(otobtl[i].get_pos1() - 1);
			if (otobtl[i].get_pos2() > pos)
				otobtl[i].set_pos2(otobtl[i].get_pos2() - 1);
			buff1.push_back(otobtl[i]);

		}
	otobtl.clear();
	otobtl = buff1;
	/*cout << "Tyt1" << endl;*/
	vector<DataCircle> buff;
	PermRegion.delete_city(otobr[pos].get_name());
	//cout << "Tyt3" << endl;
	for (int i = 0; i < otobr.size(); ++i)
		if (i != pos)
			buff.push_back(otobr[i]);
	otobr.clear();
	otobr = buff;
	//cout << "Tyt2" << endl;
}
int pos_vec(string name, vector<DataCircle> cities)
{
	int pos = -1;
	for (int i = 0; i < cities.size(); ++i)
		if (cities[i].get_name() == name)
			pos = i;
	return pos;
}
void drawtable()
{
	RenderWindow Table(VideoMode((otobr.size() + 1) * 100, (otobr.size() + 1) * 100), "Table", Style::Close | Style::Titlebar);
	int x = 0, y = 0, post = -1, num = 0;
	string s;
	vector<Textbox> messages;
	Textbox message;
	message.set_pos(x, y);
	message.set_string(" ");
	messages.push_back(message);
	x += 100;
	for (int i = 1; i < (otobr.size() + 1) * (otobr.size() + 1); ++i)
	{
		/*cout << i << " " << x << endl;*/
		if (i % (otobr.size() + 1) == 0)
		{
			y += 100;
			x = 0;
			message.set_string(PermRegion.get_name_of_city(i / (otobr.size() + 1) - 1));
		}
		else if (i > otobr.size())
			message.set_string(to_string(PermRegion.get_connection((i - 1) % (otobr.size() + 1), i / (otobr.size() + 1) - 1)));
		if (i <= otobr.size())
			message.set_string(PermRegion.get_name_of_city(i - 1));
		message.set_pos(x, y);
		messages.push_back(message);
		x += 100;
		/*Sleep(1000);*/
	}
	while (Table.isOpen())
	{
		Vector2i mouse_pos = Mouse::getPosition(Table);
		Event event;
		Table.clear(Color::White);
		while (Table.pollEvent(event))
		{
			
			for (int i = 0; i < messages.size(); ++i)
				if (messages[i].contain(mouse_pos.x, mouse_pos.y))
					post = i;
			if (event.type == Event::MouseButtonPressed)
			{
				if ((post <= otobr.size() or post / (otobr.size() + 1) == 0) and post != 0)
				{
					cout << post << endl;
					s = texting_window(Table.getSize(), false);
					PermRegion.pereimenovat_city(otobr[pos_vec(messages[post].get_text(), otobr)].get_name(), s);
					otobr[pos_vec(messages[post].get_text(), otobr)].set_name(s);
					if (post >= otobr.size() + 1)
					{
						messages[post].set_string(s);
						messages[post / otobr.size() + 1].set_string(s);
					}
					else
					{
						messages[post].set_string(s);
						messages[post * (otobr.size() + 1)].set_string(s);
					}

				}
				else
				{
					
					s = texting_window(Table.getSize(), true);
					int num = string_to_int(s);
					int pos11 = (post - 1) % (otobr.size() + 1), pos22 = (post / (otobr.size() + 1) - 1);
					if (num > 0)
					{
						if (PermRegion.get_connection(pos11, pos22) == 0)
						{
							a1 nline;
						
							nline.set_pos1(pos11);
							nline.set_pos2(pos22);
							nline.set_coords_one(otobr[pos11].get_pos_x() + otobr[pos11].get_rad(), otobr[pos11].get_pos_y() + otobr[pos11].get_rad());
							nline.set_coords_two(otobr[pos22].get_pos_x() + otobr[pos22].get_rad(), otobr[pos22].get_pos_y() + otobr[pos22].get_rad());
							nline.set_name(to_string(num));
							otobtl.push_back(nline);
						}
						PermRegion.add_connection(pos11, pos22, num);
						for (int i = 0; i < otobtl.size(); ++i)
							if ((otobtl[i].get_pos1() == pos11 or otobtl[i].get_pos2() == pos11) and (otobtl[i].get_pos1() ==pos22 or otobtl[i].get_pos2() ==pos22))
							{
								otobtl[i].set_name(to_string(num));
							}
						Vector2f posm=messages[post].getPosition();
						posm = { posm.y,posm.x };
						int nned=0;
						for (int i = 0; i < messages.size() and nned == 0; ++i)
							if (messages[i].getPosition() == posm)
								nned = i;
						messages[post].set_string(to_string(num));
						messages[nned].set_string(to_string(num));
						//cout<<
					
					}
					else
					{
						PermRegion.add_connection(pos11, pos22, 0);
						for (int i = 0; i < otobtl.size(); ++i)
							if ((otobtl[i].get_pos1() == pos11 or otobtl[i].get_pos2() == pos11) and (otobtl[i].get_pos1() == pos22 or otobtl[i].get_pos2() == pos22))
							{
								posl=i;
							}
						delete_line();
						Vector2f posm = messages[post].getPosition();
						posm = { posm.y,posm.x };
						int nned = 0;
						for (int i = 0; i < messages.size() and nned == 0; ++i)
							if (messages[i].getPosition() == posm)
								nned = i;
						messages[post].set_string(to_string(0));
						messages[nned].set_string(to_string(0));
					}
				}
			}
			if (event.key.code == Keyboard::Escape)
			{
				cout << "esc" << endl;
				Table.close();
			}
				
		}
		for (int i = 0; i < messages.size(); ++i)
			messages[i].draw(Table);
		Table.display();
	}
}
