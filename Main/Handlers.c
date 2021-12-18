#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "Defs.h"
#include "Tools.h"
#include "Handlers.h"
#include "VirtualPins.h"
#include "ti.h"
#include "Motors.h"
#include "msg.h"
#include "modbus.h"
#include "bfs.h"
#include "FreqInvr.h"

#include "VPFrz.h"
#include "Motor_X.h"
#include "Motor_Y.h"
#include "Motor_Z.h"

float X,Y,Z; // ���������� ����������
//float *pZset;

// ����� ����������
TFileName * pPrgFileName;
s8 * pPrgFileHandle;
u32 * pPrgLineCount;
u16 * pWF_CRC;

u8	*pPrgRun;		// ����
//u8	*pPrgPause;		// �����
u8 		*pRecBlock;
u8 	*pRCS;		// ��������� ���������� �����
s32 *pCurCadr;			// ������� ����� ��� ����� �����
s32 *pNumReadLine;
s32 sCurCadr;			// 

//volatile u8 * pBusy;//=&Busy;
volatile u8 	Busy = 0;
//u8 * psG0;//=&sG0;
u8 sG0 = 0; // ������ ���������� ������� G0
			// 0 - ������� ���������
			// 1 - ������ �� ������������ ����������
			// 2 - �������
			// 3 - ������� �� �������
TBlock *pBlock;

//s32 ps[2]; // ��������� �� ������ ����� ���������
s32 save_ts_pos;
TFileStream ts,rs;


// ���������� ������ ��� �������
float * pTrAngle; //����������� ����
volatile float Sr; // ����������� ����
volatile u32 Sri; // ����������� ���� � ���������
u32 *pRunSpPause;

u8 CheckPrgFile(void) {
	s8 	res;
	u32	i;
	u8 tmps[50];
//	Msg("PRGH %d\r\n",*pPrgFileHandle);
	if (*pPrgFileHandle >= 0) {
		// �� ������ ���� ������
		return 1;
	} else {
		// *pPrgFileHandle < 0 
		res = FS_Assign((u8*)pPrgFileName,pPrgFileHandle);
		if (res == FS_RESULT_OK) {
			res = FS_Reset(*pPrgFileHandle);
			if (res == FS_RESULT_OK) {
				// ��������� �� ������� �����
				i=0;
				while (i < *pCurCadr) {
					res = bFS_ReadLn(*pPrgFileHandle,tmps,50);
					if (res) {
						Msg("Err ReadLn PrgFile %s : %d\r\n",pPrgFileName,res);
						// ������
						return 0;
					}
					i++;
				}
				return 1;
			} else {
				Msg("Err Reset PrgFile %s : %d\r\n",pPrgFileName,res);
				FS_Close(pPrgFileHandle);
				return 0;
			}
		} else {
			Msg("Err Assing PrgFile %s : %d\r\n",pPrgFileName,*pPrgFileHandle);
			return 0;
		}
	}
}

u8 InitPrgStreams(void){
	// ��������� ���� 
	// ������������� ��������� ������� �� 0
	s8 	res;
//	Msg("PRGH %d\r\n",*pPrgFileHandle);
	ts.Pos = 0;
	rs.Pos = 0;
	if (*pPrgFileHandle >= 0) {
		// �� ������ ���� ������
		InitStream(&ts,*pPrgFileHandle);
		InitStream(&rs,*pPrgFileHandle);
		Msg("Open Prg Streams 1\r\n");
		*pNumReadLine=0;
		return 1;
	} else {
		// *pPrgFileHandle < 0 
		res = FS_Assign((u8*)pPrgFileName,pPrgFileHandle);
		if (res == FS_RESULT_OK) {
			res = FS_Reset(*pPrgFileHandle);
			if (res == FS_RESULT_OK) {
				InitStream(&ts,*pPrgFileHandle);
				InitStream(&rs,*pPrgFileHandle);
				Msg("Open Prg Streams 2\r\n");
				*pNumReadLine=0;
				return 1;
			} else {
				FS_Close(pPrgFileHandle);
				Msg("Err Reset PrgFile %s : %d h %d\r\n",pPrgFileName,res,*pPrgFileHandle);
				//Msg("h %d\r\n",*pPrgFileHandle);
				return 0;
			}
		} else {
			Msg("Err Assing PrgFile %s : %d\r\n",pPrgFileName,*pPrgFileHandle);
			return 0;
		}
	}
}

u8 ReadNextLine(char * CadrLine){
//	Msg("pCurCadr:%d, pPrgLineCount:%d\r\n",*pCurCadr,*pPrgLineCount);
	if (*pCurCadr < *pPrgLineCount) {
		if (CheckPrgFile()) {
			if (bFS_ReadLn(*pPrgFileHandle,(u8*)CadrLine,50)==0) return 1;
			else return 0;
			//������� ������
			//Msg("%d l %d ",*pCurCadr,strlen(afile[*pCurCadr]));
			//memcpy(CadrLine,afile[*pCurCadr],strlen(afile[*pCurCadr]));
		} else return 0;
	} 
	// ����� �����
	return 0;
}

u8 ReadPrevLine(char * CadrLine){
	if (*pCurCadr > -1) {
		if (CheckPrgFile()) {
			if (bFS_BReadLn(*pPrgFileHandle,(u8*)CadrLine,50)==0) return 1;
			else return 0;
			//������� ������
			//Msg("%d l %d ",*pCurCadr,strlen(afile[*pCurCadr]));
			//memcpy(CadrLine,afile[*pCurCadr],strlen(afile[*pCurCadr]));
		} else return 0;
		// ������� ������
		//Msg("%d l %d ",*pCurCadr,strlen(afile[*pCurCadr]));
		//memcpy(CadrLine,afile[*pCurCadr],strlen(afile[*pCurCadr]));
		//return 1;
	} 
	// ����� �����
	return 0;
}

u8 TryStrToFloat(char * Param,float * f){
  int i;
  u8 minus;
  u8 frac;
  float c; // ����� �����
  float d; // ������� �����
  u8 curd; // ������� �����
  char ch;
  u8 cdd;// ���������� ���� ������� �����

  minus = 0; // ������������ ������������� �����
  frac = 0;  // �������� � ����� �����, frac=1 ����� ������� �����������
  c = 0; // ����� �����
  d = 0; // ������� �����
  cdd = 0; // ���������� ���� ������� �����
  for (i=0;i < strlen(Param);i++) {
	ch = *(Param+i);
	switch (ch) {
      case '-':
        if (i > 1) return 0; // ����� �� � ������ - ������
        else minus = 1; // ��������� ������� ������
      break;
      case '+':
        if (i > 1) return 0; // ���� �� � ������ - ������
        else minus = 0; // ��������� ������� �����, ���� � ��� minus=0
      break;
			case '.':
      case ',':
        if (frac == 1) return 0; // ������ ����������� - ������
        else frac=1; // ��������� ������� �� ������� �����
      break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
	  case '9':
        curd=ch-48;
        if (frac == 0) 
			// ����� �����
          	c = 10*c+curd;
        else {
          	// ������� �����
         	 d = 10*d+curd;
			 cdd++;
		}
      break;
	  default: return 0; // ������
    }
  }
  // ������������ ������� �����
  while (cdd) { d/=10; cdd--;}
  *f=c+d;
  if (minus == 1) *f=-*f;
  return 1;
}

u8 IsCmd(char ch){
   if (
   		(ch == 'G') ||
   		(ch == 'g') ||
   		(ch == 'M') ||
   		(ch == 'm') ||
   		(ch == 'X') ||
   		(ch == 'x') ||
   		(ch == 'Y') ||
   		(ch == 'y') ||
   		(ch == 'P') ||
   		(ch == 'p') ||
   		(ch == 'S') ||
   		(ch == 's') ||
   		(ch == 'F') ||
   		(ch == 'f')	||
   		(ch == 'Z') ||
   		(ch == 'z')
	  ) return 1;
   else return 0;
}

u8 IsDigits(char ch){
   if (
   		(ch == '0') ||
   		(ch == '1') ||
   		(ch == '2') ||
   		(ch == '3') ||
   		(ch == '4') ||
   		(ch == '5') ||
   		(ch == '6') ||
   		(ch == '7') ||
   		(ch == '8') ||
   		(ch == '9') ||
   		(ch == '-') ||
   		(ch == '+') ||
		(ch == '.') ||
   		(ch == ',')
	  ) return 1;
   else return 0;
}

