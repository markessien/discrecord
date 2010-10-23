
#define READERRREC    0x01
#define CDRPARMS      0x0D
#define CDRAUDIOCTL   0x0E
#define CDRCAPS       0x2A
#define CDP_READCDR      0x0001     // can read CD-R
#define CDP_READCDE      0x0002     // can read CD-E
#define CDP_METHOD2      0x0003     // can read CD-R wriiten via method 2
#define CDP_WRITECDR     0x0004     // can write CD-R
#define CDP_WRITECDE     0x0005     // can write CD-E
#define CDP_AUDIOPLAY    0x0006     // can play audio
#define CDP_COMPOSITE    0x0007     // composite audio/video stream
#define CDP_DIGITAL1     0x0008     // digital output (IEC958) on port 1
#define CDP_DIGITAL2     0x0009     // digital output (IEC958) on port 2
#define CDP_M2FORM1      0x000A     // reads Mode 2 Form 1 (XA) format
#define CDP_M2FORM2      0x000B     // reads Mode 2 Form 2 format
#define CDP_MULTISES     0x000C     // reads multi-session or Photo-CD
#define CDP_CDDA         0x000D     // supports cd-da
#define CDP_STREAMACC    0x000E     // supports "stream is accurate"
#define CDP_RW           0x000F     // can return R-W info
#define CDP_RWCORR       0x0010     // returns R-W de-interleaved and err.
                                    // corrected
#define CDP_C2SUPP       0x0011     // C2 error pointers
#define CDP_ISRC         0x0012     // can return the ISRC info
#define CDP_UPC          0x0013     // can return the Media Catalog Number
#define CDP_CANLOCK      0x0014     // prevent/allow cmd. can lock the media
#define CDP_LOCKED       0x0015     // current lock state (TRUE = LOCKED)
#define CDP_PREVJUMP     0x0016     // prevent/allow jumper state
#define CDP_CANEJECT     0x0017     // drive can eject disk
#define CDP_MECHTYPE     0x0018     // type of disk loading supported
#define CDP_SEPVOL       0x0019     // independent audio level for channels
#define CDP_SEPMUTE      0x001A     // independent mute for channels
#define CDP_SDP          0x001B     // supports disk present (SDP)
#define CDP_SSS          0x001C     // Software Slot Selection
#define CDP_MAXSPEED     0x001D     // maximum supported speed of drive
#define CDP_NUMVOL       0x001E     // number of volume levels
#define CDP_BUFSIZE      0x001F     // size of output buffer
#define CDP_CURRSPEED    0x0020     // current speed of drive
#define CDP_SPM          0x0021     // "S" units per "M" (MSF format)
#define CDP_FPS          0x0022     // "F" units per "S" (MSF format)
#define CDP_INACTMULT    0x0023     // inactivity multiplier ( x 125 ms)
#define CDP_MSF          0x0024     // use MSF format for READ TOC cmd
#define CDP_OVERLAP      0x0025     // number of overlap frames for jitter
#define CDP_JITTER       0x0026     // number of frames to check for jitter
#define CDP_READMODE     0x0027     // mode to attempt jitter corr.
#define CDP_MAXWSPEED    0x0028     // maximum supported write speed of drive
#define CDP_CURRWSPEED    0x0029     // current write speed of drive

/*
 * defines for GETCDHAND  readType
 *
 */
#define CDR_ANY          0x00       // unknown
#define CDR_ATAPI1       0x01       // ATAPI per spec
#define CDR_ATAPI2       0x02       // alternate ATAPI
#define CDR_READ6        0x03       // using SCSI READ(6)
#define CDR_READ10       0x04       // using SCSI READ(10)
#define CDR_READ_D8      0x05       // using command 0xD8 (Plextor?)
#define CDR_READ_D4      0x06       // using command 0xD4 (NEC?)
#define CDR_READ_D4_1    0x07       // 0xD4 with a mode select
#define CDR_READ10_2     0x08       // different mode select w/ READ(10)

/*
 * defines for the read mode (CDP_READMODE)
 */
#define CDRM_NOJITTER      0x00     // never jitter correct
#define CDRM_JITTER        0x01     // always jitter correct
#define CDRM_JITTERONERR   0x02     // jitter correct only after a 


#define X1 176 // speed in kb/sec of 1fach 

// Return values
#define SCSINoError 0         /* No Error */
#define SCSINoAspi -1         /* No Aspi Manager Installed */
#define SCSIBusy -2           /* Aspi Module is busy (this should never occur */
#define SCSIAspiErr -3        /* Undefined Aspi error */
#define SCSINoMem -4          /* Can't allocate memory */
#define SCSINoDevice -5       /* The device is not installed */
#define SCSIAspiInval -6      /* Invalid ASPI request */
#define SCSINoAdapter -7      /* Invalid Host Adapter Number */
#define SCSIAbort -8          /* ASPI request aborted by Host */
#define SCSISelTimeout -9     /* Selection Timeout */
#define SCSIDataOverrun -10   /* Data over-run/under-run */
#define SCSIBusFree -11       /* Unexpected Bus Free */
#define SCSIBusFail -12       /* Target bus phase sequence failure */
#define SCSITargetBusy -13    /* The specified Target/LUN is busy */
#define SCSIReservation -14   /* Reservation conflict */
#define SCSINotReady -15      /* lun cannot be accessed */
#define SCSIMedium -16        /* Medium Error */
#define SCSIHardware -17      /* Non recoverable hardware error */
#define SCSIIllegalReq -18    /* Illegal Request */
#define SCSIUnitAttention -19 /* Unit Attention */
#define SCSIDataProtect -20   /* The Block is protected */
#define SCSIBlankCheck -21    /* Encounterd non blank data */
#define SCSITargetAbort -22   /* The Target Aborted the command */
#define SCSIVolOverflow -23   /* Volume overflow */
#define SCSIMiscompare -24    /* Source and data did nor match */
#define SCSIIOErr -25         /* An IO Error of unknown type */
#define SCSILockLMem -26      /* Can not lock local memory */
#define SCSILockGMem -27      /* Can not lock global memory */
#define SCSIFatal    -28      /* Fatal Error - unemploy the programmer :-) */
#define SCSINoChannel -29     /* The logical channel is not initialized */
#define SCSINotActive -30     /* The logical channel is not active */
#define SCSIChannelOverflow -31 /* Logical Channel overflow */
#define SCSIStreamerInUse -32 /* streamer is already configured for a channel */
#define SCSIBlockLimit -33    /* Illegal blocksize for a streamer */
#define SCSIOffset -34        /* Illegal offset allowed for this operation */
#define SCSIPosition -35      /* Illegal position for this operarion */
#define SCSIBlockLen -36      /* Illegal block length for this operation */
#define SCSIEndOfMedium -37   /* End of Medium detected, not really an error */
#define SCSINoModePage -38
#define SCSINoSPTI -39


#define  MAXIDLEN   64
#define  DEFWAITLEN    10000
