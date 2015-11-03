#pragma once

#include <cv.h>
#include <highgui.h>
#include <time.h>
#include <math.h>
#include "ImageProcessor.h"
#include "config.h"
#include "GUIUtils.h"

using namespace std;

namespace KGPVisionGUI 
{
  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;
  using namespace System::IO;

    CvCapture *cap;
    IplImage *frame,*HSVframe,*BinImage,*BlankImage,*staticImg,*blobImg;
  /// <summary>
  /// Summary for Form1
  ///
  /// WARNING: If you change the name of this class, you will need to change the
  ///          'Resource File Name' property for the managed resource compiler tool
  ///          associated with all .resx files this class depends on.  Otherwise,
  ///          the designers will not be able to interact properly with localized
  ///          resources associated with this form.
  /// </summary>
  public ref class Form1 : public System::Windows::Forms::Form
  {
  public:
    Form1(void)
    {
      InitializeComponent();
      vision = new ImageProcessor(Point2D(1,1),Point2D(CamView->Width - 1,CamView->Height - 1));
      vision->markerSize = markerSizetrckbar->Value;
      File ^f ;
      if(!f->Exists("ColorParameters.txt"))
        this->loadbtn->Enabled = false;
    }
  private : 
    long lastClock;
    ImageProcessor * vision;
    char activeColor;
  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~Form1()
    {
      if (components)
      {
        delete components;
      }
    }
    private: System::Windows::Forms::PictureBox^  CamView;
    protected: 

  protected: 

  protected: 

  private: System::Windows::Forms::Button^  StopCatureButton;

  private: System::Windows::Forms::Button^  StartCaptureButton;
  private: System::Windows::Forms::Timer^  CamUpdateTimer;

  private: System::Windows::Forms::Label^  FPSCOUNTER;
  private: System::Windows::Forms::Label^  label12;


  private: System::Windows::Forms::GroupBox^  groupBox2;
  private: System::Windows::Forms::RadioButton^  BlobMode;
  private: System::Windows::Forms::RadioButton^  ThresholdMode;


  private: System::Windows::Forms::Button^  drivepwm;
  private: System::Windows::Forms::Label^  label13;
  private: System::Windows::Forms::Label^  label14;
  private: System::Windows::Forms::Label^  label15;
  private: System::Windows::Forms::TrackBar^  pwm3trackBar;
  private: System::Windows::Forms::TrackBar^  pwm2trackBar;
  private: System::Windows::Forms::TrackBar^  pwm1trackBar;
  private: System::Windows::Forms::CheckBox^  checkBox1;
  private: System::Windows::Forms::CheckBox^  checkBox2;
  private: System::Windows::Forms::CheckBox^  checkBox3;
  private: System::Windows::Forms::TrackBar^  utrackBar;
  private: System::Windows::Forms::Button^  drive_btn;
  private: System::Windows::Forms::Label^  ubtn;
  private: System::Windows::Forms::Label^  vbtn;
  private: System::Windows::Forms::Label^  rbtn;
  private: System::Windows::Forms::TrackBar^  vtrackBar;
  private: System::Windows::Forms::TrackBar^  rtrackBar;
  private: System::Windows::Forms::Button^  savebtn;
  private: System::Windows::Forms::Button^  loadbtn;



    private: System::Windows::Forms::TabControl^  captureSettingstab;


    private: System::Windows::Forms::TabPage^  Threshold;
    private: System::Windows::Forms::Label^  label11;
    private: System::Windows::Forms::Label^  label10;
    private: System::Windows::Forms::Label^  label9;
    private: System::Windows::Forms::Label^  label8;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::RadioButton^  Green;
    private: System::Windows::Forms::RadioButton^  White;
    private: System::Windows::Forms::RadioButton^  Red;
    private: System::Windows::Forms::RadioButton^  Yellow;
    private: System::Windows::Forms::RadioButton^  Blue;
    private: System::Windows::Forms::RadioButton^  Orange;
    private: System::Windows::Forms::TrackBar^  trackBar6;
    private: System::Windows::Forms::TrackBar^  trackBar5;
    private: System::Windows::Forms::TrackBar^  trackBar4;
    private: System::Windows::Forms::TrackBar^  trackBar3;
    private: System::Windows::Forms::TrackBar^  trackBar2;
    private: System::Windows::Forms::TrackBar^  trackBar1;
    private: System::Windows::Forms::TabPage^  BotThresholdtab;




    private: System::Windows::Forms::RadioButton^  OriginalMode;
    private: System::Windows::Forms::TabPage^  tabPage1;
    private: System::Windows::Forms::GroupBox^  captureSourcebox;
    private: System::Windows::Forms::RadioButton^  cameraradiobtn;

    private: System::Windows::Forms::RadioButton^  imageradiobtn;
private: System::Windows::Forms::RadioButton^  None;
private: System::Windows::Forms::Label^  maxBlobSizelbl;

private: System::Windows::Forms::Label^  minBlobSizelbl;

private: System::Windows::Forms::TrackBar^  maxBlobSizetrckbar;


private: System::Windows::Forms::TrackBar^  minBlobSizetrckbar;

private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::GroupBox^  roigrpbox;
private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::TrackBar^  roiymaxtrckbar;

private: System::Windows::Forms::TrackBar^  roiymintrckbar;

private: System::Windows::Forms::TrackBar^  roixmaxtrckbar;

private: System::Windows::Forms::TrackBar^  roixmintrckbar;
private: System::Windows::Forms::CheckBox^  showroichkbox;


private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::Label^  roiymaxlbl;

private: System::Windows::Forms::Label^  roiyminlbl;

private: System::Windows::Forms::Label^  roixmaxlbl;

private: System::Windows::Forms::Label^  roixminlbl;
private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::TrackBar^  markerSizetrckbar;
private: System::Windows::Forms::Button^  loadBotSettingsbtn;
private: System::Windows::Forms::Button^  saveBotSettingsbtn;
private: System::Windows::Forms::CheckBox^  markersizechkbox;






    private: System::ComponentModel::IContainer^  components;

  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>


#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
      this->components = (gcnew System::ComponentModel::Container());
      this->CamView = (gcnew System::Windows::Forms::PictureBox());
      this->StopCatureButton = (gcnew System::Windows::Forms::Button());
      this->StartCaptureButton = (gcnew System::Windows::Forms::Button());
      this->CamUpdateTimer = (gcnew System::Windows::Forms::Timer(this->components));
      this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
      this->None = (gcnew System::Windows::Forms::RadioButton());
      this->OriginalMode = (gcnew System::Windows::Forms::RadioButton());
      this->BlobMode = (gcnew System::Windows::Forms::RadioButton());
      this->ThresholdMode = (gcnew System::Windows::Forms::RadioButton());
      this->FPSCOUNTER = (gcnew System::Windows::Forms::Label());
      this->label12 = (gcnew System::Windows::Forms::Label());
      this->drivepwm = (gcnew System::Windows::Forms::Button());
      this->label13 = (gcnew System::Windows::Forms::Label());
      this->label14 = (gcnew System::Windows::Forms::Label());
      this->label15 = (gcnew System::Windows::Forms::Label());
      this->pwm3trackBar = (gcnew System::Windows::Forms::TrackBar());
      this->pwm2trackBar = (gcnew System::Windows::Forms::TrackBar());
      this->pwm1trackBar = (gcnew System::Windows::Forms::TrackBar());
      this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
      this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
      this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
      this->utrackBar = (gcnew System::Windows::Forms::TrackBar());
      this->drive_btn = (gcnew System::Windows::Forms::Button());
      this->ubtn = (gcnew System::Windows::Forms::Label());
      this->vbtn = (gcnew System::Windows::Forms::Label());
      this->rbtn = (gcnew System::Windows::Forms::Label());
      this->vtrackBar = (gcnew System::Windows::Forms::TrackBar());
      this->rtrackBar = (gcnew System::Windows::Forms::TrackBar());
      this->savebtn = (gcnew System::Windows::Forms::Button());
      this->loadbtn = (gcnew System::Windows::Forms::Button());
      this->captureSettingstab = (gcnew System::Windows::Forms::TabControl());
      this->Threshold = (gcnew System::Windows::Forms::TabPage());
      this->maxBlobSizelbl = (gcnew System::Windows::Forms::Label());
      this->minBlobSizelbl = (gcnew System::Windows::Forms::Label());
      this->maxBlobSizetrckbar = (gcnew System::Windows::Forms::TrackBar());
      this->minBlobSizetrckbar = (gcnew System::Windows::Forms::TrackBar());
      this->label16 = (gcnew System::Windows::Forms::Label());
      this->label11 = (gcnew System::Windows::Forms::Label());
      this->label10 = (gcnew System::Windows::Forms::Label());
      this->label9 = (gcnew System::Windows::Forms::Label());
      this->label8 = (gcnew System::Windows::Forms::Label());
      this->trackBar3 = (gcnew System::Windows::Forms::TrackBar());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->label7 = (gcnew System::Windows::Forms::Label());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->Green = (gcnew System::Windows::Forms::RadioButton());
      this->White = (gcnew System::Windows::Forms::RadioButton());
      this->Red = (gcnew System::Windows::Forms::RadioButton());
      this->Yellow = (gcnew System::Windows::Forms::RadioButton());
      this->Blue = (gcnew System::Windows::Forms::RadioButton());
      this->Orange = (gcnew System::Windows::Forms::RadioButton());
      this->trackBar6 = (gcnew System::Windows::Forms::TrackBar());
      this->trackBar5 = (gcnew System::Windows::Forms::TrackBar());
      this->trackBar4 = (gcnew System::Windows::Forms::TrackBar());
      this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
      this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
      this->BotThresholdtab = (gcnew System::Windows::Forms::TabPage());
      this->markersizechkbox = (gcnew System::Windows::Forms::CheckBox());
      this->loadBotSettingsbtn = (gcnew System::Windows::Forms::Button());
      this->saveBotSettingsbtn = (gcnew System::Windows::Forms::Button());
      this->label22 = (gcnew System::Windows::Forms::Label());
      this->label21 = (gcnew System::Windows::Forms::Label());
      this->markerSizetrckbar = (gcnew System::Windows::Forms::TrackBar());
      this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
      this->roigrpbox = (gcnew System::Windows::Forms::GroupBox());
      this->roiymaxlbl = (gcnew System::Windows::Forms::Label());
      this->roiyminlbl = (gcnew System::Windows::Forms::Label());
      this->roixmaxlbl = (gcnew System::Windows::Forms::Label());
      this->roixminlbl = (gcnew System::Windows::Forms::Label());
      this->label20 = (gcnew System::Windows::Forms::Label());
      this->label19 = (gcnew System::Windows::Forms::Label());
      this->label18 = (gcnew System::Windows::Forms::Label());
      this->label17 = (gcnew System::Windows::Forms::Label());
      this->roiymaxtrckbar = (gcnew System::Windows::Forms::TrackBar());
      this->roiymintrckbar = (gcnew System::Windows::Forms::TrackBar());
      this->roixmaxtrckbar = (gcnew System::Windows::Forms::TrackBar());
      this->roixmintrckbar = (gcnew System::Windows::Forms::TrackBar());
      this->showroichkbox = (gcnew System::Windows::Forms::CheckBox());
      this->captureSourcebox = (gcnew System::Windows::Forms::GroupBox());
      this->cameraradiobtn = (gcnew System::Windows::Forms::RadioButton());
      this->imageradiobtn = (gcnew System::Windows::Forms::RadioButton());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->CamView))->BeginInit();
      this->groupBox2->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pwm3trackBar))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pwm2trackBar))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pwm1trackBar))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->utrackBar))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->vtrackBar))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rtrackBar))->BeginInit();
      this->captureSettingstab->SuspendLayout();
      this->Threshold->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxBlobSizetrckbar))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minBlobSizetrckbar))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar3))->BeginInit();
      this->groupBox1->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar6))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar5))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar4))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
      this->BotThresholdtab->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markerSizetrckbar))->BeginInit();
      this->tabPage1->SuspendLayout();
      this->roigrpbox->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roiymaxtrckbar))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roiymintrckbar))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roixmaxtrckbar))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roixmintrckbar))->BeginInit();
      this->captureSourcebox->SuspendLayout();
      this->SuspendLayout();
      // 
      // CamView
      // 
      this->CamView->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
      this->CamView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->CamView->Location = System::Drawing::Point(380, 59);
      this->CamView->Name = L"CamView";
      this->CamView->Size = System::Drawing::Size(640, 480);
      this->CamView->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
      this->CamView->TabIndex = 1;
      this->CamView->TabStop = false;
      // 
      // StopCatureButton
      // 
      this->StopCatureButton->Enabled = false;
      this->StopCatureButton->Location = System::Drawing::Point(931, 21);
      this->StopCatureButton->Name = L"StopCatureButton";
      this->StopCatureButton->Size = System::Drawing::Size(79, 32);
      this->StopCatureButton->TabIndex = 2;
      this->StopCatureButton->Text = L"Stop Capture";
      this->StopCatureButton->UseVisualStyleBackColor = true;
      this->StopCatureButton->Click += gcnew System::EventHandler(this, &Form1::StopCatureButton_Click);
      // 
      // StartCaptureButton
      // 
      this->StartCaptureButton->Location = System::Drawing::Point(380, 21);
      this->StartCaptureButton->Name = L"StartCaptureButton";
      this->StartCaptureButton->Size = System::Drawing::Size(89, 32);
      this->StartCaptureButton->TabIndex = 3;
      this->StartCaptureButton->Text = L"Start Capture";
      this->StartCaptureButton->UseVisualStyleBackColor = true;
      this->StartCaptureButton->Click += gcnew System::EventHandler(this, &Form1::StartCaptureButton_Click);
      // 
      // CamUpdateTimer
      // 
      this->CamUpdateTimer->Interval = 20;
      this->CamUpdateTimer->Tick += gcnew System::EventHandler(this, &Form1::CamUpdateTimer_Tick);
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add(this->None);
      this->groupBox2->Controls->Add(this->OriginalMode);
      this->groupBox2->Controls->Add(this->BlobMode);
      this->groupBox2->Controls->Add(this->ThresholdMode);
      this->groupBox2->Location = System::Drawing::Point(380, 545);
      this->groupBox2->Name = L"groupBox2";
      this->groupBox2->Size = System::Drawing::Size(640, 76);
      this->groupBox2->TabIndex = 18;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = L"View Mode";
      // 
      // None
      // 
      this->None->AutoSize = true;
      this->None->Location = System::Drawing::Point(347, 29);
      this->None->Name = L"None";
      this->None->Size = System::Drawing::Size(51, 17);
      this->None->TabIndex = 4;
      this->None->TabStop = true;
      this->None->Text = L"None";
      this->None->UseVisualStyleBackColor = true;
      // 
      // OriginalMode
      // 
      this->OriginalMode->AutoSize = true;
      this->OriginalMode->Checked = true;
      this->OriginalMode->Location = System::Drawing::Point(15, 29);
      this->OriginalMode->Name = L"OriginalMode";
      this->OriginalMode->Size = System::Drawing::Size(92, 17);
      this->OriginalMode->TabIndex = 3;
      this->OriginalMode->TabStop = true;
      this->OriginalMode->Text = L"Original Image";
      this->OriginalMode->UseVisualStyleBackColor = true;
      // 
      // BlobMode
      // 
      this->BlobMode->AutoSize = true;
      this->BlobMode->Location = System::Drawing::Point(254, 29);
      this->BlobMode->Name = L"BlobMode";
      this->BlobMode->Size = System::Drawing::Size(72, 17);
      this->BlobMode->TabIndex = 1;
      this->BlobMode->Text = L"Blob View";
      this->BlobMode->UseVisualStyleBackColor = true;
      // 
      // ThresholdMode
      // 
      this->ThresholdMode->AutoSize = true;
      this->ThresholdMode->Location = System::Drawing::Point(137, 29);
      this->ThresholdMode->Name = L"ThresholdMode";
      this->ThresholdMode->Size = System::Drawing::Size(98, 17);
      this->ThresholdMode->TabIndex = 0;
      this->ThresholdMode->Text = L"Threshold View";
      this->ThresholdMode->UseVisualStyleBackColor = true;
      // 
      // FPSCOUNTER
      // 
      this->FPSCOUNTER->AutoSize = true;
      this->FPSCOUNTER->Location = System::Drawing::Point(681, 31);
      this->FPSCOUNTER->Name = L"FPSCOUNTER";
      this->FPSCOUNTER->Size = System::Drawing::Size(13, 13);
      this->FPSCOUNTER->TabIndex = 5;
      this->FPSCOUNTER->Text = L"--";
      // 
      // label12
      // 
      this->label12->AutoSize = true;
      this->label12->Location = System::Drawing::Point(605, 31);
      this->label12->Name = L"label12";
      this->label12->Size = System::Drawing::Size(70, 13);
      this->label12->TabIndex = 6;
      this->label12->Text = L"Capture FPS:";
      // 
      // drivepwm
      // 
      this->drivepwm->Location = System::Drawing::Point(45, 195);
      this->drivepwm->Name = L"drivepwm";
      this->drivepwm->Size = System::Drawing::Size(114, 28);
      this->drivepwm->TabIndex = 16;
      this->drivepwm->Text = L"Drive By PWM";
      this->drivepwm->UseVisualStyleBackColor = true;
      // 
      // label13
      // 
      this->label13->AutoSize = true;
      this->label13->Location = System::Drawing::Point(6, 133);
      this->label13->Name = L"label13";
      this->label13->Size = System::Drawing::Size(43, 13);
      this->label13->TabIndex = 15;
      this->label13->Text = L"PWM 3";
      // 
      // label14
      // 
      this->label14->AutoSize = true;
      this->label14->Location = System::Drawing::Point(6, 81);
      this->label14->Name = L"label14";
      this->label14->Size = System::Drawing::Size(43, 13);
      this->label14->TabIndex = 14;
      this->label14->Text = L"PWM 2";
      // 
      // label15
      // 
      this->label15->AutoSize = true;
      this->label15->Location = System::Drawing::Point(6, 30);
      this->label15->Name = L"label15";
      this->label15->Size = System::Drawing::Size(43, 13);
      this->label15->TabIndex = 13;
      this->label15->Text = L"PWM 1";
      // 
      // pwm3trackBar
      // 
      this->pwm3trackBar->Location = System::Drawing::Point(79, 132);
      this->pwm3trackBar->Maximum = 255;
      this->pwm3trackBar->Name = L"pwm3trackBar";
      this->pwm3trackBar->Size = System::Drawing::Size(104, 45);
      this->pwm3trackBar->TabIndex = 12;
      // 
      // pwm2trackBar
      // 
      this->pwm2trackBar->Location = System::Drawing::Point(79, 81);
      this->pwm2trackBar->Maximum = 255;
      this->pwm2trackBar->Name = L"pwm2trackBar";
      this->pwm2trackBar->Size = System::Drawing::Size(104, 45);
      this->pwm2trackBar->TabIndex = 11;
      // 
      // pwm1trackBar
      // 
      this->pwm1trackBar->Location = System::Drawing::Point(79, 30);
      this->pwm1trackBar->Maximum = 255;
      this->pwm1trackBar->Name = L"pwm1trackBar";
      this->pwm1trackBar->Size = System::Drawing::Size(104, 45);
      this->pwm1trackBar->TabIndex = 10;
      // 
      // checkBox1
      // 
      this->checkBox1->AutoSize = true;
      this->checkBox1->Location = System::Drawing::Point(199, 46);
      this->checkBox1->Name = L"checkBox1";
      this->checkBox1->Size = System::Drawing::Size(91, 17);
      this->checkBox1->TabIndex = 7;
      this->checkBox1->Text = L"Anticlockwise";
      this->checkBox1->UseVisualStyleBackColor = true;
      // 
      // checkBox2
      // 
      this->checkBox2->AutoSize = true;
      this->checkBox2->Location = System::Drawing::Point(199, 86);
      this->checkBox2->Name = L"checkBox2";
      this->checkBox2->Size = System::Drawing::Size(91, 17);
      this->checkBox2->TabIndex = 8;
      this->checkBox2->Text = L"Anticlockwise";
      this->checkBox2->UseVisualStyleBackColor = true;
      // 
      // checkBox3
      // 
      this->checkBox3->AutoSize = true;
      this->checkBox3->Location = System::Drawing::Point(199, 132);
      this->checkBox3->Name = L"checkBox3";
      this->checkBox3->Size = System::Drawing::Size(91, 17);
      this->checkBox3->TabIndex = 9;
      this->checkBox3->Text = L"Anticlockwise";
      this->checkBox3->UseVisualStyleBackColor = true;
      // 
      // utrackBar
      // 
      this->utrackBar->Location = System::Drawing::Point(48, 30);
      this->utrackBar->Minimum = -10;
      this->utrackBar->Name = L"utrackBar";
      this->utrackBar->Size = System::Drawing::Size(104, 45);
      this->utrackBar->TabIndex = 9;
      // 
      // drive_btn
      // 
      this->drive_btn->Location = System::Drawing::Point(48, 195);
      this->drive_btn->Name = L"drive_btn";
      this->drive_btn->Size = System::Drawing::Size(101, 28);
      this->drive_btn->TabIndex = 10;
      this->drive_btn->Text = L"Drive By UVR";
      this->drive_btn->UseVisualStyleBackColor = true;
      // 
      // ubtn
      // 
      this->ubtn->AutoSize = true;
      this->ubtn->Location = System::Drawing::Point(29, 30);
      this->ubtn->Name = L"ubtn";
      this->ubtn->Size = System::Drawing::Size(13, 13);
      this->ubtn->TabIndex = 3;
      this->ubtn->Text = L"u";
      // 
      // vbtn
      // 
      this->vbtn->AutoSize = true;
      this->vbtn->Location = System::Drawing::Point(29, 89);
      this->vbtn->Name = L"vbtn";
      this->vbtn->Size = System::Drawing::Size(13, 13);
      this->vbtn->TabIndex = 4;
      this->vbtn->Text = L"v";
      // 
      // rbtn
      // 
      this->rbtn->AutoSize = true;
      this->rbtn->Location = System::Drawing::Point(32, 132);
      this->rbtn->Name = L"rbtn";
      this->rbtn->Size = System::Drawing::Size(10, 13);
      this->rbtn->TabIndex = 5;
      this->rbtn->Text = L"r";
      // 
      // vtrackBar
      // 
      this->vtrackBar->Location = System::Drawing::Point(48, 81);
      this->vtrackBar->Minimum = -10;
      this->vtrackBar->Name = L"vtrackBar";
      this->vtrackBar->Size = System::Drawing::Size(104, 45);
      this->vtrackBar->TabIndex = 9;
      // 
      // rtrackBar
      // 
      this->rtrackBar->Location = System::Drawing::Point(48, 132);
      this->rtrackBar->Minimum = -10;
      this->rtrackBar->Name = L"rtrackBar";
      this->rtrackBar->Size = System::Drawing::Size(104, 45);
      this->rtrackBar->TabIndex = 9;
      // 
      // savebtn
      // 
      this->savebtn->Location = System::Drawing::Point(9, 512);
      this->savebtn->Name = L"savebtn";
      this->savebtn->Size = System::Drawing::Size(75, 23);
      this->savebtn->TabIndex = 23;
      this->savebtn->Text = L"Save";
      this->savebtn->UseVisualStyleBackColor = true;
      this->savebtn->Click += gcnew System::EventHandler(this, &Form1::save_Click);
      // 
      // loadbtn
      // 
      this->loadbtn->Location = System::Drawing::Point(109, 512);
      this->loadbtn->Name = L"loadbtn";
      this->loadbtn->Size = System::Drawing::Size(75, 23);
      this->loadbtn->TabIndex = 24;
      this->loadbtn->Text = L"Load";
      this->loadbtn->UseVisualStyleBackColor = true;
      this->loadbtn->Click += gcnew System::EventHandler(this, &Form1::load_Click);
      // 
      // captureSettingstab
      // 
      this->captureSettingstab->Controls->Add(this->Threshold);
      this->captureSettingstab->Controls->Add(this->BotThresholdtab);
      this->captureSettingstab->Controls->Add(this->tabPage1);
      this->captureSettingstab->Location = System::Drawing::Point(8, 19);
      this->captureSettingstab->Name = L"captureSettingstab";
      this->captureSettingstab->SelectedIndex = 0;
      this->captureSettingstab->Size = System::Drawing::Size(363, 580);
      this->captureSettingstab->TabIndex = 4;
      // 
      // Threshold
      // 
      this->Threshold->Controls->Add(this->maxBlobSizelbl);
      this->Threshold->Controls->Add(this->minBlobSizelbl);
      this->Threshold->Controls->Add(this->maxBlobSizetrckbar);
      this->Threshold->Controls->Add(this->minBlobSizetrckbar);
      this->Threshold->Controls->Add(this->label16);
      this->Threshold->Controls->Add(this->loadbtn);
      this->Threshold->Controls->Add(this->label11);
      this->Threshold->Controls->Add(this->savebtn);
      this->Threshold->Controls->Add(this->label10);
      this->Threshold->Controls->Add(this->label9);
      this->Threshold->Controls->Add(this->label8);
      this->Threshold->Controls->Add(this->trackBar3);
      this->Threshold->Controls->Add(this->label3);
      this->Threshold->Controls->Add(this->label7);
      this->Threshold->Controls->Add(this->label6);
      this->Threshold->Controls->Add(this->label5);
      this->Threshold->Controls->Add(this->label4);
      this->Threshold->Controls->Add(this->label2);
      this->Threshold->Controls->Add(this->label1);
      this->Threshold->Controls->Add(this->groupBox1);
      this->Threshold->Controls->Add(this->trackBar6);
      this->Threshold->Controls->Add(this->trackBar5);
      this->Threshold->Controls->Add(this->trackBar4);
      this->Threshold->Controls->Add(this->trackBar2);
      this->Threshold->Controls->Add(this->trackBar1);
      this->Threshold->Location = System::Drawing::Point(4, 22);
      this->Threshold->Name = L"Threshold";
      this->Threshold->Padding = System::Windows::Forms::Padding(3);
      this->Threshold->Size = System::Drawing::Size(355, 554);
      this->Threshold->TabIndex = 0;
      this->Threshold->Text = L"Color Threshold";
      this->Threshold->UseVisualStyleBackColor = true;
      // 
      // maxBlobSizelbl
      // 
      this->maxBlobSizelbl->AutoSize = true;
      this->maxBlobSizelbl->Location = System::Drawing::Point(297, 356);
      this->maxBlobSizelbl->Name = L"maxBlobSizelbl";
      this->maxBlobSizelbl->Size = System::Drawing::Size(13, 13);
      this->maxBlobSizelbl->TabIndex = 29;
      this->maxBlobSizelbl->Text = L"0";
      // 
      // minBlobSizelbl
      // 
      this->minBlobSizelbl->AutoSize = true;
      this->minBlobSizelbl->Location = System::Drawing::Point(143, 356);
      this->minBlobSizelbl->Name = L"minBlobSizelbl";
      this->minBlobSizelbl->Size = System::Drawing::Size(13, 13);
      this->minBlobSizelbl->TabIndex = 28;
      this->minBlobSizelbl->Text = L"0";
      // 
      // maxBlobSizetrckbar
      // 
      this->maxBlobSizetrckbar->Location = System::Drawing::Point(186, 324);
      this->maxBlobSizetrckbar->Maximum = 100;
      this->maxBlobSizetrckbar->Name = L"maxBlobSizetrckbar";
      this->maxBlobSizetrckbar->Size = System::Drawing::Size(104, 45);
      this->maxBlobSizetrckbar->TabIndex = 27;
      this->maxBlobSizetrckbar->Value = 100;
      this->maxBlobSizetrckbar->Scroll += gcnew System::EventHandler(this, &Form1::maxBlobSizetrckbar_Scroll);
      // 
      // minBlobSizetrckbar
      // 
      this->minBlobSizetrckbar->Location = System::Drawing::Point(33, 324);
      this->minBlobSizetrckbar->Maximum = 100;
      this->minBlobSizetrckbar->Name = L"minBlobSizetrckbar";
      this->minBlobSizetrckbar->Size = System::Drawing::Size(104, 45);
      this->minBlobSizetrckbar->TabIndex = 26;
      this->minBlobSizetrckbar->Scroll += gcnew System::EventHandler(this, &Form1::minBlobSizetrckbar_Scroll);
      // 
      // label16
      // 
      this->label16->AutoSize = true;
      this->label16->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label16->Location = System::Drawing::Point(9, 307);
      this->label16->Name = L"label16";
      this->label16->Size = System::Drawing::Size(61, 14);
      this->label16->TabIndex = 25;
      this->label16->Text = L"Blob Size";
      // 
      // label11
      // 
      this->label11->AutoSize = true;
      this->label11->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label11->Location = System::Drawing::Point(205, 17);
      this->label11->Name = L"label11";
      this->label11->Size = System::Drawing::Size(63, 15);
      this->label11->TabIndex = 17;
      this->label11->Text = L"Maximum";
      // 
      // label10
      // 
      this->label10->AutoSize = true;
      this->label10->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label10->Location = System::Drawing::Point(52, 17);
      this->label10->Name = L"label10";
      this->label10->Size = System::Drawing::Size(59, 15);
      this->label10->TabIndex = 16;
      this->label10->Text = L"Minimum";
      // 
      // label9
      // 
      this->label9->AutoSize = true;
      this->label9->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label9->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
      this->label9->Location = System::Drawing::Point(6, 214);
      this->label9->Name = L"label9";
      this->label9->Size = System::Drawing::Size(38, 15);
      this->label9->TabIndex = 15;
      this->label9->Text = L"Value";
      // 
      // label8
      // 
      this->label8->AutoSize = true;
      this->label8->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label8->Location = System::Drawing::Point(3, 128);
      this->label8->Name = L"label8";
      this->label8->Size = System::Drawing::Size(66, 15);
      this->label8->TabIndex = 14;
      this->label8->Text = L"Saturation";
      // 
      // trackBar3
      // 
      this->trackBar3->Location = System::Drawing::Point(23, 156);
      this->trackBar3->Maximum = 256;
      this->trackBar3->Name = L"trackBar3";
      this->trackBar3->Size = System::Drawing::Size(121, 45);
      this->trackBar3->TabIndex = 2;
      this->trackBar3->TickFrequency = 16;
      this->trackBar3->Scroll += gcnew System::EventHandler(this, &Form1::trackBar3_Scroll);
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Location = System::Drawing::Point(148, 192);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(13, 13);
      this->label3->TabIndex = 9;
      this->label3->Text = L"0";
      // 
      // label7
      // 
      this->label7->AutoSize = true;
      this->label7->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label7->Location = System::Drawing::Point(6, 41);
      this->label7->Name = L"label7";
      this->label7->Size = System::Drawing::Size(29, 15);
      this->label7->TabIndex = 13;
      this->label7->Text = L"Hue";
      // 
      // label6
      // 
      this->label6->AutoSize = true;
      this->label6->Location = System::Drawing::Point(309, 269);
      this->label6->Name = L"label6";
      this->label6->Size = System::Drawing::Size(13, 13);
      this->label6->TabIndex = 12;
      this->label6->Text = L"0";
      // 
      // label5
      // 
      this->label5->AutoSize = true;
      this->label5->Location = System::Drawing::Point(154, 268);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(13, 13);
      this->label5->TabIndex = 11;
      this->label5->Text = L"0";
      // 
      // label4
      // 
      this->label4->AutoSize = true;
      this->label4->Location = System::Drawing::Point(314, 186);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(13, 13);
      this->label4->TabIndex = 10;
      this->label4->Text = L"0";
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Location = System::Drawing::Point(312, 88);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(13, 13);
      this->label2->TabIndex = 8;
      this->label2->Text = L"0";
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Location = System::Drawing::Point(151, 90);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(13, 13);
      this->label1->TabIndex = 7;
      this->label1->Text = L"0";
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->Green);
      this->groupBox1->Controls->Add(this->White);
      this->groupBox1->Controls->Add(this->Red);
      this->groupBox1->Controls->Add(this->Yellow);
      this->groupBox1->Controls->Add(this->Blue);
      this->groupBox1->Controls->Add(this->Orange);
      this->groupBox1->Location = System::Drawing::Point(30, 382);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Size = System::Drawing::Size(292, 113);
      this->groupBox1->TabIndex = 6;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"Select Threshold Color";
      // 
      // Green
      // 
      this->Green->AutoSize = true;
      this->Green->Location = System::Drawing::Point(155, 37);
      this->Green->Name = L"Green";
      this->Green->Size = System::Drawing::Size(79, 17);
      this->Green->TabIndex = 5;
      this->Green->TabStop = true;
      this->Green->Text = L"Field Green";
      this->Green->UseVisualStyleBackColor = true;
      this->Green->Click += gcnew System::EventHandler(this, &Form1::Green_Click);
      // 
      // White
      // 
      this->White->AutoSize = true;
      this->White->Location = System::Drawing::Point(155, 60);
      this->White->Name = L"White";
      this->White->Size = System::Drawing::Size(53, 17);
      this->White->TabIndex = 4;
      this->White->TabStop = true;
      this->White->Text = L"White";
      this->White->UseVisualStyleBackColor = true;
      this->White->Click += gcnew System::EventHandler(this, &Form1::White_Click);
      // 
      // Red
      // 
      this->Red->AutoSize = true;
      this->Red->Location = System::Drawing::Point(155, 83);
      this->Red->Name = L"Red";
      this->Red->Size = System::Drawing::Size(45, 17);
      this->Red->TabIndex = 3;
      this->Red->TabStop = true;
      this->Red->Text = L"Red";
      this->Red->UseVisualStyleBackColor = true;
      this->Red->Click += gcnew System::EventHandler(this, &Form1::Red_Click);
      // 
      // Yellow
      // 
      this->Yellow->AutoSize = true;
      this->Yellow->Location = System::Drawing::Point(17, 83);
      this->Yellow->Name = L"Yellow";
      this->Yellow->Size = System::Drawing::Size(90, 17);
      this->Yellow->TabIndex = 2;
      this->Yellow->TabStop = true;
      this->Yellow->Text = L"Center Yellow";
      this->Yellow->UseVisualStyleBackColor = true;
      this->Yellow->Click += gcnew System::EventHandler(this, &Form1::Yellow_Click);
      // 
      // Blue
      // 
      this->Blue->AutoSize = true;
      this->Blue->Location = System::Drawing::Point(17, 60);
      this->Blue->Name = L"Blue";
      this->Blue->Size = System::Drawing::Size(80, 17);
      this->Blue->TabIndex = 1;
      this->Blue->TabStop = true;
      this->Blue->Text = L"Center Blue";
      this->Blue->UseVisualStyleBackColor = true;
      this->Blue->Click += gcnew System::EventHandler(this, &Form1::Blue_Click);
      // 
      // Orange
      // 
      this->Orange->AutoSize = true;
      this->Orange->Checked = true;
      this->Orange->Location = System::Drawing::Point(17, 37);
      this->Orange->Name = L"Orange";
      this->Orange->Size = System::Drawing::Size(80, 17);
      this->Orange->TabIndex = 0;
      this->Orange->TabStop = true;
      this->Orange->Text = L"Ball Orange";
      this->Orange->UseVisualStyleBackColor = true;
      this->Orange->Click += gcnew System::EventHandler(this, &Form1::Orange_Click);
      // 
      // trackBar6
      // 
      this->trackBar6->Location = System::Drawing::Point(185, 236);
      this->trackBar6->Maximum = 256;
      this->trackBar6->Name = L"trackBar6";
      this->trackBar6->Size = System::Drawing::Size(121, 45);
      this->trackBar6->TabIndex = 5;
      this->trackBar6->TickFrequency = 16;
      this->trackBar6->Scroll += gcnew System::EventHandler(this, &Form1::trackBar6_Scroll);
      // 
      // trackBar5
      // 
      this->trackBar5->Location = System::Drawing::Point(26, 237);
      this->trackBar5->Maximum = 256;
      this->trackBar5->Name = L"trackBar5";
      this->trackBar5->Size = System::Drawing::Size(121, 45);
      this->trackBar5->TabIndex = 4;
      this->trackBar5->TickFrequency = 16;
      this->trackBar5->Scroll += gcnew System::EventHandler(this, &Form1::trackBar5_Scroll);
      // 
      // trackBar4
      // 
      this->trackBar4->Location = System::Drawing::Point(186, 156);
      this->trackBar4->Maximum = 256;
      this->trackBar4->Name = L"trackBar4";
      this->trackBar4->Size = System::Drawing::Size(121, 45);
      this->trackBar4->TabIndex = 3;
      this->trackBar4->TickFrequency = 16;
      this->trackBar4->Scroll += gcnew System::EventHandler(this, &Form1::trackBar4_Scroll);
      // 
      // trackBar2
      // 
      this->trackBar2->Location = System::Drawing::Point(186, 58);
      this->trackBar2->Maximum = 181;
      this->trackBar2->Name = L"trackBar2";
      this->trackBar2->Size = System::Drawing::Size(121, 45);
      this->trackBar2->TabIndex = 1;
      this->trackBar2->TickFrequency = 15;
      this->trackBar2->Scroll += gcnew System::EventHandler(this, &Form1::trackBar2_Scroll);
      // 
      // trackBar1
      // 
      this->trackBar1->Location = System::Drawing::Point(23, 59);
      this->trackBar1->Maximum = 181;
      this->trackBar1->Name = L"trackBar1";
      this->trackBar1->Size = System::Drawing::Size(121, 45);
      this->trackBar1->TabIndex = 0;
      this->trackBar1->TickFrequency = 15;
      this->trackBar1->Scroll += gcnew System::EventHandler(this, &Form1::trackBar1_Scroll);
      // 
      // BotThresholdtab
      // 
      this->BotThresholdtab->Controls->Add(this->markersizechkbox);
      this->BotThresholdtab->Controls->Add(this->loadBotSettingsbtn);
      this->BotThresholdtab->Controls->Add(this->saveBotSettingsbtn);
      this->BotThresholdtab->Controls->Add(this->label22);
      this->BotThresholdtab->Controls->Add(this->label21);
      this->BotThresholdtab->Controls->Add(this->markerSizetrckbar);
      this->BotThresholdtab->Location = System::Drawing::Point(4, 22);
      this->BotThresholdtab->Name = L"BotThresholdtab";
      this->BotThresholdtab->Padding = System::Windows::Forms::Padding(3);
      this->BotThresholdtab->Size = System::Drawing::Size(355, 554);
      this->BotThresholdtab->TabIndex = 1;
      this->BotThresholdtab->Text = L"BotThreshold";
      this->BotThresholdtab->UseVisualStyleBackColor = true;
      // 
      // markersizechkbox
      // 
      this->markersizechkbox->AutoSize = true;
      this->markersizechkbox->Location = System::Drawing::Point(211, 48);
      this->markersizechkbox->Name = L"markersizechkbox";
      this->markersizechkbox->Size = System::Drawing::Size(112, 17);
      this->markersizechkbox->TabIndex = 5;
      this->markersizechkbox->Text = L"Show Marker Size";
      this->markersizechkbox->UseVisualStyleBackColor = true;
      // 
      // loadBotSettingsbtn
      // 
      this->loadBotSettingsbtn->Location = System::Drawing::Point(136, 504);
      this->loadBotSettingsbtn->Name = L"loadBotSettingsbtn";
      this->loadBotSettingsbtn->Size = System::Drawing::Size(75, 23);
      this->loadBotSettingsbtn->TabIndex = 4;
      this->loadBotSettingsbtn->Text = L"Load";
      this->loadBotSettingsbtn->UseVisualStyleBackColor = true;
      this->loadBotSettingsbtn->Click += gcnew System::EventHandler(this, &Form1::loadBotSettingsbtn_Click);
      // 
      // saveBotSettingsbtn
      // 
      this->saveBotSettingsbtn->Location = System::Drawing::Point(24, 504);
      this->saveBotSettingsbtn->Name = L"saveBotSettingsbtn";
      this->saveBotSettingsbtn->Size = System::Drawing::Size(75, 23);
      this->saveBotSettingsbtn->TabIndex = 3;
      this->saveBotSettingsbtn->Text = L"Save";
      this->saveBotSettingsbtn->UseVisualStyleBackColor = true;
      // 
      // label22
      // 
      this->label22->AutoSize = true;
      this->label22->Location = System::Drawing::Point(149, 52);
      this->label22->Name = L"label22";
      this->label22->Size = System::Drawing::Size(25, 13);
      this->label22->TabIndex = 2;
      this->label22->Text = L"100";
      // 
      // label21
      // 
      this->label21->AutoSize = true;
      this->label21->Location = System::Drawing::Point(21, 16);
      this->label21->Name = L"label21";
      this->label21->Size = System::Drawing::Size(63, 13);
      this->label21->TabIndex = 1;
      this->label21->Text = L"Marker Size";
      // 
      // markerSizetrckbar
      // 
      this->markerSizetrckbar->Location = System::Drawing::Point(24, 42);
      this->markerSizetrckbar->Maximum = 100;
      this->markerSizetrckbar->Minimum = 10;
      this->markerSizetrckbar->Name = L"markerSizetrckbar";
      this->markerSizetrckbar->Size = System::Drawing::Size(119, 45);
      this->markerSizetrckbar->TabIndex = 0;
      this->markerSizetrckbar->Value = 100;
      this->markerSizetrckbar->Scroll += gcnew System::EventHandler(this, &Form1::markerSizetrckbar_Scroll);
      // 
      // tabPage1
      // 
      this->tabPage1->Controls->Add(this->roigrpbox);
      this->tabPage1->Controls->Add(this->captureSourcebox);
      this->tabPage1->Location = System::Drawing::Point(4, 22);
      this->tabPage1->Name = L"tabPage1";
      this->tabPage1->Size = System::Drawing::Size(355, 554);
      this->tabPage1->TabIndex = 2;
      this->tabPage1->Text = L"Capture Settings";
      this->tabPage1->UseVisualStyleBackColor = true;
      // 
      // roigrpbox
      // 
      this->roigrpbox->Controls->Add(this->roiymaxlbl);
      this->roigrpbox->Controls->Add(this->roiyminlbl);
      this->roigrpbox->Controls->Add(this->roixmaxlbl);
      this->roigrpbox->Controls->Add(this->roixminlbl);
      this->roigrpbox->Controls->Add(this->label20);
      this->roigrpbox->Controls->Add(this->label19);
      this->roigrpbox->Controls->Add(this->label18);
      this->roigrpbox->Controls->Add(this->label17);
      this->roigrpbox->Controls->Add(this->roiymaxtrckbar);
      this->roigrpbox->Controls->Add(this->roiymintrckbar);
      this->roigrpbox->Controls->Add(this->roixmaxtrckbar);
      this->roigrpbox->Controls->Add(this->roixmintrckbar);
      this->roigrpbox->Controls->Add(this->showroichkbox);
      this->roigrpbox->Location = System::Drawing::Point(15, 98);
      this->roigrpbox->Name = L"roigrpbox";
      this->roigrpbox->Size = System::Drawing::Size(315, 190);
      this->roigrpbox->TabIndex = 1;
      this->roigrpbox->TabStop = false;
      this->roigrpbox->Text = L"ROI Settings";
      // 
      // roiymaxlbl
      // 
      this->roiymaxlbl->AutoSize = true;
      this->roiymaxlbl->Location = System::Drawing::Point(287, 143);
      this->roiymaxlbl->Name = L"roiymaxlbl";
      this->roiymaxlbl->Size = System::Drawing::Size(25, 13);
      this->roiymaxlbl->TabIndex = 12;
      this->roiymaxlbl->Text = L"480";
      // 
      // roiyminlbl
      // 
      this->roiyminlbl->AutoSize = true;
      this->roiyminlbl->Location = System::Drawing::Point(143, 143);
      this->roiyminlbl->Name = L"roiyminlbl";
      this->roiyminlbl->Size = System::Drawing::Size(13, 13);
      this->roiyminlbl->TabIndex = 11;
      this->roiyminlbl->Text = L"0";
      // 
      // roixmaxlbl
      // 
      this->roixmaxlbl->AutoSize = true;
      this->roixmaxlbl->Location = System::Drawing::Point(287, 78);
      this->roixmaxlbl->Name = L"roixmaxlbl";
      this->roixmaxlbl->Size = System::Drawing::Size(25, 13);
      this->roixmaxlbl->TabIndex = 10;
      this->roixmaxlbl->Text = L"640";
      // 
      // roixminlbl
      // 
      this->roixminlbl->AutoSize = true;
      this->roixminlbl->Location = System::Drawing::Point(149, 76);
      this->roixminlbl->Name = L"roixminlbl";
      this->roixminlbl->Size = System::Drawing::Size(13, 13);
      this->roixminlbl->TabIndex = 9;
      this->roixminlbl->Text = L"0";
      // 
      // label20
      // 
      this->label20->AutoSize = true;
      this->label20->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label20->Location = System::Drawing::Point(204, 42);
      this->label20->Name = L"label20";
      this->label20->Size = System::Drawing::Size(57, 12);
      this->label20->TabIndex = 8;
      this->label20->Text = L"Maximum";
      // 
      // label19
      // 
      this->label19->AutoSize = true;
      this->label19->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label19->Location = System::Drawing::Point(65, 41);
      this->label19->Name = L"label19";
      this->label19->Size = System::Drawing::Size(54, 12);
      this->label19->TabIndex = 7;
      this->label19->Text = L"Minimum";
      // 
      // label18
      // 
      this->label18->AutoSize = true;
      this->label18->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label18->Location = System::Drawing::Point(11, 144);
      this->label18->Name = L"label18";
      this->label18->Size = System::Drawing::Size(12, 12);
      this->label18->TabIndex = 6;
      this->label18->Text = L"Y";
      // 
      // label17
      // 
      this->label17->AutoSize = true;
      this->label17->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label17->Location = System::Drawing::Point(11, 78);
      this->label17->Name = L"label17";
      this->label17->Size = System::Drawing::Size(12, 12);
      this->label17->TabIndex = 5;
      this->label17->Text = L"X";
      // 
      // roiymaxtrckbar
      // 
      this->roiymaxtrckbar->Location = System::Drawing::Point(177, 130);
      this->roiymaxtrckbar->Maximum = 480;
      this->roiymaxtrckbar->Name = L"roiymaxtrckbar";
      this->roiymaxtrckbar->Size = System::Drawing::Size(104, 45);
      this->roiymaxtrckbar->TabIndex = 4;
      this->roiymaxtrckbar->Value = 480;
      this->roiymaxtrckbar->Scroll += gcnew System::EventHandler(this, &Form1::roiymaxtrckbar_Scroll);
      // 
      // roiymintrckbar
      // 
      this->roiymintrckbar->Location = System::Drawing::Point(38, 130);
      this->roiymintrckbar->Maximum = 480;
      this->roiymintrckbar->Name = L"roiymintrckbar";
      this->roiymintrckbar->Size = System::Drawing::Size(104, 45);
      this->roiymintrckbar->TabIndex = 3;
      this->roiymintrckbar->Scroll += gcnew System::EventHandler(this, &Form1::roiymintrckbar_Scroll);
      // 
      // roixmaxtrckbar
      // 
      this->roixmaxtrckbar->Location = System::Drawing::Point(177, 67);
      this->roixmaxtrckbar->Maximum = 640;
      this->roixmaxtrckbar->Name = L"roixmaxtrckbar";
      this->roixmaxtrckbar->Size = System::Drawing::Size(104, 45);
      this->roixmaxtrckbar->TabIndex = 2;
      this->roixmaxtrckbar->Value = 640;
      this->roixmaxtrckbar->Scroll += gcnew System::EventHandler(this, &Form1::roixmaxtrckbar_Scroll);
      // 
      // roixmintrckbar
      // 
      this->roixmintrckbar->Location = System::Drawing::Point(38, 67);
      this->roixmintrckbar->Maximum = 640;
      this->roixmintrckbar->Name = L"roixmintrckbar";
      this->roixmintrckbar->Size = System::Drawing::Size(104, 45);
      this->roixmintrckbar->TabIndex = 1;
      this->roixmintrckbar->Scroll += gcnew System::EventHandler(this, &Form1::trackBar7_Scroll);
      // 
      // showroichkbox
      // 
      this->showroichkbox->AutoSize = true;
      this->showroichkbox->Location = System::Drawing::Point(234, 19);
      this->showroichkbox->Name = L"showroichkbox";
      this->showroichkbox->Size = System::Drawing::Size(75, 17);
      this->showroichkbox->TabIndex = 0;
      this->showroichkbox->Text = L"Show ROI";
      this->showroichkbox->UseVisualStyleBackColor = true;
      // 
      // captureSourcebox
      // 
      this->captureSourcebox->Controls->Add(this->cameraradiobtn);
      this->captureSourcebox->Controls->Add(this->imageradiobtn);
      this->captureSourcebox->Location = System::Drawing::Point(16, 18);
      this->captureSourcebox->Name = L"captureSourcebox";
      this->captureSourcebox->Size = System::Drawing::Size(302, 62);
      this->captureSourcebox->TabIndex = 0;
      this->captureSourcebox->TabStop = false;
      this->captureSourcebox->Text = L"Capture source";
      // 
      // cameraradiobtn
      // 
      this->cameraradiobtn->AutoSize = true;
      this->cameraradiobtn->Checked = true;
      this->cameraradiobtn->Location = System::Drawing::Point(145, 29);
      this->cameraradiobtn->Name = L"cameraradiobtn";
      this->cameraradiobtn->Size = System::Drawing::Size(61, 17);
      this->cameraradiobtn->TabIndex = 1;
      this->cameraradiobtn->TabStop = true;
      this->cameraradiobtn->Text = L"Camera";
      this->cameraradiobtn->UseVisualStyleBackColor = true;
      // 
      // imageradiobtn
      // 
      this->imageradiobtn->AutoSize = true;
      this->imageradiobtn->Location = System::Drawing::Point(21, 29);
      this->imageradiobtn->Name = L"imageradiobtn";
      this->imageradiobtn->Size = System::Drawing::Size(84, 17);
      this->imageradiobtn->TabIndex = 0;
      this->imageradiobtn->Text = L"Static Image";
      this->imageradiobtn->UseVisualStyleBackColor = true;
      // 
      // Form1
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->AutoSize = true;
      this->ClientSize = System::Drawing::Size(1034, 642);
      this->Controls->Add(this->groupBox2);
      this->Controls->Add(this->label12);
      this->Controls->Add(this->FPSCOUNTER);
      this->Controls->Add(this->captureSettingstab);
      this->Controls->Add(this->StartCaptureButton);
      this->Controls->Add(this->StopCatureButton);
      this->Controls->Add(this->CamView);
      this->Name = L"Form1";
      this->Text = L"KGPVision";
      this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->CamView))->EndInit();
      this->groupBox2->ResumeLayout(false);
      this->groupBox2->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pwm3trackBar))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pwm2trackBar))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pwm1trackBar))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->utrackBar))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->vtrackBar))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rtrackBar))->EndInit();
      this->captureSettingstab->ResumeLayout(false);
      this->Threshold->ResumeLayout(false);
      this->Threshold->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxBlobSizetrckbar))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minBlobSizetrckbar))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar3))->EndInit();
      this->groupBox1->ResumeLayout(false);
      this->groupBox1->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar6))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar5))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar4))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
      this->BotThresholdtab->ResumeLayout(false);
      this->BotThresholdtab->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markerSizetrckbar))->EndInit();
      this->tabPage1->ResumeLayout(false);
      this->roigrpbox->ResumeLayout(false);
      this->roigrpbox->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roiymaxtrckbar))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roiymintrckbar))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roixmaxtrckbar))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roixmintrckbar))->EndInit();
      this->captureSourcebox->ResumeLayout(false);
      this->captureSourcebox->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  private: System::Void StartCaptureButton_Click(System::Object^  sender, System::EventArgs^  e)
       {
         this->captureSourcebox->Enabled = false;
         cvSetCaptureProperty(cap,CV_CAP_PROP_FRAME_WIDTH,640);
         cvSetCaptureProperty(cap,CV_CAP_PROP_FRAME_HEIGHT,480);
         if(cameraradiobtn->Checked && !(cap = cvCaptureFromCAM(0)))
           MessageBox::Show("Unable to connect to device","Camera Error:",MessageBoxButtons::OK,MessageBoxIcon::Error);
         else
         {
           lastClock = clock();
           if(cameraradiobtn->Checked)
            frame = cvQueryFrame(cap);
           else
           {
               frame = cvLoadImage("Test.bmp");
               staticImg = frame;
           }
           HSVframe = cvCreateImage(cvSize(frame->width,frame->height),frame->depth,frame->nChannels);
           BlankImage = cvCreateImage(cvSize(frame->width,frame->height),frame->depth,frame->nChannels);
           blobImg = cvCreateImage(cvSize(frame->width,frame->height),frame->depth,frame->nChannels);
           BinImage = cvCreateImage(cvSize(frame->width,frame->height),IPL_DEPTH_8U,1);
           this->StopCatureButton->Enabled = true;
           this->StartCaptureButton->Enabled = false;
           this->CamUpdateTimer->Enabled = true;
         }
       }

  private: System::Void StopCatureButton_Click(System::Object^  sender, System::EventArgs^  e)
       {
         this->FPSCOUNTER->Text = "0";
         this->CamView->Image = gcnew System::Drawing::Bitmap("No Image.bmp");
         this->CamUpdateTimer->Enabled = false;
         this->StartCaptureButton->Enabled = true;
         this->StopCatureButton->Enabled = false;
         this->captureSourcebox->Enabled = true;
    /*     if(cameraradiobtn->Checked)
            cvReleaseCapture(&cap);
         else
           cvReleaseImage(&frame);
         cvReleaseImage(&HSVframe);
         cvReleaseImage(&BinImage);
         cvReleaseImage(&BlankImage);
         cvReleaseImage(&blobImg); */
     }

  private: System::Void CamUpdateTimer_Tick(System::Object^  sender, System::EventArgs^  e) 
       {
         int c;
         this->FPSCOUNTER->Text = ((int)CLOCKS_PER_SEC/(clock() - lastClock)).ToString();
         lastClock = clock();
         HSV hsvMin,hsvMax;
         if(cameraradiobtn->Checked)
             frame = cvQueryFrame(cap);
         else
             frame = staticImg;
         cvCvtColor(frame,HSVframe,CV_BGR2HSV);
          if(this->OriginalMode->Checked)
         {
           drawFigures(frame);
           this->CamView->Image = gcnew System::Drawing::Bitmap(frame->width,frame->height,frame->widthStep,System::Drawing::Imaging::PixelFormat::Format24bppRgb,(System::IntPtr)frame->imageData);
         }
         else if(this->BlobMode->Checked)
         {
           vision->processImage(HSVframe);
           getBlobImage(blobImg,vision->blobArray,vision->numBlobs);
           drawFigures(blobImg);
           this->CamView->Image = gcnew System::Drawing::Bitmap(blobImg->width,blobImg->height,blobImg->widthStep,System::Drawing::Imaging::PixelFormat::Format24bppRgb,(System::IntPtr)blobImg->imageData);
         }
         else if(this->ThresholdMode->Checked)
         {
           cvInRangeS(HSVframe,cvScalar(this->trackBar1->Value,this->trackBar3->Value,this->trackBar5->Value),cvScalar(this->trackBar2->Value,this->trackBar4->Value,this->trackBar6->Value),BinImage);
           this->CamView->Image = gcnew System::Drawing::Bitmap(BinImage->width,BinImage->height,BinImage->widthStep,System::Drawing::Imaging::PixelFormat::Format8bppIndexed,(System::IntPtr)BinImage->imageData);
         }
      }
  private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e)
       {
         this->label1->Text = this->trackBar1->Value.ToString();
         if(this->trackBar2->Value < this->trackBar1->Value)
         {
           this->trackBar2->Value = this->trackBar1->Value;
           this->label2->Text = this->trackBar2->Value.ToString();
         }
         vision->Parameters[activeColor].minhsv.h = this->trackBar1->Value;
         vision->Parameters[activeColor].maxhsv.h = this->trackBar2->Value;
       }
  private: System::Void trackBar4_Scroll(System::Object^  sender, System::EventArgs^  e)
       {
         this->label4->Text = this->trackBar4->Value.ToString();
         if(this->trackBar4->Value < this->trackBar3->Value)
         {
           this->trackBar3->Value = this->trackBar4->Value;
           this->label3->Text = this->trackBar3->Value.ToString();
         }
         vision->Parameters[activeColor].minhsv.s = this->trackBar3->Value;
         vision->Parameters[activeColor].maxhsv.s = this->trackBar4->Value;
       }
  private: System::Void trackBar5_Scroll(System::Object^  sender, System::EventArgs^  e)
       {
         this->label5->Text = this->trackBar5->Value.ToString();
         if(this->trackBar6->Value < this->trackBar5->Value)
         {
           this->trackBar6->Value = this->trackBar5->Value;
            this->label6->Text = this->trackBar6->Value.ToString();
         }
         vision->Parameters[activeColor].minhsv.v = this->trackBar5->Value;
         vision->Parameters[activeColor].maxhsv.v = this->trackBar6->Value;
       }
  private: System::Void trackBar2_Scroll(System::Object^  sender, System::EventArgs^  e)
       {
         this->label2->Text = this->trackBar2->Value.ToString();
         if(this->trackBar1->Value > this->trackBar2->Value)
         {
           this->trackBar1->Value = this->trackBar2->Value;
           this->label1->Text = this->trackBar1->Value.ToString();
         }
         vision->Parameters[activeColor].minhsv.h = this->trackBar1->Value;
         vision->Parameters[activeColor].maxhsv.h = this->trackBar2->Value;
       }
  private: System::Void trackBar3_Scroll(System::Object^  sender, System::EventArgs^  e)
       {
         this->label3->Text = this->trackBar3->Value.ToString();
         if(this->trackBar3->Value > this->trackBar4->Value)
         {
           this->trackBar4->Value = this->trackBar3->Value;
           this->label4->Text = this->trackBar4->Value.ToString();
         }
         vision->Parameters[activeColor].minhsv.s = this->trackBar3->Value;
         vision->Parameters[activeColor].maxhsv.s = this->trackBar4->Value;
       }
  private: System::Void trackBar6_Scroll(System::Object^  sender, System::EventArgs^  e)
       {
         this->label6->Text = this->trackBar6->Value.ToString();
         if(this->trackBar5->Value > this->trackBar6->Value)
         {
           this->trackBar5->Value = this->trackBar6->Value;
           this->label5->Text = this->trackBar5->Value.ToString();
         }
         vision->Parameters[activeColor].minhsv.v = this->trackBar5->Value;
         vision->Parameters[activeColor].maxhsv.v = this->trackBar6->Value;
       }
  private: System::Void minBlobSizetrckbar_Scroll(System::Object^  sender, System::EventArgs^  e)
       {
         this->minBlobSizelbl->Text = this->minBlobSizetrckbar->Value.ToString();
         if(this->maxBlobSizetrckbar->Value < this->minBlobSizetrckbar->Value)
         {
           this->maxBlobSizetrckbar->Value = this->minBlobSizetrckbar->Value;
           this->maxBlobSizelbl->Text = this->maxBlobSizetrckbar->Value.ToString();
         } 
         vision->Parameters[activeColor].blobMinDist = this->minBlobSizetrckbar->Value;
         vision->Parameters[activeColor].blobMaxDist = this->maxBlobSizetrckbar->Value;

       }
  private: System::Void maxBlobSizetrckbar_Scroll(System::Object^  sender, System::EventArgs^  e) 
         {
           this->maxBlobSizelbl->Text = this->maxBlobSizetrckbar->Value.ToString();
           if(this->maxBlobSizetrckbar->Value < this->minBlobSizetrckbar->Value)
           {
             this->minBlobSizetrckbar->Value = this->maxBlobSizetrckbar->Value;
             this->minBlobSizelbl->Text = this->minBlobSizetrckbar->Value.ToString();
           } 
           vision->Parameters[activeColor].blobMinDist = this->minBlobSizetrckbar->Value;
           vision->Parameters[activeColor].blobMaxDist = this->maxBlobSizetrckbar->Value;

         }  
  private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e)
       {
         lastClock = clock();
         cap = cvCaptureFromCAM(0);
         if(cap)
           frame = cvQueryFrame(cap);
         else
           MessageBox::Show("No capture device found","Capture Error",MessageBoxButtons::OK,MessageBoxIcon::Error);
    //     if(frame)
    //      SetupBlobDetection(frame->width,frame->height);
         cvReleaseCapture(&cap);

       }
  private: System::Void Orange_Click(System::Object^  sender, System::EventArgs^  e)
       {
         if(activeColor != ORANGE)
         {
          activeColor = ORANGE;
          loadThresholdValues();
         }
       }
  private: System::Void Blue_Click(System::Object^  sender, System::EventArgs^  e)
       {
         if(activeColor != BLUE)
         {
          activeColor = BLUE;
          loadThresholdValues();
         }
       }
  private: System::Void Yellow_Click(System::Object^  sender, System::EventArgs^  e) 
       {
         if(activeColor != YELLOW)
         {
          activeColor = YELLOW;
          loadThresholdValues();
         }
       }
  private: System::Void Red_Click(System::Object^  sender, System::EventArgs^  e) 
       {
         if(activeColor != RED)
         {
          activeColor = RED;
          loadThresholdValues();
         }
       }
  private: System::Void White_Click(System::Object^  sender, System::EventArgs^  e)
       {
         if(activeColor != WHITE)
         {
          activeColor = WHITE;
          loadThresholdValues();
         }
       }
  private: System::Void Green_Click(System::Object^  sender, System::EventArgs^  e)
       {
         if(activeColor != GREEN)
         {
          activeColor = GREEN;
          loadThresholdValues();
         }
       }
  private: void loadThresholdValues()
       {
          this->trackBar1->Value = vision->Parameters[activeColor].minhsv.h;
          this->trackBar2->Value = vision->Parameters[activeColor].maxhsv.h;
          this->trackBar3->Value = vision->Parameters[activeColor].minhsv.s;
          this->trackBar4->Value = vision->Parameters[activeColor].maxhsv.s;;
          this->trackBar5->Value = vision->Parameters[activeColor].minhsv.v;;
          this->trackBar6->Value = vision->Parameters[activeColor].maxhsv.v;
          this->minBlobSizetrckbar->Value = vision->Parameters[activeColor].blobMinDist;
          this->maxBlobSizetrckbar->Value = vision->Parameters[activeColor].blobMaxDist;
       }

  
  private: System::Void save_Click(System::Object^  sender, System::EventArgs^  e)
       {
         vision->saveColorParameters();
         this->loadbtn->Enabled = true;
       }
  private: System::Void load_Click(System::Object^  sender, System::EventArgs^  e)
       {
         vision->loadColorParameters();
         this->loadThresholdValues();
       }
  
 