u8	ApplyCmd(char cmd,char * Param, TBlock * pBlock){
	float fParam;
	u16 iParam;
	u8 res;

//	Msg("app %c %s\r\n",cmd,Param);
//	fParam=atof(Param);

	if (!TryStrToFloat(Param,&fParam)) {
	    // ������ � ���������
		return TRE_PARAM_ERROR;
	}
//	Msg("s %s d %d \r\n",Param,(int)(fParam*1000));
//	return 0;
	res = 0; // ������������ ��� �� ������
  	// ����� ������� fParam
	if ((cmd == 'g') || (cmd == 'G')) {
		//Msg("G");
		// G - �������
	    iParam=(u16)ceil(fParam);
	    res=0; // ������������ ��� �� ������
		switch (iParam) {
	    	case	0:
			case	1: 
		        // G0 � G1
	    	    (*pBlock).sGo = iParam;
				// ������� ������ !!!
//				Msg("AC sGo %d",(*pBlock).sGo);
	      	break;
	      	case 4:
	        	// G4
	        	(*pBlock).cPause = 1;
	      	break;
			case 20:
			case 21:
	        // G20-G21
	        	if (iParam == 20) (*pBlock).rMul = 25.3;  // �����
	          	else (*pBlock).rMul = 1;    // ��
	      	break;
	      	case 90:
			case 91:
	        	// G90-G91
	        	(*pBlock).rSetSizeReg = iParam-90;
	      	break;
	      	default: res = TRE_UNKNOWN_G; // ����������� G-�������
		}
	} else {
		if ((cmd == 'x') || (cmd == 'X')) {
			//Msg("�");
			// X - ��������
		    (*pBlock).Xr = fParam;
		    (*pBlock).comX = 1;
		} else {
			if ((cmd == 'y') || (cmd == 'Y')) {
				//Msg("Y");
			    // Y - ��������
			    (*pBlock).Yr=fParam;
			    (*pBlock).comY=1;
			} else {
				if ((cmd == 'z') || (cmd == 'Z')) {
				    (*pBlock).Zr=fParam;
				    (*pBlock).comZ=1;
				} else {
					if ((cmd == 'm') || (cmd == 'M')) {
						//Msg("M");
					    // M - �������
					    iParam=(u16)ceil(fParam);
					    res=0; // ������������ ��� �� ������
						switch (iParam) {
					      case 0:
								case 2:
								case 120:	
					        (*pBlock).cStop = 1;
					        (*pBlock).sStop = iParam;
					      break;
					      case 3:
								case 4:
					        // M3 M4
					        (*pBlock).cSpindel = 1;
					        (*pBlock).sSpindel = iParam-2;
									// ��������� ����� ��� ������� �.�. ��������� �� �������� ��������� ��������
									(*pBlock).cPause = 1;
									(*pBlock).lPause = *pRunSpPause; 
								break;
								case 5:
					        (*pBlock).cSpindel = 1;
					        (*pBlock).sSpindel = 0;
					      break;
								case 7:
					        (*pBlock).cCold = 1;
					        (*pBlock).sCold1 = 1;
					      break;
					      case 8:
					        (*pBlock).cCold = 1;
					        (*pBlock).sCold2 = 1;
					      break;
					      case 9:
					        (*pBlock).cCold = 1;
					        (*pBlock).sCold1 = 0;
					        (*pBlock).sCold2 = 0;
					      break;
					      default: res=TRE_UNKNOWN_M; // ����������� M-�������
					    }
					} else {
						if ((cmd == 'f') || (cmd == 'F')) {
							///Msg("F");
						    // F - �������
						    (*pBlock).cFeed = 1;
							if (fParam < 0) res = TRE_LESSZERO_F; // ������������� �������� ������
						    (*pBlock).Feed = fParam;
						} else {
							if ((cmd == 's') || (cmd == 'S')) {
							//	Msg("S");
							    // S - �������
							    if (fParam < 0) res = TRE_LESSZERO_S; // ������������� �������� ��������
							    (*pBlock).cSpindel = 1;  // ������� ��������� �������� ������������� ������� ������� ��������
							    (*pBlock).Speed = fParam;
							} else {
								if ((cmd == 'p') || (cmd == 'P')) {
									//Msg("P");
								    // P - ��������
								    if (fParam < 0) res = TRE_LESSZERO_P; // ������������� �������� �����
								    (*pBlock).lPause = (u16)ceil(fParam);
								} else { 
								   	// ����������� �������, �� ���� ������� �� ������
									//Msg("Un");
								   	res = TRE_UNKNOWN_CMD;
								}
							} // ((cmd == 's') || (cmd == 'S'))
						} //((cmd == 'f') || (cmd == 'F'))
					} //((cmd == 'm') || (cmd == 'M'))
				} //((cmd == 'z') || (cmd == 'Z'))
			}//((cmd == 'y') || (cmd == 'Y'))
		}//((cmd == 'x') || (cmd == 'X'))
	}//((cmd == 'g') || (cmd == 'G'))
	return res;
}

void InitFirstBlockFrz(TBlock * ib){
	// ����������� ��������� ������� ��� �������� Xs,Xi,Ys,Yi,Zs,Zi
//	Msg("IFB\r\n ");
  	memset((u8*)ib,0,sizeof (*ib));
	// ������� � ��
	(*ib).Mul = 1;
	(*ib).rMul = 1;
  	XYZImpToXYZ(	*(ms_X.Pos),		*(ms_Y.Pos),		*(ms_Z.Pos),
   					&((*ib).Xs),	&((*ib).Ys),	&((*ib).Zs));
	(*ib).Xsi = *(ms_X.Pos);
	(*ib).Ysi = *(ms_Y.Pos);
	(*ib).Zsi = *(ms_Z.Pos);
	(*ib).Xi = *(ms_X.Pos);
	(*ib).Yi = *(ms_Y.Pos);
	(*ib).Zi = *(ms_Z.Pos);

//	Msg("Xs %d Ys %d Zs %d\r\n",OUTF((*ib).Xs),OUTF((*ib).Ys),OUTF((*ib).Zs));
//	Msg("Xsi %d Ysi %d Zsi %d\r\n",((*ib).Xsi),((*ib).Ysi),((*ib).Zsi));

}

void InitNextBlock(TBlock * pBlock){
	//Msg("INB \r\n");
	// ����� ���������� ���������� �������
  	(*pBlock).Xs = (*pBlock).Xd;
  	(*pBlock).Ys = (*pBlock).Yd;
  	(*pBlock).Zs = (*pBlock).Zd;
	//Msg("Xs %f Ys %f \r\n",(*pBlock).Xs,(*pBlock).Ys);
}

void InitBlockByPrev(TBlock * ib,TBlock * prevb){
	//Msg("INB \r\n");
	if (prevb!=NULL) {
	  	memset((u8*)ib,0,sizeof (*pBlock));
  		(*ib).Xs = (*prevb).Xd;
  		(*ib).Ys = (*prevb).Yd;
  		(*ib).Zs = (*prevb).Zd;
  		(*ib).Xsi = (*prevb).Xdi;			   
  		(*ib).Ysi = (*prevb).Ydi;
  		(*ib).Zsi = (*prevb).Zdi;
  		(*ib).sGo = (*prevb).sGo;
  		(*ib).SetSizeReg = (*prevb).SetSizeReg;
  		(*ib).Mul = (*prevb).Mul;
  		(*ib).rSetSizeReg = (*prevb).rSetSizeReg;
  		(*ib).rMul = (*prevb).rMul;
  		(*ib).Speed = (*prevb).Speed;
  		(*ib).Feed = (*prevb).Feed;
	//	Msg("psGo %d\r\n",(*prevb).sGo);
	//	Msg("INB pZs %d pZd %d\r\n",(int)((*prevb).Zs),(int)((*prevb).Zd));
	} else InitFirstBlockFrz(ib);
//	Msg("ibsGo %d\r\n",(*ib).sGo);
}



