VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{49520E94-02E9-45CC-BD4C-41274ACA4538}#1.0#0"; "DiscRecord.dll"
Begin VB.Form FrmBurn 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Burn!"
   ClientHeight    =   7035
   ClientLeft      =   150
   ClientTop       =   540
   ClientWidth     =   8625
   Icon            =   "FrmBurn.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7035
   ScaleWidth      =   8625
   StartUpPosition =   3  'Windows Default
   Begin Burn.TimeScale TimeScale 
      Height          =   420
      Left            =   105
      TabIndex        =   13
      Top             =   5940
      Width           =   5085
      _ExtentX        =   8969
      _ExtentY        =   741
   End
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   6165
      Top             =   4395
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   16711935
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   20
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":628A
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":63E4
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":697E
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":6F18
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":74B2
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":784C
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":7BE6
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":7F80
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":8FD2
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":A024
            Key             =   ""
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":A3BE
            Key             =   ""
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":A758
            Key             =   ""
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":AAF2
            Key             =   ""
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":AE8C
            Key             =   ""
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":B226
            Key             =   ""
         EndProperty
         BeginProperty ListImage16 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":B5C0
            Key             =   ""
         EndProperty
         BeginProperty ListImage17 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":BB3E
            Key             =   ""
         EndProperty
         BeginProperty ListImage18 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":C070
            Key             =   ""
         EndProperty
         BeginProperty ListImage19 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":C5C2
            Key             =   ""
         EndProperty
         BeginProperty ListImage20 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":CB14
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Frame FrameBottomSep 
      Height          =   90
      Index           =   0
      Left            =   -165
      TabIndex        =   3
      Top             =   6360
      Width           =   11025
   End
   Begin MSComctlLib.ListView LVFiles 
      Height          =   4875
      Left            =   90
      TabIndex        =   2
      Top             =   1005
      Width           =   5100
      _ExtentX        =   8996
      _ExtentY        =   8599
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      FullRowSelect   =   -1  'True
      _Version        =   393217
      SmallIcons      =   "ImageList1"
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
         Text            =   "Size"
         Object.Width           =   2364
      EndProperty
   End
   Begin MSComctlLib.StatusBar Status 
      Align           =   2  'Align Bottom
      Height          =   270
      Left            =   0
      TabIndex        =   1
      Top             =   6765
      Width           =   8625
      _ExtentX        =   15214
      _ExtentY        =   476
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   3
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   10028
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   2
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   2
         EndProperty
      EndProperty
   End
   Begin TabDlg.SSTab SSTab 
      Height          =   5730
      Left            =   5265
      TabIndex        =   0
      Top             =   600
      Width           =   3270
      _ExtentX        =   5768
      _ExtentY        =   10107
      _Version        =   393216
      Tabs            =   1
      TabsPerRow      =   1
      TabHeight       =   520
      TabCaption(0)   =   "Burn Settings"
      TabPicture(0)   =   "FrmBurn.frx":D0AE
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "FrameProgress"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "FrameWrite"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "CmdBurn"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "TimerBurnProgress"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).ControlCount=   4
      Begin VB.Timer TimerBurnProgress 
         Enabled         =   0   'False
         Interval        =   100
         Left            =   465
         Top             =   4140
      End
      Begin VB.CommandButton CmdBurn 
         Caption         =   "Start Burn!"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   780
         Left            =   120
         Picture         =   "FrmBurn.frx":D0CA
         Style           =   1  'Graphical
         TabIndex        =   11
         Top             =   4860
         Width           =   3045
      End
      Begin VB.Frame FrameWrite 
         Caption         =   "Write settings"
         Height          =   4260
         Left            =   120
         TabIndex        =   4
         Top             =   390
         Width           =   3045
         Begin VB.TextBox TxtLabel 
            Height          =   300
            Left            =   750
            TabIndex        =   46
            Text            =   "New CD"
            Top             =   2910
            Width           =   2220
         End
         Begin VB.TextBox TxtAudioPause 
            Height          =   315
            Left            =   735
            TabIndex        =   42
            Text            =   "2"
            Top             =   2565
            Width           =   2235
         End
         Begin VB.ComboBox CmbComm 
            Height          =   315
            ItemData        =   "FrmBurn.frx":E10C
            Left            =   735
            List            =   "FrmBurn.frx":E116
            Style           =   2  'Dropdown List
            TabIndex        =   18
            Top             =   2190
            Width           =   2250
         End
         Begin VB.ComboBox CmbWriteType 
            Height          =   315
            ItemData        =   "FrmBurn.frx":E126
            Left            =   735
            List            =   "FrmBurn.frx":E130
            Style           =   2  'Dropdown List
            TabIndex        =   16
            Top             =   1845
            Width           =   2250
         End
         Begin VB.ComboBox CmbBuffer 
            Height          =   315
            ItemData        =   "FrmBurn.frx":E15D
            Left            =   735
            List            =   "FrmBurn.frx":E167
            Style           =   2  'Dropdown List
            TabIndex        =   15
            Top             =   1485
            Width           =   2250
         End
         Begin VB.ComboBox CmbMode 
            Height          =   315
            ItemData        =   "FrmBurn.frx":E186
            Left            =   735
            List            =   "FrmBurn.frx":E190
            Style           =   2  'Dropdown List
            TabIndex        =   10
            Top             =   1095
            Width           =   2250
         End
         Begin VB.ComboBox CmbSpeeds 
            Height          =   315
            Left            =   720
            Style           =   2  'Dropdown List
            TabIndex        =   7
            Top             =   690
            Width           =   2250
         End
         Begin MSComctlLib.ImageCombo CmbDevice 
            Height          =   330
            Left            =   720
            TabIndex        =   5
            Top             =   285
            Width           =   2250
            _ExtentX        =   3969
            _ExtentY        =   582
            _Version        =   393216
            ForeColor       =   -2147483640
            BackColor       =   -2147483643
            ImageList       =   "ImageList1"
         End
         Begin VB.Label Label8 
            Alignment       =   1  'Right Justify
            Caption         =   "Label:"
            Height          =   240
            Left            =   165
            TabIndex        =   47
            Top             =   2970
            Width           =   510
         End
         Begin VB.Label Label4 
            Alignment       =   1  'Right Justify
            Caption         =   "Pause:"
            Height          =   210
            Left            =   45
            TabIndex        =   41
            Top             =   2595
            Width           =   660
         End
         Begin VB.Label Label12 
            Alignment       =   1  'Right Justify
            Caption         =   "Comm:"
            Height          =   210
            Left            =   30
            TabIndex        =   19
            Top             =   2250
            Width           =   660
         End
         Begin VB.Label Label9 
            Alignment       =   1  'Right Justify
            Caption         =   "Write:"
            Height          =   210
            Left            =   30
            TabIndex        =   17
            Top             =   1905
            Width           =   660
         End
         Begin VB.Label Label5 
            Alignment       =   1  'Right Justify
            Caption         =   "Buffer:"
            Height          =   210
            Left            =   30
            TabIndex        =   14
            Top             =   1545
            Width           =   660
         End
         Begin VB.Label Label2 
            Alignment       =   1  'Right Justify
            BackStyle       =   0  'Transparent
            Caption         =   "Mode:"
            Height          =   225
            Left            =   90
            TabIndex        =   9
            Top             =   1170
            Width           =   585
         End
         Begin VB.Label Label7 
            Alignment       =   1  'Right Justify
            BackStyle       =   0  'Transparent
            Caption         =   "Speed:"
            Height          =   225
            Left            =   90
            TabIndex        =   8
            Top             =   765
            Width           =   585
         End
         Begin VB.Label Label1 
            Caption         =   "Device:"
            Height          =   210
            Left            =   105
            TabIndex        =   6
            Top             =   345
            Width           =   555
         End
      End
      Begin VB.Frame FrameProgress 
         Caption         =   "Write Progress"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   4275
         Left            =   90
         TabIndex        =   20
         Top             =   405
         Visible         =   0   'False
         Width           =   3045
         Begin MSComctlLib.ProgressBar ProgressBurn 
            Height          =   285
            Left            =   900
            TabIndex        =   26
            Top             =   315
            Width           =   2055
            _ExtentX        =   3625
            _ExtentY        =   503
            _Version        =   393216
            BorderStyle     =   1
            Appearance      =   0
            Scrolling       =   1
         End
         Begin VB.Label LabelStatus 
            Caption         =   "Conversion not started."
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   705
            Left            =   855
            TabIndex        =   40
            Top             =   3255
            Width           =   2100
         End
         Begin VB.Label LabelTrack 
            AutoSize        =   -1  'True
            Caption         =   "0"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   855
            TabIndex        =   39
            Top             =   2910
            Width           =   90
         End
         Begin VB.Label LabelLBA 
            AutoSize        =   -1  'True
            Caption         =   "0"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   855
            TabIndex        =   38
            Top             =   2595
            Width           =   90
         End
         Begin VB.Label Label24 
            Alignment       =   1  'Right Justify
            Caption         =   "Status:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   210
            Left            =   15
            TabIndex        =   37
            Top             =   3255
            Width           =   780
         End
         Begin VB.Label Label23 
            Alignment       =   1  'Right Justify
            Caption         =   "Cur Track:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   210
            Left            =   30
            TabIndex        =   36
            Top             =   2910
            Width           =   780
         End
         Begin VB.Label Label22 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "Cur LBA:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   180
            TabIndex        =   35
            Top             =   2595
            Width           =   630
         End
         Begin VB.Label LabelDriveBuffer 
            AutoSize        =   -1  'True
            Caption         =   "Not scanned"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   855
            TabIndex        =   34
            Top             =   2280
            Width           =   900
         End
         Begin VB.Label LabelFileBuf 
            AutoSize        =   -1  'True
            Caption         =   "0 Bytes of 0 bytes"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   855
            TabIndex        =   33
            Top             =   1980
            Width           =   1320
         End
         Begin VB.Label LabelElapsed 
            AutoSize        =   -1  'True
            Caption         =   "0:00"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   855
            TabIndex        =   32
            Top             =   1665
            Width           =   330
         End
         Begin VB.Label LabelTime 
            AutoSize        =   -1  'True
            Caption         =   "0:00 of 0:00"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   855
            TabIndex        =   31
            Top             =   1350
            Width           =   900
         End
         Begin VB.Label LabelBytes 
            AutoSize        =   -1  'True
            Caption         =   "0 Bytes of 0 Bytes"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   855
            TabIndex        =   30
            Top             =   1020
            Width           =   1320
         End
         Begin VB.Label Label18 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "Drive Buf:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   90
            TabIndex        =   29
            Top             =   2280
            Width           =   720
         End
         Begin VB.Label Label17 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "File Buf:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   225
            TabIndex        =   28
            Top             =   1980
            Width           =   585
         End
         Begin VB.Label LabelPercent 
            AutoSize        =   -1  'True
            Caption         =   "0%"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   855
            TabIndex        =   27
            Top             =   720
            Width           =   255
         End
         Begin VB.Label Label15 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "Progress:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   120
            TabIndex        =   25
            Top             =   345
            Width           =   690
         End
         Begin VB.Label Label14 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            BackStyle       =   0  'Transparent
            Caption         =   "Progress:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   120
            TabIndex        =   24
            Top             =   705
            Width           =   690
         End
         Begin VB.Label Label13 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            BackStyle       =   0  'Transparent
            Caption         =   "Bytes:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   345
            TabIndex        =   23
            Top             =   1020
            Width           =   465
         End
         Begin VB.Label Label11 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "Time:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   405
            TabIndex        =   22
            Top             =   1350
            Width           =   390
         End
         Begin VB.Label Label3 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "Elapsed:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   195
            Left            =   195
            TabIndex        =   21
            Top             =   1665
            Width           =   615
         End
      End
   End
   Begin MSComctlLib.Toolbar TBFiles 
      Height          =   330
      Left            =   4515
      TabIndex        =   43
      Top             =   600
      Width           =   705
      _ExtentX        =   1244
      _ExtentY        =   582
      ButtonWidth     =   609
      ButtonHeight    =   582
      Style           =   1
      ImageList       =   "ImageList1"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   2
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            ImageIndex      =   18
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            ImageIndex      =   19
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageCombo CmbType 
      Height          =   330
      Left            =   105
      TabIndex        =   44
      Top             =   600
      Width           =   4380
      _ExtentX        =   7726
      _ExtentY        =   582
      _Version        =   393216
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      Text            =   "Data CD (ISO 9660)"
      ImageList       =   "ImageList1"
   End
   Begin MSComctlLib.Toolbar TBMain 
      Height          =   330
      Left            =   15
      TabIndex        =   45
      Top             =   6435
      Width           =   8985
      _ExtentX        =   15849
      _ExtentY        =   582
      ButtonWidth     =   2408
      ButtonHeight    =   582
      Wrappable       =   0   'False
      Style           =   1
      TextAlignment   =   1
      ImageList       =   "ImageList1"
      DisabledImageList=   "ImageListPlayer"
      HotImageList    =   "ImageListPlayer"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   9
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Add File..."
            ImageIndex      =   3
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Add Dir..."
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Play   "
            Style           =   3
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Add Audio..."
            ImageIndex      =   4
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Remove Item"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Extra Tools"
            ImageIndex      =   10
            Style           =   5
            BeginProperty ButtonMenus {66833FEC-8583-11D1-B16A-00C0F0283628} 
               NumButtonMenus  =   6
               BeginProperty ButtonMenu1 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "Erase"
                  Text            =   "Erase CD/RW"
               EndProperty
               BeginProperty ButtonMenu2 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Text            =   "-"
               EndProperty
               BeginProperty ButtonMenu3 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "CopyCD"
                  Text            =   "Copy CD"
               EndProperty
               BeginProperty ButtonMenu4 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "BurnIso"
                  Text            =   "Burn ISO..."
               EndProperty
               BeginProperty ButtonMenu5 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Text            =   "-"
               EndProperty
               BeginProperty ButtonMenu6 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "DriveInfo"
                  Text            =   "Drive Info"
               EndProperty
            EndProperty
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
      EndProperty
   End
   Begin DISCRECORDLibCtl.DiscRecord DiscRecord 
      Left            =   4950
      OleObjectBlob   =   "FrmBurn.frx":E1BD
      Top             =   30
   End
   Begin VB.Label Label6 
      BackStyle       =   0  'Transparent
      Caption         =   "Essien Research && Development Burn!"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   225
      Left            =   720
      TabIndex        =   12
      Top             =   165
      Width           =   6540
   End
   Begin VB.Image Image2 
      Height          =   480
      Left            =   90
      Picture         =   "FrmBurn.frx":E1E1
      Top             =   15
      Width           =   480
   End
   Begin VB.Image Image1 
      Height          =   240
      Left            =   8145
      Picture         =   "FrmBurn.frx":EEAB
      Top             =   165
      Width           =   240
   End
   Begin VB.Shape Shape1 
      FillColor       =   &H00FFFFFF&
      FillStyle       =   0  'Solid
      Height          =   540
      Left            =   -45
      Top             =   -15
      Width           =   8700
   End
   Begin VB.Menu PopupDataFile 
      Caption         =   "PopupDataFiles"
      Visible         =   0   'False
      Begin VB.Menu mnuCreateDir 
         Caption         =   "Create Directory"
      End
      Begin VB.Menu dash 
         Caption         =   "-"
      End
      Begin VB.Menu mnuAddFile 
         Caption         =   "Add File..."
      End
      Begin VB.Menu mnuAddFolder 
         Caption         =   "Add Folder..."
      End
      Begin VB.Menu dash2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuMoveUp 
         Caption         =   "Move Up"
      End
      Begin VB.Menu mnuMoveDown 
         Caption         =   "Move Down"
      End
      Begin VB.Menu dash7 
         Caption         =   "-"
      End
      Begin VB.Menu mnuRemove 
         Caption         =   "Remove"
      End
   End
