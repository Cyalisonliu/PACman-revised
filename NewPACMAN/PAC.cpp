#include<iostream>
#include <SFML/Window/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>
#include<Windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
using namespace sf;
using namespace std;

const int H = 29;
const int W = 40;
int i = 0;
int j = 0;
string s(double n);
string s(double n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}
//所有Font以及Text
Font myfont;
Font fontA;
Text gameover;
Text mypoint;
Text mypoints;
Text mytime;
Text myscores;
Text youwin;
Text Intro;
Text play;
Text Exit;
//所有Texture以及Sprite
Texture tt;
Sprite Title;
Texture ms;
Sprite mouseChoice;
Texture mpE;
Sprite mapElement;
Texture c;
Sprite coin;
Texture b;
Sprite ball;
Texture p;
Sprite pacMan;
Texture leftP;
Texture upP;
Texture downP;
Texture g[3];
Sprite ghost[3];
Texture invisibleG;
Texture B;
Sprite goodBye;

bool wallbomb(String gamemap[H], int x, int y, bool ToF);
bool wallbomb(String gamemap[H], int x, int y, bool ToF)
{
	if (ToF == false) {
		if (gamemap[y][x] == '0')
			return true;
	}
	else {
		if (gamemap[y][x] == '0' || gamemap[y][x] == '3')
			return true;
	}
	return false;
}
void jumpout(String gamemap[H], int &x, int &y);
void jumpout(String gamemap[H], int &x, int &y)
{
	if (gamemap[y][x] == '3') {
		if (x == 0)x = 39;
		else if (x == 39)x = 0;
	}
	return;
}
bool eatcoin(String gamemap[H], int x, int y);
bool eatcoin(String gamemap[H], int x, int y)
{
	if (gamemap[y][x] == 'c') {
		gamemap[y][x] = ' ';
		return true;
	}
	return false;
}
bool eatfruit(String gamemap[H], int x, int y);
bool eatfruit(String gamemap[H], int x, int y)
{
	if (gamemap[y][x] == 'x') {
		gamemap[y][x] = ' ';
		return true;
	}
	return false;
}

