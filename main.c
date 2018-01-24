/*
** The 303 Interface,  and they said that it couldn't be done!
*/

#include <exec/types.h>
#include <exec/memory.h>
#include <exec/ports.h>
#include <exec/memory.h>
#include <exec/interrupts.h>
#include <exec/nodes.h>
#include <exec/lists.h>
#include <exec/libraries.h>
#include <exec/tasks.h>
#include <exec/execbase.h>
#include <exec/io.h>
#include <exec/resident.h>
#include <exec/exec.h>
#include <exec/errors.h>
#include <exec/alerts.h>
#include <intuition/gadgetclass.h>
#include <intuition/intuition.h>
#include <midi/midi.h>
#include <utility/tagitem.h>
#include <string.h>
#include <stdio.h>
/*#include <wbstartup.h>*/
#include <workbench/startup.h>
#include <ctype.h>
#include <Stormamiga.h>
#include <functions.h>
#include <libraries/gadtools.h>
#include <libraries/dos.h>
#include <pragma/exec_lib.h>
#include <pragma/graphics_lib.h>
#include <pragma/gadtools_lib.h>
#include <clib/alib_protos.h>
#include <clib/intuition_protos.h>
#include <clib/macros.h>
#include <clib/exec_protos.h>
#include <graphics/gfxmacros.h>

/* Gadget defines of our choosing, to be used as GadgetID's: */

#define GAD_SEND        1
#define GAD_TESTTONE    2
#define GAD_LOAD        3
#define GAD_SAVE        4
#define GAD_INTEGER     5
#define GAD_CHECKBOX1   6
#define GAD_CHECKBOX2   7
#define GAD_MONO        8
#define GAD_DRUM        9
#define GAD_MOD         10
#define GAD_CYCLE1      11
#define GAD_CYCLE2      12
#define GAD_MODE        13
#define GAD_CHANNEL     14
#define GAD_PATCH       15
#define GAD_SCROLLER    16
#define GAD_LVSTRING    17
#define GAD_LISTVIEW    18
#define GAD_PALETTE     19
#define GAD_PATCHTEXT   20
#define GAD_PORT        21
#define GAD_MIDI        22
#define GAD_ATTACK      23
#define GAD_DECAY       24
#define GAD_RELEASE     25
#define GAD_RATE        26
#define GAD_DELAY       27
#define GAD_DEPTH       28
#define GAD_CUTOFF      29
#define GAD_RES         30

/*

#define SERIAL_PORT     (1 << 0)
#define SERIAL_EXTIO    (1 << 1)
#define SERIAL_DEVICE   (1 << 2)
#define TIMER_PORT      (1 << 3)
#define TIMER_EXTIO     (1 << 4)
#define TIMER_DEVICE    (1 << 5)
#define ICR_VECTOR      (1 << 6)
#define ARRAY_ALLOCATED (1 << 7)
*/

/*
struct patchdata {
    char name[20],
    UBYTE byte1,
    UBYTE byte2
};

typedef struct patchdata PATCHDATA;

PATCHDATA array[443]=

struct patchdata
*/


STRPTR ver = "$VER: MC-303-ED V0.005a";

/* Some MC303 Constants */

#define NUM_PATCHES 316
#define NUM_DRUMS   12

/* Decalre Strings For Gadegets */
STRPTR PatchLabels[]=
{
    "Lead TB 1","Lead TB 2","WOW TB","Lead TB 3","MG Saw","Voc. Saw","Cheese Saw","Saw Lead","Calc. Saw",
    "OB2 Saw 1","Juno6 Saw","JP8 Pulse 1","MG Pluse 1","Flicker Pulse","Tri Lead 1","Tri Lead 2","PR5 Square 1",
    "JU2 Subosc.","Frog Wave","Seq. Synth","Polysynth","JP8 Pulse 2","JP8 Square","260 Pulse 90","Reso. Pulse",
    "Reso. Stack","Soft Lead","8DV Saw 1","PR5 Saw 1","D50 Saw","MG Sweep","Sweep Lead","Vocorderman",
    "4th Lead 1","4th Lead 2",

    "Normal TB","Dist. TB 1","Dist. TB 2","Acid TB 1","Acid TB 2","Acid TB 3","Acid TB 4","101 Bass 1",
    "101 Bass 2","101 Bass 3","House Bass","Sine Bass","Dub Bass","Pizz. bass","MG Bass 1","MG Bass 2",
    "MG Bass 3","MG Bass 4","MG Super Bass","Cheese Bass","Synth SB Bass","Blip Bass","KGP Bass","TBGM Bass",
    "MG Bass 5","JPMG Bass","Click Bass","KMP Bass","Osc. Bass","Reso. Bass","WOW MF Bass","WOW 101 Bass",
    "Sweep WOW Bass","MG 5th Bass","Doom Bass","Rubber Bass 1","Rubber Bass 2",
    "Acid bass","Bubble Bass","Organ Bass",

    "Ac. Bass 1","Ac. Bass 2","Fingered Bass 1","Fingered Bass 2","Picked Bass 1","Dust Pick Bass",
    "Picked Bass 2","Fretless Bass","Slap Bass",

    "Synth Stack 1","Oct Stack","Synth Stack 2","Saw Stack","Synth SB 1","Synth SB 2","Brass Perc.",
    "Brass Perc.","Dirty SB",

    "Atmosphere","Feedback Wave","X-MOD","Pacifica","7th Atom","Outer Space","Rev. Atom","2.2 Pad",
    "Jungle Pad","Psycho Pad","Pipe Pad","Ambient Pad","Flanger Pad","Bell Pad","7th Bell Pad","Fantasia",
    "Crystal","Exo. Bell Pad","Echo Bell","Warm Pad","SoundTrack","Oct. Pad","OB String Pad","X-MOD Pad",
    "Sweep Pad 1","Sweep Pad 2","Golbin","Echo Drops","Random Pad","LFO Sweep","Horror Pad","Pulse Key Pad",

    "Real Strings 1","Real String 2","Auh Strings","Hi Strings","Synth Strings 1","Synth Strings 2",
    "Synth Strings 3","Noise Strings","RND Strings","LFO Strings","Slow Strings","Slow Syn Stings",
    "Pizzicato String",

    "Choirs Auhs","Space Voice","Sweepvox","Synthvox 1","Auh","Synthvox 2","Leadvox","Auh Auh","Sky Vox",
    "Auhbient","Vibravox","Noisevox",

    "UFO FX","Saw In Saw","Feed Bell","Abduction","Loop Sweep","UP FX","Robocorder","Noisegrow",
    "LFO Techno","Calculating","Emergency!","FX Beats","Analog FX","Transformer","Dusty Scratch",
    "Space Worms","Winky FX",

    "PR5 Noise 1","PR5 Noise 2","Pink Noise","White Noise","Bomb Wind","Synth Wind","Vinyl Noise",
    "Noise Snare","Explosion","Pink Bomb",

    "Ac. Piano","Bright Piano","E.Piano 1","E.Piano 2","E.Piano 3","E.Piano 4","Organ E.Piano","Noise Piano",
    "Clavia","Analog Clavia","Digital Clavia",

    "Organ 1","Lp-Hp Organ","Organ 2","Percusive Organ","Slow Organ","Smokey Org.Chord","Organ Chord",
    "60s Organ","Dist. Organ","Church Org.1","Organ Loop","LF-Organ",

    "Glockenspiel","Vibraphone","Beat Glocken","Marimba","Timpani","Steel Drums","Sqr. Perc.","Juno Bell",
    "MG Perc","Perc Glass",

    "Tubular-Bell","Vib. Bell","7th Bells","Ring Bell","Digital Bell 1","Ring Mod.","Digital Bell 2",
    "Dirty Bell 1","Dirty Bell 2","Digital Bell 3",

    "Steel Str. Gtr.","12str Guitar","Jazz Guitar","Clean Guitar","Distortion Git.","Gtr. Harmon.",
    "Acid Guitar 1","Acid Guitar 2","Jazz Stell Gtr.","Sitar Guitar","Wah Guitar",

    "Brass 1","Bright Brass 1","Bright Brass 2","Bass&String","SB Brass Sec.","ST Brass Sec.","OB Brass",
    "Hybrid Brass","4th Brass",

    "Synth Brass 1","Synth Brass 2","Bright Syn.Brs.1","Bright Syn.Brs.2","Warm Brass 1","Stack Brass 1",
    "Warm Brass 2","Strings Brass","Warm Brass 3","Stack Brass 2","Trumpet","Muted Trumpet","Sax&Trumpet",
    "Alto Sax","Baritone Sax","Brigth Sax","Flute","Pan Flute","Afro Flute","Pipe Lead 1","Pipe Lead 2",
    "Shakuhachi",

    "Sitar 1","Sitar 2","Kalimba","Bagpipe",

    "MG Blip 1","Rev.Blip","MG Blip 2","Syn. Perc.","Powa","Douby","P-Mod Perc","Bam Hit","Bit Hit",
    "Orch. Hit","BF Hit","Organ Hit","Bim Hit","Dist. Hit","Brass Fall","Strings Hit","Space Frog","Hoo!",
    "Ha!","Afro Feet","Breath 3","Scratch Rwnd","Scratch Push","Scratch Pull","Tape Rewind","Vinyl Stop",

    "Starship","Burst Noise","Laser-Gun","Seashore","Rain","Thunder",
    "Wind","Stream","Bubble","Bird","Low Bird","Telephone","Gun Shot","Machine Gun","Carr-Pass","Car-Crash",
    "Siren","Jetplane","Helichopter","Laughing","Screaming","Punch","Heart Beat","Applause",

    NULL
};

