VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{B53696AB-693D-452E-8AA5-7353932188AE}#1.0#0"; "AudioRecord.dll"
Begin VB.Form FrmBurn 
   BorderStyle     =   1  'Fest Einfach
   Caption         =   "Audio Burn!"
   ClientHeight    =   7035
   ClientLeft      =   150
   ClientTop       =   540
   ClientWidth     =   8565
   Icon            =   "FrmBurn.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7035
   ScaleWidth      =   8565
   StartUpPosition =   3  'Windows-Standard
   Begin Burn.TimeScale TimeScale 
      Height          =   420
      Left            =   105
      TabIndex        =   14
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
         NumListImages   =   19
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":038A
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":04E4
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":0A7E
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":1018
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":15B2
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":194C
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":1CE6
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":2080
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":30D2
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":4124
            Key             =   ""
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":44BE
            Key             =   ""
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":4858
            Key             =   ""
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":4BF2
            Key             =   ""
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":4F8C
            Key             =   ""
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":5326
            Key             =   ""
         EndProperty
         BeginProperty ListImage16 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":56C0
            Key             =   ""
         EndProperty
         BeginProperty ListImage17 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":5C3E
            Key             =   ""
         EndProperty
         BeginProperty ListImage18 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":6170
            Key             =   ""
         EndProperty
         BeginProperty ListImage19 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "FrmBurn.frx":66C2
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Frame FrameBottomSep 
      Height          =   90
      Index           =   0
      Left            =   -165
      TabIndex        =   4
      Top             =   6360
      Width           =   11025
   End
   Begin MSComctlLib.ListView LVFiles 
      Height          =   5265
      Left            =   90
      TabIndex        =   2
      Top             =   615
      Width           =   5100
      _ExtentX        =   8996
      _ExtentY        =   9287
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
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
         Object.Width           =   2540
      EndProperty
   End
   Begin MSComctlLib.StatusBar Status 
      Align           =   2  'Unten ausrichten
      Height          =   270
      Left            =   0
      TabIndex        =   1
      Top             =   6765
      Width           =   8565
      _ExtentX        =   15108
      _ExtentY        =   476
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   3
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   9922
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
      TabPicture(0)   =   "FrmBurn.frx":6C14
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "FrameWrite"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "CmdBurn"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "TimerBurnProgress"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "FrameProgress"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).ControlCount=   4
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
         TabIndex        =   21
         Top             =   405
         Visible         =   0   'False
         Width           =   3045
         Begin MSComctlLib.ProgressBar ProgressBurn 
            Height          =   285
            Left            =   900
            TabIndex        =   27
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
            TabIndex        =   41
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
            TabIndex        =   40
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
            TabIndex        =   39
            Top             =   2595
            Width           =   90
         End
         Begin VB.Label Label24 
            Alignment       =   1  'Rechts
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
            TabIndex        =   38
            Top             =   3255
            Width           =   780
         End
         Begin VB.Label Label23 
            Alignment       =   1  'Rechts
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
            TabIndex        =   37
            Top             =   2910
            Width           =   780
         End
         Begin VB.Label Label22 
            Alignment       =   1  'Rechts
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
            TabIndex        =   36
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
            TabIndex        =   35
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
            TabIndex        =   34
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
            TabIndex        =   33
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
            TabIndex        =   32
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
            TabIndex        =   31
            Top             =   1020
            Width           =   1320
         End
         Begin VB.Label Label18 
            Alignment       =   1  'Rechts
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
            TabIndex        =   30
            Top             =   2280
            Width           =   720
         End
         Begin VB.Label Label17 
            Alignment       =   1  'Rechts
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
            TabIndex        =   29
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
            TabIndex        =   28
            Top             =   720
            Width           =   255
         End
         Begin VB.Label Label15 
            Alignment       =   1  'Rechts
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
            TabIndex        =   26
            Top             =   345
            Width           =   690
         End
         Begin VB.Label Label14 
            Alignment       =   1  'Rechts
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
            TabIndex        =   25
            Top             =   705
            Width           =   690
         End
         Begin VB.Label Label13 
            Alignment       =   1  'Rechts
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
            TabIndex        =   24
            Top             =   1020
            Width           =   465
         End
         Begin VB.Label Label11 
            Alignment       =   1  'Rechts
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
            TabIndex        =   23
            Top             =   1350
            Width           =   390
         End
         Begin VB.Label Label3 
            Alignment       =   1  'Rechts
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
            TabIndex        =   22
            Top             =   1665
            Width           =   615
         End
      End
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
         Picture         =   "FrmBurn.frx":6C30
         Style           =   1  'Grafisch
         TabIndex        =   12
         Top             =   4860
         Width           =   3045
      End
      Begin VB.Frame FrameWrite 
         Caption         =   "Write settings"
         Height          =   2985
         Left            =   120
         TabIndex        =   5
         Top             =   390
         Width           =   3045
         Begin VB.TextBox TxtAudioPause 
            Height          =   315
            Left            =   735
            TabIndex        =   43
            Text            =   "2"
            Top             =   2565
            Width           =   2235
         End
         Begin VB.ComboBox CmbComm 
            Height          =   315
            ItemData        =   "FrmBurn.frx":7C72
            Left            =   735
            List            =   "FrmBurn.frx":7C7C
            Style           =   2  'Dropdown-Liste
            TabIndex        =   19
            Top             =   2190
            Width           =   2250
         End
         Begin VB.ComboBox CmbWriteType 
            Height          =   315
            ItemData        =   "FrmBurn.frx":7C8C
            Left            =   735
            List            =   "FrmBurn.frx":7C96
            Style           =   2  'Dropdown-Liste
            TabIndex        =   17
            Top             =   1845
            Width           =   2250
         End
         Begin VB.ComboBox CmbBuffer 
            Height          =   315
            ItemData        =   "FrmBurn.frx":7CC3
            Left            =   735
            List            =   "FrmBurn.frx":7CCD
            Style           =   2  'Dropdown-Liste
            TabIndex        =   16
            Top             =   1485
            Width           =   2250
         End
         Begin VB.ComboBox CmbMode 
            Height          =   315
            ItemData        =   "FrmBurn.frx":7CEC
            Left            =   735
            List            =   "FrmBurn.frx":7CF6
            Style           =   2  'Dropdown-Liste
            TabIndex        =   11
            Top             =   1095
            Width           =   2250
         End
         Begin VB.ComboBox CmbSpeeds 
            Height          =   315
            Left            =   720
            Style           =   2  'Dropdown-Liste
            TabIndex        =   8
            Top             =   690
            Width           =   2250
         End
         Begin MSComctlLib.ImageCombo CmbDevice 
            Height          =   330
            Left            =   720
            TabIndex        =   6
            Top             =   285
            Width           =   2250
            _ExtentX        =   3969
            _ExtentY        =   582
            _Version        =   393216
            ForeColor       =   -2147483640
            BackColor       =   -2147483643
            ImageList       =   "ImageList1"
         End
         Begin VB.Label Label4 
            Alignment       =   1  'Rechts
            Caption         =   "Pause:"
            Height          =   210
            Left            =   45
            TabIndex        =   42
            Top             =   2595
            Width           =   660
         End
         Begin VB.Label Label12 
            Alignment       =   1  'Rechts
            Caption         =   "Comm:"
            Height          =   210
            Left            =   30
            TabIndex        =   20
            Top             =   2250
            Width           =   660
         End
         Begin VB.Label Label9 
            Alignment       =   1  'Rechts
            Caption         =   "Write:"
            Height          =   210
            Left            =   30
            TabIndex        =   18
            Top             =   1905
            Width           =   660
         End
         Begin VB.Label Label5 
            Alignment       =   1  'Rechts
            Caption         =   "Buffer:"
            Height          =   210
            Left            =   30
            TabIndex        =   15
            Top             =   1545
            Width           =   660
         End
         Begin VB.Label Label2 
            Alignment       =   1  'Rechts
            BackStyle       =   0  'Transparent
            Caption         =   "Mode:"
            Height          =   225
            Left            =   90
            TabIndex        =   10
            Top             =   1170
            Width           =   585
         End
         Begin VB.Label Label7 
            Alignment       =   1  'Rechts
            BackStyle       =   0  'Transparent
            Caption         =   "Speed:"
            Height          =   225
            Left            =   90
            TabIndex        =   9
            Top             =   765
            Width           =   585
         End
         Begin VB.Label Label1 
            Caption         =   "Device:"
            Height          =   210
            Left            =   105
            TabIndex        =   7
            Top             =   345
            Width           =   555
         End
      End
   End
   Begin MSComctlLib.Toolbar TBMain 
      Height          =   330
      Left            =   30
      TabIndex        =   3
      Top             =   6465
      Width           =   7800
      _ExtentX        =   13758
      _ExtentY        =   582
      ButtonWidth     =   2514
      ButtonHeight    =   582
      Wrappable       =   0   'False
      Style           =   1
      TextAlignment   =   1
      ImageList       =   "ImageList1"
      DisabledImageList=   "ImageListPlayer"
      HotImageList    =   "ImageListPlayer"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   5
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Add Audio..."
            ImageIndex      =   4
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Remove Track"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
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
      EndProperty
   End
   Begin AUDIORECORDLibCtl.AudioRecordObj AudioRecord 
      Left            =   5175
      OleObjectBlob   =   "FrmBurn.frx":7D23
      Top             =   15
   End
   Begin VB.Label Label6 
      BackStyle       =   0  'Transparent
      Caption         =   "Essien R&&D Audio Burn! demonstration application"
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
      TabIndex        =   13
      Top             =   165
      Width           =   6540
   End
   Begin VB.Image Image2 
      Height          =   480
      Left            =   90
      Picture         =   "FrmBurn.frx":7D47
      Top             =   15
      Width           =   480
   End
   Begin VB.Image Image1 
      Height          =   240
      Left            =   8145
      Picture         =   "FrmBurn.frx":8A11
      Top             =   165
      Width           =   240
   End
   Begin VB.Shape Shape1 
      FillColor       =   &H00FFFFFF&
      FillStyle       =   0  'Ausgefüllt
      Height          =   540
      Left            =   -45
      Top             =   -15
      Width           =   8700
   End
   Begin VB.Menu PopupDataFile 
      Caption         =   "PopupDataFiles"
      Visible         =   0   'False
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

