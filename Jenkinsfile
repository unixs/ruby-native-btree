pipeline {
  agent {
    docker { image 'unixs/ruby-cmake' }
  }

  stages {
    stage('codecheck') {
      steps {
        sh 'ruby --version'
      }
    }
  }
}
