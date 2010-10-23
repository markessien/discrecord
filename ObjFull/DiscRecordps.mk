
DiscRecordps.dll: dlldata.obj DiscRecord_p.obj DiscRecord_i.obj
	link /dll /out:DiscRecordps.dll /def:DiscRecordps.def /entry:DllMain dlldata.obj DiscRecord_p.obj DiscRecord_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DiscRecordps.dll
	@del DiscRecordps.lib
	@del DiscRecordps.exp
	@del dlldata.obj
	@del DiscRecord_p.obj
	@del DiscRecord_i.obj