End
Attribute VB_Name = "FrmBurn"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim m_CurDir As FileItem

Private Sub CmbComm_Click()
    DiscRecord.CommunicationMethod = IIf(CmbComm.ListIndex = 1, commASPI, commSPTI)
End Sub

Private Sub CmbDevice_Click()
    DiscRecord.SelectedWriterDeviceIndex = CmbDevice.SelectedItem.Index - 1
    CmbSpeeds.Clear
    DiscRecord.ListAvailableWriteSpeeds
    
    On Error Resume Next
    CmbSpeeds.ListIndex = CmbSpeeds.ListCount - 1
End Sub

Private Sub CmbType_Click()
    'Called when the type combo selection is changed
    
    Select Case CmbType.SelectedItem.Index
    Case 1 ' switch to data cd creation mode
        SwitchToDataMode
    Case CmbType.ComboItems.Count 'switch to audio cd creation mode
        SwitchToAudioMode
    Case Else
        'We are selecting a sub directory in data cd mode.
        
        'Get the number of levels we should go up to
        Dim iLevelsUp As Long
        iLevelsUp = CmbType.ComboItems.Count - (CmbType.SelectedItem.Index + 1)
        
        'loop through the parents of the parents till we reach the
        'directory that was selected
        Dim curDir As FileItem
        Set curDir = m_CurDir
        
        Do While iLevelsUp > 0
            Set curDir = curDir.Parent
            iLevelsUp = iLevelsUp - 1
        Loop
        
        'Set the found directory to the current one, and update the listing
        Set m_CurDir = curDir
        RefreshDataFiles
        
        'Remove all the other combo items for the lower directories
        Dim i As Integer
        For i = CmbType.ComboItems.Count - 1 To CmbType.SelectedItem.Index + 1 Step -1
            CmbType.ComboItems.Remove i
        Next i
    End Select
