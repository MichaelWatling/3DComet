#pragma once
#include "CometMain.h"
class CometManual :
	public CometMain
{
public:
	CometManual();
	CometManual(std::string infile, std::string outfile);
	void checkMouseAdd(int evt, int x, int y);
	static void CallBackFunction(int evt, int x, int y, int flags, void* prarm);
	void checkMouseRead(int evt, int x, int y);
	void checkMouseDeselect(int evt, int x, int y);
	void checkMouseAddTail(int evt, int x, int y);
	void create3DImage();
	void FindTail();
	void FindHeadRadius();
	void ImgShow();
	
private:
	bool read = false, deselect = false, add = true, addTail = false;
	int rad;
	
};

