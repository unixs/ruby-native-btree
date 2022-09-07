# frozen_string_literal: true

require "bundler/gem_tasks"

begin
  require "rspec/core/rake_task"
  RSpec::Core::RakeTask.new(:spec)
rescue LoadError
  warn "RSpec rake tasks was not loaded"
end

begin
  require "rubocop/rake_task"
  RuboCop::RakeTask.new
rescue LoadError
  warn "Rubocop rake tasks was not loaded"
end

task default: %i[cmake:build]

BUILD_DIR = "build"

namespace :cmake do
  desc "Remove build directory"
  task :rmbuild do
    sh "rm -rf #{BUILD_DIR}"
  end

  desc "Configure ext CMake project"
  task :configure do
    sh "mkdir #{BUILD_DIR} || true"
    sh "cd #{BUILD_DIR} && cmake .."
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
