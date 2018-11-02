#include "GUITESTFORM.h"
#include <stdlib.h>
using namespace System;
using namespace System::Windows::Forms;


[STAThreadAttribute]
int main(array<String^>^ args) {
	system("Color F3");
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GUITEST::GUITESTFORM form;
	Application::Run(%form);
	return 0;
}
