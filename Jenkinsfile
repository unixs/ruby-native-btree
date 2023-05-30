pipeline {
  agent none

  stages {
    stage('codecheck') {
      agent { docker 'unixs/ruby-cmake' }
      steps {
        sh 'env'
        sh '''#!/bin/bash -l
          make codecheck
        '''
      }
    }

    stage('test legacy') {
      agent { docker 'unixs/ruby-btree-tests:legacy' }
      steps {
        sh '''#!/bin/bash -l
          make test
        '''
      }
    }

    stage('test latest') {
      agent { docker 'unixs/ruby-btree-tests' }
      steps {
        sh '''#!/bin/bash -l
          make test
        '''
      }
    }
  }
}
