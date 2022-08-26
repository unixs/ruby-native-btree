# frozen_string_literal: true

require "bundler/gem_tasks"
require "rspec/core/rake_task"

RSpec::Core::RakeTask.new(:spec)

require "rubocop/rake_task"

RuboCop::RakeTask.new

task default: %i[rubocop spec]

namespace :cmake do
  desc "Configure ext CMake project"
  task :configure do
    sh "cmake . -B build"
  end

  desc "Build ext CMake project"
  task build: %i[cmake:configure] do
    sh "cmake --build build"
  end

  desc "`Rebuild ext CMake project"
  task rebuild: %i[cmake:configure] do
    sh "cmake --build build --clean-first"
  end

  desc "Clean ext CMake project"
  task :clean do
    sh "cmake --build build --target clean"
  end
end
