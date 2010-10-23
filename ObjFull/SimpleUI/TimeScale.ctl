VERSION 5.00
Begin VB.UserControl TimeScale 
   ClientHeight    =   465
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   7545
   ScaleHeight     =   465
   ScaleWidth      =   7545
   Begin VB.Shape Progress 
      FillColor       =   &H00FF8080&
      FillStyle       =   0  'Ausgefüllt
      Height          =   180
      Left            =   45
      Top             =   30
      Width           =   3825
   End
   Begin VB.Line LineBar 
      Index           =   0
      Visible         =   0   'False
      X1              =   5070
      X2              =   5070
      Y1              =   30
      Y2              =   255
   End
   Begin VB.Label LabelBar 
      Alignment       =   2  'Zentriert
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "0MB"
      BeginProperty Font 
         Name            =   "Small Fonts"
         Size            =   6
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   150
      Index           =   0
      Left            =   660
      TabIndex        =   0
      Top             =   225
      Width           =   315
   End
   Begin VB.Line LineBottomBorder 
      BorderColor     =   &H00FFFFFF&
      X1              =   -30
      X2              =   7470
      Y1              =   375
      Y2              =   375
   End
   Begin VB.Line LineLeftBorder 
      X1              =   0
      X2              =   0
      Y1              =   0
      Y2              =   360
   End
   Begin VB.Line LineTopborder 
      BorderColor     =   &H00808080&
      X1              =   15
      X2              =   7500
      Y1              =   0
      Y2              =   0
   End
   Begin VB.Line LineRightBorder 
      BorderColor     =   &H00FFFFFF&
      X1              =   7485
      X2              =   7485
      Y1              =   -15
      Y2              =   370
   End
End
Attribute VB_Name = "TimeScale"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Sub SetAudioMode()

    Dim i As Integer
    For i = 1 To 5
        LabelBar(i).Visible = True
        LabelBar(i).Caption = str(i * 20) & "min"
    Next i
    LabelBar(0).Caption = "0 min"
    LabelBar(5).Visible = False
    SetSize 0
    
    UserControl.Refresh
    
End Sub

Sub SetDataMode()
    Dim i As Integer
    For i = 1 To 5
        LabelBar(i).Visible = True
        LabelBar(i).Caption = str(i * 200) & "MB"
    Next i
    
    LabelBar(0).Caption = "0 MB"
    LabelBar(5).Visible = False
    SetSize 0
    
    UserControl.Refresh

End Sub
Private Sub UserControl_Initialize()
  '  progress.
   'Progress.Value = 100
    
    Dim i As Integer
    For i = 1 To 20
        Load LineBar(i)
        LineBar(i).Visible = True
    Next i
    
    For i = 1 To 5
        Load LabelBar(i)
        LabelBar(i).Visible = True
        LabelBar(i).Caption = str(i * 200) & "MB"
    Next i
    
    LabelBar(5).Visible = False
    
    SetSize 0
End Sub

Private Sub UserControl_Resize()
    
    LineRightBorder.Y1 = 0
    LineRightBorder.Y2 = UserControl.Height - 10
    LineRightBorder.X1 = UserControl.Width - 10
    LineRightBorder.X2 = UserControl.Width - 10
    
    LineLeftBorder.Y1 = 0
    LineLeftBorder.Y2 = UserControl.Height - 10
    LineLeftBorder.X1 = 10
    LineLeftBorder.X2 = 10
    
    LineBottomBorder.Y1 = UserControl.Height - 10
    LineBottomBorder.Y2 = UserControl.Height - 10
    LineBottomBorder.X1 = 0
    LineBottomBorder.X2 = UserControl.Width - 10
    
    LineTopborder.Y1 = 10
    LineTopborder.Y2 = 10
    LineTopborder.X1 = 0
    LineTopborder.X2 = UserControl.Width - 10
    
    Progress.Top = 50
    Progress.Height = UserControl.Height * (4 / 10)
    Progress.Left = 50
 '   Progress.Width = UserControl.Width - (Progress.Left + 10 + 5)
    
    Dim i As Integer
    For i = 1 To 20
        LineBar(i).Y1 = 10
        LineBar(i).Y2 = UserControl.Height / 2
        LineBar(i).X1 = i * (UserControl.Width / 20)
        LineBar(i).X2 = LineBar(i).X1
    Next i
    
    LabelBar(0).Left = 10
    LabelBar(0).Top = UserControl.Height - LabelBar(0).Height
    For i = 1 To 5
        LabelBar(i).Top = UserControl.Height - LabelBar(i).Height
        LabelBar(i).Left = (i * (UserControl.Width / 5)) - (LabelBar(i).Width / 2)
    Next i
End Sub

Sub SetDuration(nDuration As Double)
    Progress.Width = (nDuration / 100) * (UserControl.Width - 20)
    Progress.Refresh
End Sub

Sub SetSize(nSize As Long)
    Progress.Width = (nSize / 1000) * (UserControl.Width - 20)
    Progress.Refresh
End Sub

