 
TEMPLATE = lib
CONFIG  += dll
TARGET = projectBase

#DESTDIR = $(GEOSEIS)/lib

#for app;
#TEMPLATE = app
#TARGET = geoseis
#DESTDIR = Debug


CONFIG += warn_off debug

# Input
HEADERS += baseinfo.h \
           basesema.h \
           basethread.h \
           comfun.h \
           diskmng.h \
           dtime.h \
           filemng.h \
           flexvar.h \
           logfile.h \
           nodemng.h \
           projectmng.h \
           sysdefine.h  
            
SOURCES += baseInfo.cpp \
           basesema.cpp \
           basethread.cpp \
           comfun.cpp \
           diskmng.cpp \
           dtime.cpp \
           filemng.cpp \
           #geoseis.cpp \
           logfile.cpp \
           nodemng.cpp \
	   sysdefine.cpp\
           projectmng.cpp  
