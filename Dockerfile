FROM 2000jedi/checkedc:latest
RUN echo 'alias clang="clang-12"' >> ~/.bashrc
RUN echo 'cd tutorial' >> ~/.bashrc
