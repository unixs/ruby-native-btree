FROM unixs/ruby-cmake:2.7 AS build

COPY --chown=${DEV_USER}:${DEV_USER} . .

RUN gem install bundler && \
  bundle install && \
  rake cmake:build && \
  rake spec && \
  rake install && \
  ruby -e 'require "native_btree"'


FROM ruby:2.7

