SHELL := /bin/bash -l

default_target: build
.PHONY : default_target

build: deps
	bundle exec rake cmake:build
.PHONY : build

deps:
	gem install bundler
	bundle config set --local path "vendor/ruby"
	bundle config set --local without developmen
	bundle install
.PHONY : deps

codecheck: deps
	bundle exec rake rubocop
.PHONY : codecheck

test: build
	bundle exec rake spec
.PHONY : rebuild
