/*
title:  KLATT.C
author: Jon Iles (j.p.iles@cs.bham.ac.uk)
date: 20/4/94
version: 3.03
notes:  

This file contains C code to provide a simple interface to
Dennis Klatt's parwave function. This function, as the name
suggests, converts a frame of parameters into a waveform.
The parwave function itself is a translation of the Dennis's
original Fortran code, as published in JASA. The code was
posted to comp.speech in 1993, and has been updated by me
to fix a number of bugs that had been introduced. Subsequently
major rewrites have been done by Nick Ing-Simmons to improve 
efficiency and change the code into a more acceptable ANSI C style, 
and by me to remove all global variable references, fix bugs and ensure
portability.

See the README file and man page for more details.

(c) 1993 Jon Iles and Nick Ing-Simmons

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 1, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "proto.h"
#include "parwave.h"
#include "getopt.h"

#ifdef _MSC_VER
#define _DOS
#endif

#ifdef __BORLANDC__
#define _DOS
#endif

/* for default sampled glottal excitation waveform */

#define NUMBER_OF_SAMPLES 100
#define SAMPLE_FACTOR 0.00001

/* function prototypes */

static void usage PROTO((void));


/*
function USAGE

Displays the command line options.
*/

static void usage()

{
  printf("Options...\n");
  printf("-h Displays this message\n");
  printf("-i <infile> sets input filename\n");
  printf("-o <outfile> sets output filename\n");
  printf("   If output filename not specified, stdout is used\n");
  printf("-q quiet - print no messages\n");
  printf("-t <n> select output waveform\n");
  printf("-c select cascade-parallel configuration\n");
  printf("   Parallel configuration is default\n");
  printf("-n <number> Number of formants in cascade branch.\n");
  printf("   Default is 5\n");
  printf("-s <n> set sample rate\n");
  printf("-f <n> set number of milliseconds per frame, default 10\n");
  printf("-v <n> Specifies voicing source.\n");
  printf("   1=impulse train, 2=natural simulation, 3=sampled natural\n");
  printf("   Default is a simulation of natural voicing\n");
  printf("-V <filename> Input file of samples for natural voicing.\n");
  printf("-F <percent> percentage of f0 flutter\n");
  printf("    Default is 0\n");
  printf("-r <type> output 16 bit signed integers rather than ASCII\n");
  printf("   integers. Type = 1 gives high byte first, Type = 2 gives\n");
  printf("   low byte first.\n");
}


void main(int argc,char **argv)


