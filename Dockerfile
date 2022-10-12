FROM ubuntu

ENV WORK_DIR_PATH=/home/app/alt-linux
ENV BUILD_DIR_PATH=${WORK_DIR_PATH}/build
ENV EXTERNAL_DIR_PATH=${WORK_DIR_PATH}/external/

WORKDIR ${WORK_DIR_PATH}
COPY . .

# Install tools
RUN apt-get update
RUN apt-get -y install g++ cmake make git libgtest-dev libcurl4-gnutls-dev
RUN bash install.sh
