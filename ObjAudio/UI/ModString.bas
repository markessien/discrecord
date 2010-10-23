Attribute VB_Name = "ModString"
Option Explicit

Public Function CleanStringForPath(str As String) As String
    
    str = Replace(str, "\", "_", , , vbTextCompare)
    str = Replace(str, "/", "_", , , vbTextCompare)
    str = Replace(str, ":", "_", , , vbTextCompare)
    str = Replace(str, "*", "_", , , vbTextCompare)
    str = Replace(str, Chr$(34), "_", , , vbTextCompare)
    str = Replace(str, "<", "_", , , vbTextCompare)
    str = Replace(str, ">", "_", , , vbTextCompare)
    str = Replace(str, "|", "_", , , vbTextCompare)
    str = Replace(str, "?", "_", , , vbTextCompare)
    
    CleanStringForPath = str
End Function

Function FormatSize(nSize As Double) As String
    Dim sFormatted As String
    
    If Not (nSize > 0) Then
        FormatSize = "0 Bytes"
        Exit Function
    End If
    
    nSize = nSize / 1024
    If (nSize > 1024) Then
        nSize = nSize / 1024
        sFormatted = Format(nSize, "0.00") & "MB"
    Else
        sFormatted = Format(nSize, "0.00") & "KB"
    End If
    
    FormatSize = sFormatted
End Function

Public Function StripDelimitedItem(startStrg As String, _
                                    delimiter As String) As String

  'take a string separated by nulls,
  'split off 1 item, and shorten the string
  'so the next item is ready for removal.
   Dim pos As Long
   Dim item As String
   
   pos = InStr(1, startStrg, delimiter)
   
   If pos Then

      StripDelimitedItem = Mid$(startStrg, 1, pos)
      startStrg = Mid$(startStrg, pos + 1, Len(startStrg))
    
   End If

End Function

Public Function ChangeExtOfPath(strPath As String, strNewExt As String) As String
    
    Dim iPos As Integer
    iPos = InStrRev(strPath, ".")
    
    If (iPos = 0) Then
        ChangeExtOfPath = strPath + "." + strNewExt
        Exit Function
    End If
    
    Dim strExt As String, strNewPath As String
    strExt = Mid(strPath, iPos + 1, Len(strPath) - (iPos - 1))
    
    strNewPath = Mid(strPath, 1, iPos - 1)
    If strNewExt > "" Then
        strNewPath = strNewPath & "." & strNewExt
    End If
    
    ChangeExtOfPath = strNewPath
End Function

Public Function TrimNull(item As String) As String

   Dim pos As Integer
   
   pos = InStr(item, Chr$(0))
   If pos Then
         TrimNull = Left$(item, pos - 1)
   Else: TrimNull = item
   End If
  
End Function

Public Function GetTitle(sPath As String) As String
    Dim sTitle As String
    Dim iPos As Integer
    
    sTitle = sPath
    iPos = InStrRev(sPath, "\")
    
    If (iPos > 0) Then
        sTitle = Right(sPath, Len(sPath) - iPos)
    End If
   
   GetTitle = sTitle
End Function

Function Tokenize(ByVal TokenString, ByRef TokenSeparators())

    Dim NumWords, a()
    NumWords = 0
    
    Dim NumSeps
    NumSeps = UBound(TokenSeparators)
    
    Do
        Dim SepIndex, SepPosition
        SepPosition = 0
        SepIndex = -1
        
        Dim i As Integer
        For i = 0 To NumSeps - 1
        
            ' Find location of separator in the string
            Dim pos
            pos = InStr(TokenString, TokenSeparators(i))
            
            ' Is the separator present, and is it closest to the beginning of the string?
            If pos > 0 And ((SepPosition = 0) Or (pos < SepPosition)) Then
                SepPosition = pos
                SepIndex = i
            End If
            
        Next

        ' Did we find any separators?
        If SepIndex < 0 Then

            ' None found - so the token is the remaining string
            ReDim Preserve a(NumWords + 1)
            a(NumWords) = TokenString
            
        Else

            ' Found a token - pull out the substring
            Dim substr
            substr = Trim(Left(TokenString, SepPosition - 1))
    
            ' Add the token to the list
            ReDim Preserve a(NumWords + 1)
            a(NumWords) = substr
        
            ' Cutoff the token we just found
            Dim TrimPosition
            TrimPosition = SepPosition + Len(TokenSeparators(SepIndex))
            TokenString = Trim(Mid(TokenString, TrimPosition))
                        
        End If
        
        NumWords = NumWords + 1
    Loop While (SepIndex >= 0)
    
    Tokenize = a
    
End Function



Function GetPart(startStrg As String, delimiter As String) As String

'takes a string separated by "delimiter",
'splits off 1 item, and shortens the string
'so that the next item is ready for removal.

  Dim c As Integer
  Dim item As String
  
  c = 1
  
  Do

    If Mid$(startStrg, c, 1) = delimiter Then
      
      item = Mid$(startStrg, 1, c)
      startStrg = Mid$(startStrg, c + 1, Len(startStrg))
      GetPart = item
      Exit Function
    
    End If

    c = c + 1

  Loop

End Function

Public Function MakePath(Path As String, File As String) As String
    If Right$(Path, 1) <> "\" Then Path = Path & "\"
    MakePath = Path & File
End Function

Public Function FormatTime(Duration As Double) As String
    Dim strTime As String
    Dim dMins As Double
    Dim dSecs As Double
    
    Duration = Round(Duration, 0)
    
    dMins = Duration \ 60
    dSecs = Duration - (dMins * 60)
    
    strTime = Trim(str(dMins)) & ":" & IIf(dSecs = 0, "00", IIf(dSecs < 10, "0" & Trim(str(dSecs)), Trim(str(dSecs))))
    
    FormatTime = strTime
End Function

Public Function strtok(strVar As String, delims As String) As String
  Static sTmp As String
  Dim i As Long

  strtok = vbNullString

  'Initialize first time calling
  If strVar <> vbNullString Then
    sTmp = strVar
  End If

  'Nothing left to tokenize!
  If sTmp = vbNullString Then
    Exit Function
  End If

search_for_next_delimiter:

  'Loop until we find a delimiter
  For i = 1 To Len(sTmp)

    If InStr(1, delims, Mid$(sTmp, i, 1), vbBinaryCompare) > 0 Then

      If i > 1 Then
        strtok = Left(sTmp, i - 1)
        sTmp = Mid$(sTmp, i + 1, Len(sTmp) - i)
        Exit Function
      Else
        ' string starts with delimiter, so skip one
        sTmp = Right$(sTmp, Len(sTmp) - 1)
        GoTo search_for_next_delimiter
      End If

    End If

  Next i

  'Did not find any, return whatever is left in stmp
  strtok = sTmp
  sTmp = vbNullString
End Function





