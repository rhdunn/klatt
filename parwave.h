/* An implementation of a Klatt cascade-parallel formant synthesizer.
 *
 * Copyright (C) 2011 Reece H. Dunn
 * (c) 1993,94 Jon Iles and Nick Ing-Simmons
 *
 * A re-implementation in C of Dennis Klatt's Fortran code, originally by:
 *
 *     Jon Iles (j.p.iles@cs.bham.ac.uk)
 *     Nick Ing-Simmons (nicki@lobby.ti.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KLATT_PARWAVE_H
#define KLATT_PARWAVE_H

/** @brief The type of synthesis model to use.
  */
typedef enum
{
	CASCADE_PARALLEL, /* FIXME: This generates wierd audio at the end of example1.par and all through example2.par! */
	ALL_PARALLEL,
} klatt_model_t;

#define NPAR		 40        /* Number of control parameters */
#define MAX_SAM          20000     /* Maximum sample rate */
#define TRUE             1
#define FALSE            0

/** @brief The voicing source generator to use for glottal waveforms.
  */
typedef enum
{
	IMPULSIVE,
	NATURAL,
	SAMPLED,
} klatt_voicing_source_t;

typedef char flag;

/** @brief A klatt resonator.
  */
typedef struct
{
  float a;
  float b;
  float c;
  float p1; /* value at time period |n-1|. */
  float p2; /* value at time period |n-2| */
} resonator_t, *resonator_ptr;

/** @brief Parameters, global data and resonators used by the klatt synthesizer.
  */
typedef struct
{
  klatt_model_t synthesis_model; /* cascade-parallel or all-parallel */
  long samrate;     /* Number of output samples per second           */
  long FLPhz ;      /* Frequeny of glottal downsample low-pass filter */
  long BLPhz ;      /* Bandwidth of glottal downsample low-pass filter */
  long nfcascade;   /* Number of formants in cascade vocal tract    */
  klatt_voicing_source_t glsource;    /* Type of glottal source */
  int f0_flutter;   /* Percentage of f0 flutter 0-100 */
  flag quiet_flag;  /* set to TRUE for error messages */
  long nspfr;       /* number of samples per frame */
  long nper;        /* Counter for number of samples in a pitch period */
  long ns;
  long T0;          /* Fundamental period in output samples times 4 */
  long nopen;       /* Number of samples in open phase of period    */
  long nmod;        /* Position in period to begin noise amp. modul */
  long nrand;       /* Varible used by random number generator      */
  float pulse_shape_a;  /* Makes waveshape of glottal pulse when open   */
  float pulse_shape_b;  /* Makes waveshape of glottal pulse when open   */
  float onemd;
  float decay;
  float amp_bypas; /* AB converted to linear gain              */
  float amp_voice; /* AVdb converted to linear gain            */
  float par_amp_voice; /* AVpdb converted to linear gain       */
  float amp_aspir; /* AP converted to linear gain              */
  float amp_frica; /* AF converted to linear gain              */
  float amp_breth; /* ATURB converted to linear gain           */
  float amp_gain0; /* G0 converted to linear gain              */
  int num_samples; /* number of glottal samples */
  float sample_factor; /* multiplication factor for glottal samples */
  int *natural_samples; /* pointer to an array of glottal samples */
  long original_f0; /* original value of f0 not modified by flutter */

  resonator_t rnpp; /* internal storage for resonators */
  resonator_t r1p;
  resonator_t r2p;
  resonator_t r3p;
  resonator_t r4p;
  resonator_t r5p;
  resonator_t r6p;
  resonator_t r1c;
  resonator_t r2c;
  resonator_t r3c;
  resonator_t r4c;
  resonator_t r5c;
  resonator_t r6c;
  resonator_t r7c;
  resonator_t r8c;
  resonator_t rnpc;
  resonator_t rnz;
  resonator_t rgl;
  resonator_t rlp;
  resonator_t rout;
} klatt_global_t, *klatt_global_ptr;
  
/** @brief The audio characteristics of an audio frame.
  */
typedef struct
{
  long F0hz10; /* Voicing fund freq in Hz                          */        
  long AVdb;   /* Amp of voicing in dB,            0 to   70       */        
  long F1hz;   /* First formant freq in Hz,        200 to 1300     */        
  long B1hz;   /* First formant bw in Hz,          40 to 1000      */        
  long F2hz;   /* Second formant freq in Hz,       550 to 3000     */        
  long B2hz;   /* Second formant bw in Hz,         40 to 1000      */        
  long F3hz;   /* Third formant freq in Hz,        1200 to 4999    */        
  long B3hz;   /* Third formant bw in Hz,          40 to 1000      */        
  long F4hz;   /* Fourth formant freq in Hz,       1200 to 4999    */        
  long B4hz;   /* Fourth formant bw in Hz,         40 to 1000      */        
  long F5hz;   /* Fifth formant freq in Hz,        1200 to 4999    */        
  long B5hz;   /* Fifth formant bw in Hz,          40 to 1000      */        
  long F6hz;   /* Sixth formant freq in Hz,        1200 to 4999    */        
  long B6hz;   /* Sixth formant bw in Hz,          40 to 2000      */        
  long FNZhz;  /* Nasal zero freq in Hz,           248 to  528     */        
  long BNZhz;  /* Nasal zero bw in Hz,             40 to 1000      */        
  long FNPhz;  /* Nasal pole freq in Hz,           248 to  528     */        
  long BNPhz;  /* Nasal pole bw in Hz,             40 to 1000      */        
  long ASP;    /* Amp of aspiration in dB,         0 to   70       */        
  long Kopen;  /* # of samples in open period,     10 to   65      */        
  long Aturb;  /* Breathiness in voicing,          0 to   80       */        
  long TLTdb;  /* Voicing spectral tilt in dB,     0 to   24       */        
  long AF;     /* Amp of frication in dB,          0 to   80       */        
  long Kskew;  /* Skewness of alternate periods,   0 to   40 in sample#/2  */
  long A1;     /* Amp of par 1st formant in dB,    0 to   80       */        
  long B1phz;  /* Par. 1st formant bw in Hz,       40 to 1000      */        
  long A2;     /* Amp of F2 frication in dB,       0 to   80       */        
  long B2phz;  /* Par. 2nd formant bw in Hz,       40 to 1000      */        
  long A3;     /* Amp of F3 frication in dB,       0 to   80       */        
  long B3phz;  /* Par. 3rd formant bw in Hz,       40 to 1000      */        
  long A4;     /* Amp of F4 frication in dB,       0 to   80       */        
  long B4phz;  /* Par. 4th formant bw in Hz,       40 to 1000      */        
  long A5;     /* Amp of F5 frication in dB,       0 to   80       */        
  long B5phz;  /* Par. 5th formant bw in Hz,       40 to 1000      */        
  long A6;     /* Amp of F6 (same as r6pa),        0 to   80       */        
  long B6phz;  /* Par. 6th formant bw in Hz,       40 to 2000      */        
  long ANP;    /* Amp of par nasal pole in dB,     0 to   80       */        
  long AB;     /* Amp of bypass fric. in dB,       0 to   80       */        
  long AVpdb;  /* Amp of voicing,  par in dB,      0 to   70       */        
  long Gain0;  /* Overall gain, 60 dB is unity,    0 to   60       */        
 } klatt_frame_t, *klatt_frame_ptr;

void parwave(klatt_global_ptr,klatt_frame_ptr,int*);
void parwave_init(klatt_global_ptr);

#endif
