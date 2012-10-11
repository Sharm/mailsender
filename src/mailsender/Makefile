
COMPILER=g++


#CFLAGS= -Wall -ggdb -O1 -MD -DLINUX
CFLAGS= -Wall -O2 -MD
LIBS= -lSockets -lpthread
ILFLAGS+= -I/usr/include -I/usr/Include/c++/4.3 -I../../include/sockets \
          -L/usr/local/lib -L../../lib

TARGET = mailsender
BIN_PATH = ../../bin


SOURCE_FILES= 	\
	BaseLog.cpp\
	BaseConfig.cpp\
	Config.cpp	\
	Log.cpp	\
	main.cpp\
	ClientHandler.cpp	\
	ClientSocket.cpp \

HEADER_FILES= 	\
	BaseLog.h\
	BaseConfig.h\
	Define.h\
	Config.h	\
	Log.h	\
	ClientHandler.h	\
	ClientSocket.h \

OBJS=$(patsubst %.cpp, %.o,$(SOURCE_FILES))

.PHONY:all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(COMPILER) $(CFLAGS) $(ILFLAGS) $(GLOBALS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(COMPILER) $(CFLAGS) $(ILFLAGS) $(GLOBALS) -o $@ -c $<

.PHONY:clean
clean:
	 -rm -f $(OBJS) $(TARGET)

.PHONY:install
install:	
		cp $(TARGET) $(BIN_PATH) #&& \
##		cp $(HEADER) $(INCLUDE_PATH)

