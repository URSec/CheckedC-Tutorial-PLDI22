# A Tutorial on Checked C

Please `git clone` this repo to you OS. It contains the script to install and
run our docker image, and also the sample code used to in this tutorial.

##  Install Docker and Docker Compose

### For all OS
Download and install Docker from [https://docs.docker.com/engine/install/](https://docs.docker.com/engine/install/).

### For Debian-based Linux
If you're using a Debian-based Linux such as Ubuntu, you can use our script
to download and install docker:

```shell
sudo ./run.sh install
```

## Launch and enter the docker image from a terminal
After `docker` and `docker-compose` are installed, you can launch a docker
container by running the `run` script. The script will automatically download
the docker image the first time you run it, and launches a container.

### Linux/MacOS
```shell
./run.sh
```

### Windows
For Windows Users, double click `run.bat` to launch the shell.


## Using the Container

The Checked C compiler is located at `/checkedc/bin/clang-12`, the environment variable `$CC` is also set to that location.

The folder `/tutorial` maps to the local git repository, so any changes to this folder will be reflected to `/tutorial` in the docker container.
The container has `vim` pre-installed. You can also directly modify files from your host system.

## Directory Structure

```shell
tutorial                    # root directory for the whole project
|-- 3c                      # examples for 3c
|   |-- libjpeg             # libjpeg library
|   |-- tiny-bignum-c       # tiny-bignum-c library
|-- linkedlist              # simple example that demonstrates a linkedlist
|-- sum2array               # simple example that adds up two arrays
|-- tiny-bignum             # tiny-bignum-c library
|-- docker-compose.yaml     # docker setup file
|-- run.sh                  # launch shell from MacOS and Linux
|-- run.bat                 # Launch shell from Windows
```
