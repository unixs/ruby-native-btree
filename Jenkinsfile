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
      agent { docker 'unixs/ruby-btree-tests:legacy' }
      steps {
        sh 'make test'
      }
    }

    stage('test latest') {
      agent { docker 'unixs/ruby-btree-tests' }
      steps {
        sh 'make test'
      }
    }
  }
}
