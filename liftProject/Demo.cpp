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
#include <string.h>
#include <stdlib.h>

#include "Header.h"
#include "tunes.inc"
#include <process.h>

unsigned int __stdcall sm_thread(void *pArguments);
unsigned int __stdcall music_thread(void *pArguments);

/****************************************************************/
/* MAIN                                                         */
/****************************************************************/
Ubyte KeyBeep(void); // wait for key, then BEEP

void demo()

{
	HANDLE hThread_sm, hThread_music;
	unsigned int threadID_sm, threadID_music;

	Ubyte key;
	char t;
	//char LCDStr[7];
	char k, s[10], j, jTest[18], jTest2[19], jTest3[18];

	PegPresentationManager *pScrMgr;
	EcsPic *pEcsPic;

	HANDLE hpEcsPic, hpScrMgr, hGuiThread;

	void EcsGuiInit(HANDLE * hGuiThread, HANDLE * hpScrMgr, HANDLE * hpEcsPic);
	char EcsDrawBMP(char *file, PegPresentationManager *pScrMgr);

	// Basement
	char lb[] = "C:\\images\\lb.BMP";
	char lbm[] = "C:\\images\\lbm.BMP";
	char lbm2[] = "C:\\images\\lbm2.BMP";

	// Level 1
	char l1[] = "C:\\images\\l1.BMP";
	char l1m[] = "C:\\images\\l1m.BMP";
	char l1m2[] = "C:\\images\\l1m2.BMP";
	char l1d[] = "C:\\images\\l1d.BMP";

	// Level 2
	char l2[] = "C:\\images\\l2.BMP";
	char l2m[] = "C:\\images\\l2m.BMP";
	char l2m2[] = "C:\\images\\l2m2.BMP";
	char l2d[] = "C:\\images\\l2d.BMP";

	// Level 3
	char l3[] = "C:\\images\\l3.BMP";
	char l3m[] = "C:\\images\\l3m.BMP";
	char l3m2[] = "C:\\images\\l3m2.BMP";
	char l3d[] = "C:\\images\\l3d.BMP";

	// Level 4
	char l4[] = "C:\\images\\l4.BMP";
	char l4m[] = "C:\\images\\l4m.BMP";
	char l4m2[] = "C:\\images\\l4m2.BMP";
	char l4d[] = "C:\\images\\l4d.BMP";

	// Level 5
	char l5[] = "C:\\images\\l5.BMP";
	char l5m[] = "C:\\images\\l5m.BMP";
	char l5m2[] = "C:\\images\\l5m2.BMP";
	char l5d[] = "C:\\images\\l5d.BMP";

	// Level 6
	char l6[] = "C:\\images\\l6.BMP";
	char l6m[] = "C:\\images\\l6m.BMP";
	char l6m2[] = "C:\\images\\l6m2.BMP";
	char l6d[] = "C:\\images\\l6d.BMP";

	// Level 7
	char l7[] = "C:\\images\\l7.BMP";
	char l7m[] = "C:\\images\\l7m.BMP";
	char l7m2[] = "C:\\images\\l7m2.BMP";
	char l7d[] = "C:\\images\\l7d.BMP";

	// Level 8
	char l8[] = "C:\\images\\l8.BMP";
	char l8m[] = "C:\\images\\l8m.BMP";
	char l8m2[] = "C:\\images\\l8m2.BMP";
	char l8d[] = "C:\\images\\l8d.BMP";

	// Level 9
	char l9[] = "C:\\images\\l9.BMP";
	char l9d[] = "C:\\images\\l9d.BMP";

	// char toggleIm,k, s[10];
	char previouslevel = 0;
	// char previouslevel = 1;

	int count = 0;

	LedDisp(0xc);
	LcdInit(); /* Initialise Lcd screen */
	LcdClear();
	LcdLine1();
	LcdMsg("The Canopy");
	LcdLine2();
	LcdMsg("Residences");
	BEEP();

	EcsGuiInit(&hGuiThread, &hpScrMgr, &hpEcsPic); /* initialise graphics */
	pEcsPic = (EcsPic *)hpEcsPic;
	pScrMgr = (PegPresentationManager *)hpScrMgr;

	EcsDrawBMP(lb, pScrMgr); /* Demo Welcome */
	// toggleIm = 0;

	hThread_sm = (HANDLE)_beginthreadex(NULL, 0, &sm_thread, NULL, 0, &threadID_sm);
	SuspendThread(hThread_sm);
	hThread_music = (HANDLE)_beginthreadex(NULL, 0, &music_thread, NULL, 0, &threadID_music);
	SuspendThread(hThread_music);

	Ubyte key2;

	char str[] = {'l', '0', 'm'};

	while (1)
	{

		key2 = KeyBeep();

		if (count < 30000)
		{

			//count = 0; count < 30000; count += 200

			for (count = 0; count < 10000; count += 200)
			{

				Sleep(200);

				if (key2 != 0xFF)
				{

					key = key2;
				}
				else
				{

					key = ScanKey();
				}

				switch (key)
				{

				case 0: // basement

					EcsDrawBMP(lb, pScrMgr);
					LcdClear();
					LcdLine1();
					LcdMsg("Lift moving to basement");
					LcdLine2();
					LcdMsg("Basement");
					Sleep(1000);
					LcdClear();

					for (t = previouslevel; t > key; t--)
					{

						previouslevel--;
						//Spin(CCW,200,1);
						LcdLine1();
						itoa((int)previouslevel, s, 16);
						LcdMsg("    Level  ");
						LcdMsg(s);
						LcdMsg("    ");
					}

					LcdClear();
					LcdLine2();
					LcdMsg("Door  Open");
					Sleep(2000);
					LcdLine2();
					LcdMsg("Door Close");
					Sleep(1000);
					EcsDrawBMP(lb, pScrMgr);
					LcdLine1();

					previouslevel = 0;
					count = 0;
					break;

				case 1:
					// go to level 1
					LcdClear();
					EcsDrawBMP(lbm, pScrMgr);
					LcdLine1();
					LcdMsg("Lift moving to");
					LcdLine2();
					LcdMsg("Level 1");
					Sleep(250);
					LcdClear();

					if (key > previouslevel)
					{

						for (t = previouslevel; t < key - 1; t++)
						{

							previouslevel++;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest, "C:\\images\\l%dm.BMP", (int)previouslevel);

							sprintf(jTest2, "C:\\images\\l%dm2.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							EcsDrawBMP(jTest, pScrMgr);
							Sleep(200);
							EcsDrawBMP(jTest2, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
						}

						previouslevel = 1;
					}
					else
					{

						for (t = previouslevel; t > key; t--)
						{

							previouslevel--;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest3, "C:\\images\\l%dd.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							Sleep(200);
							EcsDrawBMP(jTest3, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
						}
						previouslevel = 1;
					}

					Sleep(3000);

					// level reached - play music
					EcsDrawBMP(l1, pScrMgr);
					ResumeThread(hThread_music);
					LcdClear();
					LcdLine1();
					LcdMsg("Level 1");
					LcdLine2();
					LcdMsg("Floor reached!");
					Sleep(1000);
					SuspendThread(hThread_music);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 1");
					LcdLine2();
					LcdMsg("Door Open");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					// level reached - delay for passengers to alight
					Sleep(5000);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 1");
					LcdLine2();
					LcdMsg("Door Close");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					count = 0;
					break;

				case 2: // level 2

					// go to level 2
					LcdClear();
					Sleep(500);
					LcdLine1();
					LcdMsg("Lift moving to");
					LcdLine2();
					LcdMsg("Level 2");

					Sleep(500);
					LcdClear();

					if (key > previouslevel)
					{

						for (t = previouslevel; t < key - 1; t++)
						{

							previouslevel++;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest, "C:\\images\\l%dm.BMP", (int)previouslevel);

							sprintf(jTest2, "C:\\images\\l%dm2.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							EcsDrawBMP(jTest, pScrMgr);
							Sleep(200);
							EcsDrawBMP(jTest2, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
						}

						previouslevel = 2;
					}
					else
					{

						for (t = previouslevel; t > key; t--)
						{

							previouslevel--;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest3, "C:\\images\\l%dd.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							Sleep(200);
							EcsDrawBMP(jTest3, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
						}
						previouslevel = 2;
					}

					Sleep(250);

					// level reached - display GUI
					EcsDrawBMP(l2, pScrMgr);

					// level reached - play music
					EcsDrawBMP(l2, pScrMgr);
					ResumeThread(hThread_music);
					LcdClear();
					LcdLine1();
					LcdMsg("Level 2");
					LcdLine2();
					LcdMsg("Floor reached!");
					Sleep(250);
					SuspendThread(hThread_music);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 2");
					LcdLine2();
					LcdMsg("Door Open");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					// level reached - delay for passengers to alight
					Sleep(5000);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 2");
					LcdLine2();
					LcdMsg("Door Close");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					count = 0;
					break;

				case 3: // level 3

					// go to level 3
					LcdClear();
					Sleep(250);
					LcdLine1();
					LcdMsg("Lift moving to");
					LcdLine2();
					LcdMsg("Level 3");
					Sleep(250);
					LcdClear();

					if (key > previouslevel)
					{

						for (t = previouslevel; t < key - 1; t++)
						{

							previouslevel++;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest, "C:\\images\\l%dm.BMP", (int)previouslevel);

							sprintf(jTest2, "C:\\images\\l%dm2.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							EcsDrawBMP(jTest, pScrMgr);
							Sleep(200);
							EcsDrawBMP(jTest2, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
						}

						previouslevel = 3;
					}
					else
					{

						for (t = previouslevel; t > key; t--)
						{

							previouslevel--;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest3, "C:\\images\\l%dd.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							Sleep(200);
							EcsDrawBMP(jTest3, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
							// LcdMsg("    ");
						}
						previouslevel = 3;
					}

					Sleep(3000);

					// level reached - play music
					EcsDrawBMP(l3, pScrMgr);
					ResumeThread(hThread_music);
					LcdClear();
					LcdLine1();
					LcdMsg("Level 3");
					LcdLine2();
					LcdMsg("Floor reached!");
					Sleep(250);
					SuspendThread(hThread_music);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 3");
					LcdLine2();
					LcdMsg("Door Open");
					ResumeThread(hThread_sm);
					Sleep(250);
					SuspendThread(hThread_sm);

					// level reached - delay for passengers to alight
					Sleep(5000);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 3");
					LcdLine2();
					LcdMsg("Door Close");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					count = 0;
					break;

				case 4: // level 4

					// go to level 4
					LcdClear();
					Sleep(1000);
					LcdLine1();
					LcdMsg("Lift moving to");
					LcdLine2();
					LcdMsg("Level 4");
					Sleep(1000);
					LcdClear();

					if (key > previouslevel)
					{

						for (t = previouslevel; t < key - 1; t++)
						{

							previouslevel++;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest, "C:\\images\\l%dm.BMP", (int)previouslevel);

							sprintf(jTest2, "C:\\images\\l%dm2.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							EcsDrawBMP(jTest, pScrMgr);
							Sleep(200);
							EcsDrawBMP(jTest2, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
						}

						previouslevel = 4;
					}
					else
					{

						for (t = previouslevel; t > key; t--)
						{

							previouslevel--;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest3, "C:\\images\\l%dd.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							Sleep(200);
							EcsDrawBMP(jTest3, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
							// LcdMsg("    ");
						}
						previouslevel = 4;
					}

					Sleep(3000);

					// level reached - play music
					EcsDrawBMP(l4, pScrMgr);
					ResumeThread(hThread_music);

					LcdClear();
					LcdLine1();
					LcdMsg("Level 4");
					LcdLine2();
					LcdMsg("Floor reached!");
					Sleep(1000);
					SuspendThread(hThread_music);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 4");
					LcdLine2();
					LcdMsg("Door Open");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					// level reached - delay for passengers to alight
					Sleep(5000);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 4");
					LcdLine2();
					LcdMsg("Door Close");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					count = 0;
					break;

				case 5: // level 5

					// go to level 5
					LcdClear();
					Sleep(1000);
					LcdLine1();
					LcdMsg("Lift moving to");
					LcdLine2();
					LcdMsg("Level 5");
					Sleep(1000);
					LcdClear();

					if (key > previouslevel)
					{

						for (t = previouslevel; t < key - 1; t++)
						{

							previouslevel++;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest, "C:\\images\\l%dm.BMP", (int)previouslevel);

							sprintf(jTest2, "C:\\images\\l%dm2.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							EcsDrawBMP(jTest, pScrMgr);
							Sleep(200);
							EcsDrawBMP(jTest2, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
						}

						previouslevel = 5;
					}
					else
					{

						for (t = previouslevel; t > key; t--)
						{

							previouslevel--;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest3, "C:\\images\\l%dd.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							Sleep(200);
							EcsDrawBMP(jTest3, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
							// LcdMsg("    ");
						}
						previouslevel = 5;
					}

					Sleep(3000);

					// level reached - play music
					EcsDrawBMP(l5, pScrMgr);
					ResumeThread(hThread_music);

					LcdClear();
					LcdLine1();
					LcdMsg("Level 5");
					LcdLine2();
					LcdMsg("Floor reached!");
					Sleep(1000);
					SuspendThread(hThread_music);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 5");
					LcdLine2();
					LcdMsg("Door Open");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					// level reached - delay for passengers to alight
					Sleep(5000);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 5");
					LcdLine2();
					LcdMsg("Door Close");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					count = 0;
					break;

				case 6: // level 6

					// go to level 6
					LcdClear();
					Sleep(1000);
					LcdLine1();
					LcdMsg("Lift moving to");
					LcdLine2();
					LcdMsg("Level 6");
					Sleep(1000);
					LcdClear();

					if (key > previouslevel)
					{

						for (t = previouslevel; t < key - 1; t++)
						{

							previouslevel++;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest, "C:\\images\\l%dm.BMP", (int)previouslevel);

							sprintf(jTest2, "C:\\images\\l%dm2.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							EcsDrawBMP(jTest, pScrMgr);
							Sleep(200);
							EcsDrawBMP(jTest2, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
						}

						previouslevel = 6;
					}
					else
					{

						for (t = previouslevel; t > key; t--)
						{

							previouslevel--;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest3, "C:\\images\\l%dd.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							Sleep(200);
							EcsDrawBMP(jTest3, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
							// LcdMsg("    ");
						}
						previouslevel = 6;
					}

					Sleep(3000);

					// level reached - play music
					EcsDrawBMP(l6, pScrMgr);
					ResumeThread(hThread_music);
					LcdClear();
					LcdLine1();
					LcdMsg("Level 6");
					LcdLine2();
					LcdMsg("Floor reached!");
					Sleep(1000);
					SuspendThread(hThread_music);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 6");
					LcdLine2();
					LcdMsg("Door Open");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					// level reached - delay for passengers to alight
					Sleep(5000);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 6");
					LcdLine2();
					LcdMsg("Door Close");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					count = 0;
					break;

				case 7: // level 7

					// go to level 7
					LcdClear();
					Sleep(1000);
					LcdLine1();
					LcdMsg("Lift moving to");
					LcdLine2();
					LcdMsg("Level 7");
					Sleep(1000);
					LcdClear();

					if (key > previouslevel)
					{

						for (t = previouslevel; t < key - 1; t++)
						{

							previouslevel++;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest, "C:\\images\\l%dm.BMP", (int)previouslevel);

							sprintf(jTest2, "C:\\images\\l%dm2.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							EcsDrawBMP(jTest, pScrMgr);
							Sleep(200);
							EcsDrawBMP(jTest2, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
						}

						previouslevel = 7;
					}
					else
					{

						for (t = previouslevel; t > key; t--)
						{

							previouslevel--;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest3, "C:\\images\\l%dd.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							Sleep(200);
							EcsDrawBMP(jTest3, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
							// LcdMsg("    ");
						}
						previouslevel = 7;
					}

					Sleep(3000);

					// level reached - play music
					EcsDrawBMP(l7, pScrMgr);
					ResumeThread(hThread_music);
					LcdClear();
					LcdLine1();
					LcdMsg("Level 7");
					LcdLine2();
					LcdMsg("Floor reached!");
					Sleep(1000);
					SuspendThread(hThread_music);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 7");
					LcdLine2();
					LcdMsg("Door Open");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					// level reached - delay for passengers to alight
					Sleep(5000);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 7");
					LcdLine2();
					LcdMsg("Door Close");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					count = 0;
					break;

				case 8: // level 8

					// go to level 8
					LcdClear();
					Sleep(1000);
					LcdLine1();
					LcdMsg("Lift moving to");
					LcdLine2();
					LcdMsg("Level 8");
					Sleep(1000);
					LcdClear();

					if (key > previouslevel)
					{

						for (t = previouslevel; t < key - 1; t++)
						{

							previouslevel++;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest, "C:\\images\\l%dm.BMP", (int)previouslevel);

							sprintf(jTest2, "C:\\images\\l%dm2.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							EcsDrawBMP(jTest, pScrMgr);
							Sleep(200);
							EcsDrawBMP(jTest2, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
						}

						previouslevel = 8;
					}
					else
					{

						for (t = previouslevel; t > key; t--)
						{

							previouslevel--;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest3, "C:\\images\\l%dd.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							Sleep(200);
							EcsDrawBMP(jTest3, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
							// LcdMsg("    ");
						}
						previouslevel = 8;
					}

					Sleep(3000);

					// level reached - play music
					EcsDrawBMP(l8, pScrMgr);
					ResumeThread(hThread_music);
					LcdClear();
					LcdLine1();
					LcdMsg("Level 8");
					LcdLine2();
					LcdMsg("Floor reached!");
					Sleep(1000);
					SuspendThread(hThread_music);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 8");
					LcdLine2();
					LcdMsg("Door Open");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					// level reached - delay for passengers to alight
					Sleep(5000);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 8");
					LcdLine2();
					LcdMsg("Door Close");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					count = 0;
					break;

				case 9: // level 9

					// go to level 9
					LcdClear();
					Sleep(1000);
					LcdLine1();
					LcdMsg("Lift moving to");
					LcdLine2();
					LcdMsg("Level 9");
					Sleep(1000);
					LcdClear();

					if (key > previouslevel)
					{

						for (t = previouslevel; t < key - 1; t++)
						{

							previouslevel++;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest, "C:\\images\\l%dm.BMP", (int)previouslevel);

							sprintf(jTest2, "C:\\images\\l%dm2.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							EcsDrawBMP(jTest, pScrMgr);
							Sleep(200);
							EcsDrawBMP(jTest2, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
						}

						previouslevel = 9;
					}
					else
					{

						for (t = previouslevel; t > key; t--)
						{

							previouslevel--;

							LcdLine1();

							LcdMsg("Level ");

							sprintf(jTest3, "C:\\images\\l%dd.BMP", (int)previouslevel);

							itoa((int)previouslevel, s, 16);

							Sleep(200);
							EcsDrawBMP(jTest3, pScrMgr);

							LcdMsg(s);
							Spin(CW, 200, 1);
							// LcdMsg("    ");
						}
						previouslevel = 9;
					}

					Sleep(3000);

					// level reached - play music
					EcsDrawBMP(l9, pScrMgr);
					ResumeThread(hThread_music);
					LcdClear();
					LcdLine1();
					LcdMsg("Level 9");
					LcdLine2();
					LcdMsg("Floor reached!");
					Sleep(1000);
					SuspendThread(hThread_music);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 9");
					LcdLine2();
					LcdMsg("Door Open");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					// level reached - delay for passengers to alight
					Sleep(5000);

					// level reached - activate motor for door openinng
					LcdClear();
					LcdLine1();
					LcdMsg("Level 9");
					LcdLine2();
					LcdMsg("Door Close");
					ResumeThread(hThread_sm);
					Sleep(2000);
					SuspendThread(hThread_sm);

					count = 0;
					break;

				case 10: // door control
					ResumeThread(hThread_sm);
					LcdClear();
					LcdLine1();
					LcdMsg("Door Opening");
					LcdLine2();
					LcdMsg("                ");
					Sleep(2000);
					SuspendThread(hThread_sm);

					count = 0;

					break;

				case 11: // door control
					ResumeThread(hThread_sm);
					LcdClear();
					LcdLine1();
					LcdMsg("Door Closing");
					LcdLine2();
					LcdMsg("                ");
					Sleep(2000);
					SuspendThread(hThread_sm);

					count = 0;

					break;
				}
				key2 = 0xFF;
			}
		}

		if (count >= 3000)
		{

			count = 0;
			printf("Return to basement");

			LcdClear();
			LcdLine1();
			LcdMsg("Lift moving to");
			LcdLine2();
			LcdMsg("Basement");
			Sleep(1000);
			LcdClear();

			for (t = previouslevel; t > 0; t--)
			{

				previouslevel--;
				LcdLine1();
				LcdMsg("Level ");
				Spin(CCW, 200, 1);
				sprintf(jTest3, "C:\\images\\l%dd.BMP", (int)previouslevel);
				itoa((int)previouslevel, s, 16);
				Sleep(500);
				EcsDrawBMP(jTest3, pScrMgr);

				LcdMsg(s);
				LcdMsg("     ");
			}
			Sleep(1000);

			LcdClear();
			EcsDrawBMP(lb, pScrMgr);
			LcdLine1();
			LcdMsg("    Basement    ");
			LcdLine2();
			LcdMsg("                ");
			previouslevel = 0;
			Sleep(1000);
		}

		LcdClear();
		LcdLine1();
		LcdMsg("The Canopy");
		LcdLine2();
		LcdMsg("Press a key ...");
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

unsigned int __stdcall sm_thread(void *pArguments)
{
	while (1)
	{
		Spin(CW, 100, 10);  // turn motor clockwise, 100 steps
		Spin(CCW, 100, 10); // turn motor counterclockwise, 100 steps
	}
	return (0);
}

unsigned int __stdcall music_thread(void *pArguments)
{

	while (TRUE)
	{
		PlaySong((const char *)POLKA);
		Sleep(500);
	}
	return (0);
}
