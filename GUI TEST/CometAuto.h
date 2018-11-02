#pragma once
#include "CometMain.h"
class CometAuto : public CometMain
{
public:
	CometAuto();
	CometAuto(std::string infile, std::string outfile);
	void DrawShapes();
	void FindHead();
	void FindTail();
	int CheckIfInBounds();
	void FindHeadRadius();
	void ImgShow();
	void findNewHead();
	void checkMouseRead(int evt, int x, int y);
	void checkMouseDeselect(int evt, int x, int y);
	static void CallBackFunction(int evt, int x, int y, int flags, void* prarm);
	void create3DImage();
private:
	bool deselect = false, read = true;
};

