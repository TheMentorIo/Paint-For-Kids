#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();		
	
	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar

	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	bool isValid(Point p,double ly=0,double lx=0)const;
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;				//Draw a Rectangle
	void DrawSquare(Point P1, GfxInfo SquareGfxInfo, bool selected = false) const;					//Draw a Square
	void DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo, bool selected = false) const;	//Draw a Triangle
	void DrawHex(Point P1, GfxInfo HexGfxInfo, bool selected = false) const;						//Draw a Hexagon
	void DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected = false) const;		//Draw a Circle
	
	//added functions by beshoy
	void testtoolbar(Point p); //function for testing 
	void tochangecolor(Point p1, Point p2); //changing filling color
	void picK(Point p1, Point p2, int& choise);  //pick for play mode
	void flag(Point p); //point flag just for phase one
	void chooswdrawcolor(Point p); //change drawcolor
	void drawshape(Point p); //draw shapes ("u sont need function flag")
	void isFilled();
	///Make similar functions for drawing all other figure types.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width

	
	~Output();
};

#endif