int main()
{
	String gamemap[H] = {
		"0000000000000000000000000000000000000000",
		"0000000000000000000000000000000000000000",
		"00xccccccccccccccc    cccccccccccccccx00",
		"00c000c000000c0000    0000c000000c000c00",
		"00c000c000000c0000    0000c000000c000c00",
		"00cccccccccccccccccccccccccccccccccccc00",
		"00c0000000c00c000000000000c00c0000000c00",
		"00c0000000c00c000000000000c00c0000000c00",
		"00c00cccccx00      00      00xccccc00c00",
		"00c00cc000c0000000 00 0000000c000cc00c00",
		"00c00cc000c0000000 00 0000000c000cc00c00",
		"00c00cc000c00              00c000cc00c00",
		"00ccccc000c00 00000  00000 00c000ccccc00",
		"00  000000c00 00000  00000 00c000000  00",
		"3   000000c                  c000000   3",
		"00  000000c00 00000  00000 00c000000  00",
		"00ccccc000c00 00000  00000 00c000ccccc00",
		"00c00cc000c00              00c000cc00c00",
		"00c00cc000c0000000 00 0000000c000cc00c00",
		"00c00cc000c0000000 00 0000000c000cc00c00",
		"00c00cccccx00      00      00xccccc00c00",
		"00c0000000c00c000000000000c00c0000000c00",
		"00c0000000c00c000000000000c00c0000000c00",
		"00cccccccccccccccccccccccccccccccccccc00",
		"00c000c000000c0000    0000c000000c000c00",
		"00c000c000000c0000    0000c000000c000c00",
		"00xccccccccccccccc    cccccccccccccccx00",
		"0000000000000000000000000000000000000000",
		"0000000000000000000000000000000000000000",
	};
	myfont.loadFromFile("Minecraft.ttf");
	fontA.loadFromFile("small.ttf");
	tt.loadFromFile("Title.png");
	Title.setTexture(tt);
	ms.loadFromFile("mouse.png");
	mouseChoice.setTexture(ms);
	mpE.loadFromFile("element.png");
	mapElement.setTexture(mpE);
	c.loadFromFile("coin.png");
	coin.setTexture(c);
	b.loadFromFile("ball.png");
	ball.setTexture(b);
	p.loadFromFile("yellowPacman.png");
	pacMan.setTexture(p);
	leftP.loadFromFile("leftpac.png");
	upP.loadFromFile("upPac.png");
	downP.loadFromFile("downPac.png");
	g[0].loadFromFile("redGhost.png");
	ghost[0].setTexture(g[0]);
	g[1].loadFromFile("greenGhost.png");
	ghost[1].setTexture(g[1]);
	g[2].loadFromFile("blueGhost.png");
	ghost[2].setTexture(g[2]);
	invisibleG.loadFromFile("invGhost.png");
	B.loadFromFile("pngegg.png");
	goodBye.setTexture(B);

	int L = 0, level = 0, direct = 0, shield =50, cx = 1, cy = 1, x = 19, y = 26;
	float xg[3] = { 20,20,20 }, yg[3] = { 14,14,14 };
	//float frameX = 0, frameY = 0, f1 = 0, f2 = 0;
	double point = 0, t = 0;
	bool invisible = false, playing = true;
	/*direct:
	1 = up;
	2 = down;
	3 = left;
	4 = right;
	*/

	//////一開始顯示的起始頁面(W,H,pix)//////
	RenderWindow start(VideoMode(1600, 900, 64), "start");
	pacMan.setPosition(0, 0);
	ghost[0].setPosition(30, 0);
	ghost[1].setPosition(60, 0);
	ghost[2].setPosition(90, 0);
	Intro.setFont(myfont);
	Intro.setString("Eat all PINKghost and fruit!");
	Intro.setCharacterSize(50);
	Intro.setPosition(460, 200);
	Intro.setFillColor(Color::White);

	Exit.setFont(fontA);
	Exit.setString("EXIT");
	Exit.setCharacterSize(80);
	Exit.setPosition(650, 650);
	Exit.setFillColor(Color::White);

	play.setFont(fontA);
	play.setString("PLAY");
	play.setCharacterSize(90);
	play.setPosition(650, 400);
	play.setFillColor(Color::White);

	Title.setPosition(450, 10);

	/*Music click;
	click.openFromFile();*/
	while (start.isOpen()) {//起始頁面
		Event event;
		while (start.pollEvent(event)) {//呼叫 pollEvent（）獲取事件
			if (event.type == Event::Closed) {
				start.close();
				exit(0);
			}
		}
		start.setMouseCursorVisible(false);//不要顯示出游標
		Vector2i mousePos = Mouse::getPosition(start);
		mouseChoice.setPosition(mousePos.x, mousePos.y);

		if (mousePos.x >= 650 && mousePos.x <= 900 && mousePos.y >= 400 && mousePos.y <= 500) {
			//click.pause();
			if (event.key.code == Mouse::Left) {//按左鍵的意思
				level = 1;//正常3隻鬼
				start.close();
			}
		}
		if (mousePos.x >= 650 && mousePos.x <= 950 && mousePos.y >= 650 && mousePos.y <= 750) {
			//click.pause();
			if (event.key.code == Mouse::Left) {
				exit(0);//我不想玩
			}
		}
		/*if (mouseChoice.getGlobalBounds().intersects(mouseChoice.getGlobalBounds())) {
			//click.play;
		}*/
		start.clear();//把頁面清空
		start.draw(pacMan);
		start.draw(ghost[0]);
		start.draw(ghost[1]);
		start.draw(ghost[2]);
		start.draw(play);
		start.draw(Exit);
		start.draw(Title);
		start.draw(Intro);
		start.draw(mouseChoice);
		start.display();
	}

	//////State of playing the game//////
	RenderWindow window(VideoMode(1600, 900, 64), "pacman");
	gameover.setFont(fontA);
	gameover.setString("GAME OVER");
	gameover.setCharacterSize(40);
	gameover.setFillColor(Color::Red);
	gameover.setPosition(600, 450);

	youwin.setFont(fontA);
	youwin.setString("YOU WIN");
	youwin.setCharacterSize(40);
	youwin.setFillColor(Color::Yellow);
	youwin.setPosition(600, 450);

	myscores.setFont(fontA);
	myscores.setString("TIME : ");
	myscores.setCharacterSize(30);
	myscores.setFillColor(Color::White);
	myscores.setPosition(1250, 300);

	mypoints.setFont(fontA);
	mypoints.setString("COIN : ");
	mypoints.setCharacterSize(30);
	mypoints.setFillColor(Color::Yellow);
	mypoints.setPosition(1250, 150);

	int dirGhost[3] = { 0 };
	for (int g = 0; g < 3 * level; g++) {
		ghost[g].setPosition(600, 420);
		dirGhost[g] = 0;
		cout << "*****";
	}
	pacMan.setPosition(x * 30, y * 30);

	/*SoundBuffer buffer;
	buffer.loadFromFile();
	Sound collect;
	collect.setBuffer(buffer);

	Music death;
	death.openFromFile();

	Music win;
	win.openFromFile();

	Music music;
	music.openFromFile();
	music.play();
	music.setLoop(true);*/

	while (window.isOpen()) {
		window.setFramerateLimit(80);
		window.setMouseCursorVisible(false);
		Event e;
		//////中途退出遊戲//////
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}

		while (playing == true) {
			window.clear();
			cout << "HI";
			//////Deck//////
			mypoint.setFont(myfont);
			mypoint.setString(s(point));
			mypoint.setCharacterSize(30);
			mypoint.setFillColor(Color::Yellow);
			mypoint.setPosition(1400, 150);

			mytime.setFont(myfont);
			mytime.setString(s(t));
			mytime.setCharacterSize(30);
			mytime.setFillColor(Color::White);
			mytime.setPosition(1400, 300);

			t += 0.1;

			//////let pacman walk//////
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				cout << "@@@up";
				y -= cy;
				//f2 = -30;
				//frameY = 30;
				//f1 = 30;
				//frameX = 0;
				if (wallbomb(gamemap, x, y, false) == true)//如果到wall,返回前一次位置(i.e.不更新位置)
					y += cy;
				if (eatfruit(gamemap, x, y) == true) {//吃到水果後更新map,shield = 0 -> ghost invisible
					shield = 0;
					invisible = true;
				}
				if (eatcoin(gamemap, x, y) == true) //吃到coin,更新地圖、point數
					point++;
				jumpout(gamemap, x, y);
				pacMan.setTexture(upP);
				//pacMan.setRotation(270);
				pacMan.setPosition(x * 30, y * 30);
				//pacMan.setTextureRect(sf::IntRect(frameX, frameY, f1, f2));
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				cout << "@@@down";
				y += cy;
				//f2 = 30;
				//frameY = 0;
				//f1 = 30;
				//frameX = 0;
				if (wallbomb(gamemap, x, y, false) == true)
					y -= cy;
				if (eatfruit(gamemap, x, y) == true) {
					shield = 0;
					invisible = true;
				}
				if (eatcoin(gamemap, x, y) == true) //吃到coin,更新地圖、point數
					point++;
				jumpout(gamemap, x, y);
				pacMan.setTexture(downP);
				//pacMan.setRotation(90);
				pacMan.setPosition(x * 30, y * 30);
				//pacMan.setTextureRect(sf::IntRect(frameX, frameY, f1, f2));
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				cout << "@@@left";
				x -= cx;
				if (wallbomb(gamemap, x, y, false) == true)
					x += cx;
				if (eatfruit(gamemap, x, y) == true) {
					shield = 0;
					invisible = true;
				}
				if (eatcoin(gamemap, x, y) == true) //吃到coin,更新地圖、point數
					point++;
				jumpout(gamemap, x, y);
				pacMan.setTexture(leftP);
				pacMan.setRotation(0);
				pacMan.setPosition(x * 30, y * 30);
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				cout << "@@@right";
				x += cx;
				//f2 = 30;
				//frameY = 0;
				//f1 = 30;
				//frameX = 0;
				if (wallbomb(gamemap, x, y, false) == true)
					x -= cx;
				if (eatfruit(gamemap, x, y) == true) {
					shield = 0;
					invisible = true;
				}
				if (eatcoin(gamemap, x, y) == true) //吃到coin,更新地圖、point數
					point++;
				jumpout(gamemap, x, y);
				pacMan.setTexture(p);
				pacMan.setRotation(0);
				pacMan.setPosition(x * 30, y * 30);
				//pacMan.setTextureRect(sf::IntRect(frameX, frameY, f1, f2));
			}
			
			Vector2f pos = pacMan.getPosition();

			//////let ghost walk//////
			srand(time(nullptr));
			for (int g = 0; g < 4; g++) {
				cout << "hello";
				cout << rand() ;
				dirGhost[g] = rand() % 4 + 1;
			}
			for (int g = 0; g < 3 * level; g++) {
				if (dirGhost[g] == 1) {
					yg[g] -= cy;
					if (wallbomb(gamemap, xg[g], yg[g], true) == false)
						ghost[g].move(0, -cy * 30);
					else
						yg[g] += cy;
				}
				else if (dirGhost[g] == 2) {
					yg[g] += cy;
					if (wallbomb(gamemap, xg[g], yg[g], true) == false)
						ghost[g].move(0, cy * 30);
					else
						yg[g] -= cy;
				}
				else if (dirGhost[g] == 3) {
					xg[g] -= cx;
					if (wallbomb(gamemap, xg[g], yg[g], true) == false)
						ghost[g].move(-cx * 30, 0);
					else
						xg[g] += cx;
				}
				else if (dirGhost[g] == 4) {
					xg[g] += cx;
					if (wallbomb(gamemap, xg[g], yg[g], true) == false)
						ghost[g].move(cx * 30, 0);
					else
						xg[g] -= cx;
				}

				/*//逃更多
				if (invisible == true) {// invisible
					if (xg[g] < pos.x) {
						xg[g] -= cx;
						if (wallbomb(gamemap, xg[g], yg[g], true) == false)
							ghost[g].move(-cx * 30, 0);
						else
							xg[g] += cx;
					}
					if (xg[g] > pos.x) {
						xg[g] += cx;
						if (wallbomb(gamemap, xg[g], yg[g], true) == false)
							ghost[g].move(cx * 30, 0);
						else
							xg[g] -= cx;
					}
					if (yg[g] > pos.y) {
						yg[g] += cy;
						if (wallbomb(gamemap, xg[g], yg[g], true) == false)
							ghost[g].move(0, cy * 30);
						else
							yg[g] -= cy;
					}
					if (yg[g] < pos.y) {
						yg[g] -= cy;
						if (wallbomb(gamemap, xg[g], yg[g], true) == false)
							ghost[g].move(0, -cy * 30);
						else
							yg[g] += cy;
					}
				}
				else {
					if (xg[g] < pos.x) {
						xg[g] += cx;
						if (wallbomb(gamemap, xg[g], yg[g], true) == false)
							ghost[g].move(cx * 30, 0);
						else
							xg[g] -= cx;
					}
					if (xg[g] > pos.x) {
						xg[g] += cx;
						if (wallbomb(gamemap, xg[g], yg[g], true) == false)
							ghost[g].move(-cx * 30, 0);
						else
							xg[g] -= cx;
					}
					if (yg[g] > pos.y) {
						yg[g] -= cy;
						if (wallbomb(gamemap, xg[g], yg[g], true) == false)
							ghost[g].move(0, -cy * 30);
						else
							yg[g] += cy;
					}
					if (yg[g] < pos.y) {
						yg[g] += cy;
						if (wallbomb(gamemap, xg[g], yg[g], true) == false)
							ghost[g].move(0, cy * 30);
						else
							yg[g] -= cy;
					}
				}*/
			}

			//////end let ghost walk//////

			//////吃完豆豆//////
			if (point == 282) {
				/*music.pause();
				win.play();*/
				playing = false;
				window.draw(youwin);
				window.display();
				Sleep(3000);
				window.close();
			}

			//////ghost  visibility//////
			if (shield == 50) {
				cout << "good";
				//看的到鬼
				//pacMan 及 所有ghost都有各自Texture//大小30*30
				for (int g = 0; g < 3 * level; g++) {
					if (pacMan.getGlobalBounds().intersects(ghost[g].getGlobalBounds())) {
						/*music.pause();
						death.play();*/
						playing = false;
						window.draw(gameover);
						window.display();
						Sleep(3000);
						window.close();
					}
				}
			}
			else if (shield < 50) {
				//鬼要隱形了
				//pacMan 及 所有ghost都有各自Texture
				for (int g = 0; g < 3 * level; g++)
					ghost[g].setTexture(invisibleG);
				shield++;
				if (shield == 50) {
					invisible = false;
					ghost[0].setTexture(g[0]);
					ghost[1].setTexture(g[1]);
					ghost[2].setTexture(g[2]);
				}
				for (int g = 0; g < 3 * level; g++) {
					if (pacMan.getGlobalBounds().intersects(ghost[g].getGlobalBounds())) {
						xg[g] = 20;
						yg[g] = 14;
						ghost[g].setPosition(xg[g] * 30, yg[g] * 30);//被吃掉的鬼會回到起始點
					}
				}
			}
			//////end ghost visibility//////

			//////display//////
			//////draw the map//////
			for (i = 0; i < H; i++) {
				for (j = 0; j < W; j++) {
					if (gamemap[i][j] == '0') {
						mapElement.setPosition(j * 30, i * 30);
						window.draw(mapElement);
					}
					if (gamemap[i][j] == 'c') {
						coin.setPosition(j * 30, i * 30);
						window.draw(coin);
					}
					if (gamemap[i][j] == 'x') {
						ball.setPosition(j * 30, i * 30);
						window.draw(ball);
					}
					if (gamemap[i][j] != '0') continue;
				}
			}
			//////end drawing map//////

			for (int g = 0; g < 3 * level; g++)
				window.draw(ghost[g]);
			window.draw(mytime);
			window.draw(myscores);
			window.draw(mypoint);
			window.draw(mypoints);
			window.draw(pacMan);
			window.display();
			Sleep(150);
			cout << "bad";
		}
		if (playing == false)
			window.close();
	}

	RenderWindow end(VideoMode(1600, 900, 64), "end");//結束頁面
	while (end.isOpen()) {
		pacMan.setPosition(0, 0);
		ghost[0].setPosition(30, 0);
		ghost[1].setPosition(60, 0);
		ghost[2].setPosition(90, 0);
		Exit.setFont(fontA);
		Exit.setString("Thank You");
		Exit.setCharacterSize(70);
		Exit.setPosition(550, 600);
		Exit.setFillColor(Color::White);

		goodBye.setPosition(470, 150);
		Event event;
		while (end.pollEvent(event)) {//呼叫 pollEvent（）獲取事件
			if (event.type == Event::Closed) {
				end.close();
				exit(0);
			}
		}
		end.setMouseCursorVisible(false);//不要顯示出游標
		Vector2i mousePos = Mouse::getPosition(end);
		mouseChoice.setPosition(mousePos.x, mousePos.y);

		if (mousePos.x >= 700 && mousePos.x <= 900 && mousePos.y >= 600 && mousePos.y <= 700) {
			//click.pause();
			if (event.key.code == Mouse::Left) {
				exit(0);//我不想玩
			}
		}
		end.clear();
		end.draw(pacMan);
		end.draw(ghost[0]);
		end.draw(ghost[1]);
		end.draw(ghost[2]);
		end.draw(Title);
		end.draw(mouseChoice);
		end.draw(goodBye);
		end.draw(Exit);
		end.display();
	}
	return 0;
}