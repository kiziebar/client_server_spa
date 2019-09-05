BUILD_DIR = ./bin

DIRS=${BUILD_DIR}

SOURCE_SERVER = ./src/server.c
SOURCE_CLIENT = ./src/client.c

APP_C=${BUILD_DIR}/cli.out
APP_S=${BUILD_DIR}/serv.out

CC=gcc
CFLAGS= -g -Wall

build: dirs ${APP_C} ${APP_S}

dirs:
	@mkdir -p ${DIRS}

${APP_S}: ${SOURCE_SERVER} ${SOURCE_CLIENT}
	${CC} ${CFLAGS} ${SOURCE_SERVER} -o $@

${APP_C}: ${SOURCE_SERVER} ${SOURCE_CLIENT}
	${CC} ${CFLAGS} ${SOURCE_CLIENT} -o $@
