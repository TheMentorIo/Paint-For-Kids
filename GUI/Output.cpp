#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 80;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
int iffirsttime = 0;//to draw the colors icon first time 

void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem

	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SWITCH1] = "images\\MenuItems\\switch.jpg";
	MenuItemImages[ITM_UNDO] = "images\\MenuItems\\undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\MenuItems\\redo.jpg";
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\rect.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\circle.jpg";
	MenuItemImages[ITM_SQUARE] = "images\\MenuItems\\square.jpg";
	MenuItemImages[ITM_TRIANGLE] = "images\\MenuItems\\triangle.jpg";
	MenuItemImages[ITM_HEX] = "images\\MenuItems\\hex.jpg";
	MenuItemImages[ITM_COLOR] = "images\\MenuItems\\color.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\move.jpg";
	MenuItemImages[ITM_DELETE] = "images\\MenuItems\\trash.jpg";
	MenuItemImages[ITM_CLEAR] = "images\\MenuItems\\clear.jpg";
	MenuItemImages[ITM_SAVEGRAPH] = "images\\MenuItems\\save.jpg";
	MenuItemImages[ITM_LOADGRAPH] = "images\\MenuItems\\load.jpg";
	MenuItemImages[ITM_RECORD] = "images\\MenuItems\\record.jpg";
	MenuItemImages[ITM_STOP] = "images\\MenuItems\\stop.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 50;
	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);


	string y = "images\\MenuItems\\continue.jpg";
	pWind->DrawImage(y, 900, 0, 100, 49);
	if (iffirsttime == 0)  //to draw the colors icon first time
	{
		string fill = "images\\MenuItems\\no.jpg";
		string colorsimage = "images\\MenuItems\\drawcolors.jpg";
		pWind->DrawImage(colorsimage, 1050, 0, 120, 48);
		pWind->DrawImage(fill, 1200, 0, 30, 30);
		iffirsttime++;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu

	string MenuItemImage[PLAY_ITM_COUNT];
	MenuItemImage[ITM_SWITCH2] = "images\\MenuItems\\switch.jpg";
	MenuItemImage[ITM_PICK] = "images\\MenuItems\\pick.jpg";

	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImage[i], i * 50, 0, 50, 50);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
bool Output::isValid(Point p,double ly ,double lx)const
{
	return (p.y > UI.ToolBarHeight+ly && p.y<UI.height-UI.StatusBarHeight-ly && p.x>0+lx &&p.x<UI.width-lx);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	if (isValid(P1) && isValid(P2)) {
		color DrawingClr;
		if (selected)
			DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
		else
			DrawingClr = RectGfxInfo.DrawClr;

		pWind->SetPen(DrawingClr, 1);
		drawstyle style;
		if (RectGfxInfo.isFilled)
		{
			style = FILLED;
			pWind->SetBrush(RectGfxInfo.FillClr);
		}
		else
			style = FRAME;


		pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	}
	return;
}

void Output::DrawSquare(Point P1, GfxInfo SquareGfxInfo, bool selected) const
{
	double length = 65;
	if (isValid(P1,length/2,length/2)) {
		color DrawingClr;
		if (selected)
			DrawingClr = UI.HighlightColor;
		else
			DrawingClr = SquareGfxInfo.DrawClr;

		pWind->SetPen(DrawingClr, 1);
		drawstyle style;
		if (SquareGfxInfo.isFilled)
		{
			style = FILLED;
			pWind->SetBrush(SquareGfxInfo.FillClr);
		}
		else
			style = FRAME;
		pWind->DrawRectangle(P1.x - length, P1.y - length, P1.x + length, P1.y + length, style);
	}
	return;
}

void Output::DrawTri(Point P1, Point P2, Point P3, GfxInfo TritGfxInfo, bool selected) const
{ 
	color DrawingClr;
	drawstyle style;
	if(isValid(P1) && isValid(P2) && isValid(P3))
	{
		if (selected)
			DrawingClr = UI.HighlightColor;
		else
			DrawingClr = TritGfxInfo.DrawClr;
		pWind->SetPen(DrawingClr, 1);
		if (TritGfxInfo.isFilled)
		{
			style = FILLED;
			pWind->SetBrush(TritGfxInfo.FillClr);
		}
		else
			style = FRAME;
		pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
	}
	else
	{
		return;
	}
}

