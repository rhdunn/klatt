Klatt Cascade-Parallel Formant Synthesizer v 3.03 (April 1994)
--------------------------------------------------------------

Jon Iles           j.p.iles@cs.bham.ac.uk
Nick Ing-Simmons   nicki@lobby.ti.com

History
-------

This file contains a version of the Klatt Cascade-Parallel Formant
Speech Synthesizer. The software for this synthesizer was originally
described in (1) and an updated version of the software
was described in (2). The most recent version of the software
synthesizer as described in (2) is commercially available from
Sensimetrics Inc. (3)

The code contained within this directory is a translation of the
original Fortran, into C, by Dennis Klatt. In terms of the two
articles referred to above, this version seems to be the mid point of the
development between the two systems described.


Modifications
-------------

The main part of the code in this directory was posted to comp.speech
in early 1993 as part of a crude text to speech conversion system. The
code taken from comp.speech seemed to have been modified considerably
from the original, and for use of the synthesizer in research it was
necessary to "fix" the changes that had been made. The major changes
that have been made are:

1. Re-introduced the parallel-only / cascade-parallel switch. This
allows choice of synthesis method, either using both branches, or just
using the parallel branch.

2. Correct use of bandwidth parameters. One of the cascade bandwidth
parameters was being wrongly used in the parallel branch of the
synthesizer.

3. Modified operation of natural voicing source. The amplitude of the
natural voicing source was very much smaller than the amplitude of the
impulse source, making it difficult to swap between them to evaluate
the differences.

4. Removed the software synthesizer from the context of a text to
speech system. The synthesizer is now a stand-alone program, accepting
input as a set of parameters from a file, and allowing output to a
file or to stdout.

5. Increased the number of parameters available for use in the input
file. The original comp.speech software made assumptions about a
number of the control parameters. To provide the greatest flexibility,
these parameters have been made specific in the input file. It is
important to note that the input file format is NOT compatible with
that used by the software originally posted to the comp.speech news group.

6. Added command line options to control the parameters that remain
constant during synthesis.

7. Added F0 flutter control, as described in (2).

8. Subsequently the code in parwave was re-written by Nick to improve
efficiency, and add a more acceptable ANSI style, and generally make
an elegant implementation.

9. Further re-writes have been carried out to remove all global references.
All parameters are passed around in structures.

10. The facility to use a sampled natural excitation waveform has been 
implemented. Naturalness of the resulting synthetic speech can be greatly 
improved by using the glottal excitation waveform from a natural speaker,
especially if it is the speaker on whose voice the synthesis is actually
based. This may be obtained indirectly by inverse-filtering a vowel.

11. This synthesizer appears in modified form as part of Nick's
rsynth text-to-speech system. This may be found at svr-ftp.eng.cam.ac.uk
in comp.speech/sources.

12. Fixed bug to the antiresonator code that caused overflow problems
when compiling on a PC

13. Various minor modifications to ensure correct compilation using
Microsoft C 7.0 (tested) and Borland C (untested). 

14. Modified random number generation for noise production as
previously it was dependent on the size of the "long" type.

Input File Format
-----------------

The input file consists of a series of parameter frames. Each frame of
parameters (usually) represents 10ms of audio output, although this
figure can be adjusted down to 1ms per frame. The parameters in each
frame are described below. To avoid confusion, note that the cascade
and parallel branch of the synthesizer duplicate some of the control
parameters. 

f0	This is the fundamental frequency (pitch) of the utterance
	in this case it is specified in steps of 0.1 Hz, hence 100Hz
	will be represented by a value of 1000.

av    	Amplitude of voicing for the cascade branch of the
	synthesizer in dB0. Range 0-70, value usually 60 for a vowel sound.

f1    	First formant frequency in 200-1300 Hz.

b1    	Cascade branch bandwidth of first formant in the range 40-1000 Hz. 

f2     	Second formant frequency in the range 550 - 3000 Hz.	

b2      Cascade branch bandwidth of second  formant in the range 40-1000 Hz. 

f3      Third formant frequency in the range 1200-4999 Hz.

b3      Cascade branch bandwidth of third formant in the range 40-1000 Hz. 

f4      Fourth formant frequency in 1200-4999 Hz.

b4      Cascade branch bandwidth of fourth formant in the range 40-1000 Hz. 

f5      Fifth formant frequency in the range 1200-4999 Hz.

b5      Cascade branch bandwidth of fifth formant in the range 40-1000 Hz. 

f6      Sixth formant frequency in the range 1200-4999 Hz.

b6      Cascade branch bandwidth of sixth formant in the range 40-2000 Hz. 

fnz  	Frequency of the nasal zero in the range 248-528 Hz.
	(cascade branch only) 

bnz   	Bandwidth of the nasal zero in the range 40-1000 Hz 
	(cascade branch only)

fnp   	Frequency of the nasal pole in the range 248-528 Hz 

