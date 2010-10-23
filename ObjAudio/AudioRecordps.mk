
AudioRecordps.dll: dlldata.obj AudioRecord_p.obj AudioRecord_i.obj
	link /dll /out:AudioRecordps.dll /def:AudioRecordps.def /entry:DllMain dlldata.obj AudioRecord_p.obj AudioRecord_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del AudioRecordps.dll
	@del AudioRecordps.lib
	@del AudioRecordps.exp
	@del dlldata.obj
	@del AudioRecord_p.obj
	@del AudioRecord_i.obj
