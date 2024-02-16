///////////////////////////////////////////////////////////////////////////////
//	CVM2ISO
//		080414
//			by	AZUCO
///////////////////////////////////////////////////////////////////////////////
#include	<windows.h>
#include	<stdio.h>

extern	void	decode_cvm	(char *,unsigned long,unsigned char *);

int	main(int argc,char *argv[])
{
	unsigned char	*buff=NULL;

	HANDLE			hndl;

	unsigned long	file_size;

	unsigned long	tul;
	unsigned long	fnargc=0;

	char			drive[MAX_PATH];
	char			dir[MAX_PATH];
	char			fname[MAX_PATH];
	char			ext[MAX_PATH];

	printf("CVM2ISO Prog. By AZUCO\n");

	if(argc==1){
		printf("CVM2ISO <file ...>\n");
		exit(0);
	}

///////	option	///////////////////////////////////////////////////////////////
	for(tul=1;tul<argc;tul++){
		if(argv[tul][0]=='/'){
			if(	argv[tul][1]=='a' &&
				argv[tul][2]=='f'	)
				NULL;
		}else{
			if(fnargc==0)	fnargc=tul;
		}
	}

//strcpy(argv[fnargc],"E:\\MOVIE.CVM");

	hndl=CreateFile(argv[fnargc],
					GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hndl==(HANDLE)-1){
		printf("\t%s - %d\n",argv[fnargc],fnargc);
		printf("\tError\tsource file not found\n");
		exit(-1);	}

	file_size=GetFileSize(hndl,NULL);

	_splitpath(argv[fnargc],drive,dir,fname,ext);

	if(	strcmp(_strlwr(ext),".cvm")==0){
		buff=new unsigned char[file_size];
		ReadFile(hndl,buff,file_size,&tul,NULL);
		decode_cvm(fname,file_size,buff);
		goto esc;	}

esc:
	CloseHandle(hndl);
	if(buff!=NULL){	delete[]	buff;	buff=NULL;	}
}
