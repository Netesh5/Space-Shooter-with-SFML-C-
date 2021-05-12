#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<vector>
#include<string>
#include<iostream>
using namespace std;
using namespace sf;
int main(){
	//font1;
	Font font;
	font.loadFromFile("main_font.ttf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(Color::white);
	
	//font2;
	Font font2;
	font2.loadFromFile("main_font.ttf");
	Text text2;
	text2.setFont(font2);
	text2.setCharacterSize(50);
	text2.setFillColor(Color::white);
	text2.setPosition(200.f,270.f);
	text2.setString("Game Over");
	int k=1;
	
	//music;
	Music m;
	Music fire;
	fire.openFromFile("laser.wav");
	m.openFromFile("background.wav");
	m.play();
	
	//window
	RenderWindow window(videoMode(getFullscreenModes()));
	window.setFramerateLimit(60);
	
	//background image;
	Texture background;
	background.loadFromFile("background.jpg");
	sprite background;
	background.setTexture(background);
	
	//spaceship;
	Texture sship;
	sship.loadFromFile("ship.png");
	sprite ship;
	ship.setTexture(sship);
	ship.setPosition(330,480);
	
	//bullet;
	CircleShape bullet;
	bullet.setRadius(5.f);
	bullet.setFillColor(Color::Yellow);
	int time1=0;
	
	//alien;
	Texture asteriod;
	alien.loadFileFrom("asteroid.png");
	sprite asteriod;
	asteriod.setTexture(asteriod);
	asteriod.setPosition(200,f,10,f);
	int time2=0;
	
	//score;
	int score=0;
	
	vector<Sprite>vecmon;
	vecmon.push_back(Sprite(asteriod));
	
	vector<CircleShape>vecbullet;
	vecbullet.push_back(CircleShape(bullet));
	
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event))
			if(event.type==even.Closed)
				window.close();
			if(keyboard::isKeyPressed(keyboard::Left)&&ship.getPosition().x>0){
				ship.move(-80.f,0.f);
			}
			if(keyboard::isKeyPressed(keyboard::Left)&&ship.getPosition().x>0){
				ship.move(8.f,0.f);
			}
			if(time1<5){
				time1++;
			}	
			if(Keyboard::isKeyPressed(Keyboard::Space)&&time1>=5)){
				fire.play();
				bullet.setPosition(ship.getPosition().x+60,490);
				vecbullet.push_back(CircleShape(bullet));
				time1=0;
			}
			for(size_t i=0;i<vecbullet.size();i++){
				window.draw(vecbullet[i);
			}
			for(size_t i=0;i<vecmon.size();i++){
				window.draw(vecmon[i]);
			}
			window.draw(asteriod);
			window.draw(text);
			if(k<=0){
				window.clear();
				text.setPosition(280,200);
				window.draw(text);
				window.draw(text2);
			}
			window.display();
	}
	return 0;
}
