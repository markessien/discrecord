VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form FrmErase 
   BorderStyle     =   4  'Festes Werkzeugfenster
   Caption         =   "Erase CD-RW"
   ClientHeight    =   2565
   ClientLeft      =   45
   ClientTop       =   315
   ClientWidth     =   5700
   Icon            =   "FrmErase.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2565
   ScaleWidth      =   5700
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'Fenstermitte
   Begin VB.Timer TimerEraseProgress 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   1575
      Top             =   2085
   End
   Begin VB.CommandButton CmdErase 
      Caption         =   "Erase"
      Default         =   -1  'True
      Height          =   435
      Left            =   2595
      TabIndex        =   2
      Top             =   2040
      Width           =   1440
   End
   Begin VB.CommandButton CmdCancel 
      Caption         =   "Cancel"
      Height          =   435
      Left            =   4170
      TabIndex        =   1
      Top             =   2040
      Width           =   1440
   End
   Begin VB.Frame Frame1 
      Height          =   30
      Left            =   -75
      TabIndex        =   0
      Top             =   1890
      Width           =   6150
   End
   Begin VB.Frame Frame3 
      Height          =   1875
      Left            =   90
      TabIndex        =   9
      Top             =   -30
      Visible         =   0   'False
      Width           =   5535
      Begin MSComctlLib.ProgressBar ProgressBar1 
         Height          =   345
         Left            =   1020
         TabIndex        =   12
         Top             =   600
         Width           =   3855
         _ExtentX        =   6800
         _ExtentY        =   609
         _Version        =   393216
         Appearance      =   1
      End
      Begin VB.Label Label6 
         Alignment       =   2  'Zentriert
         Caption         =   "1 minute remaining"
         Height          =   345
         Left            =   1470
         TabIndex        =   13
         Top             =   1035
         Width           =   2790
      End
      Begin VB.Label Label5 
         Alignment       =   1  'Rechts
         Caption         =   "Progress:"
         Height          =   240
         Left            =   90
         TabIndex        =   11
         Top             =   660
         Width           =   855
      End
      Begin VB.Label Label4 
         Caption         =   "The disc is being erased. This process cannot be aborted."
         Height          =   375
         Left            =   270
         TabIndex        =   10
         Top             =   195
         Width           =   5025
      End
   End
   Begin VB.Frame Frame2 
      Height          =   1875
      Left            =   90
      TabIndex        =   3
      Top             =   -30
      Width           =   5535
      Begin VB.ComboBox CmbEraseType 
         Height          =   315
         ItemData        =   "FrmErase.frx":038A
         Left            =   780
         List            =   "FrmErase.frx":0394
         Style           =   2  'Dropdown-Liste
         TabIndex        =   5
         Top             =   1080
         Width           =   4680
      End
      Begin VB.ComboBox CmbSpeeds 
         Height          =   315
         Left            =   795
         Style           =   2  'Dropdown-Liste
         TabIndex        =   4
         Top             =   1440
         Width           =   4680
      End
      Begin VB.Label Label1 
         Caption         =   $"FrmErase.frx":03D7
         Height          =   855
         Left            =   90
         TabIndex        =   8
         Top             =   180
         Width           =   5355
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "Mode:"
         Height          =   195
         Left            =   90
         TabIndex        =   7
         Top             =   1110
         Width           =   450
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "Speed:"
         Height          =   195
         Left            =   90
         TabIndex        =   6
         Top             =   1500
         Width           =   510
      End
   End
End
Attribute VB_Name = "FrmErase"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub CmdCancel_Click()
    Unload Me
End Sub

Private Sub CmdErase_Click()
    'start erase
    CmdErase.Enabled = False
    CmdCancel.Enabled = False
    
    Frame2.Visible = False
    Frame3.Visible = True
    
    TimerEraseProgress.Enabled = True
'    FrmBurn.AudioRecord.StartDiscErase True
End Sub

Private Sub Form_Load()
    CmbEraseType.ListIndex = 0
    
    'Add maximum speed
    CmbSpeeds.AddItem "Maximum Speed"
    
    'copy the speeds from the other combo
    Dim i As Integer
    For i = 0 To FrmBurn.CmbSpeeds.ListCount - 1
        Me.CmbSpeeds.AddItem FrmBurn.CmbSpeeds.List(i)
    Next i
    
    CmbSpeeds.ListIndex = 0
End Sub

Private Sub TimerEraseProgress_Timer()
    'The progress of the erase can only be estimated,
    'so if you poll, and the drive is free for use again
    'then the erase is complete.
    
    If FrmBurn.AudioRecord.EraseProgress < 0 Then
        TimerEraseProgress.Enabled = False
    End If
    
End Sub