STRPTR DrumLabels[]=
{
    "TR-909","TR-808","CR-78 & TR-606","Jazz Kit","Brush Kit","Jungle Kit","House Kit","Techno Kit 1",
    "Techno Kit 2","Techno Kit 3","Abstract Kit"," HipHop Kit", NULL
};

STRPTR ReverbLabels[]=
{
    "Room 1",
    "Room 2",
    "Room 3",
    "Hall 1",
    "Hall 2",
    "Plate",
    "Delay",
    "Panning Delay",
    NULL,
};
STRPTR ChorusLabels[]=
{
    "Chorus 1",
    "Chorus 2",
    "Chorus 3",
    "Chorus 4",
    "Feedback Chorus",
    "Flanger",
    "Short Delay",
    "Short Delay FB",
    NULL,
};
STRPTR ModeLabels[] =
{
    "Normal Mode",
    "Sound Module Mode",
    NULL,
};

extern struct WBStartup *WBenchMsg;
void *MidiBase;
BOOL terminated;             /* Used to check for end of program */
BOOL mutechecked = FALSE;    /* Used to test mute checkbox */
BOOL solochecked = FALSE;    /* Used to check the solo button */
BOOL monochecked = FALSE;    /* Used to check the mono button */
BOOL drumchecked = FALSE;    /* Used to check the drum button */
BOOL midichecked = TRUE;     /* Used for MIDI disabled ? */
BOOL TONE_ON = FALSE;        /* Used for Test tone button, TRUE= Noise, FALSE=Silence */
WORD sliderlevel = 7;
WORD incr = 1;
struct Gadget *integergad, *modegad, *checkgad1, *checkgad2, *monogad, *channelgad, *cyclegad1,
              *cyclegad2, *lvgad, *stringgad, *sendgad, *testtonegad, *patchgad, *patchtextgad,
              *savegad, *loadgad, *drumgad, *portgad, *midigad, *modgad, *attackgad, *decaygad,
              *releasegad, *rategad, *delaygad, *depthgad, *cutoffgad, *resgad;
int channel,i,cort,channum,notenum,notedelay;
char filename[80];
char *fname;
UBYTE buffer[13];
void *vi = NULL;
UBYTE MC303_CHANNEL; /* Global to tell us what channel we are working with */

/* Array to store all the details about the MC-303 that we have set */

UWORD MC303

[17]   /* The midi channel 0-15,
          Field 16 is used to store System stuff; Mainly for the load and save fuctions  */

[255];
       /* Defines for array, to make it easy you know!  B-)  */

#define MC303_MUTE    1   /* TRUE = channel is muted */
#define MC303_SOLO    2   /* TRUE = channel is soloed, NB: mute and solo can NEVER both be TRUE! */
#define MC303_PATCH   3   /* Patch number, there are 316 */
#define MC303_MONO    4   /* TRUE = MONO on, FALSE = MONO off */
#define MC303_PORT    5
#define MC303_PAN     6
#define MC303_MOD     7
#define MC303_ATTACK  8
#define MC303_DECAY   9
#define MC303_RELEASE 10
#define MC303_RATE    11
#define MC303_DELAY   12
#define MC303_DEPTH   13
#define MC303_CUTOFF  14  /* Values between 14-114 only */
#define MC303_RES     15

      /* Defines for Array Part 17, the system stuff */

#define MC303_DATA    17  /* This part of the array */

#define MC303_VERS    1   /* This is Version 0.9 */
#define MC303_MODE    2   /* TRUE= NORMAL_MODE, FALSE=SOUND_MODULE_MODE */
#define MC303_DRUM11  3   /* TRUE and part 11 is in drum Mod */

/* Define SYSX Data for the MC-303 */

    /* Operation Mode */

UBYTE NORMAL_MODE[] = {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x00,0x7f,0x7f,0x3e,0xf7};
UBYTE SOUND_MODULE_MODE[] = {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x00,0x7f,0x00,0x3f,0xf7};

    /* Effect Macros */

UBYTE REVERB[8][13] = {
    {0xf0,0x40,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x30,0x00,0x0f,0xf7},
    {0xf0,0x40,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x30,0x01,0x0e,0xf7},
    {0xf0,0x40,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x30,0x02,0x0d,0xf7},
    {0xf0,0x40,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x30,0x03,0x0c,0xf7},
    {0xf0,0x40,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x30,0x04,0x0b,0xf7},
    {0xf0,0x40,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x30,0x05,0x0a,0xf7},
    {0xf0,0x40,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x30,0x06,0x09,0xf7},
    {0xf0,0x40,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x30,0x07,0x08,0xf7},
};

UBYTE CHORUS[8][13] = {
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x38,0x00,0x07,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x38,0x01,0x06,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x38,0x02,0x05,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x38,0x03,0x04,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x38,0x04,0x03,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x38,0x05,0x02,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x38,0x06,0x01,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x01,0x38,0x07,0x00,0xf7},
};

    /* Channel Mutes, for sound module mode */


UBYTE SM_OFF_PART[16][13] = {
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x18,0x08,0x00,0x20,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1a,0x08,0x00,0x1e,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1b,0x08,0x00,0x1d,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1c,0x08,0x00,0x1c,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1d,0x08,0x00,0x1b,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1e,0x08,0x00,0x1a,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1f,0x08,0x00,0x19,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x10,0x08,0x00,0x28,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x11,0x08,0x00,0x27,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x19,0x08,0x00,0x1f,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x12,0x08,0x00,0x26,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x13,0x08,0x00,0x25,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x14,0x08,0x00,0x24,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x15,0x08,0x00,0x23,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x16,0x08,0x00,0x22,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x17,0x08,0x00,0x21,0xf7}
};

   /* Channel ON, for sound module mode */

UBYTE SM_ON_PART[16][13] = {
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x18,0x08,0x01,0x1f,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1a,0x08,0x01,0x1d,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1b,0x08,0x01,0x1c,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1c,0x08,0x01,0x1b,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1d,0x08,0x01,0x1a,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1e,0x08,0x01,0x19,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x1f,0x08,0x01,0x18,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x10,0x08,0x01,0x27,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x11,0x08,0x01,0x26,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x19,0x08,0x01,0x1e,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x12,0x08,0x01,0x25,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x13,0x08,0x01,0x24,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x14,0x08,0x01,0x23,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x15,0x08,0x01,0x22,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x16,0x08,0x01,0x21,0xf7},
    {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x17,0x08,0x01,0x20,0xf7},
};

    /* Channel 11 Drum Kit */

UBYTE DRUM_ON[] =  {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x12,0x15,0x02,0x17,0xf7};
UBYTE DRUM_OFF[] = {0xf0,0x41,0x10,0x00,0x03,0x12,0x00,0x40,0x12,0x15,0x00,0x17,0xf7};

/* NRPN and CC arrays to hold data for Specific MC303 funtions */

/* PATCHES

   To select a patch we send; CC#0=nn     nn=bank
                              CC#32=0     required by MC303
                              PC=nr       Program Change number

   We only need to know the CC#0 value and the PC number for each patch

*/

#define PATCH_CC = 0
#define PATCH_PC = 1

UBYTE PATCH[448][2] = {
    64,1,65,1,66,1,67,1,64,2,65,2,66,2,67,2,68,2,69,2,70,2,71,2,72,2,73,2,64,3,65,3,66,3,64,4,65,4,
    64,5,65,5,66,5,67,5,68,5,69,5,70,5,64,6,65,6,66,6,67,6,64,7,65,7,66,7,64,8,65,8,

    64,9,65,9,66,9,67,9,68,9,69,9,70,9,64,10,65,10,66,10,67,10,68,10,69,10,64,11,
    64,12,65,12,66,12,67,12,68,12,69,12,70,12,64,13,65,13,66,13,67,13,68,13,69,13,70,13,71,13,
    64,14,65,14,66,14,67,14,68,14,69,14,70,14,71,14,64,15,65,15,64,16,

    64,17,65,17,64,18,65,18,64,19,65,19,66,19,64,20,64,21,64,22,65,22,66,22,67,22,64,23,65,23,66,23,67,23,

    64,24,65,24,66,24,67,24,68,24,69,24,70,24,64,25,65,25,66,25,67,25,68,25,69,25,64,26,65,26,66,26,
    67,26,68,26,69,26,64,27,65,27,66,27,67,27,68,27,69,27,70,27,71,27,72,27,73,27,64,28,65,28,66,28,67,28,

    64,29,65,29,64,30,65,30,66,30,67,30,68,30,64,31,65,31,66,31,64,32,65,32,66,33,

    64,34,64,35,65,35,66,35,67,35,68,35,69,35,70,35,71,35,72,35,73,35,74,35,

    64,37,65,36,66,36,67,36,68,36,69,36,70,36,71,36,64,37,65,37,66,37,67,37,68,37,69,37,70,37,71,37,72,37,

    64,38,65,38,66,38,67,38,64,39,65,39,66,39,67,39,64,40,65,40,

    64,41,65,41,64,42,65,42,66,42,67,42,64,43,65,43,64,44,65,44,66,44,

    64,45,65,45,64,46,65,46,64,47,64,48,65,48,64,49,64,50,64,51,64,52,65,52,

    64,53,65,53,66,53,67,53,64,54,65,54,64,55,65,55,66,55,67,55,

    64,56,65,56,64,57,65,57,66,57,67,57,68,57,69,57,70,57,71,57,

    64,58,65,58,64,59,65,59,66,59,67,59,64,60,65,60,66,60,67,60,68,60,

    64,62,65,62,66,62,64,63,65,63,66,63,64,64,65,64,64,65,

    64,66,65,66,66,66,67,66,68,66,69,66,70,66,71,66,72,66,73,66,64,67,65,67,66,67,64,68,65,68,66,68,64,69,
    64,70,65,70,66,70,67,70,64,71,

    64,72,65,72,64,73,64,74,

    64,76,65,76,66,76,67,76,68,76,69,76,70,76,64,77,65,77,66,77,67,77,68,77,69,77,70,77,71,77,72,77,73,77,64,78,
    65,78,66,78,67,78,64,79,65,79,66,79,64,80,65,80,

    64,81,65,81,66,81,64,82,65,82,66,82,67,82,68,82,69,82,64,83,65,83,64,84,65,84,66,84,64,85,65,85,66,85,67,85,
    68,85,64,86,65,86,66,86,67,86,68,86
};