private: System::Void trackBar7_Scroll(System::Object^  sender, System::EventArgs^  e)
         {
           roixminlbl->Text = roixmintrckbar->Value.ToString();
           if(roixmintrckbar->Value > roixmaxtrckbar->Value)
           {
             roixmaxtrckbar->Value = roixmintrckbar->Value;
             roixmaxlbl->Text = roixmaxtrckbar->Value.ToString();
           }
           vision->rangeMin.x = roixmintrckbar->Value+1;
           vision->rangeMax.x = roixmaxtrckbar->Value-1;
         }
private: System::Void roixmaxtrckbar_Scroll(System::Object^  sender, System::EventArgs^  e) 
         {
           roixmaxlbl->Text = roixmaxtrckbar->Value.ToString();
           if(roixmintrckbar->Value > roixmaxtrckbar->Value)
           {
             roixmintrckbar->Value = roixmaxtrckbar->Value;
             roixminlbl->Text = roixmintrckbar->Value.ToString();
           }
           vision->rangeMin.x = roixmintrckbar->Value+1;
           vision->rangeMax.x = roixmaxtrckbar->Value-1;
         }
private: System::Void roiymintrckbar_Scroll(System::Object^  sender, System::EventArgs^  e) 
         {
            roiyminlbl->Text = roiymintrckbar->Value.ToString();
           if(roiymintrckbar->Value > roiymaxtrckbar->Value)
           {
             roiymaxtrckbar->Value = roiymintrckbar->Value;
             roiymaxlbl->Text = roiymaxtrckbar->Value.ToString();
           }
           vision->rangeMin.y = roiymintrckbar->Value+1;
           vision->rangeMax.y = roiymaxtrckbar->Value-1;
         }