End Sub

Sub SwitchToAudioMode()
    'Switches the app to burn an audio cd
    
    'Clear the combo, so that if any data directory is inside
    'it will be remvoed
    CmbType.ComboItems.Clear
    FillTypeCombo
    CmbType.ComboItems.item(CmbType.ComboItems.Count).Selected = True
    
    'Enable and disable the proper menus and toolbars
    TBMain.Buttons(1).Enabled = False
    TBMain.Buttons(2).Enabled = False
    TBMain.Buttons(4).Enabled = True
    TBFiles.Buttons(1).Enabled = False
    TBFiles.Buttons(2).Enabled = False
    mnuAddFile.Enabled = False
    mnuAddFolder.Enabled = False
    TxtAudioPause.Enabled = True
    
    'Change the scale to seconds/minutes
    TimeScale.SetAudioMode
    
    LVFiles.ColumnHeaders(2).Text = "Duration"
    
    'We cannot specify the label of an audio cd, so we disable
    'this textbox
    TxtLabel.Enabled = False

End Sub

Sub SwitchToDataMode()
    CmbType.ComboItems.Clear
    FillTypeCombo
    CmbType.ComboItems.item(1).Selected = True
    LVFiles.ListItems.Clear
    TBMain.Buttons(1).Enabled = True
    TBMain.Buttons(2).Enabled = True
    TBMain.Buttons(4).Enabled = False
    
    Set m_CurDir = DiscRecord.DataDisc
    RefreshDataFiles
    
    LVFiles.ColumnHeaders(2).Text = "Size"
    TxtLabel.Enabled = True
    
    If m_CurDir.Parent Is Nothing Then
        TBFiles.Buttons(1).Enabled = False
    Else
        TBFiles.Buttons(1).Enabled = True
    End If
    
    TBFiles.Buttons(2).Enabled = True
    TimeScale.SetDataMode
    mnuAddFile.Enabled = True
    mnuAddFolder.Enabled = True
    TxtAudioPause.Enabled = False
