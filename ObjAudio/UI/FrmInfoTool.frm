VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form FrmInfoTool 
   BorderStyle     =   1  'Fest Einfach
   Caption         =   "Drive Info"
   ClientHeight    =   3810
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   4830
   Icon            =   "FrmInfoTool.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3810
   ScaleWidth      =   4830
   StartUpPosition =   1  'Fenstermitte
   Begin TabDlg.SSTab SSTab1 
      Height          =   3600
      Left            =   15
      TabIndex        =   0
      Top             =   75
      Width           =   4680
      _ExtentX        =   8255
      _ExtentY        =   6350
      _Version        =   393216
      Style           =   1
      Tab             =   2
      TabHeight       =   520
      TabCaption(0)   =   "  Drive Info"
      TabPicture(0)   =   "FrmInfoTool.frx":038A
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "Frame1"
      Tab(0).ControlCount=   1
      TabCaption(1)   =   "Read Features"
      TabPicture(1)   =   "FrmInfoTool.frx":0724
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "Frame2"
      Tab(1).ControlCount=   1
      TabCaption(2)   =   "Write Features"
      TabPicture(2)   =   "FrmInfoTool.frx":0740
      Tab(2).ControlEnabled=   -1  'True
      Tab(2).Control(0)=   "Frame3"
      Tab(2).Control(0).Enabled=   0   'False
      Tab(2).ControlCount=   1
      Begin VB.Frame Frame3 
         Caption         =   "Supported write features"
         Height          =   2955
         Left            =   90
         TabIndex        =   22
         Top             =   420
         Width           =   4485
         Begin VB.CheckBox ChkCDR_w 
            Caption         =   "CD-R"
            Height          =   270
            Left            =   210
            TabIndex        =   27
            Top             =   345
            Width           =   975
         End
         Begin VB.CheckBox ChkDVDR_w 
            Caption         =   "DVD-R"
            Height          =   270
            Left            =   210
            TabIndex        =   26
            Top             =   1440
            Width           =   1755
         End
         Begin VB.CheckBox ChkCDRW_w 
            Caption         =   "CD-RW"
            Height          =   270
            Left            =   210
            TabIndex        =   25
            Top             =   712
            Width           =   990
         End
         Begin VB.CheckBox ChkDVDRAM_w 
            Caption         =   "DVD-RAM"
            Height          =   270
            Left            =   210
            TabIndex        =   24
            Top             =   1079
            Width           =   1170
         End
         Begin VB.CheckBox ChkBuf 
            Caption         =   "Buffer Underrun protection"
            Height          =   585
            Left            =   210
            TabIndex        =   23
            Top             =   1665
            Width           =   1755
         End
      End
      Begin VB.Frame Frame2 
         Caption         =   "Supported read features"
         Height          =   2955
         Left            =   -74910
         TabIndex        =   16
         Top             =   420
         Width           =   4485
         Begin VB.CheckBox ChkDVDRAM 
            Caption         =   "DVD-RAM"
            Height          =   270
            Left            =   210
            TabIndex        =   21
            Top             =   1095
            Width           =   1755
         End
         Begin VB.CheckBox ChkCDRW 
            Caption         =   "CD-RW"
            Height          =   270
            Left            =   210
            TabIndex        =   20
            Top             =   720
            Width           =   1755
         End
         Begin VB.CheckBox ChkDVDROM 
            Caption         =   "DVD-ROM"
            Height          =   270
            Left            =   210
            TabIndex        =   19
            Top             =   1455
            Width           =   1755
         End
         Begin VB.CheckBox ChkDVDR 
            Caption         =   "DVD-R"
            Height          =   270
            Left            =   210
            TabIndex        =   18
            Top             =   1830
            Width           =   1755
         End
         Begin VB.CheckBox ChkCDR 
            Caption         =   "CD-R"
            Height          =   270
            Left            =   210
            TabIndex        =   17
            Top             =   360
            Width           =   1755
         End
      End
      Begin VB.Frame Frame1 
         Caption         =   "General"
         Height          =   2610
         Left            =   -74910
         TabIndex        =   1
         Top             =   420
         Width           =   4485
         Begin VB.ComboBox CmbWriteSpeeds 
            Height          =   315
            Left            =   1530
            TabIndex        =   6
            Top             =   1230
            Width           =   2625
         End
         Begin VB.ComboBox CmbReadSpeed 
            Height          =   315
            Left            =   1530
            TabIndex        =   4
            Top             =   855
            Width           =   2625
         End
         Begin VB.Label LabSerial 
            Caption         =   "AAAA 0000 AAAA"
            Height          =   240
            Left            =   1515
            TabIndex        =   15
            Top             =   2280
            Width           =   1515
         End
         Begin VB.Label LabDate 
            Caption         =   "0 Bytes"
            Height          =   240
            Left            =   1515
            TabIndex        =   14
            Top             =   1965
            Width           =   1515
         End
         Begin VB.Label LabBufSize 
            Caption         =   "0 Bytes"
            Height          =   240
            Left            =   1515
            TabIndex        =   13
            Top             =   1650
            Width           =   1515
         End
         Begin VB.Label LabFirmware 
            Caption         =   "0.00.00"
            Height          =   165
            Left            =   1530
            TabIndex        =   12
            Top             =   585
            Width           =   1515
         End
         Begin VB.Label Label8 
            Alignment       =   1  'Rechts
            Caption         =   "Serial Number:"
            Height          =   180
            Left            =   210
            TabIndex        =   11
            Top             =   2280
            Width           =   1125
         End
         Begin VB.Label Label7 
            Alignment       =   1  'Rechts
            Caption         =   "Date:"
            Height          =   255
            Left            =   510
            TabIndex        =   10
            Top             =   1965
            Width           =   825
         End
         Begin VB.Label Label6 
            Alignment       =   1  'Rechts
            Caption         =   "Buffer Size:"
            Height          =   225
            Left            =   435
            TabIndex        =   9
            Top             =   1650
            Width           =   900
         End
         Begin VB.Label Label5 
            Caption         =   "Firmware version:"
            Height          =   225
            Left            =   120
            TabIndex        =   8
            Top             =   570
            Width           =   1290
         End
         Begin VB.Label LabName 
            Caption         =   "Unknown Device"
            Height          =   165
            Left            =   1515
            TabIndex        =   7
            Top             =   285
            Width           =   2805
         End
         Begin VB.Label Label3 
            Alignment       =   1  'Rechts
            Caption         =   "Write Speed:"
            Height          =   255
            Left            =   390
            TabIndex        =   5
            Top             =   1290
            Width           =   960
         End
         Begin VB.Label Label2 
            Caption         =   "Read Speed:"
            Height          =   255
            Left            =   405
            TabIndex        =   3
            Top             =   915
            Width           =   960
         End
         Begin VB.Label Label1 
            Alignment       =   1  'Rechts
            Caption         =   "Name:"
            Height          =   255
            Left            =   90
            TabIndex        =   2
            Top             =   270
            Width           =   1245
         End
      End
   End