private: System::Void roiymaxtrckbar_Scroll(System::Object^  sender, System::EventArgs^  e) 
         {
           roiymaxlbl->Text = roiymaxtrckbar->Value.ToString();
           if(roiymintrckbar->Value > roiymaxtrckbar->Value)
           {
             roiymintrckbar->Value = roiymaxtrckbar->Value;
             roiyminlbl->Text = roiymintrckbar->Value.ToString();
           }
           vision->rangeMin.y = roiymintrckbar->Value+1;
           vision->rangeMax.y = roiymaxtrckbar->Value-1;
         }
private: void drawFigures(IplImage * img)
         {
           if(showroichkbox->Checked)
           {
            cvRectangle(img,cvPoint(vision->rangeMin.x,vision->rangeMin.y),cvPoint(vision->rangeMax.x,vision->rangeMax.y),cvScalar(0,0,255),3);
           }
           if(this->BlobMode->Checked)
           {
             if(markersizechkbox->Checked)
             {
                for(int i = 0;i<vision->numBlobs[BLUE];i++)
                {
                  cvCircle(img,cvPoint(vision->blobArray[BLUE][i].center.x,vision->blobArray[BLUE][i].center.y),
                           vision->markerSize,
                          cvScalar(0,0,255),1); 
                }
                for(int i = 0;i<vision->numBlobs[YELLOW];i++)
                {
                  cvCircle(img,cvPoint(vision->blobArray[YELLOW][i].center.x,vision->blobArray[YELLOW][i].center.y),
                           vision->markerSize,
                          cvScalar(0,0,255),1); 
                }
             }
           }
        }
private: System::Void markerSizetrckbar_Scroll(System::Object^  sender, System::EventArgs^  e) 
         {
           this->label22->Text = markerSizetrckbar->Value.ToString();
           vision->markerSize = markerSizetrckbar->Value;
         }
private: System::Void loadBotSettingsbtn_Click(System::Object^  sender, System::EventArgs^  e) 
         {
           vision->loadBotParameters();
           this->markerSizetrckbar->Value = vision->markerSize;
         }
};
}

