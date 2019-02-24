# @Author: haidee
# @Date:   2018-07-13 Fri
# @Email:  1003261954@qq.com
# @Filename: Makefile
# @Last modified by:   haidee
# @Last modified time: 2018-08-23 Thu


PRO_GCC  =  gcc

OUTPUT   =  ./output/

PRO_NAME =  ./Park

MY_INC   =  ./inc/

MY_SRC   =  ./src/

MY_LIB   =  -lsqlite3 -lncursesw -pthread

ADDINC   =  -I./inc/

OBJ      =  $(OUTPUT)main.o $(OUTPUT)user.o \
            $(OUTPUT)Display.o \
            $(OUTPUT)Database.o $(OUTPUT)Communication.o

$(PRO_NAME):$(OBJ)
	$(PRO_GCC) $(OBJ) $(ADDINC) $(MY_LIB) -o $(PRO_NAME) -Wall

$(OUTPUT)Display.o : $(MY_SRC)Display.c $(MY_INC)Display.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)Display.c -c -o $(OUTPUT)Display.o $(ADDINC)

$(OUTPUT)Database.o : $(MY_SRC)Database.c $(MY_INC)Database.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)Database.c -c -o $(OUTPUT)Database.o $(ADDINC)

$(OUTPUT)Communication.o : $(MY_SRC)Communication.c $(MY_INC)Communication.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)Communication.c -c -o $(OUTPUT)Communication.o $(ADDINC)

$(OUTPUT)user.o : $(MY_SRC)user.c $(MY_INC)user.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)user.c -c -o $(OUTPUT)user.o $(ADDINC) $(MY_LIB)

$(OUTPUT)main.o : main.c $(MY_INC)includes.h
	$(PRO_GCC) main.c -c -o $(OUTPUT)main.o $(ADDINC) $(MY_LIB)

clean :
	@rm $(PRO_NAME) $(OBJ)

##   <-----------------------   end of file   ----------------------->   ##
