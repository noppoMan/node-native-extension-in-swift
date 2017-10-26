FROM ubuntu:14.04

RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y clang \
  libicu-dev \
  libbsd-dev \
  uuid-dev \
  git \
  libxml2-dev \
  libxslt1-dev \
  python-dev \
  libcurl4-openssl-dev \
  wget \
  zip \
  make \
  g++ \
  xz-utils

RUN update-alternatives --install /usr/bin/ld ld /usr/bin/ld.gold 9
RUN update-alternatives --set ld /usr/bin/ld.gold

ENV SWIFT_HOME=swift-4.0-RELEASE-ubuntu14.04
ENV SWIFT_DOWNLOAD_URL=https://swift.org/builds/swift-4.0-release/ubuntu1404/swift-4.0-RELEASE/$SWIFT_HOME.tar.gz
RUN wget $SWIFT_DOWNLOAD_URL
RUN tar -zxf $SWIFT_HOME.tar.gz
ENV PATH $PWD/$SWIFT_HOME/usr/bin:"${PATH}"

ENV NODE_HOME=node-v8.8.1-linux-x64
ENV NODE_DOWNLOAD_URL=https://nodejs.org/dist/v8.8.1/$NODE_HOME.tar.xz
RUN wget $NODE_DOWNLOAD_URL
RUN tar xf ./$NODE_HOME.tar.xz
ENV PATH $PWD/$NODE_HOME/bin:"${PATH}"

RUN npm i -g node-gyp

COPY . node-native-extension-in-swift

WORKDIR node-native-extension-in-swift

CMD /bin/bash ./linux-run.sh