void CalcBlockFrz(TBlock * pB,u8 exe){
//	float Li;
	// ����������� ����� ���������� Xd,Yd,Zd
	// �� ������� ���������� �����

  (*pB).SetSizeReg = (*pB).rSetSizeReg;
  (*pB).Mul = (*pB).rMul;
  if ((*pB).SetSizeReg == 0) {
    // ���������� ����������
    if ((*pB).comX == 1) {
      // ���� ������� X
      (*pB).Xd = (*pB).Xr*(*pB).Mul;
    } else {
      // ������� X �� ����
      (*pB).Xd = (*pB).Xs;
    }
    if ((*pB).comY == 1) {
      // ���� ������� Y
      (*pB).Yd = (*pB).Yr*(*pB).Mul;
    } else {
      // ������� Y �� ����
      (*pB).Yd = (*pB).Ys;
    }
    if ((*pB).comZ == 1) {
      // ���� ������� Z
      (*pB).Zd = (*pB).Zr*(*pB).Mul;
    } else {
      // ������� z �� ����
      (*pB).Zd = (*pB).Zs;
    }
  } else {
    // ������������� ����������
    if ((*pB).comX == 1) {
      // ���� ������� X
      (*pB).Xd = (*pB).Xs+(*pB).Xr*(*pB).Mul;
    } else {
      // ������� X �� ����
      (*pB).Xd = (*pB).Xs;
    }
    if ((*pB).comY == 1) {
      // ���� ������� Y
      (*pB).Yd = (*pB).Ys + (*pB).Yr*(*pB).Mul;
    } else {
      // ������� Y �� ����
      (*pB).Yd = (*pB).Ys;
    }
    if ((*pB).comZ == 1) {
      // ���� ������� Z
      (*pB).Zd = (*pB).Zs + (*pB).Zr*(*pB).Mul;
    } else {
      // ������� Z �� ����
      (*pB).Zd = (*pB).Zs;
    }
  }

//	Msg("\t\t\t\tsGo %d N %D\r\n",(*pB).sGo,(*pB).NumLine);
//	Msg("\t\t\t\tXs %d Ys %d Zs %d \r\n",OUTF((*pB).Xs),OUTF((*pB).Ys),OUTF((*pB).Zs));
//	Msg("\t\t\t\tXd %d Yd %d Zd %d \r\n",OUTF((*pB).Xd),OUTF((*pB).Yd),OUTF((*pB).Zd));

  //return;
//  if (((*pB).sGo == 1)&&(exe)) {
//	Msg("%d",exe);	
  if (exe) {
  	// ���������� ��������� ���������� ��� ��������� �����������
		XYZToXYZImpZcomp((*pB).Xd,(*pB).Yd,(*pB).Zd,
											&(*pB).Xdi,&(*pB).Ydi,&(*pB).Zdi);
//	XYZToXYZImp((*pB).Xd,(*pB).Yd,(*pB).Zd,
//  				  &(*pB).Xdi,&(*pB).Ydi,&(*pB).Zdi);
  	(*pB).Xi = (*pB).Xsi;
  	(*pB).Yi = (*pB).Ysi;
		(*pB).Zi = (*pB).Zsi;
  	(*pB).dXi = abss32((*pB).Xdi - (*pB).Xsi);
  	(*pB).dYi = abss32((*pB).Ydi - (*pB).Ysi);
		(*pB).dZi = abss32((*pB).Zdi - (*pB).Zsi);
	if (((*pB).dXi==0)&&((*pB).dYi==0)&&((*pB).dZi==0)) {
		// ���� ��� �������� ��� ���������� �������
		// ��� ������ ����� ����������
		(*pB).Nomove = (1&& (!(*pB).cFeed)  && (!(*pB).cSpindel) && (!(*pB).cCold) && \
				 			(!(*pB).cPause) && (!(*pB).cStop)    && ((*pB).sGo==1));

//		Msg("B");
	} else {
		// ���� � ��������� ����� ���������� �������
	 	(*pB).Nomove = 0; 
		// ����������� ����������� ��������
		(*pB).signX = (*pB).Xsi < (*pB).Xdi ? 1 : -1;
    (*pB).signY = (*pB).Ysi < (*pB).Ydi ? 1 : -1;
		(*pB).signZ = (*pB).Zsi < (*pB).Zdi ? 1 : -1;
//*****************************************
		(*pB).dS=sqrt(sqr((*pB).Xd-(*pB).Xs)+sqr((*pB).Yd-(*pB).Ys)+sqr((*pB).Zd-(*pB).Zs));
		
//    L = sqrt(	(double)((*pB).dXi*(*pB).dXi*1.0)+
//							(double)((*pB).dYi*(*pB).dYi*1.0)+
//							(double)((*pB).dZi*(*pB).dZi*1.0)
//						);
    (*pB).Li = sqrt(	sqr((*pB).dXi*1.0)+
							sqr((*pB).dYi*1.0)+
							sqr((*pB).dZi*1.0)
						);
		if (((*pB).dXi >= (*pB).dYi)&&((*pB).dXi >= (*pB).dZi))  {
			// ������� ��� X
			(*pB).Lax = 0;
   		(*pB).e1 = (*pB).dXi - (*pB).dYi;
  		(*pB).e2 = (*pB).dXi - (*pB).dZi;
			(*pB).dS = (*pB).dS/(*pB).dXi;
			(*pB).Laxi = (*pB).dXi;
		} else {
  			if (((*pB).dYi >= (*pB).dXi)&&((*pB).dYi >= (*pB).dZi))  {
    			// ������� ��� Y
					(*pB).Lax = 1;
					//fmvs.Rway = fmvs.dYi;
       		(*pB).e1 = (*pB).dYi - (*pB).dXi;
	  			(*pB).e2 = (*pB).dYi - (*pB).dZi;
					(*pB).dS = (*pB).dS/(*pB).dYi;
					(*pB).Laxi = (*pB).dYi;
  			} else 
  			if (((*pB).dZi >= (*pB).dXi)&&((*pB).dZi >= (*pB).dYi))  {
    			// ������� ��� Z
					(*pB).Lax = 2;
					//fmvs.Rway = fmvs.dZi;
					(*pB).e1 = (*pB).dZi - (*pB).dXi;
					(*pB).e2 = (*pB).dZi - (*pB).dYi;
					(*pB).dS = (*pB).dS/(*pB).dZi;
					(*pB).Laxi = (*pB).dZi;
  			};
		}
		// ����������� ������������� �������� �������� Tb
		// ��� �������� T = Tb / Vc
		//Msg("%s :",(*pB).s);
		switch ((*pB).Lax) {
			case 0:	(*pB).Tb = (int)((*pX_PG_MM)*(*pB).Li*K1/((*pX_SPR)*  (*pB).dXi)); 
//				Msg("dXi %d L %d Tb %d\r\n",(*pB).dXi,OUTF1((*pB).Li),(*pB).Tb);
				break;
			case 1:	(*pB).Tb = (int)((*pY_PG_MM)*(*pB).Li*K1/((*pY_SPR)*  (*pB).dYi)); 
//				Msg("dYi %d L %d Tb %d\r\n",(*pB).dYi,OUTF1((*pB).Li),(*pB).Tb);
				break;
    	case 2: (*pB).Tb = (int)((*pZ_PG_MM)*(*pB).Li*K1/((*pZ_SPR)*  (*pB).dZi)); 
//				Msg("dZi %d L %d Tb %d\r\n",(*pB).dZi,OUTF1((*pB).Li),(*pB).Tb);
				break;
		}		
//		Msg("Xsi %d Ysi %d Zsi %d \r\n",(*pB).Xsi,(*pB).Ysi,(*pB).Zsi);
//		Msg("Xdi %d Ydi %d Zdi %d \r\n",(*pB).Xdi,(*pB).Ydi,(*pB).Zdi);
//		Msg("L %d Tb %d\r\n",OUTF(L),OUTF((*pB).Tb/1000));
//		Msg("dx %d dy %d dz %d \r\n",(*pB).dXi,(*pB).dYi,(*pB).dZi);
//		Msg("signX %d signY %d signZ %d \r\n",(*pB).signX,(*pB).signY,(*pB).signZ);
//		Msg("Lax %d e1 %d e2 %d\r\n",(*pB).Lax,(*pB).e1,(*pB).e2);
	};
  }				
//----------*******************************

}

void CalcBlock(TBlock * pBlock){
//	Msg("CB\r\n");

  (*pBlock).SetSizeReg = (*pBlock).rSetSizeReg;
  (*pBlock).Mul = (*pBlock).rMul;
  if ((*pBlock).SetSizeReg == 0) {
    // ���������� ����������
    if ((*pBlock).comX == 1) {
      // ���� ������� X
      (*pBlock).Xd = (*pBlock).Xr*(*pBlock).Mul;
    } else {
      // ������� X �� ����
      (*pBlock).Xd = (*pBlock).Xs;
    }
    if ((*pBlock).comY == 1) {
      // ���� ������� Y
      (*pBlock).Yd = (*pBlock).Yr*(*pBlock).Mul;
    } else {
      // ������� Y �� ����
      (*pBlock).Yd = (*pBlock).Ys;
    }
    if ((*pBlock).comZ == 1) {
      // ���� ������� Z
      (*pBlock).Zd = (*pBlock).Zr*(*pBlock).Mul;
    } else {
      // ������� z �� ����
      (*pBlock).Zd = (*pBlock).Zs;
    }
  } else {
    // ������������� ����������
    if ((*pBlock).comX == 1) {
      // ���� ������� X
      (*pBlock).Xd = (*pBlock).Xs+(*pBlock).Xr*(*pBlock).Mul;
    } else {
      // ������� X �� ����
      (*pBlock).Xd = (*pBlock).Xs;
    }
    if ((*pBlock).comY == 1) {
      // ���� ������� Y
      (*pBlock).Yd = (*pBlock).Ys + (*pBlock).Yr*(*pBlock).Mul;
    } else {
      // ������� Y �� ����
      (*pBlock).Yd = (*pBlock).Ys;
    }
    if ((*pBlock).comZ == 1) {
      // ���� ������� Z
      (*pBlock).Zd = (*pBlock).Zs + (*pBlock).Zr*(*pBlock).Mul;
    } else {
      // ������� Z �� ����
      (*pBlock).Zd = (*pBlock).Zs;
    }
  }
/*
	Msg("CB G9%d Xs %d Ys %d Zs %d Xd %d Yd %d Zd %d \r\n",
		(*pBlock).SetSizeReg,
		(int)(*pBlock).Xd,(int)(*pBlock).Yd,(int)(*pBlock).Zd,
		(int)(*pBlock).Xs,(int)(*pBlock).Ys,(int)(*pBlock).Zs);
*/
}

void BackCalcBlock(TBlock * pBlock){
//	Msg("BCB\r\n");

  if ((*pBlock).SetSizeReg == 0) {
    // ���������� ����������
    if ((*pBlock).comX == 1) {
      // ���� ������� X
      (*pBlock).Xd = (*pBlock).Xr*(*pBlock).Mul;
    } else {
      // ������� X �� ����
      (*pBlock).Xd = (*pBlock).Xs;
    }
    if ((*pBlock).comY == 1) {
      // ���� ������� Y
      (*pBlock).Yd = (*pBlock).Yr*(*pBlock).Mul;
    } else {
      // ������� Y �� ����
      (*pBlock).Yd = (*pBlock).Ys;
    }
  } else {
    // ������������� ����������
    if ((*pBlock).comX == 1) {
      // ���� ������� X
      (*pBlock).Xd = (*pBlock).Xs - (*pBlock).Xr*(*pBlock).Mul;
    } else {
      // ������� X �� ����
      (*pBlock).Xd = (*pBlock).Xs;
    }
    if ((*pBlock).comY == 1) {
      // ���� ������� Y
      (*pBlock).Yd = (*pBlock).Ys - (*pBlock).Yr*(*pBlock).Mul;
    } else {
      // ������� Y �� ����
      (*pBlock).Yd = (*pBlock).Ys;
    }
  }
  (*pBlock).SetSizeReg = (*pBlock).rSetSizeReg;
  (*pBlock).Mul = (*pBlock).rMul;
}