Dim m_nTotalSize As Long

Private Sub AudioRecord_StatusChange(ByVal NewStatusString As String, ByVal NewStatus As AUDIORECORDLibCtl.Status, ByVal StatusTypeVal As AUDIORECORDLibCtl.StatusType)
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

Private Sub CmbComm_Click()
    AudioRecord.CommMethod = IIf(CmbComm.ListIndex = 1, commASPI, commSPTI)
End Sub

Sub SwitchToAudioMode()
    LVFiles.ListItems.Clear
    TimeScale.SetAudioMode
    LVFiles.ColumnHeaders(2).Text = "Duration"
End Sub

Private Sub CmdBurn_Click()
        
    If CmdBurn.Caption = "Stop Burn!" Then
        
        CmdBurn.Enabled = False
        SSTab.TabCaption(0) = "Burn Settings"
        CmdBurn.Caption = "Start Burn!"
        DoEvents
        
        AudioRecord.AbortBurn
        
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
        AudioRecord.TestMode = IIf(CmbMode.ListIndex = 0, True, False)
        AudioRecord.WriteSpeed = Val(CmbSpeeds.List(CmbSpeeds.ListIndex))
        AudioRecord.BurnProof = IIf(CmbBuffer.ListIndex = 0, False, True)
        AudioRecord.AudioPause = Val(TxtAudioPause.Text)
        AudioRecord.WriteType = IIf(CmbWriteType.ListIndex = 0, writeTAO, writeSAO)
        
        TimerBurnProgress.Enabled = True
        
        AudioRecord.BurnAudioCD
        
        CmdBurn.Enabled = True
        
    End If
    
