# Базовый образ
FROM ubuntu:latest

# Переменные окружения
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
    libyaml-dev sqlite3 libgmp-dev libreadline-dev openssl libssl-dev \
    ruby ruby-dev && \
  apt-get clean && \
  gem install bundler && \
  useradd -G sudo -ms /bin/bash ${DEV_USER} && \
  echo "$DEV_USER   ALL=(ALL:ALL) NOPASSWD:ALL" >> /etc/sudoers.d/${DEV_USER} && \
  su - ${DEV_USER} -c "mkdir ${DEV_PATH}"

# Смена пользователя по-умолчанию и рабочего каталога
USER ${DEV_USER}

WORKDIR ${DEV_PATH}

ENTRYPOINT ["/bin/bash", "-l"]