void G0Handler(void){
	s32 Xi,Yi,Zi;

	Busy = 1;
	XYZToXYZImpZcomp(X,Y,Z,&Xi,&Yi,&Zi);
	*(mc_X.ReqPos) = Xi;
	*(mc_Y.ReqPos) = Yi;
	*(mc_Z.ReqPos) = Zi;

	*pCorrStop = 0;

	BR_pCorrStop = 0;
	// ������� �������������� ��������� ����� ����� ��� ����� ���������� �������
	*pRecoverBlock = 0;
	if (Zi < *(ms_Z.Pos)) {
		// ���� XY ����� Z
		*(mc_X.MovePos) = 1;
		*(mc_Y.MovePos) = 1;
		sG0 = 1;
	} else {
		// ���� Z ����� XY
		*(mc_Z.MovePos) = 1;
		sG0 = 3;
	}	
//	Msg("sG0 %d Zi %d Zpos %d\r\n",sG0,Zi,*(ms_Z.Pos));
}

__inline void G1Handler(void){
	// ��� ������ G1 �� main ����� ������� �������� � �������
	*(fmvs.Vc) = *(fmvc.Vmin);
//	Msg("Vc %d Vmin %d\r\n",OUTF1T(*(fmvs.Vc)),OUTF1T(*(fmvc.Vmin)));
	Busy = 1;
	// ������ ���������
  fmvc.Enable=1;
}

void SetFeed(TBlock * pBlock){
	// ��������� �������� ������
	if ((*pBlock).cFeed) {
		(*pBlock).cFeed = 0;
		*(fmvc.V) = (*pBlock).Feed / 60;
		fmvc.Vmax = *(fmvc.V)*(*(fmvc.Vmul)/100);
//		Msg("Vc %d\r\n",OUTF(*(fmvc.V)));
		if (*(fmvs.Vc) > fmvc.Vmax) *(fmvs.Vc) = fmvc.Vmax;
		// ���������� � backup-��������
//		memcpy((void*)&(BR_fmvc_V),(void*)fmvc.V,4);    
//		Msg("Feed %d\r\n",(int)(*(fmvc.V)*1000));
//		Msg("SetFeed Vmax %d\r\n",(int)((fmvc.Vmax)*1000));
	}
}

void SetSpindle(TBlock * pBlock){
	u16 Freq;
	Freq = (int)((*pBlock).Speed)*(*pFnom)/(*pFdbyFnom);
	// ������� �������� ���� ��/��� ��� ����������� ������� ���� pFnom ��
//	*pFdbyFnom = 18000;	
// ����������� ������� ���� ��
//	*pFnom = 300;	
	// ��������� ���������� ��������
    if ((*pBlock).cSpindel == 1) { 
      // ���� ������� ���������� ���������
	  	switch ((*pBlock).sSpindel) {
       	case 0:
				//����
					FIStop();
//					Msg("Off Spindel\r\n");
				break;
        case 1:
					FISetFreq(Freq);
					FISetDir(0);
					FIStart();
//				Msg("On Dir Spindel s %d f %d\r\n",(int)(*pBlock).Speed,Freq);
				break;
        case 2:
					FISetFreq(Freq);
					FISetDir(1);
					FIStart();
//					Msg("On Back Spindel s %d f %d\r\n",(int)(*pBlock).Speed,Freq);
				break;
	  }
      // ������� ��������� ������� ����
      (*pBlock).cSpindel=0;
    }
}

void SetCold(TBlock * pBlock){
   	// ��������� ���������� ����������
    if ((*pBlock).cCold == 1) {
      if ((*pBlock).sCold1 == 1) {
        //��������
				Msg("Cool1 On\r\n");
				QSetPin(COOLER1); 
			} else {
				//���������
				Msg("Cool1 Off\r\n");
				QClrPin(COOLER1); 
			}
      if ((*pBlock).sCold2 == 1) {
        //��������
//				Msg("Cool2 On\r\n");
				QSetPin(COOLER2); 
			} else {
				//���������
//				Msg("Cool2 Off\r\n");
				QClrPin(COOLER2); 
			}
      (*pBlock).cCold = 0;
    }
}

void SetPause(TBlock * pBlock){
	// �����
    if ((*pBlock).cPause == 1) {
			StartTI(tiPrgPause,tiMsToTick((*pBlock).lPause));
//			Msg("Start Pause %d\r\n",(*pBlock).lPause);
      (*pBlock).cPause = 0;
			*(fmvs.Vc) = *(fmvc.Vmin);
    } else 	StopTI(tiPrgPause);
}

void RecSetPause(TBlock * pBlock){
	// �����
    if ((*pBlock).cPause == 1) {
      	(*pBlock).cPause = 0;
    }
}

u8 EndPause(void) {
	return EndTI(tiPrgPause);
}

void SetGoFrz(TBlock * pBlock){
	if (((*pBlock).comX)||((*pBlock).comY)||((*pBlock).comZ)) {
		(*pBlock).comX = 0;
		(*pBlock).comY = 0;
		(*pBlock).comZ = 0;
		if ((*pBlock).sGo == 0) {
			// G0
			//Msg("G0 X %d Y %d\r\n",(int)(*pBlock).Xd,(int)(*pBlock).Yd);
//			Msg("2m%d: %s",(*eb).NumLine,(*eb).s);
			X = (*pBlock).Xd;
			Y = (*pBlock).Yd;
			Z = (*pBlock).Zd;
			G0Handler();
		} else {
			//Msg("G1 X %d Y %d\r\n",(int)(*pBlock).Xd,(int)(*pBlock).Yd);
//			Msg("2m%d: %s",(*eb).NumLine,(*eb).s);
			G1Handler();
		}
	}
}

void RecSetGo(TBlock * pBlock){
	if (((*pBlock).comX)||((*pBlock).comY)||((*pBlock).comZ)) {
		(*pBlock).comX = 0;
		(*pBlock).comY = 0;
		(*pBlock).comZ = 0;
		if ((*pBlock).sGo == 0) {
			// G0
//			Msg("G0 X %d Y %d\r\n",(int)(*pBlock).Xd,(int)(*pBlock).Yd);
		} else {
			// G1
//			Msg("G1 X %d Y %d\r\n",(int)(*pBlock).Xd,(int)(*pBlock).Yd);
		}
	}
}

u8 EndGo(void){
  	// ������� ��������� ������� ��������� ��������
	// ���� ��� (�������� ���������)
	return 1;
}

void SetStop(TBlock * pBlock) {
    if ((*pBlock).cStop == 1) {
      // ������� ����
			switch ((*pBlock).sStop) {
				case 0:
					(*pPrgRun) = 0;
					BR_pPrgRun = *pPrgRun;
					FIStop();
				break;
				case 2:
					//'������ ����������'
					(*pPrgRun) = 0;
					BR_pPrgRun = *pPrgRun;
					QClrPin(COOLER1); 
					QClrPin(COOLER2); 
					FIStop();
					Msg("Full Off\r\n");// ���������!!!
				break;
			}
    }
}

void RecSetStop(TBlock * pBlock) {
    if ((*pBlock).cStop == 1) {
      // ������� ����
	  switch ((*pBlock).sStop) {
	      case 0:
					//'����� �� ������ �����'
					Msg("Pause To Start\r\n");
				break;
	      case 2:
					//'������ ����������'
					// ��������� ���������� � ����
					QClrPin(COOLER1); 
					QClrPin(COOLER2); 
					FIStop();
					Msg("Full Off\r\n");// ���������!!!
				break;
	  }
    }
}

u8 EndStop(void) {
	// �������� �� ������ ������
	return 1;
}

void ErrToMessage(u8 err,char * mess){
 	switch (err) {
		case 1: strcpy("unknown command",mess); break;
		case 2: strcpy("parametr error",mess); break;
		case 3: strcpy("unknown G-command",mess); break;
		case 4: strcpy("unknown M-command",mess); break;
		case 5: strcpy("parametr F less zero",mess); break;
		case 6: strcpy("parametr S less zero",mess); break;
		case 7: strcpy("parametr P less zero",mess); break;
		case 8: strcpy("empty line",mess); break;
		default: sprintf(mess,"unknown error %d",err);
	}
}



