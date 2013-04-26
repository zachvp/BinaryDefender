#include "mainwindow.h"
#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

void MainWindow::handleTimer()
{
	/** Keeps track of general timekeeping for round advancing purposes */
	++gameTimer;
	if(gameTimer%200 == 0){
		++seconds;
//		cout << "Time: " << seconds << " seconds" << endl;
	}
	/** Handle player movement */
	if(player->getDir() == 0  && (player->getY() > -15) && ( player->getX() > 285 && player->getX() < 325 ) ){
		player->moveUp(1);
	}
	else if(player->getDir() == 1  && (player->getY() < WINDOW_MAX_Y-45) && ( player->getX() > 285 && player->getX() < 325 )){
		player->moveDown(1);
	}
	else if(player->getDir() == 2  && (player->getX() > -30) && ( player->getY() > 205 && player->getY() < WINDOW_MAX_Y/2 + 10 )){
		player->moveLeft(1);
	}
	else if(player->getDir() == 3  && (player->getX()  < WINDOW_MAX_X) && ( player->getY() > 210 && player->getY() < WINDOW_MAX_Y/2 + 10 )){
		player->moveRight(1);
	}
	/** SMASH the walls! */
// SMASH the top two walls	
	if(q1->getRight() && ( q1->getX() < (WINDOW_MAX_X/2 - q1->getWidth() - 10) ) ){
		q1->moveRight();
	}
	else q1->setRight(false);
	
	if(q3->getLeft() && q3->getX() > ( WINDOW_MAX_X/2 + 10 )){
		q3->moveLeft();
	}
	else q3->setLeft(false);
// SMASH the bottom two walls	
	if(q2->getRight() && ( q2->getX() < (WINDOW_MAX_X/2 - q2->getWidth() - 10) ) ){
		q2->moveRight();
	}
	else q2->setRight(false);
	
	if(q4->getLeft() && q4->getX() > ( WINDOW_MAX_X/2 + 10 )){
		q4->moveLeft();
	}
	else q4->setLeft(false);
// SMASH left two walls
	if(q1->getDown() && ( q1->getY() < (WINDOW_MAX_Y/2 - q1->getHeight() - 15) ) ){
		q1->moveDown();
	}
	else q1->setDown(false);
	
	if(q2->getUp() && q2->getY() > WINDOW_MAX_Y/2 + 15){
		q2->moveUp();
	}
	else q2->setUp(false);
// SMASH the right two walls
	if(q3->getDown() && ( q3->getY() < WINDOW_MAX_Y/2 - 241) ){
		q3->moveDown();
	}
	else q3->setDown(false);

	if(q4->getUp() && q4->getY() > ( WINDOW_MAX_Y/2 + 15 )){
		q4->moveUp();
	}
	else q4->setUp(false);
	/** Now bring em back after they collide */
// reset the top two walls
	if(!q1->getRight() && ( q1->getX() > -31 ) ){
			q1->moveLeft();
	}
	if(!q3->getLeft() && ( q3->getX() < 350 ) ){
			q3->moveRight();
	}
// reset the bottom 2 walls
	if(!q2->getRight() && ( q2->getX() > -31 ) ){
			q2->moveLeft();
	}
	if(!q4->getLeft() && ( q4->getX() < 350 ) ){
			q4->moveRight();
	}
// reset the left two walls
	if(!q1->getDown() && ( q1->getY() > -23 ) ){
			q1->moveUp();
	}
	if(!q2->getUp() && ( q2->getY() < 272 ) ){
			q2->moveDown();
	}
// reset the right two walls
// reset the left two walls
	if(!q3->getDown() && ( q3->getY() > -23 ) ){
			q3->moveUp();
	}
	if(!q4->getUp() && ( q4->getY() < 272 ) ){
			q4->moveDown();
	}
	/** Checks which bullets should be moving */
	for(unsigned int i = 0; i < bullets.size(); i++){
		if(bullets[i]->getDir() == 2){// move left
			bullets[i]->move(-1.2, 0);
		}
		else if(bullets[i]->getDir() == 3){// move right
			bullets[i]->move(1.2, 0);
		}
		else if(bullets[i]->getDir() == 0){// move up
			bullets[i]->move(0, -1.2);
		}
		else if(bullets[i]->getDir() == 1){// move down
			bullets[i]->move(0, 1.2);
		}
	}
/** Check for enemy collison with player */
	for(unsigned int i = 0; i < enemies.size(); i++){
		if(enemies[i]->collidesWithItem(q1, Qt::IntersectsItemShape) ||
		enemies[i]->collidesWithItem(q2, Qt::IntersectsItemShape) || 
		enemies[i]->collidesWithItem(q3, Qt::IntersectsItemShape) ||
		enemies[i]->collidesWithItem(q4, Qt::IntersectsItemShape) ){
			delete enemies[i];
			enemies.erase(std::find(enemies.begin(), enemies.end(), enemies[i]));
			killCount++;
		}
		else if(enemies[i]->collidesWithItem(player, Qt::IntersectsItemShape) ){
			delete enemies[i];
			enemies.erase(std::find(enemies.begin(), enemies.end(), enemies[i]));
			killCount++;
			player->setHealth(player->getHealth() - enemies[i]->getDamage());
			health->setWidth(player->getHealth()*1.2);
		}
	}
/** Check for bullet exiting the scene and collision with an enemy */
	for(unsigned int i = 0; i < bullets.size(); i++){
		if(bullets[i] && (bullets[i]->getX() <= -25 || bullets[i]->getX() > WINDOW_MAX_X +10||
		bullets[i]->getY() > WINDOW_MAX_Y+10 || bullets[i]->getY() < -25) ){
//			delete bullets[i];
		bullets[i]->setPos(-200, -200);
			bullets.erase(std::find(bullets.begin(), bullets.end(), bullets[i]));
		}
		if( bullets[i]->collidesWithItem(q1, Qt::IntersectsItemShape) ||
		bullets[i]->collidesWithItem(q2, Qt::IntersectsItemShape) || 
		bullets[i]->collidesWithItem(q3, Qt::IntersectsItemShape) ||
		bullets[i]->collidesWithItem(q4, Qt::IntersectsItemShape) ){
			bullets[i]->setPos(-200, -200);
			bullets.erase(std::find(bullets.begin(), bullets.end(), bullets[i]));
		}
		for(unsigned int j = 0; j < enemies.size(); j++){
			if(bullets[i]->collidesWithItem(enemies[j], Qt::IntersectsItemShape)){
				enemies[j]->setHealth(enemies[j]->getHealth() - bullets[i]->getDamage());
				bullets[i]->setPos(-200, -200);
//				delete bullets[i];
				bullets.erase(std::find(bullets.begin(), bullets.end(), bullets[i]));
				if(enemies[j]->getHealth() <= 0){
					delete enemies[j];
					enemies.erase(std::find(enemies.begin(), enemies.end(), enemies[j]));
					killCount++;
				}
			}
		}
	}
/** This if statement handles enemy spawning */
	if(gameTimer%300 == 0){// 
		int dir = rand()%4;
		cout << "Enemy counter " << killCount << endl;
		cout << "Enemy limit " << enemyLimit << endl;
		switch(dir){
		// right side
			case 0: { enemy = new Enemy(enemyIMG, WINDOW_MAX_X, WINDOW_MAX_Y/2-15, 32, 32, 32);
							enemy->setDamage(5);
							enemies.push_back(enemy);
							scene->addItem(enemy);
							break;
						}
		// left side
			case 1: { enemy = new Enemy(enemyIMG, 0, WINDOW_MAX_Y/2-20, 32, 32, 32);
							enemy->setDamage(5);
							enemies.push_back(enemy);
							scene->addItem(enemy);
							break;
						}
		// bottom
			case 2: { enemy = new Enemy(enemyIMG, WINDOW_MAX_X/2, WINDOW_MAX_Y+40, 32, 32, 32);
							enemy->setDamage(5);
							enemies.push_back(enemy);
							scene->addItem(enemy);
							break;
						}
		// top
			case 3: { enemy = new Enemy(enemyIMG, WINDOW_MAX_X/2, -20, 32, 32, 32);
							enemy->setDamage(5);
							enemies.push_back(enemy);
							scene->addItem(enemy);
							break;
						}
		}
	}
/** Handles enemy movement. Speed, etc */
	if(enemy && gameTimer%5 == 0){
//		std::cout << "Movee" << std::endl;
		for(unsigned int i = 0; i < enemies.size(); i++){
			if(!enemies[i]->getHunt())
				enemies[i]->move(WINDOW_MAX_X/2-15, WINDOW_MAX_Y/2-15);
			if(enemies[i]->getX() == WINDOW_MAX_X/2-15 && enemies[i]->getY() == WINDOW_MAX_Y/2-15){
				enemies[i]->setHunt(true);
			}
			if(enemies[i]->getHunt()){
				enemies[i]->move(player->getX(), player->getY());
			}
		}
	}
	if(killCount >= enemyLimit){// beginning of a new round
		if(seconds != 0) enemyLimit = ( ((rounds * 50)/seconds) - ( 100 - player->getHealth() ) );
		killCount = 0;
		seconds = 0;
		rounds++;
		rString.setNum(rounds);
		rNum->setText(rString);
	}
}

