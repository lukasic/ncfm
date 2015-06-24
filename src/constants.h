#pragma once

#define CTRLD 	4

#define PATH_SEPARATOR    "/"
#define PATH_SEPARATOR_CH '/'

#define LOGFILE  "debug.log"
#define LOGLEVEL 3


extern const char * BottomMenu[];
extern const char * HeaderMenu[];


#define CMD_CLEAR	"clear"
#define CMD_EDITOR	"vim"
#define CMD_MOVE    "mv"
#define CMD_CP      "cp -R"
#define CMD_RM      "echo -rf"
#define CMD_VIEW    "hexdump -C"
#define CMD_SYMLNK  "ln -s"
#define CMD_MKDIR   "mkdir"
#define CMD_RENAME  "mv"
#define CMD_LESS    "less"

#define AWK			"awk 'BEGIN{ OFS=\"#\"; }{ print $9, $6 \" \" $7 \" \" $8, $5, $3 \":\" $4, $1 }' | sort -n"