u8	BackApplyCmd(char cmd,char * Param){
	float fParam;
	u16 iParam;
	u8 res;

//	Msg("bapp %c %s\r\n",cmd,Param);

	if (!TryStrToFloat(Param,&fParam)) {
	    // ������ � ���������
		return TRE_PARAM_ERROR;
	}
	res = 0; // ������������ ��� �� ������
  	// ����� ������� fParam
	if ((cmd == 'g') || (cmd == 'G')) {
		//Msg("G");
		// G - �������
	    iParam=(u16)ceil(fParam);
	    res=0; // ������������ ��� �� ������
		switch (iParam) {
	    	case	0:
			case	1: 
		        // G0 � G1
	    	    (*pBlock).sGo = iParam;
	      	break;
	      	case 4:
	        	// G4
	        	(*pBlock).cPause = 1;
	      	break;
			case 20:
			case 21:
		       	// G20-G21
	          	// ����������� ������� ��� ��������� ����
	        	if (iParam == 20) (*pBlock).rMul = 1;  // �����
	          	else (*pBlock).rMul = 25.3;    // ��
	      	break;
	      	case 90:
			case 91:
	        	// G90-G91
	        	(*pBlock).rSetSizeReg = iParam-90;
		        // ����������� ������� ��� ��������� ����
        		if ((*pBlock).rSetSizeReg == 1)  
					(*pBlock).rSetSizeReg=0; 
				else (*pBlock).rSetSizeReg=1;
	      	break;
	      	default: res = TRE_UNKNOWN_G; // ����������� G-�������
		}
	} else {
		if ((cmd == 'x') || (cmd == 'X')) {
			//Msg("�");
			// X - ��������
		    (*pBlock).Xr = fParam;
		    (*pBlock).comX = 1;
		} else {
			if ((cmd == 'y') || (cmd == 'Y')) {
				//Msg("Y");
			    // Y - ��������
			    (*pBlock).Yr=fParam;
			    (*pBlock).comY=1;
			} else {
				if ((cmd == 'm') || (cmd == 'M')) {
					//Msg("M");
				    // M - �������
				    iParam=(u16)ceil(fParam);
				    res=0; // ������������ ��� �� ������
					switch (iParam) {
				      case 0:
					  case 2:
				        (*pBlock).cStop = 1;
				        (*pBlock).sStop = iParam;
				      break;
				      case 3:
					  case 4:
				        // M3 M4
				        (*pBlock).cSpindel = 1;
				        (*pBlock).sSpindel = iParam-2;
				      break;
				      case 5:
				        (*pBlock).cSpindel = 1;
				        (*pBlock).sSpindel = 0;
				      break;
				      case 7:
				        (*pBlock).cCold = 1;
				        (*pBlock).sCold1 = 1;
				      break;
				      case 8:
				        (*pBlock).cCold = 1;
				        (*pBlock).sCold2 = 1;
				      break;
				      case 9:
				        (*pBlock).cCold = 1;
				        (*pBlock).sCold1 = 0;
				        (*pBlock).sCold2 = 0;
				      break;
					  case 100:
					  case 101:
						// ������� ���������� �������� �� �������� ���� �� ��������������
					 	// �� � �� �������� �������
					  break;
					  case 103: // �������� ��������
					  case 104: // 
					  break;
					  case 110: // ��������������� �����
					  break;
				      default: res=TRE_UNKNOWN_M; // ����������� M-�������
				    }
				} else {
					if ((cmd == 'f') || (cmd == 'F')) {
						///Msg("F");
					    // F - �������
					    (*pBlock).cFeed = 1;
						if (fParam < 0) res = TRE_LESSZERO_F; // ������������� �������� ������
					    (*pBlock).Feed = fParam;
					} else {
						if ((cmd == 's') || (cmd == 'S')) {
						//	Msg("S");
						    // S - �������
						    if (fParam < 0) res = 6; // ������������� �������� ��������
						    (*pBlock).cSpindel = TRE_LESSZERO_S;  // ������� ��������� �������� ������������� ������� ������� ��������
						    (*pBlock).Speed = fParam;
						} else {
							if ((cmd == 'p') || (cmd == 'P')) {
								//Msg("P");
							    // P - ��������
							    if (fParam < 0) res = TRE_LESSZERO_P; // ������������� �������� �����
							    (*pBlock).lPause = (u16)ceil(fParam);
							} else { 
							   	// ����������� �������, �� ���� ������� �� ������
								//Msg("Un");
							   	res = 1;
							}
						} // ((cmd == 's') || (cmd == 'S'))
					} //((cmd == 'f') || (cmd == 'F'))
				} //((cmd == 'm') || (cmd == 'M'))
			}//((cmd == 'y') || (cmd == 'Y'))
		}//((cmd == 'x') || (cmd == 'X'))
	}//((cmd == 'g') || (cmd == 'G'))
	return res;
}

u8 LineToBlock(const char * CadrLine,u8 * errindex, TBlock * b){
	// ������ �� CadrLine
	u8 i,reg,ParamIndex,res;
	char Param[20];
	char ch,cmd;
	//Msg("LTB\r\n");

	memset(Param,0,20);
	cmd=0;
	res=0;
	reg=0; // ����� ������ �������
	ParamIndex=0; // � ������ ������ ���������
	i=0;
	while (((*(CadrLine+i)) != 13)){
		ch = *(CadrLine+i); // ��������� ����� �� ������� *(CadrLine+i)
		// ������� ������ !!!!
		//i++;
		// ������� �������� �������� � ���������
		if (!((ch == 32) || (ch == 8))) {
			// Msg(" %d",ch);

			if (reg==0) {
				// ����� ������ �������
		        if (IsCmd(ch)) {
		          cmd=ch;
		          reg=1;
		          i++;
				  //Msg("c %c",ch);
		        } else {
		          // ������ ����������� �������
		          *errindex = i;
		          return TRE_UNKNOWN_CMD;
		        }
			} else {
				// ����� ������ ��������
		        // reg = 1
		        if (IsDigits(ch)) {
					// �������� ������ � ������ ���������
					//Msg("p %c",ch);
		          	Param[ParamIndex]=ch;
								ParamIndex++;
		          	i++;
		        } else { 
		          	// �������� � ������� � ��������
		          	// ������ ��������� � ��������� �����
								//Msg("p %s\r\n",Param);
		          	res = ApplyCmd(cmd,Param,b);
								//Msg("App res %d\r\n",res);
		          	if (res == 0) {
									// ������� ����������� ���������� r ��������� �������
									reg=0;
		            	cmd=0;
									ParamIndex = 0;
									memset(Param,0,20);
		          	} else {
		            	// ������ ��� ������������� �������
		            	// �� ���������� ����� �������� ������ G � M
		            	// ��� F ��� S ������������
									// ������������ ������
									Msg("Apply Cmd %c %s Error %d\r\n",cmd,Param,res);
		            	//*errindex = i;
		            	// return res;
									// ������
									// ���������� ����������� �������
									reg=0;
									cmd=0;
									ParamIndex = 0;
									memset(Param,0,20);
		          	}
		        }
  
			} 
		} else i++;
	}
	if (i==0) {
		res = TRE_LINE_EMPTY; // ������ ������
	} else {
		if ((cmd != 0) && (ParamIndex > 0)) {
		    res = ApplyCmd(cmd,Param,b);
			if (res) Msg("Apply Cmd %s %s Error %d\r\n",cmd,Param,res);
				//Msg("App res %d\r\n",res);		
		}
	}
	if (res==0) b->FilePos = save_ts_pos;
	return res;
}


u8 TranslateLineToBlock(const char * CadrLine,TBlock * b,TBlock * prevb,u8 exe){
// ���������� ������ � ����������� ���������
	u8 Res;
	u8 errindex;
	InitBlockByPrev(b,prevb);
 	Res = LineToBlock(CadrLine,&errindex,b);
//	Msg("TrRes %d\r\n",Res);
	if (Res == 0) {
		memset((void*)&((*b).s[0]),0,50);
		memcpy((void*)&((*b).s[0]),(void*)CadrLine,strlen(CadrLine));
		CalcBlockFrz(b,exe);
	}	
	return Res;

//	return 0;
}

#ifdef __FREZER__

#define QEBSize 10

typedef struct tagTQExBlks{
	TBlock blks[QEBSize];
	s8 head; // ������ ������ - ������ ����������� ��������
	s8 tail; // ������ ������� ���������� ��������
			 // ���� tail ��������� � head �� ������� ���� �����
			 // ���� ��������� ������ (��. ���� count)	
	s8 count;
} TQExBlks;

volatile u8 qbLock = 0;

TQExBlks qb; // ���������� �������

void InitQExBlks(void){
	// ������������� �������
	memset((u8*)&qb,0,sizeof qb);	
}

u8 qbCount(void){
 	return qb.count;
}

u8 qbIsPlace(void){
	// �������� ���������� ����� � �������
	if (qb.count < QEBSize) return 1;
	else return 0;
}


u8 qbAddBlock(TBlock * b){
	// ���������� ����� � �������
	// ���������� 1 - ���� ��������
	// ���������� 0 - ���� �� ��������
	if (qbIsPlace()) {
		memcpy((u8*)&(qb.blks[qb.tail]),(u8*)b,sizeof (*b));
		//Msg("tail %d\r\n",qb.tail);
		//Msg("bq X %d Y %d Z %d\r\n",OUTF1T(b->Xd),OUTF1T(b->Yd),OUTF1T(b->Zd));
		qb.tail++;
		qb.tail %= QEBSize; // �����������
		qb.count++;
		return 1;
	} else return 0; 
}

u8 qbExtrBlock(TBlock * b){
	// ���������� ����� �� �������
	// ���������� 1 - ���� ��������	 
	// ���������� 0 - ���� �� ��������
	if (qb.count > 0) {
		memcpy((u8*)b,(u8*)&(qb.blks[qb.head]),sizeof (*b));
		qb.head++;
		qb.head %= QEBSize; // �����������
		qb.count--;
		return 1;
	} else return 0; 
}

