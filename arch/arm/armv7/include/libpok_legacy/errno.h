typedef enum
{
		POK_ERRNO_OK                    =   0,
		POK_ERRNO_EINVAL                =   1,

		POK_ERRNO_UNAVAILABLE           =   2,
		POK_ERRNO_PARAM					=   3,
		POK_ERRNO_TOOMANY               =   5,
		POK_ERRNO_EPERM                 =   6,
		POK_ERRNO_EXISTS                =   7,

		POK_ERRNO_ERANGE                =   8,
		POK_ERRNO_EDOM                  =   9,
		POK_ERRNO_HUGE_VAL              =  10,

		POK_ERRNO_EFAULT                =  11,

		POK_ERRNO_THREAD                =  49,
		POK_ERRNO_THREADATTR            =  50,

		POK_ERRNO_TIME                 =  100,

		POK_ERRNO_PARTITION_ATTR        = 200,

		POK_ERRNO_PORT                 =  301,
		POK_ERRNO_NOTFOUND             =  302,
		POK_ERRNO_DIRECTION            =  303,
		POK_ERRNO_SIZE                 =  304,
		POK_ERRNO_DISCIPLINE           =  305,
		POK_ERRNO_PORTPART             =  307,
		POK_ERRNO_EMPTY                =  308,
		POK_ERRNO_KIND                 =  309,
		POK_ERRNO_FULL                 =  311,
		POK_ERRNO_READY                =  310,
		POK_ERRNO_TIMEOUT              =  250,
		POK_ERRNO_MODE                 =  251,

		/* Native thread is STOP()-ed or server thread is cancelled. */
		POK_ERRNO_CANCELLED            =  500,

		POK_ERRNO_PARTITION_MODE       =  601,

		POK_ERRNO_PARTITION            =  401
} pok_ret_t;