void Output::DrawHex(Point P1, GfxInfo HexGfxInfo, bool selected) const
{
	long double l = 150;
	if (isValid(P1, sqrt(3) * l / 2.0,l+10))
	{
	color DrawingClr;
	drawstyle style;
	int x[6] = { P1.x - l / 2,P1.x + l / 2,P1.x + l,P1.x + l / 2,P1.x - l / 2,P1.x - l };
	int y[6] = { P1.y - sqrt(3) * l / 2.0, P1.y - sqrt(3) * l / 2.0,P1.y,P1.y + sqrt(3) * l / 2.0, P1.y + sqrt(3) * l / 2.0, P1.y };
	if (selected)
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = HexGfxInfo.DrawClr;
	pWind->SetPen(DrawingClr, 1);
	if (HexGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexGfxInfo.FillClr);
	}
	else style = FRAME;
	pWind->DrawPolygon(x, y, 6, style);
	}
}

void Output::DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected) const
{
	double radius = sqrt(pow((P1.x - P2.x), 2) + pow((P1.y - P2.y), 2));
	if (isValid(P1,radius,radius) && isValid(P2)) {
		color DrawingClr;
		if (selected)
			DrawingClr = UI.HighlightColor;
		else
			DrawingClr = CircleGfxInfo.DrawClr;

		pWind->SetPen(DrawingClr, 1);
		drawstyle style;
		if (CircleGfxInfo.isFilled)
		{
			style = FILLED;
			pWind->SetBrush(CircleGfxInfo.FillClr);
		}
		else
			style = FRAME;
		pWind->DrawCircle(P1.x, P1.y, radius, style);
	}
	return;
}

int z = 0; //to know the mode
//z is odd play
//z is even draw
bool isfilled = false;
void Output::testtoolbar(Point p)
{
	Point p2;
	p2.x = 0;
	p2.y = 0;
	if (p.x <= 50 && p.y <= 50)
	{
		string x = "images\\MenuItems\\white.jpg";
		pWind->DrawImage(x, 0, 0, 17 * 50, 50);
		if (z % 2 == 0)
			CreatePlayToolBar();
		else
			CreateDrawToolBar();
		z++;
	}
	if (z % 2 == 0 && p.x <= 450 && p.x >= 400 && p.y <= 50)
	{
		tochangecolor(p, p2);
	}
	if (z % 2 == 1)
	{
		if (p.x >= 50 && p.x <= 100 && p.y <= 50)
		{
			int choise = 0;
			picK(p, p2, choise);

		}
	}
	if (p.x > 1050 && p.x < 1170 && p.y < 48)
	{
		chooswdrawcolor(p);
	}
	//shapes

	if (z % 2 == 0 && p.y < 50 && p.x <= 350 && p.x >= 150)
	{
		drawshape(p);
	}
	//filling
	if (p.y < 30 && p.x > 1200 && p.x < 1230)
	{
		isFilled();
	}
}