End
Attribute VB_Name = "FrmInfoTool"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()

    'copy the speeds from the other combo
'    Dim i As Integer
'    For i = 0 To UserDocument.CmbSpeeds.ListCount - 1
'        Me.CmbWriteSpeeds.AddItem FrmBurn.CmbSpeeds.List(i)
'    Next i
'
'    CmbWriteSpeeds.ListIndex = 0

    Dim strName As String
    Dim strFirmware As String
    Dim nBufferSize As Long
    Dim strDate As String
    Dim strSerial As String

    FrmBurn.AudioRecord.GetDriveInfo strName, strFirmware, nBufferSize, strDate, strSerial
    LabBufSize.Caption = FormatSize(CDbl(nBufferSize * 1024))
    LabName.Caption = strName
    LabFirmware.Caption = strFirmware
    LabDate.Caption = strDate
    LabSerial.Caption = strSerial

    FrmBurn.AudioRecord.ListAvailableReadSpeeds
    CmbReadSpeed.ListIndex = 0

    ChkCDR.Value = IIf(FrmBurn.AudioRecord.ReadFeatureSupported(featureCDR) = featureSupported, 1, 0)
    ChkCDRW.Value = IIf(FrmBurn.AudioRecord.ReadFeatureSupported(featureCDRW) = featureSupported, 1, 0)
    ChkDVDRAM.Value = IIf(FrmBurn.AudioRecord.ReadFeatureSupported(featureDVDRAM) = featureSupported, 1, 0)
    ChkDVDROM.Value = IIf(FrmBurn.AudioRecord.ReadFeatureSupported(featureDVDROM) = featureSupported, 1, 0)
    ChkDVDR.Value = IIf(FrmBurn.AudioRecord.ReadFeatureSupported(featureDVDR) = featureSupported, 1, 0)

    ChkCDR_w.Value = IIf(FrmBurn.AudioRecord.WriteFeatureSupported(featureCDR) = featureSupported, 1, 0)
    ChkCDRW_w.Value = IIf(FrmBurn.AudioRecord.WriteFeatureSupported(featureCDRW) = featureSupported, 1, 0)
    ChkDVDRAM_w.Value = IIf(FrmBurn.AudioRecord.WriteFeatureSupported(featureDVDRAM) = featureSupported, 1, 0)
    ChkBuf.Value = IIf(FrmBurn.AudioRecord.WriteFeatureSupported(featureBufferProtect) = featureSupported, 1, 0)
    ChkDVDR_w.Value = IIf(FrmBurn.AudioRecord.WriteFeatureSupported(featureDVDR) = featureSupported, 1, 0)
    
End Sub
