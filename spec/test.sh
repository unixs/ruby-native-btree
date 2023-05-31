#! /bin/bash

source $DEV_HOME/.rvm/scripts/rvm

export HOME=$DEV_HOME

env
gem env


rm -rvf vendor/ruby
bundle config set --local path "vendor/ruby"
bundle config set --local without development
bundle install
bundle exec rake cmake:rmbuild
bundle exec rake cmake:rebuild
bundle exec rake spec
