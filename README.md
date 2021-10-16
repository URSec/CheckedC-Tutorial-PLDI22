# A Tutorial on Checked C

## Setup and Installation

Download and Install Docker from [https://docs.docker.com/engine/install/](https://docs.docker.com/engine/install/).

You will need to clone this repository locally:

> git clone https://github.com/URSec/CheckedC-Tutorial-SecDev21.git

Command to setup the docker container and to use the terminal from within the container:

> docker-compose run tutorial bash

## Using the Container

The Checked C compiler is located at `/checkedc/bin/clang-12`, the environment variable `$CC` is also set to that location.

The folder `/tutorial` maps to the local git repository, so any changes to this folder will be reflected to `/tutorial` in the docker container.
The container has `vim` pre-installed. You can also directly modify files from your host system.

## Folder Structure

- /tutorial/
    - 3c/
        - libjpeg/
        - tiny-bignum-c/
    - linkedlist/
    - sum2array/
    - tiny-bignum/
