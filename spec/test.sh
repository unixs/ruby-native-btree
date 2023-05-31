#! /bin/bash

source $DEV_HOME/.bash_profile

export HOME=$DEV_HOME

env
gem env

rvm list
rvm use 3.2

bundle config set --local path "vendor/ruby"
bundle config set --local without development
bundle install
bundle exec rake cmake:rmbuild
bundle exec rake cmake:rebuild
bundle exec rake spec
