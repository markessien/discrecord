VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form FrmCopyCD 
   BorderStyle     =   1  'Fest Einfach
   Caption         =   "Copy CD"
   ClientHeight    =   2730
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   6630
   Icon            =   "FrmCopyCD.frx":0000
   LinkTopic       =   "Copy "
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2730
   ScaleWidth      =   6630
   StartUpPosition =   3  'Windows-Standard
   Begin VB.CommandButton Command1 
      Caption         =   "Start Copy"
      Height          =   645
      Left            =   4125
      TabIndex        =   5
      Top             =   1920
      Width           =   2340
   End
   Begin VB.ComboBox CmbSpeeds 
      Height          =   315
      Left            =   1710
      Style           =   2  'Dropdown-Liste
      TabIndex        =   3
      Top             =   1245
      Width           =   2250
   End
   Begin MSComctlLib.ImageCombo ImageCombo1 
      Height          =   330
      Left            =   1710
      TabIndex        =   2
      Top             =   855
      Width           =   4710
      _ExtentX        =   8308
      _ExtentY        =   582
      _Version        =   393216
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      Text            =   "ImageCombo1"
   End
   Begin VB.Label Label7 
      Alignment       =   1  'Rechts
      BackStyle       =   0  'Transparent
      Caption         =   "Read Speed:"
      Height          =   225
      Left            =   405
      TabIndex        =   4
      Top             =   1290
      Width           =   1110
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Rechts
      Caption         =   "Source Device:"
      Height          =   240
      Left            =   360
      TabIndex        =   1
      Top             =   900
      Width           =   1260
   End
   Begin VB.Label Label1 
      Caption         =   $"FrmCopyCD.frx":1042
      Height          =   615
      Left            =   405
      TabIndex        =   0
      Top             =   75
      Width           =   6015
   End
End
Attribute VB_Name = "FrmCopyCD"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Label3_Click()

End Sub
