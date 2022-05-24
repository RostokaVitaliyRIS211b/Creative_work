#include<SFML/Graphics.hpp>
#include<iostream>
#include"Textbox.h"
#include<Windows.h>
using namespace sf;
using namespace std;
string s,s1,result;
vector<Textbox> boxes;
bool ifx(int x);
bool contain(string s);
bool contain_point(string s);
bool contain_divide(string s);
double to_decimal(double znam,double chislit);
string to_decimal(string drob);
string to_usual(string drob);
int get_chislitel(string drob);
int get_znamenatel(string drob);
string get_result(string num1, string num2, char operation, bool vid);
int main()
{
	HWND hConsole = GetConsoleWindow();//Если компилятор старый заменить на GetForegroundWindow()
	ShowWindow(hConsole, SW_HIDE);
	Textbox pole1, pole2, pole3, pole4, result, plus, minus, divide, uio,vid1,vid2;
	Vector2f size = {200,20};
	pole1.set_size(size);
	pole1.set_fill_color(Color(250, 250, 250));
	pole1.set_outlinethickness(2);
	pole1.set_Outline_Color(Color(134,150,170));
	pole1.set_pos(25, 25,6,15);
	boxes.push_back(pole1);
	pole2.set_size(size);
	pole2.set_fill_color(Color(250, 250, 250));
	pole2.set_outlinethickness(2);
	pole2.set_Outline_Color(Color(134, 150, 170));
	pole2.set_pos(25, 100, 6, 15);
	boxes.push_back(pole2);
	result.set_size(size);
	result.set_fill_color(Color(250, 250, 250));
	result.set_outlinethickness(2);
	result.set_Outline_Color(Color(134, 150, 170));
	result.set_pos(25, 150, 6, 15);
	boxes.push_back(result);
	 size = { 20,20 };
	plus.set_size(size);
	plus.set_fill_color(Color(250, 250, 250));
	plus.set_outlinethickness(2);
	plus.set_Outline_Color(Color(134, 150, 170));
	plus.set_string("+");
	plus.set_pos(25, 65, 6, 15);
	boxes.push_back(plus);
	minus.set_size(size);
	minus.set_fill_color(Color(250, 250, 250));
	minus.set_outlinethickness(2);
	minus.set_Outline_Color(Color(134, 150, 170));
	minus.set_string("-");
	minus.set_pos(50, 65, 7, 14);
	boxes.push_back(minus);
	divide.set_size(size);
	divide.set_fill_color(Color(250, 250, 250));
	divide.set_outlinethickness(2);
	divide.set_Outline_Color(Color(134, 150, 170));
	divide.set_string("/");
	divide.set_pos(75, 65, 8, 15);
	boxes.push_back(divide);
	uio.set_size(size);
	uio.set_fill_color(Color(250, 250, 250));
	uio.set_outlinethickness(2);
	uio.set_Outline_Color(Color(134, 150, 170));
	uio.set_string("*");
	uio.set_pos(100, 65, 7, 17);
	boxes.push_back(uio);
	vid1.set_size(size);
	vid1.set_fill_color(Color(250, 250, 250));
	vid1.set_outlinethickness(2);
	vid1.set_Outline_Color(Color(134, 150, 170));
	vid1.set_string("/");
	vid1.set_pos(230, 150, 8, 17);
	boxes.push_back(vid1);
	vid2.set_size(size);
	vid2.set_fill_color(Color(250, 250, 250));
	vid2.set_outlinethickness(2);
	vid2.set_Outline_Color(Color(134, 150, 170));
	vid2.set_string(".");
	vid2.set_pos(255, 150, 10, 10);
	boxes.push_back(vid2);
	Image sp;
	sp.loadFromFile("oboi.jpg");
	Texture sp1;
	sp1.loadFromImage(sp);
	Sprite oboi;
	oboi.setTexture(sp1);
	oboi.setPosition(0, 0);
	enum symbols
	{
		point1 = true,
		divide1 = false
	};
	enum Events
	{
		first_pole_is_pressed=1,
		first_pole_not_pressed=-1,
		second_pole_is_pressed = 2,
		second_pole_not_pressed = -2,
		usual_vid=3,
		unusual_vid=-3
	};
	int pos = -1,first_pole=0,second_pole=0,pluspressed=0,minuspressed=0,dividepressed=0,uiopressed=0,vid=0;
	char buff;
	RenderWindow MainWindow(VideoMode(350, 200), "Calculator", Style::Close | Style::Titlebar);
	while (MainWindow.isOpen())
	{
		Vector2i mouse_pos = Mouse::getPosition(MainWindow);
		Event event;
		MainWindow.clear(Color::White);
		MainWindow.draw(oboi);
		pos = -1;
		for (int i = 0; i < boxes.size(); ++i)
			if (boxes[i].contain(mouse_pos))
				pos = i;
		while (MainWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				MainWindow.close();
				break;
			case Event::KeyPressed:
			{
				if ((event.key.code >= Keyboard::Num0 and event.key.code <= Keyboard::Num9 or event.key.code==52 or event.key.code==50 or event.key.code == Keyboard::BackSpace) and ifx(first_pole) and s.length() < 11)
				{
					string buff = s;
						if (event.key.code == 52 and !contain(s))
							s += '/';
						if (event.key.code == 50 and !contain(s))
							s += '.';
						if(event.key.code >= Keyboard::Num0 and event.key.code <= Keyboard::Num9)
							s += char(event.key.code + 22);
						if (event.key.code == Keyboard::BackSpace)
							if (s.length() > 1)
								s.erase(s.length() - 1, s.length() - 1);
							else
								s = "";
							/*cout << "h5 " <<s.length()<< endl;*/
						if (s.length() > 0)
							if (s[0] == '0')
								s = buff;
						if(s.length()>2)
							if ((s[s.length() - 2] == '/' and s[s.length() - 1] == '0'))
								s = buff;
					boxes[0].set_string(s);
				}
				if ((event.key.code >= Keyboard::Num0 and event.key.code <= Keyboard::Num9 or event.key.code == 52 or event.key.code == 50 or event.key.code == Keyboard::BackSpace) and ifx(second_pole) and s1.length() < 11)
				{
					/*cout << "yu1" << endl;*/
					string buff = s1;
						if (event.key.code == 52 and !contain(s1))
							s1 += '/';
						if (event.key.code == 50 and !contain(s1))
							s1 += '.';
				
						if (event.key.code >= Keyboard::Num0 and event.key.code <= Keyboard::Num9)
							s1 += char(event.key.code + 22);
						if (event.key.code == Keyboard::BackSpace)
							if (s1.length() > 1)
								s1.erase(s1.length() - 1, s1.length() - 1);
							else
								s1 = "";
						if (s1.length() > 0)
							if (s1[0] == '0')
								s1 = buff;
						if (s1.length() > 2)
							if ((s1[s1.length() - 2] == '/' and s1[s1.length() - 1] == '0'))
								s1 = buff;
					/*cout << "yu" << endl;*/
					boxes[1].set_string(s1);
				}
				if (event.key.code == Keyboard::Escape)
					MainWindow.close();
				break;
			}
			case Event::MouseButtonPressed:
			{
			/*	cout << pos << endl;*/
				if (event.key.code == Mouse::Left and pos==0 and !ifx(second_pole))
				{
					if (!ifx(first_pole))
					{
						first_pole = first_pole_is_pressed;
						boxes[pos].set_fill_color(Color(135, 206, 235));
						/*	cout << "rt5" << endl;*/
					}
					else
					{
						first_pole = first_pole_not_pressed;
						boxes[pos].set_fill_color(Color(250, 250, 250));
						/*cout << "rt4" << endl;*/
					}
					
				}
				if (event.key.code == Mouse::Left and pos == 1 and !ifx(first_pole))
				{
					if (!ifx(second_pole))
					{
						second_pole = second_pole_is_pressed;
						boxes[pos].set_fill_color(Color(135, 206, 235));
					}
					else
					{
						second_pole = second_pole_not_pressed;
						boxes[pos].set_fill_color(Color(250, 250, 250));
					}
				}
				if (event.key.code == Mouse::Left and !ifx(first_pole) and !ifx(second_pole) and pos<7 and pos>2)
				{
					/*cout << "g5" << endl;*/
					if (s.size() > 0 and s1.size() > 0)
					{
						if (s[s.size() - 1] != '/' and s[s.size() - 1] != '.' and s1[s1.size() - 1] != '/' and s1[s1.size() - 1] != '.' and contain(s) and contain(s1))
						{
							boxes[2].set_string(get_result(s, s1, boxes[pos].get_text()[0], ifx(vid)));
							buff = boxes[pos].get_text()[0];
						}
						/*cout << "g3" << endl;*/
							
					}
					/*cout << "g4" << endl;*/
					
				}
				if (event.key.code == Mouse::Left and !ifx(first_pole) and !ifx(second_pole) and pos > 6)
				{
					if (pos == 7)
						vid = usual_vid;
					else
						vid = unusual_vid;
				}
				break;
			}
			}
		}
		if(s.size()>0 and s1.size()>0)
			if (boxes[2].get_text().size() > 0 and s[s.size() - 1] != '/' and s[s.size() - 1] != '.' and s1[s1.size() - 1] != '/' and s1[s1.size() - 1] != '.' and contain(s) and contain(s1))
					boxes[2].set_string(get_result(s, s1, buff, ifx(vid)));
		if (pos >= 0 and boxes.size() > 0 and !ifx(first_pole) and !ifx(second_pole))
			boxes[pos].set_fill_color(Color(135, 206, 235));
		for (int i = 0; i < boxes.size(); ++i)
			boxes[i].draw(MainWindow);
		MainWindow.display();
		if (pos >= 0 and boxes.size() > 0 and !ifx(first_pole) and !ifx(second_pole))
			boxes[pos].set_fill_color(Color(250, 250, 250));
		/*cout << "124" << endl;*/
	}
	return 0;
}
bool ifx(int x)
{
	return x > 0;
}
bool contain(string s)
{
	bool flag = false;
	for (int i = 0; i < s.size() and !flag; ++i)
		if (s[i] == '.' or s[i] == '/')
			flag = true;
	return flag;
}
double to_decimal(double znam, double chislit)
{
	return znam / chislit;
}
bool contain_point(string s)
{
	bool flag = false;
	for (int i = 0; i < s.size() and !flag; ++i)
		if (s[i] == '.')
			flag = true;
	return flag;
}
bool contain_divide(string s)
{
	bool flag = false;
	for (int i = 0; i < s.size() and !flag; ++i)
		if (s[i] == '/')
			flag = true;
	return flag;
}
int get_chislitel(string drob)
{
	int ch = 0;
	for (int i = 0; i < drob.size() and drob[i] != '/'; ++i)
		if (drob[i] >= '0' and drob[i] <= '9')
			ch = ch * 10 + (int(drob[i])-48);
	if (drob[0] == '-')
		ch = -ch;
	return ch;
}
int get_znamenatel(string drob)
{
	int zm = 0,i=0;
	while (drob[i] != '/')
		++i;
	for (i;i < drob.size(); ++i)
		if (drob[i] >= '0' and drob[i] <= '9')
			zm = zm * 10 + (int(drob[i]) - 48);
	return zm;
}
string to_decimal(string drob)
{
	string s;
	int ch = get_chislitel(drob), zm1 = get_znamenatel(drob),i=0;
	double zm = to_decimal(ch, zm1);
	s = to_string(zm);
	return s;
}
string to_usual(string drob)
{
	string s;
	int count = 0,stepen=0;
	while (drob[count] != '.')
	{
		if (drob[count] >= '0' and drob[count] <= '9')
			s += drob[count];
		++count;
	}
	for (int i = count+1; i < drob.size(); ++i)
	{
		if (drob[i] >= '0' and drob[i] <= '9')
			s += drob[i];
		++stepen;
	}
	s.insert(s.size(), "/");
	s.insert(s.size(), to_string(static_cast<int>(pow(10, stepen))));
	return s;
}
string get_result(string num1, string num2, char operation, bool vid)
{
	int ch1, zm1,ch2,zm2,ch,zm;
	string result;
	switch (operation)
	{
	case'+':
	{
		if (contain_point(num1))
			num1 = to_usual(num1);
		if (contain_point(num2))
			num2 = to_usual(num2);
		ch1 = get_chislitel(num1);
		zm1 = get_znamenatel(num1);
	/*	cout << "g57" << endl;*/
		ch2 = get_chislitel(num2);
		/*cout << "g58" << endl;*/
		zm2 = get_znamenatel(num2);
		/*cout << "g56" << endl;*/
		if (zm1 == zm2)
		{
			ch = ch1 + ch2;
			zm = zm1;
		}
		else
		{
			ch = ch1 * zm2 + ch2 * zm1;
			zm = zm1 * zm2;
		}
		result = to_string(ch) + '/' + to_string(zm);
		break;
	}
	case'-':
	{
		if (contain_point(num1))
			num1 = to_usual(num1);
		if (contain_point(num2))
			num2 = to_usual(num2);
		ch1 = get_chislitel(num1);
		zm1 = get_znamenatel(num1);
		ch2 = get_chislitel(num2);
		zm2 = get_znamenatel(num2);
		if (zm1 == zm2)
		{
			ch = ch1 - ch2;
			zm = zm1;
		}
		else
		{
			ch = ch1 * zm2 - ch2 * zm1;
			zm = zm1 * zm2;
		}
		result = to_string(ch) + '/' + to_string(zm);
		break;
	}
	case'*':
	{
		if (contain_point(num1))
			num1 = to_usual(num1);
		if (contain_point(num2))
			num2 = to_usual(num2);
		ch1 = get_chislitel(num1);
		zm1 = get_znamenatel(num1);
		ch2 = get_chislitel(num2);
		zm2 = get_znamenatel(num2);
		ch = ch1 * ch2;
		zm = zm1 * zm2;
		result = to_string(ch) + '/' + to_string(zm);
		break;
	}
	case'/':
	{
		if (contain_point(num1))
			num1 = to_usual(num1);
		if (contain_point(num2))
			num2 = to_usual(num2);
		ch1 = get_chislitel(num1);
		zm1 = get_znamenatel(num1);
		ch2 = get_chislitel(num2);
		zm2 = get_znamenatel(num2);
		ch = ch1 * zm2;
		zm = zm1 * ch2;
		result = to_string(ch) + '/' + to_string(zm);
		break;
	}
	default:
		break;
	}
	if (!vid)
		result = to_decimal(result);
	return result;
	
}
//TEST_CASE("Squares are computed", "[Square]")
//{
//	REQUIRE(Square(1) == 1);
//	REQUIRE(Square(2) == 4);
//	REQUIRE(Square(3) == 9);
//	REQUIRE(Square(7) == 49);
//	REQUIRE(Square(10) == 100);
//}