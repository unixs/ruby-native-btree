pipeline {
  agent none

  stages {
    stage('codecheck') {
      agent { docker 'unixs/ruby-cmake' }
      steps {
        sh 'ruby --version'
        sh 'gem env'
        sh 'gem install bundler'
        sh 'bundle config set --local path "vendor/ruby"'
        sh 'bundle config set --local without development'
        sh 'bundle install'
        sh 'bundle exec rake rubocop'
      }
    }

    stage('test legacy') {
      agent { docker 'unixs/ruby-btree-tests:legacy' }
      steps {
        sh 'ruby --version'
        sh 'gem env'
        sh 'gem install bundler'
        sh 'bundle config set --local path "vendor/ruby"'
        sh 'bundle config set --local without development'
        sh 'bundle install'
        sh 'bundle exec rake cmake:build'
        sh 'bundle exec rake spec'
      }
    }

    stage('test latest') {
      agent { docker 'unixs/ruby-btree-tests' }
      steps {
        sh 'ruby --version'
        sh 'gem env'
        sh 'gem install bundler'
        sh 'bundle config set --local path "vendor/ruby"'
        sh 'bundle config set --local without development'
        sh 'bundle install'
        sh 'bundle exec rake cmake:build'
        sh 'bundle exec rake spec'
      }
    }
  }
}