u8 qbFirstIndex(void){
	return qb.head;
}

void qbIncIndex(u8* Index){
	(*Index)++;
	(*Index) %= QEBSize; // �����������
}

u8 qbLastFreeIndex(void){
	return qb.tail;
}

TBlock * qbGetBlockIndex(u8 Index){
	return &(qb.blks[Index]);
}

u8 qbDelFirst(void){
	// ���������� ����� �� �������
	// ���������� 1 - ���� ������
	// ���������� 0 - ������� ����� ������� ������
	if (qb.count > 0) {
		// ��������� ������� nc ����� ����� � �������� qb.head
		// � ����������������� �������� !*****!
		qb.head++;
		qb.head %= QEBSize; // �����������
		qb.count--;
		return 1;
	} else return 0; 
}

TBlock * qbFirstBlock(void){
	// ���������� ������ �� ������ ������� �������
	// ��� nil ���� �������� ���
	if (qb.count > 0) {
		// ������� �� �����
		// ���������� ������ �� ������
		//Msg("FBH %d\r\n",qb.head);
		return &(qb.blks[qb.head]);
	} else return NULL;
}

TBlock * qbLastBlock(void){
	u8 i;
	// ���������� ������ �� ��������� ������� �������
	// ��� nil ���� �������� ���
	if (qb.count > 0) {
		// ������� �� �����
		// ���������� ������ �� �����-1
		i = qb.tail;
		if (i > 0) i--;
		else i = QEBSize-1;
		Msg("LB i %d \r\n",i);
		return &(qb.blks[i]);
	} else return NULL;
}

TBlock * qbSecondBlock(void){
	// ���������� ������ �� ������ ������� �������
	// ��� nil ���� �������� ���
	u8 tmph;
	if (qb.count > 1) {
		// ������� �� �����
		// ���������� ������ �� �����
		tmph = (qb.head + 1)%QEBSize;
		return &(qb.blks[tmph]);
	} else return NULL;
}

TBlock * qbPrevPrgBlock(void){
	s8 tmpTail;
	// ���������� ������ �� ���������� ������� �������
	// ��� nil ���� �������� ���
	if (qb.count > 0) {
		// ������� �� �����
		// ���������� ������ �� �����
		tmpTail = qb.tail - 1;
		if (tmpTail < 0) tmpTail += QEBSize; 
		return &(qb.blks[tmpTail]);
	} else return NULL;
} 

u8 CheckG1Only(TBlock * b){
	// �������� ������� �������� �������� �� ��������
//	Msg("sGo %d\r\n",b->sGo);
	if 	(	(b->cFeed) ||
			(b->cSpindel) ||
			(b->cCold) ||
			(b->cPause) ||
			(b->cStop) 
		)
	{
//		Msg("G1 0\r\n");
		return 0;
	} else {
		// ��� �������� �������� �� ��������
		if 	(
				(	(b->comX) ||
					(b->comY) ||
					(b->comZ)
				) && 
				(b->sGo == 1)
			) {

//			Msg("G1 1\r\n");
			return 1;	// ���� ������� G1
		}
		else {
//			Msg("G1 0\r\n");
		 	return 0; // ��� ������� G1
		}
	}
}

u8 CheckG1FOnly(TBlock * b){
//	Msg("FsGo %d\r\n",b->sGo);
	if 	(	(b->cSpindel) ||
			(b->cCold) ||
			(b->cPause) ||
			(b->cStop) 
		)
	{
//		Msg("G1F 0\r\n");
		return 0;
	} else {
		// ��� �������� �������� �� ��������
		if 	(
				(	(b->comX) ||
					(b->comY) ||
					(b->comZ)
				) && 
				(b->sGo == 1)
			) {
//			Msg("G1F 1\r\n");
			return 1;	// ���� ������� G1
		}
		else {
//			Msg("G1F 0\r\n");
			return 0; // ��� ������� G1
		}
	}
}

u8 CheckAngle(float x0,float y0,float z0,float x1,float y1,float z1,float x2,float y2,float z2) {
	// �������� ���� 012
	float xv1,yv1,zv1,xv2,yv2,zv2,sm,m1,m2,a;
/*	
	Msg("CA %d %d %d   %d %d %d   %d %d %d\r\n",
		(int)(x0),
		(int)(y0),
		(int)(z0),
		(int)(x1),
		(int)(y1),
		(int)(z1),
		(int)(x2),
		(int)(y2),
		(int)(z2)
		);
*/	
	// ��������� ��� �������
	xv1 = x1 - x0;
	yv1 = y1 - y0;
	zv1 = z1 - z0;
	xv2 = x2 - x1;
	yv2 = y2 - y1;
	zv2 = z2 - z1;
	// ������� !!! ��� ����� ����� Z � ������ �� ���� (�������!!!)
	if ((zv1 <= 0)&&(zv2 > 0)) { /*Msg("Z");*/ return 0; }
	// � ����� ��������� ����������� ���� ������������� � ��������� ����������� !!!!!
	//************************************************
	// ����� ���� ����� ��������� v1 v2
//	Msg("xv1 %d yv1 %d zv1 %d\r\n",
//		(int)(xv1*1000),(int)(yv1*1000),(int)(zv1*1000));
//	Msg("xv2 %d yv2 %d zv2 %d\r\n",
//		(int)(xv2*1000),(int)(yv2*1000),(int)(zv2*1000));
	sm = xv1*xv2 + yv1*yv2 + zv1*zv2;
	m1 = sqrt(xv1*xv1+yv1*yv1+zv1*zv1);
	m2 = sqrt(xv2*xv2+yv2*yv2+zv2*zv2);
	//Msg("s\r\n");
	//Msg("sm %d m1 %d m2 %d\r\n",(int)(sm*1000),(int)(m1*1000),(int)(m2*1000));
	if ((m1*m2)!=0) {
		a = acos(sm/(m1*m2))*180/pi;
//		Msg("\t\t\t\ta %d\r\n",(int)(a*1000));
		if (a < *pTrAngle) {
//			Msg("<");
			return 1;
		} else {
//			Msg(">");
			return 0;
		}
	} {
//		Msg("m=0\r\n");
		return 0; // ���� �� �������� �������
	}
}

//	u8 errt; // ������ �����������
//	u8 res; // ������ ������
//	s32 sPos; // ����������� ������� � ������
	char st[50];
	TBlock ctb; // ���� ��� ����������

u8 CheckNextLine(float pX,float pY,float pZ,TBlock * b,TFileStream * strm){
	// 
	u8 errt; // ������ �����������
	u8 res; // ������ ������
	s32 sPos; // ����������� ������� � ������
//	char st[50];
//	TBlock ctb; // ���� ��� ����������

	memset((void*)&ctb,0,sizeof ctb);
	memset((void*)&st[0],0,50);

	bsFS_Pos(strm,&sPos); // ��������� ������� ��� ���������� ��������������
	res = bsFS_ReadLn(&ts,(u8*)st,50);
	//Msg("%s",s);
		// ������ !!!
	//	bsFS_Seek(strm,sPos);

	if (res == FS_RESULT_OK) {
		// �������
//		Msg("CNL px %d py %d\r\n",(int)(pX),(int)(pY));
		errt=TranslateLineToBlock(st,&ctb,b,0);
		
		// ��������������� �������, ������� ���� �� ������ ������
		bsFS_Seek(strm,sPos);
		//return 0;

		if (errt==0) {
			// ���������� ��� ������
			//Msg("z");
			if (CheckG1Only(&ctb)) {
	 			if (CheckAngle(pX,pY,pZ,b->Xd,b->Yd,b->Zd,ctb.Xd,ctb.Yd,ctb.Zd)) {
//					Msg("\t\t\tCNL A<\r\n");
					return 1; // ���� ������ ������
				}
				else {
//					Msg("\t\t\tCNL A>\r\n");
					return 0;// �������� ���� �� ������
				}
			} else {
//				Msg("\t\t\tCNL EG1\r\n");
				return 0; // � ����� �� ������ G1
			}
		} else {
//			Msg("\t\t\tCNL ET %d\r\n",errt);
			return 0; // ������ ����������
		}

	} else {
//		Msg("CNL ERL %d\r\n",res);
	 	return 0; // ������ �� �������
	}
}

TBlock rbs,rbc;
u8 SPS;


TBlock * ppb; // ������ �� ���������� ���� � �������
TBlock tb; // ���� ��� ����������
char s[50];
u8 EndTranslate = 0;

