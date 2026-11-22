/*
**	flSynclient (c) 2006 Matteo Lucarelli <matteo@matteolucarelli.net>
**	See the file LICENSE included in this package for license terms.
**
**	This program is free software; you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation; either version 2 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program; if not, write to:
**
**		Free Software Foundation, Inc.
**		59 Temple Place - Suite 330
**		Boston, MA 02111-1307
**		USA
** 150930 robwoj44 internationalized
*/

#define PROGVERS "0.6"
#define AUTHORINFO "(c)2006 Matteo Lucarelli"
#define PROGNAME "flsynclient"

#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <FL/filename.H>
#include <FL/fl_draw.H>
#include <FL/fl_message.H>

#include "UImain.h"

bool verbose=false;
int m_pid=0;

void print_usage (int exit_code)
{
	printf (_("Usage: %s [OPTIONS] ....\n"),PROGNAME);
	printf (_("  -h  --help        Display this usage information.\n"
		"  -V  --version     Display version informations.\n"
		"  -v  --verbose     Print what's going on\n"
		"  -s  --set         Set pad reading ~/.flSynclient and exit\n"));
	exit (exit_code);
}

int  parseline(char *line, char **argv, int maxarg)
{
	int argc=0;
	while (*line!=0 && argc<maxarg) {      
		while (*line==' ' || *line=='\t' || *line =='\n') *line++=0;     
		if (*line==0) break;
		*argv++ = line;
		argc++;
		while (*line!=0 && *line!=' ' && *line!='\t' && *line!='\n') line++;             
	}
	//*argv = 0;
	return argc;
}

void synclient(char* field, double value)
{
	char tmp[1024];
	
	if (verbose){
		snprintf(tmp,1024,"synclient %s=%f",field,value);
		printf(_("Executing: %s\n"),tmp);
	}else snprintf(tmp,1024,"synclient %s=%f >/dev/null 2>&1",field,value);

	system(tmp);
}

void parsesynclientoutput(FILE* fp,bool onlyset)
{
	char line[1024];
	char* argv[3];
	
	// first line must be "Parameters settings"
	if (fgets(line,1024,fp)==NULL) return;
	if (strstr(line,"settings")==NULL){
		fprintf(stderr,"%s",line);
		fl_alert("%s",line);
		exit(1);
	}
	
	while (fgets(line,1024,fp)){

		if (parseline(line,argv,3)==3){
		
			synclient(argv[0],atof(argv[2]));
			if (onlyset) continue;
		
			if (!strcmp(argv[0],"LeftEdge")){
				LeftEdge->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"RightEdge")){
				RightEdge->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"TopEdge")){
				TopEdge->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"BottomEdge")){
				BottomEdge->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"FingerLow")){
				FingerLowHigh->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"MaxTapTime")){
				MaxTapTime->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"MaxTapMove")){
				MaxTapMove->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"MaxDoubleTapTime")){
				MaxDoubleTapTime->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"ClickTime")){
				ClickTime->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"EmulateMidButtonTime")){
				EmulateMidButtonTime->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"VertScrollDelta")){
				VertScrollDelta->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"HorizScrollDelta")){
				HorizScrollDelta->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"MinSpeed")){
				MinSpeed->value(atof(argv[2]));
			}else if (!strcmp(argv[0],"MaxSpeed")){
				MaxSpeed->value(atof(argv[2]));
			}else if (!strcmp(argv[0],"AccelFactor")){
				AccelFactor->value(atof(argv[2]));
			}else if (!strcmp(argv[0],"EdgeMotionMinZ")){
				EdgeMotionMinMaxZ->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"EdgeMotionMinSpeed")){
				EdgeMotionMinSpeed->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"EdgeMotionMaxSpeed")){
				EdgeMotionMaxSpeed->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"UpDownScrolling")){
				UpDownScrolling->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"LeftRightScrolling")){
				LeftRightScrolling->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"TouchpadOff")){
				TouchpadOff->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"GuestMouseOff")){
				GuestMouseOff->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"RTCornerButton")){
				RTCornerButton->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"RBCornerButton")){
				RBCornerButton->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"LTCornerButton")){
				LTCornerButton->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"LBCornerButton")){
				LBCornerButton->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"TapButton1")){
				TapButton1->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"TapButton2")){
				TapButton2->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"TapButton3")){
				TapButton3->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"CircularScrolling")){
				CircularScrolling->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"CircScrollDelta")){
				CircScrollDelta->value(atof(argv[2]));
			}else if (!strcmp(argv[0],"CircScrollTrigger")){
				CircScrollTrigger->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"CircularPad")){
				CircularPad->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"PalmDetect")){
				PalmDetect->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"CornerCoasting")){
				CornerCoasting->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"VertTwoFingerScroll")){
				VertTwoScrolling->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"HorizTwoFingerScroll")){
				HorizTwoScrolling->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"FastTaps")){
				FastTaps->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"LockedDrags")){
				LockedDrags->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"LockedDragTimeout")){
				LockedDragTimeout->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"CoastingSpeed")){
				CoastingSpeed->value(atof(argv[2]));
			}else if (!strcmp(argv[0],"HorizEdgeScroll")){
				HorizEdgeScroll->value(atoi(argv[2]));
			}else if (!strcmp(argv[0],"VertEdgeScroll")){
				VertEdgeScroll->value(atoi(argv[2]));

			}
		}
	}
}

