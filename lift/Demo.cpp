/****************************************************************/
/* demo.c														*/
/****************************************************************/
#include "peg.hpp"
#include "demo.h"
#include "math.h"
#include "HEADER.h"
#include <embkern.h>
#include <embclib.h>
#include <malloc.h>
#include <video.h>

#include "Header.h"
#include "tunes.inc"
#include <process.h>

unsigned int __stdcall sm_thread(void* pArguments);
unsigned int __stdcall music_thread(void* pArguments);



/****************************************************************/
/* MAIN                                                         */
/****************************************************************/
Ubyte KeyBeep(void);  // wait for key, then BEEP


void demo()
{
	HANDLE hThread_sm,hThread_music;
	unsigned int threadID_sm,threadID_music;

	Ubyte key;
	char t;
	//char LCDStr[7];
	char k, s[10];


    PegPresentationManager *pScrMgr;
	EcsPic *pEcsPic;

	HANDLE hpEcsPic, hpScrMgr,hGuiThread;

	void EcsGuiInit(HANDLE *hGuiThread, HANDLE *hpScrMgr , HANDLE *hpEcsPic);
	char EcsDrawBMP(char *file, PegPresentationManager *pScrMgr);


	// Basement
	char image1[] ="C:\\images\\lb.BMP";
	char image2[] ="C:\\images\\lbm.BMP";

	// Level 1
	char image3[] ="C:\\images\\l1.BMP";
	char image4[] ="C:\\images\\l1m.BMP";

	// Level 2
	char image5[] ="C:\\images\\l2.BMP";
	char image6[] ="C:\\images\\l2m.BMP";

	// Level 3
	char image7[] ="C:\\images\\l3.BMP";
	char image8[] ="C:\\images\\l3m.BMP";

	// Level 4
	char image9[] ="C:\\images\\l4.BMP";
	char image10[] ="C:\\images\\l4m.BMP";

	// Level 5
	char image11[] ="C:\\images\\l5.BMP";
	char image12[] ="C:\\images\\l5m.BMP";


	// char toggleIm,k, s[10];
	char previouslevel=1;
 	LedDisp(0xc);
    LcdInit();		/* Initialise Lcd screen */
	LcdLine1();LcdMsg("The Canopy      ");
    LcdLine2();LcdMsg("Residences      ");
	BEEP();

	EcsGuiInit(&hGuiThread, &hpScrMgr, &hpEcsPic);	/* initialise graphics */
	pEcsPic = (EcsPic *)hpEcsPic;
	pScrMgr = (PegPresentationManager *)hpScrMgr;

	EcsDrawBMP(image1, pScrMgr);	/* Demo Welcome */
	// toggleIm = 0;

	hThread_sm = (HANDLE)_beginthreadex(NULL,0,&sm_thread,NULL,0,&threadID_sm);
	SuspendThread(hThread_sm);
	hThread_music = (HANDLE)_beginthreadex(NULL,0,&music_thread,NULL,0,&threadID_music);
	SuspendThread(hThread_music);

	//SuspendThread(hThread_music);
	while(1)
	{
		Sleep(10);
		key = KeyBeep();
		switch (key)
		{

		case 0: // basement

				EcsDrawBMP(image1, pScrMgr);
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Basement    ");
				Sleep(1500);
				LcdClear();
                for(t=previouslevel;t>key;t--)
				{
					
					previouslevel--;
					//Spin(CCW,200,1);
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");

		
				}
				Sleep(1500);
				ResumeThread(hThread_music);
                LcdClear();
                LcdLine1();LcdMsg("    Basement    ");
				LcdLine2();LcdMsg(" Floor reached! ");
				Sleep(1000);
				SuspendThread(hThread_music);
				LcdLine2();LcdMsg("   Door  Open   ");
				Sleep(2000);
				LcdLine2();LcdMsg("   Door Close   ");
				Sleep(1000);
				EcsDrawBMP(image1, pScrMgr);
				LcdLine1();LcdMsg("    Basement    ");
				LcdLine2();LcdMsg("                ");
				previouslevel=0;
				break;
				
				
		case 1 : // level 1

				// go to level 1
				LcdClear();
				EcsDrawBMP(image4, pScrMgr);
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Level 1");
				Sleep(1500);
				LcdClear();

				if(key>previouslevel) {
					
					for(t=1;t<key;t++)
					{
					
						previouslevel++;
						Spin(CW,200,1);
						LcdLine1();
						itoa((int)previouslevel,s,16);
						// EcsDrawBMP(image7, pScrMgr);
						LcdMsg("Level ");
						LcdMsg(s);
						// LcdMsg("    ");
					}
					previouslevel=1;

				} else {

					for(t=previouslevel;t>key;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					EcsDrawBMP(image3, pScrMgr);
					LcdMsg("Level ");
					LcdMsg(s);
					// LcdMsg("    ");
					}
					previouslevel=1;

				}

				Sleep(3000);

				

				// level reached - play music
				EcsDrawBMP(image3, pScrMgr);
				ResumeThread(hThread_music);
				LcdClear();
				LcdLine1();LcdMsg("Level 1");
	            LcdLine2();LcdMsg("Floor reached!");
				Sleep(1000);
				SuspendThread(hThread_music);
 
 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 1");
				LcdLine2();LcdMsg("Door Open");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				// level reached - delay for passengers to alight
				Sleep(5000);

 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 1");
				LcdLine2();LcdMsg("Door Close");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				if(ScanKey()==0xff)
				{
				LcdClear();
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Basement");
				Sleep(1000);
				LcdClear();

				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				EcsDrawBMP(image1, pScrMgr);
				LcdLine1();LcdMsg("    Basement    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=0;

				}
				break;

		case 2 : // level 2

				// go to level 2
				LcdClear();
				EcsDrawBMP(image6, pScrMgr);
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Level 2");
				Sleep(1500);
				LcdClear();

				if(key>previouslevel) {
					
					for(t=1;t<key;t++)
					{
					
						previouslevel++;
						Spin(CW,200,1);
						LcdLine1();
						itoa((int)previouslevel,s,16);
						// EcsDrawBMP(image7, pScrMgr);
						LcdMsg("Level ");
						LcdMsg(s);
						// LcdMsg("    ");
					}
					previouslevel=2;

				} else {

					for(t=previouslevel;t>key;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					EcsDrawBMP(image5, pScrMgr);
					LcdMsg("Level ");
					LcdMsg(s);
					// LcdMsg("    ");
					}
					previouslevel=2;

				}

				Sleep(3000);

				

				// level reached - play music
				EcsDrawBMP(image5, pScrMgr);
				ResumeThread(hThread_music);
				LcdClear();
				LcdLine1();LcdMsg("Level 2");
	            LcdLine2();LcdMsg("Floor reached!");
				Sleep(1000);
				SuspendThread(hThread_music);
 
 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 2");
				LcdLine2();LcdMsg("Door Open");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				// level reached - delay for passengers to alight
				Sleep(5000);

 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 2");
				LcdLine2();LcdMsg("Door Close");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				if(ScanKey()==0xff)
				{
				LcdClear();
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Basement");
				Sleep(1000);
				LcdClear();

				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				EcsDrawBMP(image1, pScrMgr);
				LcdLine1();LcdMsg("    Basement    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=0;

				}
				break;
	

		case 3: // level 3

				// go to level 3
				LcdClear();
				EcsDrawBMP(image8, pScrMgr);
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Level 3");
				Sleep(1500);
				LcdClear();

				if(key>previouslevel) {
					
					for(t=1;t<key;t++)
					{
					
						previouslevel++;
						Spin(CW,200,1);
						LcdLine1();
						itoa((int)previouslevel,s,16);
						// EcsDrawBMP(image7, pScrMgr);
						LcdMsg("Level ");
						LcdMsg(s);
						// LcdMsg("    ");
					}
					previouslevel=3;

				} else {

					for(t=previouslevel;t>key;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					EcsDrawBMP(image7, pScrMgr);
					LcdMsg("Level ");
					LcdMsg(s);
					// LcdMsg("    ");
					}
					previouslevel=3;

				}

				Sleep(3000);

				

				// level reached - play music
				EcsDrawBMP(image7, pScrMgr);
				ResumeThread(hThread_music);
				LcdClear();
				LcdLine1();LcdMsg("Level 3");
	            LcdLine2();LcdMsg("Floor reached!");
				Sleep(1000);
				SuspendThread(hThread_music);
 
 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 3");
				LcdLine2();LcdMsg("Door Open");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				// level reached - delay for passengers to alight
				Sleep(5000);

 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 3");
				LcdLine2();LcdMsg("Door Close");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				if(ScanKey()==0xff)
				{
				LcdClear();
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Basement");
				Sleep(1000);
				LcdClear();

				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				EcsDrawBMP(image1, pScrMgr);
				LcdLine1();LcdMsg("    Basement    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=0;

				}
				break;

		case 4: // level 4

				// go to level 4
				LcdClear();
				EcsDrawBMP(image10, pScrMgr);
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Level 4");
				Sleep(1500);
				LcdClear();

				if(key>previouslevel) {
					
					for(t=1;t<key;t++)
					{
					
						previouslevel++;
						Spin(CW,200,1);
						LcdLine1();
						itoa((int)previouslevel,s,16);
						// EcsDrawBMP(image7, pScrMgr);
						LcdMsg("Level ");
						LcdMsg(s);
						// LcdMsg("    ");
					}
					previouslevel=4;

				} else {

					for(t=previouslevel;t>key;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					EcsDrawBMP(image9, pScrMgr);
					LcdMsg("Level ");
					LcdMsg(s);
					// LcdMsg("    ");
					}
					previouslevel=4;

				}

				Sleep(3000);

				

				// level reached - play music
				EcsDrawBMP(image9, pScrMgr);
				ResumeThread(hThread_music);
				LcdClear();
				LcdLine1();LcdMsg("Level 4");
	            LcdLine2();LcdMsg("Floor reached!");
				Sleep(1000);
				SuspendThread(hThread_music);
 
 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 4");
				LcdLine2();LcdMsg("Door Open");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				// level reached - delay for passengers to alight
				Sleep(5000);

 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 4");
				LcdLine2();LcdMsg("Door Close");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				if(ScanKey()==0xff)
				{
				LcdClear();
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Basement");
				Sleep(1000);
				LcdClear();

				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				EcsDrawBMP(image1, pScrMgr);
				LcdLine1();LcdMsg("    Basement    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=0;

				}
				break;

		case 5: // level 5

				// go to level 5
				LcdClear();
				//EcsDrawBMP(image10, pScrMgr);
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Level 5");
				Sleep(1500);
				LcdClear();

				if(key>previouslevel) {
					
					for(t=1;t<key;t++)
					{
					
						previouslevel++;
						Spin(CW,200,1);
						LcdLine1();
						itoa((int)previouslevel,s,16);
						// EcsDrawBMP(image7, pScrMgr);
						LcdMsg("Level ");
						LcdMsg(s);
						// LcdMsg("    ");
					}
					previouslevel=5;

				} else {

					for(t=previouslevel;t>key;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					//EcsDrawBMP(image9, pScrMgr);
					LcdMsg("Level ");
					LcdMsg(s);
					// LcdMsg("    ");
					}
					previouslevel=5;

				}

				Sleep(3000);

				

				// level reached - play music
				//EcsDrawBMP(image7, pScrMgr);
				ResumeThread(hThread_music);
				LcdClear();
				LcdLine1();LcdMsg("Level 5");
	            LcdLine2();LcdMsg("Floor reached!");
				Sleep(1000);
				SuspendThread(hThread_music);
 
 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 5");
				LcdLine2();LcdMsg("Door Open");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				// level reached - delay for passengers to alight
				Sleep(5000);

 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 5");
				LcdLine2();LcdMsg("Door Close");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				if(ScanKey()==0xff)
				{
				LcdClear();
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Basement");
				Sleep(1000);
				LcdClear();

				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				EcsDrawBMP(image1, pScrMgr);
				LcdLine1();LcdMsg("    Basement    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=0;

				}
				break;

		case 6: // level 6

				// go to level 6
				LcdClear();
				//EcsDrawBMP(image10, pScrMgr);
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Level 6");
				Sleep(1500);
				LcdClear();

				if(key>previouslevel) {
					
					for(t=1;t<key;t++)
					{
					
						previouslevel++;
						Spin(CW,200,1);
						LcdLine1();
						itoa((int)previouslevel,s,16);
						// EcsDrawBMP(image7, pScrMgr);
						LcdMsg("Level ");
						LcdMsg(s);
						// LcdMsg("    ");
					}
					previouslevel=6;

				} else {

					for(t=previouslevel;t>key;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					//EcsDrawBMP(image9, pScrMgr);
					LcdMsg("Level ");
					LcdMsg(s);
					// LcdMsg("    ");
					}
					previouslevel=6;

				}

				Sleep(3000);

				

				// level reached - play music
				//EcsDrawBMP(image7, pScrMgr);
				ResumeThread(hThread_music);
				LcdClear();
				LcdLine1();LcdMsg("Level 6");
	            LcdLine2();LcdMsg("Floor reached!");
				Sleep(1000);
				SuspendThread(hThread_music);
 
 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 6");
				LcdLine2();LcdMsg("Door Open");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				// level reached - delay for passengers to alight
				Sleep(5000);

 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 6");
				LcdLine2();LcdMsg("Door Close");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				if(ScanKey()==0xff)
				{
				LcdClear();
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Basement");
				Sleep(1000);
				LcdClear();

				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				EcsDrawBMP(image1, pScrMgr);
				LcdLine1();LcdMsg("    Basement    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=0;

				}
				break;
		

		case 7: // level 6

				// go to level 7
				LcdClear();
				//EcsDrawBMP(image10, pScrMgr);
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Level 7");
				Sleep(1500);
				LcdClear();

				if(key>previouslevel) {
					
					for(t=1;t<key;t++)
					{
					
						previouslevel++;
						Spin(CW,200,1);
						LcdLine1();
						itoa((int)previouslevel,s,16);
						// EcsDrawBMP(image7, pScrMgr);
						LcdMsg("Level ");
						LcdMsg(s);
						// LcdMsg("    ");
					}
					previouslevel=7;

				} else {

					for(t=previouslevel;t>key;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					//EcsDrawBMP(image9, pScrMgr);
					LcdMsg("Level ");
					LcdMsg(s);
					// LcdMsg("    ");
					}
					previouslevel=7;

				}

				Sleep(3000);

				

				// level reached - play music
				//EcsDrawBMP(image7, pScrMgr);
				ResumeThread(hThread_music);
				LcdClear();
				LcdLine1();LcdMsg("Level 7");
	            LcdLine2();LcdMsg("Floor reached!");
				Sleep(1000);
				SuspendThread(hThread_music);
 
 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 7");
				LcdLine2();LcdMsg("Door Open");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				// level reached - delay for passengers to alight
				Sleep(5000);

 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 7");
				LcdLine2();LcdMsg("Door Close");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				if(ScanKey()==0xff)
				{
				LcdClear();
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Basement");
				Sleep(1000);
				LcdClear();

				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				EcsDrawBMP(image1, pScrMgr);
				LcdLine1();LcdMsg("    Basement    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=0;

				}
				break;

		case 8: // level 8

				// go to level 8
				LcdClear();
				//EcsDrawBMP(image10, pScrMgr);
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Level 8");
				Sleep(1500);
				LcdClear();

				if(key>previouslevel) {
					
					for(t=1;t<key;t++)
					{
					
						previouslevel++;
						Spin(CW,200,1);
						LcdLine1();
						itoa((int)previouslevel,s,16);
						// EcsDrawBMP(image7, pScrMgr);
						LcdMsg("Level ");
						LcdMsg(s);
						// LcdMsg("    ");
					}
					previouslevel=8;

				} else {

					for(t=previouslevel;t>key;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					//EcsDrawBMP(image9, pScrMgr);
					LcdMsg("Level ");
					LcdMsg(s);
					// LcdMsg("    ");
					}
					previouslevel=8;

				}

				Sleep(3000);

				

				// level reached - play music
				//EcsDrawBMP(image7, pScrMgr);
				ResumeThread(hThread_music);
				LcdClear();
				LcdLine1();LcdMsg("Level 8");
	            LcdLine2();LcdMsg("Floor reached!");
				Sleep(1000);
				SuspendThread(hThread_music);
 
 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 8");
				LcdLine2();LcdMsg("Door Open");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				// level reached - delay for passengers to alight
				Sleep(5000);

 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 8");
				LcdLine2();LcdMsg("Door Close");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				if(ScanKey()==0xff)
				{
				LcdClear();
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Basement");
				Sleep(1000);
				LcdClear();

				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				EcsDrawBMP(image1, pScrMgr);
				LcdLine1();LcdMsg("    Basement    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=0;

				}
				break;
		
		case 9: // level 9

				// go to level 9
				LcdClear();
				//EcsDrawBMP(image10, pScrMgr);
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Level 9");
				Sleep(1500);
				LcdClear();

				if(key>previouslevel) {
					
					for(t=1;t<key;t++)
					{
					
						previouslevel++;
						Spin(CW,200,1);
						LcdLine1();
						itoa((int)previouslevel,s,16);
						// EcsDrawBMP(image7, pScrMgr);
						LcdMsg("Level ");
						LcdMsg(s);
						// LcdMsg("    ");
					}
					previouslevel=9;

				} else {

					for(t=previouslevel;t>key;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					//EcsDrawBMP(image9, pScrMgr);
					LcdMsg("Level ");
					LcdMsg(s);
					// LcdMsg("    ");
					}
					previouslevel=9;

				}

				Sleep(3000);

				

				// level reached - play music
				//EcsDrawBMP(image7, pScrMgr);
				ResumeThread(hThread_music);
				LcdClear();
				LcdLine1();LcdMsg("Level 9");
	            LcdLine2();LcdMsg("Floor reached!");
				Sleep(1000);
				SuspendThread(hThread_music);
 
 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 9");
				LcdLine2();LcdMsg("Door Open");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				// level reached - delay for passengers to alight
				Sleep(5000);

 				// level reached - activate motor for door openinng
				LcdClear();
				LcdLine1();LcdMsg("Level 9");
				LcdLine2();LcdMsg("Door Close");
				ResumeThread(hThread_sm);
				Sleep(2000);
				SuspendThread(hThread_sm);

				if(ScanKey()==0xff)
				{
				LcdClear();
				LcdLine1();LcdMsg("Lift moving to");
	            LcdLine2();LcdMsg("Basement");
				Sleep(1000);
				LcdClear();

				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				EcsDrawBMP(image1, pScrMgr);
				LcdLine1();LcdMsg("    Basement    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=0;

				}
				break;
		
				

		case 10: // door control
				ResumeThread(hThread_sm);
				LcdClear();
				LcdLine1();LcdMsg("Door Opening");
				LcdLine2();LcdMsg("                ");
				Sleep(2000);
				SuspendThread(hThread_sm);

				break;
		case 11: // door control
				ResumeThread(hThread_sm);
				LcdClear();
				LcdLine1();LcdMsg("Door Closing");
				LcdLine2();LcdMsg("                ");
				Sleep(2000);
				SuspendThread(hThread_sm);
			
				break;

				
		}
			LcdClear();
			LcdLine1();LcdMsg("The Canopy");
			LcdLine2();LcdMsg("Press a key ...");

	}
}


Ubyte KeyBeep(void)
{
	Ubyte c;
	c = KeyPressed();
	LedDisp(c);
	BEEP();
	return c;
}

unsigned int __stdcall sm_thread(void* pArguments)
{
	while(1)
	{
		Spin( CW,100,10); // turn motor clockwise, 100 steps
		Spin(CCW,100,10); // turn motor counterclockwise, 100 steps
	}
	return(0);
}

unsigned int __stdcall music_thread(void* pArguments)
{
	
	while(TRUE)
	{
		PlaySong((const char*)Lift);
		Sleep(500);
	
	}
	return(0);
}