bnp   	Bandwidth of the nasal pole in the range 40-1000 Hz 

asp    	Amplitude of aspiration 0-70 dB.

kopen 	Open quotient of voicing waveform, range 0-60, usually 30.
	Will influence the gravelly or smooth quality of the voice.
	Only works with impulse and antural simulations. For the
	sampled glottal excitation waveform the open quotient is fixed.

aturb 	Amplitude of turbulence 0-80 dB. A value of 40 is useful. Can be
	used to simulate "breathy" voice quality.

tilt  	Spectral tilt in dB, range 0-24. Tilts down the output spectrum.
	The value refers to dB down at 3Khz. Increasing the value emphasizes
	the low frequency content of the speech and attenuates the high
	frequency content.

af    	Amplitude of frication in dB, range 0-80 (parallel branch)

skew  	Spectral Skew - skewness of alternate periods, range 0-40

a1    	Amplitude of first formant in the parallel branch, in 0-80 dB.

b1p  	Bandwidth of the first formant in the parallel branch, in Hz.

a2    	Amplitude of parallel branch second formant.

b2p   	Bandwidth of parallel branch second formant.

a3    	Amplitude of parallel branch third formant.

b3p	Bandwidth of parallel branch third formant.

a4    	Amplitude of parallel branch fourth formant.

b4p   	Bandwidth of parallel branch fourth formant.

a5	Amplitude of parallel branch fifth formant.

b5p   	Bandwidth of parallel branch fifth formant.

a6	Amplitude of parallel branch sixth formant.

b6p   	Bandwidth of parallel branch sixth formant.

anp   	Amplitude of the parallel branch nasal formant.

ab    	Amplitude of bypass frication in dB. 0-80.

avp	Amplitude of voicing for the parallel branch, 0-70 dB.

gain  	Overall gain in dB range 0-80.



Command Line Options
--------------------

-h Displays a help message.

-i <filename> sets input filename.

-o <outfile> sets output filename. 
   If output filename not specified, stdout is used.

-q quiet - print no messages.

-t <n> select output waveform (RTFC !)

-c select cascade-parallel configuration.
   Parallel only configuration is default.

-n <number> Number of formants in cascade branch.
   Default is 5.

-s <n> set sample rate
   Default is 10Khz.

-f <n> set number of milliseconds per frame.
   Default is 10ms per frame

-v <n> Specifies that the voicing source to be used.
   1 = impulse train.
   2 = natural simulation.
   3 = natural samples.
   Default is natural voicing

-V <filename> Specifies the filename for a sampled natural excitation
   waveform. See man page for format details.

-r <n> Output raw binary samples, rather than ASCII integer samples.
   1 = high byte, low byte arrangement.
   2 = low byte, high byte arrangement.

-F <percent> percentage of f0 flutter
   Default is 0


Example Parameter File
----------------------

Some example parameter files for a short segments of speech are included in
this distribution. e.g. file called example1.par. Use the following
to produce the output waveforms:

	klatt -i example1.par -o example1.dat -f 5 -v 2
	klatt -i example2.par -o example2.dat -f 5 -s 16000 -v 2

The '-r' option can be used to produce raw binary output, which can
then be converted to many different formats using utilities such as
'sox' (sound exchange) which are available from major ftp sites.

An example is given below of conversion to the ulaw encoded format
used by Sun Sparc SLC's

sox -r 16000 -s -w example.raw -r 8000 -b -U example.au

Beware of the byte ordering of your machine - if the above procedure
produces distored rubbish, try using -r 2 instead of -r 1. This just
reverses the byte ordering in the raw binary output file. It is also
worth noting that the above example reduces the quality of the output,
as the sampling rate is being halved and the number of bits per sample
is being halved. Ideally output should be at 16kHz with 16 bits per
sample. 


Notes
-----

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

Bug reports, comments etc. to j.p.iles@cs.bham.ac.uk


References
----------

(1) @article{klatt1980,
     AUTHOR = {Klatt,D.H.},  
     JOURNAL = {Journal of the Acoustic Society of America},  
     PAGES = {971--995},  
     TITLE = {Software for a cascade/parallel formant synthesizer},  
     VOLUME = {67},
     NUMBER = {3},
     MONTH = {March},
     YEAR =  1980}


(2) @Article{klatt1990,
  author = 	 "Klatt,D.H. and Klatt, L.C.",
  title = 	 "Analysis, synthesis and perception of voice quality
		  variations among female and male talkers.",
  journal = 	 "Journal of the Acoustical Society of America",
  year = 	 "1990",
  volume = 	 "87",
  number = 	 "2",
  pages = 	 "820--857",
  month = 	 "February"}

(3) Dr. David Williams  at

Sensimetrics Corporation,
64 Sidney Street, 
Cambridge, 
MA  02139.  
Fax: (617) 225-0470
Tel: (617) 225-2442
e-mail sensimetrics@sens.com



