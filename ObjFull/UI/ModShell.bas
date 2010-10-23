Attribute VB_Name = "ModShell"
Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Copyright ©1996-2002 VBnet, Randy Birch, All Rights Reserved.
' Some pages may also contain other copyrights by the author.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Distribution: You can freely use this code in your own
'               applications, but you can not publish
'               or reproduce this code on any web site,
'               on any online service, or distribute on
'               any media without express permission.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const OFN_ALLOWMULTISELECT As Long = &H200
Public Const OFN_CREATEPROMPT As Long = &H2000
Public Const OFN_ENABLEHOOK As Long = &H20
Public Const OFN_ENABLETEMPLATE As Long = &H40
Public Const OFN_ENABLETEMPLATEHANDLE As Long = &H80
Public Const OFN_EXPLORER As Long = &H80000
Public Const OFN_EXTENSIONDIFFERENT As Long = &H400
Public Const OFN_FILEMUSTEXIST As Long = &H1000
Public Const OFN_HIDEREADONLY As Long = &H4
Public Const OFN_LONGNAMES As Long = &H200000
Public Const OFN_NOCHANGEDIR As Long = &H8
Public Const OFN_NODEREFERENCELINKS As Long = &H100000
Public Const OFN_NOLONGNAMES As Long = &H40000
Public Const OFN_NONETWORKBUTTON As Long = &H20000
Public Const OFN_NOREADONLYRETURN As Long = &H8000& 'see comments
Public Const OFN_NOTESTFILECREATE As Long = &H10000
Public Const OFN_NOVALIDATE As Long = &H100
Public Const OFN_OVERWRITEPROMPT As Long = &H2
Public Const OFN_PATHMUSTEXIST As Long = &H800
Public Const OFN_READONLY As Long = &H1
Public Const OFN_SHAREAWARE As Long = &H4000
Public Const OFN_SHAREFALLTHROUGH As Long = 2
Public Const OFN_SHAREWARN As Long = 0
Public Const OFN_SHARENOWARN As Long = 1
Public Const OFN_SHOWHELP As Long = &H10
Public Const OFS_MAXPATHNAME As Long = 260

'OFS_FILE_OPEN_FLAGS and OFS_FILE_SAVE_FLAGS below
'are mine to save long statements; they're not
'a standard Win32 type.
Public Const OFS_FILE_OPEN_FLAGS = OFN_EXPLORER _
             Or OFN_LONGNAMES _
             Or OFN_CREATEPROMPT _
             Or OFN_NODEREFERENCELINKS

Public Const OFS_FILE_SAVE_FLAGS = OFN_EXPLORER _
             Or OFN_LONGNAMES _
             Or OFN_OVERWRITEPROMPT _
             Or OFN_HIDEREADONLY

Type SECURITY_ATTRIBUTES
    nLength As Long
    lpSecurityDescriptor As Long
    bInheritHandle As Long
End Type

Public Type OPENFILENAME
  nStructSize       As Long
  hwndOwner         As Long
  hInstance         As Long
  sFilter           As String
  sCustomFilter     As String
  nMaxCustFilter    As Long
  nFilterIndex      As Long
  sFile             As String
  nMaxFile          As Long
  sFileTitle        As String
  nMaxTitle         As Long
  sInitialDir       As String
  sDialogTitle      As String
  flags             As Long
  nFileOffset       As Integer
  nFileExtension    As Integer
  sDefFileExt       As String
  nCustData         As Long
  fnHook            As Long
  sTemplateName     As String
End Type

Public OFN As OPENFILENAME

Public Declare Function GetOpenFileName Lib "comdlg32" _
    Alias "GetOpenFileNameA" _
   (pOpenfilename As OPENFILENAME) As Long

Public Declare Function GetSaveFileName Lib "comdlg32" _
   Alias "GetSaveFileNameA" _
  (pOpenfilename As OPENFILENAME) As Long

Public Declare Function GetShortPathName Lib "kernel32" _
    Alias "GetShortPathNameA" _
   (ByVal lpszLongPath As String, _
    ByVal lpszShortPath As String, _
    ByVal cchBuffer As Long) As Long
Public Declare Function PathMatchSpec Lib "Shlwapi" _
    Alias "PathMatchSpecW" _
  (ByVal pszFileParam As Long, _
   ByVal pszSpec As Long) As Long

