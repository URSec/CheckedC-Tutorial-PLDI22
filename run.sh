#!/usr/bin/env bash

#
# This script (first downloads if not existed and) launches the docker image
# for this tutoria.
#

DOCKER_INSTALL_CMD="sudo apt-get install docker-ce docker-ce-cli containerd.io"
DOCKER_COMPOSE_INSTALL_CMD="curl -L https://github.com/docker/compose/releases/download/1.29.2/docker-compose-$(uname -s)-$(uname -m) -o /usr/local/bin/docker-compose"

#
# Initialize the environment.
#
init() {
    if [[ $1 == "install" ]]; then
        install
        exit
    fi

    # Check if docker is installed.
    if [[ ! `which docker` ]]; then
        echo "Please first install docker and docker-compose."
        echo "On Linux, run "
        echo "sudo $DOCKER_INSTALL_CMD"
        echo "and "
        echo "sudo $DOCKER_COMPOSE_INSTALL_CMD"
        echo ""
        echo "Or you can directly use this script to install docker by \"sudo ./run install\""

        exit
    fi

    # Check if docker-compose is installed
    if [[ ! `which docker-compose` ]]; then
        echo "Please install docker-compose"
        echo "On Linux, run "
        echo "sudo $DOCKER_COMPOSE_INSTALL_CMD"
        echo ""
        echo "Or you can directly use this script to install docker-compose by \"sudo ./run install\""

        exit
    fi
}

#
# Install docker and docker-compose
#
install() {
    if [[ ! `which docker` ]]; then
        $DOCKER_INSTALL_CMD
    fi

    if [[ ! `which docker-compose` ]]; then
        sudo $DOCKER_COMPOSE_INSTALL_CMD
        sudo chmod +x /usr/local/bin/docker-compose
        exit
    fi
}

#
# Entrance of this script
#
init $1

#
# Launch the tutorial image.
#
docker-compose run tutorial bash
