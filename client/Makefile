# @Author: haidee
# @Date:   2018-07-13 Fri
# @Email:  1003261954@qq.com
# @Filename: Makefile
# @Last modified by:   haidee
# @Last modified time: 2018-08-22 Wed


PRO_GCC  =  arm-linux-gcc

OUTPUT   =  ./output/

PRO_NAME =  ./Park

MY_INC   =  ./inc/

MY_SRC   =  ./src/

MY_LIB   =  -L/home/haidee/lib/jpeg/lib -ljpeg \
            -L/home/haidee/lib/alsa/lib -lasound \
            -L/home/haidee/lib/sqlite3/lib -lsqlite3 \
            -pthread

ADDINC   =  -I./inc/ \
            -I/home/haidee/lib/jpeg/include \
	    -I/home/haidee/lib/alsa/include \
            -I/home/haidee/lib/sqlite3/include

OBJ      =  $(OUTPUT)main.o $(OUTPUT)user.o \
            $(OUTPUT)Database.o \
            $(OUTPUT)ascii-table.o $(OUTPUT)JPG.o $(OUTPUT)LCD.o \
            $(OUTPUT)Serial.o $(OUTPUT)RFID.o $(OUTPUT)video.o $(OUTPUT)audio.o

$(PRO_NAME):$(OBJ)
	$(PRO_GCC) $(OBJ) $(ADDINC) $(MY_LIB) -o $(PRO_NAME) -Wall

$(OUTPUT)ascii-table.o : $(MY_SRC)ascii-table.c $(MY_INC)ascii-table.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)ascii-table.c -c -o $(OUTPUT)ascii-table.o $(ADDINC)

$(OUTPUT)JPG.o : $(MY_SRC)JPG.c $(MY_INC)JPG.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)JPG.c -c -o $(OUTPUT)JPG.o $(ADDINC)

$(OUTPUT)LCD.o : $(MY_SRC)LCD.c $(MY_INC)LCD.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)LCD.c -c -o $(OUTPUT)LCD.o $(ADDINC)

$(OUTPUT)Serial.o : $(MY_SRC)Serial.c $(MY_INC)Serial.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)Serial.c -c -o $(OUTPUT)Serial.o $(ADDINC)

$(OUTPUT)RFID.o : $(MY_SRC)RFID.c $(MY_INC)RFID.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)RFID.c -c -o $(OUTPUT)RFID.o $(ADDINC)

$(OUTPUT)video.o : $(MY_SRC)video.c $(MY_INC)video.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)video.c -c -o $(OUTPUT)video.o $(ADDINC)

$(OUTPUT)audio.o : $(MY_SRC)audio.c $(MY_INC)audio.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)audio.c -c -o $(OUTPUT)audio.o $(ADDINC)

$(OUTPUT)Database.o : $(MY_SRC)Database.c $(MY_INC)Database.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)Database.c -c -o $(OUTPUT)Database.o $(ADDINC)

$(OUTPUT)user.o : $(MY_SRC)user.c $(MY_INC)user.h $(MY_INC)includes.h
	$(PRO_GCC) $(MY_SRC)user.c -c -o $(OUTPUT)user.o $(ADDINC)

$(OUTPUT)main.o : main.c $(MY_INC)includes.h
	$(PRO_GCC) main.c -c -o $(OUTPUT)main.o $(ADDINC) $(MY_LIB)

clean :
	@rm $(PRO_NAME) $(OBJ)

##   <-----------------------   end of file   ----------------------->   ##
