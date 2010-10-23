VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form FrmCopyCD 
   BorderStyle     =   1  'Fest Einfach
   Caption         =   "Copy CD To Drive"
   ClientHeight    =   2850
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   6105
   Icon            =   "FrmCopyCD.frx":0000
   LinkTopic       =   "Copy "
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2850
   ScaleWidth      =   6105
   StartUpPosition =   1  'Fenstermitte
   Begin VB.ComboBox CmbDrives 
      Height          =   315
      Left            =   150
      Style           =   2  'Dropdown-Liste
      TabIndex        =   5
      Top             =   825
      Width           =   5835
   End
   Begin VB.Frame Frame1 
      Caption         =   "Progress"
      Height          =   885
      Left            =   135
      TabIndex        =   2
      Top             =   1290
      Width           =   5850
      Begin MSComctlLib.ProgressBar ProgressBar 
         Height          =   240
         Left            =   360
         TabIndex        =   3
         Top             =   270
         Width           =   5160
         _ExtentX        =   9102
         _ExtentY        =   423
         _Version        =   393216
         BorderStyle     =   1
         Appearance      =   0
      End
      Begin VB.Label LabelStatus 
         Caption         =   "Copy not started"
         Height          =   195
         Left            =   360
         TabIndex        =   4
         Top             =   570
         Width           =   5175
      End
   End
   Begin VB.Timer TimerProgress 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   2820
      Top             =   2325
   End
   Begin VB.CommandButton CmdCopy 
      Caption         =   "Start Copy"
      Height          =   495
      Left            =   3645
      TabIndex        =   1
      Top             =   2220
      Width           =   2340
   End
   Begin VB.Label Label1 
      Caption         =   $"FrmCopyCD.frx":1042
      Height          =   615
      Left            =   135
      TabIndex        =   0
      Top             =   90
      Width           =   5910
   End
End
Attribute VB_Name = "FrmCopyCD"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub CmdCopy_Click()
    If CmdCopy.Caption = "Start Copy" Then
        FrmBurn.DiscRecord.CopyCDToFixedDrive CmbDrives.ListIndex, TempPath & "cd_copy.iso"
        TimerProgress.Enabled = True
        LabelStatus.Caption = "Copying cd to temporary file"
        CmdCopy.Caption = "Stop Copy"
    Else
        CmdCopy.Enabled = False
        FrmBurn.DiscRecord.AbortCopy
    End If
End Sub

Private Sub Form_Load()
    On Error Resume Next
    CmbDrives.ListIndex = 0
End Sub

Private Sub TimerProgress_Timer()
    On Error Resume Next
    
    ProgressBar.Max = FrmBurn.DiscRecord.ProgressMax
    ProgressBar.Value = FrmBurn.DiscRecord.ProgressCur
    LabelStatus.Caption = "[" & Round((ProgressBar.Value / ProgressBar.Max) * 100, 2) & "%] Copying to file..."
    
End Sub

Public Sub Complete()
    'Called by event in frmburn
    
    TimerProgress.Enabled = False
    TimerProgress_Timer
    LabelStatus.Caption = "Complete"
    CmdCopy.Caption = "Start Copy"
    CmdCopy.Enabled = True
End Sub
