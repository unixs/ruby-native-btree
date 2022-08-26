FROM ruby:2.7

RUN mkdir -p /home/gem
WORKDIR /home/gem
COPY . .
RUN apt-get update && \
  apt-get -y upgrade && \
  apt-get -y install cmake && \
  gem install bundler && \
  bundle install && \
  rake build && \
  gem install pkg/native_btree-0.1.0.alpha1.gem
