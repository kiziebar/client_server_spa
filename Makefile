BUILD_DIR = ./bin

DIRS=${BUILD_DIR}

SOURCE_SERVER = ./tcp/server.c
SOURCE_CLIENT = ./tcp/client.c
SOURCE_FUNCTIONS = ./tcp/functions.c

APP_C=${BUILD_DIR}/cli.out
APP_S=${BUILD_DIR}/serv.out

CC=gcc
CFLAGS= -g -Wall

build: dirs ${APP_C} ${APP_S}

dirs:
	@mkdir -p ${DIRS}

${APP_S}: ${SOURCE_SERVER} ${SOURCE_CLIENT}
	${CC} ${CFLAGS} ${SOURCE_SERVER} ${SOURCE_FUNCTIONS} -o $@

${APP_C}: ${SOURCE_SERVER} ${SOURCE_CLIENT}
	${CC} ${CFLAGS} ${SOURCE_CLIENT} -o $@