End Sub

Private Sub AudioRecord_AudioTrackListed(ByVal Index As Long, ByVal LocalPath As String, ByVal Duration As Double)
    'This function is fired for every track in the cd when the ListAudioTracks function is called
    LVFiles.ListItems.Add LVFiles.ListItems.Count + 1, , "Audio Track" & str(Index + 1) & " (" & GetTitle(LocalPath) & ")", , 14
    LVFiles.ListItems.item(LVFiles.ListItems.Count).SubItems(1) = FormatTime(Duration)
End Sub

Private Sub AudioRecord_Complete()

    TimerBurnProgress.Enabled = False
    CmdBurn.Enabled = True
    SSTab.TabCaption(0) = "Burn Settings"
    CmdBurn.Caption = "Start Burn!"
    FrameProgress.Visible = False
    FrameWrite.Visible = True
        
    'It isn't neccesary to call this
    AudioRecord.AbortBurn

End Sub

Private Sub AudioRecord_DeviceListed(ByVal Name As String, ByVal Adapter As String)
    CmbDevice.ComboItems.Add , , Name, 8, 8
End Sub

Private Sub AudioRecord_DiscStatusChanged()
    
    Dim lensecs As Double
    Dim capacity As Double
    Dim size As Double
    Dim state As AUDIORECORDLibCtl.DiscState
    
    state = AudioRecord.DiscState
    capacity = AudioRecord.DiscCapacity
    size = AudioRecord.DiscSize
    lensecs = AudioRecord.DiscCapacitySeconds
    
    Select Case state
    Case discNotAvailable
        Status.Panels(3).Text = "No Disc in drive"
    Case discClosed
        Status.Panels(3).Text = "Non writeable CD [" & FormatSize(capacity) & ", used=" & FormatSize(size) & ")"
    Case discEmpty
        Status.Panels(3).Text = "Empty CD [" & FormatTime(lensecs) & ", " & FormatSize(capacity) & "]"
    Case discOpen
        Status.Panels(3).Text = "Open CD (Capacity=" & FormatSize(capacity) & ", used=" & FormatSize(size) & ")"
    End Select
    
    'Rescan speed, because speed may change for different mediums
    CmbSpeeds.Clear
    AudioRecord.ListAvailableWriteSpeeds
    If CmbSpeeds.ListCount Then
        CmbSpeeds.ListIndex = CmbSpeeds.ListCount - 1
    End If
    