End Sub

Sub FillTypeCombo()
    CmbType.ComboItems.Add , , "Data CD (ISO 9660)", 6, 6
    CmbType.ComboItems.Add , , "Audio CD (Red Book CD-DA)", 5, 5
End Sub

Private Sub CmdBurn_Click()
        
    If CmdBurn.Caption = "Stop Burn!" Then
        
        CmdBurn.Enabled = False
        SSTab.TabCaption(0) = "Burn Settings"
        CmdBurn.Caption = "Start Burn!"
        DoEvents
        
        DiscRecord.AbortBurn
        
        FrameProgress.Visible = False
        FrameWrite.Visible = True
    Else
        
        CmdBurn.Enabled = False
        CmdBurn.Caption = "Stop Burn!"
        
        SSTab.TabCaption(0) = "Burn progress"
        
        'Reset the objects
        ProgressBurn.Min = 0
        ProgressBurn.Max = 100
        ProgressBurn.Value = 0
        
        'Show progress
        FrameWrite.Visible = False
        FrameProgress.Visible = True
        DoEvents
        
        ' Set the record properties
        DiscRecord.TestMode = IIf(CmbMode.ListIndex = 0, True, False)
        DiscRecord.CurrentWriteSpeed = Val(CmbSpeeds.List(CmbSpeeds.ListIndex))
        DiscRecord.CDLabel = TxtLabel.Text
        DiscRecord.BurnProof = IIf(CmbBuffer.ListIndex = 0, False, True)
        DiscRecord.PauseBetweenTracks = Val(TxtAudioPause.Text)
        DiscRecord.WriteType = IIf(CmbWriteType.ListIndex = 0, writeTAO, writeSAO)
        
        TimerBurnProgress.Enabled = True
        
        If InDataMode Then
            DiscRecord.BurnDataCD
        Else
            DiscRecord.BurnAudioCD
        End If
        
        CmdBurn.Enabled = True
        
    End If
    
