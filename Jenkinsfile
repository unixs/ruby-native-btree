pipeline {
  agent none

  stages {
    stage('codecheck') {
      agent { docker 'unixs/ruby-cmake' }
      steps {
        sh 'make codecheck'
      }
    }

    stage('test latest') {
      agent { docker 'esxiyaru/ruby-btree-tests:legacy' }
      steps {
        sh './spec/test.sh'
      }
    }
  }
}
