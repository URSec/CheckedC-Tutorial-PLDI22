FROM ubuntu:latest
ENV DEBIAN_FRONTEND="noninteractive" TZ="Europe/London"
ENV CC="/code/build/bin/clang-12"
COPY . /code/
RUN apt-get update
RUN apt-get install -y build-essential clang cmake