/*  Drum Program Changes */

UBYTE DRUM[12] = {1,9,17,25,26,33,41,49,57,65,73,81};



/************************************
** Declare a few global structures **
************************************/

/*
extern struct MsgPort *CreatePort();
extern struct IORequest *CreateExtIO();
*/
extern struct Library *GadToolsBase;
extern short Enable_Abort;
struct MSource *source = NULL;
struct MRoute *route = NULL;
struct GfxBase *GfxBase = NULL;
struct IntuitionBase *IntuitionBase = NULL;
struct Library *GadToolsBase = NULL;
struct TextFont *font = NULL;
struct Screen *mysc = NULL;
struct Remember *RKey = NULL;
struct Gadget *glist = NULL;
struct Menu *menu = NULL;
struct Window *mywin = NULL;
struct Library *AslBase = NULL;

/* Main Window Structure */

struct NewWindow mynewwin =
{
    0, 0,                                               /* LeftEdge, TopEdge */
    610, 300,                                             /* Width, Height */
    -1, -1,                                               /* DetailPen, BlockPen */
    MENUPICK | MOUSEBUTTONS | GADGETUP | GADGETDOWN |
    MOUSEMOVE | CLOSEWINDOW | REFRESHWINDOW | INTUITICKS, /* IDCMPFlags */
    ACTIVATE | WINDOWDRAG | WINDOWDEPTH |
    WINDOWCLOSE | SIMPLE_REFRESH,                         /* Flags */
    NULL,                                                 /* FirstGadget */
    NULL,                                                 /* CheckMark */
    "DJ Reaver's MC-303 Editor V0.005a",                  /* Title */
    NULL,                                                 /* Screen */
    NULL,                                                 /* BitMap */
    50, 50,                                               /* MinWidth, MinHeight */
    640, 200,                                             /* MaxWidth, MaxHeight */
    WBENCHSCREEN,                                         /* Type */
};

struct TextAttr Haze80 =
{
    "topaz.font",       /* Name */
    8,                  /* YSize */
    0,                  /* Style */
    0,                  /* Flags */
};

/*****************************************
** All My Functions are in this section **
*****************************************/

/*------------------------------------------------------------------------*/
void close_midi()
{
   /* Close Midi off Properly */
   if (route) DeleteMRoute (route);
   if (source) DeleteMSource (source);
   if (MidiBase) CloseLibrary (MidiBase);
   return;
}


/*------------------------------------------------------------------------*/
void bail_out( int code, STRPTR error)
{
    if (mywin)
    {
        /*ClearMenuStrip(mywin);*/
        CloseWindow(mywin);
    }

    /* None of these three calls mind a NULL parameter, so it's not
     * necessary to check for non-NULL before calling.  If we do that,
     * we must be certain that the OpenLibrary() of GadTools succeeded,
     * or else we would be jumping into outer space:
     */

    if (GadToolsBase)
    {
        FreeMenus(menu);
        FreeVisualInfo(vi);
        FreeGadgets(glist);
        CloseLibrary(GadToolsBase);
    }
    if (mysc)
    {
        UnlockPubScreen(NULL, mysc);
    }

    if (RKey)
    {
        FreeRemember(&RKey, TRUE);
    }

    if (font)
        CloseFont(font);

    if (IntuitionBase)
        CloseLibrary( ( struct Library *)IntuitionBase);

    if (GfxBase)
        CloseLibrary( ( struct Library *)GfxBase);

    if (AslBase)
        CloseLibrary( ( struct Library *)AslBase);

    if (midichecked)
    {
        if (MidiBase)
            close_midi();
    }

    if (error)
    {
        printf("Error: %s\n", error);
    }
    exit(code);
}

/*------------------------------------------------------------------------*/
void open_midi()
{
    if (!(MidiBase = OpenLibrary (MIDINAME,MIDIVERSION)))
       bail_out (10,"Cant open midi.library");

  /* Create Our Source Node */

    if (!(source = CreateMSource (NULL,NULL)))
        bail_out(1,"Can't create source\n");

    if (!(route = MRouteSource (source, "MidiOut", NULL)))
        bail_out(1,"Can't create route\n");

    return;
}

/*------------------------------------------------------------------------*/
void noteon(int pitch)
{
    buffer[0] = (MS_NOTEON | MC303_CHANNEL-1);
    buffer[1] = pitch;
    buffer[2] = DEFAULTVELOCITY;
    PutMidiStream(source,NULL,buffer,3,3);
    return;
}

/*------------------------------------------------------------------------*/
void noteoff(int pitch)
{
    buffer[0] = (MS_NOTEOFF | MC303_CHANNEL-1);
    buffer[1] = pitch;
    buffer[2] = DEFAULTVELOCITY;
    PutMidiStream(source,NULL,buffer,3,3);
    return;
}

/*------------------------------------------------------------------------*/
void save()
{  
    struct FileRequester *request;
    long bytes_written,file_handle;
    BOOL result;
    UBYTE file[4335];
    STRPTR dirname;
    int loop1, loop2, file_pos;

    file_pos = 0;
    for (loop1 = 0; loop1 < 17; loop1++)
    {
       for (loop2 = 0;loop2 < 255; loop2++)
       {
          file[file_pos] = MC303[loop1][loop2];
          file_pos++;
       }
    }
    if (AslBase = OpenLibrary("asl.library", 37L))
    {
        if (request = (struct FileRequester *)
            AllocFileRequest());
        {
            if (RequestFile(request))
            {
                dirname = request->fr_Drawer;
                AddPart(dirname,request->fr_File,512);
                file_handle = Open(dirname, MODE_NEWFILE);
                if(file_handle == NULL)
                   printf("Could not open the file!\n");
                bytes_written = Write( file_handle, file, (long)sizeof (file) );
                if (bytes_written != sizeof(file))
                    printf("Could not save data!\n");
                Close(file_handle);
            }
            FreeFileRequest(request);
        }
        CloseLibrary(AslBase);
    }
    return;
}

/*------------------------------------------------------------------------*/
void load()
{
    struct FileRequester *request;
    long bytes_read,file_handle;
    BOOL result;
    UBYTE file[4335];
    STRPTR dirname;
    int loop1, loop2, file_pos;

    file_pos = 0;
   
    if (AslBase = OpenLibrary("asl.library", 37L))
    {
        if (request = (struct FileRequester *)
            AllocFileRequest());
        {
            if (RequestFile(request))
            {
                dirname = request->fr_Drawer;
                AddPart(dirname,request->fr_File,512);
                file_handle = Open(dirname, MODE_OLDFILE);
                if(file_handle == NULL)
                   printf("Could not open the file!\n");
                bytes_read = Read(file_handle,file,4335);
                Close(file_handle);
            }
            FreeFileRequest(request);
        }
        CloseLibrary(AslBase);
        for (loop1 = 0; loop1 < 17; loop1++)
        {
           for (loop2 = 0;loop2 < 255; loop2++)
           {
               MC303[loop1][loop2] = file[file_pos];
               file_pos++;
           }
        }
    }

   
    return;
}

/*--------------------------------------------------------------------------
** Update the entire landscape to refect the values of the current        **
** channel (code),  is called when you change the channel or after a load **
**/