End Sub

Private Sub CmdTest_Click()
     
    CmdBurn.Enabled = False
    CmdBurn.Caption = "Stop Burn!"
    
    SSTab.TabCaption(0) = "Burn progress"
    
    'Reset the objects
    ProgressBurn.Min = 0
    ProgressBurn.Max = 100
    ProgressBurn.Value = 0
    
    'Show progress
    FrameWrite.Visible = False
    FrameProgress.Visible = True
    DoEvents
    
    ' Set the record properties
    DiscRecord.TestMode = IIf(CmbMode.ListIndex = 0, True, False)
    DiscRecord.CurrentWriteSpeed = Val(CmbSpeeds.List(CmbSpeeds.ListIndex))
    DiscRecord.CDLabel = TxtLabel.Text
    DiscRecord.BurnProof = IIf(CmbBuffer.ListIndex = 0, False, True)
    DiscRecord.PauseBetweenTracks = Val(TxtAudioPause.Text)
    DiscRecord.WriteType = IIf(CmbWriteType.ListIndex = 0, writeTAO, writeSAO)
    
    TimerBurnProgress.Enabled = True
    
    DiscRecord.BurnFromISO "c:\cd_copy.iso"
    
    CmdBurn.Enabled = True
    
End Sub

Private Sub DiscRecord_Complete()
   
    If FrmCopyCD.Visible = True Then
        Call FrmCopyCD.Complete
    Else
        TimerBurnProgress.Enabled = False
        CmdBurn.Enabled = True
        SSTab.TabCaption(0) = "Burn Settings"
        CmdBurn.Caption = "Start Burn!"
        FrameProgress.Visible = False
        FrameWrite.Visible = True
    End If
    
End Sub

Private Sub DiscRecord_DeviceListed(ByVal Name As String, ByVal Adapter As String, ByVal CanWrite As Boolean)
    If FrmCopyCD.Visible = True Then
        FrmCopyCD.CmbDrives.AddItem Name
    Else
        CmbDevice.ComboItems.Add , , Name, 8, 8
    End If
End Sub

Sub UpdateDiscState()
    Dim lensecs As Double
    Dim capacity As Double
    Dim size As Double
    Dim cdState As DISCRECORDLibCtl.DiscState
    Dim cdType As DISCRECORDLibCtl.DiscType
    
    cdType = DiscRecord.DiscType
    cdState = DiscRecord.DiscState
    capacity = DiscRecord.DiscCapacityBytes
    size = DiscRecord.DiscSize
    lensecs = DiscRecord.DiscCapacitySeconds
    
    Select Case cdState
    Case discNotAvailable
        Status.Panels(3).Text = "No Disc in drive"
    Case discClosed
        If cdType = discCDRW Then
            Status.Panels(3).Text = "Non writeable CDRW [" & FormatSize(capacity) & ", used=" & FormatSize(size) & ")"
        Else
            Status.Panels(3).Text = "Non writeable CD [" & FormatSize(capacity) & ", used=" & FormatSize(size) & ")"
        End If
    Case discEmpty
        If cdType = discCDRW Then
            Status.Panels(3).Text = "Empty CDRW [" & FormatTime(lensecs) & ", " & FormatSize(capacity) & "]"
        Else
            Status.Panels(3).Text = "Empty CD [" & FormatTime(lensecs) & ", " & FormatSize(capacity) & "]"
        End If
    Case discOpen
        If cdType = discCDRW Then
            Status.Panels(3).Text = "Open CDRW (Capacity=" & FormatSize(capacity) & ", used=" & FormatSize(size) & ")"
        Else
            Status.Panels(3).Text = "Open CD (Capacity=" & FormatSize(capacity) & ", used=" & FormatSize(size) & ")"
        End If
    End Select
    
