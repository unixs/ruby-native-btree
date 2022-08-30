# frozen_string_literal: true

require "bundler/gem_tasks"
require "rspec/core/rake_task"

RSpec::Core::RakeTask.new(:spec)

require "rubocop/rake_task"

RuboCop::RakeTask.new

task default: %i[rubocop spec]

BUILD_DIR = "build"

namespace :cmake do
  desc "Remove build directory"
  task :rmbuild do
    sh "rm -rvf #{BUILD_DIR}"
  end

  desc "Configure ext CMake project"
  task configure: %i[cmake:rmbuild] do
    sh "cmake . -B #{BUILD_DIR}"
  end

  desc "Build ext CMake project"
  task build: %i[cmake:configure] do
    sh "cmake --build #{BUILD_DIR}"
  end

  desc "`Rebuild ext CMake project"
  task rebuild: %i[cmake:configure] do
    sh "cmake --build #{BUILD_DIR} --clean-first"
  end

  desc "Clean ext CMake project"
  task :clean do
    sh "cmake --build #{BUILD_DIR} --target clean"
  end
end
