#ifndef BASIC_BULLET_H
#define BASIC_BULLET_H

#include "abstract_object.h"

class BasicBullet : public AbstractObject
{
	public:
		BasicBullet(QPixmap *pm, double nx, double ny, double w, double h, int vx, int vy, int hp, int d);
		~BasicBullet();
		void move(double vx, double vy);// double vx, double vy
		int getDamage();
		void setInEnemy(bool b);
		bool getInEnemy();
		/** Subtracts 1 from strikeCount */
		void decStrike();
		int getStrike();
		
	protected:
		/** How many enemies the bullet has gone through */
		int strikeCount;
		/** If true, bullet is intersecting with an enemy */
		bool inEnemy;
		double initX;
		double initY;
		int finX;
		int finY;
		int damage;
};

#endif