End Sub

Sub UpdateDriveSpeed()
    'Rescan speed, because speed may change for different mediums
    CmbSpeeds.Clear
    DiscRecord.ListAvailableWriteSpeeds
    If CmbSpeeds.ListCount Then
        CmbSpeeds.ListIndex = CmbSpeeds.ListCount - 1
    End If
End Sub

Private Sub DiscRecord_DiscStatusChanged()
    'This event is fired when the cd is removed or put in
    'It can also be fired at other times.
    
    UpdateDiscState
    UpdateDriveSpeed
    
End Sub

Private Sub DiscRecord_ReadSpeedListed(ByVal SpeedFactor As Long, ByVal SpeedDesc As String)
    FrmInfoTool.CmbReadSpeed.AddItem SpeedDesc
End Sub

Private Sub DiscRecord_StatusChange(ByVal NewStatusString As String, ByVal NewStatus As DISCRECORDLibCtl.Status, ByVal StatusTypeVal As DISCRECORDLibCtl.StatusType)
    Select Case StatusTypeVal
    Case statusError
        'An error has occured. One can either handle it here or
        'simply display a box with the default message
        If (NewStatus = statusErrorNoASPI) Then
            MsgBox "ASPI is not installed. Please install it or switch to SPTI mode"
        Else
            MsgBox NewStatusString, vbCritical
        End If
    End Select
    
    LabelStatus.Caption = NewStatusString
End Sub

Private Sub DiscRecord_WriteSpeedListed(ByVal SpeedFactor As Long, ByVal SpeedDesc As String)
    CmbSpeeds.AddItem SpeedDesc
End Sub

Private Sub Form_Load()
        
    'Initialize the cd writing. This has to be done before all else
    DiscRecord.CommunicationMethod = DiscRecord.PreferredCommunicationMethod
    DiscRecord.Initialize
    
    'Store the root directory
    Set m_CurDir = DiscRecord.DataDisc
    
    'Add the types of burn we can do. At the moment, data and audio
    FillTypeCombo
    
    CmbType.ComboItems.item(1).Selected = True
    
    'Add a virtual device, and then list the system writer devices
    'The list function repeatedly fires a function 'DeviceListed'
    'til all the devices have been listed, after which it returns
'    CmbDevice.ComboItems.Add , , "Image Burner", 9, 9
    
    DiscRecord.ListDevices True
    
    If CmbDevice.ComboItems.Count > 1 Then
        CmbDevice.ComboItems(1).Selected = True
        DiscRecord.SelectedWriterDeviceIndex = 0  ' first device
    Else
        CmbDevice.ComboItems(1).Selected = True
    End If
    
    UpdateDiscState
    UpdateDriveSpeed
    
    'Set the mode to write mode
    CmbMode.ListIndex = 1
    
    'Set the buffer to justlink
    CmbBuffer.ListIndex = 1
    
    'Set to TAO
    CmbWriteType.ListIndex = 0
    
    'Set to comm method
    CmbComm.ListIndex = IIf(DiscRecord.CommunicationMethod = commSPTI, 0, 1)
    
    'Enable and disable the buttons
    CmbType_Click

End Sub

Sub RefreshAudioTracks()
    'Clear the listview since we will ask the object to relist everything
    'It does not have to be done this way. One can simply insert only the new
    'item into the list view
    LVFiles.ListItems.Clear
    
    
    Dim i As Integer
    For i = 1 To DiscRecord.AudioDisc.TrackCount
        LVFiles.ListItems.Add , , DiscRecord.AudioDisc.Track(i).Name, , 14
        LVFiles.ListItems.item(LVFiles.ListItems.Count).SubItems(1) = FormatTime(DiscRecord.AudioDisc.Track(i).Duration)
    Next i
    
    'We set the duration progress to the appropriate value in MINUTES
    TimeScale.SetDuration DiscRecord.AudioDisc.Duration / 60
    
    Status.Panels(2).Text = "Total Duration=" & FormatTime(DiscRecord.AudioDisc.Duration) & "  "
End Sub
Sub AddFileToDataCD()
    Dim sPattern As String: sPattern = "All Files (*.*)|*.*||"
    Dim sFilename As String
    
    sFilename = DiscRecord.FileSelectDialog(Me.hWnd, False, sPattern, "iso", 1)
    If (sFilename > "") Then
        m_CurDir.AddFile sFilename
        RefreshDataFiles
    End If
End Sub

Sub AddTrackToAudioCD()
    'Add the audio track to the discrecord object
    
    'Set pattern
    Dim sPattern As String: sPattern = "All Files (*.*)|*.*||"
    
    'Show file open dialog
    Dim sFilename As String
    sFilename = DiscRecord.FileSelectDialog(Me.hWnd, False, sPattern, "mp3", 1)
    
    'Check if the user selected anything
    If (sFilename > "") Then
            
        'Add the audio track. The duration is returned by this function
        DiscRecord.AudioDisc.AddTrack sFilename
        
        RefreshAudioTracks
        
    End If
