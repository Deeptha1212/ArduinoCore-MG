#ifndef ERRORS_H
#define ERRORS_H

#define SUCCESS          0      /* Operation completed success */

#ifndef EPERM
#define EPERM            1      /* Operation not permitted */
#endif

#ifndef ENOENT
#define ENOENT           2      /* No such file or directory */
#endif

#ifndef ESRCH
#define ESRCH            3      /* No such process */
#endif

#ifndef EINTR
#define EINTR            4      /* Interrupted system call */
#endif

#ifndef EIO
#define EIO              5      /* I/O error */
#endif

#ifndef ENXIO
#define ENXIO            6      /* No such device or address */
#endif

#ifndef E2BIG
#define E2BIG            7      /* Argument list too long */
#endif

#ifndef ENOEXEC
#define ENOEXEC          8      /* Exec format error */
#endif

#ifndef EBADF
#define EBADF            9      /* Bad file number */
#endif

#ifndef ECHILD
#define ECHILD          10      /* No child processes */
#endif

#ifndef EAGAIN
#define EAGAIN          11      /* Try again */
#endif

#ifndef ENOMEM
#define ENOMEM          12      /* Out of memory */
#endif

#ifndef EACCES
#define EACCES          13      /* Permission denied */
#endif

#ifndef EFAULT
#define EFAULT          14      /* Bad address */
#endif

#ifndef ENOTBLK
#define ENOTBLK         15      /* Block device required */
#endif

#ifndef EBUSY
#define EBUSY           16      /* Device or resource busy */
#endif

#ifndef EEXIST
#define EEXIST          17      /* File exists */
#endif

#ifndef EXDEV
#define EXDEV           18      /* Cross-device link */
#endif

#ifndef ENODEV
#define ENODEV          19      /* No such device */
#endif

#ifndef ENOTDIR
#define ENOTDIR         20      /* Not a directory */
#endif

#ifndef EISDIR
#define EISDIR          21      /* Is a directory */
#endif

#ifndef EINVAL
#define EINVAL          22      /* Invalid argument */
#endif

#ifndef ENFILE
#define ENFILE          23      /* File table overflow */
#endif

#ifndef EMFILE
#define EMFILE          24      /* Too many open files */
#endif

#ifndef ENOTTY
#define ENOTTY          25      /* Not a typewriter */
#endif

#ifndef ETXTBSY
#define ETXTBSY         26      /* Text file busy */
#endif

#ifndef EFBIG
#define EFBIG           27      /* File too large */
#endif

#ifndef ENOSPC
#define ENOSPC          28      /* No space left on device */
#endif

#ifndef ESPIPE
#define ESPIPE          29      /* Illegal seek */
#endif

#ifndef EROFS
#define EROFS           30      /* Read-only file system */
#endif

#ifndef EMLINK
#define EMLINK          31      /* Too many links */
#endif

#ifndef EPIPE
#define EPIPE           32      /* Broken pipe */
#endif

#ifndef EDOM
#define EDOM            33      /* Math argument out of domain of func */
#endif

#ifndef ERANGE
#define ERANGE          34      /* Math result not representable */
#endif

#ifndef EDEADLK
#define EDEADLK         35      /* Resource deadlock would occur */
#endif

#ifndef ENAMETOOLONG
#define ENAMETOOLONG    36      /* File name too long */
#endif

#ifndef ENOLCK
#define ENOLCK          37      /* No record locks available */
#endif

#ifndef ENOSYS
#define ENOSYS          38      /* Invalid system call number */
#endif

#ifndef ENOTEMPTY
#define ENOTEMPTY       39      /* Directory not empty */
#endif

#ifndef ELOOP
#define ELOOP           40      /* Too many symbolic links encountered */
#endif

#ifndef ETIMEDOUT
#define ETIMEDOUT       110     /* Connection timed out */
#endif

#ifndef ECONNREFUSED
#define ECONNREFUSED    111     /* Connection refused */
#endif

#ifndef EOWNERDEAD
#define EOWNERDEAD      130     /* Owner died */
#endif

#ifndef ENOTRECOVERABLE
#define ENOTRECOVERABLE 131     /* State not recoverable */
#endif

#ifndef ERFKILL
#define ERFKILL         132     /* Operation not possible due to RF-kill */
#endif

#ifndef EHWPOISON
#define EHWPOISON       133     /* Memory page has hardware error */
#endif

#ifndef SPI_BUSY
#define SPI_BUSY        134     /* SPI bus is busy */
#endif

#ifndef FIFO_NOT_EMPTY
#define FIFO_NOT_EMPTY  135     /* FIFO buffer not empty */
#endif

#ifndef FIFO_EMPTY
#define FIFO_EMPTY      136     /* FIFO buffer empty */
#endif

