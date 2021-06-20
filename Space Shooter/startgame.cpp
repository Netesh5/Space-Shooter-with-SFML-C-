#include<iostream>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<graphics.h>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;
using namespace sf;
void startgame(){
	//font1;
	int h_score;
	ifstream fin;
	fin.open("Score.txt");
	fin>>h_score;
	fin.close();
	
	Font font;
	font.loadFromFile("Fonts/arial.ttf");

	Text text; //text to display score;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(Color::White);

	Text text2; //text for game over;
	text2.setFont(font);
	text2.setCharacterSize(50);
	text2.setFillColor(Color::White);
	text2.setPosition(200.f,270.f);
	text2.setString("Game Over");
	int k=1;

	Text text3; //text for to display high score;
	text3.setFont(font);
	text3.setCharacterSize(30);
	text3.setFillColor(Color::White);

	Text text4; //text for new high score;
	text4.setFont(font);
	text4.setCharacterSize(40);
	text4.setFillColor(Color::White);

	Text text5; // text for Do you want to continue;
	text5.setFont(font);
	text5.setCharacterSize(40);
	text5.setFillColor(Color::White);

	//music;
	Music m;
	Music fire;
	fire.openFromFile("Sounds/laser.wav");
	m.openFromFile("Sounds/background.wav");

	//window
	 RenderWindow window(VideoMode(),"Space Shooter",Style::Fullscreen);
	window.setFramerateLimit(60);

	//background image;
	Texture bg;
	bg.loadFromFile("Images/background2.png");
	Sprite background;
	background.setTexture(bg);

	Texture go_bg; //game over background image
	go_bg.loadFromFile("Images/background.png");
	Sprite Go_background;
	Go_background.setTexture(go_bg);

	//spaceship;
	Texture sship;
	sship.loadFromFile("Images/ship.png");
	Sprite ship;
	ship.setTexture(sship);
	ship.setPosition(getmaxwidth()/2,getmaxheight()/2+200);
    	ship.setScale(0.2,0.2);

	//bullet;
	CircleShape bullet;
	bullet.setRadius(5.f);
	bullet.setFillColor(Color::Green);
	int time1=0;

	//asteroid;
	Texture asterooid;
	asterooid.loadFromFile("Images/asteroid.png");
	Sprite asteroid;
	asteroid.setTexture(asterooid);
	asteroid.setPosition(100.f,10.f);
	asteroid.setScale(0.12,0.12);

	int time2=0;

    	//score;
	int score=0;

	vector<Sprite>vec_asteroid; //asteroid variable ;
	vec_asteroid.push_back(Sprite(asteroid));

	vector<CircleShape>vec_bullet; // bullet variable ;
	vec_bullet.push_back(CircleShape(bullet));
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event))
            m.play();
			if(event.type==event.Closed)
				window.close();

			if(Keyboard::isKeyPressed(Keyboard::Left) && ship.getPosition().x>0){
				ship.move(-8.f,0.f);
			}
			if(Keyboard::isKeyPressed(Keyboard::Right) && ship.getPosition().x<getmaxwidth()-155){
				ship.move(8.f,0.f);
			}

			//bullet shoot;
			if(time1<7){ //time for calling the bullet
				time1++;
			}
			if(Keyboard::isKeyPressed(Keyboard::Space) && time1>=7){
				fire.play();
				bullet.setPosition(ship.getPosition().x+80,550);
				vec_bullet.push_back(CircleShape(bullet)); //generate bullet at the end of last vector
				time1=0;
			}
			for(int i=0;i<vec_bullet.size();i++){
				vec_bullet[i].move(0.f,-10.f);
				if(vec_bullet[i].getPosition().y<=0.f){ //if y-axis value of bullet is equal to zero
                    vec_bullet.erase(vec_bullet.begin()+i);
				}
			}
			//enemy movement;
			if(time2<20){ //time to recall the enemy;
                		time2++;
			}
			if(time2>=20){
                		asteroid.setPosition(50+rand()%getmaxwidth(),-15.f);//bring asteroid ;
                		vec_asteroid.push_back(Sprite(asteroid)); // suru ma erase garxa ani push_back le naya asteroid generate garxa;
                		time2=0;
			}
			for(int i=0;i<vec_asteroid.size();i++){
                		vec_asteroid[i].move(0.f,2.f);
                		if( vec_asteroid[i].getGlobalBounds().intersects(ship.getGlobalBounds())){ // to check collision between asteroid and spaceship
                   			 vec_asteroid.erase(vec_asteroid.begin()+i);
                    				k--; // indicator
                		}
			}

			//collision;
			for(int i=0;i<vec_bullet.size();i++)
                	{
                   		 for(int j=0;j<vec_asteroid.size();j++)
                    		{
                        		if(vec_bullet[i].getGlobalBounds().intersects(vec_asteroid[j].getGlobalBounds()) )
                            		{
                                		vec_asteroid.erase(vec_asteroid.begin()+j);
                                		vec_bullet.erase(vec_bullet.begin()+i);
                                		score++;
                                		break;
                            		}
                   		 }
                	}
            		text3.setPosition(getmaxwidth()-250,0);
			text3.setString("High Score : "+std::to_string(h_score));

			//Score;
            		text.setString("Score : "+std::to_string(score));

			window.clear();
			window.draw(background);
			window.draw(ship);
			for(int i=0;i<vec_bullet.size();i++){ // recalling of bullets after clearing the device;
				window.draw(vec_bullet[i]);
			}
			for(int i=0;i<vec_asteroid.size();i++){ // recalling of asteroid after clearing the device;
                		window.draw(vec_asteroid[i]);
			}

			window.draw(asteroid);
			window.draw(text);
			window.draw(text3);
			if(score>30) //movement increase of enemy
            		{
                		time2+=2;
            		}
			if(k<=0){ // after collision of spaceship
				window.clear();
				window.draw(Go_background); //display game over background image;
				text2.setPosition(getmaxwidth()/2-100,getmaxheight()/2-300); //for game over;
				text.setPosition(getmaxwidth()/2-80,getmaxheight()/2-200); //for score
				text.setCharacterSize(30);
				text.setString("Your Score : "+std::to_string(score)); // to display score
				window.draw(text); // function to display text
				window.draw(text2);
				window.draw(text3);
				text4.setPosition(getmaxwidth()/2-250,getmaxheight()/2-100);
                		text4.setString("Congratulations ! New High score : "+std::to_string(h_score));
                		text5.setPosition(getmaxwidth()/2-180,getmaxheight()/2);
                		text5.setString("Do you want to continue ? \n\n\t\tPress  Y  or  N  ");
                		window.draw(text5);
                		if(Keyboard::isKeyPressed(Keyboard::Key::Y)){
                   			 window.close();
                    			startgame();
                   		}
                   		else if(Keyboard::isKeyPressed(Keyboard::Key::N)){
                     			window.close();
                   		}

				if(score>=h_score){ // for storing the score in database
                    			window.draw(text4);
                    			ofstream fout;
                    			fout.open("Score.txt");
                   			 h_score=score;
                    			fout<<h_score;
                    			fout.close();
				}
			}
			window.display();
	}

}