Public Type BROWSEINFO
   hOwner           As Long
   pidlRoot         As Long
   pszDisplayName   As String
   lpszTitle        As String
   ulFlags          As Long
   lpfn             As Long
   lParam           As Long
   iImage           As Long
End Type
'
Public Const BIF_DONTGOBELOWDOMAIN = &H2
Public Const BIF_STATUSTEXT = &H4
Public Const BIF_RETURNFSANCESTORS = &H8
Public Const BIF_BROWSEFORCOMPUTER = &H1000
Public Const BIF_BROWSEFORPRINTER = &H2000
Public Const BIF_RETURNONLYFSDIRS = &H1
Public Const MAX_PATH = 260
'
Public Declare Function SHGetPathFromIDList _
   Lib "shell32.dll" Alias "SHGetPathFromIDListA" _
   (ByVal pidl As Long, ByVal pszPath As String) As Long
'
Public Declare Function SHBrowseForFolder Lib "shell32.dll" _
Alias "SHBrowseForFolderA" _
(lpBrowseInfo As BROWSEINFO) As Long

Public Declare Sub CoTaskMemFree Lib "OLE32.DLL" (ByVal pv As Long)

Public Declare Function CreateDirectory Lib "kernel32" _
    Alias "CreateDirectoryA" _
   (ByVal lpPathName As String, _
    lpSecurityAttributes As SECURITY_ATTRIBUTES) As Long

Public Declare Function ShellExecute Lib _
        "shell32.dll" Alias "ShellExecuteA" _
        (ByVal hWnd As Long, ByVal lpOperation _
        As String, ByVal lpFile As String, _
        ByVal lpParameters As String, _
        ByVal lpDirectory As String, _
        ByVal nShowCmd As Long) As Long

Public Declare Function MoveFile Lib "kernel32" Alias _
        "MoveFileA" (ByVal lpExistingFileName As String, ByVal _
        lpNewFileName As String) As Long

