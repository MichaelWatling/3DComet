#pragma once
#include "CometAuto.h"
#include "CometManual.h"
#include <Windows.h>




namespace GUITEST {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	CometAuto newComet;
	CometManual newComet2;
	bool CA = false;
	/// <summary>
	/// Summary for GUITESTFORM
	/// </summary>
	public ref class GUITESTFORM : public System::Windows::Forms::Form
	{
	public:
		GUITESTFORM(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUITESTFORM()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  imgLoadText;
	protected:
	private: System::Windows::Forms::Button^  imgLoadButton;
	private: System::Windows::Forms::Button^  LoadManual;
	private: System::Windows::Forms::TextBox^  saveText;
	private: System::Windows::Forms::Label^  label1;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->imgLoadText = (gcnew System::Windows::Forms::TextBox());
			this->imgLoadButton = (gcnew System::Windows::Forms::Button());
			this->LoadManual = (gcnew System::Windows::Forms::Button());
			this->saveText = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// imgLoadText
			// 
			this->imgLoadText->Location = System::Drawing::Point(11, 22);
			this->imgLoadText->Name = L"imgLoadText";
			this->imgLoadText->Size = System::Drawing::Size(215, 22);
			this->imgLoadText->TabIndex = 0;
			this->imgLoadText->Text = L"Input File Name";
			// 
			// imgLoadButton
			// 
			this->imgLoadButton->Location = System::Drawing::Point(11, 75);
			this->imgLoadButton->Name = L"imgLoadButton";
			this->imgLoadButton->Size = System::Drawing::Size(104, 23);
			this->imgLoadButton->TabIndex = 1;
			this->imgLoadButton->Text = L"Load Auto";
			this->imgLoadButton->UseVisualStyleBackColor = true;
			this->imgLoadButton->Click += gcnew System::EventHandler(this, &GUITESTFORM::imgLoadButton_Click);
			// 
			// LoadManual
			// 
			this->LoadManual->Location = System::Drawing::Point(121, 75);
			this->LoadManual->Name = L"LoadManual";
			this->LoadManual->Size = System::Drawing::Size(105, 23);
			this->LoadManual->TabIndex = 2;
			this->LoadManual->Text = L"Load Manual";
			this->LoadManual->UseVisualStyleBackColor = true;
			this->LoadManual->Click += gcnew System::EventHandler(this, &GUITESTFORM::LoadManual_Click);
			// 
			// saveText
			// 
			this->saveText->Location = System::Drawing::Point(11, 50);
			this->saveText->Name = L"saveText";
			this->saveText->Size = System::Drawing::Size(214, 22);
			this->saveText->TabIndex = 3;
			this->saveText->Text = L"Output File Name";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(8, 113);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(221, 153);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Controls:\r\nq = Quit\r\nr = Read\r\nd = Deselect\r\nm = Model Save\r\nManual Specific Cont"
				L"rols:\r\na = Add Head\r\nT= Add Tail\r\n(To finish adding press R to read)";
			this->label1->Click += gcnew System::EventHandler(this, &GUITESTFORM::label1_Click);
			// 
			// GUITESTFORM
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(250, 318);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->saveText);
			this->Controls->Add(this->LoadManual);
			this->Controls->Add(this->imgLoadButton);
			this->Controls->Add(this->imgLoadText);
			this->Name = L"GUITESTFORM";
			this->Text = L"3DComet";
			this->Load += gcnew System::EventHandler(this, &GUITESTFORM::GUITESTFORM_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void GUITESTFORM_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void imgLoadButton_Click(System::Object^  sender, System::EventArgs^  e) {

		String ^ in = imgLoadText->Text;
		char cString[50] = { 0 };
		sprintf(cString, "%s", in);
		std::string loadString(cString);

		in = saveText->Text;
		sprintf(cString, "%s", in);
		std::string saveString(cString);

		CA = true;
		newComet = CometAuto(loadString, saveString);
		
	}
	private: System::Void saveButton_Click(System::Object^  sender, System::EventArgs^  e) {
		
		
	}
private: System::Void saveButton_Click_1(System::Object^  sender, System::EventArgs^  e) {
	
}
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void LoadManual_Click(System::Object^  sender, System::EventArgs^  e) {
	String ^ in = imgLoadText->Text;
	char cString[50] = { 0 };
	sprintf(cString, "%s", in);
	std::string loadString(cString);

	in = saveText->Text;
	sprintf(cString, "%s", in);
	std::string saveString(cString);

	CA = true;
	newComet2 = CometManual(loadString, saveString);
}
};
}