End Sub

Private Sub AudioRecord_FileInDirectoryListed(ByVal Name As String, ByVal PathOnCD As String, ByVal LocalPath As String, ByVal IsDirectory As Boolean, ByVal FileSize As Double)
    LVFiles.ListItems.Add LVFiles.ListItems.Count + 1, , Name, , IIf(IsDirectory, 13, 15)
    LVFiles.ListItems.item(LVFiles.ListItems.Count).SubItems(1) = FormatSize(FileSize)
    LVFiles.ListItems.item(LVFiles.ListItems.Count).Tag = PathOnCD
End Sub

Private Sub AudioRecord_FileScanned(ByVal FilePath As String, ByVal PathOnCD As String, ByVal FileSize As Long)
    Status.SimpleText = "Scanning: " & FilePath
    m_nTotalSize = m_nTotalSize + FileSize
    TimeScale.SetSize m_nTotalSize / 1024 / 1024
    DoEvents
End Sub


Private Sub AudioRecord_ReadSpeedListed(ByVal SpeedFactor As Long, ByVal SpeedDesc As String)
    FrmInfoTool.CmbReadSpeed.AddItem SpeedDesc
End Sub



Private Sub AudioRecord_WriteSpeedListed(ByVal SpeedFactor As Long, ByVal SpeedDesc As String)
    CmbSpeeds.AddItem SpeedDesc
