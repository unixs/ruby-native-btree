pipeline {
  agent none

  stages {
    stage('codecheck') {
      agent { docker 'unixs/ruby-cmake' }
      steps {
        sh 'make codecheck'
      }
    }

    stage('test legacy') {
      agent { docker 'unixs/ruby-cmake' }
      steps {
        sh 'make test'
      }
    }
  }
}
