FROM 2000jedi/checkedc:latest
RUN apt-get install -y python3 python3-pip git imagemagick
RUN pip3 install entangled-filters
RUN echo 'export PATH=$HOME/.local/bin:$PATH' >> ~/.bashrc
RUN echo 'cd tutorial' >> ~/.bashrc