Public Declare Function GetTempPath Lib "kernel32" Alias "GetTempPathA" _
    (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long

Public Const INVALID_HANDLE_VALUE = -1
Public Const FILE_ATTRIBUTE_READONLY = &H1
Public Const FILE_ATTRIBUTE_HIDDEN = &H2
Public Const FILE_ATTRIBUTE_SYSTEM = &H4
Public Const FILE_ATTRIBUTE_DIRECTORY = &H10
Public Const FILE_ATTRIBUTE_ARCHIVE = &H20
Public Const FILE_ATTRIBUTE_NORMAL = &H80
Public Const FILE_ATTRIBUTE_TEMPORARY = &H100
Public Const FILE_ATTRIBUTE_COMPRESSED = &H800

Public Type FILETIME
   dwLowDateTime As Long
   dwHighDateTime As Long
End Type

Public Type WIN32_FIND_DATA
   dwFileAttributes As Long
   ftCreationTime As FILETIME
   ftLastAccessTime As FILETIME
   ftLastWriteTime As FILETIME
   nFileSizeHigh As Long
   nFileSizeLow As Long
   dwReserved0 As Long
   dwReserved1 As Long
   cFileName As String * MAX_PATH
   cAlternate As String * 14
End Type

Public Declare Function CopyFile Lib "kernel32" _
   Alias "CopyFileA" _
  (ByVal lpExistingFileName As String, _
   ByVal lpNewFileName As String, _
   ByVal bFailIfExists As Long) As Long

Public Declare Function FindFirstFile Lib "kernel32" _
   Alias "FindFirstFileA" _
  (ByVal lpFileName As String, _
   lpFindFileData As WIN32_FIND_DATA) As Long

Public Declare Function FindNextFile Lib "kernel32" _
   Alias "FindNextFileA" _
  (ByVal hFindFile As Long, _
   lpFindFileData As WIN32_FIND_DATA) As Long

Public Declare Function FindClose Lib "kernel32" _
  (ByVal hFindFile As Long) As Long

Public Declare Function GetFileAttributes Lib "kernel32" _
   Alias "GetFileAttributesA" _
  (ByVal lpFileName As String) As Long

Public Declare Function LockWindowUpdate Lib "user32" _
  (ByVal hwndLock As Long) As Long

Public Declare Function lstrlenW Lib "kernel32" _
  (ByVal lpString As Long) As Long

Public Function TempPath() As String
    Dim sTempPath As String     'temporary path
    Dim iBufSize As Integer     'buffer size
    Dim iRtn As Long            'return value
    
    iBufSize = 256              'and a little extra, make sure have some spaces
    sTempPath = String$(iBufSize, Chr$(0))      'load temp path buffer
    iRtn = GetTempPath(iBufSize, sTempPath)     'get a temporary path
    If iRtn > 0 Then
        sTempPath = Left$(sTempPath, iRtn)      'get the path
    Else
        sTempPath = ""
    End If
    TempPath = sTempPath
End Function


Function BrowseForFolder(hWnd As Long, sCaption As String) As String
    Dim bi As BROWSEINFO
    Dim pidl As Long
    Dim Path As String
    Dim pos As Integer
    
    bi.hOwner = hWnd
    bi.pidlRoot = 0&
    bi.lpszTitle = sCaption
    bi.ulFlags = BIF_RETURNONLYFSDIRS
    pidl = SHBrowseForFolder(bi)
    Path = Space$(MAX_PATH)
    
    If SHGetPathFromIDList(ByVal pidl, ByVal Path) Then
        pos = InStr(Path, Chr$(0))
        BrowseForFolder = Left(Path, pos - 1)
    End If
    
    Call CoTaskMemFree(pidl)
    
End Function

Function FileExists(FullPathAndFile As String) As Boolean
    On Error Resume Next

    If FileLen(FullPathAndFile) > 0 Then
        If Err = 0 Then FileExists = True
    End If
End Function

Public Function GetFreeFileName(BaseFilename As String) As String
    
    If (FileExists(BaseFilename) = False) Then
        GetFreeFileName = BaseFilename
    Else
    
        Dim strRoot As String, strNewPath As String
        Dim strExt As String, iPos As Integer, i As Integer
        iPos = InStrRev(BaseFilename, ".")
        
        If (iPos > 0) Then
            strExt = Mid(BaseFilename, iPos)
            strRoot = Mid(BaseFilename, 1, iPos - 1)
        End If
        
        For i = 0 To 5000
            strNewPath = strRoot & Trim(str(i)) & strExt
            
            If (FileExists(strNewPath) = False) Then
                GetFreeFileName = strNewPath
                Exit Function
            End If
        Next i
        
    End If
    
End Function


Public Function CreateNestedFoldersByPath(ByVal _
                        completeDirectory As String) As Integer
   On Error Resume Next
   
  'creates nested directories on the drive
  'included in the path by parsing the final
  'directory string into a directory array,
  'and looping through each to create the final path.
  
  'The path could be passed to this method as a
  'pre-filled array, reducing the code.
  
   Dim r As Long
   Dim SA As SECURITY_ATTRIBUTES
   Dim drivePart As String
   Dim newDirectory  As String
   Dim item As String
   Dim sfolders() As String
   Dim pos As Integer
   Dim x As Integer
   
  'show the path to create
   
  'must have a trailing slash for
  'the GetPart routine below
   If Right$(completeDirectory, 1) <> "\" Then
      completeDirectory = completeDirectory & "\"
   End If
  
  'if there is a drive in the string, get it
  'else, just use nothing - assumes current drive
   pos = InStr(completeDirectory, ":")

   If pos Then
         drivePart = GetPart(completeDirectory, "\")
   Else: drivePart = ""
   End If

  'now get the rest of the items that
  'make up the string
   Do Until completeDirectory = ""

    'strip off one item (i.e. "Files\")
     item = GetPart(completeDirectory, "\")

    'add it to an array for later use, and
    'if this is the first item (x=0),
    'append the drivepart
     ReDim Preserve sfolders(0 To x) As String

     If x = 0 Then item = drivePart & item
     sfolders(x) = item

    'increment the array counter
     x = x + 1

   Loop

  'Now create the directories.
  'Because the first directory is
  '0 in the array, reinitialize x to -1
   x = -1
   
   Do
   
      x = x + 1
     'just keep appending the folders in the
     'array to newDirectory.  When x=0 ,
     'newDirectory is "", so the
     'newDirectory gets assigned drive:\firstfolder.
     
     'Subsequent loops adds the next member of the
     'array to the path, forming a fully qualified
     'path to the new directory.
      newDirectory = newDirectory & sfolders(x)
      
     'the only member of the SA type needed (on
     'a win95/98 system at least)
      SA.nLength = LenB(SA)
      
      Call CreateDirectory(newDirectory, SA)
      
      
   Loop Until x = UBound(sfolders)
   
  'done. Return x, but add 1 for the 0-based array.
   CreateNestedFoldersByPath = x + 1

End Function