void update ()
{
    UWORD patch;
    /* The Mode Button */
    if (MC303[MC303_DATA][MC303_MODE])
        GT_SetGadgetAttrs(modegad, mywin, NULL, GTMX_Active, 0, TAG_DONE);
    else
        GT_SetGadgetAttrs(modegad, mywin, NULL, GTMX_Active, 1, TAG_DONE);

    /* The Mute Button */
    if (MC303[MC303_CHANNEL-1][MC303_MUTE] == TRUE)
        GT_SetGadgetAttrs(checkgad1, mywin, NULL, GTCB_Checked, TRUE, TAG_DONE);
    else
        GT_SetGadgetAttrs(checkgad1, mywin, NULL, GTCB_Checked, FALSE, TAG_DONE);

    /* The Patch Slider */
    patch = MC303[MC303_CHANNEL-1][MC303_PATCH];
    switch (MC303_CHANNEL)
    {
        case 10:
            GT_SetGadgetAttrs(patchgad, mywin, NULL, GTSC_Total,NUM_DRUMS, TAG_DONE);
            GT_SetGadgetAttrs(patchtextgad, mywin, NULL, GTTX_Text, DrumLabels[patch], TAG_DONE);
            GT_SetGadgetAttrs(patchgad, mywin, NULL, GTSC_Top,MC303[MC303_CHANNEL-1][MC303_PATCH], TAG_DONE);
            break;
        case 11:
            if (MC303[MC303_DATA][MC303_DRUM11])
            {
                GT_SetGadgetAttrs(patchgad, mywin, NULL, GTSC_Total,NUM_DRUMS, TAG_DONE);
                GT_SetGadgetAttrs(patchtextgad, mywin, NULL, GTTX_Text, DrumLabels[patch], TAG_DONE);
                GT_SetGadgetAttrs(patchgad, mywin, NULL, GTSC_Top,MC303[MC303_CHANNEL-1][MC303_PATCH], TAG_DONE);
            }
            else
            {
                GT_SetGadgetAttrs(patchgad, mywin, NULL, GTSC_Total,NUM_PATCHES, TAG_DONE);
                GT_SetGadgetAttrs(patchtextgad, mywin, NULL, GTTX_Text, PatchLabels[patch], TAG_DONE);
                GT_SetGadgetAttrs(patchgad, mywin, NULL, GTSC_Top,MC303[MC303_CHANNEL-1][MC303_PATCH], TAG_DONE);
            }
            break;
        default:
            GT_SetGadgetAttrs(patchgad, mywin, NULL, GTSC_Total,NUM_PATCHES, TAG_DONE);
            GT_SetGadgetAttrs(patchtextgad, mywin, NULL, GTTX_Text, PatchLabels[patch], TAG_DONE);
            GT_SetGadgetAttrs(patchgad, mywin, NULL, GTSC_Top,MC303[MC303_CHANNEL-1][MC303_PATCH], TAG_DONE);
            break;
    };


    /* The Mono Button */
    if (MC303[MC303_CHANNEL-1][MC303_MONO] == TRUE)
        GT_SetGadgetAttrs(monogad, mywin, NULL, GTCB_Checked, TRUE, TAG_DONE);
    else
        GT_SetGadgetAttrs(monogad, mywin, NULL, GTCB_Checked, FALSE, TAG_DONE);

    /* The Drum Button */
    if (MC303[MC303_DATA][MC303_DRUM11] == TRUE)
        GT_SetGadgetAttrs(drumgad, mywin, NULL, GTCB_Checked, TRUE, TAG_DONE);
    else
        GT_SetGadgetAttrs(drumgad, mywin, NULL, GTCB_Checked, FALSE, TAG_DONE);

    /* The Delay slider */
    GT_SetGadgetAttrs(delaygad, mywin, NULL, GTSL_Level, MC303[MC303_CHANNEL-1][MC303_DELAY], TAG_DONE);

    /* The Depth slider */
    GT_SetGadgetAttrs(depthgad, mywin, NULL, GTSL_Level, MC303[MC303_CHANNEL-1][MC303_DEPTH], TAG_DONE);

    /* The Rate slider */
    GT_SetGadgetAttrs(rategad, mywin, NULL, GTSL_Level, MC303[MC303_CHANNEL-1][MC303_RATE], TAG_DONE);

    /* The Release slider */
    GT_SetGadgetAttrs(releasegad, mywin, NULL, GTSL_Level, MC303[MC303_CHANNEL-1][MC303_RELEASE], TAG_DONE);

    /* The Decay slider */
    GT_SetGadgetAttrs(decaygad, mywin, NULL, GTSL_Level, MC303[MC303_CHANNEL-1][MC303_DECAY], TAG_DONE);

    /* The Attack slider */
    GT_SetGadgetAttrs(attackgad, mywin, NULL, GTSL_Level, MC303[MC303_CHANNEL-1][MC303_ATTACK], TAG_DONE);

    /* The Port slider */
    GT_SetGadgetAttrs(portgad, mywin, NULL, GTSL_Level, MC303[MC303_CHANNEL-1][MC303_PORT], TAG_DONE);

    /* The Resonace Slider */
    GT_SetGadgetAttrs(resgad, mywin, NULL, GTSL_Level, MC303[MC303_CHANNEL-1][MC303_RES], TAG_DONE);

    /* The Filter Silder */
    GT_SetGadgetAttrs(cutoffgad, mywin, NULL, GTSL_Level, MC303[MC303_CHANNEL-1][MC303_CUTOFF], TAG_DONE);

    return;
}

/*-------------------------------------------------------------------------
** The following routines are for sending sprecific data to different
** synth elements
**
**/

void send_delay(int value)
{
    /* Send; CC99=01, CC98=10, CC6=0-127 */
        /* Select RPN Function */
    buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[1]= 99;
    buffer[2]= 1;
        /* Select Attack */
    buffer[3]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[4]= 98;
    buffer[5]= 10;
        /* Send Value */
    buffer[6]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[7]= 6;
    buffer[8]= value;
    buffer[9]= 0;
    PutMidiStream(source,NULL,buffer,(long)sizeof buffer,(long)sizeof buffer);
        /* Update the Array */
    MC303[MC303_CHANNEL-1][MC303_DELAY]=value;
    return;
}

void send_mod(int value)
{
    return;
}

void send_depth(int value)
{
    /* Send; CC99=01, CC98=9, CC6=0-127 */
        /* Select RPN Function */
    buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[1]= 99;
    buffer[2]= 1;
        /* Select Attack */
    buffer[3]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[4]= 98;
    buffer[5]= 9;
        /* Send Value */
    buffer[6]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[7]= 6;
    buffer[8]= value;
    buffer[9]= 0;
    PutMidiStream(source,NULL,buffer,(long)sizeof buffer,(long)sizeof buffer);
        /* Update the Array */
    MC303[MC303_CHANNEL-1][MC303_DEPTH]=value;
    return;
}

void send_rate(int value)
{
    /* Send; CC99=01, CC98=8, CC6=0-127 */
        /* Select RPN Function */
    buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[1]= 99;
    buffer[2]= 1;
        /* Select Attack */
    buffer[3]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[4]= 98;
    buffer[5]= 8;
        /* Send Value */
    buffer[6]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[7]= 6;
    buffer[8]= value;
    buffer[9]= 0;
    PutMidiStream(source,NULL,buffer,(long)sizeof buffer,(long)sizeof buffer);
        /* Update the Array */
    MC303[MC303_CHANNEL-1][MC303_RATE]=value;
    return;
}

void send_patch(int value)
{               
               switch (MC303_CHANNEL)
               {
                   case 10:
                       buffer[0]= (MS_PROG | MC303_CHANNEL-1);
                       buffer[1]= (DRUM[value])-1;
                       PutMidiStream(source,NULL,buffer,2,2);
                       break;
                   case 11:
                       if (MC303[MC303_DATA][MC303_DRUM11])
                       {
                           buffer[0]= (MS_PROG | MC303_CHANNEL-1);
                           buffer[1]= (DRUM[value])-1;
                           PutMidiStream(source,NULL,buffer,2,2);
                       }
                       else
                       {
                           buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
                           buffer[1]= 0;
                           buffer[2]= PATCH[value][0];    /* This [0] should read, [PATCH_CC] */
                           PutMidiStream(source,NULL,buffer,3,3);
                           buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
                           buffer[1]= 32;
                           buffer[2]= 0;
                           PutMidiStream(source,NULL,buffer,3,3);
                           buffer[0]= (MS_PROG | MC303_CHANNEL-1);
                           buffer[1]= (PATCH[value][1])-1;  /* This [1] should read [PATCH_PC] */
                           PutMidiStream(source,NULL,buffer,2,2);
                       }
                       break;
                   default:
                       buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
                       buffer[1]= 0;
                       buffer[2]= PATCH[value][0];    /* This [0] should read, [PATCH_CC] */
                       PutMidiStream(source,NULL,buffer,3,3);
                       buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
                       buffer[1]= 32;
                       buffer[2]= 0;
                       PutMidiStream(source,NULL,buffer,3,3);
                       buffer[0]= (MS_PROG | MC303_CHANNEL-1);
                       buffer[1]= (PATCH[value][1])-1;  /* This [1] should read [PATCH_PC] */
                       PutMidiStream(source,NULL,buffer,2,2);
                       break;
               };
    return;
}

void send_mono(int value)
{
  
    return;
}

void send_mute(int value)
{
   if (MC303[value][MC303_MUTE] == TRUE)
       {
        PutMidiStream(source,NULL,SM_OFF_PART[value-1],(long)sizeof SM_OFF_PART[value-1], (long)sizeof SM_OFF_PART[value-1]);
       }
   else
       {
       PutMidiStream(source,NULL,SM_ON_PART[value-1],(long)sizeof SM_ON_PART[value-1], (long)sizeof SM_ON_PART[value-1]);
       }

   return;
}

