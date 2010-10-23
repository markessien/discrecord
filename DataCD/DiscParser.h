// DiscParser.h: Schnittstelle für die Klasse CDiscParser.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCPARSER_H__D695F4D3_1E51_4D39_A1A5_31100AC3F944__INCLUDED_)
#define AFX_DISCPARSER_H__D695F4D3_1E51_4D39_A1A5_31100AC3F944__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "discreader.h"
#include "FileRecord.h"

class CDiscParser  
{
public:
	CFileRecord* GetRoot();
	#define	DELTA(from, to)	((to) - (from) + 1)

	struct	VolumeDesc 
	{
		char	type			[DELTA(   1,	1)];
		char	id			[DELTA(   2,	6)];
		char	version		[DELTA(   7,	7)];
		char	unused1		[DELTA(   8,	8)];
		char	system_id		[DELTA(   9,	40)];
		char	volume_id		[DELTA(  41,	72)];
		char	unused2		[DELTA(  73,	80)];
		char	volume_space_size	[DELTA(  81,	88)];
		char	escape_sequences [DELTA(  89,	120)];
		char	volume_set_size	[DELTA( 121,	124)];
		char	volume_seq_number	[DELTA( 125,	128)];
		char	lbsize		[DELTA( 129,	132)];
		char	PathTableSize    [DELTA( 133,	140)];
		char	PathTablePosLE   [DELTA( 141,	144)];
		char	PathTablePosLEOpt[DELTA( 145,	148)];
		char	PathTablePosBE   [DELTA( 149,	152)];
		char	PathTablePosBEOpt[DELTA( 153,	156)];
		char	root_dir		[DELTA( 157,	190)];
		char	volume_set_id	[DELTA( 191,	318)];
		char	publisher_id		[DELTA( 319,	446)];
		char	data_preparer_id	[DELTA( 447,	574)];
		char	application_id	[DELTA( 575,	702)];
		char	copyr_file_id	[DELTA( 703,	739)];
		char	abstr_file_id	[DELTA( 740,	776)];
		char	bibl_file_id		[DELTA( 777,	813)];
		char	create_time		[DELTA( 814,	830)];
		char	mod_time		[DELTA( 831,	847)];
		char	expiry_time		[DELTA( 848,	864)];
		char	effective_time	[DELTA( 865,	881)];
		char	file_struct_vers	[DELTA( 882,	882)];
		char	reserved1		[DELTA( 883,	883)];
		char	application_use	[DELTA( 884,	1395)];
		char	fill			[DELTA(1396,	2048)];
	};

	struct iso9660_dir 
	{
		char	dr_len			[DELTA(   1,	1)];
		char	dr_eattr_len		[DELTA(   2,	2)];
		char	dr_data_pos		[DELTA(   3,	10)];
		char	dr_data_len		[DELTA(  11,	18)];
		char	dr_recording_time	[DELTA(  19,	25)];
		char	dr_file_flags		[DELTA(  26,	26)];
		char	dr_file_unit_size	[DELTA(  27,	27)];
		char	dr_interleave_gap	[DELTA(  28,	28)];
		char	dr_volume_seq_number	[DELTA(  29,	32)];
		char	dr_file_name_len	[DELTA(  33,	33)];
		char	dr_file_name		[DELTA(  34,	34)];
	};

	struct PathTableEntry
	{
		char nLen[DELTA(1,	1)];
		char nLenExtAttr[DELTA(2, 2)];
		char nPosDirStart[DELTA(3, 6)];
		char nParentIndex[DELTA(7, 8)];
		char szName[DELTA(9, 9)];
	};
	
	CDiscParser(IDiscReader* pReader);
	virtual ~CDiscParser();

	bool ReadVolumeDescriptors(bool bFromFirstSession);
	bool LoadDirectoryStructure();

private:
	bool ReadDirectory(iso9660_dir * pDir, CFileRecord* pTargetRecord, bool bUnicode);
	long BothEndianDWORDtoLong(char szValue[]);

private:
	IDiscReader* m_pReader;
	VolumeDesc m_volDescPrimary;
	VolumeDesc m_volDescSecondary;
	iso9660_dir m_iso9660root;
	CFileRecord m_root;
};

#endif // !defined(AFX_DISCPARSER_H__D695F4D3_1E51_4D39_A1A5_31100AC3F944__INCLUDED_)
