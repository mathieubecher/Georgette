#pragma once
#include "Physic2D.h"
#define SIZEW 80
#define SIZEH 40
#include <list>
#define WALL -1

/**
 * Format of the map ;
 * right contains the level of the right height ; helps to generate matching adjacent chunks
 * top and bottom contains if there is a way to go up/down (hole + stairs)
 */
struct GenFormat
{
public:
	// WALL = -1, for right & left it means there is a wall
	int right;
	int left;
	bool top;
	bool bottom;

	bool MatchingLeft(GenFormat const &other) {
		return this->left == other.right;
	}
	bool MatchingRight(GenFormat const &other) {
		return this->right == other.left;
	}
	bool MatchingTop(GenFormat const &other) {
		return this->top && other.bottom;
	}
	bool MatchingBottom(GenFormat const &other) {
		return this->bottom && other.top;
	}

	GenFormat() {
		right = -1;
		left = -1;
		top = false;
		bottom = false;
	}
};

struct CaseSave {
public :
	CaseSave(int x, int y, char c): x(x),y(y),c(c) {}
	int x;
	int y;
	char c;
};

class Map: public Physic2D
{
protected :
	std::list<CaseSave> casesSave;


public:
	~Map();
	static Map *originalChunk;
	GenFormat format;
	void Update();
	void ActionCase(CaseSave c);
	void AddForce(CHAR_INFO & c, float force);
	Map(CHAR_INFO *sprite, int x, int y, int width = SIZEW, int height = SIZEH);

	Box Collider(Vector2f pos, Vector2 size);

	std::list<CHAR_INFO*> CollideCase(Vector2f pos, Vector2 size);

	Map(std::string file, int x = 0, int y = 0, int width = 1, int height = 1);
	static float CharToBreakIndicator(char c);
	static char BreakIndicatorToChar(float i);
	virtual bool IsHouse();
	void DeleteObj();
};