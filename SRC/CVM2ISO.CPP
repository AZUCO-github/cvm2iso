///////////////////////////////////////////////////////////////////////////////
//	CVM2ISO
//		by	AZUCO
///////////////////////////////////////////////////////////////////////////////
#include	<windows.h>
#include	<stdio.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);

void	decode_cvm(char *name,unsigned long ssrc,unsigned char *src)
{
	unsigned long	hed=0;
	unsigned long	tul1;
	HANDLE			hiso;
	char			tfn[MAX_PATH];

loop:
	if(	(*(src+hed+0x00)!=0x01)	||
		(*(src+hed+0x01)!='C')	||
		(*(src+hed+0x02)!='D')	||
		(*(src+hed+0x03)!='0')	||
		(*(src+hed+0x04)!='0')	||
		(*(src+hed+0x05)!='1')	||
		(*(src+hed+0x06)!=0x01)	||
		(*(src+hed+0x07)!=0x00)		){
		hed+=0x800;
		if(hed>=ssrc)	exit(0);
		goto	loop;
	}

	if(hed<0x8000)		exit(0);
	hed-=0x8000;

	sprintf(tfn,"%s.iso",name);
	hiso=NonOverWriteCreateFile((LPCSTR)tfn);
	WriteFile(hiso,src+hed,ssrc-hed,&tul1,NULL);
	CloseHandle(hiso);
}