void Output::tochangecolor(Point p1, Point p2)
{
	string colors[6];
	colors[orange] = "images\\MenuItems\\orange.jpg";
	colors[red] = "images\\MenuItems\\red.jpg";
	colors[green] = "images\\MenuItems\\green.jpg";
	colors[blue] = "images\\MenuItems\\blue.jpg";
	colors[yellow] = "images\\MenuItems\\yellow.jpg";
	colors[black] = "images\\MenuItems\\black.jpg";
	for (int i = 0; i < 6; i++)
		pWind->DrawImage(colors[i], (i + 1) * 50 + 400, 0, 50, 50);
	string white = "images\\MenuItems\\white.jpg";
	pWind->DrawImage(white, 750, 0, 250, 50);
	pWind->WaitMouseClick(p2.x, p2.y);
	if (p2.x >= 450 && p2.x <= 500 && p2.y <= 50)
		UI.FillColor = ORANGE;
	else if (p2.x >= 500 && p2.x <= 550 && p2.y <= 50)
		UI.FillColor = RED;
	else if (p2.x >= 550 && p2.x <= 600 && p2.y <= 50)
		UI.FillColor = GREEN;
	else if (p2.x >= 600 && p2.x <= 650 && p2.y <= 50)
		UI.FillColor = BLUE;
	else if (p2.x >= 650 && p2.x <= 700 && p2.y <= 50)
		UI.FillColor = YELLOW;
	else if (p2.x >= 700 && p2.x <= 750 && p2.y <= 50)
		UI.FillColor = BLACK;

	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_COLOR] = "images\\MenuItems\\color.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\move.jpg";
	MenuItemImages[ITM_DELETE] = "images\\MenuItems\\trash.jpg";
	MenuItemImages[ITM_CLEAR] = "images\\MenuItems\\clear.jpg";
	MenuItemImages[ITM_SAVEGRAPH] = "images\\MenuItems\\save.jpg";
	MenuItemImages[ITM_LOADGRAPH] = "images\\MenuItems\\load.jpg";
	MenuItemImages[ITM_RECORD] = "images\\MenuItems\\record.jpg";
	MenuItemImages[ITM_STOP] = "images\\MenuItems\\stop.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\exit.jpg";
	for (int i = 8; i < 17; i++)
		pWind->DrawImage(MenuItemImages[i], i * 50, 0, 50, 50);
	string y = "images\\MenuItems\\continue.jpg";
	pWind->DrawImage(y, 900, 0, 100, 49);
}

void Output::picK(Point p1, Point p2, int& choise)
{
	string choose[5];
	string choosecolor[6];

	choosecolor[orange] = "images\\MenuItems\\orange.jpg";
	choosecolor[red] = "images\\MenuItems\\red.jpg";
	choosecolor[green] = "images\\MenuItems\\green.jpg";
	choosecolor[blue] = "images\\MenuItems\\blue.jpg";
	choosecolor[yellow] = "images\\MenuItems\\yellow.jpg";
	choosecolor[black] = "images\\MenuItems\\black.jpg";

	choose[0] = "images\\MenuItems\\rect.jpg";
	choose[1] = "images\\MenuItems\\circle.jpg";
	choose[2] = "images\\MenuItems\\square.jpg";
	choose[3] = "images\\MenuItems\\triangle.jpg";
	choose[4] = "images\\MenuItems\\hex.jpg";

	for (int i = 0; i < 5; i++)
		pWind->DrawImage(choose[i], 100 + 50 * i, 0, 50, 50);
	pWind->WaitMouseClick(p2.x, p2.y);

	while (choise == 0)
	{
		if (p2.x >= 100 && p2.x <= 150 && p2.y <= 50)
			choise = 10;
		else if (p2.x >= 150 && p2.x <= 200 && p2.y <= 50)
			choise = 20;
		else if (p2.x >= 200 && p2.x <= 250 && p2.y <= 50)
			choise = 30;
		else if (p2.x >= 250 && p2.x <= 300 && p2.y <= 50)
			choise = 40;
		else if (p2.x >= 300 && p2.x <= 350 && p2.y <= 50)
			choise = 50;
	}

	for (int i = 0; i < 6; i++)
		pWind->DrawImage(choosecolor[i], 100 + 50 * i, 0, 50, 50);
	//pWind->WaitMouseClick(p2.x, p2.y);

	while (choise % 10 == 0)
	{
		pWind->WaitMouseClick(p2.x, p2.y);
		if (p2.x >= 100 && p2.x <= 150 && p2.y <= 50)
			choise += 1;
		else if (p2.x >= 150 && p2.x <= 200 && p2.y <= 50)
			choise += 2;
		else if (p2.x >= 200 && p2.x <= 250 && p2.y <= 50)
			choise += 3;
		else if (p2.x >= 250 && p2.x <= 300 && p2.y <= 50)
			choise += 4;
		else if (p2.x >= 300 && p2.x <= 350 && p2.y <= 50)
			choise = +5;
		else if (p2.x >= 350 && p2.x <= 400 && p2.y <= 50)
			choise = +6;
		else if (p2.x <= 50 && p2.y <= 50)
		{
			string x = "images\\MenuItems\\white.jpg";
			pWind->DrawImage(x, 0, 0, 17 * 50, 50);
			if (z % 2 == 0)
				CreatePlayToolBar();
			else
				CreateDrawToolBar();
			z++;
			break;
		}
		else if (p2.x >= 900 && p2.x <= 1000 && p2.y <= 50 && p2.y >= 0) break;
		else if (p2.x > 0 && p2.y > 50) continue;
		else continue;
	}
	string white = "images\\MenuItems\\white.jpg";
	pWind->DrawImage(white, 100, 0, 400, 50);
}