void send_drum(int value)
{
    if (MC303_CHANNEL == 11)
             {
                 MC303[MC303_CHANNEL-1][MC303_PATCH] = 0;
                 if (drumchecked)
                 {
                     drumchecked = FALSE;
                     MC303[MC303_DATA][MC303_DRUM11] = FALSE;
                     PutMidiStream(source,NULL,DRUM_OFF,(long)sizeof DRUM_OFF, (long)sizeof DRUM_OFF);
                     update();
                 }
                 else
                 {
                     drumchecked = TRUE;
                     MC303[MC303_DATA][MC303_DRUM11] = TRUE;
                     PutMidiStream(source,NULL,DRUM_ON,(long)sizeof DRUM_ON, (long)sizeof DRUM_ON);
                     update();
                 }
             }
             else
             {
                 GT_SetGadgetAttrs(drumgad, mywin, NULL, GTCB_Checked, drumchecked, TAG_DONE);
             }
    return;
}

void send_release(int value)
{
    /* Send; CC99=01, CC98=102, CC6=14-114 */
        /* Select RPN Function */
    buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[1]= 99;
    buffer[2]= 1;
        /* Select Attack */
    buffer[3]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[4]= 98;
    buffer[5]= 102;
        /* Send Value */
    buffer[6]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[7]= 6;
    buffer[8]= value;
    buffer[9]= 0;
    PutMidiStream(source,NULL,buffer,(long)sizeof buffer,(long)sizeof buffer);
        /* Update the Array */
    MC303[MC303_CHANNEL-1][MC303_RELEASE]=value;
    return;
}

void send_decay(int value)
{
    /* Send; CC99=01, CC98=100, CC6=14-114 */
        /* Select RPN Function */
    buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[1]= 99;
    buffer[2]= 1;
        /* Select Attack */
    buffer[3]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[4]= 98;
    buffer[5]= 100;
        /* Send Value */
    buffer[6]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[7]= 6;
    buffer[8]= value;
    buffer[9]= 0;
    PutMidiStream(source,NULL,buffer,(long)sizeof buffer,(long)sizeof buffer);
        /* Update the Array */
    MC303[MC303_CHANNEL-1][MC303_DECAY]=value;
    return;
}

void send_attack(int value)
{
    /* Send; CC99=01, CC98=99, CC6=14-114 */
        /* Select RPN Function */
    buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[1]= 99;
    buffer[2]= 1;
        /* Select Attack */
    buffer[3]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[4]= 98;
    buffer[5]= 99;
        /* Send Value */
    buffer[6]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[7]= 6;
    buffer[8]= value;
    buffer[9]= 0;
    PutMidiStream(source,NULL,buffer,(long)sizeof buffer,(long)sizeof buffer);
        /* Update the Array */
    MC303[MC303_CHANNEL-1][MC303_ATTACK]=value;
    return;
}

void send_port(int value)
{
    /* Send; CC65=127, CC5=0-127 */
        /* Select RPN Function */
    buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[1]= 65;
    buffer[2]= 127;
        /* Send Portamo Value */
    buffer[3]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[4]= 5;
    buffer[5]= value;
    buffer[6]= 0;
    PutMidiStream(source,NULL,buffer,(long)sizeof buffer,(long)sizeof buffer);
        /* Update the Array */
    MC303[MC303_CHANNEL-1][MC303_PORT]=value;
    return;
}

void send_cutoff(int value)
{
    /* Send; CC99=01, CC98=32, CC06=14-114 */
        /* Select RPN Function */
    buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[1]= 99;
    buffer[2]= 1;
        /* Select cufoff filter */
    buffer[3]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[4]= 98;
    buffer[5]= 32;
        /* Filter Setting */
    buffer[6]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[7]= 6;
    buffer[8]= value;
    buffer[9]= 0;
    PutMidiStream(source,NULL,buffer,(long)sizeof buffer,(long)sizeof buffer);
        /* Update the Array */
    MC303[MC303_CHANNEL-1][MC303_CUTOFF]=value;
    return;
}

void send_res(int value)
{
    /* Send; CC99=01, CC98=33, CC06=14-114 */
        /* Select RPN Function */
    buffer[0]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[1]= 99;
    buffer[2]= 1;
       /* Select Resonace */
    buffer[3]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[4]= 98;
    buffer[5]= 33;
       /* Resonace Setting */
    buffer[6]= (MS_CTRL | MC303_CHANNEL-1);
    buffer[7]= 6;
    buffer[8]= value;
    buffer[9]= 0;
    PutMidiStream(source,NULL,buffer,(long)sizeof buffer,(long)sizeof buffer);
       /* Update the Array */
    MC303[MC303_CHANNEL-1][MC303_RES]=value;
    return;
}


/*------------------------------------------------------------------------
** Send all the info that is setup in the landscape, out the MC-303,
** this is routine is called after the Load function or when the user
**  presses the SEND button.
**/

void send ()
{
    int loop, temp;

    /* Firstly Set the module mode */
    if (MC303[MC303_DATA][MC303_MODE])
        PutMidiStream(source,NULL,NORMAL_MODE,(long)sizeof NORMAL_MODE, (long)sizeof NORMAL_MODE);
    else
        PutMidiStream(source,NULL,SOUND_MODULE_MODE,(long)sizeof SOUND_MODULE_MODE, (long)sizeof SOUND_MODULE_MODE);

    /* Is DRUM Set ? */

    /* Send the Reverb */

    /* Send the Chorus */

    /* Loop for each of the 16 midi channels */
    temp = MC303_CHANNEL;
    for (loop = 1 ; loop < 17 ; loop ++)
        {
            MC303_CHANNEL=loop;
            /* Send the Patch */
            send_patch(MC303[MC303_CHANNEL-1][MC303_PATCH]);
            /* Send the port */
            send_port(MC303[MC303_CHANNEL-1][MC303_PORT]);
            /* Send the Mod. */
            send_mod(MC303[MC303_CHANNEL-1][MC303_MOD]);
            /* Send the Attack */
            send_attack(MC303[MC303_CHANNEL-1][MC303_ATTACK]);
            /* Send the Decay */
            send_decay(MC303[MC303_CHANNEL-1][MC303_DECAY]);
            /* Send the Release */
            send_release(MC303[MC303_CHANNEL-1][MC303_RELEASE]);
            /* Send the Rate */
            send_rate(MC303[MC303_CHANNEL-1][MC303_RATE]);
            /* Send the Delay */
            send_delay(MC303[MC303_CHANNEL-1][MC303_DELAY]);
            /* Send the Depth */
            send_depth(MC303[MC303_CHANNEL-1][MC303_DEPTH]);
            /* Send the Cutoff */
            send_cutoff(MC303[MC303_CHANNEL-1][MC303_CUTOFF]);
            /* Send the Res. */
            send_res(MC303[MC303_CHANNEL-1][MC303_RES]);
            /* What about MUTE ? */
            send_mute(MC303_CHANNEL-1);
            /* And the MONO */
            if (MC303[MC303_CHANNEL-1][MC303_MONO])
                {
                buffer[0] = (MS_CTRL | MC303_CHANNEL-1);
                buffer[1] = 126;
                buffer[2] = 1;
                PutMidiStream(source,NULL,buffer,3,3);
                }
            else
                {
                buffer[0] = (MS_MODE | MC303_CHANNEL-1);
                buffer[1] = MM_POLY;
                buffer[2] = 0;
                PutMidiStream(source,NULL,buffer,3,3);
                }
        }
    MC303_CHANNEL = temp;
    return;
}





/*------------------------------------------------------------------------*/

/*/ CreateAllGadgets()
 *
 * Here is where all the initialization and creation of toolkit gadgets
 * take place.  This function requires a pointer to a NULL-initialized
 * gadget list pointer.  It returns a pointer to the last created gadget,
 * which can be checked for success/failure.
 *
 */

struct Gadget *CreateAllGadgets( struct Gadget **glistptr, void *vi, UWORD topborder)
{
    struct NewGadget ng;

    struct Gadget *gad;

    WORD index;
    struct Node *node;

    /* All the gadget creation calls accept a pointer to the previous
     * gadget, and link the new gadget to that gadget's NextGadget field.
     * Also, they exit gracefully, returning NULL, if any previous gadget
     * was NULL.  This limits the amount of checking for failure that
     * is needed.  You only need to check before you tweak any gadget
     * structure or use any of its fields, and finally once at the end,
     * before you add the gadgets.
     */

    /* We obligingly perform the following operation, required of
     * any program that uses the toolkit.  It gives the toolkit a
     * place to stuff context data:
     */
    gad = CreateContext(glistptr);
    /* Fill out a NewGadget structure to describe the gadget we want
     * to create:
     */

    /* Create a centered label (read-only) */
    ng.ng_LeftEdge = 300;
    ng.ng_TopEdge = 4+topborder;
    ng.ng_Width = 0;
    ng.ng_Height = 8;
    ng.ng_GadgetText = "MC-303 Editor";
    ng.ng_TextAttr = &Haze80;
    ng.ng_GadgetID = 0;
    ng.ng_Flags = PLACETEXT_IN | NG_HIGHLABEL;
    ng.ng_VisualInfo = vi;
    /* Text-Only gadget with GadgetText but no other text: */
    gad = CreateGadget(TEXT_KIND, gad, &ng,
        TAG_DONE);


    /* Since the NewGadget structure is unmodified by any of the
     * CreateGadget() calls, we need only change those fields which
     * are different.
     */

    /* Send Landscape Button */

