# Базовый образ
FROM ubuntu:focal

# Переменные окружения
ENV RUBY_TEST_VER=3.2.2
ENV TZ=UTC
ENV DEV_USER=developer
ENV DEV_HOME=/home/${DEV_USER}
ENV DEV_PATH=${DEV_HOME}/gem

# Установка необходимых зависимостей
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && \
  echo $TZ > /etc/timezone && \
  apt-get update && \
  apt-get -y upgrade && \
  apt-get -y install mc cmake gcovr libglib2.0-dev build-essential curl sudo \
    gawk autoconf automake bison libgdbm-dev libncurses5-dev libsqlite3-dev libtool \
    libyaml-dev sqlite3 libgmp-dev libreadline-dev openssl libssl-dev && \
  apt-get clean && \
  useradd -G sudo -ms /bin/bash ${DEV_USER} && \
  echo "$DEV_USER   ALL=(ALL:ALL) NOPASSWD:ALL" >> /etc/sudoers.d/${DEV_USER} && \
  su - ${DEV_USER} -c "mkdir ${DEV_PATH}"

# Смена пользователя по-умолчанию и рабочего каталога
USER ${DEV_USER}
SHELL [ "/bin/bash", "-l", "-c" ]
RUN gpg --keyserver keyserver.ubuntu.com --recv-keys 409B6B1796C275462A1703113804BB82D39DC0E3 7D2BAF1CF37B13E2069D6956105BD0E739499BDB && \
  curl -sSL https://get.rvm.io | bash && \
  source /home/${DEV_USER}/.rvm/scripts/rvm && \
  rvm install ${RUBY_TEST_VER}

WORKDIR ${DEV_PATH}

ENTRYPOINT ["/bin/bash", "-l"]