#ifndef BAUDRATE_MISSALIGNED
#define BAUDRATE_MISSALIGNED    137   /* Baudrate misaligned */
#endif

#ifndef ACK_NOTRECEIVED
#define ACK_NOTRECEIVED 138     /* Acknowledgment not received */
#endif

#ifndef I2C_BUS_BUSY
#define I2C_BUS_BUSY    139     /* I2C bus is busy */
#endif

#ifndef TX_FIFO_OVERFLOW
#define TX_FIFO_OVERFLOW    140 /* TX FIFO buffer overflow */
#endif

#ifndef ENOACK
#define ENOACK           141    /* No acknowledgment received for data */
#endif

#ifndef ENOACKDEV
#define ENOACKDEV        142    /* No acknowledgment received for slave address */
#endif

#ifndef ENOINST
#define ENOINST  143 /* Invalid UART instance */
#endif

#ifndef ECBUFFULL
#define ECBUFFULL  144 /* Software buffer is full */
#endif

#ifndef ECBUFEMPTY
#define ECBUFEMPTY  145 /* Software buffer is empty */
#endif

#ifndef EBUFEMPTY
#define EBUFEMPTY  146 /* Built-in buffer is empty */
#endif

#ifndef ELENEXCEED
#define ELENEXCEED       147   /* Length of data field exceeded */
#endif

#ifndef ECUSTOM1
#define ECUSTOM1         148   /* Custom error code */
#endif

#ifndef ECUSTOM2
#define ECUSTOM2         149   /* Custom error code */
#endif

#ifndef ECUSTOM3
#define ECUSTOM3         150   /* Custom error code */
#endif

#ifndef ECUSTOM4
#define ECUSTOM4         151   /* Custom error code */
#endif

#ifndef ECUSTOM5
#define ECUSTOM5         152   /* Custom error code */
#endif

#ifndef ECUSTOM6
#define ECUSTOM6         153   /* Custom error code */
#endif

#ifndef ECUSTOM7
#define ECUSTOM7         154   /* Custom error code */
#endif

#ifndef ECUSTOM8
#define ECUSTOM8         155   /* Custom error code */
#endif

#ifndef ECUSTOM9
#define ECUSTOM9         156   /* Custom error code */
#endif

#ifndef ECUSTOM10
#define ECUSTOM10        157   /* Custom error code */
#endif

#ifndef ECUSTOM11
#define ECUSTOM11        158   /* Custom error code */
#endif

#ifndef ECUSTOM12
#define ECUSTOM12        159   /* Custom error code */
#endif

#ifndef ECUSTOM13
#define ECUSTOM13        160   /* Custom error code */
#endif

#ifndef ECUSTOM14
#define ECUSTOM14        161   /* Custom error code */
#endif

#ifndef ECUSTOM15
#define ECUSTOM15        162   /* Custom error code */
#endif

#ifndef ECUSTOM16
#define ECUSTOM16        163   /* Custom error code */
#endif

#ifndef ECUSTOM17
#define ECUSTOM17        164   /* Custom error code */
#endif

#ifndef ECUSTOM18
#define ECUSTOM18        165   /* Custom error code */
#endif

#ifndef ECUSTOM19
#define ECUSTOM19        166   /* Custom error code */
#endif

#ifndef ECUSTOM20
#define ECUSTOM20        167   /* Custom error code */
#endif
/*
 * These should never be seen by user programs.  To return one of ERESTART*
 * codes, signal_pending() MUST be set.  Note that ptrace can observe these
 * at syscall exit tracing, but they will never be left for the debugged user
 * process to see.
 */
#define ERESTARTSYS     512
#define ERESTARTNOINTR  513
#define ERESTARTNOHAND  514     /* restart if no handler.. */
#define ENOIOCTLCMD     515     /* No ioctl command */
#define ERESTART_RESTARTBLOCK 516 /* restart by calling sys_restart_syscall */
#define EPROBE_DEFER    517     /* Driver requests probe retry */
#define EOPENSTALE      518     /* open found a stale dentry */

/* Defined for the NFSv3 protocol */
#define EBADHANDLE      521     /* Illegal NFS file handle */
#define ENOTSYNC        522     /* Update synchronization mismatch */
#define EBADCOOKIE      523     /* Cookie is stale */
#define ENOTSUPP        524     /* Operation is not supported */
#define ETOOSMALL       525     /* Buffer or request is too small */
#define ESERVERFAULT    526     /* An untranslatable error occurred */
#define EBADTYPE        527     /* Type not supported by server */
#define EJUKEBOX        528     /* Request initiated, but will not complete before timeout */
#define EIOCBQUEUED     529     /* iocb queued, will get completion event */

#endif /* ERRORS_H */