{
  extern char *optarg;
  char c;
  char infile[80];
  char outfile[80];
  FILE *infp;
  FILE *outfp;
  int result;
  flag done_flag;
  long value;
  int *iwave;
  int isam;
  int icount;
  int par_count;   
  int nmspf_def;
  klatt_global_ptr globals;
  klatt_frame_ptr frame;
  long *frame_ptr;
  unsigned char high_byte;
  unsigned char low_byte;
  flag raw_flag;
  flag raw_type;
  char samples_file[80];
  int loop;

  static int natural_samples[NUMBER_OF_SAMPLES]=
  {
    -310,-400,530,356,224,89,23,-10,-58,-16,461,599,536,701,770,
    605,497,461,560,404,110,224,131,104,-97,155,278,-154,-1165,
    -598,737,125,-592,41,11,-247,-10,65,92,80,-304,71,167,-1,122,
    233,161,-43,278,479,485,407,266,650,134,80,236,68,260,269,179,
    53,140,275,293,296,104,257,152,311,182,263,245,125,314,140,44,
    203,230,-235,-286,23,107,92,-91,38,464,443,176,98,-784,-2449,
    -1891,-1045,-1600,-1462,-1384,-1261,-949,-730
  };


  if(argc==1)
  {
    usage();
    exit(1);
  }

  /* set up default values */

  strcpy(infile,"");
  strcpy(outfile,"");
  strcpy(samples_file,"");

  iwave = (int*) malloc(sizeof(int)*MAX_SAM);
  if(iwave==NULL)
  {
	perror("malloc failed");
        exit(1);
  }

  globals = (klatt_global_ptr)malloc(sizeof(klatt_global_t));
  if(globals==NULL)
  {
    perror("malloc failed");
    exit(1);
  }

  frame = (klatt_frame_ptr)malloc(sizeof(klatt_frame_t));
  if(frame==NULL)
  {
	perror("malloc failed");
	exit(1);
  }

  globals->quiet_flag = FALSE;
  globals->synthesis_model = ALL_PARALLEL;
  globals->samrate = 10000;
  globals->glsource = NATURAL;
  globals->natural_samples = natural_samples;
  globals->num_samples = NUMBER_OF_SAMPLES;
  globals->sample_factor = (float) SAMPLE_FACTOR;
  nmspf_def = 10;
  globals->nfcascade = 0;
  globals->outsl = 0;
  globals->f0_flutter = 0;
  raw_flag = FALSE;

  while((c = getopt(argc,argv,"i:o:t:s:f:n:F:v:V:qchr:"))!=EOF)
  {
    switch(c)
    {
    case 'i':
      strcpy(infile,optarg);
      break;
    case 'o':
      strcpy(outfile,optarg);
      break;
    case 'q':
      globals->quiet_flag = TRUE;
      break;
    case 't':
      globals->outsl = (flag) atoi(optarg);
      break;
    case 'c':
      globals->synthesis_model = CASCADE_PARALLEL;
      globals->nfcascade = 5;
      break;
    case 's':
      globals->samrate = atoi(optarg);
      break;
    case 'f':
      nmspf_def = atoi(optarg);
      break;
    case 'v':
      globals->glsource = (flag) atoi(optarg);
      break;
    case 'V':
      strcpy(samples_file,optarg);
      break;
    case 'h':
      usage();
      exit(1);
      break;
    case 'n':
      globals->nfcascade = atoi(optarg);
      break;
    case 'F':
      globals->f0_flutter = atoi(optarg);
      break;
    case 'r':
      raw_flag = TRUE;
      raw_type = (flag) atoi(optarg);
      break;
    }
  }

  globals->nspfr = (globals->samrate * nmspf_def) / 1000;

  if(strcmp(samples_file,"")!=0)
  {
    infp = fopen(samples_file,"r");

    if(infp==NULL)
    {
      perror("Can't open voicing samples file");
      exit(1);
    }

    fscanf(infp,"%i",&(globals->num_samples));
    fscanf(infp,"%f",&(globals->sample_factor));


    globals->natural_samples = (int*) malloc(sizeof(int)*globals->num_samples);
    if(globals->natural_samples==NULL)
    {
      perror("malloc failed for natural samples");
      exit(1);
    }

    for(loop=0;loop<globals->num_samples;loop++)
    {
      fscanf(infp,"%i",&(globals->natural_samples[loop]));
    }

    fclose(infp);
  }


  if(strcmp(infile,"")==0)
  {
    infp=stdin;
  }
  else
  {
    infp = fopen(infile,"r");
    if(infp==NULL)
    {
      perror("can't open input parameter file");
      exit(1);
    }
  }

  if(strcmp(outfile,"")==0)
  {
    outfp = stdout;
    globals->quiet_flag = TRUE;
  }
  else
  {
#ifdef _DOS
    if(raw_flag==TRUE)
    {
       outfp = fopen(outfile,"wb");
    }
    else
    {
       outfp = fopen(outfile,"w");
    }
#else
    outfp = fopen(outfile,"w");
#endif

    if(outfp==NULL)
    {
      perror("can't open output file");
      exit(1);
    }
  }

  icount=0;
  done_flag = FALSE;
  parwave_init(globals);
  frame_ptr = (long*) frame;

  while(done_flag == FALSE)
  {
    for (par_count = 0; par_count < NPAR; ++par_count)
    {
      value = 0;

#ifdef __BORLANDC__
      result = fscanf(infp,"%ld",&value);
#else
      result = fscanf(infp,"%i",(int*)&value);
#endif

      frame_ptr[par_count] = value;
    }
    
    if(result == EOF)
    {
      done_flag = TRUE;
    }
    else
    {
      parwave(globals,frame,iwave);

      if(globals->quiet_flag == FALSE)
      {
	printf("\rFrame %i",icount);
	fflush(stdout);
      }

      for (isam = 0; isam < globals->nspfr; ++ isam)
      { 
	if(raw_flag == TRUE)
	{
	  low_byte = iwave[isam] & 0xff;
	  high_byte = iwave[isam] >> 8;

	  if(raw_type==1)
	  {
	    fprintf(outfp,"%c%c",high_byte,low_byte);
	  }
	  else
	  {
	    fprintf(outfp,"%c%c",low_byte,high_byte);
	  }
	}
	else
	{
	  fprintf(outfp,"%i\n",iwave[isam]);
	}
      }
      icount++;
    }
  }

  if(strcmp(infile,"")!=0)
  {
    fclose(infp);
  }

  if(strcmp(outfile,"")!=0)
  {
    fclose(outfp);
  }

  if(globals->quiet_flag == FALSE)
  {
    printf("\nDone\n");
  }
}