    ng.ng_LeftEdge = 10;
    ng.ng_TopEdge = 240+topborder;
    ng.ng_Width = 100;
    ng.ng_Height = 20;
    ng.ng_GadgetText = "Send";
    ng.ng_GadgetID = GAD_SEND;
    ng.ng_Flags = 0;
    sendgad = gad = CreateGadget(BUTTON_KIND, gad, &ng,
        TAG_DONE);

    /* Send Test Tone Button */

    ng.ng_LeftEdge = 10;
    ng.ng_TopEdge = 270+topborder;
    ng.ng_Width = 100;
    ng.ng_Height = 20;
    ng.ng_GadgetText = "Test Tone";
    ng.ng_GadgetID = GAD_TESTTONE;
    ng.ng_Flags = 0;
    testtonegad = gad = CreateGadget(BUTTON_KIND, gad, &ng,
        TAG_DONE);

    /* Load Button Button */

    ng.ng_LeftEdge = 120;
    ng.ng_TopEdge = 240+topborder;
    ng.ng_Width = 100;
    ng.ng_Height = 20;
    ng.ng_GadgetText = "Load";
    ng.ng_GadgetID = GAD_LOAD;
    ng.ng_Flags = 0;
    loadgad = gad = CreateGadget(BUTTON_KIND, gad, &ng,
        TAG_DONE);

    /* Save Button Button */

    ng.ng_LeftEdge = 120;
    ng.ng_TopEdge = 270+topborder;
    ng.ng_Width = 100;
    ng.ng_Height = 20;
    ng.ng_GadgetText = "Save";
    ng.ng_GadgetID = GAD_SAVE;
    ng.ng_Flags = 0;
    savegad = gad = CreateGadget(BUTTON_KIND, gad, &ng,
        TAG_DONE);

    /* Set the Reverb */

    ng.ng_LeftEdge = 70;
    ng.ng_TopEdge = 80+topborder;
    ng.ng_Width = 145;
    ng.ng_Height = 15;
    ng.ng_GadgetText = "Reverb:";
    ng.ng_GadgetID = GAD_CYCLE1;
    ng.ng_Flags = NG_HIGHLABEL;
    cyclegad1 = gad = CreateGadget(CYCLE_KIND, gad, &ng,
        GTCY_Labels, ReverbLabels,
        GTCY_Active, 0,
        TAG_DONE);

    /* Set the Chorus */

    ng.ng_LeftEdge = 70;
    ng.ng_TopEdge = 110+topborder;
    ng.ng_Width = 145;
    ng.ng_Height = 15;
    ng.ng_GadgetText = "Chorus:";
    ng.ng_GadgetID = GAD_CYCLE2;
    ng.ng_Flags = NG_HIGHLABEL;
    cyclegad2 = gad = CreateGadget(CYCLE_KIND, gad, &ng,
        GTCY_Labels, ChorusLabels,
        GTCY_Active, 0,
        TAG_DONE);

    /* The Mute Gadget */

    ng.ng_TopEdge = 129+topborder;
    ng.ng_LeftEdge = 550;
    ng.ng_GadgetText = "Mute:";
    ng.ng_GadgetID = GAD_CHECKBOX1;
    checkgad1 = gad = CreateGadget(CHECKBOX_KIND, gad, &ng,
        GTCB_Checked, mutechecked,
        TAG_DONE);

    /* The Solo Gadget */

    ng.ng_TopEdge = 149+topborder;
    ng.ng_LeftEdge = 550;
    ng.ng_GadgetText = "Solo:";
    ng.ng_GadgetID = GAD_CHECKBOX2;
    checkgad2 = gad = CreateGadget(CHECKBOX_KIND, gad, &ng,
        GTCB_Checked, solochecked,
        TAG_DONE);

    /* The Mono Gadget */

    ng.ng_TopEdge = 169+topborder;
    ng.ng_LeftEdge = 550;
    ng.ng_GadgetText = "Mono:";
    ng.ng_GadgetID = GAD_MONO;
    monogad = gad = CreateGadget(CHECKBOX_KIND, gad, &ng,
        GTCB_Checked, monochecked,
        TAG_DONE);

    /* The DrumKit Gadget */

    ng.ng_TopEdge = 189+topborder;
    ng.ng_LeftEdge = 550;
    ng.ng_GadgetText = "Drum:";
    ng.ng_GadgetID = GAD_DRUM;
    drumgad = gad = CreateGadget(CHECKBOX_KIND, gad, &ng,
        GTCB_Checked, drumchecked,
        TAG_DONE);

     /* The Midi Enabled Gadget */

    ng.ng_TopEdge = 159+topborder;
    ng.ng_LeftEdge = 150;
    ng.ng_GadgetText = "Midi On:";
    ng.ng_GadgetID = GAD_MIDI;
    midigad = gad = CreateGadget(CHECKBOX_KIND, gad, &ng,
        GTCB_Checked, midichecked,
        TAG_DONE);

 /*

    ng.ng_TopEdge = 69+topborder;
    ng.ng_LeftEdge = 70;
    ng.ng_GadgetText = "Solo:";
    ng.ng_GadgetID = GAD_CHECKBOX2;
    checkgad = gad = CreateGadget(CHECKBOX_KIND, gad, &ng,
        GTCB_Checked, foochecked,
        TAG_DONE);



    if (gad)
        ng.ng_TopEdge += gad->Height;

    ng.ng_GadgetText = "Bar:";
    ng.ng_GadgetID = GAD_CHECKBOX2;
    gad = CreateGadget(CHECKBOX_KIND, gad, &ng,
        GTCB_Checked, FALSE,
        TAG_DONE);

    ng.ng_TopEdge = 99+topborder;
    ng.ng_Width = 200;
    ng.ng_GadgetText = "Type:";
    ng.ng_GadgetID = GAD_INTEGER;
    integergad = gad = CreateGadget(INTEGER_KIND, gad, &ng,
        GTIN_Number, 54321,
        GTIN_MaxChars, 10,
        TAG_DONE);
    */

    /* Channel Selector Slider */