End Sub

Sub ScanDirectoryRecursive(strDirectory As String, ByRef curDir As FileItem)
    Dim wfd As WIN32_FIND_DATA
    Dim hFile As Long
    Dim curFile As FileItem
    Dim strFile As String
    Dim strPath As String
    
    hFile = FindFirstFile(strDirectory & "\*.*", wfd)
    If hFile <> INVALID_HANDLE_VALUE Then
        Do
        
            strFile = TrimNull(wfd.cFileName)
            strPath = strDirectory & "\" & strFile
            
            If (wfd.dwFileAttributes And FILE_ATTRIBUTE_DIRECTORY) Then
                If strFile > "." And strFile > ".." Then
                    Set curFile = curDir.AddEmptyFolder(strFile)
                    ScanDirectoryRecursive strPath, curFile
                    Set curFile = Nothing
                    
                    If (ObjPtr(curDir) = ObjPtr(m_CurDir)) Then
                        LVFiles.ListItems.Add , , GetTitle(strPath), , 13
                    End If
                
                End If
            Else
                Call curDir.AddFile(strPath)
                
                If (ObjPtr(curDir) = ObjPtr(m_CurDir)) Then
                    LVFiles.ListItems.Add , , GetTitle(strPath), , 15
                End If
                
                Status.Panels(1).Text = "Scanning: " & strPath
                TimeScale.SetSize DiscRecord.DataDisc.size / 1024 / 1024
                DoEvents
            End If
            
        Loop Until FindNextFile(hFile, wfd) = 0
    End If

    Call FindClose(hFile)
    
    'Sort the list
    curDir.Sort
    
End Sub
    
Sub AddFolderToDataCD()
    Dim str As String
    str = BrowseForFolder(Me.hWnd, "Folder to add...")
    
    If (Trim(str) <> "") Then
        LVFiles.ListItems.Clear
        Dim curDir As FileItem
        Dim strName As String: strName = GetTitle(str)
        Set curDir = m_CurDir.AddEmptyFolder(strName)
        
        RefreshDataFiles
        ScanDirectoryRecursive str, curDir
        m_CurDir.Sort
        RefreshDataFiles
    End If
End Sub

Function InDataMode() As Boolean
    InDataMode = Not InAudioMode
End Function

Function InAudioMode() As Boolean
    If (CmbType.SelectedItem.Index = CmbType.ComboItems.Count) Then
        InAudioMode = True
    Else
        InAudioMode = False
    End If
End Function

Private Sub Form_Unload(Cancel As Integer)
    Set m_CurDir = Nothing
    
    Unload FrmCopyCD
    Unload FrmErase
    Unload FrmInfoTool
    
End Sub

Private Sub LVFiles_AfterLabelEdit(Cancel As Integer, NewString As String)
    m_CurDir.SubFile(LVFiles.SelectedItem.Index).Name = NewString
End Sub

Private Sub LVFiles_DblClick()

    If InDataMode Then
        'An item has been double clicked. If it is a folder, we
        'list the contents of the folder and add the folder path
        'to the combo box
        
        Dim item As MSComctlLib.ListItem
        Set item = LVFiles.SelectedItem
        If item Is Nothing Then Exit Sub
        
        Dim curItem As FileItem
        Set curItem = m_CurDir.SubFile(LVFiles.SelectedItem.Index)
        
        If curItem.Type = typeFile Then
            Exit Sub
        End If
        
        LVFiles.ListItems.Clear
        Set m_CurDir = curItem
        RefreshDataFiles
        
        Dim iIndent As Integer
        iIndent = CmbType.ComboItems.item(CmbType.ComboItems.Count - 1).Indentation + 2
        
        Dim cmb As ComboItem
        Set cmb = CmbType.ComboItems.Add(CmbType.ComboItems.Count, , m_CurDir.Name, 12, 12, iIndent)
        cmb.Selected = True
        
        TBFiles.Buttons(1).Enabled = True
    End If
    
End Sub

Private Sub LVFiles_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button = 2 Then
        If InDataMode Then
            mnuCreateDir.Enabled = True
            mnuMoveUp.Enabled = False
            mnuMoveDown.Enabled = False
        Else
            mnuCreateDir.Enabled = False
            mnuMoveUp.Enabled = True
            mnuMoveDown.Enabled = True
        End If
        
        PopupMenu PopupDataFile
    End If
End Sub

Private Sub mnuMoveDown_Click()
    If LVFiles.SelectedItem Is Nothing Then Exit Sub
    
    If InAudioMode Then
        Dim nIndex As Long: nIndex = LVFiles.SelectedItem.Index
        DiscRecord.AudioDisc.MoveTrack nIndex - 1, nIndex
        RefreshAudioTracks
    End If
End Sub

Private Sub mnuMoveUp_Click()
    If LVFiles.SelectedItem Is Nothing Then Exit Sub
    
    If InAudioMode Then
        Dim nIndex As Long: nIndex = LVFiles.SelectedItem.Index
        DiscRecord.AudioDisc.MoveTrack nIndex - 1, nIndex - 2
        RefreshAudioTracks
    End If