void TranslatePrgLine(const char * s){
	u8 errt; // ������ �����������
	u8 len;
//	float pX,pY,pZ;
	// ������������ ������� �� ������������� ������
	// ���� � ������� ���� �����
	memset((void*)&tb,0,sizeof tb);
	if (qbIsPlace()) {
		if (strlen(s) > 0) {
			//Msg("%s\r\n",s);
			//NumReadLine++;
			// ����� �������� ����������
//			if (NumReadLine == 1) {
//				StartTime(timeTrCalc);
//				Msg("Start TrTime\r\n");
//			}
//			memcpy(&(tb.s[0]),&s[0],50);
			// ������ �������
			//Msg("\t\t\t\tT%d: %s\r\n",NumReadLine,s);
			ppb = qbPrevPrgBlock(); // �������� ������ �� ���������� ����
//			Msg("ppb %x\r\n",ppb);
			//return;
			// �����������
			errt=TranslateLineToBlock(s,&tb,ppb,1);
			if (errt==0) {
				tb.NumLine = *pCurCadr; // ��������� ������
				len = strlen(s);
				memset((void*)&(tb.s[0]),0,50);
				memcpy((void*)&(tb.s[0]),(void*)&(s[0]),len);
				if (!tb.Nomove) {
					if (!qbAddBlock(&tb)) {
						Msg("Error Add Block To Prg Queue\r\n");
					}
				} else {
					//Msg("No Add Block (Nomove)\r\n");
#ifdef MOVE_D					
					Msg("(Nomove) %d\r\n",tb.NumLine);
#endif					
				}
				//Msg("\t\t\t\tNS %d\r\n",tb.Nonstop);
			} 
			// � �������� ��������� ��������� �� ������ ����������
			else Msg("Err Tr Line(%s). Ec %d\r\n",s,errt);
		} else {
			Msg("Error ReadNextPrgLine\r\n");
		}
	}// else Msg("NoPlace In Prg Queue\r\n");
	// 
//	Msg("T\r\n");
}

void TranslatePrg(void){
	u8 errt; // ������ �����������
	s8 res;
	float pX,pY,pZ;
	if (EndTranslate) return;
	// ������������ ������� �� ������������� ������
	// ���� � ������� ���� �����
	memset((void*)&tb,0,sizeof tb);
	memset((void*)&(s[0]),0,50);
	if (qbIsPlace()) {
		// ������ ������ �� ������ ���������� (ts)
		// �� ���� ����� ���������� ��� ������ ������
		// ����� ������� ��������� ������� � �����
		// ������� ����� ������� � ����
		save_ts_pos=ts.Pos;
		res=bsFS_ReadLn(&ts,(u8*)s,50);
		if (res==FS_RESULT_OK) {
			(*pNumReadLine)++;
			// ����� �������� ����������
//			if (NumReadLine == 1) {
//				StartTime(timeTrCalc);
//				Msg("Start TrTime\r\n");
//			}
			memcpy((void*)&(tb.s[0]),(void*)&(s[0]),50);
			// ������ �������
			//Msg("\t\t\t\tT%d: %s\r\n",NumReadLine,s);
			ppb = qbPrevPrgBlock(); // �������� ������ �� ���������� ����
#ifdef MOVE_D			
//			if (ppb != NULL)
//			Msg("ppb NL %d Xd %d Yd %d Zd %d NS %d\r\n",(*ppb).NumLine,OUTF1T((*ppb).Xd),OUTF1T((*ppb).Yd),OUTF1T((*ppb).Zd),(*ppb).Nonstop);
//			else Msg("ppb==Null\r\n");
#endif			
			//return;
			// �����������
			errt=TranslateLineToBlock(s,&tb,ppb,1);
			if (errt==0) {
				tb.NumLine = *pNumReadLine;
				memcpy((void*)&tb.s,(void*)&(s[0]),50);
				FS_Pos(ts.f,&tb.PosSSP);
				// ���� ��� ������ �� ��������� �� ������� ��������
				// ������ G1 � ����������
				if (ppb != NULL) {
					// ���� ���������� ����
//					Msg("ppb.Nonstop %d\r\n",(*ppb).Nonstop);
					if ((*ppb).Nonstop) {
						// ���������� ���� ���������������
						// ������ � ������� ����� ���� ������ G1
						if (CheckG1Only(&tb)) {
							// � ������� ����� ������ G1
							// ����� ��������� ��������� ����
//							Msg("pX %d pY %d",(int)((*ppb).Xd),(int)((*ppb).Yd));

							if (CheckNextLine((*ppb).Xd,(*ppb).Yd,(*ppb).Zd,&tb,&ts)) {
								tb.Nonstop = 1; // ���� ���������������
//								Msg("NS=1\r\n");
							}

						} 
					} else {
						// ���������� ���� ������������
						// ������ � ������� ����� ���� G1 � F
						if (CheckG1FOnly(&tb)) {
//							Msg("pX %d pY %d",(int)((*ppb).Xd),(int)((*ppb).Yd));

							if (CheckNextLine((*ppb).Xd,(*ppb).Yd,(*ppb).Zd,&tb,&ts)) {
								tb.Nonstop = 1; // ���� ���������������
//								Msg("NS=1\r\n");
							}

						} 
					}
				} else {
					// ��� ����������� �����
					// ������ ��������� G1 F
//					Msg("nb\r\n");
					if (CheckG1FOnly(&tb)) {
						XYZImpToXYZ(*(ms_X.Pos),*(ms_Y.Pos),*(ms_Z.Pos),&pX,&pY,&pZ);
						if (CheckNextLine(pX,pY,pZ,&tb,&ts)) {
							tb.Nonstop = 1; // ���� ���������������
//							Msg("NS=1\r\n");
						}
					} 
				}
				// ����� �������� ���� Nonstop ����������
				if (!tb.Nomove) {
					if (!qbAddBlock(&tb)) {
						Msg("Error Add Block To Prg Queue\r\n");
					}
#ifdef MOVE_D					
					Msg("Add Block %d %s NS %d\r\n",tb.NumLine,tb.s,tb.Nonstop);
#endif					
				} else {
					//Msg("No Add Block (Nomove)\r\n");
#ifdef MOVE_D					
					Msg("(Nomove) %d\r\n",tb.NumLine);
#endif					
				}
				//Msg("\t\t\t\tNS %d\r\n",tb.Nonstop);
			} 
			// � �������� ��������� ��������� �� ������ ����������
			else {
				Msg("Error Traslate Line(%s). Ecode %d \r\n",s,errt);
				// ���� ��� ����� ���������� ������ ��� ������ � G-����
				//EndTranslate = 1;
			}		
		} else {
			Msg("Error ReadNextPrgLine %d\r\n",res);
			if (FS_Eof(ts.f)==FS_EOF) {
				EndTranslate = 1;
			}
		}
	}// else Msg("NoPlace In Prg Queue\r\n");
	// 

//	Msg("T\r\n");
}

void SearchStopPoint(void){
	u8 errt; // ������ �����������
	char s[50];
	float dS;

	if (SPS) {
		// ����� �������
		// � rbs ������ ��� ������������� rbc
		// ����� rs � ������ �����
		memset((void*)&rbc,0,sizeof rbc);
		memset((void*)&(s[0]),0,50);
		dS = 0;
		// ������ ������
		if (bsFS_ReadLn(&rs,(u8*)s,50)==FS_RESULT_OK) {
			//������ ���������
#ifdef MOVE_D			
			Msg("\t\t\t\tSPS: %s",s);
#endif			
			// �����������
			errt=TranslateLineToBlock(s,&rbc,&rbs,1);
			if (errt==0) {
				// ���������� ��� ������
//				if (rbc.Nomove) {
//					// ���� �������
//					SPS = 1; // ���������� �����
//				} else {
					// ���� �����
					if (CheckG1Only(&rbc)) {
						// � ������� ����� ������ G1
						// ������ ����
						if (CheckAngle(	rbs.Xs,rbs.Ys,rbs.Zs,
										rbc.Xs,rbc.Ys,rbc.Zs,
										rbc.Xd,rbc.Yd,rbc.Zd
										)
							) {
							// ���� � �����
							// ����� ������������
							// ������� ���� ���������� ��������
							// ��������� ���� �������� �����
							dS = sqrt(sqr(rbc.Xd-rbc.Xs)+sqr(rbc.Yd-rbc.Ys)+sqr(rbc.Zd-rbc.Zs));
							// ��������� � ����������� ����
							Sr = Sr + dS; 
							Sri +=	rbc.Laxi; 
#ifdef MOVE_D			
							Msg("\t\t\t\tSPS A< Sr %d Sri %d dS %d dSi %d\r\n",OUTF1T(Sr),Sri,OUTF1T(dS),rbc.Laxi);
#endif
								memcpy(&rbs,&rbc,sizeof rbs);
							SPS = 1; // ���� �� ����������� � � � ��� 1
						} else {
							// ���� �������
							// ������������� �����
#ifdef MOVE_D			
							Msg("\t\t\t\tSPS A>\r\n");
#endif
							SPS = 0; // 
						}
					} else {
						// � ������� ����� �� ������ G1 ������ ������� ������
						// ������������� �����
#ifdef MOVE_D			
						Msg("\t\t\t\tSPS EG1\r\n");
#endif
						SPS = 0;
					}
				}
				//if (!SPS)	Msg("End SPS %d Sr %d\r\n",SPS,OUTF1T(Sr));

			} else {
				// ������ ����������
#ifdef MOVE_D			
				Msg("\t\t\t\tSPS ET\r\n");
#endif
				SPS = 0;
			}
		} else {
//			Msg("\t\t\t\tSPS ERL\r\n");
			// ������ ��������� �� �������
			SPS = 0;	// ��������� �����
		}
//		if (!SPS)	Msg("End SPS %d Sr %d\r\n",SPS,OUTF1T(Sr));
		
//	Msg("S\r\n");

}

void CrushWaterHandlerFrz(void){
	Msg("Crush Water.\r\n");
	if (*pPrgRun) {
		fStopPrg = 1;	
	}
	FIStop();
	*pCrushWater = 1;
}

