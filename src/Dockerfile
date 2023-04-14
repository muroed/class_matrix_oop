FROM ubuntu:latest
ARG DIR=../

# Fix enter timezone issue
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install sudo build-essential cmake valgrind gcc libcppunit-dev -y

COPY ${DIR} /${DIR}
RUN make test && make valgrind

WORKDIR /${DIR}
cmd cat val.txt