End Sub

Private Sub TBFiles_ButtonClick(ByVal Button As MSComctlLib.Button)

    If InDataMode Then
        Select Case Button.Index
        Case 1
            'We are navigating up
            If (m_CurDir.Parent Is Nothing) Then Exit Sub
            Set m_CurDir = m_CurDir.Parent
            RefreshDataFiles
            
            If (m_CurDir.Parent Is Nothing) Then
                TBFiles.Buttons(1).Enabled = False
            End If
            
            CmbType.ComboItems.Remove CmbType.ComboItems.Count - 1
            CmbType.ComboItems.item(CmbType.ComboItems.Count - 1).Selected = True
        Case 2
            m_CurDir.AddEmptyFolder "Empty Directory"
            
            Dim lvItem As ListItem
            Set lvItem = LVFiles.ListItems.Add(, , "Empty Directory", , 13)
            Set LVFiles.SelectedItem = lvItem
            LVFiles.SelectedItem.EnsureVisible
            LVFiles.SetFocus
            LVFiles.StartLabelEdit
            
        End Select
    End If
    
End Sub

Private Sub TBMain_ButtonClick(ByVal Button As MSComctlLib.Button)
    Select Case Button.Index
    Case 1
        AddFileToDataCD
    Case 2
        AddFolderToDataCD
    Case 4
        AddTrackToAudioCD
    Case 6
        RemoveSelectedItems
    Case 10 'test
        DiscRecord.DoNothing 'function is used to debug the newest features
    End Select
End Sub

Sub RemoveSelectedItems()
    If LVFiles.SelectedItem Is Nothing Then Exit Sub
    
    If InAudioMode Then
        DiscRecord.AudioDisc.RemoveTrack LVFiles.SelectedItem.Index
        RefreshAudioTracks
    Else
        m_CurDir.RemoveByIndex (LVFiles.SelectedItem.Index)
        RefreshDataFiles
    End If
End Sub

Sub RefreshDataFiles()
    'This function clears the listview, and rereads all the files
    'in the current directory and adds them to the listview
    
    LVFiles.ListItems.Clear
    
    Dim iIcon As Integer
    Dim i As Integer
    For i = 1 To m_CurDir.SubFileCount
        iIcon = IIf(m_CurDir.SubFile(i).Type = typeDirectory, 13, 15)
        LVFiles.ListItems.Add , , m_CurDir.SubFile(i).Name, , iIcon
        LVFiles.ListItems(LVFiles.ListItems.Count).SubItems(1) = FormatSize(m_CurDir.SubFile(i).size)
    Next i
    
    If (DiscRecord.DataDisc.size = 0) Then
        Status.Panels(1).Text = ""
    Else
        Status.Panels(1).Text = "Total Size=" & FormatSize(DiscRecord.DataDisc.size)
    End If
    
    TimeScale.SetSize DiscRecord.DataDisc.size / 1024 / 1024
End Sub

Private Sub TBMain_ButtonMenuClick(ByVal ButtonMenu As MSComctlLib.ButtonMenu)
    Select Case ButtonMenu.Key
    Case "Erase"
        Load FrmErase
        FrmErase.Show 1, Me
    Case "DriveInfo"
        Load FrmInfoTool
        FrmInfoTool.Show 1, Me
    Case "CopyCD"
        Load FrmCopyCD
        FrmCopyCD.Show 0, Me
        FrmBurn.DiscRecord.ListDevices False
        FrmCopyCD.CmbDrives.ListIndex = 0
    End Select
End Sub

Private Sub TimerBurnProgress_Timer()
    Dim nPercent As Double
    Dim nDuration As Double
    Dim nProgress As Double
    
    nDuration = DiscRecord.ProgressMax
    nProgress = DiscRecord.ProgressCur
    
    If (nDuration > 0) Then
        nPercent = (nProgress / nDuration) * 100
    Else
        nPercent = 0
    End If
    
    ProgressBurn.Value = IIf(nPercent > 100, 100, nPercent)
    LabelPercent.Caption = str(Round(nPercent, 2)) & "%"
    
    Dim nUsed As Long, nLength As Long
    DiscRecord.QueryFileBuffer nUsed, nLength
    
    If (nLength = 0) Then
        LabelFileBuf.Caption = "Direct Stream"
    Else
        LabelFileBuf.Caption = FormatSize(CDbl(nUsed)) & " of " & FormatSize(CDbl(nLength))
    End If
    
    LabelBytes.Caption = FormatSize(nProgress) & " of " & FormatSize(nDuration)
    LabelLBA.Caption = DiscRecord.CurrentLBA
    LabelTrack.Caption = DiscRecord.CurrentTrack
    LabelElapsed.Caption = FormatTime(DiscRecord.TimeElapsed)
    LabelTime.Caption = FormatTime(DiscRecord.ProgressCurSeconds) & " of " & FormatTime(DiscRecord.ProgressMaxSeconds)
    LabelDriveBuffer.Caption = "Not scanned" 'it is bad for the burn to scan this
End Sub

