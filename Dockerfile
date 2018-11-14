FROM ubuntu:16.04

RUN apt-get update
RUN apt-get install -y git gcc g++ python python-dev mercurial python-setuptools qt5-default python-pygraphviz python-kiwi \
  python-pygoocanvas libgoocanvas-dev ipython gir1.2-goocanvas-2.0 python-gi python-gi-cairo python-pygraphviz python3-gi \
  python3-gi-cairo python3-pygraphviz gir1.2-gtk-3.0 ipython ipython3 openmpi-bin openmpi-common openmpi-doc libopenmpi-dev \
  autoconf cvs bzr unrar gdb valgrind uncrustify doxygen graphviz imagemagick texlive texlive-extra-utils texlive-latex-extra \
  texlive-font-utils texlive-lang-portuguese dvipng python-sphinx dia gsl-bin libgsl2 libgsl-dev flex bison libfl-dev \
  tcpdump sqlite sqlite3 libsqlite3-dev libxml2 libxml2-dev cmake libc6-dev libc6-dev-i386 libclang-dev llvm-dev automake \
  libgtk2.0-0 libgtk2.0-dev vtun lxc libboost-signals-dev libboost-filesystem-dev python-pip castxml
RUN mkdir /opt/ns3
WORKDIR /opt/ns3
RUN git clone -b ns-3.29 https://github.com/nsnam/ns-3-dev-git.git ns-3.29
WORKDIR /opt/ns3/ns-3.29
RUN pip install PyBindGen cxxfilt pygccxml
RUN ./waf configure && ./waf
WORKDIR /opt/ns3
RUN hg clone http://code.nsnam.org/netanim
WORKDIR /opt/ns3/netanim
RUN qmake NetAnim.pro && make
WORKDIR /opt/ns3/ns-3.29
RUN echo 'alias NetAnim=/opt/ns3/netanim/NetAnim' >> ~/.bashrc

