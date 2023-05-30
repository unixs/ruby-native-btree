#! /bin/bash

source $DEV_HOME/.rvm/scripts/rvm

env
gem env

rvm list

pwd

gem install bundler
bundle config set --local path "vendor/ruby"
bundle config set --local without development
bundle install
bundle exec rake cmake:build
bundle exec rake spec
