// COMMON.H
#define XMAX 		10 
#define YMAX 		25
#define XLEFT 		10
#define YTOP 		10
#define blWIDTH 	16
#define blHIGHT 	16
#define msWIDTH 	40
#define LEFT  		-1,0
#define RIGHT  		1,0
#define DOWN  		0,1
#define DRAW   		0,0
#define NO  		0
#define YES 		1
#define nBLOCK 		4
#define IDLE		0
#define PLAYING		1
#define TOUCHED 	2
#define BLACK 0x00000000
#define GRAY 0x00afafaf
#define graphicView ((CTetrisSDIView *)((CFrameWnd *)AfxGetApp()->m_pMainWnd)->GetActiveView())
#ifndef	_TETRIS_H
#define	_TETRIS_H

// BLOCK
class Block {
private:
	int bx;		/* ブロックの位置 */
	int by;
	int shape;	/* ブロックの形(色) */
public:
	Block(int, int, int);
	~Block();    // エラーポイント ~
	int GetX() { return bx; }		/* 穴埋め1 */
	int GetY() { return by; }
	void Erase();
	int CanMove(int, int);
	void Move(int, int);
	int CanTurn(int, int);
	void Turn(int, int);
	void ReDraw();
};


// TETRIS
class Tetris {
private:
	int shape;
	int tx;			/* テトリスの位置 */
	int ty;
	Block *block[nBLOCK];		/* 穴埋め2 */ /* 穴埋め3 */

public:
	Tetris();
	~Tetris();
	void Erase();
	int Enter();
	void ReDraw();
	int  Move(int, int);
	int  Turn();
};

//  MAP
class Map{   //エラーポイント ;
private:
	Block *map[XMAX][YMAX];
	int lineCount[YMAX];	/* n行目にあるブロックの数 */
public:				    	/* これがXMAXになるとその行は消える */
	Map();
	~Map() {};
	int PutOn(Block*);
	int IsVacant(int, int);
	void ReDraw();
	int DropLine();
};

#endif