void readsynclientoutput()
{
	if (verbose) printf(_("Reading synclient output\n"));
	int fds[2];
	pipe(fds);
	
	m_pid=fork();
	
	if (m_pid==(pid_t)0){
		close(fds[0]);
		dup2(fds[1],2);
		close(fds[1]);
		char cmd[1024];
		snprintf(cmd,1024,"(%s) 1>&2","synclient -l");
		if (verbose) printf(_("Executing: %s\n"),cmd);
		execlp("/bin/sh", "sh", "-c", cmd, 0);
	}
	close(fds[1]);
	FILE* fp=fdopen(fds[0],"r");
	parsesynclientoutput(fp,false);
	fclose(fp);
}

// edge 0:top, 1:bottom, 2:left, 3:right
void CalibrateEdge(int edge)
{
	int fds[2];
	pipe(fds);
	char tmp[1024];
		
	m_pid=fork();
	
	if (m_pid==(pid_t)0){
		close(fds[0]);
		dup2(fds[1],2);
		close(fds[1]);
		snprintf(tmp,1024,"(%s) 1>&2","synclient -m 100");
		if (verbose) printf(_("Executing: %s\n"),tmp);
		execlp("/bin/sh", "sh", "-c", tmp, 0);
	}
	
	fl_cursor(FL_CURSOR_WAIT);
	Fl::check();
	
	close(fds[1]);
	FILE* fp=fdopen(fds[0],"r");
	
	char* argv[3];
	int xmax=0;
	int xmin=100000;
	int ymax=0;
	int ymin=100000;
	fgets(tmp,1024,fp);
	for (int i=0; i<10 ; i++){
		if (fgets(tmp,1024,fp)==NULL) break;
		if (verbose) printf("%s\n",tmp);
		if (parseline(tmp,argv,3)<3) continue;
		if (atoi(argv[1])>xmax) xmax=atoi(argv[1]);
		if (atoi(argv[1])<xmin) xmin=atoi(argv[1]);
		if (atoi(argv[2])>ymax) ymax=atoi(argv[2]);
		if (atoi(argv[2])<ymin) ymin=atoi(argv[2]);
	}
	kill(m_pid,SIGTERM);
	fclose(fp);
	
	switch (edge){
		case 0: TopEdge->value(ymin);synclient("TopEdge",ymin);break;
		case 1: BottomEdge->value(ymax);synclient("BottomEdge",ymax);break;
		case 2: LeftEdge->value(xmin);synclient("LeftEdge",xmin);break;
		case 3: RightEdge->value(xmax);synclient("RightEdge",xmax);break;
	}
	
	fl_cursor(FL_CURSOR_DEFAULT);
	Fl::check();
}

void SaveSettings()
{
	if (verbose) printf(_("Saving settings in ~/.flSynclient\n"));
	system("synclient -l >~/.flSynclient");
}

void RevertSettings(bool onlyset)
{
	char tmp[1024];
	
	fl_cursor(FL_CURSOR_WAIT);
	Fl::check();
	
	if (verbose) printf(_("Reading settings from ~/.flSynclient\n"));
	
	fl_filename_expand(tmp,1024,"~/.flSynclient");
	FILE* fp=fopen(tmp,"r");

	if (fp==NULL) return;
	
	parsesynclientoutput(fp,onlyset);
	
	fclose(fp);
	fl_cursor(FL_CURSOR_DEFAULT);
	Fl::check();
}
	
void sighandler(int sig)
{
	if (sig==SIGCHLD)
		// comes from mixer
		if ((m_pid!=0)&&(waitpid(m_pid,NULL,WNOHANG)!=0)){
			if (verbose) printf(_("SIGCHLD from synclient\n"));
			m_pid=0;
		}
}

int main (int argc, char* argv[])
{
	int next_option;
	const char* const short_options = "hVvs";
	const struct option long_options[] = {
	{ "help",     0, NULL, 'h' },
	{ "version",  0, NULL, 'V' },
	{ "verbose",  0, NULL, 'v' },
	{ "set",      0, NULL, 's' },
	{ NULL,       0, NULL, 0   } 
	};

	do {
		next_option = getopt_long (argc, argv, short_options,long_options, NULL);
		switch (next_option)
		{
			case 'v':
				verbose=true;
				break;
			case 's':
				RevertSettings(true);
				exit(0);
				break;
			case 'h':
				print_usage(0);
				break;
			case 'V':
				printf ("%s %s %s\n",PROGNAME,PROGVERS,AUTHORINFO);
				exit(0);
				break;
			case '?':
				print_usage (1);
				break;
		}
	}
	while (next_option != -1);
	make_window();
	
	signal(SIGCHLD,sighandler);
	
	readsynclientoutput();
	Fl::run();

	return 0;
}
