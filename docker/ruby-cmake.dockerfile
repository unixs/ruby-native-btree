# Базовый образ
FROM ruby:3.2

# Переменные окружения
ENV DEV_USER=developer
ENV DEV_HOME=/home/${DEV_USER}
ENV DEV_PATH=${DEV_HOME}/gem

# Установка необходимых зависимостей
RUN apt-get update && \
  apt-get -y upgrade && \
  apt-get -y install mc cmake gcovr libglib2.0-dev build-essential && \
  apt-get clean && \
  useradd -ms /bin/bash ${DEV_USER} && \
  su - ${DEV_USER} -c "mkdir ${DEV_PATH}"

# Смена пользователя по-умолчанию и рабочего каталога
USER ${DEV_USER}
WORKDIR ${DEV_PATH}