void Output::flag(Point p)
{
	if (p.y <= 50)
		testtoolbar(p);
}

void Output::chooswdrawcolor(Point p)
{
	string drawcolors[] = { "images\\MenuItems\\blackdraw.jpg",
		"images\\MenuItems\\reddraw.jpg",
		"images\\MenuItems\\orangedraw.jpg",
		"images\\MenuItems\\bluedraw.jpg",
		"images\\MenuItems\\greendraw.jpg",
		"images\\MenuItems\\yellowdraw.jpg" };

	if (p.y < 24 && p.x>1050 && p.x < 1090)
	{
		pWind->DrawImage(drawcolors[0], 1050, 0, 120, 48);
		UI.DrawColor = BLACK;
	}
	else if (p.y < 24 && p.x>1090 && p.x < 1130)
	{
		pWind->DrawImage(drawcolors[1], 1050, 0, 120, 48);
		UI.DrawColor = RED;
	}
	else if (p.y < 24 && p.x>1130 && p.x < 1170)
	{
		pWind->DrawImage(drawcolors[2], 1050, 0, 120, 48);
		UI.DrawColor = ORANGE;
	}
	else if (p.y < 48 && p.y > 24 && p.x > 1050 && p.x < 1090)
	{
		pWind->DrawImage(drawcolors[3], 1050, 0, 120, 48);
		UI.DrawColor = BLUE;
	}
	else if (p.y < 48 && p.y > 24 && p.x > 1090 && p.x < 1130)
	{
		pWind->DrawImage(drawcolors[4], 1050, 0, 120, 48);
		UI.DrawColor = GREEN;
	}
	else if (p.y < 48 && p.y > 24 && p.x > 1130 && p.x < 1170)
	{
		pWind->DrawImage(drawcolors[5], 1050, 0, 120, 48);
		UI.DrawColor = YELLOW;
	}

}

void Output::drawshape(Point p)
{
	Point shape1;
	Point shape2;
	GfxInfo drawinfo;
	bool out = false; //if switch modes
	if (p.y < 50 && p.x <= 250 && p.x >= 150)
	{
		while (1)
		{
			pWind->WaitMouseClick(shape1.x, shape1.y);
			while (shape1.y < 50)
			{
				testtoolbar(shape1);
				if (shape1.x < 50) out = true;
				pWind->WaitMouseClick(shape1.x, shape1.y);
			}
			pWind->WaitMouseClick(shape2.x, shape2.y);
			while (shape2.y < 50)
			{
				testtoolbar(shape2);
				if (shape2.x < 50) out = true;
				pWind->WaitMouseClick(shape1.x, shape1.y);
				while (shape1.y < 50)
				{
					testtoolbar(shape1);
					if (shape1.x < 50) out = true;
					pWind->WaitMouseClick(shape1.x, shape1.y);

				}
				pWind->WaitMouseClick(shape2.x, shape2.y);
			}
			if (out) break;
			drawinfo.BorderWdth = 5;
			drawinfo.DrawClr = UI.DrawColor;	//any color for border
			if (isfilled)
			{
				drawinfo.FillClr = UI.FillColor;//any color for filling
				drawinfo.isFilled = true;
			}
			else
			{
				drawinfo.isFilled = false;
			}
			DrawRect(shape1, shape2, drawinfo, false);
		}
	}


}

void Output::isFilled()
{

	if (isfilled)
	{
		string fill = "images\\MenuItems\\no.jpg";
		pWind->DrawImage(fill, 1200, 0, 30, 30);
	}
	else
	{
		string fill = "images\\MenuItems\\yes.jpg";
		pWind->DrawImage(fill, 1200, 0, 30, 30);
	}
	bool tmp = isfilled;
	isfilled = !tmp;


}




//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

