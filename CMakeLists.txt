CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT(backup)
SET (SRC_LIST 
	backup.cpp
	jcr.cpp
	runscript.cpp
	diff/diff.c
	lib/alist.cpp
	lib/bfile.cpp
	lib/sha1.c
	sql/dbs.cpp
)

INCLUDE_DIRECTORIES(. lib/ sql/ diff/ /usr/include/mysql)

LINK_DIRECTORIES(/usr/lib/mysql)

ADD_EXECUTABLE(backup ${SRC_LIST})

TARGET_LINK_LIBRARIES(backup mysqlclient)