End Sub

Private Sub Form_Load()
    
    AudioRecord.CommMethod = AudioRecord.PreferredCommMethod
    
    'Initialize the cd writing. This has to be done before all else
    AudioRecord.Initialize
    
    SwitchToAudioMode
    
    'Add a virtual device, and then list the system writer devices
    'The list function repeatedly fires a function 'DeviceListed'
    'til all the devices have been listed, after which it returns
    CmbDevice.ComboItems.Add , , "Image Burner", 9, 9
    
    AudioRecord.ListDevices
    
    If CmbDevice.ComboItems.Count > 1 Then
        CmbDevice.ComboItems(2).Selected = True
        
        'List the supported speeds.
        'The speeds are received in an event
        
        AudioRecord.CurrentDevice = 0 ' first device
        AudioRecord.ListAvailableWriteSpeeds
        CmbSpeeds.ListIndex = CmbSpeeds.ListCount - 1 ' the max speed is the last one sent
    Else
        CmbDevice.ComboItems(1).Selected = True
    End If
    
    AudioRecord_DiscStatusChanged
    
    'Set the mode to write mode
    CmbMode.ListIndex = 1
    
    'Set the buffer to justlink
    CmbBuffer.ListIndex = 1
    
    'Set to TAO
    CmbWriteType.ListIndex = 0
    
    'Set to ASPI. SPTI not yet supported
    CmbComm.ListIndex = IIf(AudioRecord.CommMethod = commASPI, 1, 0)
    
    'Enable and disable the buttons
'    CmbType_Click
    
    'Hide the popup menus
    PopupDataFile.Visible = False
End Sub

Sub RefreshAudioTracks()
    'Clear the listview since we will ask the object to relist everything
    'It does not have to be done this way. One can simply insert only the new
    'item into the list view
    LVFiles.ListItems.Clear
    
    'Request the record object to list the audio tracks. The tracks will
    'be received in the audiotracklisted event
    AudioRecord.ListAudioTracks
    
    'We set the duration progress to the appropriate value in MINUTES
    TimeScale.SetDuration AudioRecord.TotalAudioTrackDuration / 60
    
    Status.Panels(2).Text = "Total Duration=" & FormatTime(AudioRecord.TotalAudioTrackDuration) & "  "
End Sub
Sub AddFileToDataCD()
    Dim sPattern As String
    Dim sFilename As String
    
    sPattern = "All Files (*.*)|*.*||"
                        
    sFilename = AudioRecord.FileSelectDialog(Me.hWnd, False, sPattern, "iso", 1)
    If (sFilename > "") Then
        LVFiles.ListItems.Clear
        AudioRecord.AddFile sFilename, ""
        AudioRecord.ListFilesInDataDirectory "\"
        Status.SimpleText = "Total Size=" & FormatSize(CDbl(m_nTotalSize))
        TimeScale.SetSize m_nTotalSize
    End If
End Sub

Sub AddTrackToAudioCD()
    'Add the audio track to the AudioRecord object
    
    'Set pattern
    Dim sPattern As String: sPattern = "All Files (*.*)|*.*||"
    
    'Show file open dialog
    Dim sFilename As String
    sFilename = AudioRecord.FileSelectDialog(Me.hWnd, False, sPattern, "mp3", 1)
    
    'Check if the user selected anything
    If (sFilename > "") Then
            
        'Add the audio track. The duration is returned by this function
        AudioRecord.AddAudioTrack sFilename
        
        RefreshAudioTracks
        
    End If
End Sub

