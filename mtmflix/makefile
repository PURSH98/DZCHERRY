CC = gcc
OBJS = mtmflix.o user.o series.o utilities.o
EXEC = prog
DEBUG_FLAG = # now empty, assign -g for debug 
COMP_FLAG = -std=c99 -Wall -Werror -pedantic-errors -DNDEBUG
LIN_FLAG = -L. -lmtm -lmtm_ex3
$(EXEC) : $(OBJS)
$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
mtmflix.o : mtmflix.c mtmflix.h user.h series.h utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c $(LIN_FLAG)
user.o : user.c user.h utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c $(LIN_FLAG)
series.o : series.c series.h utitilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c $(LIN_FLAG)
utilities.o : utilities.c utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c $(LIN_FLAG)
clean:
	rm -f $(OBJS) $(EXEC)