void MainWindow::shoot()
{
  valid = gameplay->mapFromGlobal(valid);
	p = gameplay->mapFromGlobal(QCursor::pos());
// y offset: 90, x: 55
	double sx = abs(player->getX()+50 - p.x());
	double sy = abs(player->getY()+80 - p.y());
	if(bullets.size() < 2){
		if( sy > sx && ( p.y() < player->getY()+80)){// shoot up
			valid = p;
			bullet = new BasicBullet(bbIMG, player->getX(), player->getY()-1, 16, 16, p.x(), p.y(), 1, 8);
			bullet->setDir(0);
			scene->addItem(bullet);
			bullets.push_back(bullet);
		}

		else if( sy > sx &&	( p.y() > player->getY()+80 ) ){// shoot down
			valid = p;
			bullet = new BasicBullet(bbIMG, player->getX(), player->getY()+1, 16, 16, p.x(), p.y(), 1, 8);
			bullet->setDir(1);
			scene->addItem(bullet);
			bullets.push_back(bullet);
		}
		else if( sx > sy && (p.x() < player->getX()+55 ) ){// shoot left
			valid = p;
			bullet = new BasicBullet(bbIMG, player->getX()-1, player->getY(), 16, 16, p.x(), p.y(), 1, 8);
			bullet->setDir(2);
			scene->addItem(bullet);
			bullets.push_back(bullet);
		}
		else if( sx > sy && ( p.x() > player->getX()+55) ){// shoot right
			valid = p;
			bullet = new BasicBullet(bbIMG, player->getX()+1, player->getY(), 16, 16, p.x(), p.y(), 1, 8);
			bullet->setDir(3);
			scene->addItem(bullet);
			bullets.push_back(bullet);
		}
	}
}

