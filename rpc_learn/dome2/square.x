struct square_in {		/* 输入（参数） */
  long	arg1;
};

struct square_out {		/* 输出（结果） */
  long	res1;
};

program SQUARE_PROG {
    version SQUARE_VERS {
	square_out	SQUAREPROC(square_in) = 1; /* 程序编号= 1 */
    } = 1;				/* 版本号 */
} = 0x31230000;			/*程序编号 */
