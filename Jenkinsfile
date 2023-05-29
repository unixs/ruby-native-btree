pipeline {
  agent {
    docker { image 'unixs/ruby-cmake' }
  }

  stages {
    stage('codecheck') {
      steps {
        sh 'ruby --version'
        sh 'gem install bundler'
        sh 'bundle config set --local path "vendor/ruby"'
        sh 'bundle config set --local without development'
        sh 'bundle install'
        sh 'bundle exec rake rubocop'
      }
    }
  }
}
