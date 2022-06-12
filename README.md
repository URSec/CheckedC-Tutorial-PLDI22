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

## Launch and enter an docker container from a terminal
After `docker` and `docker-compose` are installed, you can launch a docker
container by running the `run` script. The script will automatically download
the docker image the first time you run it, and launches a container.

### Linux/MacOS
```shell
./run.sh
```

### Windows
For Windows users, double click `run.bat` to launch the shell.


## Using the Container

The Checked C compiler is located at `/checkedc/bin/clang-12`, the environment variable `$CC` is also set to that location.

The folder `/tutorial` maps to the local git repository, so any changes to this folder on your local machine will be reflected to `/tutorial` in the docker container.
The container has `vim` pre-installed. You can also directly modify files from your host system with your favoriate editor.

## Directory Structure

```shell
tutorial                    # Root directory for the whole project
|-- 3c                      # Examples for 3c
|   |-- tiny-bignum-c       # Tiny-bignum-c source code
|-- linkedlist              # Simple example that demonstrates a linkedlist
|-- sum2array               # Simple example that adds up two arrays
|-- tiny-bignum             # Tiny-bignum-c 
|-- docker-compose.yaml     # Docker setup file
|-- run.sh                  # Launch shell from MacOS and Linux
|-- run.bat                 # Launch shell from Windows
```