void MainWindow::toggleTimer(){
	if(timer->isActive()) timer->stop();

	else timer->start();
}
/** This power may be activated about once a round to effectively clear a lane of enemies */
void MainWindow::SMASH()
{
	p = gameplay->mapFromGlobal(QCursor::pos());
	if( ( p.y() <=  273) && (p.x() > 320 && p.x() < 384 ) ){// up alley
		q1->setRight(true);
		q3->setLeft(true);
	}
	else if(	( p.y() > 338 && (p.x() > 320 && p.x() < 384 ) ) ){// down alley
		q2->setRight(true);
		q4->setLeft(true);
	}
	else if( (p.x() < 321 && ( p.y() < 340 && p.y() > 270 ) ) ){// left alley
		q1->setDown(true);
		q2->setUp(true);
	}
	else if( ( p.x() > 380 && ( p.y() < 340 && p.y() > 270 ) ) ){// right alley
		q3->setDown(true);
		q4->setUp(true);
	}
}

MainWindow::MainWindow()
{
	/** Define some colors */
	QBrush black(Qt::black);
	QBrush white(Qt::white);
	QBrush red(Qt::red);
	srand(p.x());
	
	/** Initialize gameplay and scene */
	scene = new QGraphicsScene(0, -40, WINDOW_MAX_X, WINDOW_MAX_Y, this);
//	scene->setSceneRect(0, 0, WINDOW_MAX_X*1.1, WINDOW_MAX_Y*1.1);
	gameplay = new Gameplay(scene, this);
	
	/** Configure gameplay settings */
  gameplay->setFixedSize(WINDOW_MAX_X*1.1, WINDOW_MAX_Y*1.1);
  gameplay->setWindowTitle("Binary Defender");
  
  /** Configure Cursor */
  p = QWidget::mapFromGlobal(p);
  valid = QWidget::mapFromGlobal(valid);
  
	/** Initizlize and set up the play area dummy rectangle that registers clicks */
	area = new PlayArea(-0.05*WINDOW_MAX_X, -0.05*WINDOW_MAX_Y, WINDOW_MAX_X*1.1, WINDOW_MAX_Y*1.8, this);
	// -0.05, -0.08
//	area->setPen(Qt::NoPen);

	/** Sets up SMASH power */
	SMASHcount = 5;
	/** Set up rounds */
	rounds = 1;
	rString = "Round";
	ROUND = new QGraphicsSimpleTextItem;
	ROUND->setText(rString);
	ROUND->setPos(WINDOW_MAX_X/2-20, -62);
	rString.setNum(rounds);
	rNum = new QGraphicsSimpleTextItem;
	rNum->setText(rString);// add a string here
	rNum->setPos(WINDOW_MAX_X/2, -45);
	
	/** Set up score */
	score = 0;

	/** Set up the paths the enemies will traverse */
	// double nx, double ny, double w, double h, int vx, int vy
	q1 = new GameObject(-31, -23, 320, 230, 0, 0);
	q1->setBrush(black);
	q2 = new GameObject(-31, 272, 320, 230, 0, 0);
	q2->setBrush(black);
	q3 = new GameObject(350, -23, 320, 230, 0, 0);
	q3->setBrush(black);
	q4 = new GameObject(350, 272, 320, 230, 0, 0);
	q4->setBrush(black);
	
	/** Initialize timer that will keep the time of the scene */
	timer = new QTimer(this);
	timer->setInterval(5);
	seconds = 0;

	/** Initialize a pixmap for the player and a test AbstractObject */
	playerIMG = new QPixmap("player.png", "png", Qt::AutoColor);
	player = new Player(playerIMG, WINDOW_MAX_X/2-10, WINDOW_MAX_Y/2-10, 72, 72, 100);
	player->setTransformOriginPoint(player->getX()+40, player->getY() + 45);
	gameplay->mapFromGlobal(player->pos().toPoint());
	
	/** Initialize the health bar */
	health = new HealthBar(-25, -42, 140, 16, 0, 0, player->getHealth());
	health->setBrush(red);
	health->setPen(Qt::NoPen);
	healthOutline = new GameObject(health->getX(), health->getY(), health->getWidth(), 16, 0, 0);
	healthOutline->setBrush(Qt::NoBrush);
	
	/** Initialize and set up the enemies */
	enemyIMG = new QPixmap("enemy_0.png", "png", Qt::AutoColor);
	enemy = NULL;
	killCount = 0;
	enemyLimit = 5;
	
	/** Create an image for the BasicBullet */
	bbIMG = new QPixmap("basic_bullet.png", "png", Qt::AutoColor);
	bullet = NULL;
	
	/** Add items to the scene */
	scene->addItem(area);
	scene->addItem(player); objects.push_back(player);
	scene->addItem(q1);
	scene->addItem(q2);
	scene->addItem(q3);
	scene->addItem(q4);
	scene->addItem(health);
	scene->addItem(healthOutline);
	scene->addItem(ROUND);
	scene->addItem(rNum);
	
	/** Game Events, or connections */
	connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
}

void MainWindow::movePlayer(std::string dir)
{
	if(dir == "up")
		player->setDir(0);
	else if(dir == "down")
		player->setDir(1);
	else if(dir == "left")
		player->setDir(2);
	else if(dir == "right")
		player->setDir(3);
	else
		player->setDir(-1);
}

void MainWindow::show() {
	timer->start();
	gameplay->show();
}

MainWindow::~MainWindow()
{
	timer->stop();
}

