FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y g++ \
    && apt-get install -y cmake \
    && apt-get install -y lsof \
    && apt-get install -y iputils-ping \
    && apt-get install -y net-tools \
    && apt-get install -y vim \
    && apt-get install -y ssh \
    && apt-get install -y libssl-dev \
    && apt-get install -y gdb \
    && echo "root:flzx3000c" | chpasswd

COPY sshd_config.bak /etc/ssh/sshd_config

ENV LD_LIBRATY_PATH=./
CMD [ "/etc/init.d/ssh" "start"]