    ng.ng_TopEdge = 29+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Channel:";
    ng.ng_GadgetID = GAD_CHANNEL;
    channelgad = gad = CreateGadget(SLIDER_KIND, gad, &ng,
        GTSL_Min, 1,
        GTSL_Max, 16,
        GTSL_Level, MC303_CHANNEL,
        GTSL_LevelFormat, "%2ld",
        GTSL_LevelPlace, PLACETEXT_RIGHT,
        GTSL_MaxLevelLen, 2,
        GA_IMMEDIATE, TRUE,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

    /* Patch Selector Slider */

    ng.ng_TopEdge = 49+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Patch:";
    ng.ng_GadgetID = GAD_PATCH;
    patchgad = gad = CreateGadget(SCROLLER_KIND, gad, &ng,
        GTSC_Top, 0,
        GTSC_Total, NUM_PATCHES,
        GTSC_Visible, 1,
        GTSC_Arrows, 13,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

     /* Portamento Selector Slider */

    ng.ng_TopEdge = 69+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Portamo:";
    ng.ng_GadgetID = GAD_PORT;
    portgad = gad = CreateGadget(SLIDER_KIND, gad, &ng,
        GTSL_Min, 0,
        GTSL_Max, 127,
        GTSL_Level, 0,
        GTSL_LevelFormat, "%2ld",
        GTSL_LevelPlace, PLACETEXT_RIGHT,
        GTSL_MaxLevelLen, 3,
        GA_IMMEDIATE, TRUE,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

    /* Modulation Selector Slider */

    ng.ng_TopEdge = 89+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Mod:";
    ng.ng_GadgetID = GAD_MOD;
    modgad = gad = CreateGadget(SLIDER_KIND, gad, &ng,
        GTSL_Min, 0,
        GTSL_Max, 127,
        GTSL_Level, 0,
        GTSL_LevelFormat, "%2ld",
        GTSL_LevelPlace, PLACETEXT_RIGHT,
        GTSL_MaxLevelLen, 3,
        GA_IMMEDIATE, TRUE,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

     /* Attack Selector Slider */

    ng.ng_TopEdge = 109+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Attack:";
    ng.ng_GadgetID = GAD_ATTACK;
    attackgad = gad = CreateGadget(SLIDER_KIND, gad, &ng,
        GTSL_Min, 0,
        GTSL_Max, 127,
        GTSL_Level, 0,
        GTSL_LevelFormat, "%2ld",
        GTSL_LevelPlace, PLACETEXT_RIGHT,
        GTSL_MaxLevelLen, 3,
        GA_IMMEDIATE, TRUE,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

    /* Decay Selector Slider */

    ng.ng_TopEdge = 129+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Decay:";
    ng.ng_GadgetID = GAD_DECAY;
    decaygad = gad = CreateGadget(SLIDER_KIND, gad, &ng,
        GTSL_Min, 0,
        GTSL_Max, 127,
        GTSL_Level, 0,
        GTSL_LevelFormat, "%2ld",
        GTSL_LevelPlace, PLACETEXT_RIGHT,
        GTSL_MaxLevelLen, 3,
        GA_IMMEDIATE, TRUE,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

    /* Release Selector Slider */

    ng.ng_TopEdge = 149+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Release:";
    ng.ng_GadgetID = GAD_RELEASE;
    releasegad = gad = CreateGadget(SLIDER_KIND, gad, &ng,
        GTSL_Min, 0,
        GTSL_Max, 127,
        GTSL_Level, 0,
        GTSL_LevelFormat, "%2ld",
        GTSL_LevelPlace, PLACETEXT_RIGHT,
        GTSL_MaxLevelLen, 3,
        GA_IMMEDIATE, TRUE,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

    /* Rate Selector Slider */

    ng.ng_TopEdge = 169+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Rate:";
    ng.ng_GadgetID = GAD_RATE;
    rategad = gad = CreateGadget(SLIDER_KIND, gad, &ng,
        GTSL_Min, 0,
        GTSL_Max, 127,
        GTSL_Level, 0,
        GTSL_LevelFormat, "%2ld",
        GTSL_LevelPlace, PLACETEXT_RIGHT,
        GTSL_MaxLevelLen, 3,
        GA_IMMEDIATE, TRUE,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

    /* Delay Selector Slider */

    ng.ng_TopEdge = 189+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Delay:";
    ng.ng_GadgetID = GAD_DELAY;
    delaygad = gad = CreateGadget(SLIDER_KIND, gad, &ng,
        GTSL_Min, 0,
        GTSL_Max, 127,
        GTSL_Level, 0,
        GTSL_LevelFormat, "%2ld",
        GTSL_LevelPlace, PLACETEXT_RIGHT,
        GTSL_MaxLevelLen, 3,
        GA_IMMEDIATE, TRUE,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

    /* Attack Selector Slider */

    ng.ng_TopEdge = 209+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Depth:";
    ng.ng_GadgetID = GAD_DEPTH;
    depthgad = gad = CreateGadget(SLIDER_KIND, gad, &ng,
        GTSL_Min, 0,
        GTSL_Max, 127,
        GTSL_Level, 0,
        GTSL_LevelFormat, "%2ld",
        GTSL_LevelPlace, PLACETEXT_RIGHT,
        GTSL_MaxLevelLen, 3,
        GA_IMMEDIATE, TRUE,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

    /* CutOff Selector Slider */

    ng.ng_TopEdge = 229+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Cut Off:";
    ng.ng_GadgetID = GAD_CUTOFF;
    cutoffgad = gad = CreateGadget(SLIDER_KIND, gad, &ng,
        GTSL_Min, 0,
        GTSL_Max, 127,
        GTSL_Level, 0,
        GTSL_LevelFormat, "%2ld",
        GTSL_LevelPlace, PLACETEXT_RIGHT,
        GTSL_MaxLevelLen, 3,
        GA_IMMEDIATE, TRUE,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

    /* RES Selector Slider */

    ng.ng_TopEdge = 249+topborder;
    ng.ng_LeftEdge = 315;
    ng.ng_Height = 12;
    ng.ng_GadgetText = "Res:";
    ng.ng_GadgetID = GAD_RES;
    resgad = gad = CreateGadget(SLIDER_KIND, gad, &ng,
        GTSL_Min, 0,
        GTSL_Max, 127,
        GTSL_Level, 0,
        GTSL_LevelFormat, "%2ld",
        GTSL_LevelPlace, PLACETEXT_RIGHT,
        GTSL_MaxLevelLen, 3,
        GA_IMMEDIATE, TRUE,
        GA_RELVERIFY, TRUE,
        TAG_DONE);

    /*
    ng.ng_TopEdge = 133+topborder;
    ng.ng_GadgetText = "Channel:";
    ng.ng_GadgetID = GAD_SCROLLER;
    gad = CreateGadget(SCROLLER_KIND, gad, &ng,
        GTSC_Top, 5,
        GTSC_Total, 30,
        GTSC_Visible, 10,
        GTSC_Arrows, 13,
        GA_RELVERIFY, TRUE,
        TAG_DONE);


    ng.ng_TopEdge = 149+topborder;
    ng.ng_Height = 8;
    ng.ng_GadgetText = "Number:";
    gad = CreateGadget(NUMBER_KIND, gad, &ng,
        GTNM_Number, 314159,
        TAG_DONE);
    */


    /* Text to describe the patch */

    ng.ng_TopEdge = 49+topborder;
    ng.ng_LeftEdge = 470;
    ng.ng_GadgetText = "";
    ng.ng_GadgetID = GAD_PATCHTEXT;
    patchtextgad = gad = CreateGadget(TEXT_KIND, gad, &ng,
        GTTX_Text, PatchLabels[0],
        TAG_DONE);

    /*  Set The Mode  */

    ng.ng_LeftEdge = 170;
    ng.ng_TopEdge = 35+topborder;
    ng.ng_GadgetID = GAD_MODE;
    modegad = gad = CreateGadget(MX_KIND, gad, &ng,
        GTMX_Labels, ModeLabels,
        GTMX_Active, 1,
        GTMX_Spacing, 4,
        TAG_DONE);

    /*
    NewList(&lh);
    index = 0;
    while (MonthLabels[index])
    {
        node = (struct Node *)AllocRemember(&RKey, sizeof(struct Node), MEMF_CLEAR);
        node->ln_Name = MonthLabels[index++];
        AddTail(&lh, node);
    }

    */

    /* Here's a string gadget to be attached to the listview: */
    /*
    ng.ng_Width = 150;
    ng.ng_Height = 14;
    ng.ng_GadgetText = NULL;
    ng.ng_GadgetID = GAD_LVSTRING;
    stringgad = gad = CreateGadget(STRING_KIND, gad, &ng,
        GTST_MaxChars, 50,
        TAG_DONE);

    ng.ng_LeftEdge = 130;
    ng.ng_TopEdge = 19+topborder;
    ng.ng_Width = 150;
    ng.ng_Height = 57;
    ng.ng_GadgetText = "Months:";
    ng.ng_GadgetID = GAD_LISTVIEW;
    ng.ng_Flags = NG_HIGHLABEL|PLACETEXT_LEFT;
    lvgad = gad = CreateGadget(LISTVIEW_KIND, gad, &ng,
        GTLV_Labels, &lh,
        GTLV_Top, 1,
        LAYOUTA_SPACING, 1,
        GTLV_ShowSelected, stringgad,
        GTLV_Selected, 3,
        GTLV_ScrollWidth, 18,
        TAG_DONE);

    ng.ng_LeftEdge = 320;
    ng.ng_TopEdge = 49+topborder;
    ng.ng_Width = 40;
    ng.ng_Height = 75;
    ng.ng_GadgetText = "Colors";
    ng.ng_GadgetID = GAD_PALETTE;
    ng.ng_Flags = NG_HIGHLABEL;

    gad = CreateGadget(PALETTE_KIND, gad, &ng,
        GTPA_Depth, mysc->BitMap.Depth,
        GTPA_Color, 1,
        GTPA_ColorOffset, 0,
        GTPA_IndicatorHeight, 15,
        TAG_DONE);
    */

    return(gad);
}

/*------------------------------------------------------------------------*/

/*/ HandleGadgetEvent()
 *
 * Function to handle a GADGETUP or GADGETDOWN event.  For toolkit gadgets,
 * it is possible to use this function to handle MOUSEMOVEs as well, with
 * little or no work.
 *
 */

BOOL HandleGadgetEvent( struct Gadget *gad, UWORD code)
{
    BOOL terminated = FALSE;

    switch (gad->GadgetID)
    {
       case GAD_MODE:
            /* MX gadgets report the number (0..n-1)
             * of the new active label in the code
             * field:
             */
            if (code==1)
            {
                PutMidiStream(source,NULL,SOUND_MODULE_MODE,(long)sizeof SOUND_MODULE_MODE, (long)sizeof SOUND_MODULE_MODE);
                MC303[MC303_DATA][MC303_MODE]=FALSE;
            }
            else
            {
                PutMidiStream(source,NULL,NORMAL_MODE,(long)sizeof NORMAL_MODE, (long)sizeof NORMAL_MODE);
                MC303[MC303_DATA][MC303_MODE]=TRUE;
            };
            break;

       case GAD_CHANNEL:
            MC303_CHANNEL = (WORD)code;
            update(); /* Update the landscape to match the MC303[][] array*/
            break;

       case GAD_PATCH:
            MC303[MC303_CHANNEL-1][MC303_PATCH]=code;
            send_patch(code);
            /* When we send a patch all our synthises data is reset to 0, so this should fix that up */
            /* Send the Portamo */
            send_port(MC303[MC303_CHANNEL-1][MC303_PORT]);
            /* Send the Mod. */
            send_mod(MC303[MC303_CHANNEL-1][MC303_MOD]);
            /* Send the Attack */
            send_attack(MC303[MC303_CHANNEL-1][MC303_ATTACK]);
            /* Send the Decay */
            send_decay(MC303[MC303_CHANNEL-1][MC303_DECAY]);
            /* Send the Release */
            send_release(MC303[MC303_CHANNEL-1][MC303_RELEASE]);
            /* Send the Rate */
            send_rate(MC303[MC303_CHANNEL-1][MC303_RATE]);
            /* Send the Delay */
            send_delay(MC303[MC303_CHANNEL-1][MC303_DELAY]);
            /* Send the Depth */
            send_depth(MC303[MC303_CHANNEL-1][MC303_DEPTH]);
            /* Send the Cutoff */
            send_cutoff(MC303[MC303_CHANNEL-1][MC303_CUTOFF]);
            /* Send the Res. */
            send_res(MC303[MC303_CHANNEL-1][MC303_RES]);
            /* Refresh everything */
            update();
            break;

       case GAD_CHECKBOX1:
           /* Controls channel muting */
            if (!(gad->Flags & SELECTED))
            {
                MC303[MC303_CHANNEL-1][MC303_MUTE] = FALSE;
                /* Send SYSX data to make it so */
                if (MC303[MC303_DATA][MC303_MODE]==FALSE)
                    PutMidiStream(source,NULL,SM_ON_PART[MC303_CHANNEL-1],(long)sizeof SM_ON_PART[MC303_CHANNEL-1], (long)sizeof SM_ON_PART[MC303_CHANNEL-1]);
            }
            else
            {
                MC303[MC303_CHANNEL-1][MC303_MUTE] = TRUE;
                MC303[MC303_CHANNEL-1][MC303_SOLO] = FALSE;
                /* Make sure that the SOLO button is off */
                GT_SetGadgetAttrs(checkgad2, mywin, NULL, GTCB_Checked, FALSE, TAG_DONE);
                /* Send the SYSX data to make it so */
                if (MC303[MC303_DATA][MC303_MODE]==FALSE)
                PutMidiStream(source,NULL,SM_OFF_PART[MC303_CHANNEL-1],(long)sizeof SM_OFF_PART[MC303_CHANNEL-1], (long)sizeof SM_OFF_PART[MC303_CHANNEL-1]);
            }
            break;

        case GAD_CHECKBOX2:
            /* Controls the Channel Soloing */
            if (!(gad->Flags & SELECTED))
            {
                MC303[MC303_CHANNEL][MC303_SOLO] = FALSE;
            }
            else
            {
                MC303[MC303_CHANNEL][MC303_MUTE] = FALSE;
                MC303[MC303_CHANNEL][MC303_SOLO] = TRUE;
                /* Make sure that the MUTE button is off */
                GT_SetGadgetAttrs(checkgad1, mywin, NULL, GTCB_Checked, FALSE, TAG_DONE);
            }
            break;

        case GAD_CYCLE1:
            PutMidiStream(source,NULL,REVERB[code],(long)sizeof REVERB[code], (long)sizeof REVERB[code]);
            break;

        case GAD_CYCLE2:
            PutMidiStream(source,NULL,CHORUS[code],(long)sizeof CHORUS[code], (long)sizeof CHORUS[code]);
            break;

        case GAD_TESTTONE:
            if (!(TONE_ON))
            {
                buffer[0] = (MS_NOTEON | MC303_CHANNEL-1);
                buffer[1] = MIDDLEC;
                buffer[2] = DEFAULTVELOCITY;
                TONE_ON=TRUE;
            }
            else
            {
                buffer[0] = (MS_NOTEOFF | MC303_CHANNEL-1);
                buffer[1] = MIDDLEC;
                buffer[2] = DEFAULTVELOCITY;
                TONE_ON=FALSE;
            }
            PutMidiStream(source,NULL,buffer,3,3);
            break;

        case GAD_MONO:
            if (MC303[MC303_CHANNEL-1][MC303_MONO])
            {
                buffer[0] = (MS_MODE | MC303_CHANNEL-1);
                buffer[1] = MM_POLY;
                buffer[2] = 0;
                PutMidiStream(source,NULL,buffer,3,3);
                MC303[MC303_CHANNEL-1][MC303_MONO] = FALSE;
            }
            else
            {
                buffer[0] = (MS_CTRL | MC303_CHANNEL-1);
                buffer[1] = 126;
                buffer[2] = 1;
                PutMidiStream(source,NULL,buffer,3,3);
                MC303[MC303_CHANNEL-1][MC303_MONO] = TRUE;
            }
            break;

        case GAD_SAVE:
            save();
            break;

        case GAD_LOAD:
            load();
            update();
            break;

        case GAD_MIDI:
            if (midichecked)
            {
                close_midi();
                midichecked=FALSE;
            }
            else
            {
                open_midi();
                midichecked=TRUE;
            }
            break;

         case GAD_DRUM:
             send_drum(code);
             break;

         case GAD_PORT:
             send_port(code);
             break;

         case GAD_CUTOFF:
             send_cutoff(code);
             break;

         case GAD_RES:
             send_res(code);
             break;

         case GAD_ATTACK:
             send_attack(code);
             break;

         case GAD_DECAY:
             send_decay(code);
             break;

         case GAD_RELEASE:
             send_release(code);
             break;

         case GAD_RATE:
             send_rate(code);
             break;

         case GAD_DEPTH:
             send_depth(code);
             break;

         case GAD_DELAY:
             send_delay(code);
             break;

         case GAD_SEND:
             send();
             break;

    }
    return(terminated);
}

/*------------------------------------------------------------------------*/
/***********************
**         MAIN       **
***********************/

int main (void)

{
    struct IntuiMessage *imsg;
    struct Gadget *gad;
    ULONG imsgClass;
    UWORD imsgCode;
    UWORD topborder;
    int loop1, loop2;
    
    terminated = FALSE;
    MC303_CHANNEL=1;

    /* Setup the array to match the default MC303 */

    for (loop1 = 0; loop1 < 18; loop1++)
    {
        for (loop2 = 0; loop2 < 255; loop2++)
        {
            MC303[loop1][loop2] = 64;
        }
        MC303[loop1][MC303_PATCH] = 0;
        MC303[loop1][MC303_MUTE] = FALSE;
        MC303[loop1][MC303_DELAY] = 0;
        MC303[loop1][MC303_RATE] = 0;
        MC303[loop1][MC303_DEPTH] = 0;
        MC303[loop1][MC303_PORT] = 0;
    }

    MC303[MC303_DATA][MC303_DRUM11]=FALSE;
    MC303[MC303_DATA][MC303_MODE]=FALSE;
    MC303[MC303_DATA][MC303_VERS] = 1;

    if (!(GfxBase = (struct GfxBase *)
        OpenLibrary("graphics.library", 36L)))
        bail_out(20, "Requires V36 graphics.library");

    if (!(IntuitionBase = (struct IntuitionBase *)
        OpenLibrary("intuition.library", 36L)))
        bail_out(20, "Requires V36 intuition.library");

    if (!(GadToolsBase = OpenLibrary("gadtools.library", 36L)))
        bail_out(20, "Requires V36 gadtools.library");

    /* Open Haze 8 font: (Cause I like that font) */


    if (!(font = OpenFont(&Haze80)))
        bail_out(20, "Failed to open font");

    if (!(mysc = LockPubScreen(NULL)))
        bail_out(20, "Couldn't lock default public screen");

    if (!(vi = GetVisualInfo(mysc,
        TAG_DONE)))
        bail_out(20, "GetVisualInfo() failed");

    topborder = mysc->WBorTop + (mysc->Font->ta_YSize + 1);

    open_midi();

    /* Send the default setup */
    send();

    /* Build and layout menus: */

    /*
    if (!(menu = CreateMenus(mynewmenu,
        GTMN_FrontPen, 0,
        TAG_DONE)))
        bail_out(20, "CreateMenus() failed");

    if (!LayoutMenus(menu, vi,
        TAG_DONE))
        bail_out(20, "LayoutMenus() failed");
    */

    if (!CreateAllGadgets(&glist, vi, topborder))
    {
        bail_out(20, "CreateAllGadgets() failed");
    }

    /* I could equally well use the {WA_Gadgets, glist} TagItem */
    mynewwin.FirstGadget = glist;

    /* I've actually put the inner-height in mynewwin.Height, so
     * I'll override that value with a W_INNERHEIGHT:
     */
    /* Open the window: */
    if (!(mywin = OpenWindowTags(&mynewwin,
        WA_InnerHeight, mynewwin.Height,
        WA_AutoAdjust, TRUE,
        WA_PubScreen, mysc,
        TAG_DONE)))
        bail_out(20, "OpenWindow() failed");

    /* After window is open, we must call this GadTools refresh
     * function.
     */
    GT_RefreshWindow(mywin, NULL);

    /* Set the gadgets to equal the MC303 array */
    update();

    while (!terminated)
    {
        Wait (1 << mywin->UserPort->mp_SigBit);
        /* GT_GetIMsg() returns a cooked-up IntuiMessage with
         * more friendly information for complex gadget classes.  Use
         * it wherever you get IntuiMessages:
         */
        while ((!terminated) && (imsg = GT_GetIMsg(mywin->UserPort)))
        {
            imsgClass = imsg->Class;
            imsgCode = imsg->Code;
            /* Presuming a gadget, of course, but no harm... */
            gad = (struct Gadget *)imsg->IAddress;
            /* Use the toolkit message-replying function here... */
            GT_ReplyIMsg(imsg);

            switch (imsgClass)
            {

                /*
                case MENUPICK:
                    terminated = HandleMenuEvent(imsgCode);
                    break;


                case MOUSEMOVE:
                    terminated = HandleMouseMove(gad, imsgCode);
                    break;
                */

                case GADGETUP:
                    terminated = HandleGadgetEvent(gad, imsgCode);
                    break;

                case GADGETDOWN:
                    terminated = HandleGadgetEvent(gad, imsgCode);
                    break;

                case CLOSEWINDOW:
                    terminated = TRUE;

                    /* You must use GT_BeginRefresh() where you would
                     * normally have your first BeginRefresh()
                     */

                    GT_BeginRefresh(mywin);
                    GT_EndRefresh(mywin, TRUE);
                    bail_out (0,NULL);
                    break;

            }

        }
    }
    bail_out(0, NULL);
return 0;
};

