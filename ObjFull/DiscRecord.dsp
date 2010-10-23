# Microsoft Developer Studio Project File - Name="DiscRecord" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DiscRecord - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DiscRecord.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DiscRecord.mak" CFG="DiscRecord - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DiscRecord - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DiscRecord - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DiscRecord - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\\" /I "Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\AudioDecompress\Debug\AudioDecompress.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\DiscRecord.dll
InputPath=.\Debug\DiscRecord.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DiscRecord - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\AudioDecompress\Release\AudioDecompress.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\DiscRecord.dll
InputPath=.\ReleaseMinDependency\DiscRecord.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "DiscRecord - Win32 Debug"
# Name "DiscRecord - Win32 Release MinDependency"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\ASPI.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioItem.cpp
# End Source File
# Begin Source File

SOURCE=..\DataCD\BinaryStream.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\CircularBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\Disc.cpp
# End Source File
# Begin Source File

SOURCE=..\AudioCD\DiscAudio.cpp
# End Source File
# Begin Source File

SOURCE=..\DataCD\DiscImage.cpp
# End Source File
# Begin Source File

SOURCE=..\DataCD\DiscISO9660.cpp
# End Source File
# Begin Source File

SOURCE=..\DataCD\DiscParser.cpp
# End Source File
# Begin Source File

SOURCE=.\DiscRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\DiscRecord.idl
# ADD MTL /tlb ".\DiscRecord.tlb" /h "DiscRecord.h" /iid "DiscRecord_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\DiscRecord.rc
# End Source File
# Begin Source File

SOURCE=.\DiscRecordObj.cpp
# End Source File
# Begin Source File

SOURCE=..\DiscWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\DriveLetterMap.cpp
# End Source File
# Begin Source File

SOURCE=.\FileItem.cpp
# End Source File
# Begin Source File

SOURCE=..\DataCD\FileRecord.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\Helper.cpp
# End Source File
# Begin Source File

SOURCE=..\SCSI.cpp
# End Source File
# Begin Source File

SOURCE=..\SPTI.cpp
# End Source File
# Begin Source File

SOURCE=..\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\SyncWait.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\ASPI.h
# End Source File
# Begin Source File

SOURCE=.\AudioItem.h
# End Source File
# Begin Source File

SOURCE=.\AudioItemCP.h
# End Source File
# Begin Source File

SOURCE=..\DataCD\BinaryStream.h
# End Source File
# Begin Source File

SOURCE=..\Include\CircularBuffer.h
# End Source File
# Begin Source File

SOURCE=..\Disc.h
# End Source File
# Begin Source File

SOURCE=..\AudioCD\DiscAudio.h
# End Source File
# Begin Source File

SOURCE=..\DataCD\DiscImage.h
# End Source File
# Begin Source File

SOURCE=..\DataCD\DiscISO9660.h
# End Source File
# Begin Source File

SOURCE=..\DataCD\DiscParser.h
# End Source File
# Begin Source File

SOURCE=..\DiscReader.h
# End Source File
# Begin Source File

SOURCE=.\DiscRecord.def
# End Source File
# Begin Source File

SOURCE=.\DiscRecordCP.h
# End Source File
# Begin Source File

SOURCE=.\DiscRecordObj.h
# End Source File
# Begin Source File

SOURCE=..\DiscWriter.h
# End Source File
# Begin Source File

SOURCE=..\DiscWriterDefs.h
# End Source File
# Begin Source File

SOURCE=.\DriveLetterMap.h
# End Source File
# Begin Source File

SOURCE=.\FileItem.h
# End Source File
# Begin Source File

SOURCE=..\DataCD\FileRecord.h
# End Source File
# Begin Source File

SOURCE=..\Include\Helper.h
# End Source File
# Begin Source File

SOURCE=.\License.h
# End Source File
# Begin Source File

SOURCE=.\ReferenceCode.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\SCSI.h
# End Source File
# Begin Source File

SOURCE=..\SPTI.h
# End Source File
# Begin Source File

SOURCE=..\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\Include\SyncWait.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE="..\Images\Administrative Tools.ico"
# End Source File
# Begin Source File

SOURCE="..\..\Images\Administrative Tools.ico"
# End Source File
# Begin Source File

SOURCE=.\AudioItem.rgs
# End Source File
# Begin Source File

SOURCE="..\Images\CD drive.ico"
# End Source File
# Begin Source File

SOURCE=".\Images\CD drive.ico"
# End Source File
# Begin Source File

SOURCE="..\..\Images\CD drive.ico"
# End Source File
# Begin Source File

SOURCE=..\Images\discreco.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\discreco.bmp
# End Source File
# Begin Source File

SOURCE=..\..\Images\discreco.bmp
# End Source File
# Begin Source File

SOURCE=.\DiscRecordObj.rgs
# End Source File
# Begin Source File

SOURCE=.\FileItem.rgs
# End Source File
# Begin Source File

SOURCE=..\Images\ico00001.ico
# End Source File
# Begin Source File

SOURCE=..\..\Images\ico00001.ico
# End Source File
# Begin Source File

SOURCE=..\Images\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\Images\icon2.ico
# End Source File
# Begin Source File

SOURCE=..\..\Images\icon2.ico
# End Source File
# End Group
# End Target
# End Project
