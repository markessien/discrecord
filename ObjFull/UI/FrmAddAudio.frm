VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form FrmAddAudio 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Add Audio Track"
   ClientHeight    =   5880
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7455
   Icon            =   "FrmAddAudio.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5880
   ScaleWidth      =   7455
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton CmdRemove 
      Caption         =   "Remove"
      Height          =   480
      Left            =   2010
      TabIndex        =   7
      Top             =   3630
      Width           =   1710
   End
   Begin VB.CommandButton CmdClose 
      Caption         =   "Close"
      Height          =   480
      Left            =   5535
      TabIndex        =   6
      Top             =   5265
      Width           =   1710
   End
   Begin VB.Frame Frame1 
      Caption         =   "Options"
      Height          =   975
      Left            =   210
      TabIndex        =   3
      Top             =   4200
      Width           =   7035
      Begin VB.CheckBox Check2 
         Caption         =   "Normalise the audio. This will make the files to all have the same volume"
         Height          =   210
         Left            =   210
         TabIndex        =   5
         Top             =   630
         Width           =   5955
      End
      Begin VB.CheckBox Check1 
         Caption         =   "Fade between the tracks"
         Height          =   225
         Left            =   210
         TabIndex        =   4
         Top             =   285
         Width           =   3390
      End
   End
   Begin VB.CommandButton CmdAddAudio 
      Caption         =   "Add Music File..."
      Height          =   480
      Left            =   195
      TabIndex        =   2
      Top             =   3630
      Width           =   1710
   End
   Begin MSComctlLib.ListView LVFiles 
      Height          =   2865
      Left            =   180
      TabIndex        =   1
      Top             =   690
      Width           =   7080
      _ExtentX        =   12488
      _ExtentY        =   5054
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      GridLines       =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   2
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Filename"
         Object.Width           =   6068
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "Duration"
         Object.Width           =   2540
      EndProperty
   End
   Begin VB.Label Label1 
      Caption         =   $"FrmAddAudio.frx":038A
      ForeColor       =   &H00808080&
      Height          =   495
      Left            =   195
      TabIndex        =   0
      Top             =   120
      Width           =   7125
   End
End
Attribute VB_Name = "FrmAddAudio"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim listaudio As Collection

Private Sub CmdAddAudio_Click()
    'Add the audio track to the discrecord object
    
    'Set pattern
    Dim sPattern As String: sPattern = "All Audio Files|*.mp3;*.wav;*.ogg;*.mp2;*.mpg;*.wma;*.rma|All Files (*.*)|*.*||"
    
    'Show file open dialog
    Dim sFilename As String
    sFilename = FrmBurn.DiscRecord.FileSelectDialog(Me.hWnd, False, sPattern, "mp3", 1)
    
    'Check if the user selected anything
    If (sFilename > "") Then
            
        'Add the audio track. The duration is returned by this function
        Dim lv As ListItem
        Set lv = LVFiles.ListItems.Add(, , GetTitle(sFilename))
        lv.Tag = sFilename
        
        D
    End If
End Sub

Private Sub CmdClose_Click()

    If LVFiles.ListItems.Count > 0 Then
        FrmBurn.DiscRecord.AudioDisc.AddTrack LVFiles.ListItems.item(1).Tag
    End If
    
    If LVFiles.ListItems.Count > 1 Then
        Dim i As Integer
        For i = 2 To LVFiles.ListItems.Count
            FrmBurn.DiscRecord.AudioDisc.AddFile LVFiles.ListItems.item(i).Tag
        Next i
    End If
    
End Sub

Private Sub CmdRemove_Click()
    LVFiles.ListItems.Remove LVFiles.SelectedItem.Index
End Sub
