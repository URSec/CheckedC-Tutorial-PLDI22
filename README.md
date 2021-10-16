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
After `docker` and `docker-compose` are installed, you can launch the docker
image by running:

```shell
./run.sh
```

## Folder Structure

- /tutorial/
    - 3c/
        - libjpeg/
        - tiny-bignum-c/
    - linkedlist/
    - sum2array/
    - tiny-bignum/