void sG0HandlerFrz(void){
    //Msg("%d %d %d \r\n",*mc_X.MovePos,*(mc_Y.MovePos),*(mc_Z.MovePos));
	switch (sG0) {
		case 1:
			if ((!*(mc_X.MovePos))&&(!*(mc_Y.MovePos))&&(ms_X.Level==0)&&(ms_Y.Level==0)) {
				*(mc_Z.MovePos)=1;		
				sG0 = 2;
//				Msg("sG0 2\r\n");
			}
			break;
		case 2:
			if ((!*(mc_Z.MovePos))&&(ms_Z.Level==0)) {
				sG0 = 0;
				Busy = 0;
			}
			break;
		case 3:
			if ((!*(mc_Z.MovePos))&&(ms_Z.Level==0)) {
				*(mc_X.MovePos)=1;
				*(mc_Y.MovePos)=1;
				sG0 = 4;
//				Msg("sG0 4\r\n");
			}
			break;
		case 4:
			if ((!*(mc_X.MovePos))&&(!*(mc_Y.MovePos))&&(ms_X.Level==0)&&(ms_Y.Level==0)) {
				sG0 = 0;
				Busy = 0;
			}
			break;			
	}
}


TBlock * eb = NULL;
TBlock * nb;


void RunNextCadrFrzMain(void){

//	TBlock tb;
//	if (qb.count>5) qbExtrBlock(&tb) ;
//	return;

	if (sG0 != 0) { 
		//Msg("sG0");
		sG0HandlerFrz();
		return;
	}
	if (Busy) {
		//Msg("B cX %d sX %d",(int)mvc.Xe,(int)mvs.Xe);
//		StartTimeTC(T2);
		return;
	}
	// ���������� �����
	switch (*pRCS) {
		// ��������� ��������� ������
		case rcsGetBlock:
			eb = qbFirstBlock();
			if (eb!=NULL) {
				// ���� ����
				// ��������� ��� �����
				// ������� !!!
				//Msg("m%d: %s",(*eb).NumLine,(*eb).s);
//				ShowTimeTC(T1,1);
//				ShowTimeTC(T2,2);
//				StartTimeTC(T2);
				
//				Msg("X %d %d Y %d %d Z %d %d\r\n",(*eb).Xsi,(*eb).Xdi,(*eb).Ysi,(*eb).Ydi,(*eb).Zsi,(*eb).Zdi);
//				Msg("tb %d \r\n",(*eb).Tb);
				
				// ��������� ������
				if (((*eb).sGo ==1)) {
					if ((*eb).Nonstop == 0) {
						// ���� ��������. ����� �� ����������
						Sr = sqrt(sqr((*eb).Xd-(*eb).Xs)+sqr((*eb).Yd-(*eb).Ys)+sqr((*eb).Zd-(*eb).Zs));
						Sri = (*eb).Laxi;
#ifdef MOVE_D						
						Msg("BlockStop Sr %d Sri %d\r\n",OUTF1T(Sr),Sri);
#endif						
						SPS = 0;
					} else {
						// ��������� �������� ������ ����������� ����
						Sr = sqrt(sqr((*eb).Xd-(*eb).Xs)+sqr((*eb).Yd-(*eb).Ys)+sqr((*eb).Zd-(*eb).Zs));
						Sri = (*eb).Laxi;
						// ��������� ��������� ����						
						nb = qbSecondBlock();
						if (nb == NULL) {
							//����� ��� ����� �� ���������
#ifdef MOVE_D						
							Msg("nb0 Sr %d\r\n",OUTF1T(Sr));
#endif
							SPS = 0;
						} else {
							// ���� ����
							// ��������� � ����������� ���� ���� ���������� �����
#ifdef MOVE_D						
								Msg("\t\t\t\tSPS Prev Sr %d Sri %d\r\n",OUTF1T(Sr),Sri);
#endif
							Sr = Sr + sqrt(sqr((*nb).Xd-(*nb).Xs)+sqr((*nb).Yd-(*nb).Ys)+sqr((*nb).Zd-(*nb).Zs));
							Sri += (*nb).Laxi;
							// ��������� ���� ��� ������������
							// �������� ����� � ����
							// ������������� �������� ����
							if ((*nb).Nonstop) {
								// �������� �����
								memcpy(&rbs,nb,sizeof rbs);
								// �������������� ������� � ����� ��������� � ������� ����� ������������ �����
								rs.Pos = (*nb).PosSSP;
								rs.f = ts.f;
#ifdef MOVE_D						
								Msg("\t\t\t\tSPS Prepare Sr %d Sri %d\r\n",OUTF1T(Sr),Sri);
#endif
								SPS=1;
							} else {
								SPS = 0;
							}
						}
					}
				}
//				Msg("Xs %d Xd %d Ys %d Yd %d Zs %d Zd %d\r\n",
//					(int)((*eb).Xs*1000),(int)((*eb).Xd*1000),
//					(int)((*eb).Ys*1000),(int)((*eb).Yd*1000),
//					(int)((*eb).Zs*1000),(int)((*eb).Zd*1000));

//**************************************************
				(*pCurCadr) = (*eb).NumLine;
//				Msg("RM%d:Sr %d \r\n",(*eb).NumLine,(int)(Sr*1000));
//				Msg("RM%d:G%d Xd %d Yd %d Zd %d F %d\r\n",(*eb).NumLine,(*eb).sGo,OUTF1T((*eb).Xd),OUTF1T((*eb).Yd),OUTF1T((*eb).Zd),OUTF1((*eb).Feed));
				memcpy((void*)&(BR_pCurCadr),(void*)pCurCadr,4);
				SetFeed(eb);  
				SetSpindle(eb);	 
				SetCold(eb);	 
				SetPause(eb);
				*pRCS = rcsWaitPause; 
				//Msg("sGo %d NS %d SPS %d RSPS %d",(*eb).sGo,(*eb).Nonstop,SPS,RSPS);
			} else {
				// ������� �����
				Msg("Queue is Empty\r\n");
				*pRCS = rcsEnd; 
			}
		break;
		case rcsWaitPause:
			// ����� ������� ��������� �����
			if (EndPause()) {
				*pRCS = rcsSetGo; 
//				Msg("End Pause\r\n");
			}
		break;
//11	G0,G1	�����������
		case rcsSetGo:
			//ShowTimeTC(T2,2);
			SetGoFrz(eb);
			*pRCS = rcsWaitGo; 
		break;
		case rcsWaitGo:
			if (EndGo()) {
//				if ((*eb).Nonstop) {
//					// ����������� ������ ���������� �����
//					eb = NULL;
//					qbDelFirst();
//					eb = qbFirstBlock();
//					if (eb!=NULL) {
//						//SetGo(eb);
//						//Busy = 1;
//						// ������ ���������
//					    //fmvc.Enable=1;
//					} else {
//						// ������� !!!
//	 					*pRCS = rcsGetBlock; 
//						//*pRCS = rcsEnd; 
//					}
// 					//*pRCS = rcsGetBlock; 
//				} else {
//					// ����� �������� �� �����������
//					*(fmvs.Vc) = *(fmvc.Vmin);
//					*pRCS = rcsSetStop; 
//				}
				// ������� !!!
				*pRCS = rcsSetStop; 
			}
		break;
//13	M0,M1,M2	�������
		case rcsSetStop:
			SetStop(eb);
			*pRCS = rcsWaitStop; 
		break;
		case rcsWaitStop:
			if (EndStop()) {
				*pRCS = rcsEndExecute; 
			}
		break;
		// ��������� ���������
		case rcsEndExecute:
			//Msg("ERun %d\r\n",(*eb).NumLine);
			// �������� �� ������ ����������
		    if ((*eb).cStop==1) {
				(*eb).cStop=0;
				if ((*eb).sStop == 2) {
		 			*pRCS = rcsEnd; 
					break;
				}
				if ((*eb).sStop == 120) {
					Msg("CyclePrg");
					eb = NULL;
					*pCurCadr = 0; // ������� ����� �����
					memcpy((void*)&(BR_pCurCadr),(void*)pCurCadr,4);
					*pRCS = rcsGetBlock; // ��������� ���������� ����� "������ ��������� ������" 
					FS_Close(pPrgFileHandle);
					*pPrgFileHandle = -1;
					EndTranslate = 0;
					fStartPrg = 1;
					break;
				}
			}
			SaveFilePos();		
//			Msg("sfp %d\r\n",BR_FilePos);
			qbDelFirst();
			eb = NULL;
 			*pRCS = rcsGetBlock; 
		break;
		// ����� ����������
		case rcsEnd:
			Msg("EndPrg");
			eb = NULL;
			*pPrgRun = 0;
			BR_pPrgRun = *pPrgRun;
			*pCurCadr = 0; // ������� ����� �����
			memcpy((void*)&(BR_pCurCadr),(void*)pCurCadr,4);
			*pRCS = rcsGetBlock; // ��������� ���������� ����� "������ ��������� ������" 
			FS_Close(pPrgFileHandle);
			*pPrgFileHandle = -1;
			EndTranslate = 0;
		break;
	}
}

void SaveFilePos(void){
	// ���������� ������� ����� � ����������������� ��������
	memcpy((void*)&(BR_FilePos),(void*)(&((*eb).FilePos)),4); 
}	


#endif
