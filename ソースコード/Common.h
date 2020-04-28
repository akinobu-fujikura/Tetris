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
	int bx;		/* �u���b�N�̈ʒu */
	int by;
	int shape;	/* �u���b�N�̌`(�F) */
public:
	Block(int, int, int);
	~Block();    // �G���[�|�C���g ~
	int GetX() { return bx; }		/* ������1 */
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
	int tx;			/* �e�g���X�̈ʒu */
	int ty;
	Block *block[nBLOCK];		/* ������2 */ /* ������3 */

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
class Map{   //�G���[�|�C���g ;
private:
	Block *map[XMAX][YMAX];
	int lineCount[YMAX];	/* n�s�ڂɂ���u���b�N�̐� */
public:				    	/* ���ꂪXMAX�ɂȂ�Ƃ��̍s�͏����� */
	Map();
	~Map() {};
	int PutOn(Block*);
	int IsVacant(int, int);
	void ReDraw();
	int DropLine();
};

#endif