Sub AddFolderToDataCD()
    Dim str As String
    str = BrowseForFolder(Me.hWnd, "Folder to add...")
    
    If (Trim(str) <> "") Then
        LVFiles.ListItems.Clear
        AudioRecord.AddDirectory str, ""
        Status.SimpleText = "Total Size=" & FormatSize(CDbl(m_nTotalSize))
        TimeScale.SetSize m_nTotalSize / 1024 / 1024
        AudioRecord.ListFilesInDataDirectory "\"
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Me.Hide
    'If you shut down the app while a burn is happening, the cd drive
    'might lock, and the pc will need to be rebooted. so call abort before
    'the app is exited.
    
    AudioRecord.AbortBurn
End Sub

Private Sub LVFiles_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button = 2 Then
        PopupMenu PopupDataFile
    End If
End Sub

Private Sub mnuMoveDown_Click()
    If LVFiles.SelectedItem Is Nothing Then Exit Sub
    
    Dim nIndex As Long: nIndex = LVFiles.SelectedItem.Index
    
    LVFiles.ListItems.Clear
    AudioRecord.MoveAudioTrack nIndex - 1, nIndex
    AudioRecord.ListAudioTracks
    
    If nIndex + 1 <= LVFiles.ListItems.Count Then
        Set LVFiles.SelectedItem = LVFiles.ListItems(nIndex + 1)
    End If
End Sub

Private Sub mnuMoveUp_Click()
    If LVFiles.SelectedItem Is Nothing Then Exit Sub
    
    Dim nIndex As Long: nIndex = LVFiles.SelectedItem.Index
    
    LVFiles.ListItems.Clear
    AudioRecord.MoveAudioTrack nIndex - 1, nIndex - 2
    AudioRecord.ListAudioTracks
    
    If nIndex - 1 >= 1 Then
        Set LVFiles.SelectedItem = LVFiles.ListItems(nIndex - 1)
    End If
End Sub

Private Sub TBMain_ButtonClick(ByVal Button As MSComctlLib.Button)
    Select Case Button.Index
    Case 1
        AddTrackToAudioCD
    Case 3
        RemoveSelectedItems
    Case 8
    End Select
End Sub

Sub RemoveSelectedItems()
    If LVFiles.SelectedItem Is Nothing Then Exit Sub
      Dim nIndex As Long: nIndex = LVFiles.SelectedItem.Index
      
      AudioRecord.RemoveAudioTrack nIndex - 1
    
      RefreshAudioTracks

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
        FrmCopyCD.Show 1, Me
    End Select
    
End Sub

Private Sub TimerBurnProgress_Timer()
    Dim nPercent As Double
    Dim nDuration As Double
    Dim nProgress As Double
    
    nDuration = AudioRecord.Duration
    nProgress = AudioRecord.Progress
    
    If (nDuration > 0) Then
        nPercent = (nProgress / nDuration) * 100
    Else
        nPercent = 0
    End If
    
    ProgressBurn.Value = IIf(nPercent > 100, 100, nPercent)
    LabelPercent.Caption = str(Round(nPercent, 2)) & "%"
    
    LabelBytes.Caption = FormatSize(nProgress) & " of " & FormatSize(nDuration)
    LabelLBA.Caption = AudioRecord.CurLBA
    LabelTrack.Caption = AudioRecord.CurTrack
    
    If (AudioRecord.FileBufferSize = 0) Then
        LabelFileBuf.Caption = "Direct Stream"
    Else
        LabelFileBuf.Caption = FormatSize(AudioRecord.FileBufferUsed) & " of " & FormatSize(AudioRecord.FileBufferSize)
    End If
    
    LabelElapsed.Caption = FormatTime(AudioRecord.TimeElapsed)

    LabelTime.Caption = FormatTime(AudioRecord.ProgressTime) & " of " & FormatTime(AudioRecord.DurationTime)
End Sub
